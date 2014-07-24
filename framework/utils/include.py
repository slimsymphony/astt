# ============================================================================
#
#
# %full_filespec:   include.py
#                   ----------------------------------------------------------
#                   Granite Module - Python
#
#
# Copyright (c)     Nokia. All rights reserved.
#       
# ----------------------------------------------------------------------------
"""Parser for evaluating values of #define lines from ANSI C header files.

    Examples:

    #define BAR 12345 * FOO + 54321
    #define FOO 1000

    FOO resolves to 1000l
    BAR resolves to 12399321l

    Definitions without a value will get a None for their value.
"""

# ============================================================================
# Module Setup

import sys, types, os, cPickle, re, shutil
from os.path import abspath, join, exists, isfile

global _headerPath, _cacheDirName

import core

_cacheDirName = core.FW_conf['cache_dir']
_headerPath = core.FW_conf['header_dir']

# ============================================================================
# _Include

# Separates string into a list of (hex) numbers, operations and text items.
separate_items = re.compile('\s+|' # whitespaces
                            '[-+*/%&|^~><()]|' # operations
                            '\D[^- \t\n\r\f\v+*/%&|^~><()]*|' # texts
                            '0[xX][0-9a-fA-F]+l?|' # hex code (optional 'l')
                            '\d+l?').findall # numbers (optional 'l')

# Conversion function for appending 'l' to numbers and hex strings.
append_l = lambda item: item[-1] != 'l' and item.isdigit() and item+'l' or \
                        item[-1] != 'l' and len(item) > 2 and \
                        item[0:2] in ['0X', '0x'] and item+'l' or \
                        item

class _Include:
    """An include class which parses defines from ANSI C header files.

    """
    def __init__(self, headerList):

        if type(headerList) != types.ListType:
            headerList = [headerList]

        self.headers = ' '.join(['"%s"' % self.__addPath(h) for h in headerList])

        self.unknownNames = [] # list for detecting circular definitions

        self.defines = {}
        
        for headerFile in headerList:
            self.parseHeaderFile(self.__addPath(headerFile))

    def parseHeaderFile(self, headerFile):
        if os.path.isfile(headerFile):
            oHeaderFile = open(headerFile)
        
            try:
                for line in oHeaderFile:
                    if line.startswith('#include '):
                        foundFileName = line.strip().split(None, 1)[1].strip('"')
                        self.parseHeaderFile(foundFileName)
                    elif line.startswith('#define '):
                        values = line.strip().split()

                        if len(values) >= 3:                            
                            name = values[1]
                            rawValue = ' '.join(values[2:])
                            rawValue = rawValue.split('//')[0]
                            rawValue = rawValue.split('/*')[0]
                            
                            self.defines[name] = rawValue
            finally:
                oHeaderFile.close()
                                
    def __addPath(self, filename):
        global _headerPath
        return abspath(join(_headerPath, filename))

    def __getattr__(self, name):
        """Return parsed value of macro called 'name'"""

        if name[0:2] == '__':
            raise AttributeError(name)

        return self._parseName(name)

    def parseAll(self):
        """Parse all definitions."""
        for definition, value in self.defines.iteritems():
            if value[0:1] != '_':
                try:
                    getattr(self, definition)
                except AttributeError:
                    pass # errors are silently ignored                  

        self.defines = {}

    def _parseName(self, name):
        if self.defines.has_key(name):
            value = self.defines[name]
            
            try:                        
                while 1: # Repeat until all unknown defines are resolved.
                    try:
                        items = separate_items(value)                        
                        value = ''.join([append_l(item) for item in items])
                        value = eval(value, self.__dict__)
                        setattr(self, name, value)
                        return value
                    except NameError, (nameError):
                        unknownName = str(nameError).split("'")[1]
                        if not unknownName in self.unknownNames:
                            self.unknownNames.append(unknownName)
                            unknownValue = self._parseName(unknownName)

                            setattr(self, unknownName, unknownValue)
                            self.unknownNames.pop()
                        else:
                            raise Exception, 'Circular definition detected.'
            except Exception,(e):
                raise AttributeError('Could not resolve value for "%s" from "%s": %s' %
                                     (name, self.headers, e))
        else:
            raise Exception, 'Definition not found.'                                     

    def __getstate__(self):
        odict = self.__dict__.copy()
        if odict.has_key('__builtins__'):
            del odict['__builtins__']
        return odict

