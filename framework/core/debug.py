# ============================================================================
#
#
#                                Debug Module
#                        ------------------------------
#                        Granite SW module - Python
#
#
# Copyright (c) Nokia. All rights reserved.
#
# ----------------------------------------------------------------------------

# ============================================================================
#   1   ABSTRACT
#
#   1.1 Module type
#
#       Test utility
#
#   1.2 Description
#
#       This module implements a replacement for standard out.
#
#   1.3 Notes
#
#       Code indentation rule: 4 spaces for one indentation level, no tabs!
#       Recommended maximum line length is 79 characters.
#       (see more from: http://www.python.org/doc/essays/styleguide.html)
# ----------------------------------------------------------------------------

# ============================================================================
#   2   CONTENT
#
#       1   ABSTRACT
#       1.1 Module type
#       1.2 Description
#       1.3 Notes
#
#       2   CONTENT
#
#       3   MODULE CODE
#       3.1 DebugStream class
#       3.2 Debug functions
#       3.n Self test
# ----------------------------------------------------------------------------


# ============================================================================
#   3   MODULE CODE
# ----------------------------------------------------------------------------

# Python library module imports
import types, sys, traceback, os, time, clr, core
from System import GC
from System.Diagnostics import Process

import debug

clr.AddReference("log4net")
clr.AddReference("System")
from log4net import Config, GlobalContext, ILog, LogManager, Appender, Filter, Core, Layout
from log4net.Config import XmlConfigurator
from System.IO import Directory, FileInfo
from System.Net import IPAddress
GlobalContext.Properties["GraniteLoggingBase"] = Directory.GetCurrentDirectory();
XmlConfigurator.Configure(FileInfo("..\\settings\\GraniteLogSettings.xml"));
log = LogManager.GetLogger("FrameworkLogger")

# ============================================================================
#   3.1     DebugStream class
# ----------------------------------------------------------------------------
class DebugStream:

    def __init__(self, prefix):
        self.prefix = prefix + ' '
        self.line = ''
        self.active = 0
        self.log = log

    def write(self, text):
        if self.active:
            if type(text) == types.UnicodeType:
                try:
                    text = text.encode('latin-1')
                except UnicodeError, e:
                    text = repr(text)
            self.line += text
            
            debug.orig_stdout.write(self.prefix)
            fname = ''
            if debug.level > 2:
                fname = self._funcName()
            if fname:
                debug.orig_stdout.write(fname + ': ')
            if self.line:            
                if self.line[-1] != '\n':
                    self.line = self.line + '\n'
                debug.orig_stdout.write(self.line)

            # make sure that DebugStream object has flush available
            if getattr(debug.orig_stdout, 'flush', None):
                debug.orig_stdout.flush()

            self.line = ''

            if fname:
                fname = fname + ': ' 
                
            if self.prefix == '-':
                self.log.Debug(self.prefix + " " + fname + text)
            elif self.prefix == '!':
                self.log.Error(self.prefix + " " + fname + text)
            elif self.prefix == '+' or self.prefix == '#':
                self.log.Info(self.prefix + " " + fname + text)
            else:
                self.log.Debug(self.prefix + " " + fname + text)

    def __call__(self, text):
        if self.active:
            if not type(text) in [type(''), type(u'')]:
                text = repr(text)
            self.write(text)

    def setActive(self, status):
        self.active = status

    def _funcName(self):

        # Find out call source
        try:
            raise Exception
        except:
            # Go back three steps in the stack trace
            try:
                f = sys.exc_traceback.tb_frame
                i = 0
                while f is not None and i < 3:
                    f = f.f_back
                    i += 1

                if f is not None:
                    fname = f.f_code.co_name
                    del f
                    if fname == '?':
                        fname = '(main)'
                else:
                    fname = '(main)'
            except:
                fname = '(main)'

            return fname
    
# ============================================================================
#   3.2     Debug functions
# ----------------------------------------------------------------------------

def init(orig_stdout):
    debug.orig_stdout = orig_stdout
    debug.brf = DebugStream('-')
    debug.out = DebugStream('+')
    debug.vrb = DebugStream('#')
    debug.err = DebugStream('!')
    debug.setLevel(4)

def exception(exception=None):
    if exception:
        debug.err(str(exception))
    traceback.print_exc()

def setLevel(level):
    """ Set debug level.

        0: disabled
        1: errors only
        2: brief
        3: normal
        4: verbose
    """
    debug.level = level
    debug.vrb.setActive(level >= 4 and 1 or 0)
    debug.out.setActive(level >= 3 and 1 or 0)
    debug.brf.setActive(level >= 2 and 1 or 0)
    debug.err.setActive(level >= 1 and 1 or 0)

def dumpMemoryUsage():
    """ Dumps memory usage in memory_log.txt-file
    """
    if debug.level < 3:
        return
        
    # get current process handle
    p = Process()
    currentProcess = p.GetCurrentProcess()

    if os.path.isfile('memory_log.txt'):
        memoryDumpFile = open('memory_log.txt','a')
    else:
        memoryDumpFile = open('memory_log.txt','w')
        
        # write header line
        memoryDumpFile.write(";".join(['Time', 'Private', 'Non paged (sys)', 'Paged (sys)', 'Paged', 'Peak paged', 'Virtual', 'Peak virtual', 'Working set', 'Peak working set']) + "\n")

    # write memory information
    memoryDumpFile.write(";".join([time.asctime(),
                         str(currentProcess.PrivateMemorySize64),
                         str(currentProcess.NonpagedSystemMemorySize64),
                         str(currentProcess.PagedSystemMemorySize64),
                         str(currentProcess.PagedMemorySize64),
                         str(currentProcess.PeakPagedMemorySize64),
                         str(currentProcess.VirtualMemorySize64),
                         str(currentProcess.PeakVirtualMemorySize64),
                         str(currentProcess.WorkingSet64),
                         str(currentProcess.PeakWorkingSet64)]) + "\n")
                         
    memoryDumpFile.close()
    
    # dispose process handles
    p.Dispose()
    currentProcess.Dispose()

# ============================================================================
#   3.n     Self test
# ----------------------------------------------------------------------------
if __name__ == '__main__':

    debug.init(sys.stdout)
    sys.stdout = debug.out
    sys.stderr = debug.err

    debug.brf('brief')
    debug.out('normal')
    debug.vrb('verbose')
    debug.err('error')
    sys.stderr.write('Error message\n')
    try:
        1/0
    except Exception, e:
        debug.exception(e)

def addGuiAppender(remotePort = 31337):
    """ Create and add UDP appender for GUI
    """
    appender = Appender.UdpAppender()
    appender.Name = 'GuiUdpAppender'
    debugFilter = Filter.LevelMatchFilter()
    debugFilter.LevelToMatch = Core.Level.Debug
    debugFilter.AcceptOnMatch = True

    errorFilter = Filter.LevelMatchFilter()
    errorFilter.LevelToMatch = Core.Level.Error
    errorFilter.AcceptOnMatch = True
            
    appender.AddFilter(debugFilter)
    appender.AddFilter(errorFilter)
            
    layout = Layout.XmlLayout()
    layout.ActivateOptions()

    appender.Layout = layout;
    appender.RemoteAddress = IPAddress.Parse("127.0.0.1")
    appender.RemotePort = remotePort

    appender.ActivateOptions()
    log.Logger.AddAppender(appender)
