"""Controll module for phone middleware features.
    This module implements middleware interfaces that can be used through Granite test case scripts.
"""
import clr
clr.AddReference('Nokia.Trident.Phone')
clr.AddReference('Nokia.Granite.Middleware')

import core, os
from core import uitestcase, debug
from core.testcase_exceptions import TestException

from utils.sx_utils import SxUtils

from System import DateTime, Int32

from System.Collections.Generic import List
from System.IO import Path, File, FileInfo

import zipfile

from Nokia.Granite.Middleware import ServerInterface
from interfaces import srv_granite

class JavaComponent:
    def __init__(self, phone):        
        self.phone = phone
        self.sxUtils = SxUtils()

    def isJavaApplicationRunning(self, jadFileUri) :
        """Checks if a java application with given yapas file uri is executing"""
        
        isRunningQuery = """
        
        (define jad-path "{0}")
        (define suite-id (send javamanager open-jad jad-path))
        (define current (send javamanager get-application))
        
        (when (object? current)
            (eqv? suite-id (send current get-suite-id))
                "true"
            else
                "false"
        )
        
        """
        
        result = self.phone.sx(self.sxUtils.FormatSxString(isRunningQuery, jadFileUri), doNotReport = True)
        debug.brf('javamanager returned: ' + result)
        if not result.StartsWith('true') and not result.StartsWith('false') :
            
            raise TestException('Failed to determine running state of ' + jadFileUri, self.phone)
        
        debug.brf(Path.GetFileName(jadFileUri) + ' is running? ' + result)
        return result.StartsWith('true')

    def getNumberOfExecutingJavaApplications(self) :
        """Gets the number of running Java midlets from yapas."""
        
        sxJavaAppCountQuery = """
            (define appCount (send javamanager count-running-midlets))
            (define toString (number->string appCount))
            toString
            """
        
        # Perform five attempts since sometimes the return value is something else than integer
        for attempt in range(5):

            result = self.phone.sx(sxJavaAppCountQuery, doNotReport = True)
            
            parsed, result = Int32.TryParse(result)

            if parsed:
                
                debug.brf('Number of executing Java applications: ' + str(result))
                return result
                
            else :
                self.phone.delay(500)
                
        raise TestException('Failed to determine number of executing Java applications', self.phone)

    def killJavaApplications(self, verifyKill = True) :
        """Kills all the running Java applications.
        
        Parameters:
            verifyKill(bool)     :   Flag to verify whether the Java application were all killed.

        """
        
        killAll = """
        
        (send (get-app-manager) kill-all false false)
        "ok"
        
        """
        
        if not self.phone.sx(killAll, doNotReport = True).StartsWith('ok') and verifyKill:
            raise TestException('Failed to kill executing Java applications', self.phone)
        
        self.phone.delay(500)
        
        return self.getNumberOfExecutingJavaApplications == 0


    def javaApplicationIsInstalled(self, jadPathInYapas) :
        """Checks a Java application with given yapas file URI is installed.
        
        Parameters:
            jadPathInYapas(string)     :   Path to the Java application descriptor file

        """
        
        isInstalled = """
            
            (when (= (send javamanager open-jad "{0}") java-ams-not-installed-id)
            		"false"
            	else
            		"true"
            )
            
            """
        
        result = self.phone.sx(self.sxUtils.FormatSxString(isInstalled, jadPathInYapas), doNotReport = True)
        
        if not result.StartsWith('true') and not result.StartsWith('false'):
            raise TestException('Failed to determine whether a java application is installed', self.phone)
        
        return result.StartsWith('true')
    
    
    def installJavaApplication(self, jarFileOnPc, timeout = 10000) :
        """Uploads a jar-jad file pair to device, and installs the application.
        
        Parameters:
            jarFileOnPc(string) :   Path to the Java archive or Java application descriptor file.
            timeout(int)        :   Maximum time in milliseconds to allow for the installation.
        """
        
        # If a Java application descriptor file has been supplied
        if Path.GetExtension(jarFileOnPc.ToLower()) == '.jad':
            # Use the Java archive file instead
            jarFileOnPc = Path.ChangeExtension(jarFileOnPc, '.jar')
        
        if Path.GetExtension(jarFileOnPc.ToLower()) != '.jar':
            raise TestCaseException(jarFileOnPc + ' is not supported')
        
        sourceJar = FileInfo(jarFileOnPc)
        sourceJad = FileInfo(Path.ChangeExtension(sourceJar.FullName, '.jad'))
        
        if not sourceJar.Exists:
            raise TestException(sourceJar.FullName + ' does not exist in PC', self.phone)
        
        if sourceJar.Length == 0:
            raise TestCaseException(sourceJar.FullName + ' is empty')
        
        if not sourceJad.Exists:
            raise Testexception(sourceJad.FullName + ' does not exist in PC', self.phone)
                
        if sourceJad.Length == 0:
            raise TestCaseException(sourceJad.FullName + ' is empty')
        
        # Read the Java application descriptor file as text
        info = list(File.ReadAllLines(sourceJad.FullName))
        info.insert(0, 'MIDlet information:')

        # Read the Java archive file as a zip file
        with zipfile.ZipFile(sourceJar.FullName, "r") as root:

            # Append the name of each class file in the zip
            info.append('Classes in MIDlet-Jar: ' + ', '.join([Path.GetFileName(cl) for cl in root.namelist() if Path.GetExtension(cl.ToLower()) == ".class"]))
        
        # Log the Java midlet information
        self.phone.comment("\n".join("%s"%line for line in info))
        
        # Use the memory card by default
        destinationFolder = 'E:\\NTH'
        
        # If the phone does not have a memory card
        if not self.phone.graniteConnection.phoneHasMemoryCard():
            # Use phone memory
            destinationFolder = r'C:\sp\usr\_phone\NTH'

        # Construct the full file path for the Java archive and application descriptor files                     
        jarFile = Path.Combine(destinationFolder, Path.GetFileName(sourceJar.FullName))
        jadFile = Path.ChangeExtension(jarFile, '.jad')

        # Convert the Java application descriptor file path to a URI
        jadFileMap = self.sxUtils.ConvertToSpFileUri(jadFile)
        
        # Get the lines containing midlet names       
        midletName = [line for line in info if line.Contains("MIDlet-Name:")]
        
        # If there lines with a midlet name
        if midletName.Count:
            # Get the first midlet name
            midletName = midletName[0]
            midletName = midletName.Substring(midletName.IndexOf("MIDlet-Name:") + 12).Trim()
        # Else there are no midlet names
        else:
            # Use the Java archive file name as the midlet name
            midletName =  Path.GetFileNameWithoutExtension(jarFile)
        
        # If this Java application is already installed
        if self.javaApplicationIsInstalled(jadFileMap):
            # Uninstall the Java application
            self.uninstallJavaApplication(jadFileMap, deleteFiles = True)
        
        # Copy the file Java archive and Java application descriptor files to the phone    
        self.phone.graniteConnection.writeFile(sourceJar.FullName, destinationFolder)
        self.phone.graniteConnection.writeFile(sourceJad.FullName, destinationFolder)

        installJava = """
        
        (define jad-path "{0}")    
        (application-invoke (string-append "x-java:-1*" jad-path "*Installer"))
        "ok"
        
        """

        # Start the Java application installation
        result = self.phone.sx(self.sxUtils.FormatSxString(installJava, jadFileMap), doNotReport = True)
        
        if not result.StartsWith('ok'):
            raise TestException('Failed to start installing ' + midletName, self.phone)
        
        self.phone.comment('Started installing ' + midletName + ' ...')
        
        installStart = DateTime.Now

        # Wait for the Java application to finish being installed
        while not self.javaApplicationIsInstalled(jadFileMap) and DateTime.Now.Subtract(installStart).TotalMilliseconds < timeout:
            debug.brf('Waiting for ' + midletName + ' to be installed ...')
            self.phone.delay(1000)
            self._removeInstallConfirmationDialogAndContinue(midletName)
        
        if not self.javaApplicationIsInstalled(jadFileMap):
            raise TestException('Timeout when installing ' + midletName, self.phone)
        
        self.phone.comment('Finished installing ' + midletName)
            
        return midletName, jadFileMap
    
    def _removeInstallConfirmationDialogAndContinue(self, midletName):
        """Removes the install confirmation dialog if it appears and continues with the install.
        
        Parameters:
            midletName(string) :   Name of the MIDlet currently being installed.
        """

        removeInstallConfirmationDialogAndContinue = """
        
        (define top-app (send (get-app-manager) get-topmost-application))
        (when (string=? "java-dialog" (send top-app get-name))
            (send (send top-app get-topmost-screen) remove-self)
            (send javamanager reply-installer 1)
        )
        "ok"

        """

        # Remove the install confirmation dialog if it appears and continue
        result = self.phone.sx(removeInstallConfirmationDialogAndContinue, doNotReport = True)
        
        if not result.StartsWith('ok'):
            raise TestException('Failed to remove the install confirmation dialog and continue while installing ' + midletName, self.phone)
    
    def uninstallJavaApplication(self, jadPathInYapas, timeout = 10000, deleteFiles = False) :
        """Uninstalls a jar-jad file pair from device and optionally deletes the files.
        
        Parameters:
            jadPathInYapas(string) :   Path to the Java application descriptor file on device.
            timeout(int)           :   Maximum time in milliseconds to allow for the un-install.
            deleteFiles(bool)      :   If set to True the Java files will be deleted from device.
        """    

        uninstallJava = """
                                        
        (define jad-path "{0}")
        (define suite-id (send javamanager open-jad jad-path))
        (send (get-java-ams) remove-suite suite-id false)
        "ok"
        
        """
        
        # Start the Java application uninstall
        result = self.phone.sx(self.sxUtils.FormatSxString(uninstallJava, jadPathInYapas), doNotReport = True)
        
        if not result.StartsWith('ok'):
            raise TestException('Failed to start uninstalling ' + jadPathInYapas, self.phone)
        
        uninstallStart = DateTime.Now
        
        # Wait for the Java application to finish being uninstalled
        while self.javaApplicationIsInstalled(jadPathInYapas) and DateTime.Now.Subtract(uninstallStart).TotalMilliseconds < timeout:
            self.phone.delay(500)
        
        if self.javaApplicationIsInstalled(jadPathInYapas):
            raise TestException('Failed to uninstall ' + jadPathInYapas, self.phone)

        if deleteFiles:
            self._deleteJavaFilesViaYapas(jadPathInYapas, Path.ChangeExtension(jadPathInYapas, '.jar'))

    def _deleteJavaFilesViaYapas(self, jadFileUri, jarFileUri) :
        """Deletes a jar-jad file pair from device.
        
        Parameters:
            jadPathInYapas(string) :   Path to the Java application descriptor file on device.
            jarPathInYapas(string) :   Path to the Java archive file on device.
        """    
               
        delete = """
        
        (define jad-path "{0}")
        (define jar-path "{1}")
        (when (uri-file-exists? jad-path)
            (delete-file jad-path)
        )
        (when (uri-file-exists? jar-path)
            (delete-file jar-path)
        )
        "ok"
        
        """

        # Delete the Java application descriptor and Java archive files
        result = self.phone.sx(self.sxUtils.FormatSxString(delete, jadFileUri, jarFileUri), doNotReport = True)
        
        if not result.StartsWith('ok'):
            raise TestException('Failed to delete jar/jad files', self.phone)

    def executeJavaApplication(self, jadPathInYapas, timeout = (5 * 60000)) :
        """Starts executing an installed java application.
                
        Parameters:
            jadPathInYapas(string) :   Path to the Java application descriptor file on device.
            timeout(int)           :   Maximum time in milliseconds to allow for execution.
        """
        
        executeJava = """
                
        (define jad-path "{0}")
               
        (define suite-id (send javamanager open-jad jad-path))
        (define prop-string (send javamanager get-suite-property suite-id "MIDlet-1"))
        (define prop-list (split-string prop-string ","))
        (define midlet-name (list-ref prop-list 0))
        (define midlet-class (list-ref prop-list 2))
        
        (debug "midlet name: " midlet-name)
        (debug "midlet class: " midlet-class)
        (send (get-java-manager) invoke-java-app suite-id midlet-class midlet-name false)
        "ok"
        
        """

        # Start executing the Java application using the Java application descriptor file
        result = self.phone.sx(self.sxUtils.FormatSxString(executeJava, jadPathInYapas), doNotReport = True)
        
        if not result.StartsWith('ok'):
            raise TestException('Failed to start executing java', self.phone)
        
        self.phone.comment('Java execution started')
        
        executionStart = DateTime.Now
        
        # Add a delay to wait for the Java application to start
        self.phone.delay(1000)
        
        # Wait for the Java application to finish executing
        while self.isJavaApplicationRunning(jadPathInYapas) and DateTime.Now.Subtract(executionStart).TotalMilliseconds < timeout: 
            debug.brf('Executing ' + Path.GetFileName(jadPathInYapas) + ' ...')
            self.phone.delay(1000)
        
        # If the Java application did not finish executing within the timeout period
        if self.isJavaApplicationRunning(jadPathInYapas):
            self.killJavaApplications(False)
            raise TestException('Timeout when executing java', self.phone)
        
        self.phone.comment('Finished executing Java')            


    def getReports(self, reportFolder) :
        """Gets file names of the text in the report folder.
        
        Parameters:
            reportFolder(string) :   Path of the report folder on the device.
        """
        
        # Return the file names in the report folder that are text files
        return [Path.Combine(reportFolder, txt) for txt in self.phone.graniteConnection.retrieveFiles(reportFolder) if Path.GetExtension(txt.ToLower()) == ".txt"]

