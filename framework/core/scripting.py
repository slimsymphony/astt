# -*- coding: utf-8 -*-
"""
Marble Scripting Classes

@author: ripakane
"""
# IronPython library imports
import os, time, types, threading, fnmatch, calendar, math, random, json, re, string
from datetime import date, datetime
from System.Collections.Generic import List
from System import DateTime

# Marble imports
import core
from core.testcase_exceptions import TestException
from utils.nodeutils import NodeUtils
from core.decorator import override

from interfaces.tab_interface import TABInterfaceException, unescape, escape, getXpathLiteral

from core.leader import needsEvaluation

class _ScriptBase(object):
    """ Base class for all script classes. Provides default init which
        sets the phone instance to self.phone """
    def __init__(self, phone):
        self.phone = phone
        self._supportedAoL2BuildProducts = ['ara', 'leo', 'athena']

    def _convertToReport(self, item):
        """Converts string item to report."""
        try:
            # ascii
            return str(item)
        except:
            try:
                # return utf-8 string as it is
                return item
            except:
                # give up
                return '???'

    def __getattr__(self, attr, *args, **kwargs):
        return getattr(self.phone,attr)

    def isStopping(self):
        return core.FW_conf['should_stop']

    def isInSetup(self):
        """ return boolean whether the current tc is in setup """
        if core.FW_conf['current_testcase'] and core.FW_conf['current_testcase']._inSetUp:
            return True
        else:
            return False
            
    def isInTearDown(self):
        """ return boolean whether the current tc is in teardown """
        if core.FW_conf['current_testcase'] and core.FW_conf['current_testcase']._inTearDown:
            return True
        else:
            return False

class UIState(_ScriptBase):
    """
    This class holds the status for current UI state of the phone.

    """
    #LANDSCAPE = 1
    #PORTRAIT = 2

    def __init__(self, phone):
        """Initial values for UI state."""
        super(UIState,self).__init__(phone)

        self._checkedAttributes = ['content-desc', 'resource-id', 'index', 'text']

        #self.screenOrientation = self.PORTRAIT

        # lock for ui changed flag
        #self.__uiChangedLock = threading.Lock()

        # phone screen height and width variables
        # these will be updated automatically during test execution
        #self.__SCREEN_WIDTH  = 480
        #self.__SCREEN_HEIGHT = 800

    def getScreenWidth(self):
        """Returns screen width."""
        if self.phone.isFollower():
            return 480
        else:
            return self.phone._tab.getScreenWidth()

    def getScreenHeight(self):
        """Returns screen height."""
        if self.phone.isFollower():
            return 800
        else:
            return self.phone._tab.getScreenHeight()

    #def setUIChanged(self, value):
    #    """Thread safe setter for self.__uiChanged."""
    #    with self.__uiChangedLock:
    #        self.__uiChanged = value

    #def __getUIChanged(self):
    #    """Thread safe getter for self.__uiChanged."""
    #    with self.__uiChangedLock:
    #        return self.__uiChanged

    #def setNewState(self, node):
    #    """This method is called when we have new UI xml dump

    #        Parameters

    #        node (NodeUtils) :   Screen dump xml
    #    """
    #    t1 = time.time()

    #    self.currentState = NodeUtils(node)
    #    self.currentStateFull = NodeUtils(node)

    #    self.__setScreenProperties()

    #    if not self._skipNewUIState:
    #        self.__getBreathingLineHeight()

    #    applicationNodeList = self.currentState.findall('//application')
    #    if len(applicationNodeList):
    #        applicationNode = applicationNodeList[-1]
    #        self.currentPackage = applicationNode.getAttribute("name") or None
    #    else:
    #        self.currentPackage =  None

    #    self.__buildViewFromDump(self.currentState)
    #    self.__getStatusbarHeight()

    #    debug.brf("XML-dump processing took %s seconds"%(time.time()-t1))

    #def __setScreenOrientation(self):
    #    """Sets screen orientation"""
    #    if self.phone._tab.getScreenWidth() > self.phone._tab.getScreenHeight():
    #        self.screenOrientation = self.LANDSCAPE
    #    else:
    #        self.screenOrientation = self.PORTRAIT

    def _findNodes(self, searchString, checkedAttributes = None, area = None, useExistingDump = False):
        """ Return all nodes that match to search string.

            Parameters:

            searchString (str)                  string to be searched
            checkedAttributes (string / list)   checked attribute string or list of checked attributes
                                                If multiple defined, returning first matching
                                                (default = None, self._checkedAttributes will be used)
            area (4-tuple of ints)              area points left, top, width, height
                                                If None, return all nodes found from visible dump
            useExistingDump                     use existing dump (default = False)
        """
        assert (isinstance(area, tuple) and len(area) == 4) or area == None, "given area is not valid"

        # use default list if no checked attributes defined
        if checkedAttributes is None:
            checkedAttributes = self._checkedAttributes

        # transform checkedAttributes to a list
        if isinstance(checkedAttributes, basestring):
            checkedAttributes = [checkedAttributes]

        assert isinstance(searchString, basestring) or searchString == None, "searchString must be in string format or None"
        assert isinstance(checkedAttributes, list) or isinstance(checkedAttributes, tuple), "checkedAttributes is not in list or tuple format"

        searchAttribute = []

        if searchString:
            # NOTE: Can't use escape here, because then for example finding "Apps & Games" will fail
            #searchString = escape(unescape(searchString)) # unescape is needed if user gives already escaped characters
            searchString = unescape(searchString) # unescape is needed if user gives already escaped characters
            searchString = getXpathLiteral(searchString)

            for attr in checkedAttributes:
                searchAttribute.append('@%s=%s' % (attr, searchString))
        else:
            for attr in checkedAttributes:
                searchAttribute.append('@%s!=""' % attr)

        if searchAttribute:
            searchAttribute = '(' + ' or '.join(searchAttribute) + ')'
        else:
            searchAttribute = ''

        # form a xpath expression
        areaExpression = ''

        # if area is given, add it to expression
        # area is not added if it's full screen
        if area and area != (0, 0, self.getScreenWidth(), self.getScreenHeight()):
            areaExpression += '(@center-x>="%s" and @center-y>="%s" and @center-x<="%s" and @center-y<="%s")' % (area[0], area[1], area[0] + area[2], area[1] + area[3])

        # finally, combine area and item query expressions to one xpath query
        if areaExpression:
            expr = '//node[%s]' % ' and '.join([areaExpression, searchAttribute])
        else:
            expr = '//node[%s]' % searchAttribute

        #debug.brf('*******************: %s' % expr)

        #self.__setScreenOrientation()

        return self.phone._tab._getVisibleNodes(useExistingDump).findall(expr)

    def __wildcardSearch(self, expression, checkedAttributes = None, area = None, useExistingDump = False):
        """ If the given expression contains wildcards, all nodes from
            the screen area fetched and searched against the expression whether it matches.

            Parameters:
            expression (str)                    Searched expression e.g. 'Mess?ges' or *ssag* etc.
            checkedAttributes (string / list)   checked attribute string or list of checked attributes
                                                If multiple defined, returning first matching
                                                (default = None, self._checkedAttributes will be used)
            area (4-tuple)                      Area coordinates where item needs to be located
            useExistingDump                     use existing dump (default = False)
        """
        assert (isinstance(area, tuple) and len(area) == 4) or area == None, "given area is not valid"

        # use default list if no checked attributes defined
        if checkedAttributes is None:
            checkedAttributes = self._checkedAttributes

        # transform checkedAttributes to a list
        if isinstance(checkedAttributes, basestring):
            checkedAttributes = [checkedAttributes]

        assert isinstance(expression, basestring), "searchString is not in string format"
        assert isinstance(checkedAttributes, list), "checkedAttributes is not in list format"

        nodesFound = []

        if "*" in expression or "?" in expression or ("[" in expression and "]" in expression):
            for node in self._findNodes(None, checkedAttributes, area, useExistingDump):
                for attr in checkedAttributes:
                    if fnmatch.fnmatch(node.getAttribute(attr).replace("\n"," "), expression):
                        nodesFound.append(node)
                        break

        return nodesFound

    def _searchItem(self, itemName, checkedAttributes = None, area = None, index = 0):
        """Searches item from visible nodes

            Parameters:
            itemName(string)                    item to be searched
            checkedAttributes (string / list)   checked attribute string or list of checked attributes
                                                If multiple defined, returning first matching
                                                (default = None, self._checkedAttributes will be used)
            area (4-tuple)                      Area coordinates where item needs to be located
            index                               node index (default = 0, first found node)
        """
        assert (isinstance(area, tuple) and len(area) == 4) or area == None, "given area is not valid"
        assert isinstance(index, int), "given index is not valid"

        # use default list if no checked attributes defined
        if checkedAttributes is None:
            checkedAttributes = self._checkedAttributes

        # transform checkedAttributes to a list
        if isinstance(checkedAttributes, basestring):
            checkedAttributes = [checkedAttributes]

        assert isinstance(itemName, basestring), "itemName is not in string format"
        assert isinstance(checkedAttributes, list), "checkedAttributes is not in list format"

        nodes = self._findNodes(itemName, checkedAttributes, area)

        # put index to list iteration number
        if isinstance(index, int):
            index -= 1
            if index < 0:
                index = 0

        if nodes:
            try:
                return nodes[index]
            except IndexError:
                debug.err("Item was not found with index: %s" % str(index))
                return None
        else:
            nodes = self.__wildcardSearch(itemName, checkedAttributes, area, useExistingDump = True)

            if nodes:
                try:
                    return nodes[index]
                except IndexError:
                    debug.err("Item was not found with index: %s" % str(index))
                    return None
            else:
                return None

    def __waitForItem(self, itemName, timeout, checkedAttributes = None, area = None):
        """ Waits for item to become accessible

        Parameters:
            itemName(string)                    Item to be waited for
            timeout(int)                        wait timeout
            checkedAttributes (string / list)   checked attribute string or list of checked attributes
                                                If multiple defined, returning first matching
                                                (default = None, self._checkedAttributes will be used)
            area (4-tuple)                      Area coordinates where item needs to be located
        """
        assert (isinstance(area, tuple) and len(area) == 4) or area == None, "given area is not valid"
        assert isinstance(timeout, int) or timeout == None, 'given timeout "%s" is not valid' % str(timeout)

        # use default list if no checked attributes defined
        if checkedAttributes is None:
            checkedAttributes = self._checkedAttributes

        # transform checkedAttributes to a list
        if isinstance(checkedAttributes, basestring):
            checkedAttributes = [checkedAttributes]

        assert isinstance(itemName, basestring), "itemName is not in string format"
        assert isinstance(checkedAttributes, list), "checkedAttributes is not in list format"

        if timeout == None:
            timeout=core.FW_conf['settings'].System.ExpectTimeout

        t = time.time()

        while t + timeout / 1000.0 > time.time():
            # just return if test execution is stopping
            if core.FW_conf['should_stop']:
                return

            if self._findNodes(itemName, checkedAttributes, area):
                return True

            self.phone.delay(1000, False)

        return False

    def revealItem(self, item, timeout = None, checkedAttributes = None, area = None, index = 0, doNotScroll = False):
        """ This method returns coordinates of item. If item is not visible it is scrolled to screen before returning coordinates.
            Test case fails if item does not become visible during timeout period.

        Parameters:
            item(string)                        Name of the item which needs to be visible
            timeout(int)                        Time to wait item which is not found from screen
            checkedAttributes (string / list)   checked attribute string or list of checked attributes
                                                If multiple defined, returning first matching
                                                (default = None, self._checkedAttributes will be used)
            area (4-tuple)                      Area coordinates where item needs to be located
            index(int)                          node index (default = 0, first found node)
            doNotScroll(bool)                   If set to True screen is not scrolled when trying to find item (default = False)
        """
        assert (isinstance(area, tuple) and len(area) == 4) or area == None, "given area is not valid"
        assert isinstance(timeout, int) or timeout == None, "given timeout is not valid"

        # use default list if no checked attributes defined
        if checkedAttributes is None:
            checkedAttributes = self._checkedAttributes

        # transform checkedAttributes to a list
        if isinstance(checkedAttributes, basestring):
            checkedAttributes = [checkedAttributes]

        assert isinstance(item, basestring), "item is not in string format"
        assert isinstance(checkedAttributes, list), "checkedAttributes is not in list format"

        node = self._searchItem(item, checkedAttributes, area, index)

        if node:
            return (int(node.getAttribute('center-x')), int(node.getAttribute('center-y')))
        else:
            if self.__waitForItem(item, timeout, checkedAttributes, area):
                node = self._searchItem(item, checkedAttributes, area, index)

                if node:
                    return (int(node.getAttribute('center-x')), int(node.getAttribute('center-y')))
                else:
                    return None
            else:
                if not doNotScroll:
                    coords = self.phone._tab._scroll(item)

                    if coords:
                        return coords
                    else:
                        return None
                else:
                    return None

class Select(_ScriptBase):
    """
    Class for Select
    """
    def __call__(self, item, timeout=None, doNotReport=False, index=1, doNotSelect=False, doNotScroll=False, doNotWait=False):
        """ Default select functionality

        Parameters:
            item(string|tuple)      :   item, key or coordinates to be selected
            timeout(int)            :   Wait timeout
            doNotReport(boolean)    :   Whether select is put to test report or not
            index(int)              :   Sequence number of the item to select
            doNotSelect(bool)       :   If set to True item is only scrolled to screen without selecting it
            doNotScroll(bool)       :   If set to True screen is not scrolled when trying to find item
            doNotWait(bool)         :   If set to True UI events are not waited after select
        """
        if not doNotReport:
            if isinstance(item, tuple):
                self.phone.comment('select((%s, %s))' % (str(item[0]), str(item[1])))
            else:
                self.phone.comment('select(%s)' % self._convertToReport(item))

        self.__select(item, timeout=timeout, index=index, doNotSelect=doNotSelect, doNotScroll=doNotScroll, doNotWait=doNotWait)

    def long(self,item, length=1500, timeout=None, doNotReport=False, index=1, doNotScroll=False, doNotWait=False, withAttribute = None):
        """ Long press to coordinates with default value
            or with given value if it is bigger than default value.

        Paramters:
            item(string|tuple)              item, key or coordinates to be selected
            length(int)                     press length
            timeout(int)                    wait timeout
            doNotReport(boolean)            Whether select is put to test report or not
            index(int)                      Sequence number of the item to select
            doNotScroll(bool)               If set to True screen is not scrolled when trying to find item
            doNotWait(bool)                 If set to True UI events are not waited after select
            withAttribute (string)          attribute string to be used for long select
                                            ('description' / 'resourceId' / 'indexTree' / 'text')
        """
        if not doNotReport:
            self.phone.comment('select.long(%s)' % self._convertToReport(item))

        if length < 1500:
            length = 1500

        if withAttribute != None:
            if withAttribute == 'description':
                withAttribute = 'content-desc'
            elif withAttribute == 'resourceId':
                withAttribute = 'resource-id'
            elif withAttribute == 'indexTree':
                withAttribute = 'index'
            elif withAttribute != 'text':
                raise Exception('Invalid value given to withAttribute parameter! Must be "description", "resourceId", "indexTree" or "text"')

        self.__select(item, length=length, timeout=timeout, index=index, doNotScroll=doNotScroll, doNotWait=doNotWait, checkedAttributes=withAttribute)

    def __select(self, item, length=None, timeout=None, index=1, doNotSelect=False, checkedAttributes = None, doNotScroll=False, doNotWait=False):
        """ Select item.

        Parameters:
            item(string|tuple)                  Item, key or coordinates to be selected
            length(int)                         Length of the press
            timeout(int)                        Wait timeout
            index(int)                          Sequence number of the item to select
            doNotSelect(bool)                   If set to True item is only scrolled to screen without selecting it
            checkedAttributes (string / list)   checked attribute string or list of checked attributes
                                                If multiple defined, returning first matching
                                                (default = None, self._checkedAttributes will be used)
            doNotScroll(bool)                   If set to True screen is not scrolled when trying to find item
            doNotWait(bool)                     If set to True UI events are not waited after select
        """
        # if item is int, cast to string
        if isinstance(item, int):
            item = str(item)

        try:
            if doNotWait:
                # set UI event waiting off
                self.phone._tab.waitUntilNoUIevents = False

            # Press (x, y) coordinate point when item is tuple
            if isinstance(item, tuple):
                # convert relative coordinates to absolute if needed
                origItem = item
                item = self.phone._tab._convertRelative(item)

                if origItem != item:
                    debug.brf('select: (%s, %s) converted to absolute coordinates: (%s, %s)' % (str(origItem[0]), str(origItem[1]), str(item), str(item)))

                self.phone._touch.press(item, length)
                self.phone._run('Press to coordinates: %s,%s' % item)
                return

            if item.startswith('KEYCODE'):
                self.phone._pressKey(item, length)
                self.phone._run('Press (%s) key' % item)
                if item == 'KEYCODE_POWER':
                    self.phone.delay(100, False)
                return

            # request UI state to wait and scroll the item to the screen
            coordinates = self.phone.uiState.revealItem(item = item, timeout = timeout, checkedAttributes = checkedAttributes, index = index, doNotScroll = doNotScroll)

            if coordinates:
                if not doNotSelect:
                    self.phone._touch.press(coordinates, length)
                    self.phone._run('select()')
            else:
                self.phone.fail("Cannot select %s, item is not found" % self._convertToReport(item))
        finally:
            # restore UI event waiting flag
            self.phone._tab.waitUntilNoUIevents = True

    def text(self, item, timeout=None, doNotReport=False, index=1, doNotSelect=False, doNotScroll=False, doNotWait=False):
        """ Select item by text.

        Parameters:
            item(string)            :   Item to be selected
            timeout(int)            :   Wait timeout
            doNotReport(boolean)    :   Whether select is put to test report or not
            index(int)              :   Sequence number of the item to select
            doNotSelect(bool)       :   If set to True item is only scrolled to screen without selecting it
            doNotScroll(bool)       :   If set to True screen is not scrolled when trying to find item
            doNotWait(bool)         :   If set to True UI events are not waited after select
        """
        if not doNotReport:
            self.phone.comment('select.text(%s)' % self._convertToReport(item))

        self.__select(item, timeout=timeout, index=index, doNotSelect=doNotSelect, checkedAttributes = 'text', doNotScroll=doNotScroll, doNotWait=doNotWait)

    def description(self, item, timeout=None, doNotReport=False, index=1, doNotSelect=False, doNotScroll=False, doNotWait=False):
        """ Select item by description.

        Parameters:
            item(string)            :   Item to be selected
            timeout(int)            :   Wait timeout
            doNotReport(boolean)    :   Whether select is put to test report or not
            index(int)              :   Sequence number of the item to select
            doNotSelect(bool)       :   If set to True item is only scrolled to screen without selecting it
            doNotScroll(bool)       :   If set to True screen is not scrolled when trying to find item
            doNotWait(bool)         :   If set to True UI events are not waited after select
        """
        if not doNotReport:
            self.phone.comment('select.description(%s)' % self._convertToReport(item))

        self.__select(item, timeout=timeout, index=index, doNotSelect=doNotSelect, checkedAttributes = 'content-desc', doNotScroll=doNotScroll, doNotWait=doNotWait)

    def indexTree(self, item, timeout=None, doNotReport=False, index=1, doNotSelect=False, doNotScroll=False, doNotWait=False):
        """ Select item by index tree.

        Parameters:
            item(string)            :   Item to be selected
            timeout(int)            :   Wait timeout
            doNotReport(boolean)    :   Whether select is put to test report or not
            index(int)              :   Sequence number of the item to select
            doNotSelect(bool)       :   If set to True item is only scrolled to screen without selecting it
            doNotScroll(bool)       :   If set to True screen is not scrolled when trying to find item
            doNotWait(bool)         :   If set to True UI events are not waited after select
        """
        if not doNotReport:
            self.phone.comment('select.indexTree(%s)' % self._convertToReport(item))

        self.__select(item, timeout=timeout, index=index, doNotSelect=doNotSelect, checkedAttributes = 'index', doNotScroll=doNotScroll, doNotWait=doNotWait)

    def resourceId(self, item, timeout=None, doNotReport=False, index=1, doNotSelect=False, doNotScroll=False, doNotWait=False):
        """ Select item by resourceId.

        Parameters:
            item(string)            :   Item to be selected
            timeout(int)            :   Wait timeout
            doNotReport(boolean)    :   Whether select is put to test report or not
            index(int)              :   Sequence number of the item to select
            doNotSelect(bool)       :   If set to True item is only scrolled to screen without selecting it
            doNotScroll(bool)       :   If set to True screen is not scrolled when trying to find item
            doNotWait(bool)         :   If set to True UI events are not waited after select
        """
        if not doNotReport:
            self.phone.comment('select.resourceId(%s)' % self._convertToReport(item))

        self.__select(item, timeout=timeout, index=index, doNotSelect=doNotSelect, checkedAttributes = 'resource-id', doNotScroll=doNotScroll, doNotWait=doNotWait)

class Check(_ScriptBase):
    """ Class for checking item without selecting it"""
    def __call__(self, item, timeout=None, occurrence=1, checkedAttributes=None, doNotReport=False, doNotScroll=False, getCoordinates=False):
        """ Executes check functionality

        Parameters:
            item(string)                        Item to be checked
            timeout(int)                        Timeout for check (default = None)
            occurrence(1)                       Amount of occurences (default = 1)
            checkedAttributes (string / list)   checked attribute string or list of checked attributes
                                                If multiple defined, returning first matching
                                                (default = None, self._checkedAttributes will be used)
            doNotReport(boolean)                Whether test step is put to test report or not
            doNotScroll(bool)                   If set to True screen is not scrolled when trying to find item

        Returns True if item was found, False if not
        """
        assert isinstance(occurrence, int), "Parameter occurrence must be of type int, got %s instead!" % type(occurrence)

        # if attribute is int, cast to string
        if type(item) == types.IntType:
            item = str(item)

        if not doNotReport:
            self.phone.comment('check(%s)' % self._convertToReport(item))
        
        result = None
        try:
            # request UI state to wait and scroll the item to the screen
            result = self.phone.uiState.revealItem(item = item, timeout = timeout, checkedAttributes = checkedAttributes, index = occurrence, doNotScroll = doNotScroll)
        except TestException:
            # when scrolling fails
            pass
        
        if getCoordinates:
            return result
        elif result:
            return True
        else:
            return False

    def text(self, item, timeout=None, occurrence=1, doNotReport=False, doNotScroll=False, getCoordinates=False):
        """ Check item by text.

        Parameters:
            item(string)            :   Item to be checked
            timeout(int)            :   Timeout for check (default = None)
            occurrence(1)           :   Amount of occurences (default = 1)
            doNotReport(boolean)    :   Whether test step is put to test report or not
            doNotScroll(bool)       :   If set to True screen is not scrolled when trying to find item
        """
        if not doNotReport:
            self.phone.comment('check.text(%s)' % self._convertToReport(item))

        return self.__call__(item, timeout=timeout, occurrence=occurrence, checkedAttributes='text', doNotReport=True, doNotScroll=doNotScroll, getCoordinates=getCoordinates)

    def description(self, item, timeout=None, occurrence=1, doNotReport=False, doNotScroll=False, getCoordinates=False):
        """ Check item by description.

        Parameters:
            item(string)            :   Item to be checked
            timeout(int)            :   Timeout for check (default = None)
            occurrence(1)           :   Amount of occurences (default = 1)
            doNotReport(boolean)    :   Whether test step is put to test report or not
            doNotScroll(bool)       :   If set to True screen is not scrolled when trying to find item
        """
        if not doNotReport:
            self.phone.comment('check.description(%s)' % self._convertToReport(item))

        return self.__call__(item, timeout=timeout, occurrence=occurrence, checkedAttributes='content-desc', doNotReport=True, doNotScroll=doNotScroll, getCoordinates=getCoordinates)

    def indexTree(self, item, timeout=None, occurrence=1, doNotReport=False, doNotScroll=False, getCoordinates=False):
        """ Check item by index tree.

        Parameters:
            item(string)            :   Item to be checked
            timeout(int)            :   Timeout for check (default = None)
            occurrence(1)           :   Amount of occurences (default = 1)
            doNotReport(boolean)    :   Whether test step is put to test report or not
            doNotScroll(bool)       :   If set to True screen is not scrolled when trying to find item
        """
        if not doNotReport:
            self.phone.comment('check.indexTree(%s)' % self._convertToReport(item))

        return self.__call__(item, timeout=timeout, occurrence=occurrence, checkedAttributes='index', doNotReport=True, doNotScroll=doNotScroll, getCoordinates=getCoordinates)

    def resourceId(self, item, timeout=None, occurrence=1, doNotReport=False, doNotScroll=False, getCoordinates=False):
        """ Check item by resource id.

        Parameters:
            item(string)            :   Item to be checked
            timeout(int)            :   Timeout for check (default = None)
            occurrence(1)           :   Amount of occurences (default = 1)
            doNotReport(boolean)    :   Whether test step is put to test report or not
            doNotScroll(bool)       :   If set to True screen is not scrolled when trying to find item
        """
        if not doNotReport:
            self.phone.comment('check.resourceId(%s)' % self._convertToReport(item))

        return self.__call__(item, timeout=timeout, occurrence=occurrence, checkedAttributes='resource-id', doNotReport=True, doNotScroll=doNotScroll, getCoordinates=getCoordinates)

    def notification(self, item, bestBefore=5000, timeout=5000, doNotReport=False):
        """ Checks if notification(s) are displayed withing given timeout

        Parameters:
        item(string | list)    :   Item or list of items to be checked (if any item in the list matches check is passed)
        bestBefore(int)        :   From how far the notification occurance should be checked (default = 10000 ms)
        timeout(int)           :   Timeout for check (default = 50000 ms)
        doNotReport(boolean)   :   Whether test step is put to test report or not
        """
        initialStart = datetime.now()

        if isinstance(item, str):
            item = [ item ]

        if not doNotReport:
            self.phone.comment('check.notification(%s)' % ', '.join(item))

        assert isinstance(bestBefore, int), 'parameter bestBefore is of type %s, expected %s' % (type(bestBefore), int)
        assert isinstance(timeout, int), 'parameter timeout is of type %s, expected %s' % (type(timeout), int)

        # Include the few milliseconds it takes to get here
        if bestBefore <= 0:
            bestBefore = int((datetime.now()-initialStart).total_seconds() * 1000)

        notifications = self.phone._tab._getNotifications(bestBefore)

        isMatch = False

        for notification in notifications:
            for filter in item:
                isMatch = fnmatch.fnmatch(notification, filter)
                if isMatch:
                    break
            if isMatch:
                break

        if timeout <= 0:
            return isMatch

        start = datetime.now()
        while not isMatch and (datetime.now() - start).total_seconds() * 1000 < timeout:
            self.phone.delay(200, False)
            bestBefore += 200
            isMatch = self.notification(item, bestBefore, 0, doNotReport=True)

        return isMatch

