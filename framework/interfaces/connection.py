"""IronPython interface for Granite <-> phone connection using .NET Communication Adapter."""


# Python library module imports
import sys, time, types, os
import clr

# Granite imports
import core
from core import debug

clr.AddReference('Nokia.Trident.Phone')
clr.AddReference('Nokia.RD.Framework')
clr.AddReference('Nokia.RD.Tracing')
clr.AddReference('MessageAPI')
clr.AddReference('MessageAPI.Commgr')
clr.AddReference('MessageAPI.Key')
clr.AddReference('MessageAPI.Touchpad')
clr.AddReference('Interop.DeviceScannerLib')
clr.AddReference('MessageAPIMessageSender')
clr.AddReference('ConnectionMocker')


from Nokia.Trident.Phone import CommunicationException, FuseConnectionParameter, \
                                EnumFileSystemItemAttributeType, CommunicationAdapter, FuseManager, \
                                FileServerAdapter, TestCaseException
from Nokia.RD.CoreTestTool import Log, ConnectionManager
from Nokia.RD.Communication import MessageSender, ConnectionParameters
from Nokia.RD.Tracing.PMD import PMDLoader #, PMDMessageRule
from Nokia.RD.Tracing.PMD.Encoding import Encoder
from Nokia.RD.Tracing.Decoding import MessageDecoder, InterpretationType
from Nokia.RD.Tracing.TraceActivation import TraceActivator

from Nokia.RD.MessageAPI import PhonetResource, IsiVersion, MessageAPIFactory, IteratorFactory #, MessageIdRule
from Nokia.RD.MessageAPI.Commgr.Messages import PnsSubscribedResourcesInd
from Nokia.RD.MessageAPI.Touchpad.Messages import TouchpadPenEventsReq, TouchpadPenEventsResp, TouchpadPenEventNtf
from Nokia.RD.MessageAPI.Touchpad.Subblocks import TouchpadSbPenStateInfo, TouchpadSbDisplayCoordinateData, TouchpadSbTimestamp
from Nokia.RD.MessageAPI.Touchpad.Tables import TouchpadPenEventsAction, TouchpadCoordinateType, TouchpadPenEventsStatus
from Nokia.RD.MessageAPI.Touchpad.Tables import TouchpadPenEventsAction, TouchpadCoordinateType, TouchpadPenEventsStatus

from Nokia.RD import PhonetMessage, TimestampType, TimestampPresentation, Timestamp, ByteCompareMessageRule
from ExecutionForm.UnitTest import ConnectionMocker

from System import Byte, TimeSpan, Double, DateTime, String, Array, Enum, Char, BitConverter, Console
from System.IO import File, Path 
from System.Diagnostics import TraceListener
from System.Threading import Thread, ParameterizedThreadStart
from System.Collections.Generic import List
from System.Text.RegularExpressions import Regex

from DeviceScannerLib import DeviceMapClass, DeviceAndProductScannerClass, Devices, DevicesAndProducts, EnumDeviceTypes, EnumScanDeviceType, EnumScanMedia

from utils import include
pn = include.Include('pn_const.h')

class GraniteConnectionException(Exception):
    """Exception class for connection exceptions."""
    def __init__(self, errorString = None):
        Exception.__init__(self)
        self._errorString = errorString

    def __unicode__(self):
        return '%s' % self._errorString

    def __str__(self):
        return '%s' % self._errorString

class GraniteFileSystemException(Exception):
    """Exception class for file system exceptions."""
    def __init__(self, fileSystemException):
        Exception.__init__(self)
        self.fileSystemException = fileSystemException

    def __unicode__(self):
        #return '%s' % self.fileSystemException[2].splitlines()[0]
        return '%s' % self.fileSystemException

    def __str__(self):
        #return '%s' % self.fileSystemException[2].splitlines()[0]
        return '%s' % self.fileSystemException
        
    #def __int__(self):
    #    return self.fileSystemException[5]       
    
class XmlTraceActivator(object) :

    def __init__(self, connection, pmdLoader, messageSender) :

        self.nRegId = 0
        self.activateEnd = False
        self.connection = connection
        self.pmdLoader = pmdLoader
        self.messageSender = messageSender
        self.activator = TraceActivator.Instance(self.pmdLoader, self.messageSender)
        self.activator.ActivateEnd += self._activator_activate_end

    def activator_activate_end(self, sender) :
        self._activateEnd = True

    def _activate(self) :

        if not self.connection.IsConnected :
            raise

        if not self.pmdLoader.IsLoaded :
            raise
        
        try :

            self.activator.AllDirty()
            self.activator.Activate()

            while not self.activateEnd :

                Thread.CurrentThread.Join(100)

            self.activateEnd = False

        except Exception, exc :
            raise

    def _deactivate(self) :

        if not self.connection.IsConnected :
            raise

        if not self.pmdLoader.IsLoaded :
            raise
        
        try :

            self.activator.Unregister(self.nRegId)
            self.activator.Activate()
            
            while not self.activateEnd :

                Thread.CurrentThread.Join(100)

            self.activateEnd = False

        except Exception, exc :
            raise


    def dispose(self) :

        if self.activator :
            self.activator.Dispose()

class PMDFileHandler(object):
    """Handles PMD file loading and unloading."""
    def __init__(self, pmdFilePath, pmdLoaderInstance):
        self.__loader = pmdLoaderInstance #PMDLoader()
        
        assert os.path.isfile(pmdFilePath), \
            'Invalid PMD file given: %s' % pmdFilePath        
        self.__pmdFile = pmdFilePath
        self.__currentPmdFile = ''
                
    def load(self, pmdFile = ''):
        """Loads PMD file.
        
            Parameters
            
            pmdFile     PMD file path (if not given, self.__pmdFile is used)
        """
        if not pmdFile:
            pmdFile = self.__pmdFile
        
        #if self.__loader.IsDisposed:
        #    self.__loader = PMDLoader()
    
        if self.__currentPmdFile and \
           pmdFile != self.__currentPmdFile:
            debug.out('Unloading current PMD file before loading new one')
            self.unLoad()
    
        if not self.isLoaded() and \
           pmdFile and isinstance(pmdFile, String) and \
           not String.IsNullOrEmpty(pmdFile) and File.Exists(pmdFile):
            debug.brf("Loading " + Path.GetFileName(pmdFile))
            self.__loader.Load(pmdFile)
            self.__currentPmdFile = pmdFile
    
    def unLoad(self):
        self.__loader.Unload()
        self.__currentPmdFile = ''
    
    def isLoaded(self):
        return self.__loader.IsLoaded
        
    def getLoader(self):
        return self.__loader
        
    def dispose(self):
        self.__loader.Dispose()
        self.__loader = None

    
#class ConnectionMockerThread(threading.Thread):
#    """Thread for running connection mocker."""
#    def __init__(self, blxFilePath, tcpPort = 7656):
#        """Initializes variables and starts the thread."""
#        threading.Thread.__init__(self)
#        self.__blxFilePath = blxFilePath
#        self.__tcpPort = tcpPort
#        self.setDaemon(True)
#        
#    def run(self):
#        """Runs thread activity."""
#        connectionMocker = ConnectionMocker(self.__tcpPort)
#        connectionMocker.OpenBlx(self.__blxFilePath)
#
#        while True:
#            pass
        
        
# ============================================================================
class GraniteConnection(object):
    """A class that maintains a Phonet message connection with a phone."""
    # take filter values from win32com's constants
