# -*- coding: ascii -*-
# ============================================================================
#
#
# %full_filespec:   file_utils.py
#                   ----------------------------------------------------------
#                   Granite Python Module
#
#
# Copyright (c)     Nokia. All rights reserved.
#
# ----------------------------------------------------------------------------
"""Contains string filtering and converting methods and functions getting
   and checking directories.
"""

import os, re, sys, traceback
from shutil import rmtree, copy2
from zipfile import ZipFile, ZIP_DEFLATED

import clr
clr.AddReference('System')
import System.Environment
from System.Environment import GetFolderPath

# Path max lengh in MS Windows is 255, redused to 250 to be on safe side.
PATH_MAX_LEN = 250

# Regular expression for filtering illegal characters from filename.
rIllegalChar = re.compile(r'[\x00-\x1f\\/:*?"<>|.]')

class FileUtilsException(Exception):
    """Exception class for test report generation exceptions with or without
       traceback info.
    """
    def __init__(self, errorString = None):
        Exception.__init__(self)
        if errorString:
            self._errorString = errorString
        else:
            et, ev, tb = sys.exc_info()
            self._errorString = \
                            ''.join(traceback.format_exception(et, ev, tb))

    def __unicode__(self):
        return 'FileUtilsException: %s' % self._errorString

def filterValidFilename(name):
    """Filter out such characters which are not suitable in file name.
    """
    name = rIllegalChar.sub('_', name)
    name = name.strip()
    name = name.replace(' ', '_')
    return name

def checkValidPath(folderPath, maxRelDepth = 50):
    """Check validity of path depth so that operating system dependent
        path max length is not exceeded.
    """
    return len(folderPath) <= PATH_MAX_LEN - maxRelDepth and True or False    

def filterValidPath(filePath, minFileLen = 8):
    """Filter out such characters which are not suitable in file name
        and split path if its length exceeds PATH_MAX_LEN.
    """
    index, midfix = 1, '__'
    dirName = os.path.normpath(os.path.dirname(filePath))

    assert len(os.path.join(dirName, 'X' * minFileLen)) <= PATH_MAX_LEN, \
                        "Path depth too high for successful file operations!'"

    fileName = filterValidFilename(os.path.basename(filePath))
    filePath = os.path.join(dirName, fileName)

    if len(filePath) > PATH_MAX_LEN:
        while 1:
            suffix = str(index).zfill(4)
            fileBase, fileExt = os.path.splitext(fileName)
            fixedBaseLen = \
                PATH_MAX_LEN - len(os.path.join(dirName, suffix + fileExt))
            # 
            if fixedBaseLen >= 4:
                length = len(fileBase)  + (fixedBaseLen - (len(fileBase + midfix)))
                idx, remainder = length / 2, length % 2
                fileBase = fileBase[:idx + remainder] + midfix + fileBase[-idx:]
            else:
                fileBase = fileBase[:fixedBaseLen]

            fileName = fileBase + suffix + fileExt
            filePath = os.path.join(dirName, fileName)

            if os.path.isfile(filePath):
                index += 1
                continue
            else:
                break

    return filePath

def convertUnicodeToString(unicodeString):
    """Convert unicode to str."""
    return str(unicodeString.encode('latin-1'))

def convertUnicodeToAscii(unicodeString):
    """Convert unicode to ascii. Replace unknown characters with '?'."""
    return unicodeString.encode('ascii', 'replace')

def filterString(value):
    """Replaces all marks from given string which are in replaceDict."""
    # dictionary = {mark to be replaced: used replace mark}
    replaceDict = {'"': '_',
                   "'": '_',
                   '/': '_',
                   '<': '_',
                   '>': '_',
                   '@': '_',
                   '&': '_',
                  }

    for mark in replaceDict.keys():
        value = value.replace(mark, replaceDict[mark])

    return value

def getUserHomeDir():
    """Returns user's home directory."""
    return os.path.join('C:', os.getenv('HOMEPATH'))

def formUniquePath(prefixPath):
    """ Creates a unique path string from the given path
    
        Checks if given path exists in the file system.
        Running number is added to the end so that created path is non-existing.
    
        Parameters
        prefixPath    string    path that is to be made unique
    
        Returns a string representing the created path.
    """
    counter = 0
    newPath = filterValidPath(prefixPath)
    while os.path.isdir(newPath):
        counter += 1
        newPath = filterValidPath(prefixPath + '_' + str(counter))
    return newPath

def archiveFolder(sourceFolder, targetPath, deleteSource = False):
    """Archives(Zip) whole(recursive) source folder content.

        Parameters:
                sourceFolder        source folder of files to be zipped
                targetPath          target path of zipped file
                deleteSource        boolen value if source folder is deleted
                                    after zipping
    """
    fileList = []

    # Change directory to sourceFolder folder, store current directory.
    curDir = os.path.abspath(os.curdir)
    os.chdir(sourceFolder)

    # Get list of all files under sourceFolder.
    iterator = os.walk(u'.')
    for directory, folder, files in iterator:
        if files:
            fileList.extend([os.path.join(directory, item) for item in files])

    # Zip files.
    zipped = ZipFile(targetPath, 'w', ZIP_DEFLATED)
    for filePath in fileList:
        # Filenames need special encoding
        zipped.write(filePath, filePath.encode('CP437'))

    zipped.close()

    # Change back to the original directory.
    os.chdir(curDir)

    # Delete sourceFolder.
    if deleteSource:
        try:
            rmtree(sourceFolder)
        except IOError, err:
            raise FileUtilsException("Error in folder deletion: %s" % err)

def launchFile(filePath):
    """Launches file with associated application.

        Parameters:
                filePath        path of the file to be launched
    """
    try:
        # Try to open file with associated application.
        os.startfile(filePath)
    except WindowsError: # works only in windows
        raise FileUtilsException('Error in launching file %s' % filePath)