class Navigate(_ScriptBase):
    """ Class for navigating to items
    """
    def __init__(self, phone):
        """

        """
        super(Navigate,self).__init__(phone)

    @override
    def navigate(self, item, doNotSelect=False, fromRecent=None):
        """ Default navigate functionality

        Parameters:
            item (string)        :   Name of the item where to navigate
            doNotSelect (bool)   :   If set to True item is only scrolled to screen without selecting it
            fromRecent (bool)    :   When True, application is launched from recent apps if found
                                     When False, application is removed from recent apps before navigate
                                     When None, normal navigate is in use (default)

            Returns True if navigating succeeded, False if not.
        """
        return self.__navigate(item, doNotSelect=doNotSelect, fromRecent=fromRecent)

    def __navigate(self, item, doNotSelect=False, fromRecent=None, fromAppList=False, fromLetterView=False, fast=False, doNotReport=False):
        """ Internal navigate method

        Parameters:
            item (string)        :   Name of the item where to navigate
            doNotSelect (bool)   :   If set to True item is only scrolled to screen without selecting it
            fromRecent (bool)    :   When True, application is launched from recent apps if found
                                     When False, application is removed from recent apps before navigate
                                     When None, normal navigate is in use (default)
            fromAppList (bool)   :   When True, application is directly searched from application list
                                     When False, application is firstly searched from my space and then from application list (default)
            fromLetterView (bool):   When True, application is searched using letter view
                                     When False, application is searched using normal view (default)
            fast (bool)          :   When True, use fast scrolling when searching
                                     When False, use normal speed scroll when searching (default)
            doNotReport(boolean) :   Whether test step is put to test report or not

            Returns True if navigating succeeded, False if not.
        """
        # get device information in order to know which product is under test
        deviceInfo = self.phone.deviceInfo(doNotReport = True)

        commentString = self._convertToReport(item)
        if doNotSelect == True:
            if fromRecent == True:
                raise Exception('Cannot use doNotSelect and fromRecent == True together!')
            commentString += ', doNotSelect'
        if fromRecent != None:
            commentString += ', fromRecent=%s' % str(fromRecent)
        if fromAppList != False:
            commentString += ', fromAppList=%s' % str(fromAppList)
        if fromLetterView != False:
            commentString += ', fromLetterView=%s' % str(fromLetterView)
        if fast != False:
            commentString += ', fast=%s' % str(fast)

        if not doNotReport:
            self.phone.comment('navigate(%s)' % commentString)

        node = None
        coords = None

        # don't search node if fromAppList or fromLetterView or fast is True and we are in my space
        if not ((fromAppList or fromLetterView or fast) and self.state.inMainMenu(timeout = 500, doNotReport = True)):
            node = self.phone.uiState._searchItem(item)

        # from recent apps functionality
        if fromRecent == True:
            if self.__fromRecent(item, fromRecent):
                # NOTE: Application already launched so returning
                return True
        elif fromRecent == False:
            self.__fromRecent(item, fromRecent)

        if node:
            coords = (int(node.getAttribute('center-x')), int(node.getAttribute('center-y')))
        else:
            # don't try to scroll node if fromAppList or fromLetterView or fast is True and we are in my space
            if not ((fromAppList or fromLetterView or fast) and self.state.inMainMenu(timeout = 500, doNotReport = True)):
                # try to scroll if node is not found
                # NOTE: fromLetterView and fast parameters delivered to scroll
                coords = self.phone._tab._scroll(unescape(item), fromLetterView=fromLetterView, fast=fast)

        # check that if we are in idle, swipe to app list and try again (ONLY FOR ARA)
        if not coords and self.phone.state.inMainMenu(timeout = 500, doNotReport = True) and \
            deviceInfo.has_key('ro.build.product') and deviceInfo['ro.build.product'] in self._supportedAoL2BuildProducts:
            if not fromAppList:           
                self.phone.comment('Swiping to app list and searching "%s" again...' % self._convertToReport(item))
            else:
                self.phone.comment('Swiping to app list and searching "%s"' % self._convertToReport(item))

            for i in range(5):
                self.phone._tab._backSwipe()

                if not self.phone.state.inMainMenu(timeout = 500, doNotReport = True):
                    break
                else:
                    if i == 4:
                        self.phone.fail('Swiping to app list failed in navigate!')
                    else:
                        self.phone.warn('Swiping to app list failed! Trying again...')
                        time.sleep(0.5)

            if not node:
                node = self.phone.uiState._searchItem(item)

            if node:
                coords = (int(node.getAttribute('center-x')), int(node.getAttribute('center-y')))
            else:
                # NOTE: fromLetterView and fast parameters delivered to scroll
                coords = self.phone._tab._scroll(unescape(item), fromLetterView=fromLetterView, fast=fast)

        if coords:
            if not doNotSelect:
                self.phone._touch.press(coords)
                self.phone._run('navigate()')

            return True
        else:
            self.phone.fail('Cannot navigate to %s, item not found!' % self._convertToReport(item))

            return False

    def __fromRecent(self, item, mode):
        """From recent apps functionality for navigate

            Parameters

            item (string)        :   Name of the item where to navigate
            mode (bool)          :   When True, application is launched from recent apps
                                     When False, application is removed from recent apps before navigate

            Returns True if execution succeeded, False if not
        """
        success = False

        try:
            self.phone.exit()
            self.phone.select.long('KEYCODE_BACK')

            # check recent apps layout type and use horizontal scroll with new layout
            self.phone._tab._getVisibleTexts()

            newLayout = False

            if self.phone._tab._currentDump and \
               self.phone._tab._currentDump.find('//node[@resource-id="com.android.systemui:id/delete_button"]'):
                newLayout = True

                textList = []

                for i in range(100):
                    try:
                        self.phone.getItem.description(item, area = (90, 190, 300, 500), doNotReport = True)
                    # exception means that item was not found
                    except Exception:
                        if not textList or textList != self.phone._tab._getVisibleTexts(returnAsDict = False):
                            textList = self.phone._tab._getVisibleTexts(returnAsDict = False)
                            self.phone._tab._backSwipe(reverse = True, light = True)
                        else:
                            break
                    else:
                        break

            if self.phone.check.description(item, doNotScroll = newLayout):
                if mode == True:
                    self.phone.comment('Launching "%s" from recent apps' % self._convertToReport(item))
                    self.phone.select.description(item)

                    success = True
                else:
                    self.phone.comment('Removing "%s" from recent apps' % self._convertToReport(item))

                    if newLayout:
                        self.phone.select.resourceId('com.android.systemui:id/delete_button')
                    else:
                        self.phone.select.long(item, withAttribute = 'description')
                        self.phone.select('Remove')

                    self.phone.exit()

                    success = True
            else:
                self.phone.comment('Cannot find "%s" from recent apps' % self._convertToReport(item))
                self.phone.exit()
        except Exception, err:
            # run exit in case of exception
            self.phone.exit()
            debug.err('Failure in navigate from recent: %s' % self._convertToReport(err))

        return success

    def __call__(self, item, doNotSelect=False, fromRecent=None):
        return self.navigate(item=item, doNotSelect=doNotSelect, fromRecent=fromRecent)

    @override
    def jump(self, item, fromRecent=None):
        """ Navigate using jump method.

            Parameters:
                item(string)         :   Name of the item to be launched
                fromRecent (bool)    :   When True, application is launched from recent apps if found
                                         When False, application is removed from recent apps before navigate
                                         When None, normal navigate is in use (default)
        """
        self.phone.comment('navigate.jump(%s)' % self._convertToReport(item))

        # from recent apps functionality
        if fromRecent == True:
            if self.__fromRecent(item, fromRecent):
                # NOTE: Application already launched so returning
                return True
        elif fromRecent == False:
            self.__fromRecent(item, fromRecent)

        if not self.phone._tab._navigateJump(item):
            self.phone.fail('navigate.jump(%s) failed' % self._convertToReport(item))

    def letter(self, item, doNotSelect=False, fromRecent=None):
        """ navigate.letter functionality
            NOTE: Cannot be in profile, because main code lies in tab _scroll.

            Parameters:
                item(string)         :   Name of the item
                doNotSelect (bool)   :   If set to True item is only scrolled to screen without selecting it
                fromRecent (bool)    :   When True, application is launched from recent apps if found
                                         When False, application is removed from recent apps before navigate
                                         When None, normal navigate is in use (default)

            Returns True if navigating succeeded, False if not.
        """
        commentString = self._convertToReport(item)
        if doNotSelect == True:
            commentString += ', doNotSelect'
        if fromRecent != None:
            commentString += ', fromRecent=%s' % str(fromRecent)
            
        self.phone.comment('navigate.letter(%s)' % commentString)
        
        # check that item's first letter is ascii. If not we must use navigate.search instead
        if not item[0] in string.ascii_uppercase:
            self.phone.comment('navigate.letter: first letter is not human readable --> using normal navigate instead!')
            return self.__navigate(item, doNotSelect = doNotSelect, fromRecent = fromRecent)
        else:
            return self.__navigate(item, doNotSelect = doNotSelect, fromRecent = fromRecent, fromLetterView = True, doNotReport = True)

    def fast(self, item, doNotSelect=False, fromRecent=None):
        """ navigate.fast functionality
            NOTE: Cannot be in profile, because main code lies in tab _scroll.

            Parameters:
                item(string)         :   Name of the item
                doNotSelect (bool)   :   If set to True item is only scrolled to screen without selecting it
                fromRecent (bool)    :   When True, application is launched from recent apps if found
                                         When False, application is removed from recent apps before navigate
                                         When None, normal navigate is in use (default)

            Returns True if navigating succeeded, False if not.
        """
        commentString = self._convertToReport(item)
        if doNotSelect == True:
            commentString += ', doNotSelect'
        if fromRecent != None:
            commentString += ', fromRecent=%s' % str(fromRecent)
            
        self.phone.comment('navigate.fast(%s)' % commentString)

        # check that item's first letter is ascii. If not we must use navigate.search instead
        if not item[0] in string.ascii_uppercase:
            self.phone.comment('navigate.fast: first letter is not human readable --> using normal navigate instead!')
            return self.__navigate(item, doNotSelect = doNotSelect, fromRecent = fromRecent)
        else:            
            return self.__navigate(item, doNotSelect = doNotSelect, fromRecent = fromRecent, fast = True, doNotReport = True)

    @override
    def random(self, item, fromRecent=None):
        """ navigate.random functionality defined in profile."""
        raise Exception('navigate.random not implemented in product profile!')

    @override
    def search(self, item, doNotSelect=False, fromRecent=None):
        """ navigate.search functionality defined in profile."""
        raise Exception('navigate.search not implemented in product profile!')

    @override
    def fromAppList(self, item, doNotSelect=False, fromRecent=None):
        """ navigate.fromAppList functionality defined in profile."""
        raise Exception('navigate.fromAppList not implemented in product profile!')


class Expect(_ScriptBase):
    """ Class to be used to verify status of screen objects

    """
    def __call__(self, params, timeout=None, occurrence=None, fromArea=None, refresh=True, checkedAttributes = None, doNotReport=False):
        """ Default expect functionality

        Parameters:
            params(string|list)                 List(or name of the single item) of items that are expected to be on the screen.
                                                Functionality can be reversed by leading exclamation mark(!). So this can be used
                                                to verify that something is not on screen.
            timeout(int)                        Wait timeout
            occurrence(int)                     Number of matches expected
            fromArea(tuple)                     X, Y, Width, Height
            refresh(bool)                       Whether dump is made or not
            checkedAttributes (string / list)   checked attribute string or list of checked attributes
                                                If multiple defined, returning first matching
                                                (default = None, self._checkedAttributes will be used)
            doNotReport(boolean)                Whether expect is put to test report or not
        """
        assert isinstance(occurrence, int) or occurrence==None, "Parameter occurrence must be of type int or None, got %s instead!" % type(occurrence)
        assert fromArea==None or isinstance(fromArea, tuple), \
            "Parameter fromArea must be tuple, got %s instead!" % type(fromArea)

        checkArea = False

        if not isinstance(params,type([])):
            params = [params]

        if timeout == None:
            timeout = core.FW_conf['settings'].System.ExpectTimeout

        time_t1 = time.time()
        currentItem = ""

        if not doNotReport:
            self.phone.comment('expect("%s")' % ', '.join(self._convertToReport(x) for x in params))

        while True:
            itemsFound = 0
            notFoundItemsList = []

            for itemName in params:
                currentItem = itemName[:]

                # Item is not expected
                if itemName.startswith("!") or (occurrence != None and occurrence < 1):
                    if itemName.startswith("!"):
                        itemName = itemName[1:]
                    if occurrence < 1:
                        occurrence = 1

                    result = self.phone.uiState._searchItem(itemName, checkedAttributes = checkedAttributes, area = fromArea, index = occurrence != None and occurrence or 0) == None

                    if result:
                        itemsFound += 1
                    else:
                        notFoundItemsList.append(currentItem)
                else:
                    result = self.phone.uiState._searchItem(itemName, checkedAttributes = checkedAttributes, area = fromArea, index = occurrence != None and occurrence or 0) != None

                    if result:
                        itemsFound += 1
                    else:
                        notFoundItemsList.append(currentItem)

            if itemsFound == len(params) or time.time() > time_t1 + timeout / 1000.0:
                result = bool(itemsFound == len(params))
                break

        if result == False:
            commentList = []

            for item in notFoundItemsList:
                strNot = ' not '
                if item.startswith("!"):
                    strNot = " "
                    item = item[1:]
                commentList.append('item "%s" is%sfound'%(item,strNot))

            commentString = ", ".join(commentList)

            if occurrence > 1:
                self.phone.fail('expect("%s") failed, %s %s times' % (', '.join(params), commentString, occurrence))
            elif fromArea != None:
                self.phone.fail('expect("%s") failed, %s within the area of "%s"' % (', '.join(params), commentString, fromArea))
            else:
                self.phone.fail('expect("%s") failed, %s' % (', '.join(params), commentString))

        return result

    def text(self, item, timeout=None, occurrence=1, fromArea=None, doNotReport=False):
        """ Method for checking texts

        Parameters:
            item(string)        :   Text to be checked
            timeout(int)        :   Wait timeout
            occurrence(int)     :   Number of matches expected
            fromArea(str|tuple) :   Image name or X, Y, Width, Height
            doNotReport(boolean):   Whether expect is put to test report or not
        """
        # if attribute is int, cast to string
        if type(item) == types.IntType:
            item = str(item)

        if not doNotReport:
            self.phone.comment('expect.text(%s)' % item)

        return self.__call__(item, timeout, occurrence=occurrence, fromArea=fromArea, checkedAttributes = 'text', doNotReport=True)

    def description(self, item, timeout=None, occurrence=1, fromArea=None, doNotReport=False):
        """ Expect item by content description.

        Parameters:
            item(string)        :   Content description to be expected
            timeout(int)        :   Wait timeout
            occurrence(int)     :   Number of matches expected
            fromArea(str|tuple) :   Image name or X, Y, Width, Height
            doNotReport(boolean):   Whether expect is put to test report or not
        """
        # if attribute is int, cast to string
        if type(item) == types.IntType:
            item = str(item)

        if not doNotReport:
            self.phone.comment('expect.description(%s)' % item)

        return self.__call__(item, timeout, occurrence=occurrence, fromArea=fromArea, checkedAttributes = 'content-desc', doNotReport=True)

    def indexTree(self, item, timeout=None, occurrence=1, fromArea=None, doNotReport=False):
        """ Expect item by index tree.

        Parameters:
            item(string)        :   Index tree to be expected
            timeout(int)        :   Wait timeout
            occurrence(int)     :   Number of matches expected
            fromArea(str|tuple) :   Image name or X, Y, Width, Height
            doNotReport(boolean):   Whether expect is put to test report or not
        """
        # if attribute is int, cast to string
        if type(item) == types.IntType:
            item = str(item)

        if not doNotReport:
            self.phone.comment('expect.indexTree(%s)' % item)

        return self.__call__(item, timeout, occurrence=occurrence, fromArea=fromArea, checkedAttributes = 'index', doNotReport=True)

    def resourceId(self, item, timeout=None, occurrence=1, fromArea=None, doNotReport=False):
        """ Expect item by resource id.

        Parameters:
            item(string)        :   Resource id to be expected
            timeout(int)        :   Wait timeout
            occurrence(int)     :   Number of matches expected
            fromArea(str|tuple) :   Image name or X, Y, Width, Height
            doNotReport(boolean):   Whether expect is put to test report or not
        """
        # if attribute is int, cast to string
        if type(item) == types.IntType:
            item = str(item)

        if not doNotReport:
            self.phone.comment('expect.resourceId(%s)' % item)

        return self.__call__(item, timeout, occurrence=occurrence, fromArea=fromArea, checkedAttributes = 'resource-id', doNotReport=True)

    def notification(self, item, bestBefore=10000, timeout=5000, doNotReport=False):
        """ Expects notification(s) to be displayed withing given timeout

        Parameters:
        item(string|list)      :   Item to be checked
        bestBefore(int)        :   From how far the notification occurance should be checked (default = 10000 ms)
        timeout(int)           :   Timeout for check (default = 50000 ms)
        doNotReport(boolean)   :   Whether test step is put to test report or not
        """
        if isinstance(item, str):
            item = [ item ]

        if not doNotReport:
            self.phone.comment('expect.notification(%s)' % ', '.join(item))

        assert isinstance(bestBefore, int), 'parameter bestBefore is of type %s, expected %s' % (type(bestBefore), int)
        assert isinstance(timeout, int), 'parameter timeout is of type %s, expected %s' % (type(timeout), int)

        if not self.phone.check.notification(item, bestBefore, timeout, doNotReport=True):
            notifications = self.phone._tab._getNotifications(bestBefore + timeout)
            self.phone.comment('Seen notifications:\n%s' % '\n'.join(notifications))
            if len(item) == 1:
                self.phone.fail('expect.notification(%s) failed, notification has not been seen' % item[0])
            else:
                self.phone.fail('expect.notification(%s) failed, notifications have not been seen' % ', '.join(item))

class NotExpect(_ScriptBase):
    """ Class used to check that some object is not on screen

    """
    def __handleParams(self, params):
        """Put exlamation mark to params so that we can use expect class."""
        if not isinstance(params,type([])):
            params = [params]

        newParams = []

        for name in params:
            if name.startswith("!"):
                newParams.append(name[1:])
            else:
                newParams.append("!"+name)

        return newParams

    def __call__(self, params, timeout=None, occurrence=None, fromArea=None, checkedAttribute = None, doNotReport=False):
        """ Use Expect-class to check that items in params are not on screen

        Parameters:
            params(string|list)                 List(or name of the single item) of items that are not expected to be on the screen.
            timeout(int)                        Wait timeout
            occurrence(int)                     Number of matches expected
            fromArea(tuple)                     X, Y, Width, Height
            checkedAttribute string             checked XML attribute
            doNotReport(boolean)                Whether expect is put to test report or not
        """
        assert checkedAttribute in self.phone.uiState._checkedAttributes or checkedAttribute == None, 'Wrong checkedAttribute given!'

        if not isinstance(params,type([])):
            params = [params]

        if not doNotReport:
            if checkedAttribute == 'content-desc':
                self.phone.comment('notExpect.description("%s")' % ', '.join(params))
            elif checkedAttribute == 'resource-id':
                self.phone.comment('notExpect.resourceId("%s")' % ', '.join(params))
            elif checkedAttribute == 'index':
                self.phone.comment('notExpect.indexTree("%s")' % ', '.join(params))
            elif checkedAttribute == 'text':
                self.phone.comment('notExpect.text("%s")' % ', '.join(params))
            else:
                self.phone.comment('notExpect("%s")' % ', '.join(params))

        # expect --> not expect with "!"
        params = self.__handleParams(params)

        self.phone.expect(params, timeout = timeout, occurrence = occurrence, checkedAttributes = checkedAttribute, doNotReport = True)

    def text(self, item, timeout=None, occurrence=1, fromArea=None, doNotReport=False):
        """ Method for not expecting texts

        Parameters:
            item(string)        :   Text to be checked
            timeout(int)        :   Wait timeout
            occurrence(int)     :   Number of matches expected
            fromArea(str|tuple) :   Image name or X, Y, Width, Height
            doNotReport(boolean):   Whether expect is put to test report or not
        """
        return self.__call__(item, timeout, occurrence=occurrence, fromArea=fromArea, checkedAttribute = 'text', doNotReport=doNotReport)

    def description(self, item, timeout=None, occurrence=1, fromArea=None, doNotReport=False):
        """ Not expect item by content description.

        Parameters:
            item(string)        :   Content description to be expected
            timeout(int)        :   Wait timeout
            occurrence(int)     :   Number of matches expected
            fromArea(str|tuple) :   Image name or X, Y, Width, Height
            doNotReport(boolean):   Whether expect is put to test report or not
        """
        return self.__call__(item, timeout, occurrence=occurrence, fromArea=fromArea, checkedAttribute = 'content-desc', doNotReport=doNotReport)

    def indexTree(self, item, timeout=None, occurrence=1, fromArea=None, doNotReport=False):
        """ Not expect item by index tree.

        Parameters:
            item(string)        :   Index tree to be expected
            timeout(int)        :   Wait timeout
            occurrence(int)     :   Number of matches expected
            fromArea(str|tuple) :   Image name or X, Y, Width, Height
            doNotReport(boolean):   Whether expect is put to test report or not
        """
        return self.__call__(item, timeout, occurrence=occurrence, fromArea=fromArea, checkedAttribute = 'index', doNotReport=doNotReport)

    def resourceId(self, item, timeout=None, occurrence=1, fromArea=None, doNotReport=False):
        """ Not expect item by resource id.

        Parameters:
            item(string)        :   Resource id to be expected
            timeout(int)        :   Wait timeout
            occurrence(int)     :   Number of matches expected
            fromArea(str|tuple) :   Image name or X, Y, Width, Height
            doNotReport(boolean):   Whether expect is put to test report or not
        """
        return self.__call__(item, timeout, occurrence=occurrence, fromArea=fromArea, checkedAttribute = 'resource-id', doNotReport=doNotReport)

    def notification(self, item, bestBefore=10000, timeout=5000, doNotReport=False):
        """ Expects notification(s) not to be displayed withing given timeout

        Parameters:
        item(string|list)      :   Item to be checked
        bestBefore(int)        :   From how far the notification occurance should be checked (default = 10000 ms)
        timeout(int)           :   Timeout for check (default = 50000 ms)
        doNotReport(boolean)   :   Whether test step is put to test report or not
        """
        if isinstance(item, str):
            item = [ item ]

        if not doNotReport:
            self.phone.comment('notExpect.notification(%s)' % ', '.join(item))

        assert isinstance(bestBefore, int), 'parameter bestBefore is of type %s, expected %s' % (type(bestBefore), int)
        assert isinstance(timeout, int), 'parameter timeout is of type %s, expected %s' % (type(timeout), int)

        if self.phone.check.notification(item, bestBefore, timeout, doNotReport=True):
            notifications = self.phone._tab._getNotifications(bestBefore + timeout)
            self.phone.comment('Seen notifications:\n%s' % '\n'.join(notifications))
            if len(item) == 1:
                self.phone.fail('notExpect.notification(%s) failed, notification has been seen' % item[0])
            else:
                self.phone.fail('notExpect.notification(%s) failed, notifications have been seen' % ', '.join(item))


class TryExpect(_ScriptBase):
    """ Check which one of the lists match the screen contents

    """
    def __call__(self, params, timeout=None, occurrence=None, fromArea=None, refresh=True, checkedAttribute = None, doNotReport=False):
        """ Default TryExpect functionality

        Parameters:
            params(list of lists)   :   List of lists containing possible screen contents
            timeout(int)            :   Wait timeout
            occurrence(int)         :   Number of matches expected
            fromArea(str|tuple)     :   Image name or X, Y, Width, Height
            checkedAttribute string :   checked XML attribute
            doNotReport(boolean)    :   Whether tryExpect is put to test report or not

        Return value is list containing indexes of list which matched the screen.
        """
        assert checkedAttribute in self.phone.uiState._checkedAttributes or checkedAttribute == None, 'Wrong checkedAttribute given!'

        if not doNotReport:
            if checkedAttribute == 'content-desc':
                self.phone.comment('tryExpect.description("%s")' % (isinstance(params,basestring) and params or ', '.join([self._convertToReport(x) for x in params])))
            elif checkedAttribute == 'resource-id':
                self.phone.comment('tryExpect.resourceId("%s")' % (isinstance(params,basestring) and params or ', '.join([self._convertToReport(x) for x in params])))
            elif checkedAttribute == 'index':
                self.phone.comment('tryExpect.indexTree("%s")' % (isinstance(params,basestring) and params or ', '.join([self._convertToReport(x) for x in params])))
            elif checkedAttribute == 'text':
                self.phone.comment('tryExpect.text("%s")' % (isinstance(params,basestring) and params or ', '.join([self._convertToReport(x) for x in params])))
            else:
                self.phone.comment('tryExpect("%s")' % (isinstance(params,basestring) and params or ', '.join([self._convertToReport(x) for x in params])))

        returnValue = []
        if isinstance(params,str):
            params = [params]

        assert type(params) == types.ListType, 'Invalid parameter given for tryExpect: %s' % self._convertToReport(params)

        if timeout==None:
            timeout=core.FW_conf['settings'].System.ExpectTimeout

        duration=time.time()

        while True:
            i = 0

            for l in params:
                expectResult = False

                try:
                    # NOTE: dump is taken only when i == 0
                    expectResult = self.phone.expect(l, timeout=0, occurrence=occurrence, fromArea=fromArea, refresh = i == 0 and True or False, checkedAttributes = checkedAttribute, doNotReport=True) #Use zero timeout because timeout is handled already
                except TestException:
                    # we can't stop on exceptions here
                    pass
                else:
                    # if result was True, add item index to list
                    if expectResult:
                        returnValue.append(i)

                i += 1

            # when we have found items or timeout exceeds, break away
            if len(returnValue) or time.time() > duration + timeout/1000.0:
                break

        return returnValue

    def text(self, item, timeout=None, occurrence=1, fromArea=None, doNotReport=False):
        """ Method for try expecting texts

        Parameters:
            item(string)        :   Text to be checked
            timeout(int)        :   Wait timeout
            occurrence(int)     :   Number of matches expected
            fromArea(str|tuple) :   Image name or X, Y, Width, Height
            doNotReport(boolean):   Whether expect is put to test report or not
        """
        return self.__call__(item, timeout, occurrence=occurrence, fromArea=fromArea, checkedAttribute = 'text', doNotReport=doNotReport)

    def description(self, item, timeout=None, occurrence=1, fromArea=None, doNotReport=False):
        """ Try expect item by content description.

        Parameters:
            item(string)        :   Content description to be expected
            timeout(int)        :   Wait timeout
            occurrence(int)     :   Number of matches expected
            fromArea(str|tuple) :   Image name or X, Y, Width, Height
            doNotReport(boolean):   Whether expect is put to test report or not
        """
        return self.__call__(item, timeout, occurrence=occurrence, fromArea=fromArea, checkedAttribute = 'content-desc', doNotReport=doNotReport)

    def indexTree(self, item, timeout=None, occurrence=1, fromArea=None, doNotReport=False):
        """ Try expect item by index tree.

        Parameters:
            item(string)        :   Index tree to be expected
            timeout(int)        :   Wait timeout
            occurrence(int)     :   Number of matches expected
            fromArea(str|tuple) :   Image name or X, Y, Width, Height
            doNotReport(boolean):   Whether expect is put to test report or not
        """
        return self.__call__(item, timeout, occurrence=occurrence, fromArea=fromArea, checkedAttribute = 'index', doNotReport=doNotReport)

    def resourceId(self, item, timeout=None, occurrence=1, fromArea=None, doNotReport=False):
        """ Try expect item by resource id.

        Parameters:
            item(string)        :   Resource id to be expected
            timeout(int)        :   Wait timeout
            occurrence(int)     :   Number of matches expected
            fromArea(str|tuple) :   Image name or X, Y, Width, Height
            doNotReport(boolean):   Whether expect is put to test report or not
        """
        return self.__call__(item, timeout, occurrence=occurrence, fromArea=fromArea, checkedAttribute = 'resource-id', doNotReport=doNotReport)


