"""
Utility module for SX script string handlings


Usage examples:

sxUtils = SxUtils()

convert = sxUtils.ConvertToSpFileUri
format = sxUtils.FormatSxString
isVisible = sxUtils.CanBeVisibleInFileManager

files = [r'C:\sp\usr\_phone\testData\file.mp3', r'E:\testData\file2.mp4', r'C:\sp\usr\file3.wav']

sxString = \
'''
(begin
    (define granite-music-player (create-player 'audio-type 'media))
    (send granite-music-player set-uri "{0}")
    (send granite-music-player play {1})
    (wait {2}
        (lambda ()
            (send granite-music-player stop)
        )
    )
)
'''

showPlayer = False
playbackTime = 10000

for file in files :
    print format(sxString, convert(file), showPlayer, playbackTime)
    print 'Is visible in file manager application: ' + str(isVisible(file))
"""
from System import String, Array, Double, Single, Decimal
from System.IO import File, Path


class SxUtils(object):
    
    """
    Utils for creating sx script strings
    """
    def __init__(self) :
        self._decimalSeparator = '.'

    def FormatSxString(self, sxString, *args) :
        
        """
        FormatSxString(self: SxUtils, sxString: str, args: positional arguments) -> str

        Replaces one or more format items in a specified string with the string 
        representation of a specified object.

        sxString: sx script as a composite format string

        args: A list of positional arguments that contains zero or more objects to format. 

        Returns: A copy of format in which the format items have been replaced by the string 
        representation of the corresponding objects in args.
        """
        
        if len(args) :
            
            params = Array[object]([[arg, 'null'][arg is None] for arg in args])

            isa = self._isInstanceOfAny
            replace = self._replaceAll

            for i in range(0, params.Length) :
                
                if isa(params[i], bool) :
                    params[i] = str(params[i]).ToLower()
                
                elif isa(params[i], Double, Single, Decimal) :
                    params[i] = replace(params[i], '.,', self.DecimalSeparator)

            sxString = String.Format(sxString, params)

        return sxString

    def ReadFromLocalFile(self, filepath, *args) :
        
        """
        ReadFromLocalFile(self: SxUtils, filepath: str, args: positional arguments) -> str

        Reads a sx script string from a local, PC file, and replaces one or more 
        format items in a specified string with the string representation of a specified object.

        filepath: local, PC file containing a sx script (as a composite format string)

        args: A list of positional arguments that contains zero or more objects to format. 

        Returns: A copy of format in which the format items have been replaced by the string 
        representation of the corresponding objects in args.
        """
        
        return self.FormatSxString(File.ReadAllText(filepath), args)

    @property
    def DecimalSeparator(self) :

        """
        Decimal separator, which is used when formatting float (Single), Double, or Decimal to string
        """

        return self._decimalSeparator

    @DecimalSeparator.setter
    def DecimalSeparator(self, value) :
        
        if value == '.' or value == ',' :
            self._decimalSeparator = value
        
        else :
            raise Exception(String.Format('Decimal separator cannot be \'{0}\'', value))

    @property
    def SpUserFolderName(self) :
        
        """
        User -folder name (token), used by SP
        """
        
        return 'usr'

    @property
    def SpMemoryCardFolderName(self) :
    
        """
        Memory card -folder name (token), used by SP
        """
    
        return '_memory_card'

    @property
    def SpPhoneFolderName(self) :
    
        """
        Phone -folder name (token), used by SP
        """
    
        return '_phone'

    @property
    def SpRootUri(self) :
    
        """
        Root Uri (protocol), used by SP
        """
    
        return 'file:///'

    @property
    def SpRootPath(self) :
        
        """
        Absolute root path of SP C-drive mounting in NOS file system
        """   
        
        return r'c:\sp'

    @property
    def SpUserFolderUri(self) :
 
        """
        Absolute SP user -folder Uri
        """
           
        return self.SpRootUri + self.SpUserFolderName

    @property
    def SpUserFolderPath(self) :
    
        """
        Absolute path of SP user -folder in NOS file system
        """
        
        return Path.Combine(self.SpRootPath, self.SpUserFolderName)

    @property
    def SpMemoryCardFolderUri(self) :
        
        """
        Absolute SP memory card Uri
        """

        return self.SpUserFolderUri + '/' + self.SpMemoryCardFolderName

    @property
    def SpMemoryCardFolderPath(self) :
        
        """
        Absolute path of SP memory card -folder in NOS file system
        """

        return 'e:\\'

    @property
    def SpPhoneFolderUri(self) :
    
        """
        Absolute SP phone -folder Uri
        """

        return self.SpUserFolderUri + '/' + self.SpPhoneFolderName

    @property
    def SpPhoneFolderPath(self) :
    
        """
        Absolute path of SP phone -folder in NOS file system
        """

        return Path.Combine(self.SpUserFolderPath, self.SpPhoneFolderName)

    def CanBeVisibleInFileManager(self, fileUriOrPath) :
    
        """
        CanBeVisibleInFileManager(self: SxUtils, fileUriOrPath: str) -> bool
        
        fileUriOrPath: Either SP uri or the actual SP file path in NOS file system

        Returns: True if file or folder with given Uri or path can be visible in File manager, in phone UI. Otherwise False
        """

        if String.IsNullOrEmpty(fileUriOrPath) :
            return False

        if (fileUriOrPath.Contains('/') and fileUriOrPath.Contains('\\')) :
            return False

        fileUriOrPath = fileUriOrPath.ToLower();
        
        mmcPath = self.SpMemoryCardFolderPath.ToLower()
        mmcUri = self.SpMemoryCardFolderUri.ToLower()

        if fileUriOrPath.StartsWith(mmcPath) or fileUriOrPath.StartsWith(mmcUri) :
            return True

        rootPath = self.SpPhoneFolderPath.ToLower()
        rootUri = self.SpPhoneFolderUri.ToLower()

        if fileUriOrPath.StartsWith(rootPath) or fileUriOrPath.StartsWith(rootUri) :
            return True

        return False

    def CanConvertToSpFilePath(self, spFileUri) :
    
        """
        CanConvertToSpFilePath(self: SxUtils, spUri: str) -> Tuple[bool, str]

        spFileUri: absolute SP file Uri, which is to be converted

        Returns: True and empty string if given sp file Uri can be converted to absolute
        file path in NOS file system. Otherwise False and error reason
        """
            
        if (String.IsNullOrEmpty(spFileUri)) :
            return False, 'SP uri cannot be None or empty'

        if spFileUri.Contains('\\') :
            return False, String.Format('\'{0}\' contains invalid path name characters', spFileUri)

        prefix = self.SpRootUri.ToLower()

        if not spFileUri.ToLower().StartsWith(prefix) :
            return False, String.Format('Not a proper SP file Uri: \'{0}\'', spFileUri)

        if spFileUri.Length >= prefix.Length + 2 :
            if spFileUri[prefix.Length + 1] == ':' :
                return False, 'SP does not support absolute file Uris'

        if self._containsInvalidPathNameChars(spFileUri.Replace(prefix, '')) :
            return False, String.Format('\'{0}\' contains invalid path name characters', spFileUri)

        return True, ''

    def ConvertToSpFilePath(self, spFileUri) :
    
        """
        ConvertToSpFilePath(self: SxUtils, spFileUri: str) -> str

        spFileUri: absolute SP file Uri, which is to be converted to real file path in NOS file system

        Returns: Corresponding absolute file path in NOS file system
        """

        converts, reason = self.CanConvertToSpFilePath(spFileUri)

        if not converts :
            raise Exception(reason)

        prefix = self.SpRootUri.ToLower()

        spMmcMount = self.SpMemoryCardFolderUri.ToLower()

        if spFileUri.ToLower().StartsWith(spMmcMount) :
            return self.SpMemoryCardFolderPath + spFileUri.Substring(spMmcMount.Length).Replace('/', '\\').Trim('\\')

        return Path.Combine(self.SpRootPath, spFileUri.Substring(prefix.Length).Replace('/', '\\').Trim('\\'))

    def CanConvertToSpFileUri(self, spFilePath) :

        """
        CanConvertToSpFileUri(self: SxUtils, spFilePath: str) -> Tuple[bool, str]

        spFilePath: absolute SP file path in NOS file system, which is to be converted to file Uri

        Returns: True and empty string if given sp file Uri can be converted to absolute
        file path in NOS file system. Otherwise False and error reason
        """

        if (String.IsNullOrEmpty(spFilePath)) :
            return False, 'SP file path cannot be None or empty'

        if not Path.IsPathRooted(spFilePath) :
            return False, 'Only absolute directory paths are supported'

        if spFilePath.Contains('/') :
            return False, String.Format('\'{0}\' contains invalid path name characters', spFilePath)

        return True, ''

    def ConvertToSpFileUri(self, spFilePath) :
    
        """
        ConvertToSpFileUri(self: SX, spFilePath: str) -> str

        spFilePath: absolute SP file path in NOS file system, which is to be converted to file Uri

        Returns: Corresponding absolute SP file Uri
        """

        converts, reason = self.CanConvertToSpFileUri(spFilePath)

        if not converts :
            raise Exception(reason)

        if spFilePath.Length == 2 :
            if spFilePath[1] == ':' :
                spFilePath = spFilePath + '\\'

        pathRoot = Path.GetPathRoot(spFilePath)

        if pathRoot.ToLower() == self.SpMemoryCardFolderPath.ToLower() :
            spUri = spFilePath.Replace(pathRoot, self.SpMemoryCardFolderUri + '/')
            spUri = spUri.Replace('\\', '/')
            return spUri.Trim('/')

        if not Path.GetPathRoot(self.SpRootPath).ToLower().StartsWith(pathRoot.ToLower()) :
            raise Exception(String.Format('Invalid drive letter \'{0}\'', pathRoot))

        nameWithoutDrive = spFilePath.Substring(pathRoot.Length)

        if not nameWithoutDrive.Length :
            raise Exception('Not possible to access root of the drive via SX')
        
        if nameWithoutDrive.Contains('\\') :
            rootFolder = nameWithoutDrive.Substring(0, nameWithoutDrive.IndexOf('\\'))
        else :
            rootFolder = nameWithoutDrive

        if self._containsInvalidPathNameChars(nameWithoutDrive) :
            raise Exception(String.Format('\'{0}\' contains invalid path name characters', nameWithoutDrive))

        spRoot = self.SpRootPath.ToLower()

        if not spRoot.EndsWith(rootFolder.ToLower()) :
            raise Exception(String.Format('SX can only access files under \'{0}\'', spRoot))
        
        subPath = nameWithoutDrive.Substring(rootFolder.Length).TrimStart('\\')

        subPath = subPath.Replace('\\', '/')

        spUri = self.SpRootUri + subPath
        
        if spUri == self.SpRootUri :
            return spUri

        return spUri.Trim('/')

    def _containsInvalidPathNameChars(self, filePath) :

        for inv in ":*?\"<>|" :
            if filePath.Contains(inv) :
                return True

        return False

    def _replaceAll(self, value, subStrings, replaceBy) :
        
        value = str(value)
        
        for sub in subStrings :
            value = value.Replace(sub, replaceBy)

        return value

    def _isInstanceOfAny(self, value, *types) :

        if not len(types) :
            return True

        for type in types :

            if isinstance(value, type) :
                return True

        return False

