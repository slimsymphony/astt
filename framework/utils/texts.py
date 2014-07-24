"""
Internal texts module for handling logical texts

@author: Risto Pakanen
"""

import os, time, cPickle
from zipfile import ZipFile

import clr
clr.AddReference('System.Xml')
from System.Xml import XmlDocument

import core
from core import debug


class Texts(object):
    """Class for handling logical text dictionary."""
    def __init__(self):
        """Dictionary will be created in class init."""
        # s40evo.zip is zipped yapas/localization/display/s40evo - folder
        sourceFileName = os.path.join(core.FW_conf['header_dir'], 's40evo.zip')
        cacheFileName = os.path.join(core.FW_conf['cache_dir'], 'texts.cache')
            
        self.__langDict = {}
            
        if os.path.isfile(sourceFileName):
            # open language zip file
            zfile = ZipFile(sourceFileName)

            # just for debugging
            startTime = time.clock()        
        
            if os.path.isfile(cacheFileName):
                st_mode, st_ino, st_dev, st_nlink, st_uid, st_gid, cached_st_size,\
                    st_atime, cached_st_mtime, st_ctime  = os.stat(cacheFileName)

                st_mode, st_ino, st_dev, st_nlink, st_uid, st_gid, st_size, \
                    st_atime, st_mtime, st_ctime  = os.stat(sourceFileName)

                # if cache file is valid and it's newer than source file, it's used
                if cached_st_size > 0 and cached_st_mtime > st_mtime:
                    self.__langDict = cPickle.load(open(cacheFileName, 'rb'))
                    debug.vrb('Getting dict from cache...')

            if not self.__langDict:
                debug.vrb('Generating new dict...')
                self.__langDict = self.__generateLangDict(zfile)
                
                if self.__langDict:
                    # dump dict to cache
                    cacheFile = open(cacheFileName, 'wb')
                    cPickle.dump(self.__langDict, cacheFile, 0)
                    cacheFile.close()
                
            debug.vrb('Generation took %s seconds' % str(time.clock() - startTime))
                        
    def __generateLangDict(self, zfile):
        """Method for generating dictionary for logical texts of every language variant.
           Dictionary has the following data hierarchy: {'language variant': {'<text id>': '<translation>'}}
           Parses files from given zip file without extracting it.
           Uses .NET XmlDocument directly for parsing XML files to save time.
           
            Parameters
            
            zfile       ZipFile instance of the source zip file
            
            Returns generated language dict
        """
        langDict = {}
        
        # iterate all files which are inside zip file
        for oZFile in zfile.filelist:
            # only handle xml files
            if oZFile.filename.endswith('.xml'):
                xmlFilePath = oZFile.filename
                            
                # get language variant name from file path
                languageVariant = os.path.split(os.path.dirname(xmlFilePath))[-1]
                
                # open xml file from zip and parse it with XmlDocument
                oFile = zfile.open(oZFile.filename)
                xmlFile = XmlDocument()            
                xmlFile.LoadXml(oFile.read())
                # zip file handle no longer needed                
                oFile.close()
                
                # setup empty language variant dict
                langVariantDict = {}
                
                # loop through all language text nodes called "message"
                for languageNode in xmlFile.SelectNodes('//message'):
                    textId = languageNode.GetAttribute('id')
                    
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
                                break
                            except Exception, err:
                                # try next encoding              
                                pass
                    else:
                        debug.err('ERROR: Unable to get translation text, translation node missing from XML!')
                    
                    # put data into variant dict, use text id as key, translation as value  
                    langVariantDict[textId] = translationText
                
                # append variant dict to language dict having variant name as key
                langDict[languageVariant] = langVariantDict

        # close language zip file
        zfile.close()
                
        return langDict
        
    def getTranslation(self, langVariant, textId):
        """Get translation text for given language variant and textId.
        
            Parameters
            
            langVariant         language variant string (e.g. 'en_GB')
            textId              logical text id string
        
            Returns translation text if it's found, otherwise None
        """
        # FIXME: Uncomment this assert when module has be taken into use fully!
        #assert self.__langDict, 'No language dictionary generated!'
                
        returnValue = None
        
        if self.__langDict and self.__langDict.has_key(langVariant):
            returnValue = self.__langDict[langVariant].get(textId, None)
            if returnValue != None:
                returnValue = returnValue.decode('unicode_escape') # Produce a string that is suitable as Unicode literal in Python source code
                
        return returnValue

    def getLogicalText(self, langVariant, findText):
        """Get logical text ids for given language variant and text.
        
            Parameters
            
            langVariant         language variant string (e.g. 'en_GB')
            findText            text string
        
            Returns list of logical ids if it's found, otherwise None
        """
                
        returnValues = []
        
        if self.__langDict and self.__langDict.has_key(langVariant):
            [returnValues.append(id) for id, text in self.__langDict[langVariant].iteritems() if (text == findText)]
            
        if returnValues != []:
            return returnValues
        else:
            return None
        
    def isLogicalText(self, langVariant, textId):
        """Returns whether given text id is logical text or not.
        
            Parameters
            
            langVariant         language variant string (e.g. 'en_GB')
            textId              logical text id string
        
            Returns True / False
        """
        # FIXME: Uncomment this assert when module has be taken into use fully!
        #assert self.__langDict, 'No language dictionary generated!'
                
        returnValue = False
        
        if self.__langDict and self.__langDict.has_key(langVariant):
            returnValue = self.__langDict[langVariant].has_key(textId)
            
        return returnValue        
        
