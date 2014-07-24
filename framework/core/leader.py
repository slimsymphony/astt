import core
import clr
import time, sys, os, types
from types import MethodType

clr.AddReference('LeaderFollowerInterface')
from Nokia.Granite.IPC.Services.LeadFollower import GraniteLeadService
from Nokia.Granite.IPC.Interfaces import *

clr.AddReference('System.Xml.Linq')
from System.Xml.Linq import XElement, XDocument

from datetime import datetime

import linecache
import re
regex = re.compile("[ \t]*class (.*)\(.*uitestcase.UITestCase.*\):.*")

import smtplib
from email.mime.text import MIMEText

step_interval_counter = 1
scripting_methods = ['navigate','jump','select','long','back','exit',\
                                'back','push','clear','backspace',\
                                'sx','expect','notExpect','tryExpect','check',\
                                'swipe','drag','flick','doubleTap',\
                                'selectDate','selectTime','adjustVolume',\
                                'images','texts','pinchOut','pinchIn',\
                                'compareImage','getValue','capture','addMarkerToBlx',\
                                'yapasGarbageCollectorReq','expectReset','waitForReconnection',\
                                'connectUsb','connectSim','connectMemoryCard',\
                                'connectAvPlug','executeHwOperation','setVoltage', \
                                'write', 'input', 'delay', 'createCall', \
                                'releaseCall','answerCall','rejectCall', \
                                'comment']

def needsEvaluation(aString):
    """ check if value needs evaluation in follower end 
    Return tuple:
    (boolean, string) : True, 'self.settings.referencePhone.PhoneNumber'
                        False, None
    """
    tc = core.FW_conf['current_testcase']
    if not tc:
        return False, None

    if not isinstance(aString, basestring):
        return False, None

    settingDict = {}
    toBeEvaluated = core.FW_conf['settings'].TestRun.EvaluateSettings.replace(' ', '')
    toBeEvaluated = toBeEvaluated.replace('\n', '')
    toBeEvaluated = toBeEvaluated.split(',')
    for setting in toBeEvaluated:
        if len(setting) > 0:
            # if pox settings and backend is not available, do not check the evaluation need for it. Otherwise POX backend will be started each time here
            #if setting in ['self.settings.Virtual.PhoneNumber', 'self.settings.Main.VoIPAccount', \
            #               'self.settings.Main.VoIPPassword', 'self.settings.TestRun.POXSIPRegistrarServerUri' ] and not core.FW_conf['connection'].backendAvailable:
            #    continue
            try:
                s = eval('%s' % setting.replace('self.', 'tc.'))
                if len(s) > 0:
                    settingDict[setting] = s
            except Exception as e:
                debug.err('MTBF Settings: %s: No such setting. Check values of "Settings specific to Follower"' % setting)

    ret = False
    for k, v in settingDict.iteritems():
        try:
            if v in aString:
                ret = True
                aString = aString.replace(v, k)
        except:
            debug.err('not able to evaluate parameter %s' % str(aString))
            return False, None
    
    if ret:    
        return ret, aString
    else:
        return False, None
                                
def executeInFollower(string):
    """ Sets the current test step information and executes the command in Follower """
    tc = core.FW_conf['current_testcase']
    if not tc:
        debug.out('No current testcase, cannot execute "%s"in Follower' % string)
        return

    core.FW_conf['leader'].currentTestStep = string
    core.FW_conf['leader'].ExecuteString(string)

def caption_handler(step):
    """ handle captions to video stream and take still images from video stream on defined interval """ 

    global step_interval_counter
    debug.out('caption handler: %s' % step)

    core.FW_conf['leader'].currentTestStep = step  # step which will be sent to follower

    # captions to video
    if core.FW_conf['blackbox'] != None:
        core.FW_conf['blackbox'].videoRecording_SetText(step)

    # if step is not delay or comment, handle still image taking
    if not 'comment' in step and not 'delay' in step and core.FW_conf['settings'].TestRun.VideoStillImageCaptureInterval != 0: 
        if core.FW_conf['settings'].TestRun.VideoStillImageCaptureInterval < 1:
            interval = 10
        else:
            interval = core.FW_conf['settings'].TestRun.VideoStillImageCaptureInterval

        step_interval_counter = step_interval_counter % interval
        if step_interval_counter == 0:
            debug.brf('Step counter hit, take still image..')
            core.FW_conf['current_testcase'].takeVideoStillImage()
            step_interval_counter = 1
        else:
            step_interval_counter += 1