class Exit(_ScriptBase):
    """ Class to implement exit functionality

    """
    def __init__(self, phone):
        """
        Constructor
        """
        super(Exit,self).__init__(phone)
        # counter for exit failures
        self.__exitFailures = 0
        self.uiFreezeDetectionOngoing = False

    def __followerExit(self):
        """ Tries to secure the idle state in followers
        """
        raise Exception('MUST BE REIMPLEMENTED!')

        self.phone.select('KEYCODE_POWER', doNotReport=True)
        self.phone.delay(5000, False)
        self.phone.select('KEYCODE_POWER', doNotReport=True)
        self.phone.delay(1000, False)
        self.__backToIdleWithSwipe() # open screen lock
        self.phone.delay(1500, False)
        self.__backToIdleWithSwipe() # close application with swipe
        self.phone.delay(1000, False)

        self.__backToIdleWithBackPress(True) # if still in some application, this could close it
        self.phone.delay(500, False)
        self.__backToIdleWithBackPress() # return to idle screen top with 2 back press
        self.phone.delay(500, False)
        self.__backToIdleWithBackPress()
        self.phone.delay(2000, False)

    def _checkUiFreeze(self):
        """ check wether current situation is really a freeze """
        if not self.phone.isMain():
            return

        if self.uiFreezeDetectionOngoing:
            return

        try:
            self.uiFreezeDetectionOngoing = True

            self.phone.comment('Freeze detection')

            motionCountBefore = core.FW_conf['blackbox'].getCountMotionFrames()

            try:
                screenHeight = self.phone.uiState.getScreenHeight()
                screenWidth = self.phone.uiState.getScreenWidth()
            except Exception, err:
                debug.err('Freeze detection: Exception "%s" when reading screen dimensions' % str(err))
                screenHeight = screenWidth = None

            if not screenHeight or not screenWidth:
                self.phone.warn('Freeze detection: Cannot read screen dimensions for UI freeze check!')
                screenWidth = 480
                screenHeight = 800

            # swipe a bit to see if it causes motion
            self.phone.comment('Freeze detection: Drag screen a bit..')
            yCoordinate = int(screenHeight/1.5) # tab interface will catch any exceptions. returns hard-coded value if unable to get via device connection
            try:
                self.phone._touch.drawLine((screenWidth-2, yCoordinate), (screenWidth - 100, yCoordinate), stepSize = 30)
                self.phone._run('Move screen a bit to see is UI freezed', testStepReporting = False)
            except Exception, err:
                debug.err('Freeze detection: Exception "%s" when dragging screen' % str(err))

            if motionCountBefore == core.FW_conf['blackbox'].getCountMotionFrames():
                self.phone.comment('Freeze detection: no movement with swiping. SW type: %s' % self.phone._tab.swType)
                
                if core.FW_conf['graybox_enabled'] and not core.FW_conf['settings'].System.HWAssistedPowerKey:
                    self.phone.warn('Freeze detection: Trying to press KEYCODE_POWER via SW..')

                try:
                    self.phone.select('KEYCODE_POWER')
                    self.phone.delay(3000)
                    motionCountBefore = core.FW_conf['blackbox'].getCountMotionFrames() # screen lock might work, get motion count here
                    self.phone.select('KEYCODE_POWER')
                    self.phone.delay(3000)
                except:
                    self.phone.comment('Freeze detection: Failed to press keylock in %s mode' % (self.phone.isFullBlackBox() and 'full blackbox' or core.FW_conf['blackbox_enabled'] and 'blackbox' or 'whitebox'))

                if core.FW_conf['blackbox'].getCountMotionFrames() == motionCountBefore:

                    dumpCheckOk = self.phone.checkQCRamdumps(True)[0] # releases ramdump mode, which corresponds to a freeze. will wait movement with True parameter

                    if core.FW_conf['blackbox'].getCountMotionFrames() == motionCountBefore:

                        if core.FW_conf['should_stop']:
                            return

                        if self.phone._tab.swType != 'user':
                            # Check if systemui is running
                            try:
                                am = self.phone._tab._activityManager
                                activity = am.GetActivityByName('com.android.systemui')
                                if activity == None:
                                    self.phone.comment('Freeze check: com.android.systemui was not running')
                                else:
                                    self.phone.comment('Freeze check: com.android.systemui was running')
                            except Exception, e:
                                self.phone.comment('Unable to get process listing during UI freeze (%s)' % str(e.message))

                            if core.FW_conf['settings'].TestRun.CreateBugReportOnFailure:
                                self.phone.createBugReport()
                                self.phone._createBugReport = False # no need to create bug report after this point

                            # Force ram dump
                            try:
                                self.phone.comment('Freeze detected. Trying to force RAM dump mode..')
                                if core.FW_conf['settings'].TestRun.LoggingEnabled:
                                    self.phone._tab._addLogMarker('MARBLE: FORCE RAM DUMP MODE')
                                self.phone.shell("echo c> /proc/sysrq-trigger")
                                self.phone.delay(5000, False)
                                dumpCheckOk = self.phone.checkQCRamdumps(True)[0] # freeze=True so check will wait for UI movement
                            except Exception, ex:
                                self.phone.comment('Freeze detection: Could not force ram dump: %s' % str(ex.message))

                            if dumpCheckOk:
                                self.phone.fail('Forced RAM dump (UI Freeze detected with external camera)')
                                return

                        try:
                            if dumpCheckOk: # dump checking ok, no need to wait for dump generation
                                self.phone.resetPhone('UI Freeze detected with external camera')
                            else:
                                self.phone.resetPhone('UI Freeze detected with external camera', True)
                        finally:
                            self.phone.fail('UI Freeze detected with external camera')
                    else:
                        self.phone.comment('Motion detected, not a freeze. Continue..')
                else:
                    self.phone.comment('Motion after power key. Not a freeze. Continue..')
            else:
                self.phone.comment('Motion after swipe. Not a freeze. Continue..')

        except TestException:
            raise

        except TABInterfaceException as e:
            self.phone.resetPhone('UI Freeze detection rebooted phone because of serious connection problem (%s)' % e.message, True)

        except Exception as e: # if some operation raises exception (should not), catch it here.
            debug.err('UI Freeze detection exception: %s' % e.message)
            raise

        finally:
            self.uiFreezeDetectionOngoing = False

    def _isInIdle(self):
        """ Detect idle state via external video camera """
        if core.FW_conf['blackbox'].isVideoRecorderAvailable() and core.FW_conf['blackbox'].videoClient.GetCurrentState() == 'idle':
            self.inIdle = True
            return True
        else:
            return False

    def __fullBlackBoxExit(self):
        """ uses external video camera to detect idle state
            return True if Idle could be reached, otherwise False
        """
        if not core.FW_conf['blackbox'].isVideoRecorderAvailable():
            raise Exception('__fullBlackBoxExit: No video camera available. Check settings.')

        import sys
        sys.path.append('..')
        from override.Exit import ExitOverrides
        exitOverrides = ExitOverrides(self.phone)
        return exitOverrides.FullBlackBoxExit()
    
    @override
    def exit(self):
        return self.__exit()

    def __exit(self):
        """Goes to phone's main menu.

            Returns True if main menu was reached, False if not
        """
        
        self.phone.comment('self.exit()')
        
        # get device information in order to know which product is under test
        deviceInfo = self.phone.deviceInfo(doNotReport = True)

        # wake up the device
        if not self.phone.isLeader() and self.phone._tab._isServerAvailable() and self.phone._tab._isServerConnected():
            self.phone._tab._executeTabOperation(self.phone._tab._tabConn.TestServerClient.wakeUp)

        okPressCount = 0

        # NOTE: When changing range, remember to change home key pressing conditions!!!
        for i in range(12):
            # just return if test execution is stopping
            if core.FW_conf['should_stop']:
                return False

            NormandyAndroidPackage = False
            oldKeyguardFound = False
            newKeyguardFound = False
            glanceScreenFound = False
            keyguardStatusViewFound = False

            # ensure device state before running exit
            self.phone._tab._checkDeviceStatus()

            # ensure server connection before running exit
            self.phone._tab._connectServer()

            if not self.phone.state.inMainMenu(doNotReport = True):
                # don't press back in keyguard and FirstTimeUse
                if not self.phone._tab._currentDump or \
                    (self.phone._tab._currentDump and \
                    not self.phone._tab._currentDump.find('//node[@package="com.android.keyguard"]') and \
                    not self.phone._tab._currentDump.find('//node[@package="com.nokia.FirstTimeUse"]')):
                    self.phone._pressKey('KEYCODE_BACK', maximumDuration = 1000)
                    self.phone._run('back key press')

                try:
                    # get visible texts (refreshes also currentDump)
                    visibleTextDict = self.phone._tab._getVisibleTexts()
                except Exception:
                    # in case check fails to dump fetching
                    visibleTextDict = {}

                # set flag to False so that we will query screen dimensions from current application
                self.phone._tab._screenDimensionsQueried = False

                # if back has no effect, try back swipe with Ara
                if not self.phone.state.inMainMenu(timeout = 500, doNotReport = True) and \
                   deviceInfo.has_key('ro.build.product') and deviceInfo['ro.build.product'] in self._supportedAoL2BuildProducts and \
                   self.phone._tab._currentDump and \
                   self.phone._tab._currentDump.find('//node[@package="com.nokia.homescreen"]') and \
                   not self.phone._tab._currentDump.find('//node[@resource-id="com.nokia.homescreen:id/grid"]'):
                    if self.phone._tab._currentDump.find('//node[@class="android.widget.ExpandableListView"]'):
                        # reverse back swipe from application list
                        self.phone.swipe.viewSwipe(reverse = True)
                    else:
                        # FIXME: If fastlane goes to own package, create support for it instead of checking the class
                        # back swipe from fastlane
                        self.phone.swipe.viewSwipe()

                    # continue to next loop round
                    continue

                visibleTexts = []
                okOrCloseKeyPressed = False

                for textDict in visibleTextDict:

                    if textDict['text'] in ['Ok', 'OK', 'ok']:
                        okPressCount += 1

                    if textDict['text'] in ['Ok', 'OK', 'ok', 'close', 'Close', 'Continue', 'Done']:
                        self.phone._tab._touchWithCoords(textDict['center_x'], textDict['center_y'])
                        debug.brf('"%s" pressed in exit' % textDict['text'])
                        okOrCloseKeyPressed = True

                    if textDict['package'] == 'android':
                        NormandyAndroidPackage = True

                    if textDict['resource-id'] == 'android:id/key1':
                        oldKeyguardFound = True

                    if textDict['package'] == 'com.android.keyguard':
                        newKeyguardFound = True

                    if textDict['package'] == 'com.nokia.glancescreen':
                        glanceScreenFound = True

                    if textDict['resource-id'] == 'com.android.keyguard:id/keyguard_status_view':
                        keyguardStatusViewFound = True

                    # add visible text to a list
                    visibleTexts.append(textDict['text'])

                if okPressCount > 5: # if Ok pressed multiple times, time to try back few times
                    debug.brf('Ok pressed %s times, trying back presses..' % str(okPressCount))
                    for i in range(3):
                        self.phone._pressKey('KEYCODE_BACK')
                        self.phone._run('back key press')
                    okPressCount = 0
                    continue

                if okOrCloseKeyPressed:
                    # continue to next loop round
                    continue

                # 2.1 products: microsoft account in FirstTimeUse
                if self.phone._tab._currentDump.find('//node[@package="com.nokia.FirstTimeUse"]') and \
                    'Microsoft account' in visibleTexts:
                        if 'Sign in' in visibleTexts:
                            debug.brf('Press back to skip sign in..')
                            self.phone._pressKey('KEYCODE_BACK')
                            self.phone._run('back key press')
                        try:
                            self.phone.select('Yes', doNotReport=True)
                            debug.brf('"Yes" pressed to end signing in..')
                        except:
                            pass
                        continue

                # check do we have the whole keyguard keyboard visible
                if keyguardStatusViewFound and self.phone._tab._currentDump and \
                    self.phone._tab._currentDump.find('//node[@resource-id="com.android.keyguard:id/keyguard_pin_view"]') and \
                    self.phone._tab._currentDump.find('//node[@resource-id="com.android.keyguard:id/key9"]'):
                    keyguardStatusViewFound = False

                #debug.brf('NormandyAndroidPackage: %s' % NormandyAndroidPackage)
                #debug.brf('oldKeyguardFound: %s' % oldKeyguardFound)
                #debug.brf('newKeyguardFound: %s' % newKeyguardFound)
                #debug.brf('keyguardStatusViewFound: %s' % keyguardStatusViewFound)

                # Ara old keyguard
                if oldKeyguardFound:
                    for keyResId in ['android:id/key2', 'android:id/key0', 'android:id/key1', 'android:id/key4', 'android:id/key2', 'android:id/key6']:
                        self.phone._tab._touchWithResourceId(keyResId)

                    self.phone._tab._touchWithResourceId('android:id/key_enter') # press enter
                # Ara new keyguard
                elif newKeyguardFound:
                    if keyguardStatusViewFound:
                        # perform up swipe to get the keyguard keypad visible
                        self.phone.swipe.upSwipe()
                    else:
                        # clear previous code
                        if self.phone.check.resourceId('com.android.keyguard:id/delete_button', timeout = 0, doNotReport = True, doNotScroll = True):
                            self.phone.select.long('com.android.keyguard:id/delete_button', withAttribute = 'resourceId', doNotReport = True, doNotScroll = True)

                        # get the security code for the device
                        securityCode = None
                        try:
                            securityCode = eval("core.FW_conf['settings'].%s.SecurityCode" % self.getName())
                        finally:
                            if not securityCode or securityCode == '12345':
                                securityCode = '201426'

                        # input code
                        for d in securityCode:
                            self.phone.select.resourceId('com.android.keyguard:id/key%s' % d, doNotReport = True, doNotScroll = True, doNotWait = True)

                        if self.phone.check.resourceId('com.android.keyguard:id/key_enter', timeout = 0, doNotReport = True, doNotScroll = True):
                            self.phone.select.resourceId('com.android.keyguard:id/key_enter', doNotReport = True, doNotScroll = True)
                # Ara glance screen
                elif glanceScreenFound:
                    self.phone._pressKey('KEYCODE_POWER')
                    self.phone._run('power key press')
                # Normandy
                elif NormandyAndroidPackage or 'Enter security code' in visibleTexts:
                    if not 'Enter security code' in visibleTexts:
                        self.phone.swipe.viewSwipe()

                    if 'Enter security code' in self.phone._tab._getVisibleTexts(False):
                        self.phone.swipe.viewSwipe()
                        self.phone.input('201349')
                # Home key press with ara if nothing else helps
                elif not self.phone.state.inMainMenu(doNotReport = True) and \
                    deviceInfo.has_key('ro.build.product') and deviceInfo['ro.build.product'] in self._supportedAoL2BuildProducts and \
                    i > 5:

                    if i < 11:
                        self.phone.select('KEYCODE_HOME', doNotReport = True)
                        self.phone.comment('Home key pressed in exit in order to return to main menu')
                    # within two last iterations press long home
                    else:
                        self.phone.select.long('KEYCODE_HOME', doNotReport = True)
                        self.phone.warn('Long home key press in exit in order to return to main menu!')

                # wait that UI stabilizes before next loop round
                self.phone.state.wait(1000, doNotReport=True)
            else:
                # in setup phase press home key to ensure that we are not in my space's edit mode
                if core.FW_conf['current_testcase'] and core.FW_conf['current_testcase']._inSetUp:
                    self.phone.select('KEYCODE_HOME', doNotReport = True)
                    self.phone.comment('Home key pressed in exit when running setup')

                return True

        if not core.FW_conf['should_stop']:
            self.phone.warn('Unable to reach main menu!')

        return False

    def __call__(self):
        """ Default exit functionality

            Returns True if exit succeeds, False if not.
        """
        if self.phone.isLeader():
            core.FW_conf['leader'].sendTouches = False
            core.FW_conf['leader'].ExecuteString('self.follower.exit()')

        if self.phone.isFullBlackBox():
            self.phone.comment("Full BlackBox exit")
            if not self.__fullBlackBoxExit():
                self.phone.fail('Full blackbox exit failed')
            return
        
        e = None
        exitOk = False

        # ensure device state before running exit
        self.phone._tab._checkDeviceStatus()

        # ensure server connection before running exit
        self.phone._tab._connectServer()

        # wake up the device
        self.state.wakeUp()

        try:
            exitOk = self.exit()
        except Exception as e:
            exitOk = False # if exit failed due to unhandled exception (connection error etc), try to run ui freeze checking
        finally:

            if exitOk:
                self.__exitFailures = 0

            elif not exitOk:

                if not core.FW_conf['should_stop']:
                    self.warn('Unable to reach main menu!')

                self.__exitFailures += 1
                if e:
                    if not core.FW_conf['should_stop']:
                        self.phone.warn('Exception occurred in exit: "%s"' % str(e))

                if core.FW_conf['blackbox'].isVideoRecorderAvailable() and self.phone.isMain(): # if video recorder available, check UI Freeze
                    self._checkUiFreeze()
                    if self.phone.isLeader():
                        core.FW_conf['leader'].sendTouches = True

                if self.__exitFailures >= core.FW_conf['settings'].System.MaximumExitFailures:
                    self.phone.resetPhone('Exit failures reached the maximum: %s!' % core.FW_conf['settings'].System.MaximumExitFailures, True) # True: wait for ram dumps to generate

                if e:
                    raise e

            elif self.phone.isLeader():
                core.FW_conf['leader'].sendTouches = True

        return exitOk

class Input(_ScriptBase):
    """Class for inputing texts to phone."""
    def __init__(self, phone):
        """

        """
        super(Input,self).__init__(phone)
        self.blackBoxVkb = None
        self.vkb = None
        self.SPEED_NORMAL = 250
        self.SPEED_SLOW = 500
        self.SPEED_FAST = 0

    def __call__(self, text, defaultText='', failsafe=False, timeout=None, mode='Abc', orientation='portrait', delayBetweenPresses=None):
        """ Calls default input method.

        Parameters:
            text(string)        :   Text to be written
            defaultText(string) :   Text already in input field
            failsafe(bool)      :   If set to true failsafe method is used(much slower)
            timeout(int)        :   Wait timeout
            mode(string)        :   Mode to be used in blackbox input
            orientation(string) :   Orientation to be used in blackbox input
            delayBetweenPresses :   Delay between each keypress (BlackBox mode)
        """
        if len(text):
            if self.phone.isFullBlackBox() or self.phone.isLeader() or self.phone.isFollower(): # input using hardcoded settings
                if self.blackBoxVkb == None:
                    self.blackBoxVkb = BlackBoxVirtualKeyboard(self.phone)
                self.blackBoxVkb._writeBlackBox(text, mode=mode, orientation=orientation, delayBetweenPresses=delayBetweenPresses)
            else:
                # NOTE: default input mode when using TAB is push
                self.push(text)
        else:
            self.phone.comment("Empty string given for input!")

    def write(self, text, defaultText='', failsafe=False, timeout=None, mode='Abc', orientation='portrait', delayBetweenPresses=None, typingDelay=None):
        """ Write using virtual keyboard

        Parameters:
            text(string)        :   Text to be written
            defaultText(string) :   Text already in input field
            failsafe(bool)      :   If set to true failsafe method is used(much slower)
            timeout(int)        :   Wait timeout
            mode(string)        :   Mode to be used in blackbox input
            orientation(string) :   Orientation to be used in blackbox input
            delayBetweenPresses :   Delay between each keypress (BlackBox mode)
            typingDelay         :   Delay between each keypress (WhiteBox mode)
        """
        if not (self.phone.isFullBlackBox() or self.phone.isLeader() or self.phone.isFollower()):
            if self.vkb == None:
                self.vkb = VirtualKeyboard()
                self.vkb.setPhone(self.phone)
            if typingDelay == None:
                typingDelay == self.SPEED_NORMAL
            try:
                self.vkb.waitForVKB(timeout)
            except TestException as ex:
                self.phone.warn("Exception occured while waiting for virtual keyboard:%s\nUsing input.push."%str(ex))
                self.push(text)
            else:
                self.phone.comment('input.write(%s)' % self._convertToReport(text))
                self.vkb._write(text, defaultText, timeout, typingDelay)
                self.vkb._resetVKB()

        else:
            if self.blackBoxVkb == None:
                self.blackBoxVkb = BlackBoxVirtualKeyboard(self.phone)
            self.blackBoxVkb._writeBlackBox(text, mode=mode, orientation=orientation, delayBetweenPresses=delayBetweenPresses)

    def push(self, text):
        """Pushes the given string to focused text field

        Parameters:
            text(string)            :   Text to be pushed to input field
        """
        self.phone.comment('input.push(%s)' % self._convertToReport(text))
        assert not self.phone.isLeader(), 'Leader mode and follower cannot push text!'
        self.phone._tab.input(text)

    def hide(self, timeout=1000):
        """ Hides virtual keyboard if it is visible.

            returns : True if virtual keyboard was on screen and was closed,
                      False if virtual keyboard was not visible.
        """

        self.phone.comment('input.hide()')
        returnValue = None

        startTime = time.time()

        while returnValue== None:
            if (time.time()-startTime) > (timeout/1000.0):
                returnValue =  False

            elif self.phone._tab._tabConn.TestServerClient.Keyboard and self.phone._tab._tabConn.TestServerClient.Keyboard.KeyboardOn:

                self.phone._pressKey('KEYCODE_BACK', None)
                self.phone._run('Hide virtual keyboard')

                returnValue = True
            else:
                time.sleep(0.1)

        return returnValue


class Clear(_ScriptBase):
    """Class for clearing texts from phone."""
    def __init__(self, phone):
        """

        """
        super(Clear,self).__init__(phone)
        self.blackBoxVkb = None
        self.clearButtonCoords = None

    def __call__(self, number=0, time=3):
        """ Calls default input method. """

        if self.phone.isFullBlackBox():
            if not self.blackBoxVkb:
                self.blackBoxVkb = BlackBoxVirtualKeyboard(self.phone)
            self.blackBoxVkb.clear(time=time)
            return

        assert not self.phone.isLeader(), 'default clear is not allowed in Leader mode. Use clear.backspace instead!'

        self.phone.comment('clear(%s)' % (number != 0 and str(number) or ""))
        # use backspace clear when using TAB
        self.backspace(number, doNotReport = True)

    def backspace(self, number=0, doNotReport = False):
        """ Clear text using backspace-button in virtual keyboard

        Parameters:
            number(int or string) :   Number of times to press backspace or string 'all' to clear all
        """
        # read bb keyboard settings to get clear key coordinates
        if self.phone.isBlackBox():
            if not self.blackBoxVkb:
                self.blackBoxVkb = BlackBoxVirtualKeyboard(self.phone)
            self.blackBoxVkb._loadVkbSettings()
            self.blackBoxVkb._loadCoords('portrait', 'Abc')
            self.clearButtonCoords = tuple(self.blackBoxVkb.coords['backspace'])

        if self.phone.isFullBlackBox():
            self.blackBoxVkb.backspace(times=number)
            return

        if not doNotReport:
            self.phone.comment('clear.backspace(%s)' % (number != 0 and str(number) or ""))

        if self.phone.isBlackBox():
            assert self.clearButtonCoords != None, 'Cannot touch clear, no keyboard coordinates loaded'
            self.phone._tab._clear(number, self.clearButtonCoords)
        else:
            self.phone._tab._clear(number)


class Back(_ScriptBase):
    """Class for back stepping."""
    def __call__(self, count = 1):
        """Executes default back stepping.

        Parameters:
            count(int)  :   times to press back-key
        """
        assert type(count) == types.IntType and count >= 1, \
               'Invalid count value (%s) given!' % count

        self.phone.comment('back(%s)' % (count != 1 and str(count) or ""))

        for i in range(count):
            self.phone._pressKey('KEYCODE_BACK', None)
        self.phone._run('Back key pressing %s times' % str(count))

    def long(self):
        """Executes long back step."""
        self.phone.comment('back.long()')
        self.phone._pressKey('KEYCODE_BACK', length = 1500)
        self.phone._run('Long back key press')


class Home(_ScriptBase):
    """Class for home stepping."""
    def __call__(self):
        """Executes default home stepping."""
        self.phone.comment('home()')

        self.phone._pressKey('KEYCODE_HOME', None)
        self.phone._run('Home key press')


