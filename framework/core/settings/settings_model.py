"""Settings model."""

# ============================================================================
# Module Setup

import os, types, re

from utils.nodeutils import NodeUtils


class SettingsModelException(Exception):
    """Base exception class for settings exceptions."""
    def __init__(self, errorString):
        Exception.__init__(self)
        self._errorString = errorString
        self._name = 'Settings exception'

    def __str__(self):
        return '%s: %s' % ( self._name, self._errorString)

class OldSettingsVersionException(SettingsModelException):
    """This exception is raised if version number of settings file to be
    loaded is older that used settings model uses."""
    pass

class UnsupportedSettingsVersionException(SettingsModelException):
    """This exception is raised if version number of settings file to be
    loaded is too new for used settings model."""
    pass

class TestWareSettingsException(SettingsModelException):
    """This exception is raised if loaded settings file is not
    testwaresettings file."""
    pass

# ============================================================================

# abstract base class, should not be instantiated
class _SettingsModel:
    """Class for reading/writing settings XML file."""
    VAL_URLTYPE = "URL"
    BRANCH_NO = 'No'
    BRANCH_CLOSE = 'Close'
    BRANCH_OPEN = 'Open'
    SETTING_XML_VERSION = "0"

    def __init__(self):
        self._path = None               # path for subblock setting files
        self._settingsDocument = None   # NodeUtils document
        self._settingsFileName = None
        self._enumDict = {}             # list of setting spesific enumerators
        self._nodeToTreeId = {}         # dictionary for node and tree id pairs
        self._settType = None
        self._initialize()

    def _initialize(self):
        """Initializes attributes."""
        self._settingsDocument = None
        self._settingsFileName = None
        self._enumDict = {}
        self._nodeToTreeId = {}
        self._settType = None

    def _makeSettings(self, postValidate = True):
        """Loads sub settings under each URL property."""
        # find all nodes which links to separate XML files
        filesToAdd = self._settingsDocument.findall(
            '//property[@type="URL"]')

        # load subblock from XML file to each node
        for fileNode in filesToAdd:
            # Load child settings from file if it is not yet loaded
            # Child setting exists if user saved settings is loaded
            if not fileNode.hasChildNodes():
                self.loadSubBlockFor(fileNode, self._path,
                                     postValidate = postValidate)

    def _getRawValue(self, node):
        """Returns value and type from dom node

            parameters node domNode where value is read

            Returns tuple (value, type). Both value and type are string.
            Returns (None, None) if 'val' attribute is not set in dom node.
        """
        valueNode = node.getAttribute('val')

        # if 'val' attribute is not found from dom node
        if valueNode == None:
            return (None, None)

        return (valueNode, self.getNodeType(node))

    def _setRawValue(self, node, value):
        """Sets value to dom node

            Parameters
                node    dom node where value is set
                value   value to be set
        """
        node.setAttribute('val', value)

    def getTreeIdforPath(self, path):
        """Return corresponding tree id for node.

            If path is not valid node, None is returned
        """
        return self._nodeToTreeId.get(path)

    def setTreeIdForNode(self, treeId, node):
        """Sets treeId for given node

            Parameters

            treeId  wxTreeid instance
            node    settings node instance
        """
        self._nodeToTreeId[self.getPath(node)] = treeId

    def _copyValues(self, sourceModel, sourceNode, ignoreRemovedValues = False,
                    ignoreDifferentTypes = True, onlyMissingValues = False):
        """Copies recursively values of sourceModel to this document

        Parameters
                sourceModel SettingsModel instance which contains data to be
                            copied
                sourceNode  xmlDOM node which siblings and childs are copied

                ignoreRemovedValues
                            does not raise SettingsModelException if
                            destination settings does not have settings item
                            which is in source settings.

                ignoreDifferentTypes
                            does not raise SettingsModelException if
                            destination settings type differs from the item
                            in source settings.
                            If types differ, value is not copied.
                           
                onlyMissingValues
                            copy only values that are missing from destination
                            
            If operation fails, throws SettingsModelException.
        """
        while sourceNode:
            path = sourceModel.getPath(sourceNode)
            sourceVal, sourceType  = sourceModel._getRawValue(sourceNode)

            if sourceVal is not None:
            # copy value of sourceNode to current document
                try:
                    destNode = self.getNodeFromPath(path)
                except SettingsModelException, err:
                    if ignoreRemovedValues:
                        # no need to check for child nodes because
                        # destination does not have these.
                        # take just possible next node and continue
                        sourceNode = sourceModel.getNext(sourceNode)
                        continue                    

                    if onlyMissingValues:                        
                        parentPath = '/'.join(path.split('/')[:-1])
                        
                        try:
                            parentNode = self.getNodeFromPath(parentPath)                            
                        except SettingsModelException:
                            parentOfParentPath = '/'.join(parentPath.split('/')[:-1])                            
                            
                            try:
                                parentOfParentNode = self.getNodeFromPath(parentOfParentPath)
                            except SettingsModelException:
                                print "onlyMissing values doesn't support more than two setting levels"
                            else:
                                parentOfParentNode.append(sourceNode.parent().clone())
                        else:
                            parentNode.append(sourceNode.clone())
                            
                        sourceNode = sourceModel.getNext(sourceNode)
                        continue
                        
                    raise err

                if not onlyMissingValues:
                    destVal, destType = self._getRawValue(destNode)
    
                    if destType != sourceType:
                        # if types differ, value is not copied
                        if not ignoreDifferentTypes:
                            raise SettingsModelException(
                                'Settings value types does not match for value ' \
                                '"%s".\n' \
                                'Destination type "%s". Source type "%s"' % \
                                (self.getPath(destNode), destType, sourceType))
                    else:
                        # if types match, copy value from source
                        self._setRawValue(destNode, sourceVal)

            child = sourceModel.getChild(sourceNode)
            if child:
                self._copyValues(sourceModel, child, ignoreRemovedValues,
                                 ignoreDifferentTypes, onlyMissingValues)
            sourceNode = sourceModel.getNext(sourceNode)

    def _validate(self, settType):
        """Validate that loaded xml file is valid settings file.

            This validation is common for all applications.

            Parameters

                versionCheck
                    bool, default True
                    Check settings version
                """
        doc = self._settingsDocument

        # check that root node is configuration and
        # there is 'settType' property block
        if doc.getName() != 'configuration' or \
           not doc.find('/configuration/property[@name="%s"]' % settType):

            raise SettingsModelException('Invalid settings file.')

    def loadSettings(self, fname, path = '',
                     settType = "Settings", postValidate=False):

        """Load settings XML to memory

            Parameters

            fname          file path and file name

            path (optional) correction for loading settings xml and
                            for relative path which is used in URL nodes

            settType(default "Settings") Block which will be accessed trough this model

            postValidate (bool) Call postivalide after load. Default True

        """
        # FIXME: load xml first without validation,
        # then assign DTD to it and validate it
        # Otherwise it is difficult to define correct path for DTD in XML file
        self._initialize()
        self._path = path

        try:
            self._settingsDocument = NodeUtils(path + fname)
        except ValueError, err:            
            # NOTE nodeutils throws value errors
            raise SettingsModelException('Invalid settings file. (Parse error)')

        self._validate(settType)
        self._makeSettings(postValidate)
        self._makeEnumerations()
        # store settings type. It is used f.ex. in getValue
        self._settType = settType

        try:
            if postValidate:
                self.postValidate()
        except UnsupportedSettingsVersionException:
            # save file name
            self._settingsFileName = path + fname
            raise
        else:
            # save file name
            self._settingsFileName = path + fname

    def postValidate(self):
        """Make application spesific validation of model centent.

            Check settings version.
            Overload this method to do application spesific checkings.

            Raises
                OldSettingsVersionException if settings xml has old version

                UnsupportedSettingsVersionException if settings xml has too
                new version.

        """
        # version check XML file
        version = float(self._settingsDocument.getAttribute('version'))

        if version < float(self.SETTING_XML_VERSION):

            raise OldSettingsVersionException(\
                'Expected version %s, got version %s.' % \
                (self.SETTING_XML_VERSION, version))

        if version > float(self.SETTING_XML_VERSION):
            raise UnsupportedSettingsVersionException(\
                'Expected version %s, got version %s.' % \
                (self.SETTING_XML_VERSION, version))

    def _makeEnumerations(self):
        """Makes enumeration values to self._enumDict."""
        # init enum values from XML
        enums = self._settingsDocument.findall('/configuration/property[@name="enumerations"]/*')
        for node in enums:
            enumValues = []
            for value in node.findall('*[@name]'):
                enumValues.append(value['name'])
            self._enumDict[node.getAttribute('name')] = enumValues

    def isEnumType(self, node):
        """Returns whether the node type is enum or not."""
        return self._enumDict.has_key(self.getNodeType(node))

    def isIntType(self, node):
        """Returns whether the node type is Int or not."""
        return self.getNodeType(node) == 'Int'

    def isStringType(self, node):
        """Returns whether the node type is Str or not."""
        return self.getNodeType(node) == 'Str'

    def isURLType(self, node):
        """Returns whether the node type is URL or not."""
        return self.getNodeType(node) == 'URL'

    def isPhoneNumberType(self, node):
        """Returns whether the node type is PhoneNumber or not."""
        return self.getNodeType(node) == 'PhoneNumber'

    def isComplexIgnoreflagType(self, node):
        """Returns whether the node type is ComplexIgnoreflag or not."""
        return self.getNodeType(node) == 'ComplexIgnoreflag'

    def isListType(self, node):
        """Returns whether the node type is List or not."""
        return self.getNodeType(node) == 'List'

    def isRootNode(self, node):
        """Returns whether the node is root node or not."""
        return node == self.getRootNode()

    def isBranchNode(self, node):
        """Returns whether the node is a branch node or not."""
        return node.getAttribute('branch') \
               in [self.BRANCH_OPEN, self.BRANCH_CLOSE]
               
    def isVisible(self, node, showHidden=True):
        """ Checks whether this node is visible in settings tree.

            If node or any of it's parent(s) are hidden False is returned.

            Parameters

            node            NodeUtils instance representing setting
                            property being examined
                            
            showHidden      boolean, default value = True
                            indicates whether 'Show advanced' setting is enabled

            Returns boolean indicating visibility of this node in settings tree.
        """
        # if showHidden then all settings are visible hence return true
        if not showHidden:
            tempNode = node
            # go through node and it's parents
            while tempNode and tempNode['mandatory']:
                if tempNode['mandatory'] == 'Hidden':
                    return False
                tempNode = tempNode.parent()

        return True

    def isValidSettingsFile(self, path):
        """ Checks whether given path is valid settings file.
        
        Parameters:
        
        path    str    absolute path to the file being tested
        
        Returns True if the file is a valid settings file.
        """
        
        # open the file as a NodeUtils instance
        try:
            settingsNode = NodeUtils(path)
        except Exception:
            return
        
        # check that property "Settings" is found
        if settingsNode.getName() == 'configuration' and \
            settingsNode.find('/configuration/property[@name="Settings"]'):
            return True

    def getEnumValueList(self, value):
        """Returns all enum values in a list."""
        return self._enumDict[value]

    def getValidValues(self, node):
        """Returns valid values in python list. If valid values don't exist,
           False is returned.

           NOTE: Value separator is ;
        """
        validValues = node.getAttribute('valid_values')

        if validValues:
            return validValues.split(';')
        else:
            return False

    def getBooleanType(self, node):
        """Returns the value of booleanType attribute.
           None will be returned if no value.
        """
        booleanTypeNode = node.getAttribute('booleanType')

        if booleanTypeNode:
            return booleanTypeNode
        else:
            return None

    def getMinValue(self, node):
        """Returns the value of min_value attribute.
           None will be returned if no value.
        """
        minValue = node.getAttribute('min_value')

        if minValue:
            return minValue != u'' and minValue or None
        else:
            return None

    def getMaxValue(self, node):
        """Returns the value of max_value attribute.
           None will be returned if no value.
        """
        maxValue = node.getAttribute('max_value')

        if maxValue:
            return maxValue != u'' and maxValue or None
        else:
            return None

    def getChilds(self, node):
        """Returns childs of given node

            Parameters

            node    node which childs is asked
        """
        return node.getChildNodes()

    def getRootNode(self):
        """Returns the root node of settings."""
        rootNode = self._settingsDocument.find('/configuration/property[@name="%s"]' % self._settType)
        return rootNode

    def getFileName(self):
        """Returns the file name of settings."""
        if self._settingsFileName:
            return self._settingsFileName
        else:
            return None

    def getPath(self, node):
        """Returns the setting path of node in same path format which is used
           in setValue and getValue methods.
        """
        assert node, 'Node is not defined'
        pathList = []

        while 1:
            # this stops to <configuration> node because
            # it does not have name attribute
            name = node.getAttribute('name')
            if not name:
                break
            pathList.insert(0, name)
            node = node.parent()

        # skip first value which is self._settType
        assert pathList[0] == self._settType
        return '/'.join(pathList[1:])

    def deleteChildNodes(self, node):
        """Deletes all child nodes of parent.

            This must be done before loading new settings subblock.
        """
        if node.hasChildNodes():
            for child in node.getChildNodes():
                node.remove(child)

    def validateLoadingSubBlock(self, fileNode, path, fileName):
        """Validates if sub block load will succeed or not.

            Parameters

                fileNode : XMLDom node under which the sub block will be loaded
                           filename is read from 'val' attribute of fileNode.

                path : directory from where file will be loaded

                fileName : sub block file name

            Returns True if load will succeed, otherwise False.
        """
        try:
            childConf = _SettingsModel()
            childConf.SETTING_XML_VERSION = self.SETTING_XML_VERSION

            nodeData = self.getNodeData(fileNode)
            childConfType = nodeData['urlType']

            childConf.loadSettings(fileName,
                                   path = path, settType = childConfType)

            childNodesXpath = '/configuration/property[@name="%s"]/*' % childConfType

            # select all child nodes which matches to parent nodes URLtype
            childNodes = \
                childConf._settingsDocument.findall(childNodesXpath)

            if not childNodes:
                raise SettingsModelException(\
                    'Category "%s" not found from "%s".' % \
                    (nodeData['urlType'], fileName))

            return True
        except SettingsModelException, err:
            print 'Sub block validation error: ', unicode(err)
            return False

    def loadSubBlockFor(self, fileNode, path, fileName = None,
                        postValidate = True):
        """Loads sub block from XML file.

            Parameters

                fileNode : XMLDom node under which the sub block will be loaded
                           filename is read from 'val' attribute of fileNode.

                path : directory from where file will be loaded

                fileName: sub block file name (default = None)

            Raises SettingsModelException if xml file does not have a
            property node which settType attribute is same than fileNode's
            URLtype attribute.
        """
        # FIXME: Dublicate code in validateLoadingSubBlock, find out how to
        # combine

        # NOTE: validateLoadingSubBlock have to be called before this method,
        #       because settings data are destroyed here even if loading
        #       doesn't succeed.

        # delete child nodes
        self.deleteChildNodes(fileNode)

        # update file name if given
        if fileName:
            self.setValue(fileNode, fileName, automaticTypeCast = True)

        childConf = _SettingsModel()
        childConf.SETTING_XML_VERSION = self.SETTING_XML_VERSION

        nodeData = self.getNodeData(fileNode)
        childConfType = nodeData['urlType']

        childConf.loadSettings(nodeData['val'],
                               path = path, settType = childConfType,
                               postValidate = postValidate)

        childNodesXpath = '/configuration/property[@name="%s"]/*' % childConfType

        # select all child nodes which matches to parent nodes URLtype
        childNodes = childConf._settingsDocument.findall(childNodesXpath)

        if not childNodes:
            raise SettingsModelException(\
                'Category "%s" not found from "%s".' % \
                (nodeData['urlType'], nodeData['val']))

        # append found child nodes to parent node
        for childNode in childNodes:
            fileNode.append(childNode.clone())

