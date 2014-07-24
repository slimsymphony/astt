#!/usr/bin/python
#
#               CorVA audio verification
#               ------------------------
#
#
#
#   Copyright (c) Nokia. All rights reserved.
#
#   Reason:         
#   Reference:      
#   Description:    CorVA audio verification module
#
# ----------------------------------------------------------------------------

GRANITE_IN_USE = True

# if ipy lib is not copied to TestScripts folder, then import via sys.path

# sys.path.append(r"C:\Program Files (x86)\IronPython 2.7.1\Lib")

from System.Diagnostics import Process
import re, datetime, time, os, glob
import sys
import clr

if GRANITE_IN_USE:
    import core
    from core import debug
    from utils.file_utils import filterValidFilename
    from utils.nodeutils import NodeUtils
else: # execution from CTT
    from CapitsuCTT.CommonModules import Support
    from Nokia.Trident.Phone import TestCaseException

clr.AddReference('WaveRecorder.dll')
from WaveRecorder import WaveRecorder

clr.AddReference('WavePlayer.dll')
from WavePlayer import WavePlayer

FAIL_MESSAGE = "AUDIO COMPARISON FAILED."
WARNING = 'Warning'
FAIL_CASE = 'Fail case'
GEN_WARN = 'General warning'
COMMENT = 'Comment'

