import sys, shutil
from os import path, walk
from glob import iglob

usageInfo = """This script stores names of all dll-files found from execution
directory to a list. These dll-files are then overwritten by
files in cttPath-tree if files with matching names are found.

Usage:
    updateFiles path/to/ctt_installation_folder
"""


def updateFiles(cttPath):
    assert path.isdir(cttPath), '%s is not valid directory'%cttPath
    dllList = [path.split(f)[1].lower() for f in iglob("./*.dll")]
    dllList.extend(["MessageAPI/%s" % path.split(f)[1].lower() for f in iglob("./MessageAPI/*.dll")])

    for dirname, dirs, files in walk(cttPath):
        files = [i.lower() for i in files]
        for i in dllList:
            filePath, fileName = path.split(i)

            if fileName in files:
                print "Copying %s/%s..."%(dirname, fileName)
                shutil.copy2(path.join(dirname, fileName),"./%s" % filePath)


if len(sys.argv)<2:
    print usageInfo
else:
    updateFiles(sys.argv[1])