def follower_handler2(func, args):
    """ handles necessary scripting methods to follower """

    debug.out('---- Wrapped: "%s" called with args %s' % (func, args))

    kls = None # save executed class
    fun = None # save executed function

    if func[0] != '_':
        if args:
            step = '%s(%s)' % ( func, args )
        else:
            step = '%s()' % func
            
        if func in scripting_methods:
            caption_handler(step)
            
class LeaderHandler(object):
    """ Wrapper class for sending execution information to follower clients. 
    """

    def __init__(self, wrapped):
        """ initialize wrapper 
        Parameters:
        wrapped (instance)    :     instance of a class to be wrapped
        """
        self.wrapped = wrapped
        self.gls = core.FW_conf['leader']
        assert self.gls != None, "Granite leader service has not been initialized!"

    # check if this is needed. direct calls to class, which have already been wrapped by getattr in testcase class
    #def __call__(self, *args,**kwargs):
    #    debug.brf('direct call to %s' % type(self.wrapped))
    #    func = getattr(self.wrapped, '__call__')
    #    return lambda *args, **kwargs: self._wrap(func, args, kwargs)

    def __getattr__(self, name):
        debug.out('Leaderhandler getattr (%s: %s)' % (self.wrapped.__class__.__name__, name))
        if hasattr(self.wrapped, name):
            func = getattr(self.wrapped, name)
            return lambda *args, **kwargs: self._wrap(func, args, kwargs)
            
        debug.err('LeaderHandler: No member with name %s' % name)
        raise AttributeError(name)
        
    def follower_handler(self, func, args):
        """ handles necessary scripting methods to follower """

        debug.vrb('---- Wrapped: "%s" of "%s" called with args %s' % (func.__name__, self.wrapped.__class__.__name__, args))

        kls = None # save executed class
        fun = None # save executed function

        # if called object, use class name as test step
        if func.__name__ == '__call__':
            kls = self.wrapped.__class__.__name__
            step = '%s%s' % ( self.wrapped.__class__.__name__, args )

        # private methods are not set as test step
        elif func.__name__[0] == '_':
            kls = self.wrapped.__class__.__name__
            fun = func.__name__

        else:
            kls = self.wrapped.__class__.__name__
            fun = func.__name__
            step = '%s.%s%s' % ( self.wrapped.__class__.__name__, func.__name__, args )
            
            if fun in scripting_methods:
                caption_handler(step)
                
        if kls == 'GraniteReferencePhoneInterface':
            if fun in ['createCall', 'sendSms']:
                ret = needsEvaluation(args[0])
                debug.brf(ret)
                if ret and ret[0]:
                    self.gls.ExecuteString('self.referencePhone.%s(%s)' % (fun, ret[1]))
                else:
                    self.gls.ExecuteString("self.referencePhone.%s('%s')" % (fun, args[0]))
                
            elif fun in ['sendMms']:
                debug.brf(args)
                if len(args) > 1:
                    msgType = args[1]
                else:
                    msgType = ''

                ret = needsEvaluation(args[0])
                if ret and ret[0]:
                    self.gls.ExecuteString("self.referencePhone.%s(%s, '%s')" % (fun, ret[1], msgType))
                else:
                    self.gls.ExecuteString("self.referencePhone.%s('%s', '%s')" % (fun, args[0], msgType))

            elif not fun.startswith('_'): # ignore private methods
                self.gls.ExecuteString('self.referencePhone.%s()' % fun)

        elif kls == 'Sensor' and not fun.startswith('_'):
            self.gls.ExecuteString("self.remote.srv.sensor.%s()" % fun)

        elif kls == 'GraniteBlackBoxInterface':
            if fun in ['connectSim', 'connectMemoryCard', 'connectUsb','connectAvPlug','executeHwOperation']:
                self.gls.ExecuteString("self.blackBox.%s('%s')" % (fun, args[0]))
            
        # inputting is handled from virtualkeyboard class, touch press sends will be disabled
        #if kls == "Input":
        #    self.gls.inputParams.Add(args[0])
        #    self.gls.sendTouches = False

        # VirtualKeyboard class is not handled at the moment. To include, wrap it in scripting.py
        # elif kls in ["VirtualKeyboard"]: 
        #    pass
            
        #else:
        #    self.gls.inputParams.Clear()
        #    self.gls.sendTouches = True
        

    # wrapped equals / not equals methods, call wrapped
    def __eq__(self, obj):
        return self.wrapped == obj
        
    def __ne__(self, obj):
        return not self.__eq__(obj)

    def _wrap(self, func, args, kwargs):
        self.follower_handler(func, args)
        if type(func) == MethodType:
            result = func(*args, **kwargs)
        else:
            result = func(self.wrapped, *args, **kwargs)
        return result