class CorVA(object):

    def __init__(self, tc, waveInDeviceName=None, channels=1, ref_folder=None):
        """ initializes audio device for audio recording

        Parameters
        waveInDeviceName (str)     :      Device name defined in Granite CorVA settings, e.g "Headset" or "Loudspeaker". Will be mapped to PC audio device
        channels (int)             :      Number of channels to record. Default = 1
        ref_folder (str)           :      Reference audio folder. If not given, default reference_files/audio will be used
        
        """

        self.logging = True
        self._verifyCounter = 0
        
        if GRANITE_IN_USE:
            # Todo: Do checking that audio testing setup exists
            self.corva_on = core.FW_conf['settings'].Multimedia.CorVAEnabled
            self._tc = tc
            self._currentCaseResult = tc.result
            self._tcName = filterValidFilename(tc.tcId)
        else:
            self.corva_on = True
            self.Support = Support()
        
        if GRANITE_IN_USE:
            self.acq_folder = os.path.abspath( os.path.join( core.FW_conf['test_result_dir'],"audio") )
        else:
            self.acq_folder = os.path.normpath(os.path.join(os.getcwd(),"TestScripts/_ExecutionData/captured_audio"))
            
        # create directory for captured audiofiles if it doesn't exist
        if not os.path.isdir(self.acq_folder):
            os.mkdir(self.acq_folder)

        # set the reference data folder
        if ref_folder == None:
            if GRANITE_IN_USE:
                # by default, refence data folder is .\granite\reference_files\audio, if not given in initialization or in setting file
                if core.FW_conf['settings'].Multimedia.ReferenceAudioPath == "":
                    self.ref_folder = os.path.normpath(os.path.join(os.path.abspath(core.FW_conf['startup_path']), '../reference_files/audio'))
                else:
                    self.ref_folder = core.FW_conf['settings'].Multimedia.ReferenceAudioPath
                    # if reference audio folder has been given as absolute path, use it. Otherwise use relative from startup_path
                    if not os.path.isabs(self.ref_folder):
                        self.ref_folder = os.path.normpath(os.path.join(os.path.abspath(core.FW_conf['startup_path']), self.ref_folder))
            else:
                self.ref_folder = os.path.join(os.getcwd(),"TestScripts/TestData/reference_audio")

        if GRANITE_IN_USE:
            self._corva_path = os.path.normpath(os.path.join(os.path.abspath(core.FW_conf['startup_path']), 'dlls/corva/'))
            self._corva_exe = os.path.normpath(os.path.join(self._corva_path, 'CorVA.exe'))
        else:
            self._corva_exe = os.path.normpath(os.path.join(os.getcwd(), 'TestScripts/M3WLib/corva/CorVA.exe'))

        if GRANITE_IN_USE:
            self.audio_testing_config = dict(

                mode = int(core.FW_conf['settings'].Multimedia.Mode),
                frame_size = int(core.FW_conf['settings'].Multimedia.Framesize),
                threshold = int(core.FW_conf['settings'].Multimedia.Threshold),
                noise_level = float(core.FW_conf['settings'].Multimedia.NoiseLevel),
                start_channel= int(core.FW_conf['settings'].Multimedia.StartChannel),

                rec_time = int(core.FW_conf['settings'].Multimedia.DefaultAudioRecordingTime),
                rec_file = None,
                rec = False,      # if true, record always new file with compare_audio (with given rec file name)
                
                timepairs = (),

                fail_mode = core.FW_conf['settings'].Multimedia.DefaultCorVAActionOnFail,
                save_passed_recordings = core.FW_conf['settings'].Multimedia.SavePassedRecordings,
                
            )
        else: #read from settings file
            self.audio_testing_config = dict(

                mode = self.Support.CorvaMode,
                frame_size = self.Support.CorvaFramesize,
                threshold = self.Support.Threshold,
                noise_level = self.Support.CorvaNoiselevel,
                start_channel= self.Support.CorvaStartChannel,

                rec_time = self.Support.DefaultAudioRecordingTime,
                rec_file = None,
                rec = False,      # if true, record always new file with compare_audio (with given rec file name)

                timepairs = (),  # timepairs to ignore parts of the reference file
                
                fail_mode = self.Support.DefaultActionOnFail, # fail the case
                save_passed_recordings = self.Support.SavePassedRecordings
                
            )
        
        # name of this instance/recorder
        if waveInDeviceName == None:
            self.name = 'default_recorder'
        else:
            self.name = waveInDeviceName

        self.device = None

        # if corva is not enabled, don't try to open recording audio device. Exception is rec mode
        self._write_log('corva enabler mode: %s' % self.corva_on)
        if not( self.corva_on or self.corva_on == 'Rec' ):
            self._write_log("corva not in use, not opening recording device")
            return
            
        # initialize recorder for this CorVA instance
        try:
            device = None
            if waveInDeviceName == None:
                self._write_log("Opening default wave device.." )
                self.waveRecorder = WaveRecorder()
            else:
                if GRANITE_IN_USE:
                    device = getattr(core.FW_conf['settings'].Multimedia, waveInDeviceName, None)
                else:
                    device = eval('self.Support.' + waveInDeviceName)
                    
                self._write_log("Opening wavein device %s '%s'.." % (waveInDeviceName, device))
                if channels == 1: self.waveRecorder = WaveRecorder(device)
                else: self.waveRecorder = WaveRecorder(device, 48000, channels, 16)

                self.device = device
                core.FW_conf['audio_devices'].append(self)
                
        except Exception, e:
            # if audio device cannot be opened, give warning to TC and GUI and disable corva (cases won't fail because of corva initialization)
            
            if device == None:
                msg = "Tried to open default wave in device. Error: %s" % (e)
            else:
                msg = "tried to open device with string \'%s\'. Error: %s" % (device, e)

            self._write_log(msg)

            if GRANITE_IN_USE:
                self._tc.warn(msg)
                self._currentCaseResult.addGeneralWarning(msg)
                self.corva_on = False
                self.waveRecorder = None
                # self.audio_testing_config["fail_mode"] = WARNING
            else:
                raise TestCaseException(msg);

    def __del__(self):
        """ if GC finds this, stop recording properly """
        if self.waveRecorder:
            self.dispose()

    def dispose(self):
        """ Method to free the audio device from this instance. 
            Will be called by Granite framework on teardown, if audio recorder have not been disposed
        """

        if self.waveRecorder:
            debug.brf('Disposing audio recorder %s (%s)' % (self.name, self.device))
            self.waveRecorder.Dispose()
            core.FW_conf['audio_devices'].remove(self)
            self.waveRecorder = None
        
    def _run_command(self, args, wait=True):
        # todo: if dll calling is not ready, do exception catching + failing
        
        p = Process()
        p.StartInfo.FileName = args[0]
        p.StartInfo.Arguments = " ".join(args[1:])
        self._write_log("cwd: %s" % os.getcwd() )
        if GRANITE_IN_USE:
            p.StartInfo.WorkingDirectory = self._corva_path
        else:            
            p.StartInfo.WorkingDirectory = os.getcwd() + "/TestScripts/M3WLib/CorVA"
        
        p.StartInfo.UseShellExecute = True
        
        # workaround for corva failed frame plotting, change working directory 
