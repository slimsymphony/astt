# -*- coding: latin-1 -*-
# ============================================================================
# NOKIA
# MP FPD
# Test Services Oulu
#
#
#                       nodeutils module
#                       ----------------
#
#
# Copyright (c) Nokia. All rights reserved.
# ----------------------------------------------------------------------------

# ============================================================================
#   1   ABSTRACT
#
#   1.1 Module type
#
#       Shared utility
#
#   1.2 Description
#
#       This module contains nodeutils shared utility.
#
#       NodeUtils class implements wrapper on top of .NET XML interface.
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
#
#       3.0.1   GLOBAL DEFINITIONS
#       3.0.2   PUBLIC FUNCTIONS
#       3.0.3   LOCAL FUNCTIONS
#
#       3.1     NodeUtilsWithDotNet class
#       3.2     NodeUtils class
#
# ----------------------------------------------------------------------------
"""NodeUtils component - Wrapper on XML DOM-objects.

    NodeUtils class implements wrapper on top of xml DOM-objects so that they
    can be accessed and modified easier than plain DOM-objects.

    Note

        - See self tests in nodeutils.py for usage examples.
"""
# ============================================================================
#   3   MODULE CODE
# ----------------------------------------------------------------------------

# Python library module imports
import os, re, sys, tempfile, time
from types import NoneType

# .NET imports
import clr

clr.AddReference('System.Xml')
clr.AddReference('System.Xml.Linq')
clr.AddReference('GraniteWbxmlDecoder')

from System.Xml import XmlReader, XmlReaderSettings, DtdProcessing, \
                       XmlDocument, XmlElement, XmlTextWriter, \
                       XmlComment, XmlText, XmlDeclaration
from System.Xml.Xsl import XslCompiledTransform, XsltArgumentList
from System.Xml.Linq import XDocument
from System.IO import StringReader, File
from System import WeakReference

##
## 3.0.1 GLOBAL DEFINITIONS
##

search_paths = ['.','..']

# dictionary for keeping only one NodeUtils instance per XmlElement
# --> saves memory and makes finding nodes much faster! :)
_node_cache = {}
    
##
## 3.0.2 PUBLIC FUNCTIONS
##

# ----------------------------------------------------------------------------
#       3.1 NodeUtilsWithDotNet class
# ----------------------------------------------------------------------------
class NodeUtilsWithDotNet(object):
    def transform(self, styleSheet, targetFile = None, encoding = 'UTF-8', **parameters):
        """
        Transforms XML DOM tree using given XSLT stylesheet.
        Caller is responsible for deleting created temporary file if argument
        targetFile is not given.

        Parameters:

            - styleSheet:
                Stylesheet file path string.

            - targetFile
                Target path of the output file.

            - encoding:
                Output encoding format(default: UTF-8).

            - **parameters:
                Transform parameter keyword arguments.

        Return:

            - targetFile path.
        """
        # Create temporary file, if targetFile argument is missing.
        if not targetFile:
            targetFile = tempfile.mktemp(suffix = '.tmp')
                       
        # Parse XML and XSLT documents.  
        with XmlReader.Create(styleSheet) as xsltDoc: 
        
            # Set DtdProcessing to Parse in order to get XmlReader to accept it
            xmlReaderSettings = XmlReaderSettings()
            xmlReaderSettings.DtdProcessing = DtdProcessing.Parse                

            with StringReader(self.toxml()) as stringReader:
                with XmlReader.Create(stringReader,xmlReaderSettings) as xmlDoc:
                    #xmlDoc = xmlDocReader.Create(stringReader,xmlReaderSettings)
                                  
                    transform = XslCompiledTransform()       
                    transform.Load(xsltDoc)
            
                    # open destination file handle            
                    targetFileObj = File.OpenWrite(targetFile)        
        
                    # create xslt argument list for transformation
                    xsltArgumentList = XsltArgumentList()
                    for key, value in parameters.iteritems():
                        xsltArgumentList.AddParam(key, "", value)
                 
                    # make xslt transformation
                    transform.Transform(xmlDoc, xsltArgumentList, targetFileObj)        
           
        # close destination file handle
        targetFileObj.Close()
                
        return targetFile
        
    def createProcessingInstruction(self, target, text):
        """ Create processing instruction string.

        Parameters:

            - target:
                Processing instruction target.

            - text:
                Processing instruction text.
        """
        # Create processing instruction field
        pi = XmlDocument().CreateProcessingInstruction(target, text)        
        return pi

    def validateDtd(self):
        """Validate xml file's dtd."""
        # Validata XML files with internal DTD.
        xmlFile = self.getXMLData()
        
        if os.path.isfile(xmlFile) and self._dtdValidate:
            oFile = open(xmlFile, 'rb')
            xmlData = oFile.read()
            oFile.close()            
        
            # Set DtdProcessing to Parse in order to get XmlReader to accept it
            xmlReaderSettings = XmlReaderSettings()
            xmlReaderSettings.DtdProcessing = DtdProcessing.Parse                
                   
            with StringReader(xmlData) as stringReader:
                # just create xml reader instance to validate
                with XmlReader.Create(stringReader,xmlReaderSettings) as xmlReader:
                    pass

            # FIXME: Improve reporting in case of crash here!