# ============================================================================
# Pre-caching

_instances={}

if not exists(_cacheDirName):
    os.mkdir(_cacheDirName)
    print '%s subdirectory created for cached header files.' % _cacheDirName
    #debug.vrb('%s subdirectory created for cached header files.' % _cacheDirName)

def _getInstance(headerFilename, headerList):

    if _instances.has_key(headerFilename):
        return _instances[headerFilename]
    else:
        global _headerPath, _cacheDirName
        # Use pre-cached version if it exists (and is newer than header file!)
        cachedFilename = abspath(join(_cacheDirName, headerFilename+'.cache'))
        filename = abspath(join(_headerPath, headerFilename))

        if isfile(cachedFilename):
            st_mode, st_ino, st_dev, st_nlink, st_uid, st_gid, cached_st_size,\
                st_atime, cached_st_mtime, st_ctime  = os.stat(cachedFilename)

            st_mode, st_ino, st_dev, st_nlink, st_uid, st_gid, st_size, \
                st_atime, st_mtime, st_ctime  = os.stat(filename)

            if cached_st_size > 0 and cached_st_mtime > st_mtime:
                _instances[headerFilename] = cPickle.load(open(cachedFilename, 'rb'))
                return _instances[headerFilename]

        print 'Parse (and cache) header file: %s' % headerFilename
        #debug.out('Parse (and cache) header file: %s' % headerFilename)
        _instances[headerFilename] = _Include(headerList)
        cacheFile = open(cachedFilename, 'wb')
        try:
            _instances[headerFilename].parseAll()
            # dump using protocol 0, because others won't work with IronPython
            cPickle.dump(_instances[headerFilename], cacheFile, 0)
            cacheFile.close()
        except Exception, e:
            try:
                cacheFile.close()
            finally:
                os.remove(cachedFilename)
                #debug.err('Cache file (%s) removed. Error: %s' % (cachedFilename, e))

        return _instances[headerFilename]

class IncludeHelper:

    def lookup(self, lookupName, lookupValue, default = []):
        """Return a list of define-names matching *name* == value

            Example
                print pn.lookup('PN_MEDIA', 0x01) -->

                ['PN_MEDIA_IND_CONNECTED', 'PN_MEDIA_RESERVED']
        """
        if self.defines:
            self.parseAll()

        result = [key for key in self.__dict__.keys() \
                if key.find(lookupName) >= 0 and \
                   getattr(self, key) == lookupValue]
        if result == []:
            result = default

        return result

    def returnValues(self, lookupName):
        """Return a list of defines matching *name* """
        if self.defines:
            self.parseAll()

        return [(key, getattr(self, key)) for key in self.__dict__.keys() \
                if key.find(lookupName) >= 0]

    def returnValueKey(self, lookupName):
        """Return a list of defines matching *name* """
        if self.defines:
            self.parseAll()

        return [(getattr(self, key), key) for key in self.__dict__.keys() \
                if key.find(lookupName) >= 0]
    def returnFilePath(self):
        """Returns the whole file path."""
        global _headerPath
        return abspath(join(_headerPath, self.filename))

def Include(headerList):
    """Return instance of parsed header file.

    Usage
        from include import Include

        sms = Include('srvsms_isi.h')
        const = Include('pn_const.h')

        print sms.SMS_MESSAGE_SEND_REQ
        print const.PN_SMS

        Multiple headers can be parsed with one Include:

        inc = Include(['incs/srvsms_isi.h', 'pn_const.h'])

    Notes
        - Parsed header files are relative to _headerPath -path.

        Notes
            - Automatically parses all defines from the given file
            - Creates cached-versions into ./cache/ -subdirectory.
            - Cached version is used if its found and its newer
              than the header file
    """
    # append common phonet constant headers by default
    headers = ['pn_const.h', 'pn_obj_auto.h']
    
    if type(headerList) == types.ListType:
        headers.extend(headerList)
    else:
        headers.append(headerList)
        
    instance = IncludeHelper()

    for headerFilename in headers:
        instance.__dict__.update(_getInstance(headerFilename, headers).__dict__)
        instance.filename = headerFilename

    return instance
    