##        try:
##            cwd = os.getcwd()
##            os.chdir(self._corva_path)
##            self._write_log("changed wd: %s" % os.getcwd() )
##        except:
##            self._write_log("Could not change working directory. Plotting might not work." )
##            
        p.Start()
        
        if wait:
            p.WaitForExit()
            return p.ExitCode

##        os.chdir(cwd)
##        self._write_log("changed tp original wd: %s" % os.getcwd() )
        
    def _clear_result_files( self, prefix ):
        """ clear any existing result files found with prefix
        """

        self._write_log("clear result files with prefix %s" % prefix)

        for file in glob.glob('%s\%s*' % (self.acq_folder, prefix) ):
            self._write_log( "Delete %s" % file )
            try:
                os.remove(file)
            except os.error:
                self._write_log('Unable to delete corva result files: %s' % str(os.error))

    def _write_log( self, message ):
        """ output debug log from corva if logging enabled """

        if self.logging != True: return

        if GRANITE_IN_USE:
            self._tc.comment("corva: %s" % str(message))
        else: # CTT, print on the output log
            print "%s: %s" % (self.__class__.__name__, str(message))
        
        # todo: add logging to file

    def _getNewRecFilename(self):
        """ return a filename for new recording 
            TODO: define filter to ignore certain files (e.g. ".wav")
        """
        now = datetime.datetime.now()
        sec = int(now.second)
        min = int(now.minute)
        hour = int(now.hour)
        day = int(now.day)
        month = int(now.month)
        year = int(now.year)
            
        self._verifyCounter += 1
        if GRANITE_IN_USE:
            return "%s_%s_%d%02d%02d_%02d%02d_%02d_%s_.wav" % (self.name, self._tcName, year, month, day, hour, min, sec, self._verifyCounter)
        else:
            return "%s_%d%02d%02d_%02d%02d_%02d_.wav" % (self.name, year, month, day, hour, min, sec)
            
    def _compare (self, ref, rec, params={} ):
        """ private compare 
        """

        cmd = [self._corva_exe, \
            str(params["mode"]), \
            self.ref_folder + "/" + ref, \
            self.acq_folder + "/" + rec, \
            str(params["frame_size"]), \
            str(params["threshold"])]
        
        if params["mode"] >= 3:
            cmd.append( str(params["noise_level"]) )
        cmd.append( str(params["start_channel"]) )

        for t in params['timepairs']:
            cmd.append( str(t) )
        
        for i in cmd:
            sys.stdout.write("%s " % i)
        print " "
            
        self._write_log(cmd)
        process = None
        compResult = -1 # set comparison result as fail by default

        msg = "'audio compare %s <> %s'" % (ref, rec)
        if GRANITE_IN_USE:
            debug.out(msg)
        else:
            self._write_log(msg)

        try:
            # compResult = subprocess.call(cmd, stdout = fnull, stderr = fnull)
            compResult = self._run_command(cmd)
        
        except WindowsError, err:
            self._write_log('Unable to start process: %s' % str(err))
            if GRANITE_IN_USE:
                self._tc.fail("Error with audio compare: Cannot execute CorVA.")
            else: # ctt
                raise TestCaseException("Error with CorVA audio compare: Cannot execute CorVA.")
            

        # read return code from start. (not needed, don't wait for recording to start
        # returnCode = process.poll()

        self._write_log("audio comparison result: %s" % compResult)

        if compResult != 0:
            return False
        else:
            return True

    def startRecording(self, filename = None, time = None ):
        """ record audio file
            starts background process for recording (does not wait for return)
            filename = name of the file (will be recorded in acq_folder)
            time = length of the recording. if not given, recording will be stopped after default timeout (CTT options)
                   if time is given, recording will not return until timeout expires
            
        """

        if not( self.corva_on or self.corva_on == 'Rec' ):
            self._write_log("corva not in use, skipping recording")
            return

        if filename == None:
            filename = self._getNewRecFilename()

        if time == None:
            self._write_log("audio recording started to %s" % self.acq_folder + "\\" + filename)
                
        else:
            self._write_log("audio record to %s for %s seconds" % (self.acq_folder + "\\" + filename, time))
            
        if GRANITE_IN_USE:
            self.waveRecorder.startRecording(self.acq_folder + "/" + filename, int(core.FW_conf['settings'].Multimedia.MaxRecordTime) )
        else:
            self.waveRecorder.startRecording(self.acq_folder + "/" + filename, int(self.Support.MaxRecordTime) )
        
        if time:
            self.stopRecording(time)
        
        self.audio_testing_config["rec_file"] = filename
        
        return filename
        
    def stopRecording(self, timeout = 0):
        """ stop ongoing recording
            timeout = timeout in seconds before stopping recording.
                      function will not return until timeout expires.
        """
        
        if not( self.corva_on or self.corva_on == 'Rec' ):
            self._write_log("corva not in use, skipping recording (stop)")
            return

        if timeout == 0:
            self._write_log("stop_recording now.")
        else:
            self._write_log("stop_recording. timeout: %s " % timeout)
            
        self.waveRecorder.StopRecording(timeout * 1000)

    def compareAudio(self, ref = None, parameters={} ):
        """ compare audio
            ref = file to compare against
            param = dict of audio comparision parameters:
                    mode, rame_size, threshold, noise_level, start_channel, rec_time,
                    rec_file, rec
                    usage example: self.Earpiece.compareAudio("foo.wav", {'rec_time': 5} )
            return in DEFAULT mode no return, fail executed TC.
                   for modes COMMENT, WARNING and GEN_WARN True if compare successful, otherwise False
        """

        self._write_log("Starting comparison..")
        
        if not self.corva_on or self.corva_on == 'Rec':
            self._write_log("Compare: CorVA not enabled, return.")
            return
        
        # merge given parameters to audio_testing_config, do not change default settings
        params = self.audio_testing_config.copy()
        params.update(parameters)
        
        self._write_log("Fail mode is: %s" % params["fail_mode"])
        

        if ref == None:
            self._write_log("Error with audio compare: no reference wav given.")
            if GRANITE_IN_USE:
                self._tc.fail("Error with audio compare: no reference wav given.")
            else: # ctt
                raise TestCaseException("Error with CorVA audio compare: no reference wav given.")
                
        refPath = self.ref_folder + "/" + ref
        if not(os.path.isfile(refPath)):
            self._write_log("Error with audio compare: reference wav %s does not exist." % refPath)
            if GRANITE_IN_USE:
                self._tc.fail("Error with audio compare: reference wav %s does not exist." % refPath)
            else: # ctt
                raise TestCaseException("Error with audio compare: reference wav %s does not exist." % refPath)

                
        # if rec file not given, record to default_rec_file_name
        if params["rec_file"] == None:
            rec = self._getNewRecFilename()
        else:
            rec = params["rec_file"]

        
        fn_prefix = re.sub(r'\.wav$', '',rec)
        
        # if rec_file to compare against is given, do not clear the result files yet.
        if params["rec_file"] == None:  
            self._clear_result_files(fn_prefix)

        # if recording is needed
        if params["rec_file"] == None \
            or params["rec"]:
            self.startRecording(rec, params["rec_time"])
            
        result = self._compare(ref, rec, params)

        if result == True:
            self._write_log("AUDIO VERIFY PASSED")

            if not params['save_passed_recordings'] in ('True', True):
                self._clear_result_files(fn_prefix)
                
            if GRANITE_IN_USE:
                self._tc.comment("Audio verify %s <-> %s passed." % (ref, rec))
                
            return True

        else:

            self._write_log("Audio verify FAILED")

            # put comments in Granite logs
            if GRANITE_IN_USE: 
                oAudioRes = NodeUtils('audio_test_result', True)
                oAudioRes.setAttribute('comment', 'corva logs, plotfiles and recorded audiofiles')
                # TODO: put information is the log from main or remote
                # oAudioRes.setAttribute('corva_log', self.serverMode and 'remote' or 'main')

                oRefAudio = NodeUtils('reference_audio', True)
                oRefAudio.setAttribute('name', refPath)
                oAudioRes.append(oRefAudio)

                # todo: add check if there's more than 1 recording or corvalog

                recordings = glob.glob('%s\%s*.wav' % (self.acq_folder, fn_prefix) )
                for file in recordings:
                    self._write_log( "Adding recorded audio file path %s to xml result. index %s" % (file,recordings.index(file) ) )
                    # oRecFile = NodeUtils('recorded_audio%s' % recordings.index(file), True)
                    oRecFile = NodeUtils('recorded_audio', True)
                    oRecFile.setAttribute('name', file)
                    oAudioRes.append(oRecFile)


                corvaLoglink = ''
                corvaLogs = glob.glob('%s\%s*.log' % (self.acq_folder, fn_prefix) )
                for file in corvaLogs:
                    self._write_log( "Adding Corva log path %s to xml result" % file )
                    corvaLoglink = file
                    # oCorvaLog = NodeUtils('corva_log%s' % corvaLogs.index(file), True)
                    oCorvaLog = NodeUtils('corva_log', True)
                    oCorvaLog.setAttribute('name', file)
                    oAudioRes.append(oCorvaLog)

                # sometimes image plotting might fail
                img_files = glob.glob('%s\%s*.png' % (self.acq_folder, fn_prefix) )
                if len(img_files) < 1:
                    self._write_log("Image files not found: %s*.png" % fn_prefix)
                    oAplot = NodeUtils('image', True)
                    oAplot.setAttribute('error', 'failed to plot image!')
                    oAudioRes.append(oAplot)

                for file in img_files:
                    self._write_log( "Adding plotted image path %s to xml result. index %s" % (file, img_files.index(file) ) )
                    # oAplot = NodeUtils('image%s' % img_files.index(file), True)
                    oAplot = NodeUtils('image', True)
                    oAplot.setAttribute('name', file)
                    oAudioRes.append(oAplot)

                self._currentCaseResult.addBlock(oAudioRes)

            message = FAIL_MESSAGE + (" Compared %s <-> %s") % (ref, rec)
            # message = '<a href=%s link type:"text/plain" >CorVa log File</a><br /><br />' % corvaLoglink

            if params['fail_mode'] == FAIL_CASE:  # fail the case
                if GRANITE_IN_USE:
                    self._tc.fail(message)
                else:
                    raise TestCaseException(message)
            elif params['fail_mode'] == WARNING:  # put warning to TC
                if GRANITE_IN_USE:
                    self._tc.warn(message)
                else: #todo: add ctt log warning
                    raise TestCaseException(message)
            elif params['fail_mode'] == GEN_WARN: # warning to GUI
                if GRANITE_IN_USE:
                    self._currentCaseResult.addGeneralWarning(message)
                else: #todo: add ctt log warning
                    raise TestCaseException(message)
            elif params['fail_mode'] == COMMENT:  # no fail, just comment
                if GRANITE_IN_USE:
                    self._tc.comment(message)
                else: #todo: add ctt log comment
                    self._write_log("Audio verify failed. Not failing the case.")
                    return False
                    
            else:
                if GRANITE_IN_USE: 
                    self._tc.fail("Audio testing mode not defined. Failed comparison %s <-> %s") % (ref, rec)
                else:
                    raise TestCaseException(message)

            return False