class Sensor:
    def __init__(self, phone):
        self.phone = phone
        
    def setLandscape(self):
        self.setOrientation('left')
    
    def setPortrait(self):
        self.setOrientation('bottom')
    
    def setOrientation(self, orientation = 'bottom'):
        assert orientation in ['top','bottom','left','right'], "Unsupported orientation value given %s orientation" % str(orientation)
    
        degOrientation = 0
        if (orientation == 'top'):
            degOrientation = 180
        elif (orientation == 'right'):
            degOrientation = 90
        elif (orientation == 'left'):
            degOrientation = 270
        elif (orientation == 'bottom'):
            degOrientation = 0
            
        sxString = \
"""
(begin
    (define sensor-manager (get-sensor-manager))
    (send sensor-manager submit-rotation %s)
)
""" % str(degOrientation)
        #self.phone.comment("Change orientation using SX code")
        self.phone.sx(sxString, doNotReport = True)
        
    def getOrientation(self):
        sxString = \
"""
(begin
    (define sensor-manager (get-sensor-manager))
    (set! data (send sensor-manager get-rotation))
)
"""
        self.phone.comment("Get orientation using SX code")
        deg = self.phone.sx(sxString, convertToString=True, doNotReport = True)
        if deg == '270':
            return 'left'
        elif deg == '0':
            return 'bottom'
        elif deg == '90':
            return 'right'
        elif deg == '180':
            return 'top'
        