def getFileList(pathList, fileExt = '', recursive = False, sortFiles = False):
    """Get valid file list from file/folder path or list of from file/folder
        paths.

        Parameters:

                pathList    file/folder path string or list of file/folder
                            string path(s)
                fileExt     extension of files to be included in file list
                recursive   boolen value to determine if files are listed
                            recursively
                sortFiles   boolen value to determine if file list is to be
                            sorted by modification time.

    Return value:
        list of valid file paths.
    """
    fileList = []

    if not isinstance(pathList, list):
        pathList = [pathList]

    for path in pathList:
        if os.path.isfile(path):
            if path.endswith(fileExt):
                fileList.append(path)
        elif os.path.isdir(path):
            # Get resursive list of file paths.
            if recursive:
                iterator = os.walk(unicode(path))
                for directory, folder, files in iterator:
                    if files:
                        for item in files:
                            itemPath = os.path.join(directory, item)
                            if os.path.isfile(itemPath) and \
                               itemPath.endswith(fileExt):
                                fileList.append(itemPath)
            # Get non resursive list of file paths.
            else:
                files = os.listdir(unicode(path))
                for item in files:
                    itemPath = os.path.join(path, item)
                    if os.path.isfile(itemPath) and \
                       itemPath.endswith(fileExt):
                        fileList.append(itemPath)

    # Sort files by creation time.
    if sortFiles:
        fileList = __sortByModificationTime(fileList)

    return fileList

def __sortByModificationTime(paths):
    """ Sort files by creation time.

        Parameters:
                paths   list of file paths to be sorted.

    Return value:
        list of sorted file paths.
    """
    fileDict, sortedList = {}, []

    timeStamps = [os.path.getmtime(item) for item in paths]
    fileDict = dict(zip(timeStamps, paths))
    timeStamps.sort()
    sortedList = [fileDict.get(timeStamp) for timeStamp in timeStamps]

    return sortedList

def updateFile(sourcePath, targetPath, copyFile = True, createBackUp = False):
    """ Checks modification times and updates with newer file and creates a
        backup file if needed.

    Parameters:

        - sourcePath:
            Source folder path of the files.

        - targetPath:
            Target folder path of the files.

        - copyFile:
            Copy files flag.

        - createBackUp:
            Create backup flag.

    Return value:
        Boolean value representing if a differences in modification times
        between source and target files.
    """
    srcModTime = os.path.getmtime(sourcePath)
    if os.path.isfile(targetPath):
        tgtModTime = os.path.getmtime(targetPath)
        if tgtModTime != srcModTime:
            if createBackUp:
                try:
                    copy2(targetPath, targetPath + '.bak')
                except IOError, err:
                    raise FileUtilsException("Error in creating backup file: %s" % err)
            if copyFile:
                try:
                    copy2(sourcePath, targetPath)
                except IOError, err:
                    raise FileUtilsException("Error in overwriting file: %s" % err)
            isDifferent = True
        else:
            isDifferent = False
    else:
        if copyFile:
            # Make sure target folder is created before file copying.
            targetFolder = os.path.dirname(targetPath)
            if not os.path.isdir(targetFolder):
                os.makedirs(targetFolder)
            try:
                copy2(sourcePath, targetPath)
            except IOError, err:
                raise FileUtilsException("Error in creating backup file: %s" % err)
        isDifferent = True

    return isDifferent
    
def copyFiles(sourceFolder, targetFolder, fileList, overwrite = True):
    """Copy files from source to target with shutil's copy2.

        Parameters

            sourceFolder    source directory
            targetFolder    destination directory
            fileList        relative list of file paths to copy
            overwrite       overwrite files True/False (default = True)
            
            Returns         List of strings
                            Files (as relative paths) that were copied            
    """
    assert os.path.isdir(sourceFolder), \
                            "copyFiles: source directory doesn't exist!"
    assert os.path.isdir(targetFolder), \
                            "copyFiles: destination directory doesn't exist!"

    copiedFiles = []

    for relPath in fileList:
        # strip leading division, backslash in relPath name.
        sourceFile = os.path.join(sourceFolder, relPath.lstrip('/\\'))
        targetFile = os.path.join(targetFolder, relPath.lstrip('/\\'))

        if not overwrite and os.path.isfile(targetFile):
            continue

        # ensure that destination directory exists
        targetSubDir = os.path.dirname(targetFile)
        if not os.path.isdir(targetSubDir):
            os.makedirs(targetSubDir)

        # ensure that destination directory exists
        copy2(sourceFile, targetFile)
        
        copiedFiles.append(relPath)
        
    return copiedFiles

#  Some misc ucs2 conversion functions
def ucs2(text):
    """Return text in UTF-16 -format WITHOUT end of string zeros added."""
    if type(text) == types.StringType:
        text = unicode(text, 'latin-1')
    return text.encode('utf-16')[2:] # UTF-16 identifier in [0-1]

def ucs2z(text):
    """Return text in UTF-16 -format WITH end of string zeros added."""
    return ucs2(text) + '\0\0'

def getFileHandleInformation(filePath = None):
    """Get file handle information from os by using handle.exe.
    
        Parameters
        
        filePath        if given, handle.exe output will be directed to this file
    """
    handleAppPath = os.path.join(os.getcwd(), 'A2//art2shared//apps//handle.exe')
    
    try:
        if filePath:
            debugFile = open(filePath, 'w')
            subprocess.call(handleAppPath, stdout = debugFile)
            debugFile.close()        
        else:
            subprocess.call(handleAppPath)
    except Exception, err:
        print 'Failure in handle.exe execution: %s' % str(err)
        
        