##    def getNext(self,node):
##        return node.next()
##
##    def getChildNodes(self,node):
##        return node.getChildNodes()
##

    def getNext(self, node):
        """Returns next sibling of XML node.

            This method is used for updating GUI.
        """
        return node.next()

    def getChild(self, node):
        """Returns first child node of XML node.

            This method is used for updating GUI.
        """
        if node.hasChildNodes():
            return node.first()
        else:
            return None

    def getNodeData(self, node):
        """Returns node name and attribute names and values.

            Returns dictionary with keys: name, value, hint,
                                          branch, mandatory, urlType
        """
        return {
            'name':         node.getAttribute('name'),
            'val':          node.getAttribute('val'),
            'hint':         node.getAttribute('hint'),
            'type':         node.getAttribute('type'),
            'branch':       node.getAttribute('branch'),
            'mandatory':    node.getAttribute('mandatory'),
            'urlType':      node.getAttribute('urlType'),
            }

    def getNodeFromPath(self, path):
        """Converts simple xpath like path syntax to real Xpath syntax.
           Finds corresponding XML node.

            parameters
                path    string configuration path
                        or dom node which is returned (passed trough)

            Returns XML node where the given path points.

            Raises SettingsModelException if settings item not found from given path.

            Example of supported syntax and conversion result:
            'Settings/User/User name' ->
            '/configuration/property[@name="Settings"]/property[@name="User"]/property[@name="User name"]'

            'Settings/User/[3]' ->
            '/configuration/property[@name="Settings"]/property[@name="User"]/property[position()=3]'
        """
        # if already dom node, return it
        if not isinstance(path, (str, unicode)):
            return path

        # add self._settType to path string
        path = path and self._settType + '/' + path or self._settType

        pathSteps = path.split('/')

        pathX = '/configuration'
        for step in pathSteps:
            if step.startswith('['):
                # '[xx]' -> 'xx'
                pathX += '/property[position()=%s]' % step[1:-1]
            else:
                pathX += '/property[@name="%s"]' % step

        node = self._settingsDocument.find(pathX)

        if not node:
            raise SettingsModelException('No settings data in path "%s"' % path)

        return node

    def getNodeType(self, node):
        """Returns type of node value."""
        return node.getAttribute('type')

    def getValue(self, path):
        """Reads value from settings.

            Parameters

            path    property node names separated by /
                    or
                    NodeUtils object

            Returns value. Return value is typecasted to Int / Bool / List / Str.
            Returns None if value is not defined.
        """
        node = self.getNodeFromPath(path)
        value, nodeType = self._getRawValue(node)

        # automatic typecasting
        # FIXME: This is a temporary solution, because there's no
        # support for 'undefined' - setting value
        if nodeType == "Int":
            if value:
                value = int(value)
            else:
                # FIXME: int should always be defined, this should not be
                # needed
                value = 0
        elif nodeType == "Bool":
            # check booleanType
            # NOTE: this attribute doesn't exist in gui settings
            booleanType = self.getBooleanType(node)

            if booleanType and booleanType == 'OnOff':
                value = value == "True" and 'on' or 'off'
            else:
                value = value == "True" and True or False
        elif nodeType == 'List':
            # convert string format to list type
            if len(value):
                if isinstance(value, str) or isinstance(value, unicode):
                    value = eval(value)
            else:
                value = '[]'

        # else value is is string (or None or ...)
        return value

    def setValue(self, path, value, automaticTypeCast = False):
        """Writes value to settings.

            Parameters

            path   path as string or NodeUtils

            value   value in unicode

            automaticTypeCast (Bool) default False
                If not True, checks that value type is correct.
                Otherwise tries to conver value automatically.
                (May cause error)

        """
        node = self.getNodeFromPath(path)
        nodeType = self.getNodeType(node)

        if not automaticTypeCast:
            # NOTE: data type checks are made during user input

            if nodeType in ['Str', 'URL']:
                assert isinstance(value, str) or \
                       isinstance(value, unicode)
            elif nodeType == 'Bool':
                assert isinstance(value, bool)
            elif nodeType == 'Int':
                assert isinstance(value, int)
            elif nodeType == 'PhoneNumber':
                assert isinstance(value, str)  or \
                       isinstance(value, unicode)
            elif nodeType == 'ComplexIgnoreflag':
                assert isinstance(value, str)  or \
                       isinstance(value, unicode)
            elif nodeType == 'List':
                assert isinstance(value, str)  or \
                       isinstance(value, unicode)
            else:
                raise SettingsModelException(\
                    'Invalid value (%s) or value type(%s).' \
                       % (value, nodeType))
        else:
            if nodeType == 'Bool':
                # NOTE: This if is for converting old settings to new format
                #       Empty values can exist which have changed to boolean
                if value == '':
                    value = 'False'

                # check booleanType
                # NOTE: this attribute doesn't exist in gui settings
                booleanType = self.getBooleanType(node)

                if booleanType and booleanType == 'OnOff':
                    if value == 'on':
                        value = 'True'
                    elif value == 'off':
                        value = 'False'

        # finally convert values always to unicode
        # actually needed only for Booleans. Ints are converted automatically
        # in this DOM
        value = unicode(value)
        self._setRawValue(node, value)
        
        # set remote branch accordingly
        if node['name'] == 'remote phone in use':
            self.setRemoteBranchVisibility()

    def saveSettings(self, fname):
        """Saves settings to XML file.

            Parameters
            fname       settings file name
        """
        self._settingsDocument.save(fname)
        # save file name
        self._settingsFileName = fname

    def getMandatoryParameters(self, showHidden=True):
        """Returns python list of mandatory parameters (NodeUtils)."""
        mandatoryParameters = self._settingsDocument.findall(\
                                    '//property[@mandatory="True"]')
        # FIXME can mandatoryParameters be returned?
        # if not use list notation in conversion

        paramList = []
        # get nodes out of NodeUtils list to python list
        for param in mandatoryParameters:
            if self.isVisible(param, showHidden):
                paramList.append(param)
        return paramList

    def setBranchStatus(self, node, status):
        """Sets node's branch status."""
        assert status in [self.BRANCH_OPEN, self.BRANCH_CLOSE], \
            'status attribute must be Open or Close'

        node.setAttribute('branch', status)

    def validateDataTypeValue(self, node, dataType, value):
        """Validates that value is valid for dataType.

            Parameters

                node       settings node
                dataType  ('Int' | 'Str' | 'PhoneNumber' | 'List')
                value       unicode value to be validated

            Returns True if value is valid, otherwise False
        """
        assert dataType in ['Int', 'Str', 'PhoneNumber', 'List'], \
            "dataType must be 'Int', 'Str' or 'PhoneNumber', got %s" % dataType
        assert isinstance(value, unicode), \
            'value must be unicode, got %s' % type(value)

        returnValue = False

        if dataType == 'Int':
            # reExp = re.compile(r'^[0-9]{1,}$') # one or more numbers

            # empty or one or more numbers
            reExp = re.compile(r'^[0-9]{0,}$')
            if reExp.match(value):
                returnValue = True

                # check if node has min and/or max value(s)
                minValue = self.getMinValue(node)

                if minValue and value == '':
                    returnValue = False

                if returnValue and minValue and \
                   int(value) < int(minValue):
                    returnValue = False

                maxValue = self.getMaxValue(node)

                if returnValue and maxValue and \
                   value != '' and int(value) > int(maxValue):
                    returnValue = False

        elif dataType == 'Str':
            # every string is valid unicode string
            returnValue = True
        elif dataType == 'PhoneNumber':
            # empty or contains (p, w, +, *, #) signs and numbers
            reExp = re.compile(r'^[pw+*#0-9]{0,}$')
            if reExp.match(value):
                returnValue = True
        elif dataType == 'List':
            try:
                if isinstance(eval(value), list):
                    returnValue = True
            except (NameError, SyntaxError):
                returnValue = False

        return returnValue
    
    def setSettingsVersion(self, versionNumber):
        """Sets version number for settings."""
        self._settingsDocument.setAttribute('version', versionNumber)