class Messaging:
    def __init__(self, phone):
        self.phone = phone
                    
    def generateMessage(self, text="Test message", recipient=None, type="sms", state="pending", location="outbox"):
        """
        Generates a message to sql database in the phone via sx call
        """

        assert location in ['inbox', 'outbox', 'drafts'], "Unsupported message folder name given."
        assert type in ['sms', 'sms-email', 'java-smil', 'sms-class2', 'sms-undefined', 'sms-deliv', 'mms', 'mms-read-reply', 'mms-notif',\
            'mms-conf-smil', 'mms-nonconf-smil', 'service-indication', 'service-load', 'vcard', 'vcal', 'email', 'email-deleted',\
            'email-preloaded', 'email-header', 'email-body', 'sms-mwi', 'sms-java', 'sms-ota-prov', 'mms-java-notif', 'mms-java',\
            'sms-mynokia', 'cell-broadcast', 'mms-deliv', 'cell-broadcast-unsupported', 'sms-class0', 'cell-broadcast-class0',\
            'cell-broadcast-class0-unsupported'], "Unsupported message type given."
        assert state in ['unread', 'read', 'downloading-body', 'unsent', 'draft', 'pending', 'sending',\
            'sent', 'sending-failed', 'delivered', 'temp-fail', 'cancel', 'email-deleted'], "Unsupported message state given."

        if recipient == None:
            recipient = self.phone.settings.Main.SIM1PhoneNumber

        sxString = \
