import clr
import time
import core
from core import debug

clr.AddReference('accCntr.dll')
from accCntr import *

clr.AddReference('MessageAPI.Accessory')
from Nokia.RD.MessageAPI.Accessory.Messages import *
from Nokia.RD.MessageAPI.Accessory.Tables import *

clr.AddReference('Nokia.Trident.Phone')
from Nokia.Trident.Phone import Indications, TestCaseException

##clr.AddReference('MessageAPI')
##from Nokia.RD.MessageAPI import ReceivedMessagesIterator, IsiVersion, PhonetResource


class AccessoryControl:
    """ Accessory controlling module. Needs accesory box to be connected """ 

    OPEN_CABLE = 'open cable'
    DISCONNECT = 'disconnect' # separate disconnect value when sending disconnect isi message
    ECI_HEADSET = 'eci headset'
    BASIC_HEADSET = 'basic headset'
    HEADPHONE = 'headphone'
    CVIDEO = 'cvideo'

    # accessory box connections
    _accBoxAddressDict = {
            OPEN_CABLE: 2,
            ECI_HEADSET: 5,
            BASIC_HEADSET: 7,
            HEADPHONE: 8,
            CVIDEO: 6,
            DISCONNECT: 2
    }

    # indication check dictionary contains values that are checked from accessory connection indication message
    _accConnectionIndicationCheckDict = {
        HEADPHONE: {
            'AudioProfile': 'ACC_HEADPHONE',
            # 'AudioType': 'ACC_STEREO',
            # 'Connector': 'ACC_CONNECTOR_NOKIA_AV',
            'DeviceProfile': 'ACC_DP_FM_RADIO_ANTENNA',
            # 'EnhancementActive': 'ACC_ON'
            'Subblocks': '0'
        },
        OPEN_CABLE: {
            'AudioProfile': 'ACC_NO_AUDIO',
            'DeviceProfile': 'ACC_DP_OPEN_CABLE',
            'Subblocks': '0',
        },
        DISCONNECT: {        
            'AudioProfile': 'ACC_NO_AUDIO',
            'DeviceProfile': 'ACC_DP_NOT_CONNECTED',
            'Subblocks': '0',

        },
        ECI_HEADSET: {
            'AudioProfile': 'ACC_HEADSET',
            'DeviceProfile': 'ACC_DP_FM_RADIO_ANTENNA',
            'Subblocks': '1',
        },
        CVIDEO: {
            'AudioProfile': 'ACC_HEADPHONE',
            'DeviceProfile': 'ACC_DP_FM_RADIO_ANTENNA',
            'Subblocks': '0',
        },
        BASIC_HEADSET: {
            'AudioProfile': 'ACC_HEADSET',
            'DeviceProfile': 'ACC_DP_FM_RADIO_ANTENNA',
            'Subblocks': '1',
        }

        
    }
        
    def __init__(self, communicationAdapter = None):
        """initialize accessory control. uses main phone settings CorVA/AccessoryBoxConnected"""
        
        debug.brf( "Accessory Control initialize")
        if communicationAdapter == None:
            communicationAdapter = core.FW_conf['connection'].graniteConnection.CommunicationAdapter
            self.connection = core.FW_conf['connection']

        self._AccOn = core.FW_conf['settings'].Multimedia.AccessoryBoxConnected
        
        if self._AccOn == "False":
            self._AccOn = False  # set False string to False boolean
        if self._AccOn == "True":
            self._AccOn = True  # set True string to True boolean
        
        if self._AccOn:
            debug.brf( "%s: Trying to activate accessorybox..." % (self.__class__.__name__))
            self._AccessoryBox = accCntr_cl()
            if not self._AccessoryBox.AccBoxActivate():
                raise TestCaseException("%s: Accessory Box activation failed." % (self.__class__.__name__) )
            debug.brf( "%s: Accessory Control activated" % (self.__class__.__name__))
            
        else:
            debug.brf( "%s: WARNING: ACCESSORY BOX NOT CONNECTED. Dummy mode.." % (self.__class__.__name__) )
            
        self.MessageSender = communicationAdapter.MessageApiSender
        
      
    def _checkAccessoryIndication(self, indication, accessory=None):
        """verify accessory indication""" 
        
        if accessory == None:
            accessory = self.DISCONNECT  # select disconnection by default
            debug.brf( "%s: No accessory defined, selecting %s. Check Accessory Indication for accessory %s..." % (self.__class__.__name__,self.DISCONNECT, accessory) )
        else:
            debug.brf( "%s: Check Accessory Indication for accessory %s..." % (self.__class__.__name__, accessory) )

        # save things needed for indication to a dictionary. AudioType, Connector, EnhancementActive not needed at the moment
        indRespDict = {
            'AudioProfile': indication.AudioProfile.ToString(),
            # 'AudioType': indication.AudioType.ToString(),
            # 'Connector': indication.Connector.ToString(),
            'DeviceProfile': indication.DeviceProfile.ToString(),
            'Subblocks': indication.Subblocks.Count.ToString()
            # 'EnhancementActive': indication.EnhancementActive.ToString()
        }

        # if accessory has not been defined in class variable (dictionary), raise test case exception        
        if not self._accConnectionIndicationCheckDict.has_key(accessory):
            debug.brf( "%s: No indication responses defined for accessory %s\nIndication responses received:" % (self.__class__.__name__, accessory ) )
            for key in sorted(indRespDict):
                debug.brf( "\'%s\': \'%s\'," % (key, indRespDict[key]) )
            raise TestCaseException("%s: No accessory indication values defined for accessory \'%s\'" % (self.__class__.__name__, accessory) )
                
        # check indRespDict against class variable accConnectionIndicationCheckDict, if not matching, print out incorrect attributes.
        if indRespDict != self._accConnectionIndicationCheckDict[accessory]:
            for k in indRespDict:
                if not k in self._accConnectionIndicationCheckDict[accessory]:
                    debug.brf( "%s: Error: key %s is not defined in indication response table %s." % ( self.__class__.__name__, k, accessory) )
                elif indRespDict[k] != self._accConnectionIndicationCheckDict[accessory][k]:
                    debug.brf( "%s: Expected (%s indication property %s) %s, got %s" % ( self.__class__.__name__, accessory, k, self._accConnectionIndicationCheckDict[accessory][k], indRespDict[k]) )
                    
            debug.brf( "Check these indication responses and add/modify to dictionary if correct(%s)" % accessory )
            for key in sorted(indRespDict):
                debug.brf( "\'%s\': \'%s\'," % (key, indRespDict[key]) )
            
            if self._AccOn:
                raise TestCaseException("%s: Accessory indication receive check failed" % (self.__class__.__name__) )
            else:
                debug.brf( "%s: Accessory Box Control OFF, not raising a fail. (Indication was not OK!)" % (self.__class__.__name__) )
                
        else:
            debug.brf( "%s: Accessory indication OK!" % (self.__class__.__name__) )
        
    
    def _sendAccessoryRequest(self, accessory=None, disconnect=False, verifyIndication=True):
        """handles accessory request sending and indication verification if needed"""
        
        debug.brf( '%s: sending accessory simulate request asynchronously' % (self.__class__.__name__) )

        # 0x0e = ACC_SIMULATE_PLUG_CONNECT = 14

        # select either disconnect or connect
        if disconnect:
            action = AccTestReq.ActionField(AccTestReqAction.ACC_SIMULATE_PLUG_DISCONNECT)
            debug.brf( "%s: send disconnect request" % (self.__class__.__name__) )
        else:
            action = AccTestReq.ActionField(AccTestReqAction.ACC_SIMULATE_PLUG_CONNECT)
            debug.brf( "%s: send connect request" % (self.__class__.__name__) )
        
        # test request to be sent
        req = AccTestReq(action)
        
        if verifyIndication: # subscribe to PN_ACCESSORY indications
            self.connection.queryIndications("PN_ACCESSORY")
            iter = self.connection.graniteConnection.createMessageIterator("PN_ACCESSORY", "ACC_CONNECTION_IND")
        
        self.MessageSender.SendAsynchronously(req)
        
        if verifyIndication: debug.brf( '%s: Reading response indication' % (self.__class__.__name__) )
        
        if verifyIndication: 
            ind = iter.GetNext()
            
            if (ind != None):
                try:
                    self._checkAccessoryIndication(ind, accessory)
                except:
                    self.connection.graniteConnection.unsubscribeIndications("PN_ACCESSORY")
                    raise TestCaseException("%s: Accessory request failed, indication was NOT OK." % self.__class__.__name__ )
            else:
                iter.Dispose()
                self.connection.graniteConnection.unsubscribeIndications("PN_ACCESSORY")
                raise TestCaseException("%s: Accessory request failed, could not get indication from server" % self.__class__.__name__ )

            self.connection.graniteConnection.unsubscribeIndications("PN_ACCESSORY")
            iter.Dispose()

    def _deactivateAccessoryBox(self):
        """deactivate accessory box via accCtrl.dll""" 
        debug.brf('%s deactivate accessorybox' % (self.__class__.__name__))
        if self._AccOn: self._AccessoryBox.AccBoxDeactivate()

    def disconnectAccessory(self, verify=True):
        """desconnect accessory with accessory box, send accessory disconnection request and verify indication""" 
        if not self._AccOn:
            debug.brf( '%s: (disconnect) Accessory box is not enabled, simulating disconnection' % (self.__class__.__name__ ) )
            self._sendAccessoryRequest(disconnect=True, verifyIndication=False)
            return
        
        debug.brf( '%s: disconnecting accessory (verify disconnection:\'%s\')' % (self.__class__.__name__, verify ))
        if self._AccOn:
            self._AccessoryBox.SelectAcc(AccessoryControl._accBoxAddressDict[self.DISCONNECT])
        self._deactivateAccessoryBox()
        self._sendAccessoryRequest(disconnect=True, verifyIndication=verify)
        
    def insertAccessory(self, accessory=None):
        """insert accessory with accessory box, send accessory request (and verify indication)"""
        
        if not self._AccOn:
            debug.brf( '%s: (insert accessory %s) Accessory box is not enabled, simulating connection' % (self.__class__.__name__, accessory ))
            self._sendAccessoryRequest(accessory, disconnect=False, verifyIndication=False)
            return
        
        # disconnect accessory without getting indication
        self.disconnectAccessory(verify=False)
                
        if accessory != None and AccessoryControl._accBoxAddressDict.has_key(accessory):
            debug.brf( '%s: insert accessory "%s" (%s)' % (self.__class__.__name__, accessory, AccessoryControl._accBoxAddressDict[accessory] ))
            if self._AccOn: self._AccessoryBox.SelectAcc(AccessoryControl._accBoxAddressDict[accessory])
            self._sendAccessoryRequest(accessory)
        else:
            raise TestCaseException("%s: error: no accessory \"%s\" address defined (accBox)" % (self.__class__.__name__, accessory) )
            