class SxCons(object) :
    """  Returns a newly allocated pair whose first element is a and second element is d.
         (cons a d) -> pair?
         a : any/c
         d : any/c
    """
    def __init__(self, a=None, d=None) :
        self.a = a
        self.d = d

    @property
    def A(self) :
        return self.a

    @A.setter
    def A(self, value) :
        self.a = value

    @property
    def D(self) :
        return self.d

    @D.setter
    def D(self, value) :
        self.d = value

    def __str__(self) :
        return self.ToString()

    def ToString(self) :
        _a = self.a
        _d = self.d

        if _a == None : 
            _a = 'null'
        elif isinstance(_a, str) :
            _a = '"%s"' %_a
        elif insinstance(_a, bool) :
            _a = str(_a).lower()
        else :
            _a = str(_a)

        if _d == None : 
            _d = 'null'
        elif isinstance(_d, str) :
            _d = '"%s"' %_d
        elif isinstance(_d, bool) :
            _d = str(_d).lower()
        else :
            _d = str(_d)

        return '(cons %s %s)' %(_a, _d)

class SxVector(list) :
    """ A vector is a fixed-length array with constant-time access and 
        update of the vector slots, which are numbered from 0 to one
        less than the number of slots in the vector. """

    def __init__(self, *args) :

        list.__init__(self)

        for arg in args :
            if isinstance(arg, list) or isinstance(arg, tuple) :
                for item in arg :
                    list.append(self, item)
            else :
                list.append(self, arg)

    def __str__(self) :
        return self.ToString()

    def ToString(self) :

        if self.Count == 0 :
            return '(vector)'

        format = 'vector'

        for item in self : 

            _item = item

            if _item == None :
                _item = 'null'
            elif isinstance(_item, str) :
                _item = '"%s"' %_item
            elif isinstance(_item, bool) :
                _item = str(_item).lower()
            else :
                _item = str(_item)

            format = ' %s %s' %(format, _item)

        return '(%s)' %format.strip()