"""
(begin

        (define msg-text "%s")
        (define recipient "%s")

        (define msg (create-msg-data))
        (send msg set-message-text msg-text)
        (send msg set-msg-type '%s)
        (send msg set-msg-state '%s)
        (send msg set-location "%s")
        (send msg add-recipient recipient)

        ;; SIM1 = 0
        ;; SIM2 = 1
        (send msg set-sim-id 0)
        (set! query (send msg-db-access save-msg msg on-response-saved))

)
""" % (text, recipient, type, state, location)

        self.phone.comment("Generate a message to sql database in the phone memory via sx call.")
        self.phone.comment("text=%s, recipient=%s, type=%s, state=%s, location=%s" % (text, recipient, type, state, location))

        self.phone.sx(sxString, doNotReport = True)

class Gallery:
    def __init__(self, phone):
        self.phone = phone
        
    def __writeGalleryFile(self,filePath,memory, mediafolder):
        """
            Internal method for writing content
        """        
        
        assert os.path.isfile(filePath), "No file found from path '%s'" % filePath
        
        assert memory == 'main' or (memory == 'memorycard' and self.phone.graniteConnection.phoneHasMemoryCard()), \
            "No memory card in phone while trying to write file to memory card"
        sxPath = ""
        destPath = ""        
        filename = os.path.basename(filePath)
        if memory == 'main':
            sxPath = "file:///usr/_phone/%s" % mediafolder
            destPath = r"C:\sp\usr\_phone\%s" % mediafolder
        elif memory == 'memorycard':
            sxPath = "file:///usr/_memory_card/%s" % mediafolder
            destPath = r"E:\%s" % mediafolder
        else:
            self.phone.fail('Unknown memory mode selected : "%s"' % memory)
                    
        self.phone.graniteConnection.writeFile(filePath, destPath)
       
        sxCode = "(send (get-mds2-manager) file-created-signal \"%s/%s\" 'origin-unspecified)" % (sxPath,filename)
        self.phone.sx(sxCode, doNotReport = True)

    def __removeGalleryFile(self,filename, memory, mediafolder):
        """
            Internal method for removing file from gallery
        """
        galleryFile = ""
        if memory == 'main':            
            galleryFile = r"C:\sp\usr\_phone\%s\%s" % (mediafolder, filename)
        elif memory == 'memorycard':
            galleryFile = r"E:\%s\%s" % (mediafolder, filename)
        else:
            self.phone.fail('Unknown memory mode selected : "%s"' % memory)         
        
        self.phone.graniteConnection.removeFile(galleryFile)    
        
    def writeImage(self,filePath, memory='main'):
        """
        Writes image to gallery folder and updates file info to metadata server
        
        Parameters:
            filePath    Local path for image
            memory      Phone memory where image is saved. Either: "main" or "memorycard"
        
        """     
        self.__writeGalleryFile(filePath, memory, '_my_pictures')
    
        
    def removeImage(self,filename, memory='main'):
        """
            Deletes file from main memory or memory card.
        """
        self.__removeGalleryFile(filename,memory,'_my_pictures')

        

    def writeMusic(self,filePath, memory='main'):
        """
        Writes music file to gallery folder and updates file info to metadata server
        
        Parameters:
            filePath    Local path for music file
            memory      Phone memory where music file is saved. Either: "main" or "memorycard"

        """
        self.__writeGalleryFile(filePath, memory, '_my_music')

    def removeMusic(self,filename, memory='main'):
        """
            Deletes file from main memory or memory card.
        """
        self.__removeGalleryFile(filename,memory,'_my_music')
        
    def writeVideo(self,filePath, memory='main'):
        """
        Writes video file to gallery folder and updates file info to metadata server

        Parameters:
            filePath    Local path for video file
            memory      Phone memory where video file is saved. Either: "main" or "memorycard"
        
        """
        self.__writeGalleryFile(filePath, memory, '_my_videos')

    def removeVideo(self,filename, memory='main'):
        """
            Deletes file from main memory or memory card.
        """
        self.__removeGalleryFile(filename,memory,'_my_video')
        
    def updateMetadata(self,filename):
        """
            Updates data media info to meta data server
        """    
        if filename[:8] != "file:///":
            if filename[:5].lower() == "c:\sp":
                filename = "file://" + filename[5:].replace('\\', '/')
            elif filename[:2].lower() == "e:":
                filename = "file:///usr/_memory_card" + filename[2:].replace('\\', '/')
            else:
                return

        self.phone.comment("Updating metadata for file: " + filename)   
        sxCode = "(send (get-mds2-manager) file-created-signal \"%s\" 'origin-unspecified)" % (filename)
        self.phone.sx(sxCode, doNotReport = True)

    def removeMetadataFromCache(self,filename):
        """
            Remove media meta data from cache
        """    
        if filename[:5].lower() == "c:\sp":
            filename = "file://" + filename[5:].replace('\\', '/')
        elif filename[:2].lower() == "e:":
            filename = "file:///usr/_memory_card" + filename[2:].replace('\\', '/')
        else:
            return

        self.phone.comment("Deleting metadata cache for file: " + filename)
        sxCode = "(send (get-image-manager) remove-from-cache \"%s\")" % filename
        self.phone.sx(sxCode, doNotReport = True)

