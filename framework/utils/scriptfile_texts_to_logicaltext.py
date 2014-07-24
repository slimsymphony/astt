import fileinput
import sys
import os.path
import re
import os
import getopt
from zipfile import ZipFile

import clr
clr.AddReference('System.Xml')
from System.Xml import XmlDocument

noGranite = False
try:
    import core
except:
    noGranite = True

from datetime import date

class ToLogicalText():
         
    def __init__(self, tc=None):
        self.dict = {}
        self._loadTexts()
        if len(self.dict) == 0:
            self.__msg('Warning, no texts.xml available in any of the result folders. Using old s40evo.zip')
            self.__msg('To fix this, please try run some test case to refresh the dictionary')
            self._loadOldTextDict()

    def _loadTexts(self):
        """ Load texts.xml """

        if noGranite:
            findTextsXmlPath = '..\\..\\test_sets\\'
        else:
            findTextsXmlPath = os.path.join(core.FW_conf['startup_path'], '..\\test_sets\\')

        foundfiles = []
        found = False
        for root, dirs, files in os.walk(findTextsXmlPath):
            if 'Main_texts.xml' in files:
                foundfiles.append(root + '\\Main_texts.xml')
                found = True
                
        if not found:
            # return, no texts.xml found
            return

        self.__msg('using file %s for translation' % (self._get_newest_file(foundfiles)))

        f = open(self._get_newest_file(foundfiles), 'r')
        xml = XmlDocument()
        xml.LoadXml(f.read())
        lines = f.readlines()
        f.close()
        
        errors = False

        for languageNode in xml.SelectNodes('//text'):
            
            logicalId = languageNode.GetAttribute('id')
            translationNode = languageNode.GetAttribute('translation')
            translationText = ''
                    
            # get translation text from node
            if translationNode:
                # try first utf-8 and then latin-1 encoding
                for encoding in ['utf-8', 'latin-1']:        
                    try:
                        #NOTE: InnerText returns '' if there's no text node
                        translationText = translationNode.encode(encoding)
                    except Exception, err:
                        # try next encoding              
                        pass
            else:
                errors = True

            if translationText != '' and self.dict.has_key(translationText) and logicalId not in self.dict[translationText]:
                #self.__msg('translation text %s' % translationText)
                #for i in self.dict[translationText]:
                #    self.__msg('dict has already %s' % i)
                #self.__msg('logical id is    %s' % logicalId)
                #self.__msg('self.dict[translationText] == logicalId    %s' % (self.dict[translationText] == logicalId))
                self.dict[translationText].append(logicalId)
            else:
                self.dict[translationText] = [logicalId]

        if errors:
            self.__msg('Warning: some texts did not have logical id')

    def _get_newest_file(self, files):
        # create a dict that contains list of files and their modification timestamps
        name_n_timestamp = dict([(x, os.stat(x).st_mtime) for x in files])
 
        # return the file with the latest timestamp
        return max(name_n_timestamp, key=lambda k: name_n_timestamp.get(k))

    def _loadOldTextDict(self):
                
        if noGranite:
            sourceFileName = '..\include\s40evo.zip'
        else:
            sourceFileName = os.path.join(core.FW_conf['header_dir'], 's40evo.zip')

        if not os.path.isfile(sourceFileName):
            self.__msg('error: cannot find localization file (%s)' % sourceFileName)
            if noGranite:
                sys.exit(1)
            else:
                self.tc.fail()

        zFile = ZipFile(sourceFileName)

        f = zFile.open('s40evo/en-GB/en-GB.xml', 'r')
        xml = XmlDocument()
        xml.LoadXml(f.read())
        zFile.close()

        lines = f.readlines()
        f.close()
    
        for languageNode in xml.SelectNodes('//message'):
            logicalId = languageNode.GetAttribute('id')
            # "translation" node has the translation text
            translationNode = languageNode.SelectSingleNode('translation')
            translationText = ''
                    
            # get translation text from node
            if translationNode:
                # try first utf-8 and then latin-1 encoding
                for encoding in ['utf-8', 'latin-1']:        
                    try:
                        #NOTE: InnerText returns '' if there's no text node
                        translationText = translationNode.InnerText.encode(encoding)
                    except Exception, err:
                        # try next encoding              
                        pass
            else:
                self.__msg('ERROR: Unable to get translation text, translation node missing from XML!')

            # self.__msg('self.dict[%s] = %s' % (translationText, logicalId))
            if self.dict.has_key(translationText):
                self.dict[translationText].append(logicalId)
            else:
                self.dict[translationText] = [logicalId]
                
    def __process_file(self, file, dryrun=False):
    
        if file[-3:] != '.py':
            self.__msg('File %s is not .py file, skip..' % file)
            return

        self.__msg('Processing file %s..' % file)

        ln = 0
        path, fn = os.path.split(file)
        outfile = fn.replace(".py", "")
        if not dryrun:
            outfile = path + "\\" + outfile + "_using_logical_texts.py"
            f = open(outfile, "w")
        
        no_translation = []
        
        lines = fileinput.input( file)
        for line in lines:
            if not line.find('self.navigate') > -1 and not line.find('input') > -1 and not re.search('feature *=', line) and not re.search('subarea *=', line):
                r = re.findall(r"[\'|\"](.+?)[\'|\"]",line)
                newline = line
                for i in range(len(r)):
                    if r[i][0] == '!':
                        r[i] = r[i][1:]

                    if self.dict.has_key(r[i]):
                        if len(self.dict[r[i]]) > 1:
                            self.__msg('found %s logical ids for translation "%s":\n\t%s\n' % (len(self.dict[r[i]]), r[i], str(self.dict[r[i]])))
                            newline = re.sub("'%s'" % r[i].encode("unicode_escape"), "'%s'" % self.dict[r[i]][0], newline)
                            newline = re.sub('"%s"' % r[i].encode("unicode_escape"), '"%s"' % self.dict[r[i]][0], newline)
                            newline = newline.rstrip() + " # (%s). Same logical IDs for this translation: %s\n" % (r[i], str(self.dict[r[i]]))
                        else:
                            newline = re.sub("'%s'" % r[i].encode("unicode_escape"), "'%s'" % self.dict[r[i]][0], newline)
                            newline = re.sub('"%s"' % r[i].encode("unicode_escape"), '"%s"' % self.dict[r[i]][0], newline)
                            newline = newline.rstrip() + " # (%s)\n" % r[i]
                    else:
                        no_translation.append(r[i])
                
                if not dryrun:                
                    f.write(newline)
                        
            else:
                if not dryrun:
                    f.write(line)
            ln += 1 
            
        if not dryrun:
            f.close()
            orig = path + '\\' + fn
            backup = path + '\\' + fn + '_orig'
            #self.__msg('renaming %s to %s' % (orig, backup))
            if os.path.isfile(backup):
                self.__msg('Deleting old backup file %s' % backup)
                os.remove(backup)
            os.rename(orig, backup)
            #self.__msg('renaming %s to %s' % (outfile, orig))
            os.rename(outfile, orig)
            
        if len(no_translation) > 0:
            pass
            # self.__msg('no translation for texts %r' % (no_translation,))
        
    def __process_directory(self, dir, dryrun=False):
        
        self.__msg('Processing directory %s..' % dir)

        listing = os.listdir(dir)
        for infile in listing:
            if os.path.isdir(dir + "\\" + infile) == True:
                self.__process_directory(dir + "\\" + infile, dryrun)
            else:
                self.__process_file(dir + "\\" + infile, dryrun)
                
    def translateToLogicalText(self, input, dryrun=False):
        """ Translate scripts written in EN-GB to use logical strings. Requires s40evo.zip to be included in Granite framework

        Parameters:
        input (string)      :       Path or filename to be translated

        """
        self.__msg('Opening input..')
        if os.path.isfile(input):
            self.__process_file(input, dryrun)
        elif os.path.isdir(input):
            self.__process_directory(input, dryrun)
        else:
            self.__msg( 'Cannot find %s as path or file' % input)
            return 
            
        if dryrun:
            self.__msg('Dryrun, not changing file(s)')
        else:
            self.__msg('Original files have been renamed with suffix _orig')

    def __msg(self, msg):
        if noGranite:
            print msg
        else:
            debug.brf(msg)
    
    
if __name__ == "__main__":

    if len(sys.argv) < 2:
        print "no input file or path"
        sys.exit(1)
        
    input = sys.argv[1]
        
    argv = sys.argv[2:]
    try:
        opts, args = getopt.getopt(argv,"dhi:",["ofile="])
    except getopt.GetoptError:
        printusage()
        sys.exit(2)
    
    dryrun = False
    
    for opt, arg in opts:
        if opt == '-h':
            printusage()
        elif opt == '-d':
            dryrun = True
        elif opt in ("-i", "--input"):
            input = arg
            
    if not input:
        print('No input file or directory')
        sys.exit(1)
            
    t = ToLogicalText()
    t.translateToLogicalText(input, dryrun)