##    CONN_FILTER = { 'fcEmpty': constants.eMessagingFilterCommandEmpty,
##                    'fcIndex': constants.eMessagingFilterCommandIndex,
##                    'fcEqual': constants.eMessagingFilterCommandEqual,
##                    'fcLess': constants.eMessagingFilterCommandLess,
##                    'fcGreater': constants.eMessagingFilterCommandGreater,
##                    'fcBetween': constants.eMessagingFilterCommandBetween,
##                    'fcArray': constants.eMessagingFilterCommandArray,
##                    'fcList': constants.eMessagingFilterCommandList,
##                    'fcNot': constants.eMessagingFilterCommandNot,
##                    'fcAnd': constants.eMessagingFilterCommandAnd,
##                    'fcOr': constants.eMessagingFilterCommandOr,
##                    'fcLogAnd': constants.eMessagingFilterCommandLogAnd,
##                    'fcLogOr': constants.eMessagingFilterCommandLogOr }

    def __init__(self, pmdFilePath): 
        # default timeout for send and recv functions
        self.defaultTimeout = 5000

        self.PMDFileHandler = None
        self.__pmdFilePath = pmdFilePath
        
        self.CommunicationAdapter = None
        		
        self.MessageSender = None
        self.MessageApiSender = None

        self.Connection = None
        
        self.ConnectionManager = None
               
        self.BinaryLog = None

        self.Decoder = None

        self.Encoder = None
        
        self.fileSystem = None

        self.subscribedResources = List[PhonetResource]()

        self.internallySubscribedKeyindications = False
        self.externallySubscribedKeyindications = False
                        
        self.EnumFileSystemItemAttributeType = EnumFileSystemItemAttributeType
        
        self.__connectionMockerInUse = False
        
        self.connBusName = None
        
        self.__traceMessages = []
        self.__traceLogCleared = False

    def initPMDdependentModules(self):
        if not self.isPMDLoaded() :
            raise GraniteConnectionException('Connection needs a proper PMD file!')

        self.PMDLoader = self.PMDFileHandler.getLoader()                

        self.Decoder = MessageDecoder(self.PMDLoader)        
        self.Decoder.Interpretation = InterpretationType.SingleLinePMD
        self.Decoder.AddHex = False
        self.Decoder.FirstTimestamp = TimestampType.None #TimestampType.PCAbsolute
        self.Decoder.FirstTimestampPresentation = TimestampPresentation.Milliseconds
        self.Decoder.SecondTimestamp = TimestampType.None

        #self.Encoder = Encoder(self.PMDLoader)        

    def _dataReceived(self, sender, args):
        # return right away if there's no data to process
        if not args:
            return
        
        # process data if tracing is enabled and debug level is high enough
        if core.FW_conf['tracing_enabled'] and debug.level >= 2:
            timestamp = DateTime.Now.ToString("HH:mm:ss:FFFFFF").PadRight(15, Char.Parse('0'))

            # send trace data to stderr when launched with GUI, in cli mode to file        
            try:
                traceString = ''

                if self.Decoder:
                    phonet = None
                                        
                    try:
                        phonet = PhonetMessage(args.Data)
                        traceString = timestamp + ':' + self.Decoder.Decode(phonet)
                    except Exception, err:
                        debug.out('Unable to decode message for tracing')
                    finally:
                        if phonet:
                            phonet.Dispose()
                else:
                    traceString = timestamp + ':' + args.Direction == DirectionType.In and "<- " or "-> " + \
                                  BitConverter.ToString(args.Data).Replace('-', ',')

                if core.FW_conf['cli_mode']:
                    # in command line mode we write trace data to file
                    if traceString:
                        self.__writeTraceStringToLog(traceString)
                else:
                    # in GUI mode we push trace data to stderr
                    if (len(traceString) > 300):
                        traceString = traceString[:300] + '...'
                
                    if traceString:
                        Console.Error.WriteLine(traceString)
                        Console.Error.Flush()
            except Exception, err:
                debug.out('Unable to decode/write message for tracing')

    def __writeTraceStringToLog(self, traceString):
        """Writes trace string to log file in cli mode."""        
        cliTraceDir = os.path.join(core.FW_conf['test_result_dir'], 'trace_data')
        cliTraceFileName = os.path.join(cliTraceDir, core.FW_conf['test_result_name'] + '.txt')
                
        if not os.path.isdir(cliTraceDir):
            os.makedirs(cliTraceDir)          
            
        if not self.__traceLogCleared and os.path.isfile(cliTraceFileName):
            os.remove(cliTraceFileName)
            self.__traceLogCleared = True

        if not core.FW_conf['test_result_name']:                        
            self.__traceMessages.append(traceString)
        else:
            cliTraceFile = open(cliTraceFileName, 'a')        
        
            if self.__traceMessages:
                for trace in self.__traceMessages:
                    cliTraceFile.write(trace + '\n')
                    
                self.__traceMessages = []

            cliTraceFile.write(traceString + '\n')
            cliTraceFile.close()            
               
    def isConnected(self) :

        """
        Checks if connection is connected
        """           
        try:
            if self.CommunicationAdapter and self.CommunicationAdapter.IsConnected:
                return True
            else:
                return False
        except Exception, err:
            raise GraniteConnectionException(str(err))
    
    def isConnectedDevice(self) :

        """
        Checks if connection is connected to device
        """

        return self.Connection and self.Connection.IsConnectedDevice


    def isConnectedMedia(self) :

        """
        Checks if connection is connected to media
        """

        return self.Connection and self.Connection.IsConnectedMedia


    def isDisconnected(self) :
        
        """
        Checks if connection is disconnected
        """
        
        return self.Connection and self.Connection.IsDisconnected

    
    def isPMDLoaded(self) :
        
        """
        Checks if PMD file is loaded properly
        """
        
        return self.PMDFileHandler and self.PMDFileHandler.isLoaded()

    
    def startBlxRecording(self, blxFilename) :
        
        """
        Start blx recording
        
        Parameters
        
        blxFilename		Name of the blx file to be recorded, in format
        			'C:\\TEST\\log.blx' or 'C:\\TEST\log' (extension is added automatically)
        """
        
        try :

            if self.isConnected() :

                if not String.IsNullOrEmpty(blxFilename) :
                    
                    if self.CommunicationAdapter :

                        if blxFilename.ToLower().EndsWith(".blx") and blxFilename.Length > 4 :
                            blxFilename = blxFilename.Substring(0, blxFilename.LastIndexOf("."))

                        self.CommunicationAdapter.StartBlxRecording(blxFilename)

                else :

                    raise GraniteConnectionException('File name for blx log must be defined')

            else :

                raise GraniteConnectionException('Nokia.RD.Connection is not open.')
                    

        except CommunicationException, exc :
            raise GraniteConnectionException('Error occured when starting blx recording: ' + str(exc))


    def stopBlxRecording(self) :

        """
        Stops blx recording
        """
        
        try :
            if self.CommunicationAdapter :
                self.CommunicationAdapter.StopBlxRecording()
            
        except CommunicationException, exc :
            
            raise GraniteConnectionException('Error occured when stopping blx recording: ' + str(exc))


    def stopRecordingRemoveTempFile(self) :
        
        """
        Stops blx recorging and removes the temporar blx file
        """
        
        try :
            if self.CommunicationAdapter :
                self.CommunicationAdapter.StopRecordingRemoveTempFile()
            
        except CommunicationException, exc :
            raise GraniteConnectionException('Error occured when stopping blx recording and removing temp file: ' + str(exc))           


    def getPhoneSoftwareVersion(self) :

        """
        Gets the phone SW version string
        """
        
        try :

            if self.CommunicationAdapter :

                return self.CommunicationAdapter.PhoneSoftwareVersion
        
        except CommunicationException, exc :
            raise GraniteConnectionException('Error occured when requesting phone software version: ' + str(exc))   


    def getGrowingBinaryLog(self) :

        """
        Return an active (growing) binary log instance
        """
        
        try :

            if self.CommunicationAdapter :

                return self.CommunicationAdapter.BinaryLog
        
        except CommunicationException, exc :
            raise GraniteConnectionException('Error occured when requesting binary log instance: ' + str(exc))   


    def canConnectDevice(self) :

        """
        Checks if device is reachable
        """
        
        try :

            if self.Connection :

                return self.Connection.CanConnectDevice
        
        except CommunicationException, exc :
            raise GraniteConnectionException(str(exc))

    
    def canConnectMedia(self) :
        
        """
        Checks if connection media is reachable
        """
        
        try :

            if self.Connection :

                return self.Connection.CanConnectMedia
        
        except CommunicationException, exc :
            raise GraniteConnectionException(str(exc))
   
    
    def __getPNMsg(self, (resource, objectid), request, utid = 1, recv_dev = 0):
        
        """
        Creates a new phonet message and returns it.

            resource    message's resource
            objectid    message's object id
            request     ISI message data
            utid        universal transaction id
            recv_dev    received device
        """
        
        assert type(request) == types.ListType, \
               'Request must be delivered in a list'

        # create new phonet message data
        
        data = [pn.PN_MEDIA_ROUTING_REQ,
                recv_dev, #pn.PN_DEV_DONT_CARE + (objectid >> 8) & 0x03,
                pn.PN_DEV_PC,
                resource,
                0,
                0,
                objectid & 0xFF,
                0, #5, #self.messageStream.ObjectId ?????????????
                utid]

        data.extend(request)      

        return data

    def unsubscribeAllIndications(self, receiverDevice="PN_DEV_HOST") :

        if not self.isConnected() :
            raise GraniteConnectionException('Nokia.RD.Communication.Connection was not open.')
        
        #we can't allow to unssubscribe all indications if the keypad listener is active
        if not self.internallySubscribedKeyindications :
       
            try :
                self.sendMessageApiMessageAsynchronously(PnsSubscribedResourcesInd(), receiverDevice)
                self.CommunicationAdapter.FinishedAsynchronousMessaging()
            except Exception, exc :
                raise GraniteConnectionException(str(exc))

        else :

            resources = list()

            for resource in self.subscribedResources :
                resourceString = str(resource)
                if resourceString != "PN_KEY" :
                    resources.append(resourceString)

            self.unsubscribeIndications(resources, receiverDevice)


    def unsubscribeIndications(self, resourceIdString, receiverDevice="PN_DEV_HOST") :

        if not self.isConnected() :
            raise GraniteConnectionException('Nokia.RD.Communication.Connection was not open.')

        resourcesList = list()

        if isinstance(resourceIdString, String) :

            resourcesList.append(resourceIdString)

        elif not isinstance(resourceIdString, list) :
            raise GraniteConnectionException("'resourceIdString' is not a proper string or a list")

        else :

            resourcesList = resourceIdString
        
        try :

            for resourceString in resourcesList :

                if not isinstance(resourceString, String) or String.IsNullOrEmpty(resourceString) :
                    continue

                resourceString = resourceString.ToUpper()

                if resourceString == "PN_KEY" and self.internallySubscribedKeyindications :

                    continue

                elif resourceString == "PN_KEY" and not self.internallySubscribedKeyindications :
                    self.externallySubscribedKeyindications = False

                if not resourceString.StartsWith("PN_") :
                    raise GraniteConnectionException("Inproper resource id name: '" + resourceString + "'")

                #Casting string to PhonetResource enum
                phonetResource = clr.Convert(Enum.Parse(clr.GetClrType(PhonetResource), resourceString), PhonetResource)

                if self.subscribedResources.Contains(phonetResource) :

                    self.subscribedResources.Remove(phonetResource)

            req = PnsSubscribedResourcesInd()
           
            for resource in self.subscribedResources :

                req.ResourceId.Add(resource)

            self.sendMessageApiMessageAsynchronously(req, receiverDevice)

            if self.subscribedResources.Count == 0 :

                self.CommunicationAdapter.FinishedAsynchronousMessaging()


        except Exception, exc :
            raise GraniteConnectionException(str(exc))


    def subscribeIndications(self, resourceIdString, receiverDevice="PN_DEV_HOST") :

        """
        Subscribes indicationa from a resource. Uses an interanal list of subscribed resources in order to
        avoid an indication subscripbtion to override earlier subscribtions. Requires a PMD file to be
        loaded.

            resourceIdString    resource(s) whose indications are under interest, either a string or list
                                of strings, in format:
                                'PN_CAMERA'; or a list: ['PN_CAMERA', 'PN_KEY']

            receiverDevice      receiver device from where to subscribe, by default 'PN_DEV_HOST'. Usually
                                changed if subscribing indication from modem servers with dualSIM devices:
                                'PN_DEV_MODEM' or 'PN_DEV_MODEM_2'
        """
        
        if not self.isConnected() :
            raise GraniteConnectionException('Nokia.RD.Communication.Connection was not open.')

        if not self.isPMDLoaded() :
            raise GraniteConnectionException('No PMD file loaded: PMD information is mandatory \
                                            when subscribing indications')

        resourcesList = list()

        if isinstance(resourceIdString, String) :

            resourcesList.append(resourceIdString)

        elif not isinstance(resourceIdString, list) :
            raise GraniteConnectionException("'resourceIdString' is not a proper string or a list")

        else :

            resourcesList = resourceIdString
        
        try:
            for resourceString in resourcesList :

                if not isinstance(resourceString, String) :
                    continue

                if String.IsNullOrEmpty(resourceString) :
                    continue
                
                resourceString = resourceString.ToUpper()

                if not resourceString.StartsWith("PN_") :
                    raise GraniteConnectionException("Inproper resource id name: '" + resourceString + "'")

                """
                Checks if the key server indication is subscribed by keyBoardListener or by some external party
                """
                if resourceString == "PN_KEY" and not self.internallySubscribedKeyindications :
                    self.externallySubscribedKeyindications = True

                """
                Casting string to PhonetResource enum (in C#: (PhonetResource)Enum.Parse(typeof(PhonetResource), resourceString) )
                This is in order to avoid caller to import PhonetResource Enum
                """
                phonetResource = clr.Convert(Enum.Parse(clr.GetClrType(PhonetResource), resourceString), PhonetResource)

                if not self.subscribedResources.Contains(phonetResource) :

                    self.subscribedResources.Add(phonetResource)

            req = PnsSubscribedResourcesInd()
           
            for resource in self.subscribedResources :

                req.ResourceId.Add(resource)

            self.sendMessageApiMessageAsynchronously(req, receiverDevice)
        except Exception, exc:
            raise GraniteConnectionException(str(exc))

            
    def startTouchPadListener(self, handler) :

        if not self.isConnected() :
            raise GraniteConnectionException('Nokia.RD.Communication.Connection was not open.')

        self.TouchpadListenerThread = None
        
        try :

            req = TouchpadPenEventsReq(TouchpadPenEventsReq.ActionField(TouchpadPenEventsAction.TOUCHPAD_PEN_EVENTS_START), \
                                       TouchpadPenEventsReq.CoordinateTypeField(TouchpadCoordinateType.TOUCHPAD_COORDINATE_TYPE_ALL))
        
            resp = self.sendMessageApiMessage(req)

            if resp == None:
            
                raise GraniteConnectionException('Received no response for TOUCHPAD_PEN_EVENTS_REQ')

            resp = self._removeDecodingErrors(resp)
            
            resp = TouchpadPenEventsResp.Create(resp.Xml.InnerXml, IsiVersion())

            if resp == None:
            
                raise GraniteConnectionException('Failed to convert TOUCHPAD_PEN_EVENTS_RESP')

            if resp.Status != TouchpadPenEventsStatus.TOUCHPAD_PEN_EVENTS_OK :
                raise GraniteConnectionException('Failed to start Touchpad listener: ' + str(resp.Status))

            self.TouchpadListenerThread = Thread(ParameterizedThreadStart(self._touchpadListener))
            self.TouchpadListenerThread.IsBackground = True
            self.TouchpadListenerThread.Start(handler)

        except Exception, exc :

            if self.TouchpadListenerThread :
                if self.TouchpadListenerThread.IsAlive :
                    self.TouchpadListenerThread.Abort()

            raise GraniteConnectionException(str(exc))


    def stopTouchPadListener(self) :

        try :

            if self.TouchpadListenerThread :
                if self.TouchpadListenerThread.IsAlive :
                    self.TouchpadListenerThread.Abort()

            req = TouchpadPenEventsReq(TouchpadPenEventsReq.ActionField(TouchpadPenEventsAction.TOUCHPAD_PEN_EVENTS_STOP), \
                                       TouchpadPenEventsReq.CoordinateTypeField(TouchpadCoordinateType.TOUCHPAD_COORDINATE_TYPE_ALL))

            self.sendMessageApiMessageAsynchronously(req)

        except Exception, exc :

            raise GraniteConnectionException(str(exc))


    def startKeyboardListener(self, handler) :

        """
        Starts polling Key Server indication in background. Requires a PMD file to be loaded.

            handler     handler/callback method where the thread passes the key event indication information:
                        key code and key state, in string format, e.g.: 'KBD_KEY_1', 'KBD_KEY_DOWN'. Example
                        definition for handler method : 'def keyHandler(self, keyCode, keyState) :'

            Returns:    -
        """

        self.KeyboardListenerThread = None
        
        try :
            
            if not self.isConnected() :
                raise GraniteConnectionException('Nokia.RD.Communication.Connection was not open.')

            if not self.isPMDLoaded() :
                raise GraniteConnectionException('No PMD file loaded: PMD information is mandatory \
                                              when decoding key event indications ')

            self.internallySubscribedKeyindications = True
            self.subscribeIndications("PN_KEY")
            
            self.KeyboardListenerThread = Thread(ParameterizedThreadStart(self._keyboardListener))
            self.KeyboardListenerThread.IsBackground = True
            self.KeyboardListenerThread.Start(handler)

        except Exception, exc :

            try :
                if self.KeyboardListenerThread :
                    if self.KeyboardListenerThread.IsAlive :
                        self.KeyboardListenerThread.Abort()
            except :
                pass
                        
            raise GraniteConnectionException(str(exc))


    def stopKeyboardListener(self) :

        if not self.isPMDLoaded() :
            raise GraniteConnectionException('No PMD file loaded: PMD information is mandatory \
                                              unsubscribing indications.')

        if not self.externallySubscribedKeyindications  :

            self.unsubscribeIndications("PN_KEY")

        self.internallySubscribedKeyindications = False

        if self.KeyboardListenerThread :

            if self.KeyboardListenerThread.IsAlive :

                self.KeyboardListenerThread.Abort()


    def _touchpadListener(self, handler) :
        
        try :

            touchIter = self.createMessageIterator("PN_TOUCHPAD", "TOUCHPAD_PEN_EVENT_NTF")

            while True :

                ntf = touchIter.GetNext()

                if not ntf :
                    continue

                ntf = self._removeDecodingErrors(ntf)
                
                ntf = TouchpadPenEventNtf.Create(ntf.Xml.InnerXml, IsiVersion())

                if not ntf :

                    continue

                if not ntf.Subblocks :

                    continue

                pressure = None
                state = None
                x = None
                y = None
                displayStatus = None
                xCoordinate = None
                yCoordinate = None
                timestamp = None

                if ntf.Subblocks.TouchpadSbPenStateInfo :

                    pressure = ntf.Subblocks.TouchpadSbPenStateInfo.Pressure.Value
                    state = ntf.Subblocks.TouchpadSbPenStateInfo.State.FormattedValue
                    x = ntf.Subblocks.TouchpadSbPenStateInfo.X.Value
                    y = ntf.Subblocks.TouchpadSbPenStateInfo.Y.Value
                
                if ntf.Subblocks.TouchpadSbDisplayCoordinateData :

                    displayStatus = ntf.Subblocks.TouchpadSbDisplayCoordinateData.DisplayTouchStatus.FormattedValue
                
                    xCoordinate = ntf.Subblocks.TouchpadSbDisplayCoordinateData.XCoordinate.Value

                    yCoordinate = ntf.Subblocks.TouchpadSbDisplayCoordinateData.YCoordinate.Value

                if ntf.Subblocks.TouchpadSbTimestamp :

                    timestamp = ntf.Subblocks.TouchpadSbTimestamp.Timestamp.Value

                if pressure and state and x and y and displayStatus and xCoordinate and yCoordinate and timestamp :

                    handler(pressure, state, x, y, displayStatus, xCoordinate, yCoordinate, timestamp)
                   
        except Exception, exc :
            
            if self.TouchpadListenerThread :
                if self.TouchpadListenerThread.IsAlive :
                    self.TouchpadListenerThread.Abort()

            raise GraniteConnectionException(str(exc))


    def _keyboardListener(self, handler) :

        """
        Infinite loop for polling key server events, and should be only used with a dedicated thread.
        Requires a PMD file to be loaded. Handles key event information as Xml because of poor MessageAPI
        implementation for Key Server indications.

            handler     handler/callback method where the thread passes the key event indication information:
                        key code and key state, in string format, e.g.: 'KBD_KEY_1', 'KBD_KEY_DOWN'. Example
                        definition for handler method : 'def keyHandler(self, keyCode, keyState) :'

            Returns:    -
        """
        
        try :
 
            kbdIter = self.createMessageIterator("PN_KEY", "KBD_EVENT_IND")
      
            while True :

                ind = kbdIter.GetNext()

                if not ind :
                    continue
                
                keyCode = None
                keyState = None

                fields = ind.Xml.SelectNodes(".//IsiMessage//Subblock[@Name='KBD_SINGLE_PRESS_KEY_EVENT_INFO']//Field")

                if not fields :
                    continue

                if fields.Count != 2 :
                    continue

                if not fields[0].Attributes.Count or not fields[1].Attributes.Count :
                    continue

                if fields[0].Attributes[0].Value.ToLower().Contains("code") :             
                    if fields[1].Attributes[0].Value.ToLower().Contains("state") :
                        keyCode = fields[0].InnerText
                        keyState = fields[1].InnerText
                        
                elif fields[1].Attributes[0].Value.ToLower().Contains("code") :             
                    if fields[0].Attributes[0].Value.ToLower().Contains("state") :
                        keyCode = fields[1].InnerText
                        keyState = fields[0].InnerText

                if keyCode and keyState :
                    handler(keyCode, keyState)

        except Exception, exc :

            try :
                if self.KeyboardListenerThread :
                    if self.KeyboardListenerThread.IsAlive :
                        self.KeyboardListenerThread.Abort()
            except :
                pass
            
            raise GraniteConnectionException(str(exc))


    def connect(self, phone, connGuid, traceConnGuid=None):        
        """Create a connection with given connection Guid."""
        if not self.isConnected():
            phoneName = phone.getName() != 'Main' and 'remote phone' or 'phone'

            debug.brf('Opening %s connection...' % phoneName)
        
            self.ConnectionManager = ConnectionManager
                        
            # get a list of current Fuse connections and their parameteters
            fuseConnParams = self.ConnectionManager.Instance.GetFuseConnections()
            
            if self.__connectionMockerInUse:
                #connectionMockerThread = ConnectionMockerThread(r'C:\isa_test_A2\Granite_test_run.blx')
                #connectionMockerThread.start()
                                
                self.ConnectionManager.Instance.NewPrimaryConnection('ConnectionMocker')
                self.CommunicationAdapter = self.ConnectionManager.Instance.PrimaryConnection
                debug.brf('Using ConnectionMocker Fuse connection')
            else:
                connectionFound = False
                
                if fuseConnParams.Count:            
                    for fuseConn in fuseConnParams:
                        debug.vrb('Found Fuse connection: %s, %s' % (fuseConn.Name, fuseConn.Guid))
                        
                        # when connection guid/name has been with --connection, always use it
                        # in display capture mode Fuse connection name is used
                        # otherwise connection Guid from settings is used
                        if (core.FW_conf['param_connection'] and (fuseConn.Guid == core.FW_conf['param_connection'] or fuseConn.Name == core.FW_conf['param_connection'])) or \
                           (not core.FW_conf['param_connection'] and fuseConn.Guid == connGuid):
                            # Set Main phone connection by using PrimaryConnection
                            if connGuid == core.FW_conf['settings'].Main.Connection:
                                self.ConnectionManager.Instance.NewPrimaryConnection(fuseConn.Name)
                                self.CommunicationAdapter = self.ConnectionManager.Instance.PrimaryConnection
                            else:
                                fuseconnection = self.ConnectionManager.Instance.FindConnectionParameter(fuseConn.Name)
                                connections = self.ConnectionManager.Instance.Connections
                                connections.Add(CommunicationAdapter(ConnectionParameters(fuseconnection)))
                                self.CommunicationAdapter = self.ConnectionManager.Instance.GetConnectionByName(fuseConn.Name)

                            debug.brf('Using Fuse connection: %s, %s for %s phone' % (fuseConn.Name, fuseConn.Guid, phone.getName()))
                            
                            # save connection Guid to current_connection
                            phone.current_connection = fuseConn.Guid
                            
                            # get bus name from connection string
                            self.connBusName = fuseConn.ConnectionString.split()[0].split(':')[1]
                            connectionFound = True

                # raise exception is connection was not found!
                if not connectionFound:                    
                    # dispose ConnectionManager with close                    
                    self.close(phoneName)

                    if core.FW_conf['param_connection']:
                        connString = core.FW_conf['param_connection']
                    else:
                        connString = connGuid
                         
                    raise SystemExit('Fuse connection "%s" was not found! Unable to continue!' % connString)
            
            if not self.CommunicationAdapter:                
                raise GraniteConnectionException('CommunicationAdapter is None, Could not open the Nokia.RD.Communication.Connection!')
            
            self.PMDFileHandler = PMDFileHandler(self.__pmdFilePath, self.CommunicationAdapter.PMDLoader)
            self.PMDFileHandler.load()
            self.initPMDdependentModules()
            
            # create own MessageSender for phonet message traffic only
            self.MessageSender = MessageSender(self.CommunicationAdapter.Connection)

            self.MessageApiSender = self.CommunicationAdapter.MessageApiSender
            self.Connection = self.CommunicationAdapter.Connection
            self.BinaryLog = self.CommunicationAdapter.BinaryLog

            if self.MessageApiSender and self.PMDLoader and self.BinaryLog:
                self.fileSystem = FileServerAdapter(self.MessageApiSender, self.PMDLoader, self.BinaryLog)
            else:
                debug.brf('Filesystem not initialized')
                self.fileSystem = None 
                   
            #self.IteratorFactory = IteratorFactory(MessageAPIFactory(),
            #                                       MessageDecoder(self.PMDLoader),
            #                                       self.PMDLoader, self.BinaryLog)
    
            # connect only if we are not already connected
            if not self.__connectionMockerInUse and not self.isConnected():
                self.CommunicationAdapter.Connect()

            if not core.FW_conf['cli_mode']:
                self.CommunicationAdapter.EnableRaisingDataEvents = True
                self.CommunicationAdapter.DataEvent += self._dataReceived
            self.__traceMessages = []            
                        
        if not self.isConnected():
            raise GraniteConnectionException('Could not open the Nokia.RD.Communication.Connection!')
        
 
    def __convertToPhonetMessage(self, grnMessage) :

        """
        Converts old Granite-style message to PhonetMessage object
        """       
        if grnMessage != None and isinstance(grnMessage, list):
            newMessage = List[Byte]()

            for item in grnMessage :
                byteItem = clr.Convert(item & 0xFF, Byte)
                newMessage.Add(byteItem)

            return PhonetMessage(newMessage.ToArray())


    def sendAsynchronously(self, receiver = None, requestData = None, utid = 1,
             commonMessageData = None, recv_dev = 0):       
        
        """
        Send ISI message asynchronously to the phone.

            receiver    Tuple of resource id and receiver object id
                        OR
                        resource id

            requestData         ISI message data coming after UTID

            utid                universal transaction id
            commonMessageData   common isi message data which is ready to be
                                sent
                                receiver and requestData are left None in
                                these cases
            recv_dev            receiver device                                

            Returns:    -

            raises GraniteConnectionExceptions
        """        
        if commonMessageData:

            if self.isConnected():            
                phonetMessage = None
                
                try:        
                    #self.MessageSender.SendAsynchronously(self.__convertToPhonetMessage(commonMessageData))
                    phonetMessage = self.__convertToPhonetMessage(commonMessageData)
                    self.MessageSender.BeginSend(phonetMessage)        
                except Exception, exc:
                    raise GraniteConnectionException(str(exc)) 
                finally:
                    if phonetMessage:
                        phonetMessage.Dispose()        
            else:
                raise GraniteConnectionException('Nokia.RD.Communication.Connection was not open.')

        else:
            if type(receiver) != types.TupleType:
                receiver = (receiver, pn.PN_OBJ_ROUTER)

            else:
                if receiver[1] == None:
                    receiver = (receiver[0], pn.PN_OBJ_ROUTER)

            if utid == None:
                utid = 1

            if self.isConnected():
                phonetMessage = None
                
                try:
                    grnMessage = self.__getPNMsg(receiver, requestData, utid, recv_dev)
                    #self.MessageSender.SendAsynchronously(self.__convertToPhonetMessage(grnMessage))                    
                    phonetMessage = self.__convertToPhonetMessage(grnMessage)
                    self.MessageSender.BeginSend(phonetMessage)
                except Exception, exc :
                    raise GraniteConnectionException(str(exc))                  
                finally:
                    if phonetMessage:
                        phonetMessage.Dispose()        
            else:
                raise GraniteConnectionException('Nokia.RD.Communication.Connection was not open.')

    
    def send(self, receiver = None, requestData = None, timeout = 0, utid = 1,
             commonMessageData = None, recv_dev = 0):       
        
        """
        Send ISI message to the phone.

            receiver            Tuple of resource id and receiver object id
                                OR resource id

            requestData         ISI message data coming after UTID
            timeout             send timeout, default value from connection
                                parameters
            utid                universal transaction id
            commonMessageData   common isi message data which is ready to be
                                sent
                                receiver and requestData are left None in
                                these cases
            recv_dev            receiver device

            Returns:    -

            raises GraniteConnectionExceptions
        """        
        if commonMessageData:

            if self.isConnected():

                originalTimeout = self.MessageSender.Timeout
        
                phonetMessage = None
                
                try:        
                    self.MessageSender.Timeout = timeout or self.defaultTimeout
                    
                    phonetMessage = self.__convertToPhonetMessage(commonMessageData)
                    result, self.response = self.MessageSender.Send(phonetMessage)

                    if str(result) != 'Success' :
        
                        raise GraniteConnectionException('WARNING: Unable to send message to phone: ' + str(result))
        
                except Exception, exc:
                    raise GraniteConnectionException(str(exc))

                finally:
                    self.MessageSender.Timeout = originalTimeout
                    if phonetMessage:
                        phonetMessage.Dispose()        
            else:
                raise GraniteConnectionException('Nokia.RD.Communication.Connection was not open.')

        else:
            if type(receiver) != types.TupleType:
                receiver = (receiver, pn.PN_OBJ_ROUTER)

            else:
                if receiver[1] == None:
                    receiver = (receiver[0], pn.PN_OBJ_ROUTER)

            if utid == None:
                utid = 1

            if self.isConnected():

                originalTimeout = self.MessageSender.Timeout
                phonetMessage = None
                
                try:
                    self.MessageSender.Timeout = timeout or self.defaultTimeout
                                        
                    grnMessage = self.__getPNMsg(receiver, requestData, utid, recv_dev)
                    
                    self.utid = utid
                                        
                    phonetMessage = self.__convertToPhonetMessage(grnMessage)
                    result, self.response = self.MessageSender.Send(phonetMessage)

                    if str(result) != 'Success' :
                        raise GraniteConnectionException('WARNING: Unable to send message to phone: ' + str(result))
                    
                except Exception, exc :
                    raise GraniteConnectionException(str(exc))
                finally :
                    self.MessageSender.Timeout = originalTimeout
                    if phonetMessage:
                        phonetMessage.Dispose()
            else:
                raise GraniteConnectionException('Nokia.RD.Communication.Connection was not open.')

    def recv(self, timeout = 0):
        
        """
        Receive phonet message from the phone.

            timeout     recv timeout, default value from connection parameters

            Returns:    (length, response)

            raises GraniteConnectionExceptions
        """

        if self.response != None:
            message = [int(x) for x in self.response.ToArray()]
            # place req utid to resp
            message[8] = self.utid
            data = self.response.Count, message

            # dispose PhonetMessage
            self.response.Dispose()

            self.response, self.utid = None, None
            return data
        else:
            raise GraniteConnectionException('No response data received')


    def sendPhonetMessage(self, phonetMessage, timeout = 0, receiverDevice="PN_DEV_HOST") :

        """
        Send ISI message in Phonet container (see Nokia.RD.PhonetMessage) to the phone. If 
        using other receiver device than "PN_DEV_HOST", a PMD file must be loaded.

            phonetMessage       ISI message in PhonetMessage container

            timeout             send timeout, default value from connection
                                parameters

            receiverDevice      Name of the receiver device. Default name id "PN_DEV_HOST",
                                but when communicating with DualSIM servers, "PN_DEV_MODEM"
                                or "PN_DEV_MODEM_2" must be used
                           
            Returns:            Response ISI message in PhonetMessage container

            raises GraniteConnectionExceptions
        """

        if not isinstance(phonetMessage, PhonetMessage) :
            
            raise GraniteConnectionException("'phonetMessage' parameter must be instance of PhonetMessage class")
        
        originalTimeout = self.MessageSender.Timeout

        try :

            self.MessageSender.Timeout = timeout or self.defaultTimeout

            if receiverDevice != "PN_DEV_HOST" :
                
                if String.IsNullOrEmpty(receiverDevice) :
                
                    raise GraniteConnectionException("Given 'receiverdevice' is null or empty string")

                if not self.isPMDLoaded() :
  
                    raise GraniteConnectionException("PMD is not loaded: cannot search for '" + receiverDevice + "' without loaded PMD file")

                found, id = self._getDeviceId(receiverDevice, self.PMDLoader)

                if found :

                    phonetMessage.PhonetHeader.ReceiverDevice = id

                else :

                    raise GraniteConnectionException("Could not find '" + receiverDevice + "' from " + Path.GetFileName(self.PMDLoader.Filename))

            sendResult, response = self.MessageSender.Send(phonetMessage)

            if str(sendResult) != 'Success' :
            
                raise GraniteConnectionException('Failed to send phonet message, reason: ' + str(sendResult))

            return response
        
        except Exception, exc :

            raise GraniteConnectionException(str(exc))
        
        finally :

            self.MessageSender.Timeout = originalTimeout


    def sendPhonetMessageAsynchronously(self, phonetMessage, receiverDevice="PN_DEV_HOST", responseHandler=None):

        """
        Asynchronously send ISI message in Phonet container (see Nokia.RD.PhonetMessage) to the phone. If 
        using other receiver device than "PN_DEV_HOST", a PMD file must be loaded.

            phonetMessage       ISI message in PhonetMessage container

            receiverDevice      Name of the receiver device. Default name id "PN_DEV_HOST",
                                but when communicating with DualSIM servers, "PN_DEV_MODEM"
                                or "PN_DEV_MODEM_2" must be used

            responseHandler     Optional handler method for handling response message, e.g.
                                "def ResponseHandler(self, sendChannel, messageArgs)".
                                Note that messageArgs.Response is an instance of PhonetMessage
      
            Returns:            -

            raises GraniteConnectionExceptions
        """

        if not isinstance(phonetMessage, PhonetMessage) :
            
            raise GraniteConnectionException("'phonetMessage' parameter must be an instance of PhonetMessage class")
        
        try :

            if receiverDevice != "PN_DEV_HOST" :
                
                if String.IsNullOrEmpty(receiverDevice) :
                
                    raise GraniteConnectionException("Given 'receiverdevice' is null or empty string")

                if not self.isPMDLoaded() :
  
                    raise GraniteConnectionException("PMD is not loaded: cannot search for '" + receiverDevice + "' without loaded PMD file")

                found, id = self._getDeviceId(receiverDevice, self.PMDLoader)

                if found :

                    phonetMessage.PhonetHeader.ReceiverDevice = id

                else :

                    raise GraniteConnectionException("Could not find '" + receiverDevice + "' from " + Path.GetFileName(self.PMDLoader.Filename))

            if responseHandler :

                self.MessageSender.BeginSend(phonetMessage, responseHandler)

            else :

                self.MessageSender.BeginSend(phonetMessage)

        except Exception, exc :
            
            raise GraniteConnectionException(str(exc))


    def sendByteArray(self, byteArray, timeout=0, receiverDevice="PN_DEV_HOST") :

        """
        Send ISI message as an array of bytes to the phone. If 
        using other receiver device than "PN_DEV_HOST", a PMD file must be loaded.

            byteArray           ISI message as an array of bytes:
                                Array[Byte]((0x00,0x00,0x10,0x61,0x00,0x16,0x00,0x01,
                                             0x00,0x80,0x01,0x00,0x00,0x00,0x00,0x00,
                                             0x01,0x40,0x00,0xf0,0x00,0x00,0x00,0x00,
                                             0x00,0x00,0x00,0x00))

            timeout             send timeout, default value from connection
                                parameters

            receiverDevice      Name of the receiver device. Default name id "PN_DEV_HOST",
                                but when communicating with DualSIM servers, "PN_DEV_MODEM"
                                or "PN_DEV_MODEM_2" must be used
                           
            Returns:            Response ISI message as an array of bytes

            raises GraniteConnectionExceptions
        """

        if not isinstance(byteArray, Array[Byte]) or not byteArray :

            raise GraniteConnectionException("'byteArray' is not a proper array of bytes (Array[Byte])")

        return self.sendPhonetMessage(PhonetMessage(byteArray), timeout, receiverDevice).ToArray()


    def sendByteArrayAsynchronously(self, byteArray, receiverDevice="PN_DEV_HOST", responseHandler=None) :

        """
        Asynchronously send ISI message as an array of bytes to the phone. If 
        using other receiver device than "PN_DEV_HOST", a PMD file must be loaded.

            byteArray           ISI message as an array of bytes:
                                Array[Byte]((0x00,0x00,0x10,0x61,0x00,0x16,0x00,0x01,
                                             0x00,0x80,0x01,0x00,0x00,0x00,0x00,0x00,
                                             0x01,0x40,0x00,0xf0,0x00,0x00,0x00,0x00,
                                             0x00,0x00,0x00,0x00))

            receiverDevice      Name of the receiver device. Default name id "PN_DEV_HOST",
                                but when communicating with DualSIM servers, "PN_DEV_MODEM"
                                or "PN_DEV_MODEM_2" must be used

            responseHandler     Optional handler method for handling response message, e.g.
                                "def ResponseHandler(self, sendChannel, messageArgs)".
                                Note that messageArgs.Response is an instance of PhonetMessage 
                           
            Returns:            -

            raises GraniteConnectionExceptions
        """

        if not isinstance(byteArray, Array[Byte]) or not byteArray :

            raise GraniteConnectionException("'byteArray' is not a proper array of bytes (Array[Byte])")

        self.sendPhonetMessageAsynchronously(PhonetMessage(byteArray), receiverDevice, responseHandler)


    def sendHexString(self, hexString, timeout=0, receiverDevice="PN_DEV_HOST") :
        
        """
        Send ISI message in hex string format to the phone. If 
        using other receiver device than "PN_DEV_HOST", a PMD file must be loaded.

            hexString           ISI message as hex string, in format:
                                "00,00,10,61,00,16,00,01,00,80,01,00,00,00,00,00,
                                 01,40,00,f0,00,00,00,00,00,00,00,00"

            timeout             send timeout, default value from connection
                                parameters

            receiverDevice      Name of the receiver device. Default name id "PN_DEV_HOST",
                                but when communicating with DualSIM servers, "PN_DEV_MODEM"
                                or "PN_DEV_MODEM_2" must be used
                           
            Returns:            Response ISI message in hex string format

            raises GraniteConnectionExceptions
        """

        if not isinstance(hexString, String) or String.IsNullOrEmpty(hexString) :
            raise GraniteConnectionException("'hexString' is not a proper string")

        return str(self.sendPhonetMessage(PhonetMessage(hexString), timeout, receiverDevice))

            
    def sendHexStringAsynchronously(self, hexString, receiverDevice="PN_DEV_HOST", responseHandler=None) :

        """
        Asynchronously send ISI message in hex string format to the phone. If 
        using other receiver device than "PN_DEV_HOST", a PMD file must be loaded.

            hexString           ISI message as hex string, in format:
                                "00,00,10,61,00,16,00,01,00,80,01,00,00,00,00,00,
                                 01,40,00,f0,00,00,00,00,00,00,00,00"

            receiverDevice      Name of the receiver device. Default name id "PN_DEV_HOST",
                                but when communicating with DualSIM servers, "PN_DEV_MODEM"
                                or "PN_DEV_MODEM_2" must be used
                           
            responseHandler     Optional handler method for handling response message, e.g.
                                "def ResponseHandler(self, sendChannel, messageArgs)".
                                Note that messageArgs.Response is an instance of PhonetMessage

            Returns:            -

            raises GraniteConnectionExceptions
        """

        if not isinstance(hexString, String) or String.IsNullOrEmpty(hexString) :

            raise GraniteConnectionException("'hexString' is not a proper string")

        self.sendPhonetMessageAsynchronously(PhonetMessage(hexString), receiverDevice, responseHandler)


    # def sendXmlMessage(self, messageXmlString, timeout = 0, receiverDevice="PN_DEV_HOST"):
        
        # """
        # Send ISI message in XML string presentation to the phone. PMD file must be loaded in
        # order to use this method

            # messageXmlString    XML presentation of ISI message, in string format

            # timeout             send timeout, default value from connection
                                # parameters

            # receiverDevice      Name of the receiver device. Default name id "PN_DEV_HOST",
                                # but when communicating with DualSIM servers, "PN_DEV_MODEM"
                                # or "PN_DEV_MODEM_2" must be used
                           
            # Returns:            Response ISI message in XML string presentation

            # raises GraniteConnectionExceptions
        # """

        # if String.IsNullOrEmpty(messageXmlString) or not isinstance(messageXmlString, String) :
            # raise GraniteConnectionException("'messageXmlString' is not a proper string")

        # if not self.isPMDLoaded() :
            # raise GraniteConnectionException("PMD is not loaded: cannot create message from xml string without PMD file")

        # try :

            # phonetMessageReq = self.Encoder.EncodeMessage(messageXmlString)

            # phonetMessageResp = self.sendPhonetMessage(phonetMessageReq, timeout, receiverDevice)

            # decoder = MessageDecoder(self.PMDLoader)
            # decoder.FirstTimestamp = TimestampType.None
            # decoder.SecondTimestamp = TimestampType.None
            # decoder.Interpretation = InterpretationType.XMLForAnalysis

            # return decoder.Decode(phonetMessageResp)

        # except Exception, exc :

            # raise GraniteConnectionException(str(exc))        


    # def sendXmlMessageAsynchronously(self, messageXmlString, receiverDevice="PN_DEV_HOST", responseHandler=None):
   
        # """
        # Asynchronously send ISI message in XML strin presentation to the phone. PMD file must be loaded in
        # order to use this method

            # messageXmlString        XML presentation of ISI message, in string format


            # receiverDevice          Name of the receiver device. Default name id "PN_DEV_HOST",
                                    # but when communicating with DualSIM servers, "PN_DEV_MODEM"
                                    # or "PN_DEV_MODEM_2" must be used
            
            # responseHandler         Optional handler method for handling response message, e.g.
                                    # "def ResponseHandler(self, sendChannel, messageArgs)".
                                    # Note that messageArgs.Response is an instance of PhonetMessage; not string
        
            # Returns:                -

            # raises GraniteConnectionExceptions
        # """
     
        # if String.IsNullOrEmpty(messageXmlString) or not isinstance(messageXmlString, String) :
            # raise GraniteConnectionException("'messageXmlString' is not a proper string")

        # if not self.isPMDLoaded() :
            # raise GraniteConnectionException("PMD is not loaded: cannot create message from xml string without PMD file")

        # try :

            # phonetMessage = self.Encoder.EncodeMessage(messageXmlString)

            # self.sendPhonetMessageAsynchronously(phonetMessage, receiverDevice, responseHandler)

        # except Exception, exc :

            # raise GraniteConnectionException(str(exc))


    def sendMessageApiMessage(self, messageApiMessage, timeout = 0, receiverDevice="PN_DEV_HOST", removeDecodingErrors=True):
 
        """
        Send ISI message in Nokia.RD.MessageApi.Message presentation to the phone. PMD file must be loaded in
        order to use this method

            messageApiMessage       Nokia.RD.MessageApi.Message based presentation of ISI message

            timeout                 send timeout, default value from connection
                                    parameters

            receiverDevice          Name of the receiver device. Default name id "PN_DEV_HOST",
                                    but when communicating with DualSIM servers, "PN_DEV_MODEM"
                                    or "PN_DEV_MODEM_2" must be used
                      
            removeDecodingErrors    If set to True (default value), removes decoding errors from response
                                    messages. E.g. infonion chipsets produce not valid, problematic decoding errors
     
            Returns:                Response ISI message as Nokia.RD.MessageApi.Message class instance

            raises GraniteConnectionExceptions
        """
       
        if not messageApiMessage :
            raise GraniteConnectionException('Given Nokia.RD.MessageApi.Message is not valid')
        
        if not self.isPMDLoaded() :
            raise GraniteConnectionException("PMD is not loaded: cannot send messageApi message without PMD file")

        originalTimeout = self.MessageApiSender.Timeout
        
        try : 
            
            self.MessageApiSender.Timeout = timeout or self.defaultTimeout
            
            response = None 

            if receiverDevice != "PN_DEV_HOST" :

                responseXmlString = self.sendXmlMessage(messageApiMessage.Xml.OuterXml, timeout, receiverDevice)
                
                response = MessageAPIFactory().CreateMessage(responseXmlString)

            else :

                sendResult, response = self.MessageApiSender.Send(messageApiMessage)

                if str(sendResult) != 'Success' :

                    raise GraniteConnectionException('Failed to send messageApi message, reason: ' + str(sendResult))

            
            if removeDecodingErrors and response:

                response = self._removeDecodingErrors(response)

            return response

        except Exception, exc :

            raise GraniteConnectionException(str(exc))

        finally :

            self.MessageApiSender.Timeout = originalTimeout


    def sendMessageApiMessageAsynchronously(self, messageApiMessage, receiverDevice="PN_DEV_HOST", responseHandler=None):

        """
        Asynchronously send  ISI message in Nokia.RD.MessageApi.Message presentation to the phone. PMD file must be loaded in
        order to use this method

            messageApiMessage       Nokia.RD.MessageApi.Message based presentation of ISI message

            receiverDevice          Name of the receiver device. Default name id "PN_DEV_HOST",
                                    but when communicating with DualSIM servers, "PN_DEV_MODEM"
                                    or "PN_DEV_MODEM_2" must be used

            responseHandler         Optional handler method for handling response message, e.g.
                                    "def ResponseHandler(self, sendChannel, messageArgs)".
                                    Note that messageArgs.Response is an instance of Nokia.RD.MessageApi.Message
                                    only if using default value with 'receiverDevice'; otherwise it would be an
                                    instance of PhonetMessage

                           
            Returns:                -

            raises GraniteConnectionExceptions
        """
        
        if not messageApiMessage :
            raise GraniteConnectionException('Given Nokia.RD.MessageApi.Message is not valid')
        
        if not self.isPMDLoaded() :
            raise GraniteConnectionException("PMD is not loaded: cannot send messageApi message without PMD file")
        
        try : 
                        
            if receiverDevice != "PN_DEV_HOST" :
            
                self.sendXmlMessageAsynchronously(messageApiMessage.Xml.OuterXml, receiverDevice, responseHandler)
             
            elif responseHandler :

                self.MessageApiSender.SendAsynchronously(messageApiMessage, responseHandler)

            else :

                self.MessageApiSender.SendAsynchronously(messageApiMessage)
            
        except Exception, exc :

            raise GraniteConnectionException(str(exc))


    def createMessageIterator(self, resourceIdString, messageIdString=None, subMessageIdString=None) :
        
        if not isinstance(resourceIdString, String) or String.IsNullOrEmpty(resourceIdString) :
            raise GraniteConnectionException("'resourceIdString' is not a proper string")

        if messageIdString:
            if not isinstance(messageIdString, String) or String.IsNullOrEmpty(messageIdString) :
                raise GraniteConnectionException("'messageIdString' is not a proper string")

        if subMessageIdString:
            if not isinstance(subMessageIdString, String) or String.IsNullOrEmpty(subMessageIdString) :
                raise GraniteConnectionException("'subMessageIdString' is not a proper string")
        
        if not self.isPMDLoaded() :
            raise GraniteConnectionException("PMD is not loaded: cannot create message iterator without PMD file")

        try :

            if messageIdString and subMessageIdString:

                return self.MessageApiSender.Iterator.Create(resourceIdString, messageIdString, subMessageIdString)

            elif messageIdString:    
                
                return self.MessageApiSender.Iterator.Create(resourceIdString, messageIdString)
                
            else :

                return self.MessageApiSender.Iterator.Create(resourceIdString)

        except Exception, exc :
            raise GraniteConnectionException(str(exc))


    def createTraceMessageIterator(self, resourceIdString, messageIdString, subMessageIdString=None) :
        
        if not isinstance(resourceIdString, String) or String.IsNullOrEmpty(resourceIdString) :
            raise GraniteConnectionException("'resourceIdString' is not a proper string")

        if not isinstance(messageIdString, String) or String.IsNullOrEmpty(messageIdString) :
            raise GraniteConnectionException("'messageIdString' is not a proper string")

        if subMessageIdString :
            if not isinstance(subMessageIdString, String) or String.IsNullOrEmpty(subMessageIdString) :
                raise GraniteConnectionException("'subMessageIdString' is not a proper string")

        if not self.isPMDLoaded() :
            raise GraniteConnectionException("PMD is not loaded: cannot create trace message iterator without PMD file")

        try :

            if subMessageIdString :

                return self.MessageSender.Iterator.TraceMsg.Create(resourceIdString, messageIdString, subMessageIdString)

            else :

                return self.MessageSender.Iterator.TraceMsg.Create(resourceIdString, messageIdString)

        except Exception, exc :
            raise GraniteConnectionException(str(exc))


    def tryActivateTraceGroup(self, traceXml) :
        pass


    def _removeDecodingErrors(self, messageApiMessage) :
        
        """
        Removes possible decoding error from a Nokia.RD.MessageApi.Message based message. Implemeted 
        for compatibility to Infenion chipsets, which pad messages with extra zeroes, which are seen
        as decoding errors.

            messageApiMessage    original Nokia.RD.MessageApi.Message based message

            Returns:             Decode error free Nokia.RD.MessageApi.Message

        """

        try :

            if messageApiMessage.Xml.HasChildNodes :

                isiNode = messageApiMessage.Xml.SelectSingleNode(".//IsiMessage")
                
                if not isiNode :

                    return messageApiMessage

                decodingErrors = isiNode.SelectNodes("./DecodeError")

                if not decodingErrors or decodingErrors.Count == 0 :

                    return messageApiMessage

                errorsFound = False

                for error in decodingErrors :

                    isiNode.RemoveChild(error)
                    errorsFound = True

                if errorsFound :

                    return MessageAPIFactory().CreateMessage(isiNode.OuterXml)
     
            return messageApiMessage

        except :

            return messageApiMessage       


    def _getDeviceId(self, name, pmdLoader) :

        """
        Gets the the numeric device ID matching to its string presentation

            name        String presentation of the device ID, in format
                        "PN_DEV_HOST" or "PN_DEV_MODEM" or "PN_DEV_MODEM_2"

            pmdLoader   PMDLoader instance, with PMD file loaded. Used for seraching
                        the actual receiver device ID.

            Returns:    (Found, DeviceID)

        """

        ID = 0

        if String.IsNullOrEmpty(name) :
            return False, ID

        if pmdLoader == None :
            return False, ID

        if not isinstance(pmdLoader, PMDLoader) :
            return False, ID

        if not pmdLoader.IsLoaded :
            return False, ID

        originalValue = pmdLoader.SearchRecursively

        pmdLoader.SearchRecursively = True

        ig = pmdLoader.Information.GetInfoGroup("PN_DEVICES")
        
        if ig == None :
            pmdLoader.SearchRecursively = originalValue
            return False, ID
       
        i = ig.GetInfo(name)
        
        if i == None :
            pmdLoader.SearchRecursively = originalValue
            return False, ID

        pmdLoader.SearchRecursively = originalValue

        ID = clr.Convert(i.Id, Byte)
        
        return True, ID


    def close(self, connectionName):
        """Closes the phone connection.
        
            Parameters

            connectionName  "Main", "Remote1", "Remote2", ...
        """
        # unsubscribe from DataEvents
        if self.CommunicationAdapter:
            if not core.FW_conf['cli_mode']:
                self.CommunicationAdapter.DataEvent -= self._dataReceived
                self.CommunicationAdapter.EnableRaisingDataEvents = False

        # close primary connection
        if self.isConnected():
            self.CommunicationAdapter.Disconnect()

        # dispose Decoder
        if self.Decoder:
            self.Decoder.Dispose()

        # dispose fileSystem
        if self.fileSystem:
            self.fileSystem.Dispose()

        # dispose MessageSender
        if self.MessageSender:
            self.MessageSender.Dispose()

        # clear references to PMDLoader
        self.PMDLoader = None
        self.PMDFileHandler = None

        # clear references to connection layer
        self.CommunicationAdapter = None                
        self.Connection = None
        self.Decoder = None
        self.Encoder = None     # FIXME: Add disposing when taking Encoder into use
        self.BinaryLog = None
        self.MessageSender = None
        self.MessageApiSender = None
        self.fileSystem = None     

        # NOTE: when closing remote phone connection, we can't dispose ConnectionManager
        if self.ConnectionManager and connectionName == 'Main':
            # NOTE: ConnectionManager's Dispose will take care of disposing everything underneath
            # NOTE2: This can be done only once!!! Otherwise it will mess up the connection layer!
            self.ConnectionManager.Instance.Dispose()

        self.ConnectionManager = None

    def createFileData(self):
        
        """
        Creates a FileData object
        """
        
        if self.fileSystem == None :
            raise GraniteConnectionException('FileSystem interface is not initialized')
            
        try:
            return self.fileSystem.CreateFileData()
        except TestCaseException, exc :
            message = exc.Message
            if exc.InnerException :
                message = message + "; InnerException: " + exc.InnerException.Message
            raise GraniteFileSystemException(message)

    
    def createFolder(self, phoneFolderPath):
        
        """
        Creates folder to the phone.

            Parameters

            phoneFolderPath     phone's folder path in format
                                'C:\\predefgallery\\test'
        """
        
        if self.fileSystem == None :
            raise GraniteConnectionException('FileSystem interface is not initialized')
        
        if self.isConnected():
            try:
                self.fileSystem.CreateFolder(phoneFolderPath)
            except TestCaseException, exc :
                message = exc.Message
                if exc.InnerException :
                    message = message + "; InnerException: " + exc.InnerException.Message
                raise GraniteFileSystemException(message)
        else:
            raise GraniteConnectionException('Nokia.RD.Communication.Connection is not open.')
 

    def fileExists(self, phoneFilePath) :
        
        """
        Checks if a file exists in phone file system

            Parameters

            phoneFilePath     Path of the file in phone file system in format
            									'C:\\predefgallery\\test.txt'
            
            Returns
            
            True if exists; False otherwise
        """        
        if self.fileSystem == None :
            raise GraniteConnectionException('FileSystem interface is not initialized')
                                
        if self.isConnected():
            try:
                return self.fileSystem.FileExists(phoneFilePath)
                debug.brf('fileExist')
            except TestCaseException, exc :
                message = exc.Message
                if exc.InnerException :
                    message = message + "; InnerException: " + exc.InnerException.Message
                raise GraniteFileSystemException(message)
        else:
            raise GraniteConnectionException('Nokia.RD.Communication.Connection is not open.')

    def phoneHasMemoryCard(self) :
        
        """
        Checks if the device has a memory card inserted
            
            Returns
            
            True is memory card inserted
        """
        
        if self.fileSystem == None :
            raise GraniteConnectionException('FileSystem interface is not initialized')
        
        if self.isConnected():
            try:
                return self.fileSystem.PhoneHasMemoryCard()
            except TestCaseException, exc :
                message = exc.Message
                if exc.InnerException :
                    message = message + "; InnerException: " + exc.InnerException.Message
                raise GraniteFileSystemException(message)
        else:
            raise GraniteConnectionException('Nokia.RD.Communication.Connection is not open.')


    def getFolderContent(self, phoneFolderPath, searchPattern=None):
        
        """
        Returns folder content from the phone.

            Parameters

            phoneFolderPath     phone's folder path in format
                                'C:\\predefgallery'
            
            searchPattern				optinal string pattern to be utilized in search, e.g. *.mp*

        """
                
        if self.fileSystem == None :
            raise GraniteConnectionException('FileSystem interface is not initialized')
        
        if self.isConnected():
            try:
                            
                if searchPattern : 
                
                    folderContent = \
                                self.fileSystem.GetFolderContent(phoneFolderPath, searchPattern)
                else :
                    
                    folderContent = \
                                self.fileSystem.GetFolderContent(phoneFolderPath)
            except TestCaseException, exc :
                message = exc.Message
                if exc.InnerException :
                    message = message + "; InnerException: " + exc.InnerException.Message
                                
                #FIXME: Proper kind of check for not existing folder!!!
                if 'does not exist' in message:
                    return []

                raise GraniteFileSystemException(message)                
            else:
                return folderContent
        else:
            raise GraniteConnectionException('Nokia.RD.Communication.Connection is not open.')

    def readFile(self, phoneFilePath, localFilePath):
        
        """
        Read file from the phone.

            Parameters

            phoneFilePath   file path in phone in format
                            'C:\\predefgallery\\test.txt'

            localFilePath   local file path in format
                            'C:\\TEMP\\test.txt'
        """

        if self.fileSystem == None :
            raise GraniteConnectionException('FileSystem interface is not initialized')

        if self.isConnected():
            try:
                self.fileSystem.ReadFile(phoneFilePath, os.path.dirname(localFilePath))
            except TestCaseException, exc :
                message = exc.Message
                if exc.InnerException :
                    message = message + "; InnerException: " + exc.InnerException.Message
                raise GraniteFileSystemException(message)
        else:
            raise GraniteConnectionException('Nokia.RD.Communication.Connection is not open.')

    def getAvailableFreeSpace(self, drive):
        
        """
        Get the available free space from phone in bytes.

            Parameters

            phoneFilePath   file path in phone in format
                            'C:\\predefgallery\\test.txt'

            localFilePath   local file path in format
                            'C:\\TEMP\\test.txt'
        """
        
        freespace = -1
            
        if self.fileSystem == None :
            raise GraniteConnectionException('FileSystem interface is not initialized')

        if self.isConnected():
            try:
                freespace = self.fileSystem.GetAvailableFreeSpace(drive)
            except TestCaseException, exc :
                message = exc.Message
                if exc.InnerException :
                    message = message + "; InnerException: " + exc.InnerException.Message
                raise GraniteFileSystemException(message)
        else:
            raise GraniteConnectionException('Nokia.RD.Communication.Connection is not open.')            

        return freespace

    def hasMemoryCard(self):
        return self.fileSystem.PhoneHasMemoryCard()
        
    def fill(self, path, freemem = 0, filesize = 10):
        
        """
        Get the available free space from phone in bytes.

            Parameters

            path   file path in phone which is being filled

            freemem   memory after fill operation is done
            
            filesize  temporary file size what are used in fill operation
        """
                
            
        if self.fileSystem == None :
            raise GraniteConnectionException('FileSystem interface is not initialized')

        if self.isConnected():
            try:
                return self.fileSystem.Fill(path, freemem,filesize)
            except TestCaseException, exc :
                message = exc.Message
                if exc.InnerException :
                    message = message + "; InnerException: " + exc.InnerException.Message
                raise GraniteFileSystemException(message)
        else:
            raise GraniteConnectionException('Nokia.RD.Communication.Connection is not open.')            

        return None

    def removeFile(self, phoneFilePath):
        
        """
        Removes file from the phone.

            Parameters

            phoneFilePath   phone's file path in format
                            'C:\\predefgallery\\test.txt'

        """
        if self.fileSystem == None :
            raise GraniteConnectionException('FileSystem interface is not initialized')
            
        if self.isConnected():
            try:
                debug.out("Deleting file: " +phoneFilePath)
                self.fileSystem.DeleteFile(phoneFilePath)
            except TestCaseException, exc :
                message = exc.Message
                if exc.InnerException :
                    message = message + "; InnerException: " + exc.InnerException.Message
                raise GraniteFileSystemException(message)
        else:
            raise GraniteConnectionException('Nokia.RD.Communication.Connection is not open.')


    def removeFolder(self, phoneFolderPath):
        """Removes folder from the phone.

            Parameters

            phoneFolderPath     phone's folder path in format
                                'C:\\predefgallery\\test'

        """

        if self.fileSystem == None :
            raise GraniteConnectionException('FileSystem interface is not initialized')

        if self.isConnected():
            try:
                self.fileSystem.DeleteFolder(phoneFolderPath)
            except TestCaseException, exc :
                message = exc.Message
                if exc.InnerException :
                    message = message + "; InnerException: " + exc.InnerException.Message
                raise GraniteFileSystemException(message)
        else:
            raise GraniteConnectionException('Nokia.RD.Communication.Connection is not open.')


    def retrieveFiles(self, phoneFolderPath, searchPattern="*", searchRecursively=False) :
        
        """
        Retrieves all files and folder (relative names) from a given folder path

            Parameters

            phoneFolderPath		 	Absolute path of the folder in phone file system in format
            				      'C:\predefgallery'
            
            searchPattern		      Search pattern. '*' is supported
            
            searchRecursively		      Value indicating whether to searc recursively
            
            Returns
            
            Folder content as a python list of strings
        """
        
        if self.fileSystem == None :
            raise GraniteConnectionException('FileSystem interface is not initialized')
            
        if self.isConnected():
            try:
            
                contents = list()
            
                content = self.fileSystem.RetrieveFiles(phoneFolderPath, searchPattern, searchRecursively)
                
                if content :
                    for item in content :
                        contents.append(item)
                
                return contents
                
            except TestCaseException, exc :
                message = exc.Message
                if exc.InnerException :
                    message = message + "; InnerException: " + exc.InnerException.Message
                raise GraniteFileSystemException(message)
        else:
            raise GraniteConnectionException('Nokia.RD.Communication.Connection is not open.')
    
    
    def setAttribute(self, phoneItemPath, itemAttribute):
        
        """
        Sets file or folder attributes from the phone.

            Parameters

            phoneItemPath   phone's file path in format
                            'C:\\predefgallery\\test.txt'

            itemAttribute   see win32com's constants
                            (constants.eFileAttributeNormal)
        """

        if self.fileSystem == None :
            raise GraniteConnectionException('FileSystem interface is not initialized')
                       
        if self.isConnected():
            try:
                self.fileSystem.SetAttribute(phoneItemPath, itemAttribute)
            except TestCaseException, exc :
                message = exc.Message
                if exc.InnerException :
                    message = message + "; InnerException: " + exc.InnerException.Message
                raise GraniteFileSystemException(message)
        else:
            raise GraniteConnectionException('Nokia.RD.Communication.Connection is not open.')


    def writeFile(self, localFilePath, phoneDirPath):
        
        """
        Writes file to the phone.

            Parameters

            localFilePath       local file path in format
                                'C:\\TEST\\test.txt'
            phoneDirPath        phone's directory path in format
                                'C:\\predefgallery'
        """
        
        if self.fileSystem == None :
            raise GraniteConnectionException('FileSystem interface is not initialized')
        
        if self.isConnected():
            try:                
                return self.fileSystem.WriteFile(localFilePath, phoneDirPath)
            except TestCaseException, exc :
                message = exc.Message
                if exc.InnerException :
                    message = message + "; InnerException: " + exc.InnerException.Message
                raise GraniteFileSystemException(message)
        else:
            raise GraniteConnectionException('Nokia.RD.Communication.Connection is not open.')


    def writeFromBuffer(self, phoneFilePath, fileData):
        
        """
        Writes file to the phone using file data buffer.

            Parameters

            phoneFilePath       phone's file path in format
                                'C:\\predefgallery\\test.txt')
            fileData            file data object, array of bytes, or (System.Collections.Generic.)List of Bytes
        """
        
        if self.fileSystem == None :
            raise GraniteConnectionException('FileSystem interface is not initialized')
        
        if self.isConnected():
            try:
                return self.fileSystem.WriteFromBuffer(phoneFilePath, fileData)
            except TestCaseException, exc :
                message = exc.Message
                if exc.InnerException :
                    message = message + "; InnerException: " + exc.InnerException.Message
                raise GraniteFileSystemException(message)
        else:
            raise GraniteConnectionException('Nokia.RD.Communication.Connection is not open.')