class Read(_ScriptBase):    
    """Class for reading screen items"""
    def __call__(self, searchString=None, area=None, doNotReport=False, fullInfo=False, checkedAttribute = 'text', refreshDump=True):
        """Executes read screen

        Read returns list of screen items

        Parameters:
            searchString (str)     :  Optional string containing wildcard(s). Only items matching this will be returned
            area(4-tuple of ints)  :  Area x,y,w,h where text is read from
            doNotReport(boolean)   :  Whether test step is put to test report or not
            fullInfo(boolean)      :  Provide also coordinate information
            checkedAttribute       :  XML attributes which will be checked

        Return:
            List of strings | List of tuples
        """
        assert isinstance(area, tuple) or area == None or area == 'full', 'Given area needs to be tuple of 4 integers!'
        if searchString != None:
            assert "*" in searchString or "?" in searchString or ("[" in searchString and "]" in searchString), 'Given searchString does not contain any wildcards'

        if not doNotReport:
            self.phone.comment('read(%s)' % ','.join([searchString != None and self._convertToReport(searchString) or '',
                                                      area != None and str(area) or '',
                                                      fullInfo != False and 'True' or '']).strip(','))

        # by default, use visible screen area as area.
        if area == None:
            area = (0,0,self.phone.uiState.getScreenWidth(), self.phone.uiState.getScreenHeight())

        foundItems = []
        nodes = self.phone.uiState._findNodes(None, checkedAttributes = checkedAttribute, area = area,useExistingDump=not(refreshDump))

        if isinstance(checkedAttribute, str):
            checkedAttribute = [ checkedAttribute ]

        for node in nodes:
            for attribute in checkedAttribute:
                item = node.getAttribute(attribute)

                # Skip empty items and items that don't match the given filter string
                if not item or searchString != None and not fnmatch.fnmatch(item, searchString):
                    continue

                if fullInfo:
                    item = (item, (int(node.getAttribute("left")), int(node.getAttribute("top")), int(node.getAttribute("right")), int(node.getAttribute("bottom"))))
                foundItems.append(item)

        if not doNotReport:
            self.phone.comment('Screen contents read, %s items found' % len(foundItems))

        return foundItems

    def text(self, searchString=None, area=None, fullInfo=False, refreshDump=True, doNotReport=False):
        """ Return screen items which have text """
        if not doNotReport:
            self.phone.comment('read.text(%s)' % ','.join([searchString != None and self._convertToReport(searchString) or '',
                                                       area != None and str(area) or '',
                                                       fullInfo != False and 'True' or '']).strip(','))

        return self.__call__(searchString, area, doNotReport=True, fullInfo=fullInfo, checkedAttribute = 'text', refreshDump=refreshDump)

    def description(self, searchString=None, area=None, fullInfo=False, refreshDump=True, doNotReport=False ):
        """ Return screen items which have description """
        if not doNotReport:
            self.phone.comment('read.description(%s)' % ','.join([searchString != None and self._convertToReport(searchString) or '',
                                                              area != None and str(area) or '',
                                                              fullInfo != False and 'True' or '']).strip(','))

        return self.__call__(searchString, area, doNotReport=True, fullInfo=fullInfo, checkedAttribute = 'content-desc', refreshDump=refreshDump)

    def indexTree(self, searchString=None, area=None, fullInfo=False, refreshDump=True, doNotReport=False):
        """ Return screen items which have index tree """
        if not doNotReport:
            self.phone.comment('read.indexTree(%s)' % ','.join([searchString != None and self._convertToReport(searchString) or '',
                                                            area != None and str(area) or '',
                                                            fullInfo != False and 'True' or '']).strip(','))

        return self.__call__(searchString, area, doNotReport=True, fullInfo=fullInfo, checkedAttribute = 'index', refreshDump=refreshDump)

    def resourceId(self, searchString=None, area=None, fullInfo=False, refreshDump=True, doNotReport=False):
        """ Return screen items which have resource id """
        if not doNotReport:
            self.phone.comment('read.resourceId(%s)' % ','.join([searchString != None and self._convertToReport(searchString) or '',
                                                             area != None and str(area) or '',
                                                             fullInfo != False and 'True' or '']).strip(','),)

        return self.__call__(searchString, area, doNotReport=True, fullInfo=fullInfo, checkedAttribute = 'resource-id', refreshDump=refreshDump)

    def className(self, searchString=None, area=None, fullInfo=False, refreshDump=True, doNotReport=False):
        """ Return screen items which have resource id """
        if not doNotReport:
            self.phone.comment('read.className(%s)' % ','.join([searchString != None and self._convertToReport(searchString) or '',
                                                             area != None and str(area) or '',
                                                             fullInfo != False and 'True' or '']).strip(','),)

        return self.__call__(searchString, area, doNotReport=True, fullInfo=fullInfo, checkedAttribute = 'class', refreshDump=refreshDump)

    def notifications(self, searchString='', bestBefore=5000, doNotReport=False):
        """
        Gets all the notifications that have been displayed in the last five seconds.

        Parameters:
        searchString    str     filters notifications according to this string
        bestBefore      int     defines time (ms) how far back from the current time notifications are fetched

        Returns list of tuples (datetime timestamp, str notification text)
        """
        if not doNotReport:
            self.phone.comment('read.notifications(%s)' % ', '.join([searchString != None and self._convertToReport(searchString) or '',
                                                             bestBefore != 5000 and str(bestBefore) or '']).strip(', '),)

        assert isinstance(searchString, str), 'parameter searchString is of type %s, expected %s' % (type(searchString), str)
        assert isinstance(bestBefore, int), 'parameter bestBefore is of type %s, expected %s' % (type(bestBefore), int)

        notifications = self.phone._tab._getNotifications(bestBefore, includeTimeStamp=True)
        if not searchString:
            return notifications

        filtered = []
        for notification in notifications:
            if fnmatch.fnmatch(notification[1], searchString):
                filtered.append(notification)

        return filtered


class TimePicker(_ScriptBase):
    """ Class for selecting time from time picker"""

    def __init__(self, phone):
        """Initialize test case instance for class."""

        super(TimePicker,self).__init__(phone)

        # relative picker lenghts, will be mapped to screen width, e.g 480 pixels
        self.hPickerUnit = 0.152083333
        self.mPickerUnit = 0.322916667

        self.__UIEventThread = None
        self.is12HourFmt = None

    def __getMinutesAngle(self, minutes):
        """ Returns angle to given minute value. xx:15 minutes treated as 0 angle
        """
        if minutes > 45:
            angle = - math.radians((60-minutes) * 6 + 90)
        else:
            angle = math.radians(minutes * 6 - 90)
        return angle

    def __getHoursAngle(self, hours):
        """ Returns angle to given minute value. 03:xx treated as 0 angle
        """
        if hours > 9:
            angle = - math.radians((12-hours) * 30 + 90)
        else:
            angle = math.radians(hours * 30 - 90)
        return angle

    def __getPickerCenter(self):
        """ The position of the timepicker center
            Return
                (int, int)  :   if picker found, otherwise None
        """

        cx, cy = None, None
        pickerResourceIds = ['com.nokia.alarmclock:id/alam_picker', 'android:id/timePicker']

        for rId in pickerResourceIds:
            pickerNodes = self.phone._tab._getDump().findall('//node[@resource-id="%s" and @class="android.view.View"]' % rId)
            if pickerNodes:
                for node in pickerNodes:
                    bounds = self.phone._tab._getCoordsFromBounds(node.getAttribute('bounds'))
                    cx, cy = self.phone._tab._getCenterCoordsFromBoundCoords(bounds)
                    break

        return cx, cy

    def __getPickerLengths(self, orientation):
        """ get the distance from picker center to hour and minute picker
            Params
                orientation (string)    :     orientation of phone. 'portrait' or 'landscape'
            Return
                (int),(int) : distance of hourpicker, distance of minutepicker
        """
        mPickerLen, hPickerLen = None, None

        if orientation == 'portrait':
            m = self.phone._tab.getScreenWidth()
        elif orientation == 'landscape':
            m = self.phone._tab.getScreenHeight()
        else:
            debug.err('unknown orientation: %s' % orientation)
            return None, None

        mPickerLen = int(m * self.mPickerUnit)
        hPickerLen = int(m * self.hPickerUnit)

        return mPickerLen, hPickerLen

    def __getTimeFromScreen(self):
        """ read screen labelnodes and return found time
            Return
                (int, int)  :  hours (always in 24 hour format), minutes
        """
        maxAttemps = 10
        h, m = None, None

        for i in range(maxAttemps):
            labelNodes = self.phone._tab._getDump().findall('//node[@class="android.widget.TextView"]')
            for node in labelNodes:
                timeOnScreen = node.getAttribute('text')
                try:
                    if self.is12HourFmt:
                        parsedTime = time.strptime(timeOnScreen,"%I:%M %p")
                    else:
                        parsedTime = time.strptime(timeOnScreen,"%H:%M")
                        
                    h = parsedTime[3]
                    m = parsedTime[4]

                except:
                    pass

            if h != None and m != None:
                return h, m

        if h == None or m == None:
            self.phone.fail("pickTime: Could not read time from screen")

    def __getPickerLocations(self, pickersBackgroundCoords, currentTime, orientation):
        """ Return coordinates of minute and hour picker center coordinates on given time

            Params:
                pickersBackgroundCoords  (tuple of ints)    :    center coordinates of picker background. If not given, tries to fetch them
                currentTime (tuple of ints)                 :    current time in (hour, minute)
                orientation (string)                        :    phone orientation. 'portrait' or 'landscape'

            Return
                ((int, int), (int, int))    :     (minute center coords), (hour center coords)
                or None if not found
        """

        mLocationX, mLocationY, hLocationX, hLocationY = None, None, None, None
        h, m = currentTime
        cx, cy = pickersBackgroundCoords

        mLen, hLen = self.__getPickerLengths(orientation)
        if mLen and hLen:
            mLocationX = int(cx + mLen * math.cos(self.__getMinutesAngle(m)))
            mLocationY = int(cy + mLen * math.sin(self.__getMinutesAngle(m)))
            hLocationX = int(cx + hLen * math.cos(self.__getHoursAngle(h)))
            hLocationY = int(cy + hLen * math.sin(self.__getHoursAngle(h)))

        #debug.brf('minutepicker location %s, %s' % (mLocationX,mLocationY))
        #debug.brf('hourpicker location %s, %s' % (hLocationX,hLocationY))

        return (mLocationX, mLocationY), (hLocationX, hLocationY)

    def __getCirclePoints(self, center, from_point, to_angle, interval):
        """ getCirclePoints will calculate points on a circle path

        Parameters:
            center (tuple of ints)                  : x/y coordinate from circle center
            from_point (tuple of ints)              : x/y coordinate from starting point where to start circle path
            to_angle (angle in radians)             : angle where the path will be drawn
            interval (interval angle in degrees)    : interval how many degrees there will be between the calculated points
        """

        # radius is needed for calculating the points
        radius = math.sqrt( math.pow((center[0] - from_point[0]),2) + math.pow(center[1]-from_point[1],2) )

        # get current angle from from_point. x,y: 1,0 = zero angle, 0,1 = -pi/2, -1,0 = pi, 0,1 as pi/2
        if (from_point[0] < center[0] and from_point[1] > center[1]): # angles in lower left quarter
            angle = math.pi - math.asin( (-(center[1] - from_point[1]) )/ radius )
        elif (from_point[0] < center[0] and from_point[1] <= center[1]): # angles in upper left
            angle = -math.pi - math.asin( (-(center[1] - from_point[1]) )/ radius )
        else:
            angle = math.asin( (-(center[1] - from_point[1]) )/ radius )

        # debug.brf("from angle deg: %s to_angle deg: %s" % (math.degrees(angle), math.degrees(to_angle)))

        interval = math.radians(interval)

        points = []  # starting point
        points.append(from_point)

        # flag of direction the 'motion' goes to
        clockwise = False
        anticlockwise = False

        for i in range(60): # 60 points is the maximum

            if angle < to_angle:  # if to_angle is bigger, length to clockwise direction is absolute value from to_angle substracted from current angle modulus the whole circle
                len_cw = math.fabs(angle - to_angle) % (2 * math.pi)
                len_acw = 2 * math.pi - math.fabs(len_cw)
            else:                 # same as above, but anticlockwise
                len_acw = math.fabs(angle - to_angle) % (2 * math.pi)
                len_cw = 2 * math.pi - math.fabs(len_acw)

            if len_cw > len_acw:
                # turn anticlockwise
                anticlockwise = True
                if clockwise == True:  # if clockwise turns have been done, then no direction changing needed. break point drawing
                    break

                angle = angle - interval

            else:
                # turn clockwise
                clockwise = True
                if anticlockwise == True:  # if anticlockwise turns have been done, then no direction changing needed. break point drawing
                    break

                angle = angle + interval

            # calculate x/y to current angle
            x = int(round(radius*math.cos(angle) + center[0]))
            y = int(round(radius*math.sin(angle) + center[1]))
            points.append( (x,y) )

            # debug.brf("angle %s (%s,%s) remainding: %s (deg: %s)" % (str(math.degrees(angle)), x, y, str(angle - to_angle), str(math.degrees(angle-to_angle))))

        # append still the last wanted point to get accurate
        x = int(math.ceil(radius*math.cos(to_angle) + center[0]))
        y = int(math.ceil(radius*math.sin(to_angle) + center[1]))
        points.append( (x,y) )

        # debug.brf("points %s" % points)
        return points

    def __call__(self, hours=None, minutes=None):
        """ Executes timepicker functionality
            Supports setting 24h and 12h modes. If minute or hour cannot be set, execution will fail the case.

        Parameters:
            hours(int)      :   Hour to be selected in 24 hour clock (if system time is 12 hours, 00 is 12am, 23:59 is 11:59pm etc
            minutes(int)    :   Minute to be selected
        """
        self.is12HourFmt = False
        try:
            self.is12HourFmt = True if self.phone.sql.executeCommand('/data/data/com.android.providers.settings/databases/settings.db', "select value from 'system' where name='time_12_24'") == '12' else False
        except:
            pass

        if hours != None:
            assert hours >= 0 and hours <= 23, "Hours are not between 0 and 23"

        if minutes != None:
            assert int(minutes) >= 0 and int(minutes) <=59, "Minutes are not between 0 and 59"

        if hours != None and minutes != None:
            self.phone.comment('pickTime(%02d:%02d)' % (hours, minutes))
        elif hours != None:
            self.phone.comment('pickTime(%02d:xx)' % hours)
        elif minutes != None:
            self.phone.comment('pickTime(xx:%02d)' % minutes)

        # angle interval in degrees, affects how many points are calculated to circle.
        hour_interval = 5
        minute_interval = 10

        msg = ""
        pickerTableCenter = None, None
        delay=1 # delay between points in touch drawShape
        min = None, None  # minute picker coordinates
        hour = None, None # hour picker coordinates
        minutes_set = False
        orientation = self.phone.orientation()

        for i in range(4):  # try getting time picker icons 4 times
            # FIXME: Use event approach instead

            if pickerTableCenter[0] == None:
                 pickerTableCenter = self.__getPickerCenter()

            if not pickerTableCenter[0]:
                msg = "timepicker center not visible"
                continue

            currentTime = self.__getTimeFromScreen()
            if currentTime[0] == None or currentTime[1] == None:
                msg = 'could not read time from screen'
                continue

            min, hour = self.__getPickerLocations(pickerTableCenter, currentTime, orientation)
            if not min[0] or not hour[0]:
                msg = 'could not get locations of time pickers'
                continue

            if minutes != None:
                if minutes == currentTime[1]:
                    minutes_set = True

            break

        if not msg == "":
            self.phone.fail(msg)

        success = False

        if minutes != None and not minutes_set :
            attemps = 10
            angle_adjust = 0.07 # hard-coded adjustment to angle

            for i in range(attemps): # try to get to correct few times

                steps = self.__getCirclePoints(pickerTableCenter, min, self.__getMinutesAngle(minutes)+angle_adjust, minute_interval)
                self.phone._touch.drawShape( steps, delay=delay )
                self.phone._Phone__purgeKeyPresses()

                currentTime = self.__getTimeFromScreen()

                if minutes == currentTime[1]:
                    success = True
                    break

                # minute picker was not on correct position
                rand = random.randint(2,5)   # move time picker a random amount anticlockwise from current minutes
                if minutes > rand:
                    temp = minutes - rand
                else:
                    temp = (60-rand) + minutes

                if i == attemps-1: # if this was the last attemp, break the loop
                    break
                elif i == 5: # change adjust to normal if problems
                    angle_adjust = 0
                elif i > 5:  # try adjusting
                    angle_adjust = angle_adjust + 0.05

                debug.out("Could not set minutes to %s" % minutes)

                currentTime = self.__getTimeFromScreen()
                min, hour = self.__getPickerLocations(pickerTableCenter, currentTime, orientation)

            if not success:
                self.phone.fail("pickTime: Could not get minutes set")
            success = False

        if hours != None:

            attemps = 10
            angle_adjust = 0.4 # hard-coded adjustment to angle

            for i in range(attemps): # try to get to correct time few times

                steps = self.__getCirclePoints(pickerTableCenter,hour,(self.__getHoursAngle(hours) + angle_adjust),6)
                self.phone._touch.drawShape( steps , delay=delay)
                self.phone._Phone__purgeKeyPresses()

                currentTime = self.__getTimeFromScreen()
                min, hour = self.__getPickerLocations(pickerTableCenter, currentTime, orientation)
                if currentTime[0] == hours:
                    success = True
                    break

                test = []

                if self.is12HourFmt:
                    test.append('%02d' % ((hours-1+12) % 12))
                    test.append('%02d' % (hours))
                    test.append('%02d' % ((hours+1) % 12))
                else:
                    test.append('%02d' % ((hours-1+24) % 24))
                    test.append('%02d' % (hours))
                    test.append('%02d' % ((hours+1) % 24))

                if not self.is12HourFmt:
                    temp_h = (hours + 12) % 24  # test also whether hour picker needs to be turned 360 degrees to get correct time
                    test.append('%02d' % (temp_h-1))
                    test.append('%02d' % (temp_h))
                    test.append('%02d' % (temp_h+1))

                if '%02d' % currentTime[0] in test:

                    if test.index('%02d' % currentTime[0]) == 4:  # 24 hour format, picker needs to be turned 360 degrees over

                        # divide in 3 steps (getCirclePoints returns shortest path)
                        steps = self.__getCirclePoints(pickerTableCenter, steps[-1], self.__getHoursAngle((hours + 4) % 24), hour_interval)
                        self.phone._touch.drawShape( steps , delay=delay )

                        steps = self.__getCirclePoints(pickerTableCenter, steps[-1], self.__getHoursAngle((hours + 8) % 24), hour_interval)
                        self.phone._touch.drawShape( steps , delay=delay)

                        steps = self.__getCirclePoints(pickerTableCenter, steps[-1], (self.__getHoursAngle(hours) + angle_adjust), hour_interval)
                        self.phone._touch.drawShape( steps , delay=delay)
                        self.phone._Phone__purgeKeyPresses()

                        # read time after picker moving
                        currentTime = self.__getTimeFromScreen()
                        min, hour = self.__getPickerLocations(pickerTableCenter, currentTime, orientation)

                    if '%02d' % currentTime[0] in test and test.index('%02d' % currentTime[0]) == 1: # index 1 == exact hour was found, no need to adjust
                        success = True
                        break

                if i == attemps-1: # this was final attemp, break the loop
                    break
                elif i == 5: # change adjust to normal if problems
                    angle_adjust = 0
                elif i > 5:  # try adjusting
                    angle_adjust = angle_adjust + 0.3

                debug.out("Could not set hour to %s" % hours)

                currentTime = self.__getTimeFromScreen()
                min, hour = self.__getPickerLocations(pickerTableCenter, currentTime, orientation)

            if not success:
                self.phone.fail("pickTime: Could not get hours set")
            success = False


class DatePicker(_ScriptBase):
    """ Class for selecting date from date picker"""
    def __init__(self, phone):
        """Initialize test case instance for class."""
        super(DatePicker,self).__init__(phone)
        self.months = {}

        for k, v in enumerate(calendar.month_abbr):
            try:
                self.months[v] = int(k)
            except:
                pass

    def _readCurrentDate(self, state=None):
        """ state as complete xml dump. returns found date as date object or None """
        if not state:
            state = self.phone._tab._getDump()

        for node in state.findall('//node[@resource-id="android:id/chooseDate"]'):
            debug.out('date text node: %s' % node.getAttribute('text'))
            try:
                dt = DateTime.TryParse(node.getAttribute('text'))
                if len(dt) == 2 and dt[0]:
                    return date(dt[1].Year, dt[1].Month, dt[1].Day)

            except:
                pass

        return None

    def __getDateFormat(self, picker_nodes):
        """ analyze current date format from time pickers
            Param
                picker_nodes (list of NodeUtils)    :    timepicker nodes containing picker texts
            Return
            (int, int, int)     :      index number of year, month and day of given picker nodes
        """

        year, month, day = -1, -1, -1

        for i in range(len(picker_nodes)):
            textNodes = picker_nodes[i].findall('./node[@text]')
            for t in textNodes:
                pickerValue = 0
                try:
                    pickerValue = int(t.getAttribute('text')) # try converting to date number
                except:
                    if self.months.has_key(t.getAttribute('text')): # if could not convert to number, try getting from months dictionary
                        try:
                            pickerValue = self.months[t.getAttribute('text')]
                            month = i # if value is found from months dictionary, this picker is month picker for sure
                            break
                        except:
                            pass

                if not pickerValue:
                    break

                if pickerValue > 31:
                    year = i
                    break

                elif pickerValue > 12 or (pickerValue <= 31 and month != -1): # this picker needs to be day
                    day = i
                    break

                elif day != -1 and pickerValue <= 12:
                    month = i
                    break

                elif month != -1 and pickerValue > 0 and pickerValue <= 31:
                    day = i
                    break

                debug.out('could not determine %s' % pickerValue)

        if (year, month, day).count(-1) == 1: # one missing, fill in
            missedIndex = (year, month, day).index(-1)
            missing = set((2,1,0)).difference((year, month, day)).pop()
            temp = list((year, month, day))
            temp[missedIndex] = missing
            year, month, day = temp[0], temp[1], temp[2]

        return year, month, day

    def __getCenterNodeIndex(self, node):
        """ determine the center node index from given pickernode """

        textNodes = node.findall('./node[@text]')

        if len(textNodes) == 0:
            return -1

        # index number of center node. (e.g. if 5 values visible, center index is 2, if 3 values visible, center index is 1..)
        if len(textNodes) == 2: # happens if selector is at maximum

            center_y1 = self.phone._tab._getCenterCoordsFromBoundCoords(self.phone._tab._getCoordsFromBounds( textNodes[0].getAttribute('bounds')))
            center_y2 = self.phone._tab._getCenterCoordsFromBoundCoords(self.phone._tab._getCoordsFromBounds( textNodes[1].getAttribute('bounds')))

            #determine which is closer to picker center
            center_picker = self.phone._tab._getCenterCoordsFromBoundCoords(self.phone._tab._getCoordsFromBounds( node.getAttribute('bounds')))

            len_1 = (center_y1[1] - center_picker[1])**2
            len_2 = (center_y2[1] - center_picker[1])**2
            c = min(len_1, len_2)

            center_node = 0 if c == len_1 else 1

        else:
            center_node = (len(textNodes) - 1) / 2

        return center_node

    def __call__(self, yyyy=None, mm=None, dd=None,selectdate=None, attemps=30 ):
        """ Executes datepicker functionality

        Parameters:
            dd(int)                      :   Day to be selected
            mm(int)                      :   Month to be selected
            yyyy(int)                    :   Year to be selected
            selectdate(date object)      :   Date to be selected
            attemps(int)                 :   How many times date selection will be tried (default 30)
        """

        if selectdate == None:
            assert None not in [dd,mm,yyyy], "Not enough parameters for selectDate"
            assert isinstance(yyyy, int), "First parameter is not a int!"
            temp = date(yyyy,mm, dd) # test that given date is valid
        else:
            dd = selectdate.day
            mm = selectdate.month
            yyyy = selectdate.year

        self.phone.comment('pickDate(%s)' % date(yyyy,mm, dd))

        state = self.phone._tab._getDump()
        picker_nodes = state.findall('//node[@class="android.widget.NumberPicker"]')

        if len(picker_nodes) != 3:
            self.phone.fail("Date picker should have 3 selectors, found %s possible coordinates for date picker. Is date picker visible on screen?" % len(picker_nodes))

        select_date = [yyyy, mm, dd]  # use time picker in this order

        # TODO: check if max values can be read somehow
        max_values = [2037, 12, 29] # corresponding maximum values to be used
        min_values = [1970, 1, 1] # corresponding maximum values to be used

        # Check the phone date format and choose order of the pickers
        order = self.__getDateFormat(picker_nodes)

        assert order.count(-1) == 0, "Cannot determine the date format"

        # TODO: use self.sql.executeCommand('/data/data/com.android.providers.settings/databases/settings.db', "select * from 'system'") to read date format
        # sort by order of determined, year, month, date. e.g. (2,0,1) = year index = 2, month index = 0, day index = 1
        picker_nodes = picker_nodes[order[0]], picker_nodes[order[1]], picker_nodes[order[2]]

        i = 0
        success = False

        for node in picker_nodes:

            # x marks wanted d, m or y
            x = select_date[i]
            max_val = max_values[i]
            min_val = min_values[i]
            i += 1

            # calculate the step size in pixels on y-axis, use distance between two selections as the distance unit. constant to adjust against the sensitivity
            if max_val > 31: # when using year picker, use different constant to adjust the picker sensitivity
                constant = 1.3
            else:
                constant = 1.2

            last_drag_direction = None # remember where the direction was dragged last time
            last_selected = None # last_selected value to save the current selected date value. If picker does not move, step size needs to be increased

            for count in range(attemps):

                if core.FW_conf['should_stop']:
                    return

                textNodes = state.findall('//node[@text and ancestor::node[@class="android.widget.NumberPicker" and @bounds="%s"]]' % node.getAttribute('bounds'))
                center_node = self.__getCenterNodeIndex( state.find('//node[@class="android.widget.NumberPicker" and @bounds="%s"]' % node.getAttribute('bounds')) )

                distance = math.fabs( \
                    int(self.phone._tab._getCoordsFromBounds( textNodes[ (center_node+1) % len(textNodes) ].getAttribute('bounds'))[1]) -   \
                    int(self.phone._tab._getCoordsFromBounds( textNodes[(center_node) % len(textNodes)].getAttribute('bounds'))[1])         \
                    )

                step = distance * constant

                # currently selected d, m or y
                current_sel_center = self.phone._tab._getCenterCoordsFromBoundCoords( self.phone._tab._getCoordsFromBounds(textNodes[center_node].getAttribute('bounds')) )

                debug.out('current selection %s' % textNodes[center_node].getAttribute('text'))
                try:
                    current_sel = int(textNodes[center_node].getAttribute('text'))

                except Exception as e: # month names cannot be converted to int, need to use dictionary
                    if self.months.has_key(textNodes[center_node].getAttribute('text')):
                        current_sel = self.months[textNodes[center_node].getAttribute('text')]
                    else:
                        debug.err('Failed to read date value from %s' % textNodes[center_node].getAttribute('text'))
                        return

                # hack: check if current value is smaller or bigger than max_val values, change them if seen (year column only (i=1)
                if i == 1:
                    if last_selected and last_drag_direction == 'up': # if picker was scrolled up, it might be possible that it went to minimum value. change min_val
                        if last_selected > current_sel:
                            debug.out("Picker went around. Changed min_val value from %s to %s" % (min_val, current_sel))
                            min_val = current_sel
                    elif last_selected and last_drag_direction == 'down': # if picker was scrolled up, it might be possible that it went to maximum value. change max_val
                        if last_selected < current_sel:
                            debug.out("Picker went around. Changed max_val value from %s to %s" % (max_val, current_sel))
                            max_val = current_sel
                    if current_sel > max_val:
                        debug.out("Selection is bigger than maximum value. Changed max_val value from %s to %s" % (max_val, current_sel))
                        max_val = current_sel
                    elif current_sel < min_val:
                        debug.out("Selection is smaller than minimum value. Changed min_val value from %s to %s" % (min_val, current_sel))
                        min_val = current_sel

                # if selected date did not change after, change step size
                if last_selected == current_sel:
                    step += 2
                    last_selected = None

                if current_sel > x:  # if current selection is bigger than wanted, count distances
                    distance_up = int( current_sel - x )    # distance_up is counted by numbers above current number
                    debug.out("selection bigger than wanted value. current date: %s - getting to %d (max_val %s, min_val %s) distance_up: %s" % (current_sel, x, max_val, min_val, distance_up ) )

                    if math.fabs(distance_up) > 20: multiplier = 9
                    elif math.fabs(distance_up) > 4: multiplier = 5
                    else: multiplier = 1

                    self.phone._touch.drawLine(  current_sel_center, \
                                        (current_sel_center[0], current_sel_center[1] + int(step * multiplier)), 30)
                    self.phone._run('Swiping down time picker', testStepReporting = False)
                    debug.out('swiped down %s -> %s (date picker steps :%s)' % (current_sel_center, (current_sel_center[0], current_sel_center[1] + step), multiplier))
                    last_drag_direction='down'

                elif current_sel < x:
                    distance_down = int( x - current_sel )
                    debug.out("selection smaller than wanted value. current date: %s - getting to %d (max_val %s, min_val %s) distance_down: %s" % (current_sel, x, max_val, min_val, distance_down ) )

                    if math.fabs(distance_down) > 20: multiplier = 9
                    elif math.fabs(distance_down) > 4: multiplier = 5
                    else: multiplier = 1

                    self.phone._touch.drawLine(  current_sel_center, \
                                        (current_sel_center[0], current_sel_center[1] - int(step * multiplier)), 30)
                    self.phone._run('Swiping up time picker', testStepReporting = False)
                    debug.out('swiped up %s -> %s (date picker steps :%s)' % (current_sel_center, (current_sel_center[0], current_sel_center[1] - step),multiplier))
                    last_drag_direction='up'

                else:
                    debug.brf("Select date: selected %s" % x)
                    success = True
                    break # if already selected

                # TODO: if picker can turn around, take into use

                #if current_sel > x:  # if current selection is bigger than wanted, count distances
                #    distance_up = int( current_sel - x )    # distance_up is counted by numbers above current number
                #    distance_down = int( (max_val - current_sel + 1) + (x - min_val) )   # distance to go around the picker: distance to maximum value + distance from minimum to wanted
                #    debug.brf("selection bigger than wanted value. current date: %s - getting to %d (max_val %s, min_val %s) distance_up: %s, distance_down: %s" % (current_sel, x, max_val, min_val, distance_up, distance_down ) )

                #elif current_sel < x:
                #    distance_up = int( current_sel - min_val + 1 + max_val - x) # distance to go around the picker: distance to minimum value + maximum value - wanted
                #    distance_down = int( x - current_sel )
                #    debug.brf("selection smaller than wanted value. current date: %s - getting to %d (max_val %s, min_val %s) distance_up: %s, distance_down: %s" % (current_sel, x, max_val, min_val, distance_up, distance_down ) )

                #else:
                #    debug.brf("Select date: selected %s" % x)
                #    success = True
                #    break # if already selected

                #if distance_up < distance_down:  # if scrolling up (dragging down)
                #    if math.fabs(distance_up) > 10: multiplier = 10
                #    elif math.fabs(distance_up) > 2: multiplier = 5
                #    else: multiplier = 1

                #    self.phone._touch.drawLine(  current_sel_center, \
                #                        (current_sel_center[0], current_sel_center[1] + int(step * multiplier)), 30)
                #    self.phone._run('Swiping down time picker', testStepReporting = False)
                #    debug.out('swiped down %s -> %s (date picker steps :%s)' % (current_sel_center, (current_sel_center[0], current_sel_center[1] + step), multiplier))
                #    last_drag_direction='down'
                #else: # if scrolling down (dragging up)
                #    if math.fabs(distance_up) > 10: multiplier = 10
                #    elif math.fabs(distance_down) > 2: multiplier = 5
                #    else: multiplier = 1
                #    #elif distance_down == 0: multiplier = 1
                #    #else: multiplier = distance_down
                #    self.phone._touch.drawLine(  current_sel_center, \
                #                        (current_sel_center[0], current_sel_center[1] - int(step * multiplier)), 30)
                #    self.phone._run('Swiping up time picker', testStepReporting = False)
                #    debug.out('swiped up %s -> %s (date picker steps :%s)' % (current_sel_center, (current_sel_center[0], current_sel_center[1] - step),multiplier))
                #    last_drag_direction='up'

                state = self.phone._tab._getDump()
                last_selected = current_sel

            assert success == True, "Failed to select %s from date picker" % x
            success = False