# ----------------------------------------------------------------------------
#       3.2 NodeUtils class
# ----------------------------------------------------------------------------
class NodeUtils(NodeUtilsWithDotNet):
    """Common NodeUtils class.

        Class implements wrapper on top of xml DOM-objects so that they
        can be accessed and modified easier than plain DOM-objects.

        Parameters when creating objects from this class:

            content         -- Python tuple (<file name>,<xml block>) where
                               <filename> is relative path+filename of the xml data file
                               and <xml block> is name of the xml block inside of the xml file.
                               For example if <xml block> is "ok note" then xml block like
                               <tag name="ok note"> will be used OR

                               XML-string OR

                               relative filename (d_test/file.xml) OR

                               NodeUtils-instance OR

                               Document-instance

            makeNewNode     -- Make a new tag with name in content parameter skipping
                               findElement. default = False.
                               
            dtdValidate     -- Whether DTD is validated or not. boolean, default = True

        Notes

            - See self tests in nodeutils.py for usage examples.

    """
    def __init__(self, content, makeNewNode = False, dtdValidate = True):
        """Initialize the object.

        Not to be called directly. This is executed automatically when
        creating an object of this class.
        """
        # store default filename for validator
        self.__dict__["_xmlData"] = None
        self.__dict__["_dtdValidate"] = dtdValidate

        self.findElement(content, makeNewNode)

    def _get_text(self):
        """Get element's text node content."""
        return self._root.InnerText

        #encodings = ['utf-8', 'latin-1']
        
        #for encoding in encodings:        
        #    try:
        #        # NOTE: InnerText returns '' if there's no text node
        #        return self._root.InnerText.encode(encoding)
        #    except Exception, err:
        #        # try next encoding              
        #        pass
                
        ## if we haven't returned anything, raise exception                
        #raise AssertionError("_get_text(): Internal error!")

    def _set_text(self, new_text):
        """Set element's text node content."""
        # check whether element already has text node
        if self._root.HasChildNodes and \
           self._root.FirstChild and \
           isinstance(self._root.FirstChild, XmlText):
            existingTextNode = self._root.FirstChild
        else:
            existingTextNode = None
        
        if new_text:
            if existingTextNode:
                existingTextNode.Value = cast_value(new_text)
            # create new text node
            else:
                self._root.AppendChild(\
                    self._root.OwnerDocument.CreateTextNode(cast_value(new_text)))
        else:
            # remove existing text node
            if existingTextNode:
                self._root.RemoveChild(existingTextNode)

    def _del_text(self):
        """Delete element's text node."""
        # check whether element already has text node
        if self._root.HasChildNodes and \
           self._root.FirstChild and \
           isinstance(self._root.FirstChild, XmlText):
            self._root.RemoveChild(self._root.FirstChild)

    def __contains__(self, item):
        """???

        Returns

            [0 | 1]

        Scope of the method

            ???
        """
        assert isinstance(item, (str, unicode)) or isinstance(item, NodeUtils)

        if isinstance(item, (str, unicode)):
            for child in self._root.ChildNodes:
                if child.Name == item:
                    return 1
        else:
            for child in self._root.ChildNodes:
                if NodeUtils(child) == item:
                    return 1

        return 0

    def __delattr__(self, name):
        """Delete XML tag/block.

        Parameters

            name    -- NodeUtils, XML tag to delete

        Examples::

            del mySelectionlist.defaultitem

            node.name = child named 'name'

            <root>
                <name> .. </name>
            </root>

        Notes

            - XML tag must be one level below root node, otherwise it is not
              found by this delete method.
        """
        if name == '_root':
            # in case of _root, remove everything including 
            # cache and reference to XmlElement
            self._root.RemoveAll()
            _removeFromNodeCache(str(self._root))
            del self.__dict__['_root']            
        else:        
            for child in [x for x in self.getChildNodes()]:
                if child.getName() == name:
                    self._removeChild(child)

    def __delitem__(self, item):
        """Delete XML attribute.

        Parameters

            item    -- String / NodeUtils class, attribute to delete

        Scope of the method

            ???

        Examples::

            del XML_Element['attributeName']

            node[0] = 1st child etc.
            node['name'] = node's name-attribute
            node['text'] = node's first child's value
        """
        if isinstance(item, (str, unicode)): # Delete attribute named 'item'
            if item == 'text':
                #self._text = u''
                self._del_text()
            else:
                self._root.RemoveAttribute(item)
        elif isinstance(item, NodeUtils):
            self._removeChild(item)                