class AudioPlayer(object):
    """ Class for playing audio via connected audiodevice """

    def __init__(self, tc, waveOutDeviceName, audioFileLocation=None):
        """ initializes audio device for audio playback 
        Parameters
        waveOutDeviceName (str)     :      Device name defined in Granite CorVA settings, e.g "FMTX"
        audioFileLocation (str)     :      Location of audio files to be played. Defaults to None, which means that test_content folder will be used
        
        """
        self._tc = tc
        self._currentCaseResult = tc.result
        self.logging = True
        
        # name of this instance/recorder
        self.name = waveOutDeviceName
        self.device = None
        
        if audioFileLocation == None:
            if core.FW_conf['settings'].Multimedia.AudioTestDataFolder == "": # by default, use test_content folder to read data from
                self.dataLocation = os.path.normpath(os.path.join(os.path.abspath(core.FW_conf['startup_path']), '../test_content'))
            else:
                self.dataLocation = core.FW_conf['settings'].Multimedia.AudioTestDataFolder
                if not os.path.isabs(self.dataLocation):
                    self.dataLocation = os.path.normpath(os.path.join(os.path.abspath(core.FW_conf['startup_path']), self.dataLocation))
        else:
            self.dataLocation = audioFileLocation

        # initialize recorder for this CorVA instance
        try:
            if GRANITE_IN_USE:
                device = getattr(core.FW_conf['settings'].Multimedia, waveOutDeviceName, None)
                self._write_log("Opening waveout device %s '%s'.." % (waveOutDeviceName, device))
                self.player = WavePlayer(device)
                # register this instance to Granite framework
                self.device = device
                core.FW_conf['audio_devices'].append(self)
                
            else:
                raise TestCaseException('Playback not supported with CTT');
                
        except Exception, e:
            # if audio device cannot be opened, give warning to TC and GUI and disable corva (cases won't fail because of corva initialization)
            self.player = None
            msg = "Could not open audio device %s for playback. Error: %s" % (waveOutDeviceName, e)
            self._tc.comment(msg)
            self._write_log(msg)
            #self._tc.fail(msg)
            self._currentCaseResult.addGeneralWarning(msg)

    def __del__(self):
        """ if GC finds the object, dispose wave device properly """

        if self.player:
            self.dispose()

    def dispose(self):
        """ Method to free the audio device from this instance. 
            Will be called by Granite framework on teardown, if audio player have not been disposed
        """

        if self.player:
            debug.brf('Disposing audio player %s (%s)' % (self.name, self.device))
            if self.status():
                self.stop()
            self.player.Dispose()
            core.FW_conf['audio_devices'].remove(self)
            self.player = None

    def status(self):
        """ return boolean true if playback is on, false if not. 
            Note: playing flag on will be only set false after StopPlayback, not in the end of audio.
        """
        return self.player.playing;

    def play(self, audioFile):
        """ Starts playing back given audiofile 

        Params 
        audioFile (str)     :      file name to play. If no path given, test_content folder will be used

        """

        if not self.player:
            self._tc.comment('Cannot start playback, player has not been initialized properly')
            return

        # stop playback
        if self.status():
            self.stop()

        # check that is given audioFile a path to file
        if os.path.split(audioFile)[0] != "":
            file = audioFile
        else:
            file = os.path.join(self.dataLocation, audioFile)

        try:
            self.player.StartPlayback(file)
            self._tc.comment('Audio file %s playback started on %s (%s)' % (file, self.name, self.device))
        except Exception, e:
            msg = "Could not start file %s audio playback on device %s (%s) for playback. Error: %s" % (file, self.name, self.device, e)
            self._tc.comment(msg)
            self._write_log(msg)
            self._tc.warn(msg)
            self._currentCaseResult.addGeneralWarning(msg)

    def stop(self):
        """ Stops the audio playback """

        if not self.player:
            self._tc.comment('Cannot stop playback, player has not been initialized properly')
            return

        try:
            self.player.StopPlayback()
            self._tc.comment('Audio playback stopped on %s (%s)' % (self.name, self.device))
        except Exception, e:
            msg = "Could not stop audio playback on device %s (%s) for playback. Error: %s" % (self.name, self.device, e)
            self._tc.comment(msg)
            self._write_log(msg)
            self._tc.warn(msg)
            self._currentCaseResult.addGeneralWarning(msg)

    def _write_log( self, message ):
        """ output debug log from audioplayer if logging enabled """

        if self.logging != True: return

        if GRANITE_IN_USE:
            self._tc.comment("corva audioplayer: %s" % str(message))
        else: # CTT, print on the output log
            print "%s: %s" % (self.__class__.__name__, str(message))