class Time(_ScriptBase):
    """Class providing time related scripting methods."""
    def pickTime(self, *args, **kwargs):
        self.phone._pickTime(*args, **kwargs)

    def pickDate(self, *args, **kwargs):
        self.phone._pickDate(*args, **kwargs)

    def setSystemDateTime(self, dateTime, disableNetworkTime = True):
        """Sets the given time to the device

            Parameters

            dateTime            Python datetime or .NET DateTime instance

            disableNetworkTime    whether action will automatically disable network time synching (Android 4.2 onwards)

            Returns True if set was successfull, False if not
        """
        assert self.phone._tab._tabConn, 'TAB connection not available!'
        assert not self.phone.isLeader(), 'Cannot set time in Leader mode'
        assert isinstance(dateTime, datetime) or isinstance(dateTime, DateTime), \
            'Invalid dateTime instance given! Either Python datetime or .NET DateTime instance needed'

        self.phone.comment('setSystemDateTime(%s)' % dateTime)

        return self.phone._tab._time.setSystemDateTime(dateTime)

    def setSystemDate(self, year, month, day):
        """Sets the given date to the device

            Parameters

            year            year (int)
            month           month (int)
            day             day (int)

            Returns True if set was successfull, False if not
        """
        assert self.phone._tab._tabConn, 'TAB connection not available!'
        assert not self.phone.isLeader(), 'Cannot set time in Leader mode'

        self.phone.comment('setSystemDate(%s, %s, %s)' % (year, month, day))

        return self.phone._tab._time.setSystemDate(year, month, day)

    def setSystemTime(self, hour, minute, second):
        """Sets the given time to the device

            Parameters

            hour            hour (int)
            minute          minute (int)
            second          second (int)

            Returns True if set was successfull, False if not
        """
        assert self.phone._tab._tabConn, 'TAB connection not available!'
        assert not self.phone.isLeader(), 'Cannot set time in Leader mode'

        self.phone.comment('setSystemTime(%s, %s, %s)' % (hour, minute, second))

        return self.phone._tab._time.setSystemTime(hour, minute, second)

    def synchPcDateTime(self, disableNetworkTime = True, doNotReport = False):
        """Sets PC's time to the device

            Parameters

            doNotReport           whether action is not to be reported (default = False)

            disableNetworkTime    whether action will automatically disable network time synching (Android 4.2 onwards) (default = True)

            Returns True if set was successfull, False if not
        """
        assert self.phone._tab._tabConn, 'TAB connection not available!'
        assert not self.phone.isLeader(), 'Cannot sync time in Leader mode'

        if not doNotReport:
            self.phone.comment('synchPcDateTime()')

        return self.phone._tab._time.syncPcDateTime(disableNetworkTime)

    def getSystemDateTime(self, asLocal = False):
        """Gets device's time

            Parameters

            asLocal           True to convert to local time (default = False)

            Returns Python datetime instance
        """
        assert self.phone._tab._tabConn, 'TAB connection not available!'

        self.phone.comment('getSystemDateTime()')

        return self.phone._tab._time.getSystemDateTime(asLocal)

    def getTimeZoneOffset(self):
        """Gets device's time zone offset

            Returns Python timedelta instance
        """
        assert self.phone._tab._tabConn, 'TAB connection not available!'

        self.phone.comment('getTimeZoneOffset()')

        return self.phone._tab._time.getTimeZoneOffset()

    def getTimeDiffToLocalPc(self, utc = True):
        """Gets the delta between PC clock and device clock: as accurately as is't possible via default shell

            Parameters

            utc           Value indicating whether to use UTC time from both ends (default = True)

            Returns Python timedelta instance
        """
        assert self.phone._tab._tabConn, 'TAB connection not available!'

        self.phone.comment('getTimeDiffToLocalPc()')

        return self.phone._tab._time.getTimeDiffToLocalPc(utc)

    def enableAutomaticNetworkTime(self, enable):
        """Enables or disables automatic time updates via network. Works from Android 4.2 onwards

            Parameters

            enable           Enable or disable
        """
        assert self.phone._tab._tabConn, 'TAB connection not available!'

        self.phone.comment('enableAutomaticNetworkTime(%s)' % enable)

        self.phone._tab._time.enableAutomaticNetworkTime(enable)

    def enableAutomaticNetworkTimeZone(self, enable):
        """Enables or disables automatic time zone updates via network. Works from Android 4.2 onwards

            Parameters

            enable           Enable or disable
        """
        assert self.phone._tab._tabConn, 'TAB connection not available!'

        self.phone.comment('enableAutomaticNetworkTimeZone(%s)' % enable)

        self.phone._tab._time.enableAutomaticNetworkTimeZone(enable)

    def setUtcTimeZone(self):
        """Sets the device's time zone to UTC
        """
        assert self.phone._tab._tabConn, 'TAB connection not available!'

        self.phone.comment('setUtcTimeZone()')

        self.phone._tab._time.setUtcTimeZone()

    def setTimeZone(self, timeZone):
        """Sets the device's time zone

            Parameters

            timeZone           Time zone in which to change: if format 'GMT[+-]HH:mm'
        """
        assert self.phone._tab._tabConn, 'TAB connection not available!'

        self.phone.comment('setTimeZone(%s)' % timeZone)

        self.phone._tab._time.setTimeZone(timeZone)

    def getTimeZone(self):
        """Gets the device's time zone

            Returns the device's time zone: if format 'GMT[+-]HH:mm'
        """
        assert self.phone._tab._tabConn, 'TAB connection not available!'

        self.phone.comment('getTimeZone()')

        return self.phone._tab._time.timeZone

    def getTimeZoneDetails(self):
        """Gets the device's time zone details

            Returns the device's time zone details
        """
        assert self.phone._tab._tabConn, 'TAB connection not available!'

        self.phone.comment('getTimeZoneDetails()')

        return self.phone._tab._time.timeZoneDetails


class Toggle(_ScriptBase):
    """Class providing toggle related scripting methods."""
    def __init__(self, phone):
        """ Initialize supported button types """
        super(Toggle,self).__init__(phone)
        # supported button types
        self._supportedButtons = ['android.widget.ToggleButton', 'android.widget.Switch', 'android.widget.CheckBox', 'android.widget.RadioButton', 'android.widget.CheckedTextView']

    def __call__(self, item, timeout = None):
        """Call toggle.set"""
        # checked == None, don't care, just toggle
        self.set(item, checked = None, timeout = timeout)

    def __findToggleButton(self, item, timeout = None):
        """Find toggle button ('android.widget.ToggleButton', 'android.widget.Switch', 'android.widget.CheckBox', 'android.widget.RadioButton')

            Parameters

            item            button index tree, content description, resource id or text / content description of item related to button
            timeout(int)    wait timeout

            Returns button node (NodeUtils) or None
        """
        foundNode = None

        if timeout == None:
            timeout = core.FW_conf['settings'].System.ExpectTimeout

        t = time.time()

        while t + timeout / 1000.0 > time.time() and not foundNode:
            # just return if test execution is stopping
            if core.FW_conf['should_stop']:
                return

            for visibleNode in self.phone._tab._getVisibleNodes().findall('//node'):
                #debug.brf('visibleNode: %s' % visibleNode.toprettyxml())

                # try to match index, content desc, resource id or related text / content desc
                if ((visibleNode.getAttribute('index') == item or visibleNode.getAttribute('content-desc') == item or visibleNode.getAttribute('resource-id') == item) or \
                    (visibleNode.getAttribute('related_text') == item or visibleNode.getAttribute('related_content') == item)) and \
                    visibleNode.getAttribute('class') in self._supportedButtons:
                    foundNode = visibleNode
                    break

            if not foundNode:
                self.phone.delay(1000, False)

        if not foundNode:
            self.phone.fail('toggle could not find item with: %s' % self._convertToReport(item))

        return foundNode

    def get(self, item, timeout = None):
        """Get toggle status of button

            Parameters

            item            button index tree, content description, resource id or text / content description of item related to button
            timeout(int)    wait timeout

            Returns True if button toggle state is checked, False if not, None if button was not found
        """
        self.phone.comment('toggle.get(%s)' % self._convertToReport(item))

        toggleState = None

        toggleButton = self.__findToggleButton(item, timeout = timeout)

        if toggleButton:
            toggleState = toggleButton.getAttribute('checked') == 'true'

        return toggleState

    def set(self, item, checked, timeout = None):
        """Toggle button

            Parameters

            item            button index tree, content description, resource id or text / content description of item related to button
            checked         wanted toggle value True/False or None (= don't care, just toggle)
            timeout(int)    wait timeout

            Returns True if button was toggled, False if button was not found
        """
        self.phone.comment('toggle.set(%s)' % ','.join([self._convertToReport(item), checked != None and str(checked) or '']).strip(','))
        assert checked in [True, False, None], 'Wrong checked value in toggle.set: %s. Must be either True/False' % str(checked)

        toggleButton = self.__findToggleButton(item, timeout = timeout)

        if toggleButton:
            coords = self.phone._tab._getCoordsFromBounds(toggleButton.getAttribute('bounds'))
            centerX, centerY = self.phone._tab._getCenterCoordsFromBoundCoords(coords)

            if toggleButton.getAttribute('class') == 'android.widget.Switch':
                # determine x coordinate point according to checked status
                if toggleButton.getAttribute('checked') == 'true':
                    x = coords[0] # left
                else:
                    #x = coords[2] # right # NOTE: this presses too right
                    x = centerX + 10
            else:
                x = centerX

            if checked == None:
                #debug.brf('toggle coords: %s, %s' % (x, centerY))
                self.phone._touch.press((x, centerY))
                self.phone._run('scripting: Press to coordinates: %s,%s' % (x,centerY))
            # toggle only if needed
            elif (checked and toggleButton.getAttribute('checked') == 'false') or \
                 (not checked and toggleButton.getAttribute('checked') == 'true'):
                    #debug.brf('toggle coords: %s, %s' % (x, centerY))
                    self.phone._touch.press((x, centerY))
                    self.phone._run('scripting: press to coordinates: %s,%s' % (x,centerY))

            return True
        else:
            return False


class Orientation(_ScriptBase):
    """Class providing display orientation related scripting methods."""
    def __call__(self):
        """Call orientation.get"""
        return self.get()

    def setPortrait(self, doNotReport = False):
        """Set orientation to portrait.

            Parameters

            doNotReport     whether action is not to be reported (default = False)

            Returns True if set was successfull, False if not.
        """
        if not doNotReport:
            self.phone.comment('orientation.setPortrait()')

        returnValue = False

        if self.phone._tab._isServerAvailable():
            if self.phone._tab._isServerConnected():
                success, turnOK = self.phone._tab._executeTabOperation(self.phone._tab._tabConn.TestServerClient.setOrientationNatural)

                # check that change was made
                if success and turnOK and self.get(True) == 'portrait':
                    returnValue = True

                self.phone._tab._screenDimensionsQueried = False

        return returnValue

    def setLandscape(self, withLeftTurn = True):
        """Set orientation to landscape.

            Parameters

            withLeftTurn        set orientation by turning device to left (default = True)

            Returns True if set was successfull, False if not.
        """
        self.phone.comment('orientation.setLandscape()')
        assert not self.phone.isLeader(), 'Leader mode and follower cannot set orientation!'

        returnValue = False

        if self.phone._tab._isServerAvailable():
            if self.phone._tab._isServerConnected():
                success, naturalOK = self.phone._tab._executeTabOperation(self.phone._tab._tabConn.TestServerClient.setOrientationNatural)

                if withLeftTurn:
                    success, turnOK = self.phone._tab._executeTabOperation(self.phone._tab._tabConn.TestServerClient.setOrientationLeft)
                else:
                    success, turnOK = self.phone._tab._executeTabOperation(self.phone._tab._tabConn.TestServerClient.setOrientationRight)

                # check that change was made
                if naturalOK and success and turnOK and self.get(True) == 'landscape':
                    returnValue = True

                self.phone._tab._screenDimensionsQueried = False

        return returnValue

    def get(self, doNotReport = False):
        """Get current orientation.

            Parameters

            doNotReport     whether action is not to be reported (default = False)

            Returns 'portrait', 'landscape' or 'unknown'
        """
        if not doNotReport:
            self.phone.comment('orientation.get()')

        orientation = 'unknown'

        if self.phone._tab._isServerAvailable():
            if self.phone._tab._isServerConnected():
                success, response = self.phone._tab._executeTabOperation(self.phone._tab._tabConn.TestServerClient.getDisplayOrientation)

                if success:
                    if response == 0:
                        orientation = 'portrait'
                    else:
                        orientation = 'landscape'

        return orientation


class Volume(_ScriptBase):
    """Class providing volume related scripting methods."""
    def __call__(self):
        """Call volume.getRinger"""
        return self.getRinger()

    def up(self, steps = 1):
        """Set volume up by given steps.

            Parameters

            steps           volume steps (int) (default = 1)
        """
        assert isinstance(steps, int), 'Invalid volume steps: "%s" given' % str(steps)
        self.phone.comment('volume.up(%s)' % (steps != 1 and str(steps) or ''))

        if steps == 0:
            steps = 1

        for i in range(steps):
            self.phone._pressKey('KEYCODE_VOLUME_UP', waitUntilNoUIevents = False)
            self.phone._run('volume up press')

    def down(self, steps = 1):
        """Set volume down by given steps.

            Parameters

            steps           volume steps (int) (default = 1)
        """
        assert isinstance(steps, int), 'Invalid volume steps: "%s" given' % str(steps)
        self.phone.comment('volume.down(%s)' % (steps != 1 and str(steps) or ''))

        if steps == 0:
            steps = 1

        for i in range(steps):
            self.phone._pressKey('KEYCODE_VOLUME_DOWN', waitUntilNoUIevents = False)
            self.phone._run('volume down press')

    def setRinger(self, level):
        """Set ringer volume.

            Parameters

            level           volume level (int)
        """
        assert type(level) == types.IntType, 'Volume level must be integer!'
        assert not self.phone.isLeader(), 'Leader mode and follower cannot call volume.setRinger()'

        self.phone._tab._checkScriptingServiceConnection()

        self.phone.comment('volume.setRinger(%s)' % str(level))

        if self.phone._tab.serverLevelInUse and getattr(self.phone._tab._tabConn, 'ScriptingServiceClient', None):
            self.phone._tab._tabConn.ScriptingServiceClient.setRingerVolume(level)

    def setMedia(self, level):
        """Set media volume.

            Parameters

            level           volume level (int)
        """
        assert type(level) == types.IntType, 'Volume level must be integer!'
        assert not self.phone.isLeader(), 'Leader mode and follower cannot call volume.setMedia()'

        self.phone._tab._checkScriptingServiceConnection()

        self.phone.comment('volume.setMedia(%s)' % str(level))

        if self.phone._tab.serverLevelInUse and getattr(self.phone._tab._tabConn, 'ScriptingServiceClient', None):
            self.phone._tab._tabConn.ScriptingServiceClient.setMediaVolume(level)

    def getRinger(self):
        """Get ringer volume.

            Returns volume level (int)
        """
        self.phone.comment('volume.getRinger()')

        self.phone._tab._checkScriptingServiceConnection()

        if self.phone._tab.serverLevelInUse and getattr(self.phone._tab._tabConn, 'ScriptingServiceClient', None):
            return self.phone._tab._tabConn.ScriptingServiceClient.getRingerVolume()

    def getMedia(self):
        """Get media volume.

            Returns volume level (int)
        """
        self.phone.comment('volume.getMedia()')

        self.phone._tab._checkScriptingServiceConnection()

        if self.phone._tab.serverLevelInUse and getattr(self.phone._tab._tabConn, 'ScriptingServiceClient', None):
            return self.phone._tab._tabConn.ScriptingServiceClient.getMediaVolume()


class Kill(_ScriptBase):
    """ Class for killing or force stopping processes/applications """

    def __init__(self, phone):
        """ Initialize test case instance for class """
        super(Kill,self).__init__(phone)
        self.doNotKill = [ 'com.nokia.homescreen', 'com.android.launcher' ]

    def __call__(self, applicationName=None, forced=False, doNotReport=False):
        """ Executes kill or force stop command

        Parameters:
            applicationName(str)   :  Name or the process/application/package
            forced(boolean)        :  Whether to call kill instead of of forceStop (default = False)
            doNotReport(boolean)   :  Whether test step is put to test report or not
        """

        assert not self.phone.isLeader(), 'Leader mode and follower cannot kill applications!'

        if not applicationName:
            self.topmost(forced, doNotReport)
            return

        if self.doNotKill.__contains__(applicationName):
            return

        if not doNotReport:
            self.phone.comment('kill(%s, forced=%s)' % (applicationName, forced))

        am = self.phone._tab._activityManager

        activity = am.GetActivityByName(applicationName)

        if activity != None and activity.IsApplication:
            if forced:
                activity.Kill()
            else:
                activity.ForceStop()

    def topmost(self, forced=False, doNotReport=False):
        """ Executes kill or force stop command for the topmost application

        Parameters:
            forced(boolean)         :  Whether to call kill instead of of forceStop (default = False)
            doNotReport(boolean)   :  Whether test step is put to test report or not
        """
        # wait that UI stabilizes before querying package
        self.phone.state.wait(3000, doNotReport=True)

        package = self.phone._tab._getCurrentPackageName()

        if package:
            self.__call__(package, forced)