class Call:
    def __init__(self, phone):
        self.phone = phone
        
    def answer(self):
        sxString = \
"""
(begin
(define incoming-calls (voice-call-manager::get-incoming))
(define waiting-calls (voice-call-manager::get-waiting))
(cond
((pair? incoming-calls)
(stop-vibrator)
(when (not in-voice-call)
(send (get-audio-manager) start-voice-call
(lambda ()
(send (car incoming-calls) accept)
)
)
(set! in-voice-call true)
(listen-proximity-sensor)
(send (get-sensor-manager) set-sensor-activated 'proximity-sensor true)
else
(debug "voice-call-application - warning: received incoming call when in-voice-call == true")
(send (car incoming-calls) accept)
)
)
((pair? waiting-calls)
(send (car waiting-calls) accept)
)
)
)
"""
        return self.phone.sx(sxString, doNotReport = True)       

    def end(self):
        """
            End call via SX
        """
        self.phone.sx("(voice-call-manager::disconnect-all)", doNotReport = True)
    
    def create(self, phonenumber):
        """
            Creates a call using SX code
        """
        sxString = \
"""
(begin
(define my_number "%s")
(launch-service 'place-simple-voice-call
(send (get-app-manager) find-singleton-app (parse-uri-scheme (get-meta-data (send phone-config ref/default 'hub-app-key 'idle) 'uri)))
(define result (send handle get-result)) 
my_number
)
)
""" % str(phonenumber)
        return self.phone.sx(sxString, doNotReport = True)        