#        else: # Delete item child
#            self._root.RemoveChild(self._root[item])

    # FIXME: Take this back into use when memory leak in caching system is fixed!
    #def __del__(self):
    #    """When NodeUtils is deleted,
    #       remove cache and reference to XmlElement in _root.
    #   """
    #   _removeFromNodeCache(str(self._root))
    #    del self.__dict__['_root']
                
    def __eq__(self, nodeutils):
        """???

        Returns

            ???

        Scope of the method

            ???
        """
        if isinstance(nodeutils, NodeUtils):
            return self.toxml() == nodeutils.toxml()

        return 0

    def __getattr__(self, name):
        """ Returns child tag of current NodeUtils class.

        Returns

            NodeUtils class

        Scope of the method

            ???

        Examples::

            xml = "<taga>
                       <tagb>content1</tagb>
                       <tagc>
                             <tagd>content3</tagd>
                       </tagc>

                   </taga>"

            model = NodeUtils(xml)

            d_tag = model.tagc.tagd
            d_tag['text'] == 'content3'

        """
        if name[0:2] != '__': # Check for internal method
            for child in self._root.ChildNodes:
                if child.Name == name:
                    return NodeUtils(child)

        raise AttributeError(name)

    def __getitem__(self, item):
        """ Returns attribute or content ['text'] of the xml tag. If item
            is a child node, new NodeUtils instance is returned from it.

        This method overrides [] operator. E.g. to xml tags attributes
        can be accessed following way: model['attribute'].

        When giving special attribute ['text'], tags content is returned
        instead of tags attribute.


        Returns

            item == 'text'   -- Content of the tag.
                             E.g. node['text'] = node's first child's value.

            item is String   -- value of the 'item' attribute.
                             E.g. node['name'] = node's name-attribute.


            item is number   -- item child of the tag as (as NodeUtils class).
                             E.g. node[0] = 1st child.


        Examples::

            When having following xml definition,

            xml = "<taga>
                       <tagb attrib1='a'>content1</tagb>
                       <tagc></tagc>
                       <tagd>content3</tagd>
                   </taga>"

            model = NodeUtils(xml)

            debug.brf(model.tagb['text'])
            >>> content1
            debug.brf(model.tagb['attrib1'])
            >>> attrib1
            debug.brf(model.tagc['text'])
            >>> None
            debug.brf(model.tagc['attrib1'])
            >>> None
            debug.brf(model[2]['text'])
            >>> content3

        """
        if isinstance(item, (str, unicode)): # Get attribute
            if item == 'text':
                #return self._text or None
                return self._get_text() or None
            else:
                return self._root.GetAttribute(item)
        else:
            # Return item child instead
            return NodeUtils(self._root.ChildNodes[item])
            
    def __len__(self):
        """Get children count

        Return amount of child nodes in the xml block.

        Returns

            integer

        Scope of the method

            ???
        """
        return self._root.ChildNodes and len(self._root.ChildNodes) or 0

    def __nonzero__(self):
        """ Returns True

        Because __len__ is overridden in NodeUtils, boolean value of NodeUtils is returned
        using that instead of being always True (which is a default behaviour). Therefore
        __nonzero__ must be overridden also.
        """
        return True

    def __repr__(self):
        """ Returns class name as string.

        """
        return "<NodeUtils instance: '%s'>" % str(self._root)

    def __setattr__(self, name, value):
        """ Adds new tag/block to current xml data.

        Parameters:

            name  -- name of the new xml block/tag

            value -- new xml tag/block to insert

        Returns

            None

        Scope of the method

        Examples::

            xml1 = "<a/>"
            xml2 = "<b/>"
            m1 = NodeUtils(xml1)
            m2 = NodeUtils(xml2)
            m1.b = m2

        Note

            - Name of the new xml tag/block must be same as
              root tag of the new tag/block. (As seen in the example)

        """
        # skip __setattr__ magic for _root item
        # XmlElement is just put to _root
        if name == '_root' and isinstance(value, XmlElement):
            self.__dict__['_root'] = value
            return

        newChild = NodeUtils(value, makeNewNode = True)

        for oldChild in [child for child in self._root.ChildNodes]: # Use copied node list
            if oldChild.Name == name:
                self._root.ReplaceChild(\
                    self._root.OwnerDocument.ImportNode(newChild._root, True),
                    oldChild)
                return

        # Must be a new one..
        assert newChild._root.Name == name, \
               "Name '%s' must match content: '%s'" % (name, newChild)

        self.append(newChild)

    def __setitem__(self, item, value):
        """ Sets tags attribute value or content ['text']. If parameters are
            child nodes, old child (item) is replaced with new child (value).

        See __getitem__() for details.

        Returns

            None

        Scope of the method

            ???

        Examples::

            node[0] = 1st child etc.
            node['name'] = node's name-attribute
            node['text'] = node's first child's value
        """
        if isinstance(item, (str, unicode)): # Replace attribute named 'item'
            if isinstance(value, (int, long)):
                value = unicode(value)
            elif isinstance(value, (str, unicode)):
                value  = self.escapeXMLText(value)
            if item == 'text':
                #self._text = value
                self._set_text(value)
            else:
                self._root.SetAttribute(item, value)
        else: # Replace item child with new child
            newChild = NodeUtils(value)
            oldChild = self._root.ChildNodes[item]
            self._root.ReplaceChild(\
                self._root.OwnerDocument.ImportNode(newChild._root, True), oldChild)

    def __str__(self):
        """ Returns string presentation of the model.

        Returns

            String presentation of the xml model.

        Example::

            debug.brf(str(model))

        """
        return "<NodeUtils instance: '%s'>" % str(self._root)
        
    def _findFile(self,fname):
        """ looks for file fname from search_paths.
        returns path/fname is file is found.
        """
        if os.path.isfile(fname):
            return fname
            
        # Search XML file for parsing
        for sp in search_paths:
            p = os.path.join(sp, fname)
            if os.path.isfile(p):
                return p
        assert 0,'file %s not found.' % fname

    def _lookupHelper(self, node, attribute, value, itemList):
        """ lookup helper for recursive lookups.

        Parameters

            node            NodeUtils instance to be searched

            attribute       attribute name to be searched

            value           attribute value to be searched

            itemList        result list
        """
        assert isinstance(node, NodeUtils), \
            '_lookupHelper needs NodeUtils instance!'
              
        if node.getAttribute(attribute) == value:
            itemList.append(node)

        for childNode in node.getChildNodes():
            try:
                if childNode.getAttribute(attribute) == value:
                    itemList.append(childNode)
            except AttributeError, e:
                pass

            if len(childNode.getChildNodes()) > 0:
                self._lookupHelper(childNode, attribute, value, itemList)

        return itemList

    def _xmlFromStringOrFile(self, content):
        """ Detects if content is xml data as string
        or content is filename.

        returns

          nodetools element object which contains XML data.
        """
        if content.find('<') >= 0 and len(content) > 1: # Is it an XML string?
            #try:
            #    try:
            #        content = content.encode('utf-8')
            #    except UnicodeError, e:
            #        content = unicode(content).encode('utf-8')
            #except UnicodeError, e:
            #    content = unicode(content, 'latin-1').encode('utf-8')
                
            xmlDocument = XmlDocument()
            xmlDocument.LoadXml(content)
            
            return self._element(xmlDocument)
        else:
            content = self._findFile(content)

            # store filename for validator
            self.__dict__["_xmlData"] = content
            
            # validate dtd
            self.validateDtd()
            
            xmlDocument = XmlDocument()
            xmlDocument.Load(content)
            
            return self._element(xmlDocument)
            
    def _removeChild(self, node):
        """Removes child (both _Node instance and xml node inside).
        
            node        _Node instance
        """
        assert isinstance(node, NodeUtils), \
            'NodeUtils instance must be given to __removeChild!'
                
        self._root.RemoveChild(node._root)

    def append(self, newChild):
        """Insert new item to the end of the xml block.

        Parameters

            newChild            -- The new item.
        """
        assert isinstance(newChild, (str, unicode, NodeUtils)), \
            'Invalid value "%s" given to append!' % str(newChild)
            
        if isinstance(newChild, (str, unicode)):
            newChild = NodeUtils(newChild)

        # create new child element by importing it to current document context
        newChild = NodeUtils(self._root.OwnerDocument.ImportNode(\
            newChild._root, True))
        
        self._root.AppendChild(newChild._root)
        
    def clone(self, deep = True):
        """copy the content

        Makes a duplicate copy of the xml block's content.

        Parameters

            deep                -- Boolean value for deep/shallow copy.
        """
        return NodeUtils(self._root.CloneNode(deep))

    def ensurePath(self, path):
        """Returns True if a path from node is found to be valid.

        Parameters:

            path                --Path in format 'tag/tag2/tag3'

        Returns

            -True if path is valid, otherwise False

        Scope of the method

            - Returns information about the component's internal state.

        Examples

            'queryproperty.ensurePath("softkeys/selection")'
        """
        pathTags = path.split('/')
        currentTag = self

        while pathTags:
            searchTagName = pathTags.pop(0)
            if searchTagName in currentTag:
                currentTag = currentTag.__getattr__(searchTagName)
            else:
                return False

        return True

    def escapeXMLText(self, text):
        """ Escapes unallowed characters for XML elements

        Character Range accepted by XML specification 1.0::

            Char    ::=    #x9 | #xA | #xD | [#x20-#xD7FF] | [#xE000-#xFFFD] |[#x10000-#x10FFFF]
            /* any Unicode character, excluding the surrogate blocks, FFFE, and FFFF */

        If phone software has bugs, text captured by ART may contain
        unicode characters which are not in the legal range of XML
        characters. These characters would kill our DOM functionality

        Most of strings are accepted as is. This is why can speed up
        conversion by first scanning a string and escaping it only
        if escaping is required.

        Strip the last 0x10000 - 0x10FFFF slice away for speed efficiency,
        it shouldn't be in use (16-bit unicode ends to 0xFFFF).

        Parameters:

            - text: input text string

        Returns:

            - (Possible) escaped text so that it fits into XML


        """
        # iterate through characters
        for c in text:
            c = ord(c)
            if (c >= 0x20) and (c <= 0xD7FF): continue
            if (c == 0x9) or (c == 0x0A) or (c == 0x0D): continue
            if (c >= 0xe000) and (c <= 0xfffd): continue
            # invalid character
            break
        else:
            # text is good as is
            return text

        # special escaping needed
        buf = ""
        for c in text:
            l = ord(c)
            if ((l >= 0x20) and (l <= 0xD7FF)) or (l == 0x9) or (l == 0x0A) or (l == 0x0D) or \
             ((l >= 0xe000) and (l <= 0xfffd)):
                buf += c
            else:
                buf += "[Illegal character " + hex(l) + "]"

        return buf

    def find(self, xpath):
        """Find the first node that matches to the xpath expression.

        Parameters

            xpath               -- XPath expression

        Returns

            NodeUtils instance of first matching Node
        """        
        foundNode = None

        #import time
        #startTime = time.clock()        
        
        try:
            foundNode = self._node(self._root.SelectSingleNode(xpath))
        except Exception:
            foundNode = None
            
        #print 'find **********************************: ', time.clock() - startTime            

        return foundNode

    def findall(self, xpath):
        """Iterate over nodes that match to the xpath expression.

        Parameters

            xpath               -- XPath expression

        Returns

            List NodeUtils instances of matching Nodes
        """
        #import time
        #startTime = time.clock()        
        
        foundNodes = \
                [self._node(foundNode) for foundNode in self._root.SelectNodes(xpath)]                
            
        #print 'find **********************************: ', time.clock() - startTime            

        return foundNodes

    def findElement(self, content, makeNewNode = False):
        """Sets xml root node according to given content

        Parameters

            content     -- NodeUtils or Xml Element or XML string or XML filename.
        """
        if makeNewNode:
            if isinstance(content, NodeUtils):
                self.__dict__['_root'] = content._root
            elif isinstance(content, XmlElement):
                self.__dict__['_root'] = content                
            else:
                self.__dict__['_root'] = self._element(content)
        elif isinstance(content, XmlElement):
            self.__dict__['_root'] = content
        elif isinstance(content, XmlDocument):
            self.__dict__['_root'] = self._element(content)
        elif isinstance(content, NodeUtils):
            self.__dict__['_root'] = content._root
        elif type(content) in (type(''), type(u'')):
            self.__dict__['_root'] = self._xmlFromStringOrFile(content)
        else:
            assert 0, "Unsupported content:\n'%s'\ntype:%s" % \
                      (str(content), type(content))

    def first(self):
        """Get first item.

        Returns first node from same level as self.

        Returns

            The first node as NodeUtils or None
        """
        # NOTE: Loops needed in order to filter out 
        #       XmlComment, XmlText and XmlDeclaration tags
        for child in self._root.ChildNodes:
            if not isinstance(child, (XmlComment, XmlText, XmlDeclaration)):
                return NodeUtils(child)            

    def getAttribute(self, attrName):
        """Returns attribute value for given attribute name.

        Parameters

            attrName            -- attribute name

        Returns

            attribute value
        """
        return self._root.GetAttribute(attrName)

    def getAttributes(self, element = None, iterValues = False):
        """Return list of attribute names.

        Parameters

            element  -- NodeUtils

        Returns

            list of attribute names or attribute name/value pairs
        """
        if not element:
            element = self

        if iterValues:
            iterList = []
                        
            #for attr in self._xmlElem.Attributes:
            #    yield attr.Name, attr.Value
            
            for attr in self._root.Attributes:
                iterList.append((attr.Name, attr.Value))
            
            return iterList           
            #return zip(element._root.getAttributes())
        else:
            nameList = []
            #for attr in self._xmlElem.Attributes:
            #    yield attr.Name
            
            for attr in self._root.Attributes:
                nameList.append(attr.Name)
                
            return nameList
            #return list(element._root.getAttributeNames())

    def getChildNodes(self, removeItems = False, element = None):
        """Return list of element's childs.

        Parameters

            element       nodeutils element or None (= self)
        """
        if not element:
            element = self

        childNodes = []    
            
        for childNode in element._root.ChildNodes:
            # NOTE: Filter out XmlComment, XmlText and XmlDeclaration tags
            if not isinstance(childNode, (XmlComment, XmlText, XmlDeclaration)):
                childNodes.append(NodeUtils(childNode))

        if removeItems:
            for childNode in [x for x in element.getChildNodes()]:            
                element._removeChild(childNode)
            
        return childNodes

    def getXMLData(self):
        """ Return file path of current xml document.
        """
        return self.__dict__['_xmlData']

    def getIndex(self, item):
        """Return index of child item.

        Parameters

            item    -- NodeUtils

        Returns

            index number as integer
        """
        i=0
        for child in self._root.ChildNodes:
            if child._root == item._root:
                return i
            i += 1

        return -1

    def getItems(self, removeItems = False):
        """Get child items.

        Returns a list of child items that are next from root level.

        Parameters

            removeItems         remove items from parent (default = False)

        Returns

            List of NodeUtils

        Scope of the method

            - Returns information about the component's internal state.
        """
        items = [child for child in self._root.ChildNodes]
        
        if removeItems:
            for childNode in [x for x in self.getChildNodes()]:            
                self._removeChild(childNode)

        return map(NodeUtils, items)

    def getName(self):
        """Return a name of the node.

        Returns the name of the node (name of the tag).

        Returns

            name as a string.

        Scope of the method

            - Returns information about the component's internal state.
        """
        return self._root.Name

    def hasAttributes(self):
        """Returns boolean value of the existence of attributes
           in current node.
        """
        return self._root.HasAttributes

    def hasChildNodes(self):
        """Returns boolean value of the existence of child nodes
           in current node.
        """            
        for childNode in self._root.ChildNodes:
            # NOTE: Filter out XmlComment, XmlText and XmlDeclaration tags
            if not isinstance(childNode, (XmlComment, XmlText, XmlDeclaration)):
                return True
        
        return False

    def insertBefore(self, newItem, itemInModel):
        """Insert an item

        Insert new 'item' to model before item 'itemInModel'.

        Parameters

            newItem     -- New item to insert to model, see findElement content
                           parameter.

            itemInModel -- Item which appears after 'newItem' in the model.
                           see findElement content parameter
        """
        # create element from item
        newItem = NodeUtils(newItem)
        
        self._root.InsertBefore(newItem._root, itemInModel._root)

    def last(self):
        """Get last item.

        Returns last node from same level than self.

        Returns

            The last node as NodeUtils or None
        """
        # NOTE: Loop needed in order to filter out XmlComment, XmlText and XmlDeclaration tags
        lastNode = self._root.LastNode
        
        while lastNode:
            if not isinstance(lastNode, (XmlComment, XmlText, XmlDeclaration)):                               
                return NodeUtils(lastNode)
            else:
                lastNode = NodeUtils(lastNode.PreviousSibling)

    def lookup(self, attribute, value, searchAllNodes = False):
        """Return a child containing 'value'.

        Return the first child of which attribute contains given value.

        Parameters

            attribute           -- Attribute to be examined.

            value               -- Value to be searched for.

            searchAllNodes      -- bool, search just one level of hierarchy
                                  or also trough lower level child nodes.
                                  default = False.

        Returns

            - The child found from the nodeList (as NodeUtils).

            - None, if xml child was not found.

        Scope of the method

            - Returns information about the component's internal state.

        Examples

            'messagesListProperty = node.lookup("name", "messages")'
        """        
        if searchAllNodes:
            nodeList = self._lookupHelper(self, attribute, value, [])
        else:
            nodeList = self.getChildNodes()

        for childNode in nodeList:
            if childNode.getAttribute(attribute) == value:
                return childNode   

        return None

    def next(self):
        """Get next child.

        Returns next node (if exists) from same level as self.

        Returns

            The next node as NodeUtils or None
        """
        next = (self._root.NextSibling and \
               isinstance(self._root.NextSibling, XmlElement)) and \
               self._root.NextSibling or None
        if next:
            return NodeUtils(next)
        else:
            return None

    def parent(self):
        """Get parent item.

        Return parent node (if exists).

        Returns

            The parent node as NodeUtils or None
        """
        parent = self._root.ParentNode

        if parent:
            return NodeUtils(parent)
        else:
            return None

    def previous(self):
        """Get previous item.

        Returns previous node (if exists) from same level as self.

        Returns:

            Previous node as NodeUtils or None
        """
        prev = (self._root.PreviousSibling and \
               isinstance(self._root.PreviousSibling, XmlElement)) and \
               self._root.PreviousSibling or None
        
        if prev:
            return NodeUtils(prev)
        else:
            return None

    def remove(self, child):
        """Removes child node.

        Parameters

            child           -- child node to be removed
        """
        assert child, 'child node has to be given to remove!'
        self._removeChild(child)
    
    def removeAttribute(self, attribute, element = None):
        """Remove attribute from element

        Parameters

            attribute       attribute name
            element         NodeUtils or None (==self)

        Returns

            list of attribute names
        """
        if not element: element = self

        element._root.RemoveAttribute(attribute)

    def removeByAttribute(self, attribute, value, searchAllNodes = False):
        """Removes a child containing 'value'.

        Remove the first child of which attribute contains given value.

        Parameters

            attribute           -- Attribute to be examined.

            value               -- Value to be searched for.

            searchAllNodes      -- bool, search just one level of hierarchy
                                  or also trough lower level child nodes.
                                  default = False.

        Scope of the method

            - Affects the component's internal state / data model.

        Examples

            'node.removeByAttribute("name", "messages")'
        """
        child = self.lookup(attribute, value, searchAllNodes)
        
        if child:
            self._removeChild(child)

    def replaceChild(self, child, newChild, removeCloned = False):
        """Replace child with newChild.

        Parameters

            child               -- Child to be replaced.

            newChild            -- Child to be used as replacement.

            removeCloned        -- Flag to determine if replacement child is to be
                                   removed from source xml.
        """
        if removeCloned and newChild.parent():
            #newChild._root.parent.RemoveChild(newChild._root.xml)
            parentNode = NodeUtils(newChild._root.ParentNode)            
            parentNode._removeChild(newChild)

        self._root.ReplaceChild(\
            self._root.OwnerDocument.ImportNode(newChild._root, True), child._root)

    def reset(self, origDoc):
        self.findElement(origDoc)

    def setAttribute(self, attrName, value):
        """Set attribute and attribute value for node.

        Parameters

            attrName            -- name of attribute.

            value               -- new value for attribute.
        """
        self._root.SetAttribute(attrName, cast_value(value))

    def save(self, fileName, encoding = 'utf-8', indent = "    ", processInfo = False, processInfoAddress = None):
        """Save xml document.

        Parameters

            fileName            -- filename(path) for xml document saving location.

            encoding            -- encoding to be used in xml file.

            indent              -- xml indent string to be used in saving.

            processInfo         -- boolean value to determine if additional
                                   processing information is appended to xml data.
                                   (detailed report specific)
        """
        if processInfo:
            if processInfoAddress:
                xslAddress = "type='text/xsl' href='"+processInfoAddress+"'"
                processInfo = self.createProcessingInstruction("xml-stylesheet",xslAddress)             
            elif self._root.Name=='testreport':
                processInfo = self.createProcessingInstruction("xml-stylesheet",
                    "type='text/xsl' href='../xslt/test_report_xml_to_html.xslt'")
            else:
                processInfo = self.createProcessingInstruction("xml-stylesheet",
                    "type='text/xsl' href='../xslt/mem_leak_xml_to_html.xslt'")
    
        # create new XMLDocument for saving
        doc = XmlDocument()
                        
        # remove possible xml comment in root level
        for child in doc.ChildNodes:
            if isinstance(child, XmlComment):
                doc.RemoveChild(child)
        
        # add xml declaration
        #doc.AppendChild(doc.CreateXmlDeclaration('1.0', 'utf-8', ''))
               
        # add process info if found
        if processInfo:
            doc.AppendChild(doc.ImportNode(processInfo, True))
            
        # add root element
        doc.AppendChild(doc.ImportNode(self._root, True))

        doc.Save(fileName)
                
        self.__dict__["_xmlData"] = fileName

    def setName(self, nodeName):
        """Set the name of the node.

        Scope of the method

            - Changes node name to data structure.

        Parameters

            nodeName            -- new name for node.
        """
        # name is protected attribute in MS .NET xml interface, 
        # so new node needs to be created        
        if nodeName != self._root.Name:            
            # create new element and copy attributes and childs to it
            newElem = self._root.OwnerDocument.CreateElement(nodeName)
            
            for attrName, attrValue in self.getAttributes(iterValues = True):
                newElem.SetAttribute(attrName, attrValue)
            
            for child in self._root.ChildNodes:
                newElem.AppendChild(child.CloneNode(True))
              
            # get old node's possible parent
            oldParent = self._root.ParentNode
            
            if oldParent:
                oldParent.RemoveChild(self._root)
                oldParent.AppendChild(newElem)

            # delete old node
            _removeFromNodeCache(str(self._root))
            del self.__dict__['_root']
              
            # put new element instance to _root  
            self._root = newElem

    def toprettyxml(self):
        """Returns xml document with indentation.
        """                
        # do pretty printing with XDocument in System.Xml.Linq        
        XDoc = XDocument()
        
        with StringReader(self._root.OuterXml) as stringReader:
            return XDoc.Load(stringReader).ToString()
        
    def toxml(self, encoding = 'utf-8'):
        """Returns xml document without indentation.
        """
        # FIXME: How to use/set encoding?
        return self._root.OuterXml
        
    def _element(self, content):
        """Lower level constructor function for node's root element.
           
            Parameters
            
            content      XmlDocument instance or string
        """
        elementToReturn = None
        
        # check whether XmlElement is available
        if isinstance(content, XmlDocument):
            elementToReturn = content.DocumentElement
        # create new node from string
        elif isinstance(content, (str, unicode)):
            # if given string is in xml format
            # element is created via CreateDocumentFragment
            if content.startswith('<'):
                xmlDoc = XmlDocument()
                xmlFragment = xmlDoc.CreateDocumentFragment()
                xmlFragment.InnerXml = content
                xmlDoc.AppendChild(xmlFragment)
                elementToReturn = xmlDoc.DocumentElement
            else:
                xmlDoc = XmlDocument()
                elementToReturn = xmlDoc.CreateElement(content)
        else:
            raise AssertionError('Invalid root element creation! content: %s' % str(content))
        
        return elementToReturn
        
    def _node(self, xmlElement):
        """Lower level constructor function for each xml node which is searched.
           
            Parameters
            
            xmlElement       XmlElement instance
            
           Returns NodeUtils instance (either new or from cache)
        """
        assert isinstance(xmlElement, XmlElement), \
            'XmlElement instance must be given to _node!'
       
        # FIXME: New NodeUtils is returned every time
        #        Remove this when memory leak in caching system is fixed!
        return NodeUtils(xmlElement)
       
        # make string from the element instance
        xmlElementName = str(xmlElement)
        nodeToReturn = None
            
        # if element name not yet in cache
        if not _isInNodeCache(xmlElementName):
            # make new NodeUtils instance
            nodeToReturn = NodeUtils(xmlElement)
            # put weak references of both node and xml element to cache
            _setToNodeCache(xmlElementName, WeakReference(nodeToReturn, False))
        # element already in cache       
        else:
            nodeWeakRef = _getFromNodeCache(xmlElementName)
            
            if nodeWeakRef:
                # if node is alive, we can use it directly
                if nodeWeakRef.IsAlive:
                    nodeToReturn = nodeWeakRef.Target
                # if node is already dead
                else:
                    # destroy cache and weak references
                    _removeFromNodeCache(xmlElementName)
                    
                    # create new node
                    nodeToReturn = NodeUtils(xmlElement)
                    # put weak references of both node and xml element to cache
                    _setToNodeCache(xmlElementName, WeakReference(nodeToReturn, False))
            else:
                # node just died --> create new one
                _removeFromNodeCache(xmlElementName)                
                
                nodeToReturn = NodeUtils(xmlElement)
                # put weak references of both node and xml element to cache
                _setToNodeCache(xmlElementName, WeakReference(nodeToReturn, False))
           
        # return created node / node from cache
        return nodeToReturn                
        
