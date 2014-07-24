# ============================================================================
#
#
#                          Phone file Dumper
#                        -----------------------
#
#
# Copyright (c) Nokia. All rights reserved.
# ============================================================================

# Python library module imports
import clr

clr.AddReference('Nokia.Trident.Phone')

from Nokia.Trident.Phone import PmdDecoder

from os import makedirs
from os.path import join, split, isdir, isfile
from System import DateTime

from interfaces.connection import GraniteConnection

import core
from interfaces.connection_interface import ConnectionException
from utils.nodeutils import NodeUtils
from utils.file_utils import filterValidFilename

##
## 3.1 CommonFileDumper class
##
# ============================================================================
class CommonFileDumper:
# ----------------------------------------------------------------------------
    def __init__(self, phone):
        self.phone = phone
        self.phoneName = self.phone.getName() != 'Main' and 'remote phone' or 'phone'
        self.prevDumpFiles = []
        self.targetDumpPath = 'C:\\predefgallery'
        self.xFileDecoder = PmdDecoder()
        #Use already loaded PMD file for XFile decoding
        self.xFileDecoder.PmdFilePath = phone.graniteConnection._GraniteConnection__pmdFilePath
        self.xFileDecoder.PmdLoader = phone.graniteConnection.PMDLoader
                        
    def extractDumpFiles(self, doNotFailCase = None):
        """ Extract dump file(s) from the phone.
            
            If doNotFailCase is True testcase is not failed. This is for intentionally created X-file testing.
        """
        newDumpFiles = []

        for targetFileName, localAbsPath in self.getNewDumpFiles():
            try:
                self.phone.readFile(\
                    join(self.targetDumpPath, targetFileName), localAbsPath)
            except Exception, e:
                debug.err('Extracting file %r from the phone '
                          'NOT successful: %s.' % (targetFileName, e))
            else:
                newDumpFiles.append(localAbsPath)
                debug.out('Extracting file %r from the phone '
                          'successful.' % targetFileName)
                
        #File decoding is done on if files exist
        if newDumpFiles:
            #Fix me: Do not automatically decode XFiles, because can't be sure if correct PMD file is used for decoding!
            #self.decodeXFile(newDumpFiles)
            if isinstance(newDumpFiles, list):
                self.addXFilesToReport(newDumpFiles)

            # fail test case only on main phone
            if not doNotFailCase and self.phoneName == 'phone':
                self.phone.result.addFailure('X-Files generated during testcase execution')
            else:
                self.phone.warn('X-Files found from the %s' % self.phoneName)
       
        return newDumpFiles

    def removeDumpFiles(self):
        """ Remove dump file(s) from the phone.
        """

        self.prevDumpFiles = []
        
        try:
            targetFileNames = self.phone.getFolderContent(\
                self.targetDumpPath + '\\*.xf')[0]
        except Exception, err:
            debug.out('Querying x-files from the %s failed: (%s)' % (self.phoneName, str(err)))
        else:            
            for targetDumpFile in targetFileNames:
                try:
                    self.phone.removeFile(\
                        join(self.targetDumpPath, targetDumpFile), forced = True)
                except Exception, e:
                    if targetDumpFile not in self.prevDumpFiles:
                        self.prevDumpFiles.append(targetDumpFile)
                        
                    debug.err('Removing file %r from the phone '
                              'NOT successful: %s.' % (targetDumpFile, e))
                else:
                    if targetDumpFile in self.prevDumpFiles:
                        self.prevDumpFiles.remove(targetFileName)            
                    debug.out('Removing file %r from the phone '
                              'successful.' % targetDumpFile)

    def getNewDumpFiles(self):
        """Returns new dump files by comparing file lists from current
           and previous query.
        """
        newDumpFiles = []

        try:
            targetFileNames = self.phone.getFolderContent(\
                self.targetDumpPath + '\\*.xf')[0]
        except Exception, err:
            debug.out('Querying x-files from the %s failed: (%s)' % (self.phoneName, str(err)))
        else:        
            for targetFileName in targetFileNames:
                if targetFileName not in self.prevDumpFiles:
                    localAbsPath = join(self.getLocalDumpPath(), targetFileName)
                    newDumpFiles.append((targetFileName, localAbsPath))
                    self.prevDumpFiles.append(targetFileName)

        return newDumpFiles

    def getLocalDumpPath(self):
        """ Get actual local dump path.
            Override this method if local dump path is not suitable.
        """
        localDumpPath = join(core.FW_conf['test_result_dir'],
                             'x_files',
                             self.phone.getName() != 'Main' and self.phone.getName() or '',
                             DateTime.Now.ToString("yyyyMMddHHmmss") + '_' + filterValidFilename(self.phone.currentTcId))
        #Fix me: repeat_index is not working correctly in this case when GUI is in use  +'_' + core.FW_conf['repeat_index'].ToString())
        
        # create folder if it doesn't exist.
        if not isdir(localDumpPath):
            makedirs(localDumpPath)
        
        return localDumpPath

    def decodeXFile(self, xFileName):
        """ decode extracted dumpfiles to ascii

        """
        debug.brf('DO NOT USE automatic XFile decoding in Granite!!!')
        self.addXFilesToReport(xFileName)
        for xFileName in xFileName:
            if isfile(xFileName):
                outputFile = xFileName.rstrip('.XF') + '.txt'
                f = open(outputFile, 'w')
                f.write(self.xFileDecoder.DecodeXFile(xFileName))
                f.close()

    def addXFilesToReport(self, xFileName):
        """ Adds created and decoded XFiles to Granite test report
            
            Parameters: Xfilename which have been extracted from phone to harddrive

        """
        oDumpFiles = NodeUtils('dump_files', True)
        oDumpFiles.setAttribute('comment', 'saved to ' + join(core.FW_conf['test_result_dir'], 'x_files'))

        for xFileName in xFileName:
            oXFile = NodeUtils('x_file', True)
            xFileName = xFileName.replace(join(core.FW_conf['test_result_dir'], 'x_files'),'')
            oXFile.setAttribute('mulder', xFileName)
            #oXFile.setAttribute('reset_reason', 'RESET')
            oDumpFiles.append(oXFile)

        self.phone.result.addBlock(oDumpFiles)