class Pinch(_ScriptBase):
    """Class providing pinch related scripting methods."""
    def __call__(self):
        """Call default pinch"""
        return self._pinch()

    def _pinch(self, fromPoint1, fromPoint2, toPoint1, toPoint2, doNotReport = False):
        """Pinch functionality

            Parameters

            fromPoint1          first finger's start coordinates
            fromPoint2          second finger's start coordinates
            toPoint1            first finger's end coordinates
            toPoint2            second finger's end coordinates
            doNotReport         whether action is not to be reported (default = False)

            Returns True if pinch was made successfully, False if not
        """
        assert isinstance(fromPoint1, tuple), 'Pinch: fromPoint1 must be tuple, got "%s" instead' % str(fromPoint1)
        assert isinstance(fromPoint2, tuple), 'Pinch: fromPoint2 must be tuple, got "%s" instead' % str(fromPoint2)
        assert isinstance(toPoint1, tuple), 'Pinch: fromPoint1 must be tuple, got "%s" instead' % str(toPoint1)
        assert isinstance(toPoint2, tuple), 'Pinch: fromPoint1 must be tuple, got "%s" instead' % str(toPoint2)

        if not doNotReport:
            self.phone.comment('pinch((%s,%s), (%s,%s), (%s,%s), (%s,%s))' % \
                (str(fromPoint1[0]), str(fromPoint1[1]), str(fromPoint2[0]), str(fromPoint2[1]),
                 str(toPoint1[0]), str(toPoint1[1]), str(toPoint2[0]), str(toPoint2[1])))

        # convert possible relative coordinates to absolute
        origFromPoint1 = fromPoint1
        origFromPoint2 = fromPoint2
        origToPoint1 = toPoint1
        origToPoint2 = toPoint2

        fromPoint1 = self.phone._tab._convertRelative(fromPoint1)
        fromPoint2 = self.phone._tab._convertRelative(fromPoint2)
        toPoint1 = self.phone._tab._convertRelative(toPoint1)
        toPoint2 = self.phone._tab._convertRelative(toPoint2)

        if origFromPoint1 != fromPoint1 or origFromPoint2 != fromPoint2 or origToPoint1 != toPoint1 or origToPoint2 != toPoint2:
            debug.brf('pinch: ((%s,%s), (%s,%s), (%s,%s), (%s,%s)) converted to absolute coordinates: ((%s,%s), (%s,%s), (%s,%s), (%s,%s))' % \
                    (str(origFromPoint1[0]), str(origFromPoint1[1]), str(origFromPoint2[0]), str(origFromPoint2[1]),
                     str(origToPoint1[0]), str(origToPoint1[1]), str(origToPoint2[0]), str(origToPoint2[1]),
                     str(fromPoint1[0]), str(fromPoint1[1]), str(fromPoint2[0]), str(fromPoint2[1]),
                     str(toPoint1[0]), str(toPoint1[1]), str(toPoint2[0]), str(toPoint2[1])))

        pinchSuccessful = False

        if self.phone.isBlackBox():
            pinchSuccessful = self.__blackBoxPinch([fromPoint1, fromPoint2, toPoint1, toPoint2])
        else:
            if self.phone._tab._isServerAvailable():
                if self.phone._tab._isServerConnected():
                    success, response = self.phone._tab._executeTabOperation(\
                        self.phone._tab._tabConn.TestServerClient.pinch, fromPoint1[0], fromPoint1[1], fromPoint2[0], fromPoint2[1], toPoint1[0], toPoint1[1], toPoint2[0], toPoint2[1], 20)
                    pinchSuccessful = success and response

        return pinchSuccessful

    def _pinchOut(self, fromPoint = None, angle = 45.0, length = 0.25, doNotReport = False):
        """Pinch out functionality

            Parameters

            fromPoint           pinch coordinates given in tuple (can be either relative or absolute coordinates)
                                (default = None, screen dimensions will be used)
            angle               pinch angle (default = 45.0)
            length              pinch length (default = 0.25)
                                if given as relative, it's tied to screen dimensions
            doNotReport         whether action is not to be reported (default = False)

            Returns True if pinch was made successfully, False if not
        """
        assert isinstance(fromPoint, tuple) or fromPoint == None, 'fromPoint parameter must be tuple, got "%s" instead' % str(fromPoint)
        assert angle <= 360, "Too high value for angle"

        commentString = ''

        if not doNotReport:
            params = []

            if fromPoint != None:
                params.append('(' + ','.join([str(x) for x in fromPoint]) + ')')
            if angle != 45.0:
                params.append(str(angle))
            if length != 0.25:
                params.append(str(length))

            if params:
                commentString = 'pinchOut(%s)' % ','.join(params)
            else:
                commentString = 'pinchOut()'

        if fromPoint == None:
            fromPoint = (self.phone._tab.getScreenWidth() / 2, self.phone._tab.getScreenHeight() / 2)

        # convert possible relative coordinates to absolute
        origfromPoint = fromPoint
        fromPoint = self.phone._tab._convertRelative(fromPoint)

        # convert float length to pixels
        if isinstance(length, float):
            maxLength = math.sqrt((math.pow((self.phone._tab.getScreenHeight() / 2), 2) + math.pow((self.phone._tab.getScreenWidth() / 2), 2)))
            length = int(math.ceil((maxLength * length)))

        if not doNotReport:
            commentString += ' --> '
            commentString += 'pinchOut((%s), %s, %s)' % (','.join([str(x) for x in fromPoint]), str(angle), str(length))
            self.phone.comment(commentString)

        pinchSuccessful = False

        if self.phone.isBlackBox():
            pinchSuccessful = self.__blackBoxPinch([fromPoint], angle, length, direction = 'out')
        else:
            if self.phone._tab._isServerAvailable():
                if self.phone._tab._isServerConnected():
                    success, response = self.phone._tab._executeTabOperation(self.phone._tab._tabConn.TestServerClient.pinchOut, fromPoint[0], fromPoint[1], length, angle, 20)
                    pinchSuccessful = success and response

        return pinchSuccessful

    def _pinchIn(self, fromPoint = None, angle = 45.0, length = 0.25, doNotReport = False):
        """Pinch in functionality

            Parameters

            fromPoint           pinch coordinates given in tuple (can be either relative or absolute coordinates)
                                (default = None, screen dimensions will be used)
            angle               pinch angle (default = 45.0)
            length              pinch length (default = 0.25)
                                if given as relative, it's tied to screen dimenstions
            doNotReport         whether action is not to be reported (default = False)

            Returns True if pinch was made successfully, False if not
        """
        assert isinstance(fromPoint, tuple) or fromPoint == None, 'fromPoint parameter must be tuple, got "%s" instead' % str(fromPoint)
        assert angle <= 360, "Too high value for angle"

        commentString = ''

        if not doNotReport:
            params = []

            if fromPoint != None:
                params.append('(' + ','.join([str(x) for x in fromPoint]) + ')')
            if angle != 45.0:
                params.append(str(angle))
            if length != 0.25:
                params.append(str(length))

            if params:
                commentString = 'pinchIn(%s)' % ','.join(params)
            else:
                commentString = 'pinchIn()'

        if fromPoint == None:
            fromPoint = (self.phone._tab.getScreenWidth() / 2, self.phone._tab.getScreenHeight() / 2)

        # convert possible relative coordinates to absolute
        origfromPoint = fromPoint
        fromPoint = self.phone._tab._convertRelative(fromPoint)

        # convert float length to pixels
        if isinstance(length, float):
            maxLength = math.sqrt((math.pow((self.phone._tab.getScreenHeight() / 2), 2) + math.pow((self.phone._tab.getScreenWidth() / 2), 2)))
            length = int(math.ceil((maxLength * length)))

        if not doNotReport:
            commentString += ' --> '
            commentString += 'pinchIn((%s), %s, %s)' % (','.join([str(x) for x in fromPoint]), str(angle), str(length))
            self.phone.comment(commentString)

        pinchSuccessful = False

        if self.phone.isBlackBox():
            pinchSuccessful = self.__blackBoxPinch([fromPoint], angle, length, direction = 'in')
        else:
            if self.phone._tab._isServerAvailable():
                if self.phone._tab._isServerConnected():
                    success, response = self.phone._tab._executeTabOperation(self.phone._tab._tabConn.TestServerClient.pinchIn, fromPoint[0], fromPoint[1], length, angle, 20)
                    pinchSuccessful = success and response

        return pinchSuccessful

    def __blackBoxPinch(self, points = [], angle = None, length = None, direction = None):
        """Pinch functionality in blackbox mode.

            Parameters

            points              list of coordinate points
            angle               pinch angle
            length              pinch length
            direction           None / "in" / "out"

            Returns True if blackBox pinch was made, False if not
        """
        stepSize = 10
        steps = []

        if len(points) == 1 and angle and length and direction in ['in', 'out']:
            fromPoint = points[0]
            angle = math.radians(angle)

            #Define travel directions for fingers
            #Values need to be inverted because math-functions use angles which increase counter-clockwise
            #And Y-axis on phone is reversed.
            if angle > 90:
                x1Dir = -1
                x2Dir = 1
            else:
                x1Dir = 1
                x2Dir = -1

            y1Dir = -1
            y2Dir = 1

            #Calculate steps required
            numSteps = int(length / stepSize)

            #Add start/end point
            x1 = x2 = fromPoint[0]
            y1 = y2 = fromPoint[1]
            steps = [(fromPoint,fromPoint)]

            #Create intermediate steps
            for ii in range(0, numSteps):
                x1 += x1Dir * stepSize * math.sin(angle)
                y1 += y1Dir * stepSize * math.cos(angle)
                x2 += x2Dir * stepSize * math.sin(angle)
                y2 += y2Dir * stepSize * math.cos(angle)
                steps.append(((int(x1),int(y1)),(int(x2),int(y2))))

            endPoint1 = (int(x1Dir * length * math.sin(angle)+self.phone._tab.getScreenWidth()/2),int(y1Dir * length * math.cos(angle)+self.phone._tab.getScreenHeight()/2))
            endPoint2 = (int(x2Dir * length * math.sin(angle)+self.phone._tab.getScreenWidth()/2),int(y2Dir * length * math.cos(angle)+self.phone._tab.getScreenHeight()/2))

            #Add end point
            if int(x1) != int(endPoint1[0]) or int(y1) != int(endPoint1[1]):
                steps.pop(-1)
                steps.append((endPoint1,endPoint2))

            if direction=='in':
                steps.reverse()
        elif len(points) == 4:
            fromPoint1, fromPoint2, toPoint1, toPoint2 = points
            fromX1, fromY1 = fromPoint1
            fromX2, fromY2 = fromPoint2
            toX1, toY1 = toPoint1
            toX2, toY2 = toPoint2

            # find biggest difference
            xDifference1 = abs(fromX1 - toX1)
            xDifference2 = abs(fromX2 - toX2)
            yDifference1 = abs(fromY1 - toY1)
            yDifference2 = abs(fromY2 - toY2)

            maxDifference = max([xDifference1, xDifference2, yDifference1, yDifference2])
            #debug.brf('max difference: %s' % maxDifference)

            # calculate steps required
            numSteps = int(maxDifference / stepSize)
            stepSize1 = xDifference1 / numSteps
            stepSize2 = xDifference2 / numSteps
            stepSize3 = yDifference1 / numSteps
            stepSize4 = yDifference2 / numSteps
            x1 = fromX1
            x2 = fromX2
            y1 = fromY1
            y2 = fromY2

            # loop and append steps
            for i in range(numSteps):
                if fromX1 < toX1:
                    x1 += stepSize1
                else:
                    x1 -= stepSize1

                if fromX2 < toX2:
                    x2 += stepSize2
                else:
                    x2 -= stepSize2

                if fromY1 < toY1:
                    y1 += stepSize3
                else:
                    y1 -= stepSize3

                if fromY2 < toY2:
                    y2 += stepSize4
                else:
                    y2 -= stepSize4

                steps.append(((int(x1),int(y1)),(int(x2),int(y2))))
        else:
            debug.err('Invalid data given to __blackBoxPinch!')
            return False

        #debug.brf('steps: %s' % str(steps))

        for i in range(len(steps)):
            debug.out(str(steps[i][0][0])+ ";"+str(steps[i][0][1]) + ";;" +str(steps[i][1][0]) + ";" +str(steps[i][1][1]))

        self.phone._touch.pressPointMultiTouch(steps, None)
        self.phone._run('pinch', testStepReporting=False)

        return True


class _GestureWrapper(object):
    """Wrapper class so that old self.gesture.x test script calls will work."""
    def swipe(self):
        pass
    def drag(self):
        pass
    def flick(self):
        pass
    def doubleTap(self):
        pass


class Swipe(_ScriptBase):
    """ Class for swipe gesture

    """
    def __call__(self, fromPoint, toPoint, stepSize=20):
        """ Perform swipe gesture

        Parameters:
            fromPoint(tuple)    :   Coordinates of start point
            topoint(tuple)      :   Coordinates of end point
            stepSize(int)       :   Number of pixels between calculated intermediate points
        """
        self.phone.comment('swipe((%s,%s), (%s,%s))'%( str(fromPoint[0]), str(fromPoint[1]), str(toPoint[0]), str(toPoint[1])))

        # convert to relative coordinates if needed
        origFromPoint = fromPoint
        origToPoint = toPoint
        fromPoint = self.phone._tab._convertRelative(fromPoint)
        toPoint = self.phone._tab._convertRelative(toPoint)

        if origFromPoint != fromPoint or origToPoint != toPoint:
            debug.brf('swipe: ((%s, %s), (%s, %s)) converted to absolute coordinates: ((%s, %s), (%s, %s))' % \
                (str(origFromPoint[0]), str(origFromPoint[1]), str(origToPoint[0]), str(origToPoint[1]),
                 str(fromPoint[0]), str(fromPoint[1]), str(toPoint[0]), str(toPoint[1])))

        self.phone._touch.drawLine(fromPoint, toPoint, stepSize = stepSize)
        self.phone._run('swipe(%s,%s)'%( str(fromPoint), str(toPoint)))

    def viewSwipe(self, reverse = False, fromMiddle = False):
        """Perform swipe across the screen to change UI view 
           reverse(bool)  :  False: start from right True: start from left
           fromMiddle    :  True: start from middle of the screen
        """

        yCoordinate = int(self.phone.uiState.getScreenHeight() / 1.5)

        if reverse:
            fromPoint = (2, yCoordinate)

            if fromMiddle:
                toPoint = ((self.phone.uiState.getScreenWidth() / 2)-2, yCoordinate)
            else:
                toPoint = (self.phone.uiState.getScreenWidth()-2, yCoordinate)
        else:
            fromPoint = (self.phone.uiState.getScreenWidth()-2, yCoordinate)

            if fromMiddle:
                toPoint = ((self.phone.uiState.getScreenWidth() / 2)+2, yCoordinate)
            else:
                toPoint = (2, yCoordinate)

        debug.out('tab_interface: drawLine %s -> %s' % (str(fromPoint), str(toPoint)) )
        self.phone._touch.drawLine(fromPoint, toPoint, stepSize = 100)
        self.phone._run('tab_interface: gesture.swipe(%s,%s)'%( str(fromPoint), str(toPoint)))

        self.phone.state.wait(2000, 1000, doNotReport=True, usePageFlipCount = True)

    def upSwipe(self):
        """" perform up swipe e.g. to open lock screen """
        try:
            xCoordinate = int(self.phone.uiState.getScreenWidth() / 2)
            fromPoint = (xCoordinate, self.phone.uiState.getScreenHeight() - 10)
            toPoint = (xCoordinate, 10)
            self.phone._touch.drawLine(fromPoint, toPoint)
            self.phone._run('swipe upswipe: gesture.swipe(%s,%s)'%( str(fromPoint), str(toPoint)))
        except Exception as e:
            debug.err('Failed to perform upswipe %s' % e.message)

class Drag(_ScriptBase):
    """ Class for drag gesture

    """
    def __call__(self, item, toItem, duration=None,timeout=None):
        """  Drag item to item / endpoint

        Parameters:
            item(str)               :   Start drag from this items midpoint
            toItem(str or tuple)    :   Drag to item name or endpoint coordinates
        """
        assert isinstance(item, str), "Parameter item must be string, got %s instead!" % type(item)
        assert isinstance(toItem, str) or isinstance(toItem, tuple), "Parameter toItem must be string or tuple, got %s instead!" % type(toItem)

        if isinstance(toItem, tuple):
            self.phone.comment('drag(%s, (%s, %s))' % (self._convertToReport(item), str(toItem[0]), str(toItem[1])))

            # convert to relative coordinates if needed
            origToItem = toItem
            toItem = self.phone._tab._convertRelative(toItem)

            if origToItem != toItem:
                debug.brf('drag: (%s, %s) converted to absolute coordinates: (%s, %s)' % (str(origToItem[0]), str(origToItem[1]), str(toItem[0]), str(toItem[1])))
        else:
            self.phone.comment('drag(%s, %s)' % (self._convertToReport(item), self._convertToReport(toItem)))
            toItem = self.phone.uiState.revealItem(item = toItem, timeout = timeout, doNotScroll = True)

        coordinates = self.phone.uiState.revealItem(item = item, timeout = timeout, doNotScroll = True)

        if coordinates is None:
            self.phone.fail("Item %s not visible, cannot drag" % self._convertToReport(item))
        if toItem is None:
            self.phone.fail("Drag to item not visible, cannot drag")

        self.phone._touch.drawLine(coordinates, toItem, duration=duration, dragHold=True)
        self.phone._run('drag()')


class Flick(_ScriptBase):
    """ Class for flick gesture

    """
    def __call__(self, item = None, direction = 'up', timeout=None, speed=1000, doNotReport=False):
        """ Perform flick gesture

        Parameters:
            item(string|tuple)  :   Name of the item or coordinates where flick gesture is started
            direction(string)   :   direction of the flick
            doNotReport         :   whether action is not to be reported (default = False)

        """
        assert direction in ['up','down','left','right'], "Direction should be one of 'up','down','left' or'right', got %s instead"%direction

        displayUpdateInterval = 20
        stepLength = int(speed / 1000.0 * displayUpdateInterval)

        if item:
            if not doNotReport:
                self.phone.comment('flick(%s, %s)' % (self._convertToReport(item),direction))

            if not isinstance(item, tuple):
                startPoint = self.phone.uiState.revealItem(item, timeout=timeout, doNotScroll = True)
            else:
                startPoint = item

                # convert to relative coordinates if needed
                origStartPoint = startPoint
                startPoint = self.phone._tab._convertRelative(startPoint)

                if origStartPoint != startPoint:
                    debug.brf('flick: (%s, %s) converted to absolute coordinates: (%s, %s)' % (str(origStartPoint[0]), str(origStartPoint[1]), str(startPoint[0]), str(startPoint[1])))

            if startPoint != None:
                if direction =='up':
                    endpoint = (startPoint[0],1)
                elif direction=='down':
                    endpoint = (startPoint[0],self.phone.uiState.getScreenHeight() - 1)
                elif direction=='left':
                    endpoint = (1,startPoint[1])
                elif direction=='right':
                    endpoint = (self.phone.uiState.getScreenWidth() - 1,startPoint[1])
            else:
                self.phone.fail("Item %s not visible, cannot flick" % self._convertToReport(item))

            #debug.brf('lick startpoint: %s' % (str(startPoint)))
            #debug.brf('lick endpoint: %s' % (str(endpoint)))

            self.phone._touch.drawLine(startPoint, endpoint, stepSize=stepLength, duration=None, holdPenToStopScroll=False)
            self.phone._run('flick()')
        else:
            if not doNotReport:
                self.phone.comment('flick(%s, speed=%s)' % (direction, speed))

            # set "status bar height" in AoL mode
            self.phone.uiState.statusbarHeight = 40

            # set "breathing line height" in AoL mode
            self.phone.uiState.breathingLineHeight = 5

            if direction in ['up','down']:
                startPoint = (self.phone.uiState.getScreenWidth()/2,self.phone.uiState.getScreenHeight()-self.phone.uiState.breathingLineHeight)
                endpoint = (self.phone.uiState.getScreenWidth()/2,self.phone.uiState.statusbarHeight*3)
            else:
                startPoint = (0,self.phone.uiState.getScreenHeight()/2)
                endpoint = (self.phone.uiState.getScreenWidth() - 1,self.phone.uiState.getScreenHeight()/2)

            #debug.brf('lick startpoint: %s' % (str(startPoint)))
            #debug.brf('lick endpoint: %s' % (str(endpoint)))

            if direction in ['down','left']:
                startPoint, endpoint = (endpoint,startPoint)

            self.phone._touch.drawLine(startPoint, endpoint, stepSize=stepLength, duration=None, holdPenToStopScroll=False)
            self.phone._run('flick(%s)'%direction)


class DoubleTap(_ScriptBase):
    """ Class for doubleTap gesture

    """
    def __call__(self, item, timeout=None, index=1):
        """ Perform double tap-gesture

        Parameters:
            item(string|tuple)      :   item or coordinates to be selected
            timeout(int)            :   Wait timeout
            index(int)              :   Sequence number of the item to select
        """
        self.phone.comment('doubleTap(%s)'% ((isinstance(item, tuple) and ', '.join(str(x) for x in item)) or self._convertToReport(item)))

        # Press (x, y) coordinate point when item is tuple
        if isinstance(item, tuple):
            # convert to relative coordinates if needed
            origPoint = item
            coordinates = self.phone._tab._convertRelative(item)

            if origPoint != coordinates:
                debug.brf('doubleTap: (%s, %s) converted to absolute coordinates: (%s, %s)' % (str(origPoint[0]), str(origPoint[1]), str(coordinates[0]), str(coordinates[1])))
        else:
            coordinates = self.phone.uiState.revealItem(item, timeout, index=index, doNotScroll = True)

        if coordinates:
            self.phone._touch.press(coordinates, waitUntilNoUIevents = False)
            self.phone._touch.press(coordinates)
            self.phone._run('double tap()')

            # TODO: is double tap success check needed?
                #if self.phone._tab._isServerAvailable() and self.phone._tab._isServerConnected():
                #    success, tapOK = self.phone._tab._executeTabOperation(self.phone._tab._tabConn.TestServerClient.tapSequence,
                #                                                          List[int]([coordinates[0], coordinates[1], coordinates[0], coordinates[1]]), 20, 0)
                #else:
                #    tapOK = False

                #if not tapOK:
                #    self.phone.fail('double tap "%s" failed!' % str(item))
        else:
            self.phone.fail("Cannot double tap %s, item is not found" % self._convertToReport(item))


class Device(_ScriptBase):
    """Class providing interface for SL4A scripting service methods."""
    def __getattr__(self, attr, *args, **kwargs):
        """Map scripting service level to self."""
        self.phone.comment('device(%s)' % str(attr))

        function = None

        if self.phone._tab.serverLevelInUse:
            self.phone._tab._checkScriptingServiceConnection()

            if getattr(self.phone._tab._tabConn, 'ScriptingServiceClient', None):
                function = getattr(self.phone._tab._tabConn.ScriptingServiceClient, attr, None)

        if not function:
            raise AttributeError("Unknown scripting method: %s" % str(attr))
        else:
            return function


class Shell(_ScriptBase):
    """Class providing shell scripting interface."""
    def __call__(self, shellCommand = ""):
        """Execute given command in shell.

            Parameters

            shellCommand            shellCommand string

            Returns response in string[]
        """
        self.phone.comment('shell(%s)' % shellCommand)

        if self.phone._tab._tabConn:
            shellResponse = self.phone._tab._tabConn.ShellCommand(shellCommand)

            try:
                return list(shellResponse)
            except:
                return ""
        else:
            return ""


class State(_ScriptBase):
    """Class providing information about phone state."""
    def __call__(self, doNotReport=False):
        """Calls state.get."""
        return self.get(doNotReport=doNotReport)

    def get(self, timeout = 2000, waitUntilNoUIevents=True, doNotReport=False):
        """Returns current application package name."""
        if not doNotReport:
            self.phone.comment('state.get()')

        if waitUntilNoUIevents:
            # wait that UI stabilizes before querying package
            self.wait(timeout, 800, doNotReport=True)

        return self.phone._tab._getCurrentPackageName()

    @override
    def inMainMenu(self, timeout = 1000, doNotReport = False):
        """Returns True if phone is in main menu, False if not.
        
            Parameters

            timeout             maximum timeout for wait in milliseconds
            doNotReport         whether action is not to be reported (default = False)
        """
        if not doNotReport:
            self.phone.comment('state.inMainMenu()')

        if self.phone._tab.serverLevelInUse:
            try:
                self.phone.state.wait(timeout, doNotReport=True)

                visibleTexts = self.phone._tab._getVisibleTexts(False)

                deviceInfo = self.phone.deviceInfo(doNotReport = True, refresh = False)

                # check if we have Ara's main menu page (we could be also on app list or on fastlane)
                if deviceInfo.has_key('ro.build.product') and deviceInfo['ro.build.product'] in self._supportedAoL2BuildProducts:
                    if self.phone._tab._currentDump and \
                       (self.phone._tab._currentDump.find('//node[@resource-id="com.proto.launcher:id/grid"]') or \
                        self.phone._tab._currentDump.find('//node[@resource-id="com.nokia.homescreen:id/grid"]')):
                        return True
                    else:
                        return False
                # check Normandy's fastlane vs. main menuif not core.FW_conf['should_stop']:
                elif deviceInfo.has_key('ro.build.product') and deviceInfo['ro.build.product'] == 'msm8625':
                    if self.phone._tab._currentDump and self.phone._tab._currentDump.find('//node[@package="com.proto.launcher"]'):
                        if self.phone._tab._currentDump.find('//node[@class="android.widget.ListView"]'):
                            return False
                        else:
                            return True
                    else:
                        return False
                # other product and scripting service available
                elif getattr(self.phone._tab._tabConn, 'ScriptingServiceClient', None):
                    # get launchable applications
                    launchableApplications = self.phone._tab._getLaunchableApplications()

                    #debug.brf('apps: %s' % [x for x in launchableApplications.Keys])
                    #debug.brf('matching: %s' % [x in launchableApplications.Keys for x in visibleTexts])

                    if (len(visibleTexts) > 0):
                        percentage = float(100.0 * (float([x in launchableApplications.Keys for x in visibleTexts].count(True)) / float(len(visibleTexts))))
                    else:
                        percentage = 0

                    #debug.brf('percentage: %s' % percentage)

                    # FIXME: Find out more reliable way to do this
                    if percentage >= 50:
                        return True
                    else:
                        return False
                # unable to check main menu
                else:
                    return False
            except Exception, err:
                if not core.FW_conf['should_stop']:
                    debug.err('Failed to execute inMainMenu!')

                # in case of exception return False
                return False
        else:
            return False

    def wait(self, timeout = 5000, interval = 800, doNotReport=False, usePageFlipCount = False):
        """Waits until no more UI events are arriving from the device.

            Parameters

            timeout         maximum timeout for wait in milliseconds
            interval        interval for event waiting in milliseconds
        """
        assert isinstance(timeout, int) and timeout > 0, 'given timeout "%s" is not valid' % str(timeout)
        assert isinstance(interval, int) and interval > 0, 'given interval "%s" is not valid' % str(interval)

        if not doNotReport:
            self.phone.comment('state.wait(%s, %s)' % (str(timeout), str(interval)))

        self.phone._tab._waitUntilNoUIEvents(eventInterval = interval, maximumDuration = timeout, usePageFlipCount = usePageFlipCount)

    def waitBoot(self, timeout = 120):
        """Waits until device is online and booted.

            Parameters

            timeout         maximum timeout for waiting in seconds
                            (default = 120)

            Returns True if device online and booted, False if not
        """
        assert isinstance(timeout, int) and timeout > 0, 'given timeout "%s" is not valid' % str(timeout)
        success = False

        self.phone.comment('state.waitBoot(%s)' % str(timeout))

        try:
            success = self.phone._tab._waitForDeviceOnline(timeout = timeout)
        except Exception:
            # catch all exceptions in script level
            success = False

        return success

    def wakeUp(self):
        """ wake up the device using test server client """
        self.phone._tab._executeTabOperation(self.phone._tab._tabConn.TestServerClient.wakeUp)