class Mtc:
    def __init__(self, phone, middleware):
        self.phone = phone
        self.middleware = middleware

    """
        Set the MTC state:
         - Supported states are: 'NORMAL', 'CHARGING', 'ALARM', 'TEST' and 'LOCAL'.
    """
    def setState(self, state):
        state = state.upper()
        assert state in ['NORMAL','LOCAL','CHARGING', 'ALARM','TEST'], "Invalid state entered: %s" % state

        # send wait message from main FW process to GUI
        core.FW_conf['connection'].sendWaitMessageToGraniteGUI(60, 'Changing MTC state')

        self.middleware.MtcServer.setMtcStateAndVerify(state)

        # clear Granite server so that we won't report about phone reset
        self.phone.clearGraniteServer()

    """
    Get the phone MTC state:
     - Return value is string 'NORMAL', 'CHARGING', 'ALARM', 'TEST' and 'LOCAL'
    """
    def getState(self):
        return self.middleware.MtcServer.getMtcState()

class Adl:
    def __init__(self, phone, middleware):
        self.phone = phone
        self.middleware = middleware
        
    def flashDiff(self, flashFile, console=False):
        # send wait message from main FW process to GUI
        self.phone.comment("Starting ADL Flash with diff file '" + flashFile + "'")
        if not console:
            core.FW_conf['connection'].sendWaitMessageToGraniteGUI(90, 'Flashing diff')
        flashStatus = self.middleware.AdlServer.FlashDiff(flashFile)
        flashStatus = flashStatus[:-1]
        # clear Granite server so that we won't report about phone reset
        if not console:
            self.phone.clearGraniteServer()
        self.phone.comment("ADL Flash completed with status '" + flashStatus + "'")        
        return flashStatus == 'Update successful'
        
class MiddlewareComponents(ServerInterface):
    def __init__(self, phone, cAdapter):
        super(MiddlewareComponents,self).Initialize(cAdapter)
        self.java = JavaComponent(phone)
        self.messaging = Messaging(phone)
        self.gallery = Gallery(phone)
        if core.FW_conf['settings'].TestRun.ExecutionMode == 'Leader':
            from core.leader import LeaderHandler
            self.sensor = LeaderHandler(Sensor(phone))
        else:
            self.sensor = Sensor(phone)
        self.mtc = Mtc(phone, self)
        self.Sensor = self.sensor # Visual C## style naming for legacy use
        self.call = Call(phone)
        self.phone = phone
        self.adl = Adl(phone, self)
        
    