class TestwareSettingsModel(_SettingsModel):
    """Testware settings model class.

        Used in ART2 GUI.
    """
    SETTING_XML_VERSION = "50"
    TMP_SETTING_FILE = ""

    def postValidate(self):
        """Validate that settings is valid testware settings.
        """
        _SettingsModel.postValidate(self)
        try:
            self.getValue('Test run')
        except SettingsModelException:
            raise TestWareSettingsException(SettingsModelException)
            

class ReadOnlySettingsModel(TestwareSettingsModel):
    """Setting model to be used from scripts and fw. No access to setValue
       etc. methods.

        Used in ART2 Framework.
    """
    def __init__(self):
        """Initialize class."""
        _SettingsModel.__init__(self)

    def __del__(self):
        """Destructor."""
        _SettingsModel.__del__(self)

    def setTreeIdForNode(self, treeId, node):
        """Disabled method."""
        assert 0, "Usage of this method is not allowed!"

    def setValue(self, path, value, automaticTypeCast = False):
        """Disabled method."""
        assert 0, "Usage of this method is not allowed!"

    def setBranchStatus(self, node, status):
        """Disabled method."""
        assert 0, "Usage of this method is not allowed!"

    def clearARTpackageValues(self):
        """Disabled method."""
        assert 0, "Usage of this method is not allowed!"

    def deleteChildNodes(self, node):
        """Disabled method."""
        assert 0, "Usage of this method is not allowed!"

    def saveSettings(self, fname):
        """Disabled method."""
        assert 0, "Usage of this method is not allowed!"