class SxList(list) :
    
    def __init__(self, *args) :
        
        list.__init__(self)

        for arg in args :
            if isinstance(arg, list) or isinstance(arg, tuple) :
                for item in arg :
                    list.append(self, item)
            else :
                list.append(self, arg)

    def __str__(self) :
        return self.ToString()

    def ToString(self) :

        if self.Count == 0 :
            return '(list)'

        format = 'list'

        for item in self : 
            
            _item = item

            if _item == None :
                _item = 'null'
            elif isinstance(_item, str) :
                _item = '"%s"' %_item
            elif isinstance(_item, bool) :
                _item = str(_item).lower()
            else :
                _item = str(_item)

            format = ' %s %s' %(format, _item)

        return '(%s)' %format.strip()

class SxDictionary(dict):

    def __init__(self, *args):
        
        dict.__init__(self, *args)
    
    def __str__(self) :
        return self.ToString()

    def ToString(self) :

        if self.Count == 0 :
            return '(dictionary)'

        format = 'dictionary'

        for key in self.Keys :
            
            _key = key
            _value = self[key]

            if _key == None :
                _key = 'null'
            elif isinstance(_key, str) :
                _key = '"%s"' %_key
            elif isinstance(_key, bool) :
                _key = str(_key).lower()
            else :
                _key = str(_key)
            
            if _value == None :
                _value = 'null'
            elif isinstance(_value, str) :
                _value = '"%s"' %_value
            elif isinstance(_value, bool) :
                _value = str(_value).lower()
            else :
                _value = str(_value)

            format = '%s (%s %s)' %(format, _key, _value)

        return '(%s)' %format.strip()