class BlackBoxVirtualKeyboard(_ScriptBase):

    def __init__(self, phone):
        super(BlackBoxVirtualKeyboard,self).__init__(phone)
        self.vkbSettings = None
        self.coords = None
        self.mode = None # current mode
        self.orientation = None # current orientation

    def _pressSpecialKey(self, key, mode='Abc', orientation='portrait'):
        """ press shift, enter or other special key """
        assert key in ['shift', 'enter']
        self.phone.comment('Input special key %s' % key)
        self._loadVkbSettings()
        self._loadCoords(orientation, mode)
        if not key in self.coords.keys(): # check transition to different mode
            new_mode = self._findModeForChar(key)
            if not new_mode:
                self.__raise('Cannot find vkb mode where char %s is' % key)
        else:
            self.phone._touch.press(tuple(self.coords[key]))
            self.phone._run('Press to coordinates: %s,%s' % tuple(self.coords[key]))

    def _writeBlackBox(self, string, mode='Abc', orientation='portrait', delayBetweenPresses=None):
        """ write text using black box """

        self.phone.comment('Input %s' % string)
        self._loadVkbSettings()

        if not self.vkbSettings:
            self.__raise('Mapped VirtualKeyboard: no settings data loaded')

        if not self.vkbSettings.has_key(orientation):
            self.__raise('Mapped VirtualKeyboard: no orientation mode named %s' % str(orientation))

        if not self.vkbSettings[orientation].has_key(mode):
            self.__raise('Mapped VirtualKeyboard: error with setting file, mode %s not defined for orientation %s' % (str(mode), orientation) )

        self._loadCoords(orientation, mode)

        if delayBetweenPresses == None or delayBetweenPresses == 0:
            delayBetweenPresses = int(core.FW_conf['settings'].System.BlackBoxVKBDelayBetweenPresses)

        if self.phone.isLeader():
            # if writed text equals the phone number settings, it needs to be evaluated in follower
            ret = needsEvaluation(string)
            if ret and ret[0]:
                debug.brf('Sending %s in for Follower write' % ret[1])
                core.FW_conf['leader'].InputString(ret[1], True, mode, orientation, delayBetweenPresses, core.FW_conf['settings'].TestRun.EvaluateSettings)
                core.FW_conf['leader'].sendTouches = False
            else:
                core.FW_conf['leader'].sendTouches = True

        if self.mode == 'Abc' or self.mode == 'ABC':
            caps = True
        else:
            caps = False

        for c in string:

            # if caps mode on and non-caps char written, press shift. Or if caps wanted and kbd in non-caps mode.
            if (caps and c.islower()) or (not caps and not c.islower()):
                 # or if abc mode and caps mode needed
                if self.coords.has_key('shift'): # numberic (pin, phonenumber etc) modes dont define shift
                    self.phone._touch.press(tuple(self.coords['shift']), wait=delayBetweenPresses)

            c = c.lower() # all chars in settings are lower
            if c == ' ':
                c = 'space'

            if not c in self.coords.keys(): # check transition to different mode
                new_mode = self._findModeForChar(c)
                if not new_mode:
                    self.__raise('Cannot find vkb mode where char %s is' % c)

                self._transition(new_mode)

            if type(self.coords[c][0]) == types.StringType: # if coord is a stringtype, it's a long press or key sequence
                if self.coords[c][0] == "long": # long press for key
                    key = self.coords[c][1]
                    debug.brf('long press %s' % key)
                    self.phone._touch.press(tuple(self.coords[key]), 1500, wait=delayBetweenPresses)
                else:
                    for key in self.coords[c]:
                        self.phone._touch.press(tuple(self.coords[key]), wait=delayBetweenPresses)
            else:
                debug.out('enter %s %s %s' % (c, self.coords[c][0], self.coords[c][1]))
                self.phone._touch.press(tuple(self.coords[c]), wait=delayBetweenPresses)

            if self.mode != 'ABC':
                caps = False

        self.phone._run('Write in BlackBox VKB')

        if self.phone.isLeader():
            core.FW_conf['leader'].inputParams.Clear()
            core.FW_conf['leader'].sendTouches = True

    def _loadVkbSettings(self):
        """ load settings from vkb setting file """
        try:
            f = open(os.path.join(core.FW_conf['settings_dir'],'vkb.settings'), 'r')
            data = f.read()
            f.close()
            self.vkbSettings = json.loads(data)

        except Exception as e:
            debug.err('Error loading VKB settings data: %s' % e.message)

    def _loadCoords(self, orientation=None, mode=None, recursive=False):
        """ load coordinates for orientataion / mode """

        self.coords = {}

        if not self.mode:
            self.mode = 'Abc'
        if not self.orientation:
            self.orientation = 'portrait'

        if not mode:
            mode = self.mode
        elif not recursive:
            self.mode = mode

        if not orientation:
            orientation = self.orientation
        else:
            self.orientation = orientation

        #if not self.vkbSettings[orientation][mode].has_key('h_span') or \
        #    not self.vkbSettings[orientation][mode].has_key('v_span') or \
        #    not self.vkbSettings[orientation][mode].has_key('rows'):
        #    self.__raise('Blackbox VirtualKeyboard: error with setting file, check that orientation %s / mode %s has keys "h_span", "v_span" and "rows"' % (orientation, mode))
        if not self.vkbSettings[orientation].has_key(mode):
            self.__raise('Mapped VirtualKeyboard: mode %s not defined for orientation %s"' % (mode, orientation))
        layout = self.vkbSettings[orientation][mode]

        if layout.has_key('base') and layout['base'] != "":
            if not self.vkbSettings[orientation].has_key(layout['base']):
                self.__raise('Mapped VirtualKeyboard: %s orienation mode %s has unknown base layout %s"' % (orientation, mode, layout['base']))
            baselayout = self.vkbSettings[orientation][layout['base']]
            self._loadCoords(orientation, layout['base'], recursive=True)
        else:
            baselayout = None

        if layout.has_key('rows'): # if each row has unique
            # if rows are defined, then only coordinates are the same as in base layout
            self.coords = {}

            for i in layout['rows']:
                # get first coords from current or secondly from base layout
                first_coords = None
                if layout['rows'][i].has_key('first'):
                    first_coords = layout['rows'][i]['first']
                elif baselayout != None and baselayout['rows'][i].has_key('first'):
                    first_coords = baselayout['rows'][i]['first']

                if first_coords:
                    # get keys information for layout, from current or base
                    selected_layout = None
                    if layout['rows'][i].has_key('keys'):
                        selected_layout = layout
                    elif baselayout != None and baselayout['rows'][i].has_key('keys'):
                        selected_layout = baselayout
                    if selected_layout:
                        for j in range( len(selected_layout['rows'][i]['keys']) ):
                            x = first_coords[0] + selected_layout['h_span'] * j
                            self.coords[selected_layout['rows'][i]['keys'][j]] = (x, first_coords[1])

                # get special keys
                selected_layout = None
                if layout['rows'][i].has_key('special_keys'):
                    selected_layout = layout
                elif baselayout != None and baselayout['rows'][i].has_key('special_keys'):
                    selected_layout = baselayout

                if selected_layout:
                    if selected_layout['rows'][i].has_key('special_keys'):
                        for key, value in selected_layout['rows'][i]['special_keys'].iteritems():
                            # if self.coords.has_key(key):
                                # raise Exception('Blackbox VirtualKeyboard: %s is defined twice' % key)
                            self.coords[key] = tuple(value)

        elif layout.has_key('keys'): # if no rows defined, all the keys are aligned
            # get first coords from current or secondly from base layout
            first_coords = None
            if layout.has_key('first'):
                first_coords = layout['first']
            elif baselayout != None and baselayout.has_key('first'):
                first_coords = baselayout['first']

            for i in range(len(layout['keys'])):
                x = first_coords[0] + layout['h_span'] * ( i % layout['columns'])
                y = first_coords[1] + layout['v_span'] * ( int ( i / layout['columns']) )
                self.coords[layout['keys'][i]] = (x, y)

            if layout.has_key('special_keys'):
                for key, value in layout['special_keys'].iteritems():
                    if self.coords.has_key(key):
                        self.__raise('Mapped VirtualKeyboard: %s is defined twice' % key)
                    self.coords[key] = tuple(value)

        if layout.has_key('hidden'): # if there's hidden keys accessible with double keys etc.
            for key, value in layout['hidden'].iteritems():
                if type(value) == types.ListType: # list type means repeat sequence
                    for i in value:
                        self.coords[key] = tuple(value) # value will be tuple of CHARS

    def _findModeForChar(self, char, orientation=None):
        """ get the vkb mode where char is """

        if not orientation:
            orientation = self.orientation

        for mode in self.vkbSettings[orientation]:

            if not self.vkbSettings[orientation][mode].has_key('rows'):
                continue

            for row in self.vkbSettings[orientation][mode]['rows']:

                if self.vkbSettings[orientation][mode]['rows'][row].has_key('keys'):

                    if char in self.vkbSettings[orientation][mode]['rows'][row]['keys']:
                        return mode

        return None

    def _transition(self, new_mode, orientation=None):
        """ vkb transition from mode to new mode """

        if not orientation:
            orientation = self.orientation

        if not self.vkbSettings[orientation][self.mode].has_key('transitions'):
            self.__raise('Mapped VirtualKeyboard: No transition defined for orientation %s mode %s -> %s' % (orientation, self.mode, new_mode))
        transitions = self.vkbSettings[orientation][self.mode]['transitions']

        debug.out('current mode %s and wanted mode %s' % (self.mode, new_mode))

        success = False

        origin_mode = self.mode

        for ke, va in transitions.iteritems():
            if new_mode in va:
                debug.out('1: key %s takes to %s mode (mode definition type: %s)' % (ke, va, type(va)))
                debug.out('press key(s) %s to get to mode %s' % (ke, new_mode))
                self.phone._touch.press(tuple(self.coords[ke]))
                self.phone._run('Press to coordinates: %s,%s' % tuple(self.coords[ke]))
                self.phone.delay(100, False)
                success = True
                break
            else: # search transitions in layout if the mode is there
                if not type(va) == types.ListType:
                    va = [va]
                for v in va:
                    debug.out('searching from transition layouts %s' % repr(self.vkbSettings[orientation][v]))#['transitions']))
                    for key, tra in self.vkbSettings[orientation][v]['transitions'].iteritems():
                        debug.out('2: key %s takes to %s mode (mode definition type %s)' % (key, tra, type(tra)))
                        if new_mode in tra:
                            debug.out('%s needs to be pressed (from layout %s)' % (key, tra))
                            debug.out('mode %s is in first level transition: %s' % (tra, tra in transitions.values()))
                            debug.out('checking 1st level %s takes to mode %s, which is needed: %s' % (key, v, v in transitions.values()))
                            if v in transitions.values():
                                self._transition(v, orientation)
                                self.phone.delay(100)
                                debug.out('layout changed1')
                                self._transition(new_mode, orientation)
                                debug.out('layout changed2')
                                success = True
                                break

        if not success:
            self.__raise('No vkb transition info defined from %s to %s. Defined: %r' % (origin_mode, new_mode, transitions))

        self.mode = new_mode
        debug.out('load coords for %s' % self.mode)
        self._loadCoords()

    def clear(self, time=3, mode=None, orientation=None):
        """ press the backspace for defined amount of time """
        self._loadVkbSettings()
        self._loadCoords(orientation, mode)
        self.phone._touch.press(tuple(self.coords['backspace']), time*1000)
        self.phone._run('Press to coordinates: %s,%s' % tuple(self.coords['backspace']))

    def backspace(self, times=0, mode=None, orientation=None):
        """ press backspace for times defined """
        self._loadVkbSettings()
        if not mode and not self.mode:
            self.mode = 'Abc'
        if not orientation and not self.orientation:
            self.orientation = 'portrait'

        if times==0:
            times = 1
        elif times=='all':
            self.clear(time=10)
            return

        self._loadCoords()
        for i in range(times):
            self.phone._touch.press(tuple(self.coords['backspace']))
            self.phone._run('Press to coordinates: %s,%s' % tuple(self.coords['backspace']))

    def __raise(self, message):
        """ private raise, enable touch sending before raise in leader mode """

        if self.phone.isLeader():
            core.FW_conf['leader'].inputParams.Clear()
            core.FW_conf['leader'].sendTouches = True

        raise Exception(message)


class _UINode(_ScriptBase):
    """Node class for GetItem functionality."""
    def __init__(self, phone, getItem, searchString, node, autoRefresh, usedAttribute, index = 1):
        """Initialize class and store attributes"""
        super(_UINode,self).__init__(phone)
        self.__getItem = getItem
        self.__searchString = searchString
        self.__node = node
        self.__autoRefresh = autoRefresh
        self.__usedAttribute = usedAttribute
        self.__index = index

    def __getattr__(self, attr, *args, **kwargs):
        """Map NodeUtils to self."""
        self.__refreshNode()

        return getattr(self.__node, attr)

    def __str__(self):
        """Returns Node information in string"""
        return """<UI Node instance:
                description: %s
                text: %s
                resource id: %s
                index tree: %s
                bounds: %s
                center point: %s
                isChecked: %s
                isCheckable: %s
                isClickable: %s>
               """ % (self.getDescription(), self.getText(), self.getResourceId(), self.getIndexTree(), str(self.getBounds()), \
                      str(self.getCenterPoint()), self.isChecked(), self.isCheckable(), self.isClickable())

    def __refreshNode(self):
        """Refresh node with getItem so that updates to node location etc are updated."""
        if self.__autoRefresh:
            if self.__node.getAttribute(self.__usedAttribute):
                #debug.brf('_UINode: Refreshing with %s' % self.__usedAttribute)
                index = self.__index + 1
                #if index != 1:
                #    debug.brf('_UINode: Using index %s' % index)

                self.__node = self.__getItem(self.__searchString, doNotReport=True, checkedAttributes=self.__usedAttribute, index=index, calledFromUINode=True)

            if not self.__node:
                raise TestException('Item no longer available with search string: "%s"' % self.__searchString)

    def getDescription(self):
        """Returns content description of the node."""
        self.__refreshNode()

        return self.__node.getAttribute('content-desc')

    def getText(self):
        """Returns text of the node."""
        self.__refreshNode()

        return self.__node.getAttribute('text')

    def getResourceId(self):
        """Returns resource id of the node."""
        self.__refreshNode()

        return self.__node.getAttribute('resource-id')

    def getIndexTree(self):
        """Returns index tree of the node."""
        self.__refreshNode()

        return self.__node.getAttribute('index')

    def getBounds(self):
        """Returns x, y, width and height of the node in tuple."""
        self.__refreshNode()

        coords = self.phone._tab._getCoordsFromBounds(self.__node.getAttribute('bounds'))

        return ((coords[0], coords[1], coords[2] - coords[0], coords[3] - coords[1]))

    def getCenterPoint(self):
        """Returns center point of the node in tuple."""
        self.__refreshNode()

        return (int(self.__node.getAttribute('center-x')), int(self.__node.getAttribute('center-y')))

    def isChecked(self):
        """Returns whether node is checked or not."""
        self.__refreshNode()

        if self.__node.getAttribute('checked') == 'true':
            return True
        else:
            return False

    def isCheckable(self):
        """Returns whether node is checkable or not."""
        self.__refreshNode()

        if self.__node.getAttribute('checkable') == 'true':
            return True
        else:
            return False

    def isClickable(self):
        """Returns whether node is clickable or not."""
        self.__refreshNode()

        if self.__node.getAttribute('clickable') == 'true':
            return True
        else:
            return False

    def select(self, **kwargs):
        """Select functionality for GetItem."""
        self.__refreshNode()

        if self.__node.getAttribute('content-desc'):
            self.phone.select.description(self.__node.getAttribute('content-desc'), **kwargs)
        elif self.__node.getAttribute('text'):
            self.phone.select.text(self.__node.getAttribute('text'), **kwargs)
        elif self.__node.getAttribute('resource-id'):
            self.phone.select.resourceId(self.__node.getAttribute('resource-id'), **kwargs)
        else:
            raise TestException('Unable to select item with search string: "%s"' % self.__searchString)

    def check(self, **kwargs):
        """Check functionality for GetItem."""
        self.__refreshNode()

        if self.__node.getAttribute('content-desc'):
            self.phone.check.description(self.__node.getAttribute('content-desc'), **kwargs)
        elif self.__node.getAttribute('text'):
            self.phone.check.text(self.__node.getAttribute('text'), **kwargs)
        elif self.__node.getAttribute('resource-id'):
            self.phone.check.resourceId(self.__node.getAttribute('resource-id'), **kwargs)
        else:
            raise TestException('Unable to check item with search string: "%s"' % self.__searchString)

    def doubleTap(self, **kwargs):
        """DoubleTap functionality for GetItem."""
        self.__refreshNode()

        if self.__node.getAttribute('content-desc'):
            self.phone.doubleTap(self.__node.getAttribute('content-desc'), **kwargs)
        elif self.__node.getAttribute('text'):
            self.phone.doubleTap(self.__node.getAttribute('text'), **kwargs)
        elif self.__node.getAttribute('resource-id'):
            self.phone.doubleTap(self.__node.getAttribute('resource-id'), **kwargs)
        else:
            raise TestException('Unable to double tap item with search string: "%s"' % self.__searchString)

    def drag(self, toItem, **kwargs):
        """Drag functionality for GetItem."""
        self.__refreshNode()

        if self.__node.getAttribute('content-desc'):
            self.phone.drag(self.__node.getAttribute('content-desc'), toItem, **kwargs)
        elif self.__node.getAttribute('text'):
            self.phone.drag(self.__node.getAttribute('text'), toItem, **kwargs)
        elif self.__node.getAttribute('resource-id'):
            self.phone.drag(self.__node.getAttribute('resource-id'), toItem, **kwargs)
        else:
            raise TestException('Unable to drag item with search string: "%s"' % self.__searchString)

    def flick(self, **kwargs):
        """Flick functionality for GetItem."""
        self.__refreshNode()

        if self.__node.getAttribute('content-desc'):
            self.phone.flick(self.__node.getAttribute('content-desc'), **kwargs)
        elif self.__node.getAttribute('text'):
            self.phone.flick(self.__node.getAttribute('text'), **kwargs)
        elif self.__node.getAttribute('resource-id'):
            self.phone.flick(self.__node.getAttribute('resource-id'), **kwargs)
        else:
            raise TestException('Unable to flick item with search string: "%s"' % self.__searchString)

    def toggle(self, **kwargs):
        """Toggle functionality for GetItem."""
        self.__refreshNode()

        if self.__node.getAttribute('content-desc'):
            self.phone.toggle(self.__node.getAttribute('content-desc'), **kwargs)
        elif self.__node.getAttribute('text'):
            self.phone.toggle(self.__node.getAttribute('text'), **kwargs)
        elif self.__node.getAttribute('resource-id'):
            self.phone.toggle(self.__node.getAttribute('resource-id'), **kwargs)
        else:
            raise TestException('Unable to toggle item with search string: "%s"' % self.__searchString)


class GetItem(_ScriptBase):
    """Class for accessing screen items"""
    def __call__(self, searchString, area=None, autoRefresh=True, doNotReport=False, checkedAttributes=None, index = 1, calledFromUINode = False, returnList = False):
        """Get screen items according to search string and checked attributes

        Parameters:
            searchString (str)     :  Search string which can also contain wildcard(s)
            area(4-tuple of ints)  :  Area x,y,w,h where text is read from
            autoRefresh(boolean)   :  Whether UI node is automatically refreshed or not
            doNotReport(boolean)   :  Whether test step is put to test report or not
            checkedAttributes      :  XML attributes which will be checked
                                      (None stands for all possible attributes)
            index(int)             :  Sequence number of the item
            calledFromUINode       :  Whether GetItem has been called from UINode class
            returnList             :  Whether list for found nodes is returned (for GetItems)

        Return:
            Returns found node instance if found, otherwise raises TestException
        """
        assert isinstance(area, tuple) or area == None or area == 'full', 'Given area needs to be tuple of 4 integers!'
        assert isinstance(index, int), 'Given index need to be integer!'

        if not doNotReport:
            commentString = searchString

            if area != None:
                commentString += ', area=(%s, %s, %s, %s)' % (area[0], area[1], area[2], area[3])
            if autoRefresh != True:
                commentString += ', autoRefresh=%s' % str(autoRefresh)

            self.phone.comment('getItem(%s)' % commentString)

        # put index to list iteration number
        index -= 1
        if index < 0:
            index = 0

        # by default, use visible screen area as area.
        if area == None:
            area = (0,0,self.phone.uiState.getScreenWidth(), self.phone.uiState.getScreenHeight())

        # use default list if no checked attributes defined
        if checkedAttributes is None:
            checkedAttributes = self.phone.uiState._checkedAttributes
        elif not isinstance(checkedAttributes, list):
            checkedAttributes = [checkedAttributes]

        foundNodes = []
        nodes = self.phone.uiState._findNodes(None, checkedAttributes = checkedAttributes, area = area)

        foundNode = None
        usedAttribute = None
        foundIndex = 0
                       
        for node in nodes:
            for attribute in checkedAttributes:
                item = node.getAttribute(attribute)

                # skip empty items and items that don't match the given filter string
                if not item or not fnmatch.fnmatch(item, searchString):
                    continue
                
                # continue if index is not matching
                if index != 0 and index != foundIndex:                    
                    #debug.brf('Item found but moving on: %s' % node.getAttribute('text'))
                    foundIndex += 1
                    continue

                foundIndex += 1

                #debug.brf('Item found: %s' % node.getAttribute('text'))

                foundNode = node
                usedAttribute = attribute                
                break

            if foundNode:
                if returnList:
                    foundNodes.append(_UINode(self.phone, self, searchString, foundNode, autoRefresh, usedAttribute, foundIndex - 1))
                    foundNode = None
                else:
                    break

        if returnList:
            if foundNodes:
                return foundNodes
            else:
                raise TestException('Items not found with %s: "%s"' % (checkedAttributes == None and 'search string' or checkedAttributes[0], searchString))
        else:
            if foundNode:
                if calledFromUINode:
                    return foundNode
                else:
                    return _UINode(self.phone, self, searchString, foundNode, autoRefresh, usedAttribute, index)
            else:
                raise TestException('Item not found with %s: "%s"' % (checkedAttributes == None and 'search string' or checkedAttributes[0], searchString))

    def text(self, searchString, area=None, autoRefresh=True, doNotReport=False, index=1):
        """ Get item according to text

            Parameters

            searchString (str)     :  Search string which can also contain wildcard(s)
            area(4-tuple of ints)  :  Area x,y,w,h where text is read from
            autoRefresh(boolean)   :  Whether UI node is automatically refreshed or not
            doNotReport(boolean)   :  Whether test step is put to test report or not
            index(int)             :  Sequence number of the item
        """
        if not doNotReport:
            self.phone.comment('getItem.text(%s)' % ','.join([searchString != None and self._convertToReport(searchString) or '',
                                                           area != None and str(area) or '']).strip(','))

        return self.__call__(searchString, area, autoRefresh=autoRefresh, doNotReport=True, checkedAttributes = 'text', index=index)

    def description(self, searchString, area=None, autoRefresh=True, doNotReport=False):
        """ Get item according to description

            Parameters

            searchString (str)     :  Search string which can also contain wildcard(s)
            area(4-tuple of ints)  :  Area x,y,w,h where text is read from
            autoRefresh(boolean)   :  Whether UI node is automatically refreshed or not
            doNotReport(boolean)   :  Whether test step is put to test report or not
        """
        if not doNotReport:
            self.phone.comment('getItem.description(%s)' % ','.join([searchString != None and self._convertToReport(searchString) or '',
                                                                  area != None and str(area) or '']).strip(','))

        return self.__call__(searchString, area, autoRefresh=autoRefresh, doNotReport=True, checkedAttributes = 'content-desc')

    def indexTree(self, searchString, area=None, autoRefresh=True, doNotReport=False):
        """ Get item according to index tree

            Parameters

            searchString (str)     :  Search string which can also contain wildcard(s)
            area(4-tuple of ints)  :  Area x,y,w,h where text is read from
            autoRefresh(boolean)   :  Whether UI node is automatically refreshed or not
            doNotReport(boolean)   :  Whether test step is put to test report or not
        """
        if not doNotReport:
            self.phone.comment('getItem.indexTree(%s)' % ','.join([searchString != None and self._convertToReport(searchString) or '',
                                                                area != None and str(area) or '']).strip(','))

        return self.__call__(searchString, area, autoRefresh=autoRefresh, doNotReport=True, checkedAttributes = 'index')

    def resourceId(self, searchString, area=None, autoRefresh=True, doNotReport=False, index=1):
        """ Get item according to resource id

            Parameters

            searchString (str)     :  Search string which can also contain wildcard(s)
            area(4-tuple of ints)  :  Area x,y,w,h where text is read from
            autoRefresh(boolean)   :  Whether UI node is automatically refreshed or not
            doNotReport(boolean)   :  Whether test step is put to test report or not
            index(int)             :  Sequence number of the item
        """
        if not doNotReport:
            self.phone.comment('getItem.resourceId(%s)' % ','.join([searchString != None and self._convertToReport(searchString) or '',
                                                                 area != None and str(area) or '']).strip(','),)

        return self.__call__(searchString, area, autoRefresh=autoRefresh, doNotReport=True, checkedAttributes = 'resource-id', index=index)


class GetItems(_ScriptBase):
    """Class for accessing multiple screen items"""
    def __call__(self, searchString, area=None, autoRefresh=True, doNotReport=False, checkedAttributes=None):
        """Get screen items according to search string and checked attributes

        Parameters:
            searchString (str)     :  Search string which can also contain wildcard(s)
            area(4-tuple of ints)  :  Area x,y,w,h where text is read from
            autoRefresh(boolean)   :  Whether UI node is automatically refreshed or not
            doNotReport(boolean)   :  Whether test step is put to test report or not
            checkedAttributes      :  XML attributes which will be checked
                                      (None stands for all possible attributes)

        Return:
            Returns list of node instances if found, otherwise raises TestException
        """
        assert isinstance(area, tuple) or area == None or area == 'full', 'Given area needs to be tuple of 4 integers!'

        if not doNotReport:
            commentString = searchString

            if area != None:
                commentString += ', area=(%s, %s, %s, %s)' % (area[0], area[1], area[2], area[3])
            if autoRefresh != True:
                commentString += ', autoRefresh=%s' % str(autoRefresh)

            self.phone.comment('getItems(%s)' % commentString)

        return self.phone.getItem(searchString, area, autoRefresh=autoRefresh, doNotReport=True, checkedAttributes=checkedAttributes, returnList=True)

    def text(self, searchString, area=None, autoRefresh=True, doNotReport=False):
        """ Get items according to text

            Parameters

            searchString (str)     :  Search string which can also contain wildcard(s)
            area(4-tuple of ints)  :  Area x,y,w,h where text is read from
            autoRefresh(boolean)   :  Whether UI node is automatically refreshed or not
            doNotReport(boolean)   :  Whether test step is put to test report or not
        """
        if not doNotReport:
            self.phone.comment('getItems.text(%s)' % ','.join([searchString != None and self._convertToReport(searchString) or '',
                                                           area != None and str(area) or '']).strip(','))

        return self.__call__(searchString, area, autoRefresh=autoRefresh, doNotReport=True, checkedAttributes = 'text')

    def description(self, searchString, area=None, autoRefresh=True, doNotReport=False):
        """ Get items according to description

            Parameters

            searchString (str)     :  Search string which can also contain wildcard(s)
            area(4-tuple of ints)  :  Area x,y,w,h where text is read from
            autoRefresh(boolean)   :  Whether UI node is automatically refreshed or not
            doNotReport(boolean)   :  Whether test step is put to test report or not
        """
        if not doNotReport:
            self.phone.comment('getItems.description(%s)' % ','.join([searchString != None and self._convertToReport(searchString) or '',
                                                                  area != None and str(area) or '']).strip(','))

        return self.__call__(searchString, area, autoRefresh=autoRefresh, doNotReport=True, checkedAttributes = 'content-desc')

    def indexTree(self, searchString, area=None, autoRefresh=True, doNotReport=False):
        """ Get items according to index tree

            Parameters

            searchString (str)     :  Search string which can also contain wildcard(s)
            area(4-tuple of ints)  :  Area x,y,w,h where text is read from
            autoRefresh(boolean)   :  Whether UI node is automatically refreshed or not
            doNotReport(boolean)   :  Whether test step is put to test report or not
        """
        if not doNotReport:
            self.phone.comment('getItems.indexTree(%s)' % ','.join([searchString != None and self._convertToReport(searchString) or '',
                                                                area != None and str(area) or '']).strip(','))

        return self.__call__(searchString, area, autoRefresh=autoRefresh, doNotReport=True, checkedAttributes = 'index')

    def resourceId(self, searchString, area=None, autoRefresh=True, doNotReport=False):
        """ Get items according to resource id

            Parameters

            searchString (str)     :  Search string which can also contain wildcard(s)
            area(4-tuple of ints)  :  Area x,y,w,h where text is read from
            autoRefresh(boolean)   :  Whether UI node is automatically refreshed or not
            doNotReport(boolean)   :  Whether test step is put to test report or not
        """
        if not doNotReport:
            self.phone.comment('getItems.resourceId(%s)' % ','.join([searchString != None and self._convertToReport(searchString) or '',
                                                                 area != None and str(area) or '']).strip(','),)

        return self.__call__(searchString, area, autoRefresh=autoRefresh, doNotReport=True, checkedAttributes = 'resource-id')