class StopWatch(object) :

    def __init__(self) :

        self.startTime = DateTime(0)

    def start(self) :

        self.startTime = DateTime.Now

    def split(self) :

        if self.startTime != DateTime(0) :

            return DateTime.Now.Subtract(self.startTime).TotalMilliseconds

        else :
            return 0.0     

    def stop(self) :

        retVal = self.split()
        self.startTime = DateTime(0)
        return retVal


class DeviceScannerAndMap(object) :
    
    """
    Class for using Nokia Device Scanner and Device Map Type Library.
    """
    
    def __init__(self) :
        
        """
        Initialize variables.
        """
        
        self.scaningOngoing = False
        self.devices = None
        self.scannedDevices = None

        self.deviceMapInstance = DeviceMapClass()
        self.deviceMapInstance.MonitorDeviceType = EnumDeviceTypes.eDeviceTypeNokiaTerminal
        self.deviceMapInstance.OnDeviceChanged += self.deviceMapInstance_OnDeviceChanged

        self.deviceScannerInstance = DeviceAndProductScannerClass()
        self.deviceScannerInstance.OnScanningAborted += self.deviceScannerInstance_OnScanningAborted
        self.deviceScannerInstance.OnScanningFinish += self.deviceScannerInstance_OnScanningFinish

        
    def deviceMapInstance_OnDeviceChanged(self, eStatus, bstrDevicePath, bstrDeviceProperty) :

        self.scaningOngoing = False
        print 'device changed: %s' % \
              ','.join([str(eStatus), str(bstrDevicePath), str(bstrDeviceProperty)])


    def deviceScannerInstance_OnScanningAborted(self) :

        self.scaningOngoing = False
        print 'scanning aborted...'


    def deviceScannerInstance_OnScanningFinish(self, eDeviceType) :

        self.scaningOngoing = False
        print 'scanning finished...'
 
                       
    def __startScanning(self, timeout):
        
        """
        Starts scanning usb phones. Uses "Nokia.DeviceAndProductScanner.1"

            Parameters

            timeout         wait timeout in seconds after scan
        """
        
        try:
            self.deviceScannerInstance.StartScanning(EnumScanDeviceType.eScanDeviceTypeProduct,
                                                     EnumScanMedia.eScanMediaUsb)
            sw = StopWatch()
            sw.start()

            self.scaningOngoing = True

            while self.scaningOngoing :

                if sw.split() >= TimeSpan.FromSeconds(clr.Convert(timeout, Double)).TotalMilliseconds :

                    self.scaningOngoing = False
                    raise GraniteConnectionException('Timeout occured when scanning devices')

                Thread.CurrentThread.Join(200)

            self.__abortScanning()

        except Exception, exc :
            raise GraniteConnectionException(\
                'Error in scanning devices: %s' % str(exc))


    def __abortScanning(self):
        
        """
        Aborts scanning of devices. Uses "Nokia.DeviceAndProductScanner.1" 
        """
        
        try:

            self.deviceScannerInstance.AbortScanning()
            
        except Exception, exc :
            raise GraniteConnectionException(\
                'Error in aborting scanning of devices: %s' % str(exc))


    def getDevices(self, timeout = 3):
        
        """
        Get devices that are connected via usb.
        Uses both "Nokia.DeviceMap.1" and "Nokia.DeviceAndProductScanner.1".

        Parameters

        timeout			wait timeout in seconds after scan (default = 3)

        Puts connected device instances to self.devices and
        self.scannedDevices.
        """
        
        try:
            self.devices = self.deviceMapInstance.GetDevices(\
                                EnumDeviceTypes.eDeviceTypeNokiaTerminal)

            self.__startScanning(timeout)
            self.scannedDevices = self.deviceScannerInstance.GetDevicesAndProducts()

            if self.devices.Count == 0 or self.scannedDevices.Count == 0:
                self.devices = None
                self.scannedDevices = None
                raise GraniteConnectionException('No devices found.')
        except Exception, exc:
            raise GraniteConnectionException('No devices found: %s' % str(exc))
            self.devices = None
            self.scannedDevices = None

    def getDeviceCount(self):
        
        """
        Get device count. Uses "Nokia.DeviceAndProductScanner.1".
        """
        
        return self.scannedDevices and self.scannedDevices.Count or 0


    def getDeviceDescription(self, index = 1):
        
        """
        Get device description by index. Uses "DeviceMapClass".

        Parameters

        index       device index number (1...n)

        Returns device description or None.
        """
        
        deviceDescription = None

        assert type(index) == types.IntType, 'index must be integer!'

        try:
            if self.devices and index <= self.devices.Count:
                deviceDescription = \
                    self.devices.Item(index = index).DeviceDescription
        except Exception, exc:
            raise GraniteConnectionException(\
                'Error in getting device description: %s' % str(exc))

        return deviceDescription


    def getDevicePath(self, index = 1):
        
        """
        Get device path by index. Uses "DeviceMapClass".

        Parameters

        index       device index number (1...n)

        Returns device path or None.
        """
        
        devicePath = None

        assert type(index) == types.IntType, 'index must be integer!'

        try:
            if self.devices and index <= self.devices.Count:
                devicePath = \
                    self.devices.Item(index = index).DevicePath
        except Exception, exc:
            raise GraniteConnectionException(\
                'Error in getting device path: %s' % str(exc))

        return devicePath


    def getComPort(self, index = 1):
        
        """
        Get com port by index. Uses "DeviceMapClass".

        Parameters

        index       device index number (1...n)

        Returns com port or None.
        """
        
        comPort = None

        assert type(index) == types.IntType, 'index must be integer!'

        try:
            if self.scannedDevices and index <= self.scannedDevices.Count:
                comPort = \
                    self.scannedDevices.Item(index = index).ComPort
        except Exception, exc:
            raise GraniteConnectionException(\
                'Error in getting com port: %s' % str(exc))

        return comPort


    def getDeviceName(self, index = 1):
        
        """
        Get device name by index. Uses "Nokia.DeviceAndProductScanner.1".

        Parameters

        index       device index number (1...n)

        Returns device name or None.
        """
        
        deviceName = None

        assert type(index) == types.IntType, 'index must be integer!'

        try:
            if self.scannedDevices and index <= self.scannedDevices.Count:
                deviceName = \
                    self.scannedDevices.Item(index = index).DeviceName
        except Exception, exc:
            raise GraniteConnectionException(\
                'Error in getting device name: %s' % str(exc))

        return deviceName


    def getDeviceType(self, index = 1):
        
        """
        Get device type by index. Uses "Nokia.DeviceAndProductScanner.1".

        Parameters

        index       device index number (1...n)

        Returns device type or None.
        """
        
        deviceType = None

        assert type(index) == types.IntType, 'index must be integer!'

        try:
            if self.scannedDevices and index <= self.scannedDevices.Count:
                deviceType = \
                    self.scannedDevices.Item(index = index).DeviceType
        except Exception, exc:
            raise GraniteConnectionException(\
                'Error in getting device type: %s' % str(exc))

        return deviceType


    def getDeviceId(self, index = 1):
        
        """
        Get device id by index. Uses "Nokia.DeviceAndProductScanner.1".

        Parameters

        index       device index number (1...n)

        Returns device id or None.
        """
        
        deviceId = None

        assert type(index) == types.IntType, 'index must be integer!'

        try:
            if self.scannedDevices and index <= self.scannedDevices.Count:
                deviceId = \
                    self.scannedDevices.Item(index = index).Id
        except Exception, exc:
            raise GraniteConnectionException(\
                'Error in getting com port: %s' % str(exc))

        return deviceId


    def getMedia(self, index = 1):
        
        """
        Get media by index. Uses "Nokia.DeviceAndProductScanner.1".

        Parameters

        index       device index number (1...n)

        Returns media or None.
        """
        
        media = None

        assert type(index) == types.IntType, 'index must be integer!'

        try:
            if self.scannedDevices and index <= self.scannedDevices.Count:
                media = \
                    self.scannedDevices.Item(index = index).Media
        except Exception, exc:
            raise GraniteConnectionException(\
                'Error in getting media: %s' % str(exc))

        return media


    def getProductHardwareVersion(self, index = 1):
        
        """
        Get product hardware version by index. Uses "Nokia.DeviceAndProductScanner.1".

        Parameters

        index       device index number (1...n)

        Returns product hardware version or None.
        """
        
        hardwareVersion = None

        assert type(index) == types.IntType, 'index must be integer!'

        try:
            if self.scannedDevices and index <= self.scannedDevices.Count:
                hardwareVersion = \
                    self.scannedDevices.Item(index = index).ProductHardwareVersion
        except Exception, exc:
            raise GraniteConnectionException(\
                'Error in getting product hardware version: %s' % str(exc))

        return hardwareVersion


    def getProductImei(self, index = 1):
        
        """
        Get product imei by index. Uses "Nokia.DeviceAndProductScanner.1".

        Parameters

        index       device index number (1...n)

        Returns product imei or None.
        """
        
        productImei = None

        assert type(index) == types.IntType, 'index must be integer!'

        try:
            if self.scannedDevices and index <= self.scannedDevices.Count:
                productImei = \
                    self.scannedDevices.Item(index = index).ProductImei
        except Exception, exc:
            raise GraniteConnectionException(\
                'Error in getting product imei: %s' % str(exc))

        return productImei


    def getProductSoftwareVersion(self, index = 1):
        
        """
        Get product software version by index. Uses "Nokia.DeviceAndProductScanner.1".

        Parameters

        index       device index number (1...n)

        Returns product software version or None.
        """
        
        softwareVersion = None

        assert type(index) == types.IntType, 'index must be integer!'

        try:
            if self.scannedDevices and index <= self.scannedDevices.Count:
                softwareVersion = \
                    self.scannedDevices.Item(index = index).ProductSoftwareVersion
        except Exception, exc:
            raise GraniteConnectionException(\
                'Error in getting product software version: %s' % str(exc))

        return softwareVersion


    def getProductType(self, index = 1):
        
        """
        Get product type by index. Uses "Nokia.DeviceAndProductScanner.1".

        Parameters

        index       device index number (1...n)

        Returns product type or None.
        """
        
        productType = None

        assert type(index) == types.IntType, 'index must be integer!'

        try:
            if self.scannedDevices and index <= self.scannedDevices.Count:
                productType = \
                    self.scannedDevices.Item(index = index).ProductType
        except Exception, exc:
            raise GraniteConnectionException(\
                'Error in getting product type: %s' % str(exc))

        return productType


    def getIpAddress(self, index = 1):
        
        """
        Get ip address by index. Uses "Nokia.DeviceAndProductScanner.1".
        Returns nothing with phones, valid only with devices.

        Parameters

        index       device index number (1...n)

        Returns ip address or None.
        """
        
        ipAddress = None

        assert type(index) == types.IntType, 'index must be integer!'

        try:
            if self.scannedDevices and index <= self.scannedDevices.Count:
                ipAddress = \
                    self.scannedDevices.Item(index = index).IpAddress
        except Exception, exc:
            raise GraniteConnectionException(\
                'Error in getting ip address: %s' % str(exc))

        return ipAddress


    def getSerialNumber(self, index = 1):
        
        """
        Get serial number by index. Uses "Nokia.DeviceAndProductScanner.1".
        Returns nothing with phones, valid only with devices.

        Parameters

        index       device index number (1...n)

        Returns serial number or None.
        """
        
        serialNumber = None

        assert type(index) == types.IntType, 'index must be integer!'

        try:
            if self.scannedDevices and index <= self.scannedDevices.Count:
                serialNumber = \
                    self.scannedDevices.Item(index = index).SerialNumber
        except Exception, exc:
            raise GraniteConnectionException(\
                'Error in getting serial number: %s' % str(exc))

        return serialNumber