# ============================================================================
# Internal Utility Functions
def cast_value(value):
    """Cast value into an UTF-8 string.

    Caveat: Assumes UTF-8 or US-ASCII encoding for strings!
    Caveat: None value is returned without modifications.
    """
    if isinstance(value, (str, NoneType)):
        return value

    try:
        return value.encode('utf-8') # unicode string?
    except AttributeError:
        return unicode(value).encode('utf-8') # something else..

def _isInNodeCache(xmlElementName):
    """Checks whether given xml element in in cache or not.
    
        Parameters
        
        xmlElementName      XmlElement instance name in string    
        
        Returns True if given xml element name is in cache, otherwise False.
    """
    return xmlElementName in _node_cache
        
def _getFromNodeCache(xmlElementName):
    """Get weak reference to NodeUtils instance of the given xml element from cache
    
        Parameters
        
        xmlElementName      XmlElement instance name in string    
        
        Returns weak reference to NodeUtils if given xml element name is in cache, otherwise None.
    """
    while True:
        try:
            if _isInNodeCache(xmlElementName):
                return _node_cache[xmlElementName]
            else:
                return None
        except Exception, err:
            # this may happen if multiple threads call this simultaneously
            pass

def _setToNodeCache(xmlElementName, nodeWeakRef):
    """Set weak reference to NodeUtils instance for the given xml element to cache
    
        Parameters
        
        xmlElementName      XmlElement instance name in string    
        nodeWeakRef         WeakReference to NodeUtils        
    """
    while True:
        try:
            _node_cache[xmlElementName] = nodeWeakRef
            break
        except Exception, err:
            # this may happen if multiple threads call this simultaneously
            pass
        
def _removeFromNodeCache(xmlElementName):
    """Remove weak reference to NodeUtils instance of the given xml element from cache
    
        Parameters
        
        xmlElementName      XmlElement instance name in string
    """
    while True:
        try:
            if _isInNodeCache(xmlElementName):
                del _node_cache[xmlElementName]
            break
        except Exception, err:
            # this may happen if multiple threads call this simultaneously
            pass
            