class VirtualKeyboard(_ScriptBase):
    """ Class for virtual keyboard-component

    Note!!! THIS CLASS MEANT TO BE USED IN scripting.py ONLY!!!

    Format for the layout maps is:
    self.__layoutMaps[LAYOUT_ID][CHARACTER]=((x_center,y_center),flags_fo_ all_case_views_which_has_this_character,on_which_characters_popup_list_this_character_is)
    """
    maxStringLengthToServer = 350
    knownMajorModes = ['url', 'recipient-list','text']
    knownMinorModes = ['phonenumber','email', 'email-or-recipient']

    LAYOUT_QWERTY =                        0b1
    LAYOUT_ITUT =                         0b10
    LAYOUT_EMAIL =                       0b100
    LAYOUT_LANG_EN =                    0b1000
    LAYOUT_LANG_CH =                   0b10000
    LAYOUT_DIALER =                   0b100000
    LAYOUT_NUMBER_MODE =             0b1000000
    LAYOUT_RECIPIENT_LIST =         0b10000000
    LAYOUT_LANDSCAPE =             0b100000000
    LAYOUT_PORTRAIT =             0b1000000000
    LAYOUT_URL =                 0b10000000000
    LAYOUT_EMAIL_OR_RECIPIENT = 0b100000000000

    CASE_UPPER =            0b1
    CASE_LOWER =           0b10
    CASE_SYMBOLS_1 =      0b100
    CASE_SYMBOLS_2 =     0b1000
    CASE_ITUT_NUMBERS = 0b10000
    CASE_SYMBOLS_3 =   0b100000
    CASE_ALL_SYMBOLS = (CASE_SYMBOLS_1|CASE_SYMBOLS_2|CASE_SYMBOLS_3)

    BUTTONLAYOUT_MASK =   0b111
    LANGUAGE_MASK =     0b11000

    alphaCaseDetectionDict = {
                            LAYOUT_QWERTY:'Q',
                            LAYOUT_ITUT:'DEF',
                            LAYOUT_EMAIL:'Q',
                             }

    specialCharacterViewDetectionDict = {
                               LAYOUT_QWERTY:'ABC',
                               LAYOUT_ITUT:'?123',
                               LAYOUT_EMAIL:'ABC',
                               }

    spaceButtonText = {
                       LAYOUT_LANG_EN:['EN','EN-GB','ENG'],
                       LAYOUT_LANG_CH:['ZH-CN']
                       }

    # button names will be given values the first time vkb existence is checked
    shiftButtonNames = []
    numberModeNames = []
    returnButtonNames = []
    callbuttonNames = []
    backspaceButtonNames = []

    inputInterval = {"normal":40,
                     "slow":100}

    def __init__(self):
        self.__layoutMaps = {}
        self.__REentrantLock = False
        self.currentLayout = None
        self.currentCase = None
        self.phone = None
        self.capsLockOn = False
        self.prevLanguage = None
        self.prevKBFeatures = None

        self.gls = None # leader service

        # Visited views contains flags for views that are known by virtual keyboard
        self.__visitedViews = 0b0
        self.vkbOnScreen = False
        self.orientation = None

        '''
        self.modifierStatusDict = {
                                   'case':self.CASE_UPPER,
                                   'symbol':self.CASE_SYMBOLS_2
                                   }
        '''

        self.searchstring = ""
        self.waitingForVKB = False
        self.timeout = None
        self.inputLanguage = None

    def setPhone(self,phone):
        """ Set new phone instance to virtual keyboard-class

        Parameters:
            phone (Phone)  :   new phone-instance
        """
        self.phone = phone

    def _resetVKB(self):
        """ """
        self.__layoutMaps = {}
        self.__visitedViews = 0b0
        self.currentLayout = None
        self.orientation = None

    def __getCase(self, keyboard):
        """ Resolve correct case

        """

        alphaKeys = keyboard.Keys.FindAll(lambda k:k.Label.isalpha())

        if len(alphaKeys)>10: # e.g. space and enter are counted as alpha so use value large enough
            if keyboard.ShiftMode == 0:
                self.currentCase = self.CASE_LOWER
            else:
                self.currentCase = self.CASE_UPPER
        else:
            if keyboard.Keys.Find(lambda k:k.Label=="@"):
                self.currentCase = self.CASE_SYMBOLS_1
            else:
                self.currentCase = self.CASE_SYMBOLS_2


        if keyboard.ShiftMode == 2:
            self.capsLockOn = True


    def __findKey(self, keyboard, keyName):
        """ """

        result = keyboard.Keys.FindAll(lambda key: key.Label == keyName)

        if result.Count < 1:
            return None
        return result[0]

    def __checkLayout(self):
        """ Check layout from display and add layouts to dict if needed

        Parameters:
            getNewDump(bool)    :   set to false if new dump from phone is not needed
        """

        if self.phone.isFollower():
            debug.out('follower mode, no layout check')
            return

        if self.__REentrantLock:
            return

        keyboard = self.phone._tab._tabConn.TestServerClient.Keyboard

        self.inputLanguage = keyboard.Locale
        self.orientation = eval("self.LAYOUT_%s"%self.phone.orientation().upper())
        self.currentLayout = self.LAYOUT_QWERTY
        self.currentLayout = self.currentLayout | self.LAYOUT_LANG_EN
        self.currentLayout = self.currentLayout | self.orientation
        self.prevLanguage = self.inputLanguage

        self.__getCase(keyboard)

        debug.out("__checkLayout: %s"%self.currentCase)

        if self.currentLayout not in self.__layoutMaps.keys():
            self.__layoutMaps[self.currentLayout] = {}

        # Find coordinates for shift-key
        shiftKey = self.__findKey(keyboard, "shift")
        # Map page-key to shift with qwerty-layout
        if not shiftKey:
            shiftKey = self.__findKey(keyboard, "page")
        if shiftKey:
            xc = shiftKey.X+(shiftKey.W/2)
            yc = shiftKey.Y+(shiftKey.H/2)

            if self.currentLayout&self.BUTTONLAYOUT_MASK&self.LAYOUT_QWERTY or \
                self.currentLayout&self.BUTTONLAYOUT_MASK&self.LAYOUT_EMAIL:
                self.__layoutMaps[self.currentLayout]['shift']=((xc,yc),self.CASE_LOWER|self.CASE_UPPER|self.CASE_SYMBOLS_1|self.CASE_SYMBOLS_2,False)
            else:
                self.__layoutMaps[self.currentLayout]['shift']=((xc,yc),self.currentCase,False)

        # Collect all characters from current view to dictionary
        for characterKey in keyboard.Keys.FindAll(lambda key: len(key.Label) == 1):
            character = characterKey.Label
            xc = characterKey.X+(characterKey.W/2)
            yc = characterKey.Y+(characterKey.H/2)

            if character.isalpha():
                # Upper- and lower-case alphabets are in same locations
                self.__layoutMaps[self.currentLayout][character.lower()]=((xc,yc),self.CASE_LOWER,False)
                self.__layoutMaps[self.currentLayout][character.upper()]=((xc,yc),self.CASE_UPPER,False)
            else:
                if self.__layoutMaps[self.currentLayout].has_key(character) and \
                   self.__layoutMaps[self.currentLayout][character][1] == (xc,yc):

                    cases = self.__layoutMaps[self.currentLayout][character][1] & self.currentCase
                    self.__layoutMaps[self.currentLayout][character]=((xc,yc),cases,False)
                else:
                    self.__layoutMaps[self.currentLayout][character]=((xc,yc),self.currentCase,False)

        # Add popup list characters
        for popUpContainer in keyboard.Keys.FindAll(lambda key: key.PopUpKeys):
            for popUpCharacter in popUpContainer.PopUpKeys:
                character = popUpCharacter.Key
                xc = popUpContainer.X+(popUpContainer.W/2)
                yc = popUpContainer.Y+(popUpContainer.H/2)

                if character.isalpha():
                    # Upper- and lower-case alphabets are in same locations
                    self.__layoutMaps[self.currentLayout][character.lower()]=((xc,yc),self.CASE_LOWER,True)
                    self.__layoutMaps[self.currentLayout][character.upper()]=((xc,yc),self.CASE_UPPER,True)
                else:
                    if self.__layoutMaps[self.currentLayout].has_key(character) and \
                       self.__layoutMaps[self.currentLayout][character][1] == (xc,yc):

                        cases = self.__layoutMaps[self.currentLayout][character][1] | self.currentCase
                        self.__layoutMaps[self.currentLayout][character]=((xc,yc),cases,True)
                    else:
                        self.__layoutMaps[self.currentLayout][character]=((xc,yc),self.currentCase,True)




        spaceKey = self.__findKey(keyboard, "space")
        if spaceKey:
            xc = spaceKey.X+(spaceKey.W/2)
            yc = spaceKey.Y+(spaceKey.H/2)
            if self.currentLayout&self.LAYOUT_ITUT:
                self.__layoutMaps[self.currentLayout][' ']=((xc,yc),self.CASE_LOWER|self.CASE_UPPER,False)
            else:
                self.__layoutMaps[self.currentLayout][' ']=((xc,yc),self.CASE_LOWER|self.CASE_UPPER|self.CASE_SYMBOLS_1|self.CASE_SYMBOLS_2,False)

        changeKey = self.__findKey(keyboard, "change")

        if changeKey:
            xc = changeKey.X+(changeKey.W/2)
            yc = changeKey.Y+(changeKey.H/2)
            self.__layoutMaps[self.currentLayout]['change']=((xc,yc),self.CASE_LOWER|self.CASE_UPPER|self.CASE_SYMBOLS_1|self.CASE_SYMBOLS_2,False)


        clearKey = self.__findKey(keyboard, "delete")
        if clearKey:
            xc = clearKey.X+(clearKey.W/2)
            yc = clearKey.Y+(clearKey.H/2)
            self.__layoutMaps[self.currentLayout]['clear']=((xc,yc),self.CASE_LOWER|self.CASE_UPPER|self.CASE_SYMBOLS_1|self.CASE_SYMBOLS_2,False)

        enterKey = self.__findKey(keyboard, "enter")
        if enterKey:
            xc = enterKey.X+(enterKey.W/2)
            yc = enterKey.Y+(enterKey.H/2)
            self.__layoutMaps[self.currentLayout]['\n']=((xc,yc),self.CASE_LOWER|self.CASE_UPPER|self.CASE_SYMBOLS_1|self.CASE_SYMBOLS_2,False)

        # Add current view to already known views
        if self.currentCase&(self.CASE_LOWER|self.CASE_UPPER) and not self.currentLayout&self.LAYOUT_ITUT:
            self.__visitedViews = self.__visitedViews|self.CASE_LOWER|self.CASE_UPPER
        else:
            self.__visitedViews = self.__visitedViews|self.currentCase

        self.__REentrantLock = False
        return

    def __getCoordinateListForString(self, string, firstCharacter):
        """ Returns list of coordinates for all characters which can be enterd without changing case

        Parameters:
            string  :   string which contains all character that need to be entered
            firstCharacters(bool)   :   set to true if string contains first character of the textinput-field
        """
        coordinateList = []
        charactersEntered = 0
        breakReason = None

        for i in range(len(string)):
            # Get coordinates for keys as long the case needs to be changed. FIXME! add switchCase to loop
            # no need to care about case in Email layout with other than alphabet characters
            if string[i] in self.__layoutMaps[self.currentLayout].keys() and \
               (self.__layoutMaps[self.currentLayout][string[i]][1]&self.currentCase):
                coords, case, isPopUp = self.__layoutMaps[self.currentLayout][string[i]]

                if isPopUp:
                    breakReason = 'popup'
                    break

                coordinateList.append(coords)
                if self.currentCase==self.CASE_UPPER and not self.capsLockOn:
                    self.currentCase = self.CASE_LOWER
                charactersEntered +=1
            else:
                breakReason = 'case'
                break

        return (coordinateList,charactersEntered,breakReason)

    def __switchCase(self, character):
        """ This method changes the case according to current case and next character

        Parameters:
            character   :   next character that needs to be entered
        """

        layoutViews = self.CASE_LOWER|self.CASE_UPPER|self.CASE_SYMBOLS_1|self.CASE_SYMBOLS_2
        # FIXME: Don't use isalpha etc. Use case bit mask support in dict instead!

        # Search correct view for character if it is not found from layoutMap-dictionary and content of some view(s) are not known
        stopLoop = 0
        while (character not in self.__layoutMaps[self.currentLayout].keys()) and (self.__visitedViews!=layoutViews) and stopLoop < 10:
            #Change to symbol mode if characters is not alphabet and current case is either lower or upper
            if not character.isalpha() and self.currentCase&(self.CASE_LOWER|self.CASE_UPPER):
                self.phone._touch.press(self.__layoutMaps[self.currentLayout]['change'][0])

                self.currentCase = self.CASE_SYMBOLS_1
                self.phone._run('Switch case',testStepReporting=False)
                debug.out("Case switched to CASE_SYMBOLS_1")
            # Switch between symbol mode cases if character is not alphabet
            elif not character.isalpha() and self.currentCase&self.CASE_ALL_SYMBOLS:
                self.phone._touch.press(self.__layoutMaps[self.currentLayout]['shift'][0])
                self.phone._run('Switch case',testStepReporting=False)
                if self.currentCase&self.CASE_SYMBOLS_1:
                    self.currentCase = self.CASE_SYMBOLS_2
                    debug.out("Case switched to CASE_SYMBOLS_2")
                else:
                    self.currentCase = self.CASE_SYMBOLS_1
                    debug.out("Case switched to CASE_SYMBOLS_1")

            elif character.isalpha():
                if character.isalpha() and not self.currentCase&(self.CASE_LOWER|self.CASE_UPPER):
                    self.phone._touch.press(self.__layoutMaps[self.currentLayout]['change'][0])


                    self.phone._run('Switch case',testStepReporting=False)
                    self.currentCase = self.CASE_LOWER
                    debug.out("Case switched to CASE_LOWER")
            # add small delay to ensure keyboard view has changed
            self.phone.delay(300,False)
            self.__checkLayout()
            stopLoop += 1

        self.phone.failUnless(character in self.__layoutMaps[self.currentLayout].keys(), "Character %s not found from keyboard keys: %s"%(character,self.__layoutMaps[self.currentLayout].keys()))

        desiredCase = self.__layoutMaps[self.currentLayout][character][1]

        # Loop until correct case is reached
        stopLoop = 0
        while not self.currentCase&desiredCase and stopLoop < 10:
            coordinates = []

            if self.currentCase&(self.CASE_LOWER|self.CASE_UPPER):
                #Switch from alphabet state
                if desiredCase&(self.CASE_LOWER|self.CASE_UPPER):
                    # Switch between upper- and lower-case
                    debug.out('Switch between upper- and lower-case')
                    coordinates.append(self.__layoutMaps[self.currentLayout]['shift'][0])
                    # Switch current case with bitwise XOR-operation
                    self.currentCase = self.currentCase ^ (self.CASE_LOWER|self.CASE_UPPER)
                else:
                    #Switch from alpha to special character
                    debug.out('Switch from alpha to special character')
                    coordinates.append(self.__layoutMaps[self.currentLayout]['change'][0])
                    self.currentCase = self.CASE_SYMBOLS_1
            else:
                #Switch from special character state
                #With ITU-T layout this handles also transition from number- to alpha-mode
                if desiredCase&(self.CASE_LOWER|self.CASE_UPPER):
                    debug.out('Switch from special character to alpha')
                    coordinates.append(self.__layoutMaps[self.currentLayout]['change'][0])

                    self.currentCase = self.CASE_LOWER
                else:
                    # Switch between first and second special character screens
                    debug.out('Switch between first and second special character screens')
                    coordinates.append(self.__layoutMaps[self.currentLayout]['shift'][0])
                    # Switch current case with bitwise XOR-operation
                    self.currentCase = self.currentCase ^ (self.CASE_SYMBOLS_1|self.CASE_SYMBOLS_2)

            if coordinates:
                debug.out("switchCase: currentCase: %s, desiredCase: %s"%(self.currentCase,desiredCase))
                self.phone._touch.press(coordinates)
                self.phone._run('Switch case',testStepReporting=False)
                # add small delay to ensure keyboard view has changed
                self.phone.delay(300,False)
            else:
                debug.out("No coordinates in switchCase! currentCase: %s, desiredCase: %s"%(self.currentCase,desiredCase))


            stopLoop += 1

        if not self.__visitedViews&self.currentCase:
            self.__checkLayout()

    def getClearButtonCoordinates(self):
        """ Returns coordinates of clear-button

        """
        if self.__layoutMaps[self.currentLayout].has_key('clear'):
            return self.__layoutMaps[self.currentLayout]['clear'][0]
        else:
            return False

    def getEnterButtonCoordinates(self):
        """ Returns coordinates of enter-button

        """
        if self.__layoutMaps[self.currentLayout].has_key('\n'):
            return self.__layoutMaps[self.currentLayout]['\n'][0]
        else:
            return False

    def pressKeyboardButton(self, button):
        """ This method is used to press a button on virtual keyboard

        """
        if self.__layoutMaps[self.currentLayout].has_key(button):
            self.phone._touch.press(self.__layoutMaps[self.currentLayout][button][0])
            self.phone._run('Switch case',testStepReporting=False)
            return True
        else:
            return False

    def waitForVKB(self, timeout=None):
        """ This method is used to check if virtual keyboard is visible on the screens

        parameteres:
            timeout(int) : Time in milliseconds to wait for virtual keyboard to become visible

        """
        returnValue = None
        if not timeout:
            if self.timeout:
                timeout = self.timeout
            else:
                timeout=core.FW_conf['settings'].System.ExpectTimeout

        startTime = time.time()

        vkbErrorPrinted = False
        i = 0
        while returnValue== None:
            if (time.time()-startTime) > timeout/1000.0:
                self.phone.fail("Cannot find virtual keyboard from screen")
                returnValue =  False


            if not self.phone._tab._tabConn.TestServerClient.Keyboard or not self.phone._tab._tabConn.TestServerClient.Keyboard.KeyboardOn or not self.phone._tab._tabConn.TestServerClient.Keyboard.Locale:
                if i==0:
                    self.phone.comment("Wait for virtual keyboard")
            else:
                returnValue = True

            i+=1

        return returnValue

    def __selectPopupKey(self, key):
        """ Select character from popup-list

            parameters
                key : character which should be entered

        """
        y_offset = 10

        coords, case, isPopUp = self.__layoutMaps[self.currentLayout][key]

        success, touchActionSucceeded = self.phone._tab._executeTabOperation(self.phone._tab.touchDown,coords[0],coords[1])
        self.phone.delay(1000, False)

        try:
            popupKey = self.phone._tab._tabConn.TestServerClient.Keyboard.Keys.Find(lambda k: k.Label == key)
            x = popupKey.X+(popupKey.W/2)
            y = popupKey.Y+(popupKey.H/2)+y_offset
        except Exception:
            success, touchActionSucceeded = self.phone._tab._executeTabOperation(self.phone._tab.touchUp,x,y)
            self.phone.fail("Unable to input %s using popup-list"%key)

        success, touchActionSucceeded = self.phone._tab._executeTabOperation(self.phone._tab.touchMove,x,y)
        self.phone.delay(300, False)
        success, touchActionSucceeded = self.phone._tab._executeTabOperation(self.phone._tab.touchUp,x,y)

        self.phone.delay(500,False)
        self.__getCase(self.phone._tab._tabConn.TestServerClient.Keyboard)

        return 1


    def _write(self, string, defaultText='', timeout=None, delay=None):
        """ Method for entering text using VKB.

        Parameters:
            string      :   string to be entered
            defaultText :   Text already in textinput-field
            timeout     :   Time to wait for keyboard to appear
            delay       :   Delay between keypresses
        """

        if self.phone.isLeader():
            if self.gls == None:
                self.gls = core.FW_conf['leader']
            # if writed text equals the phone number settings, it needs to be evaluated in follower
            ret = needsEvaluation(string)
            if ret and ret[0]:
                self.gls.inputParams.Add(ret[1])
                debug.brf('Writing %s in Follower' % str(self.gls.inputParams[0]))
                self.gls.sendTouches = False
            else:
                self.gls.sendTouches = True

        if len(string):
            self.phone.sendWaitMessageToMarbleGUI( int(len(string) * 0.5 ), 'Writing with virtual keyboard. Wait %s seconds.' % ( int(len(string) * 0.5) ))
        else:
            self.phone.fail('Cannot write empty text!')

        self.timeout = timeout
        self.__checkLayout()
        # check that do we have spaces in the string
        splittedStrings = string.split(' ')

        for splittedString in splittedStrings[:]:
            # check that did we have spaces in the string
            # add space to string if needed
            if len(splittedStrings) > 1 and \
               splittedStrings.index(splittedString) != splittedStrings.index(splittedStrings[-1]):
                splittedString += ' '

            # Last item in list is empty if string to write ends to space. 
            if len(splittedString)==0:
                break

            charactersLeft = len(splittedString)
            if self.phone.isFollower():
                # temporary, allow basic writing
                debug.out('follower, selecting current case')
                if self.currentLayout & self.LAYOUT_DIALER or self.currentLayout & self.LAYOUT_NUMBER_MODE:
                    debug.out('LAYOUT CASE LOWER')
                    self.currentCase = self.CASE_ITUT_NUMBERS
                elif self.currentLayout & self.LAYOUT_EMAIL:
                    debug.out('LAYOUT EMAIL. CASE LOWER')
                    self.currentCase = self.CASE_LOWER
                elif self.currentLayout & self.LAYOUT_PORTRAIT and self.currentLayout & self.LAYOUT_QWERTY:
                    debug.out('LAYOUT PORTRAIT QWERTY CASE LOWER')
                    self.currentCase = self.CASE_LOWER
                else:
                    debug.out('LAYOUT DEFAULT, CASE UPPER')
                    self.currentCase = self.CASE_UPPER
            else:
                self.__getCase(self.phone._tab._tabConn.TestServerClient.Keyboard)
            characterCoordinates = []

            #Switch to correct case
            self.__switchCase(splittedString[0])

            # Enter first charcter separately to verify correct case after it has been entered
            if (not self.currentLayout&self.LAYOUT_DIALER and not self.currentLayout&self.LAYOUT_NUMBER_MODE) or self.capsLockOn:
                # Get coordinates for keys. If empty list is returned text cannot be entered.
                characterCoordinates, charactersEntered, breakReason = self.__getCoordinateListForString(splittedString[0], defaultText=='' and charactersLeft==len(splittedString))
                if not breakReason == 'popup':
                    self.phone.failUnless(charactersEntered,"Cannot write text: '%s'"%splittedString)

                    charactersLeft -= charactersEntered

                    debug.out("_write: %s"%characterCoordinates)
                    debug.out('Enter first character "%s"'%splittedString[0])

                    self.phone._touch.press(characterCoordinates, wait=delay, waitUntilNoUIevents=False )
                    self.phone._run('Enter first character "%s"'%splittedString[0],testStepReporting=False)
                else:
                    charactersEntered = self.__selectPopupKey(splittedString[0])
                    charactersLeft -= charactersEntered

                # Check layout to verify case after the first character
                if charactersLeft:
                    if self.phone.isFollower():
                        if self.currentLayout & self.LAYOUT_DIALER or self.currentLayout & self.LAYOUT_NUMBER_MODE:
                            debug.out('LAYOUT ITUT_NUMBERS')
                            self.currentCase = self.CASE_ITUT_NUMBERS
                        else:
                            debug.out('SETTING CASE LOWER')
                            self.currentCase==self.CASE_LOWER
                    else:
                        self.phone.delay(150, testStepReporting = False)
                        self.__checkLayout()

            # Loop until all characters are entered
            while charactersLeft:
                if self.phone.isFollower(): # slow down the writing in follower. some chars will not appear correctly if too fast
                    self.phone.delay(100, testStepReporting = False)
                characterCoordinates = []
                startIndex = len(splittedString)-charactersLeft

                #Switch to correct case
                self.__switchCase(splittedString[startIndex])

                # Get coordinates for keys. If empty list is returned text cannot be entered.
                characterCoordinates, charactersEntered, breakReason = self.__getCoordinateListForString(splittedString[startIndex:], defaultText=='' and charactersLeft==len(splittedString))
                if not charactersEntered and not breakReason == "popup":
                    self.phone.failUnless(charactersEntered,"Cannot write text: '%s'"%splittedString)

                charactersLeft -= charactersEntered

                debug.out("_write: %s"%characterCoordinates)
                debug.out('Enter characters "%s"'%splittedString[startIndex:len(splittedString)-charactersLeft])

                # With long texts it might be possible that message to server is too large.
                # Split too large messages by using maxStringLengthToServer-variable
                coordsLeft = len(characterCoordinates)
                coordsStartIndex = 0
                wait = delay != None and delay or self.inputInterval[core.FW_conf["settings"].System.InputInterval]
                while coordsLeft:
                    if coordsLeft<self.maxStringLengthToServer:
                        debug.out("Writing from index %s to %s"%(coordsStartIndex,len(characterCoordinates)))
                        self.phone._touch.press(characterCoordinates[coordsStartIndex:], wait=wait, waitUntilNoUIevents=False)
                        self.phone._run('Enter characters "%s"'%splittedString[startIndex:len(splittedString)-charactersLeft],testStepReporting=False)
                        coordsLeft = 0
                    else:
                        self.phone._touch.press(characterCoordinates[coordsStartIndex:(coordsStartIndex+self.maxStringLengthToServer)], wait=wait, waitUntilNoUIevents=False)
                        self.phone._run('Enter characters "%s"'%splittedString[startIndex+coordsStartIndex:len(splittedString)-charactersLeft],testStepReporting=False)
                        coordsStartIndex += self.maxStringLengthToServer
                        coordsLeft = len(characterCoordinates)-coordsStartIndex
                        debug.out("coordsStartIndex: %s, coordsLeft: %s"%(coordsStartIndex,coordsLeft))
                if breakReason == 'popup':
                    charactersEntered = self.__selectPopupKey(splittedString[startIndex+charactersEntered])
                    charactersLeft -= charactersEntered

        # Leader has all information for inputting a environment specific text string at this point
        if self.phone.isLeader() and not self.gls.sendTouches:
            self.gls.SendLayoutMaps(repr(self.__layoutMaps))
            self.gls.ExecuteString('self.uiState.vkb._VirtualKeyboard__visitedViews=%s' % self.__visitedViews)
            self.gls.ExecuteString('self.uiState.vkb.currentLayout=%s' % self.currentLayout)
            if self.gls.inputParams[0] != None:
                self.gls.InputString(self.gls.inputParams[0], True)
            else:
                self.gls.InputString(string) # should not get here
            self.gls.inputParams.Clear()
            self.gls.sendTouches = True

