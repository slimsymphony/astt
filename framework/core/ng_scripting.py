# -*- coding: utf-8 -*-
"""
Created on 2.3.2012

@author: teemukok
"""
import os, time, core, types, math, random, fnmatch, threading, re, json, calendar
from datetime import date, datetime
from string import maketrans

from core import uitestcase, scripting
from core import phone
from core.testcase_exceptions import TestException
from utils.nodeutils import NodeUtils
from core.leader import needsEvaluation

import clr
clr.AddReference('System')
from System import DateTime
from System.Globalization import CultureInfo, DateTimeStyles

def unescape(t):
    """Revert HTML-escape the text in `t`."""
    return (t
        .replace("&amp;", "&").replace("&lt;", "<").replace("&gt;", ">")
        .replace("&#39;", "´").replace("&quot;", '"').replace('&apos;',"'")
        )

def escape(t):
    """HTML-escape the text in `t`."""
    return (t
        .replace("&", "&amp;").replace("<", "&lt;").replace(">", "&gt;")
        .replace("´", "&#39;").replace('"', "&quot;").replace("'",'&apos;')
        )


class NGUIState(object):
    """
    This class holds status for current UI state of the phone.

    """
    LANDSCAPE = 1
    PORTRAIT = 2

    VISIBLE = 0
    HIDDEN = 1
    NOT_FOUND = 2

    def __init__(self, phone):
        """ Initial values for UI state

        """
        # Contains just visible items
        self.currentState = None
        # Contains the whole dump
        self.currentStateFull = None
        self.currentApplication = None
        self.statusbarHeight = 0
        self.breathingLineHeight = 0
        self.screenOrientation = self.PORTRAIT
        self.phone = phone
        self.vkb = VirtualKeyboard()
        self.vkb.setPhone(self.phone)
        self.__uiChangedLock = threading.Lock()
        self.vkbTransitionInProgress = False

        # set phone UI to changed by default
        self.__uiChanged = True

        # phone screen height and width variables
        # these will be updated automatically during test execution
        self.__SCREEN_WIDTH  = 480
        self.__SCREEN_HEIGHT = 800

        # this will be set to true in following test case actions: display capture, menu and images
        # we can't do anything extra with these actions when new UI dump arrives
        self._skipNewUIState = False

    def getScreenWidth(self):
        """Returns SCREEN_WIDTH."""
        return self.__SCREEN_WIDTH

    def getScreenHeight(self):
        """Returns SCREEN_HEIGHT."""
        return self.__SCREEN_HEIGHT

    def getPreventNativeDigitsInField(self):
        """ Returns True if widget which has focus prevents native digits """
        try:
            return eval(self.phone.sx('(send (send (send (send primary-root-container get-focused) get-focused) get-focused) get-prevent-native-digits)', convertToString=True, doNotReport=True).title())
        except Exception:
            return True

    def getNativeDigitsList(self):
        """ Returns native digit list from phone"""
        return self.phone.sx('(send config-manager get-setting "./yapas/display/native-digits")',convertToString=True, doNotReport=True)

    def getGlobalNativeDigitsSetting(self):
        """ """
        return eval(self.phone.sx('(send config-manager get-boolean "./yapas/display/native-digits-enabled")',convertToString=True, doNotReport=True).title())

    def setUIChanged(self, value):
        """Thread safe setter for self.__uiChanged."""
        with self.__uiChangedLock:
            self.__uiChanged = value

    def __getUIChanged(self):
        """Thread safe getter for self.__uiChanged."""
        with self.__uiChangedLock:
            return self.__uiChanged

    def setNewState(self, node):
        """ This method is called by teststep_analyzer(and displayUpdateListener when implementation is finished)
            when new ui dump is received from Granite server

        Parameters:
            node(NodeUtils) :   Screen dump xml
        """
        # initialize test step so that we won't run any steps in previous test step
        # FIXME: Remove this and improve test step clearing logic
        self.phone._initTestStep()

        t1 = time.time()
        self.currentState = NodeUtils(node)
        self.currentStateFull = NodeUtils(node)

        self.__setScreenProperties()

        if not self._skipNewUIState:
            self.__getBreathingLineHeight()

        applicationNodeList = self.currentState.findall('//application')
        if len(applicationNodeList):
            applicationNode = applicationNodeList[-1]
            self.currentApplication = applicationNode.getAttribute("name") or None
        else:
            self.currentApplication =  None

        if self.getGlobalNativeDigitsSetting():
            self.addNativeDigits()

        self.__processJavaNode()

        self.__buildViewFromDump(self.currentState)
        self.__getStatusbarHeight()

        if not self._skipNewUIState:
            self.vkb._isVKBOnScreen(node)

        debug.out("XML-dump processing took %s seconds"%(time.time()-t1))

    def __processJavaNode(self):
        """ Move a node containing java texts and images under the java-widget-node

        """
        javaNode = self.currentState.find('java')
        if javaNode:
            javaWidgetNode = self.currentState.find('//java-widget')

            # Sometimes Granite server does not receive notification about topmost-screen-changed-event and java-node is sent to FW
            # There's no midlet visible if java-widget-node is not found from dump
            if javaWidgetNode:
                # Replace attribute names
                for node in javaNode.findall('*'):
                    node.setAttribute('coords',"%s,%s,%s,%s"%(node["x"], node["y"], node["width"], node["height"]))
                    node.setAttribute('handled-touch-events','press')
                    node.removeAttribute('x')
                    node.removeAttribute('y')
                    node.removeAttribute('width')
                    node.removeAttribute('height')
                    for attr in node.getAttributes(iterValues=True):
                        if attr[0].find("_")>-1:
                            node.setAttribute(attr[0].replace('_','-'),attr[1])
                            node.removeAttribute(attr[0])
                        elif attr[0]=='fg':
                            node.setAttribute('fore-color',attr[1])
                            node.removeAttribute(attr[0])
                    if node.getName()=='label':
                        node.setAttribute('text',node["text"])
                        node["text"] = ''
                    elif node.getName()=='image_widget':
                        node.setName('image-widget')
                        if self.phone.server_version['yyy'] > 4 or (self.phone.server_version['yyy'] == 4 and self.phone.server_version['xxx'] >= 4):
                            node.setAttribute('image',node["text"])
                            node["text"] = ''
                        else:
                            node.setAttribute('image',self.phone.getJavaImageFilename(node.getAttribute('animation-id')))
                    node.setAttribute('visible','true')

                javaNode.setAttribute('visible', 'true')
                javaNode.setAttribute('coords', javaWidgetNode.getAttribute('coords'))
                javaWidgetNode.append(NodeUtils(javaNode))
                self.currentState.remove(javaNode)

    def __buildViewFromDump(self, dumpXml):
        """ Builds view from items which are visible on phone display
        """
        view = NodeUtils('container',True)

        containerId = 0
        nodeId = 0

        onStatusbar = False
        isScrollable = False
        onTabArea = False
        self.vkbTransitionInProgress = False

        # Go throught the dump and set left/right/top/bottom/width/height/center-x/center-y
        # TODO: remove when dump contains these
        for node in dumpXml.findall('//*'):
            try:
                if node.getName()=="textinput":
                    name = "text"
                x,y,w,h = [int(p) for p in node.getAttribute('coords').split(",")]
                node.setAttribute('left',str(x))
                node.setAttribute('right',str(x+w))
                node.setAttribute('top',str(y))
                node.setAttribute('bottom',str(y+h))
                node.setAttribute('width',str(w))
                node.setAttribute('heigth',str(h))
                node.setAttribute('center-x',str(x+(w/2)))
                node.setAttribute('center-y',str(y+(h/2)))
                node.setAttribute('id',nodeId)
                nodeId +=1
            except Exception,e:
                x = y = w = h = None
                pass

        #loop through the items which are itself visible and do not have ancestor that is not visible
        for node in dumpXml.findall('//*[(@visible="true" or @visible="hidden" or ancestor::evo-dynamic-keyboard) and @width>"0" and @heigth>"0" and @center-x>="0" and @center-x<="%s" and not(ancestor::*[@visible="false" or @width<="0" or @heigth<="0"])]' % self.getScreenWidth()):

            # Check if VKB transition is in progress
            if node.getName() == 'evo-dynamic-keyboard':
                if int(node.getAttribute('bottom')) > self.getScreenHeight() and int(node.getAttribute('top')) <= self.getScreenHeight():
                    self.vkbTransitionInProgress = True

            # Check if VKB special characters popup hides everything else. (the popup which opens with e.g. select.long(','))
            if node.getName() == 'stacked-container':
                appStackContainer = node.find("preceding-sibling::app-stack-container")
                if appStackContainer:
                    stackedContainer = node.find("preceding-sibling::stacked-container")
                    if stackedContainer:
                        coords = stackedContainer.getAttribute('coords').split(',')
                        if int(coords[2])==self.__SCREEN_WIDTH and int(coords[3])==self.__SCREEN_HEIGHT:
                            view = None
                            view = NodeUtils('container',True)
                            containerId = 1

            # items in stacked-container- and application-nodes might overlap with former items
            if 'application' in node.getName() or 'container' in node.getName() or 'evo-dynamic-keyboard' in node.getName():
                if node.getName() == 'application': # whenever application node is received, old view will be discarded
                    view = None
                    view = NodeUtils('container',True)
                    containerId = 1
                else:
                    containerId +=1
                    if node.getName()=='stacked-container' or node.getName()=='evo-dynamic-keyboard':
                        coords = node.getAttribute("coords")
                        #Container covers other items if it has background color
                        if coords and (node.getAttribute("background-color") or node.getAttribute("name") == "tab-area" or \
                                node.getName()=='evo-dynamic-keyboard'):
                            view = self.__trimContainerArea([int(p) for p in coords.split(",")],view)

                if node.getAttribute('name') == 'tab-area':
                    onTabArea = True

            if node.getName() == 'screen':
                self.__clearRegionFromCurrentState([int(p) for p in node.getAttribute('coords').split(",")], view,-1)

            if node.getName() == 'statusbar': # when we start going through statusbar node, set flag. Will be disabled on next application or fast-menu node
                onStatusbar = True
                statusbarNode = NodeUtils(node.clone(), True) # create a new node for view from statusbar
                statusbarNode.getChildNodes(removeItems=True) # remove child nodes from newly created node
                view.append(statusbarNode)

            if node.getName() in ['application','fast-menu','evo-dynamic-keyboard','scroll-container'] and node.hasChildNodes():# and node.getAttribute('name')!='dialog-area':#'stacked-container',
                onStatusbar = False
                isScrollable = False
                if node.getName() == 'fast-menu' or node.getName() =='scroll-container': # fast-menu items are scrollable
                    isScrollable = True

                debug.out(node.getAttribute("name"))
                x,y,w,h = [int(p) for p in node.getAttribute('coords').split(",")]

                # NOTE: This is here so that fast-menu which is outside the screen doesn't clear container areas
                if node.getName() == 'fast-menu' and y < 0:
                    continue

                view = self.__clearContainerArea((x,y,w,h),view)

            elif (node.getName() =='image-widget' and node.getAttribute('image') or node.getName() in ['label','textinput']) and node.getAttribute('coords') or node.getName()=='key':
                try:
                    x,y,w,h = [int(p) for p in node.getAttribute('coords').split(",")]
                except Exception,e:
                    debug.out("Error in coords attribute: %s" % node.getAttribute('coords'))
                    raise e

                # Read bounding-box value for textinput to get actual text area
                if node.getName()=='textinput':
                    boxX,boxY,boxW,boxH = [int(p) for p in node.getAttribute('bounding-box').split(",")]
                    if boxW*boxH<w*h:
                        x = x+boxX
                        y = y+boxY
                        w,h = (boxW,boxH)
                        node.setAttribute('coords',"%s,%s,%s,%s"%(x,y,w,h))

                        node.setAttribute('left',str(x))
                        node.setAttribute('right',str(x+w))
                        node.setAttribute('top',str(y))
                        node.setAttribute('bottom',str(y+h))
                        node.setAttribute('width',str(w))
                        node.setAttribute('heigth',str(h))
                        node.setAttribute('center-x',str(x+(w/2)))
                        node.setAttribute('center-y',str(y+(h/2)))


                # read handled touch events from parent nodes for image-widget nodes
                if node.getName() == 'image-widget' and node.getAttribute('handled-touch-events') == "":
                    for i in range(2):
                        ancestorNode = node.find('./ancestor::*[%s]' % str(i + 1))

                        if ancestorNode and ancestorNode.getAttribute('handled-touch-events') != "":
                            node.setAttribute('handled-touch-events', ancestorNode.getAttribute('handled-touch-events'))
                            break

                if onTabArea:
                    view = self.__setNonTabAreaItemsFromRegionHidden((x,y,w,h),view)

                # If item is in form-editor or scoll-container get container area from parent of it.
                formEditorContainer = node.find("ancestor::form-editor")
                scrollContainer = node.find("ancestor::scroll-container")

                if formEditorContainer:
                    node.setAttribute('container-area',formEditorContainer.findall("ancestor::*[contains(name(),'container') and @top>='0']")[-1].getAttribute('coords'))
                elif scrollContainer:
                    node.setAttribute('container-area',scrollContainer.getAttribute('coords'))
                else:
                    button =  node.find(("ancestor::button"))
                    if button:
                        node.setAttribute('container-area',button.findall("ancestor::*[contains(name(),'container') and @top>='0']")[0].getAttribute('coords'))
                    else:
                        node.setAttribute('container-area',node.findall("ancestor::*[contains(name(),'container') and @top>='0']")[0].getAttribute('coords'))

                if node.getName() == 'key':
                    keyText = node.getAttribute('text')
                    node = NodeUtils(node.toxml())
                    if keyText:
                        node.setName('label')
                        node.setAttribute('text', keyText)
                    else:
                        node.setName('image-widget')
                        node.setAttribute('image', node.getAttribute('name'))

                    node.setAttribute('visible','true')
                    node.setAttribute('handled-touch-events','press')
                    #node.setAttribute('coords', key.getAttribute('coords'))
                    #view.append(newNode)

                node.setAttribute('center',"%s,%s"%(x+(w/2),y+(h/2)))
                node.setAttribute('container',str(containerId))
                # set information is the current item in statusbar area or not
                node.setAttribute('is-in-statusbar',str(onStatusbar).lower())

                # if tab area flag is on, do still a check if current item is still in a tab area container
                if onTabArea == True:
                    if len(node.findall('./ancestor::*[@name="tab-area"]')) == 0:
                        onTabArea = False

                # set information is the current item in tab area or not
                node.setAttribute('is-in-tab-area', str(onTabArea).lower())

                # if scrollable flag is on, do still a check if current item is still in a scrollable container
                if isScrollable == True:
                    if len(node.findall('./ancestor::scroll-container')) == 0 and len(node.findall('./ancestor::fast-menu')) == 0:
                        isScrollable = False

                    # Check visibility of scrollable items based on container area
                    cX, cY,cW,cH = [int(p) for p in node.getAttribute('container-area').split(",")]
                    containerArea = (cX, cY, cW, cH)
                    left = int(node.getAttribute("left"))
                    right = int(node.getAttribute("right"))
                    top = int(node.getAttribute("top"))
                    bottom = int(node.getAttribute("bottom"))

                    if (self.__isPointOnArea((left,top), containerArea) or self.__isPointOnArea((right,top), containerArea) or
                        self.__isPointOnArea((left,bottom), containerArea) or self.__isPointOnArea((right,bottom), containerArea) or
                        (top<cY and bottom>cY+cH) or (left<cX and right>cX+cW)):
                        node.setAttribute('visible','true')
                    else:
                        node.setAttribute('visible','hidden')

                node.setAttribute('is-scrollable',str(isScrollable).lower())
                debug.out("Adding node %s to xml"%node.getName())
                if not node in view:
                    view.append(NodeUtils(node))

        self.currentState = view
        debug.out(self.currentState.toprettyxml())

        # save current state (visible xml) for debugging purposes
        if not os.path.isdir(os.path.join(core.FW_conf["test_result_dir"],'application_xml')):
            os.makedirs(os.path.join(core.FW_conf["test_result_dir"],'application_xml'))
        self.currentState.save(os.path.join(core.FW_conf["test_result_dir"],'application_xml',"%s_%s.xml"%(self.phone.getName(),(self.currentApplication and self.currentApplication or 'unknown')+'_visible')))

    def __clearContainerArea(self, area, view):
        """ Removes items which have container in area given in area-parameter

        """
        x,y,w,h = area

        # Loop through all objects on screen and remove ones which container area is completely covered by given area
        for node in view.findall('/*[@container-area]'):
            containerX, containerY,containerW,containerH = [int(p) for p in node.getAttribute('container-area').split(",")]
            if containerX>=x and containerX+containerW<=x+w and containerY>=y and containerY+containerH<=y+h:
                if node.getName() in ['label','textinput']:
                    debug.out("Removing node %s(%s,%s) from area %s,%s,%s,%s"%(node.getAttribute("text"),containerX+containerW/2, containerY+containerH/2,x,y,w,h))
                view.remove(node)

        return view

    def __clearRegionFromCurrentState(self,area, view, currentContainer):
        """ Removes all items from given area

        """
        x,y,w,h = area

        # Loop through all objects on screen and remove ones which are completely covered by given area and are not in same container as area
        for node in view.findall('/*[@center and @container!="%s"]'%currentContainer):
            nodeX, nodeY, nodeW, nodeH = [int(p) for p in node.getAttribute('coords').split(",")]
            if nodeX>=x and (nodeX+nodeW)<=(x+w) and nodeY>=y and (nodeY+nodeH)<=(y+h):
                if node.getName()=='label':
                    debug.out("Removing node %s(%s,%s,%s,%s) from area %s,%s,%s,%s"%(node.getAttribute("text"),nodeX, nodeY,nodeW,nodeH,x,y,w,h))
                view.remove(node)

        return view

    def __setNonTabAreaItemsFromRegionHidden(self,area, view):
        """ Removes all non tab-area items from given area

        """
        x,y,w,h = area

        # Loop through all objects on screen and remove ones which are completely covered by given area and are not in same container as area
        for node in view.findall('/*[@center and @is-in-tab-area="false"]'):
            nodeX, nodeY, nodeW, nodeH = [int(p) for p in node.getAttribute('coords').split(",")]
            if nodeX>x and (nodeX+nodeW)<(x+w) and nodeY>y and (nodeY+nodeH)<(y+h):
                if node.getName()=='label':
                    debug.out("Removing node %s(%s,%s,%s,%s) from area %s,%s,%s,%s"%(node.getAttribute("text"),nodeX, nodeY,nodeW,nodeH,x,y,w,h))

                node.setAttribute("visible","hidden")
        return view

    def __trimContainerArea(self, area, view):
        """ Trim visible areas of container on lower layers if areas overlap

            Parameters:
                area(tuple or list) :   coordinates of new container(x,y,w,h)
                view(NodeUtils)     :   Node containing visible items.

        """
        t1 = time.time()
        x,y,w,h = area

        if w < self.getScreenWidth() or y < 0 or y > self.getScreenHeight():
            return view

        for node in view.findall('/*[@container-area]'):
            cX, cY, cW, cH = [int(p) for p in node.getAttribute('container-area').split(",")]

            # Trim top of the lower container if new container covers upper portion of lower container
            if y<=cY and y+h>cY:
                cH=cH-(cY-(y+h))
                cY = y+h
            elif y>cY and cY+cH>y: # Trim bottom of the lower container
                cH=y-cY
            else:
                continue

            node.setAttribute("container-area","%s,%s,%s,%s"%(cX, cY, cW, cH))
            if int(node.getAttribute("center-x"))> cX and int(node.getAttribute("center-x"))< cX+cW and \
                int(node.getAttribute("center-y"))> cY and int(node.getAttribute("center-y"))< cY+cH :
                node.setAttribute('visible','true')
            else:
                node.setAttribute('visible','hidden')

            # Update also full capture
            fullNode = self.currentStateFull.find("//*[@id='%s']"%node.getAttribute('id'))
            fullNode.setAttribute("container-area","%s,%s,%s,%s"%(cX, cY, cW, cH))
            fullNode.setAttribute('visible',node.getAttribute('visible'))

        #debug.brf("Container trim took %s seconds"%(time.time()-t1))
        return view

    def addNativeDigits(self):
        """ Add native digits to labels and textinputs"""
        nativeDigits = None
        result = self.currentStateFull.findall('//*[@native-digits="false" and string-length(@text)!=0]')

        if len(result):
            try:
                nativeDigits = self.getNativeDigitsList().decode("utf-8")
            except Exception, e:
                debug.err("Error while decoding native digit list: %s"%str(e))
            else:
                arabicDigits = "".join([str(d).decode("utf-8") for d in range(10)])

                native_regexp = u"(%s)" %  u"|".join(nativeDigits)
                arabic_regexp = u"(%s)" %  u"|".join(arabicDigits)

                def _sub_arabic_to_native(match_object):
                    return nativeDigits[arabicDigits.find(match_object.group(0))]

                def _sub_native_to_arabic(match_object):
                    return arabicDigits[nativeDigits.find(match_object.group(0))]

                for node in result:
                    text = node.getAttribute("text")#.decode("utf-8")
                    if u'\u206f' not in text:
                        #nativeText = text.translate(maketrans(arabicDigits,nativeDigits))
                        nativeText = re.sub(arabic_regexp, _sub_arabic_to_native, text)
                        if nativeText != text:
                            node.setAttribute("original-text",text)
                            node.setAttribute("text",nativeText)
                    else:
                        newText = []
                        translate = False
                        for c in text:
                            if c == u'\u206f':
                                translate = False
                                continue
                            elif c == u'\u206e':
                                translate = True
                                continue
                            if translate:
                                newText.append(nativeText = re.sub(arabic_regexp, _sub_arabic_to_native, c))
                            else:
                                newText.append(c)

        result = self.currentStateFull.find('//evo-dynamic-keyboard')
        if result and not self.getPreventNativeDigitsInField():
            if not nativeDigits:
                try:
                    nativeDigits = self.getNativeDigitsList().decode("utf-8")
                except Exception, e:
                    debug.err("Error while decoding native digit list: %s"%str(e))
                else:
                    arabicDigits = [str(d) for d in range(10)]

            for node in result.findall('//key'):
                text = node.getAttribute("text")
                nativeText = text.translate(maketrans(arabicDigits,nativeDigits))
                if nativeText != text:
                    node.setAttribute("original-text",text)
                    node.setAttribute("text",nativeText)


    def __setScreenProperties(self):
        """Sets screen size and orientation after new state has been received"""

        node = self.currentState.find('//container[@name="primary-root-container"]')
        if node:
            x,y,w,h = [int(p) for p in node.getAttribute('coords').split(",")]
        else:
            return

        if w>h:
            self.screenOrientation=self.LANDSCAPE
        else:
            self.screenOrientation=self.PORTRAIT

        # width and height in dump are according to layout
        self.__SCREEN_WIDTH = w
        self.__SCREEN_HEIGHT = h

    def isItemInside(self, itemToCheck, acceptedArea):
        """ Checks if given item is fully within the bounds of accepted area.

            Parameters:
            itemToCheck(tuple)      :   X, Y, Width, Height
            acceptedArea(tuple)     :   X, Y, Width, Height

            Returns bool True if the given item is inside the accepted area.
            Otherwise False.
        """
        assert isinstance(itemToCheck, tuple), "Parameter itemToCheck must be of type tuple, got %s instead!" % type(itemToCheck)
        assert len(itemToCheck) >= 4, "Parameter itemToCheck must have at least four elements, got %s instead!" % len(itemToCheck)
        assert isinstance(acceptedArea, tuple), "Parameter acceptedArea must be of type tuple, got %s instead!" % type(acceptedArea)
        assert len(acceptedArea) >= 4, "Parameter acceptedArea must have at least four elements, got %s instead!" % len(acceptedArea)

        if itemToCheck[0] >= acceptedArea[0] and \
            itemToCheck[1] >= acceptedArea[1] and \
            itemToCheck[0]+itemToCheck[2] <= acceptedArea[0]+acceptedArea[2] and \
            itemToCheck[1]+itemToCheck[3] <= acceptedArea[1]+acceptedArea[3]:
            return True

        return False

    def __getXpathLiteral(self, string):
        """ If string contains both single and double quotes it must be splitted.

        """

        if not '"' in string:
            return '"' + string + '"'
        if not "'" in string:
            return "'" + string + "'"



        #if the value contains both single and double quotes, construct an
        #expression that concatenates all non-double-quote substrings with
        #the quotes, e.g.:
        #concat("foo", '"', "bar")

        sb = "concat("
        substrings = string.split('"')
        for i in range(len(substrings)):
            needComma = (i>0);
            if substrings[i] != "":
                if i > 0:
                    sb += ", "

                sb += "\""
                sb += substrings[i]
                sb += '"'
                needComma = True
            if i < (len(substrings) - 1):
                if needComma:
                    sb += ", "
                sb += "'\"'"

        sb += ")"
        return sb

    def getItemNodes(self, itemName=None, contentType=None, area=None, relatedItem=None, relatedAreaEnd=None):
        """ Return all label, textinput or image-widget nodes from that matches defined attributes.
            If area=None, return all texts found from visible dump

            Parameters:
            itemName (str)          :   item to be searched (bitmap, text)
            contentType (str|list)  :   content type to be searched.
            area (4-tuple of ints)  :   area points left, top, width, height
            relatedItem (str)       :   item name which needs to be in the same cell-renderer as the searched item
        """
        fullDumpUsed = False
        assert contentType in ['image-widget', 'label', 'textinput', None] or isinstance(contentType, list), "content type not valid"
        assert (isinstance(area, tuple) and len(area) == 4) or area == None, "given area is not valid"

        if contentType == None:                     # if content type is not given, return all content types
                contentType = ['label','textinput','image-widget']
        elif isinstance(contentType, basestring):   # transform contentType to a list
            contentType = [contentType]

        # attribute definitions for searched item xpath query expression.
        imageAttribute = []
        textAttribute = []

        if itemName:

            # get logical names translated, getImage/getText returns the string untouched if no translation found
            item = self._getImage(itemName)
            item = self._getText(item)

            item = self.__getXpathLiteral(item)

            if 'image-widget' in contentType: # only if image-widget contentType is defined, include image attributes
                imageAttribute.append('contains(@image, %s)' % item)
            if 'label' in contentType or 'textinput' in contentType: # only if label or textinput contentType is defined, include text attributes
                # use special search when using TAB
                textAttribute.append('@text=%s' % item)

        # create expression for related item, which needs to be in the same cell-renderer with searched item
        if relatedItem != None:
            relatedPathExpressions = []

            # Split relatedItem if it contains several items forming a path to desired item
            if relatedItem.find('//')>-1:
                relatedPathItems = relatedItem.split('//')
                relatedItem = relatedPathItems.pop(-1)

                # Create xpath expression for searching nodes only after each item in relatedItem-path
                for pathItem in relatedPathItems:
                    related = self._getImage(pathItem)
                    related = self._getText(related)

                    relatedPathExpression = 'self::image-widget[contains(@image,"%s")]' % related
                    relatedPathExpression += ' or self::label[@text="%s"] or self::textinput[@text="%s"]' % (related, related)
                    relatedPathExpression = '//*[(@visible="true" or @visible="hidden") and (%s)]/ancestor::cell-renderer[1]/following-sibling::cell-renderer' % relatedPathExpression

                    relatedPathExpressions.append(relatedPathExpression)

                    # exclude related items from search results (e.g 'Flight mode', relatedTo='Flight mode' is not a result..)
                    imageAttribute.append('not(contains(@image,"%s"))' % related)
                    textAttribute.append('@text!="%s"' % related)

            relatedPathExpression = "".join(relatedPathExpressions)
            if relatedAreaEnd != None:
                endExpression = 'self::image-widget[contains(@image,"%s")]' % relatedAreaEnd
                endExpression += ' or self::label[@text="%s"] or self::textinput[@text="%s"]' % (relatedAreaEnd, relatedAreaEnd)
                endExpression = '(%s//*[(@visible="true" or @visible="hidden") and (%s)])[1]/ancestor::cell-renderer[1]/preceding-sibling::cell-renderer' % (relatedPathExpression,endExpression)

                relatedPathExpression = relatedPathExpression + "[count(.| %s)=count(%s)]" % (endExpression,endExpression)

            related = self._getImage(relatedItem)
            related = self._getText(related)

            # related text can be a text with .png ending, related expression will have to search all types
            relatedItemExpression = 'self::image-widget[contains(@image,"%s")]' % related
            relatedItemExpression += ' or self::label[@text="%s"] or self::textinput[@text="%s"]' % (related, related)
            relatedItemExpression = '//*[(@visible="true" or @visible="hidden") and (%s)]/ancestor::cell-renderer[1]' % relatedItemExpression

            relatedItemExpression = relatedPathExpression + relatedItemExpression
            # exclude related items from search results (e.g 'Flight mode', relatedTo='Flight mode' is not a result..)
            imageAttribute.append('not(contains(@image,"%s"))' % related)
            textAttribute.append('@text!="%s"' % related)

            dump = self.currentStateFull # full dump needs to be used when related items are used
            fullDumpUsed = True
        else:
            relatedItemExpression = ''
            dump = self.currentState

        # if attributes are defined, form expression of those
        if imageAttribute:
            imageAttribute = '[' + ' and '.join(imageAttribute) + ']'
        else:
            imageAttribute = ''

        if textAttribute:
            textAttribute = '[' + ' and '.join(textAttribute) + ']'
        else:
            textAttribute = ''

        # form a xpath expression of needed content types
        expr = []
        if 'image-widget' in contentType:
            expr.append('self::image-widget%s' % imageAttribute)
        if 'label' in contentType:
            expr.append('self::label%s' % textAttribute)
        if 'textinput' in contentType:
            expr.append('self::textinput%s' % textAttribute)
        if 'node' in contentType:
            expr.append('self::node%s' % textAttribute)

        expr = ' or '.join(expr)

        # create area search expression
        areaExpression = ' and ((@center-x<="%s" and @center-x>="0") or (@left<"0" and @right >"%s"))' % (self.getScreenWidth(),self.getScreenWidth()) # make sure that items are vertically on screen area
        # if area is given, add it to expression
        # area is not added if it's full screen

        if area and area != (0, 0, self.getScreenWidth(), self.getScreenHeight()):
            areaExpression += ' and @center-x>="%s" and @center-y>="%s" and @center-x<="%s" and @center-y<="%s"' % (area[0], area[1], area[0] + area[2], area[1] + area[3])

        # finally, combine related item, area and item query expressions to one xpath query
        expr = '%s//*[((@visible="true" or @visible="hidden")%s) and (%s)]' % (relatedItemExpression, areaExpression, expr)

        if fullDumpUsed:
            return self.__getVisibleDumpNodes(dump.findall(expr))
        else:
            return dump.findall(expr)

    def __getVisibleDumpNodes(self, nodeList):
        """ Returns nodes in nodeList which are also found from visible items. """
        visibleNodesList = []
        for visibleNode in self.currentState.findall('/*'):
            if visibleNode in nodeList:
                visibleNodesList.append(visibleNode)

        return visibleNodesList

    def searchItem(self, itemName, touchType, contentType, index=1, area=None,refresh=True, containerObject=None, relatedAreaEnd=None):
        """Searches item from hw keys,text and image.

            Parameters:
            index(int)          :   Sequence number of the item to look for. When index is None return first node
                                    found below top of the screen.
            area(str|tuple)     :   Image name or X, Y, Width, Height
            refresh(bool)       :   Whether dump is made or not
            containerObject     :   Object which needs to be in the same container
        """
        #FIX Me add HW checking from XML

        # NOTE: do refresh here before starting the search
        assert self.getCurrentState(refresh=refresh), 'No xml available!'

        if self.vkbTransitionInProgress:
            # VKB is currently in transition. Refresh again.
            assert self.getCurrentState(refresh=refresh), 'No xml available!'

        if (contentType==None or contentType=='text'):
            textNodes = self.getItemNodes(itemName, ['label', 'textinput'], area, containerObject, relatedAreaEnd)

            if textNodes:
                if index is not None:
                    # text nodes are returned with exact match, index number can be used directly unlike in images case
                    if len(textNodes) >= index:
                        if touchType:
                            if textNodes[index-1].getAttribute('handled-touch-events') == "":
                                self.phone.fail('Text %s is not touchable' %itemName)
                        return textNodes[index-1]
                else:
                    return [node for node in textNodes if node.getAttribute('handled-touch-events') != ""]

        if contentType==None or contentType=='image':
            image = self._getImage(itemName)    # find png name for image to check against found image nodes
            imageNodes = self.getItemNodes(itemName, 'image-widget', area, containerObject, relatedAreaEnd)
            if imageNodes:
                if index is not None:
                    # loop through the images since image name is searched with 'contains' so returned list can contain other, unwanted images (e.g. foobar.png bar.png etc..)
                    for node in imageNodes:
                        # check current image name and if it matches (ignore index counting on images that are not matching)
                        imagefound = os.path.split(node.getAttribute('image'))[-1]
                        if image == imagefound: # if image name was correct one
                            index -= 1          # count down the index
                            if index == 0:      # when index is correct, return the node
                                return node
                else:
                    return [imageNode for imageNode in imageNodes if os.path.split(imageNode.getAttribute('image'))[-1] == image]

        # if no items found, check if searched item was using wildcards
        node = self.wildcardSearch(itemName, area, containerObject, index, relatedAreaEnd=relatedAreaEnd)
        if node:
            return node

        return None

    def wildcardSearch(self, expression, area, relatedItem, index=1, relatedAreaEnd=None):
        """ If the given expression contains wildcards, all the text and images from
            the screen area fetched and searched against the expression whether it matches.

            Parameters:
            expression (str)    :     Searched expression e.g. 'Mess?ges' or *ssag* etc.
            area (4-tuple)      :     Area coordinates where item needs to be located
            relatedItem (str)   :     Item name which is related to searched string

        """

        if "*" in expression or "?" in expression or ("[" in expression and "]" in expression):
            nodesFound =[]

            textNodes = self.getItemNodes(None, ['label', 'textinput'], area, relatedItem, relatedAreaEnd=relatedAreaEnd)
            for node in textNodes:
                if fnmatch.fnmatch(node.getAttribute('text').replace("\n"," "), expression):
                    nodesFound.append(node)

            imageNodes = self.getItemNodes(None, 'image-widget', area, relatedItem, relatedAreaEnd=relatedAreaEnd)
            for node in imageNodes:
                if fnmatch.fnmatch(os.path.split(node.getAttribute('image'))[-1], expression):
                    nodesFound.append(node)

            if nodesFound:
                if index is not None:
                    return nodesFound[index-1]
                else:
                    return nodesFound

        return None

    def isItemVisible(self, itemName, touchType=True, contentType=None, index=1, area=None, refresh=True, containerObject=None, relatedAreaEnd=None):
        """Checks if item is visible. Returns tuple containing status ,coordinates and item node.

            Parameters:
            index(int)                  :   Sequence number of the item to look for
            area(str|tuple)             :   Image name or X, Y, Width, Height
            containerObject(string)     :   Object which needs to be in the same container
        """

        item=0
        result = None

        #if index==None:
        #    area = (0,0,self.getScreenWidth(),self.getScreenHeight())

        item=self.searchItem(itemName, touchType, contentType, index=index, area=area, refresh=refresh, containerObject=containerObject, relatedAreaEnd=relatedAreaEnd)

        if item:
            if index is not None:
                x,y,w,h = [int(p) for p in item.getAttribute('coords').split(",")]

                x_center = x+(w/2)
                y_center = y+(h/2)

                topLeft = (x,y)
                topRight = (x+w,y)
                bottomLeft = (x,y+h)
                bottomRight = (x+w,y+h)
                top = int(item.getAttribute('top'))
                bottom = int(item.getAttribute('bottom'))
                left = int(item.getAttribute('left'))
                right = int(item.getAttribute('right'))

                if (item.getAttribute('visible') != 'hidden') and (self.__isPointOnScreen(topLeft) or self.__isPointOnScreen(topRight) or self.__isPointOnScreen(bottomLeft) or self.__isPointOnScreen(bottomRight) or (top < 0 and bottom > self.getScreenHeight()) or (left < 0 and right > self.getScreenWidth()) ):
                    result = (self.VISIBLE,(x_center,y_center), item)
                else:
                    result = (self.HIDDEN,(x_center,y_center), item)
            else:
                resultList = []
                for i in item:
                    x,y,w,h = [int(p) for p in i.getAttribute('coords').split(",")]

                    x_center = x+(w/2)
                    y_center = y+(h/2)

                    topLeft = (x,y)
                    topRight = (x+w,y)
                    bottomLeft = (x,y+h)
                    bottomRight = (x+w,y+h)

                    top = int(i.getAttribute('top'))
                    bottom = int(i.getAttribute('bottom'))
                    left = int(i.getAttribute('left'))
                    right = int(i.getAttribute('right'))

                    if (i.getAttribute('visible') != 'hidden') and (self.__isPointOnScreen(topLeft) or self.__isPointOnScreen(topRight) or self.__isPointOnScreen(bottomLeft) or self.__isPointOnScreen(bottomRight) or (top < 0 and bottom > self.getScreenHeight()) or (left < 0 and right > self.getScreenWidth()) ):
                        return (self.VISIBLE,(x_center,y_center), i)
                    else:
                        resultList.append((self.HIDDEN,(x_center,y_center), i))
                result = resultList[0]
        else:
            result = (self.NOT_FOUND,(0,0), item)

        return result

    def __isPointOnScreen(self, point):
        """ """

        pointX, pointY = point

        if ( pointX>=0 and pointX<=self.getScreenWidth() ) and ( pointY>=0 and pointY<=self.getScreenHeight() ):
            return True
        else:
            return False

    def __isPointOnArea(self, point, area):
        """Checks if point is inside the area.

            Parameters:
            point(int, int)             :   Coordinates of the point (x,y)
            area(int, int, int, int)    :   Coordinates, width and height of the area (x,y,w,h)

            Return: Boolean
        """

        pointX, pointY = point
        areaX,areaY,areaWidth,areaHeight = area

        if (pointX >= areaX and pointX <= areaX+areaWidth) and (pointY >= areaY and pointY <= areaY+areaHeight):
            return True
        else:
            return False


    def isItemInStatusBar(self, itemName):
        """Checks if item is under status bar node.

           Return: Boolean
        """
        # try seeking image
        image = None
        if '/' in itemName: # if this is possibly a logical image name, try get the png name
            image = self._getImage(itemName)
        elif '.png' in itemName:
            image = itemName

        if image:
            nodes = self.currentState.findall('//image-widget[@visible="true" and contains(@image,"%s") and @is-in-statusbar="true"]' % image)
            if len(nodes) > 0:
                return True

        # try seeking text
        text = self._getText(itemName)
        nodes = self.currentState.findall('//label[@visible="true" and @text="%s" and @is-in-statusbar="true"]' % text)
        if len(nodes) > 0:
            return True

        return False

    def isItemScrollable(self, itemName, containerObject=None, relatedAreaEnd=None):
        """Checks if item is scrollable

           Return: Boolean
        """
        # get all nodes matching the item name
        nodes = self.getItemNodes(itemName, area=None, relatedItem=containerObject, relatedAreaEnd=relatedAreaEnd)
        for node in nodes:
            if node.getAttribute('is-scrollable') == "true":
                return True

        # try if it was wildcard
        node = self.wildcardSearch(itemName, area=None, relatedItem=containerObject, relatedAreaEnd=relatedAreaEnd)
        if node:
            if node.getAttribute('is-scrollable') == "true":
                return True

        return False

    def isItemSelectable(self, itemName, touchType=True, contentType=None, index=1, containerObject=None, relatedAreaEnd=None):
        """Checks if item is selectable. Returns tuple containing status ,coordinates and item node.

            Parameters:
            index(int)                  :   Sequence number of the item to select
            containerObject(string)     :   Object which needs to be in the same container
        """
        item=0
        result = None
        item=self.searchItem(itemName, touchType, contentType, index=index, containerObject=containerObject, relatedAreaEnd=relatedAreaEnd)

        if item:
            assert item.getAttribute('center-x') and \
                   item.getAttribute('center-y') and \
                   item.getAttribute('width') and \
                   item.getAttribute('heigth'), \
                   'Attributes missing from widget dump xml!'

            x_center = int(item.getAttribute('center-x'))
            y_center = int(item.getAttribute('center-y'))
            w = int(item.getAttribute('width'))
            h = int(item.getAttribute('heigth'))

            # use bottom y value when image-widget has swipe* in handled-touch-events
            if item.getName() == 'image-widget' and 'swipe' in item.getAttribute('handled-touch-events') and \
               item.getAttribute('bottom'):
                y_center = int(item.getAttribute('bottom'))-1

            if item.getAttribute('visible')=='hidden':
                result = (self.HIDDEN,(x_center,y_center), item)

            # if item is in statusbar
            elif self.isItemInStatusBar(itemName):
                # if statusbar is outside screen in horizontal level, it's hidden and can be revealed
                if ( x_center < 0 or x_center > self.getScreenWidth() ) and (y_center > 0 or y_center < self.statusbarHeight ):
                    result = (self.HIDDEN,(x_center,y_center), item)
                # if item is for some reason outside the statusbar area, it is not visible and cannot be revealed
                elif ( x_center > 0 or x_center < self.getScreenWidth() ) and (y_center < 0 or y_center > self.statusbarHeight ):
                    result = (self.NOT_FOUND,(0,0), item)
                else:
                    result = (self.VISIBLE,(x_center,y_center), item)
            else:
                # check if statusbar is on the screen
                if self.statusbarHeight > 0:
                    # statusbar will get the screen touches in height + 10 pixel area
                    untouchableAreaHeight = self.statusbarHeight + 10
                else:
                    untouchableAreaHeight = 0  # if no statusbar, then whole area is touchable

                if x_center < 0 or x_center > self.getScreenWidth() or y_center < untouchableAreaHeight or y_center > self.getScreenHeight()-1:
                    result = (self.HIDDEN,(x_center,y_center), item)
                else:
                    if not item.getAttribute('is-in-tab-area')=='true':
                        result = self.__checkCenterVisibility(item, x_center, y_center)
                    else:
                        result = (self.VISIBLE,(x_center,y_center))
        else:
            result = (self.NOT_FOUND,(0,0), item)

        return result

    def __checkCenterVisibility(self, itemNode, itemXc, itemYc):
        """ Check if center point of item is covered by item in tab-area

            Parameters

            itemNode            item node (NodeUtils=
            itemXc              center x coordinate of item
            itemYc              center y coordinate of item
        """
        for sibling in itemNode.findall('following-sibling::*[@is-in-tab-area="true"]'):
            name = sibling.getAttribute('image')
            siblingX, siblingY, siblingW, siblingH = [int(c) for c in sibling.getAttribute('coords').split(",")]
            if itemXc>=siblingX and itemXc <=(siblingX + siblingW) and itemYc>=siblingY and itemYc <= (siblingY + siblingH):
                return (self.HIDDEN,(itemXc,itemYc), itemNode)

        return (self.VISIBLE,(itemXc,itemYc), itemNode)


    def waitForItem(self, itemName, timeout, index=1,containerObject=None, relatedAreaEnd=None):
        """ Waits for item to become accessible

        Parameters:
            itemName(string)    :   Item to be waited for
            timeout(int)        :   wait timeout
            index(int)          :   Sequence number of the item to look for

        """
        t = time.time()

        while t+timeout/1000.0>time.time():
            #self.getCurrentState(refresh=True)
            isScrollable = self.isItemScrollable(itemName,containerObject=containerObject, relatedAreaEnd=relatedAreaEnd)
            itemVisibility = self.isItemVisible(itemName, index=index, containerObject=containerObject, relatedAreaEnd=relatedAreaEnd)[0]
            if (isScrollable and itemVisibility != self.NOT_FOUND) or (not isScrollable and itemVisibility == self.VISIBLE):
                return True
            self.phone.delay(1000, False)

        return False

    def getCurrentState(self, refresh = False):
        """ Returns current UI dump

        Parameters:
            refresh(bool)   :   If set to True new UI dump is requested from Granite server
        """
        if self.currentState == None or (refresh and self.__getUIChanged()):
            self.phone.sx('dump')

        return self.currentState

    def getCurrentApplication(self):
        """ Returns name of the topmost application in display

        """
        currentState = self.getCurrentState(refresh=True)

        return self.currentApplication

    def __getStatusbarHeight(self):
        """ Returns height of statusbar

        """
        if self.currentState:
            statusbarNode = self.currentState.find('//statusbar')
            if statusbarNode:
                self.statusbarHeight = int(statusbarNode.getAttribute('coords').split(",")[3])
            else:
                self.statusbarHeight = 0

    def __getBreathingLineHeight(self):
        """ Returns height of breathing line

        """
        if self.currentState:
            breathingLineNode = self.currentState.find('//image-widget[@visible="true" and contains(@image,"%s")]'% self._getImage('options/indicator'))

            if breathingLineNode:
                self.breathingLineHeight = int(breathingLineNode.getAttribute('coords').split(",")[3])
            else:
                self.breathingLineHeight = 0

    def revealItem(self, item, timeout=None, index=1, containerObject=None, relatedAreaEnd=None):
        """ This method returns coordinates of item. If item is hidden it is scrolled to screen before returning coordinates.
            Test case fails if item does not become visible during timeout period.

        Parameters:
            item(string)            :   Name of the item which needs to be visible
            timeout(int)            :   Time to wait item which is not found from screen
            index(int)              :   Sequence number of the item to look for
            containerObject(str)    :   object which needs to be in the same container
        """

        item = scripting.escape(scripting.unescape(item)) # unescape is needed if user gives already escaped characters

        result = self.isItemSelectable(item, index=index, containerObject=containerObject, relatedAreaEnd=relatedAreaEnd)

        if result[0]==self.VISIBLE:
            return result[1]
        else:
            # If result is Hidden then scroll display to get xml which has result which is visible
            if result[0]==self.HIDDEN and self.isItemScrollable(item,containerObject=containerObject, relatedAreaEnd=relatedAreaEnd):
                #Calling scrolling of screen and it returns new result when item is visible
                result=self.__scroll(result, item, index=index, containerObject=containerObject, relatedAreaEnd=relatedAreaEnd)
                #self.tc.delay(500,False)
                #Verifying that item is visible before pressing coordinates
                if result[0]==self.VISIBLE:
                    return result[1]

            # Item not found from the dump yet, try again
            else:
                if timeout==None:
                    timeout=core.FW_conf['settings'].System.ExpectTimeout

                if self.waitForItem(item, timeout, index=index,containerObject=containerObject, relatedAreaEnd=relatedAreaEnd):
                    result = self.isItemSelectable(item, index=index, containerObject=containerObject, relatedAreaEnd=relatedAreaEnd)
                    if result[0]==self.VISIBLE:
                        return result[1]
                    else:
                        # If result is Hidden then scroll display to get xml which has result which is visible
                        if result[0]==self.HIDDEN:
                            #Calling scrolling of screen and it returns new result when item is visible
                            result=self.__scroll(result, item, index=index, containerObject=containerObject, relatedAreaEnd=relatedAreaEnd)
                            #self.tc.delay(500,False)
                            #Verifying that item is visible before pressing coordinates
                            if result[0]==self.VISIBLE:
                                return result[1]

                        else:
                            return None
                else:
                    return None

    def __scroll(self, result, item, index=1, containerObject=None, relatedAreaEnd=None):
        """ Scrolls display to get item visible and returns result which has new coordinates

        Parameters:
            result(tuple)   :   contains status of item which needs to be scrolled to display
            item(string)    :   item name
            index(int)      :   Sequence number of the item to look for
        """
        defaultSideWidth=150
        counter=0
        initialDump = None

        itemCommented = self._getCommented(item) # commented/translated version for test step run

        if not self.isItemScrollable(item,containerObject=containerObject, relatedAreaEnd=relatedAreaEnd):
            if containerObject:
                self.phone.fail('Cannot scroll to item, item %s (related to %s) is not scrollable' % (self._getCommented(item),self._getCommented(containerObject)))
            else:
                self.phone.fail('Cannot scroll to item, item is not scrollable %s' %self._getCommented(item))

        maximumDuration = 240000
        startTime=time.time()
        previousScrollValue = 0
        scrollModStep = 0

        containerX, containerY, containerW, containerH = [int(c) for c in result[-1].getAttribute('container-area').split(",")]

        screenWidth = min([self.getScreenWidth(),containerX + containerW])
        screenHeight = min([self.getScreenHeight(),containerY + containerH])

        screenTop = max(0,containerY)

        while result[0]==self.phone.uiState.HIDDEN:
            initialDump = self.currentState.toxml('utf-8')

            # Check if item is outside of screen at right
            if result[1][0]>=screenWidth:
                yCoordinate = 20

                distance=result[1][0] #Distance from end of screen to coordinate

                #If y coordinates are bigger than screenwith then set them to 0
                if screenWidth-distance<0:
                    x_move=0
                else:
                    x_move=screenWidth-distance
                self.phone._touch.drawLine((screenWidth,yCoordinate),(x_move,yCoordinate))
                self.phone._run('Scrolling left "%s" from UI' % itemCommented, testStepReporting = False)
                self.phone.delay(500,False)
                result = self.phone.uiState.isItemSelectable(item, index=index, containerObject=containerObject, relatedAreaEnd=relatedAreaEnd)
                #If selected item visible return result to caller
                if result[0]==self.phone.uiState.VISIBLE:
                    return result

            # Checking if item is outside of screen at bottom of screen
            if result[1][1]>=screenHeight:
                scrollEndY=screenHeight-result[1][1] #Distance from end of screen to coordinate
                distanceToScroll = scrollEndY

                # increase scrollModStep if we haven't been able to scroll
                # NOTE: This is done due to possible brightness adjust bar in settings list
                if previousScrollValue == 0:
                    previousScrollValue = scrollEndY
                elif previousScrollValue == scrollEndY:
                    scrollModStep += 40
                else:
                    previousScrollValue = 0
                    scrollModStep = 0

                if scrollEndY<screenTop:
                    scrollEndY=screenTop

                # -60 so that we won't grab the option list from the bottom of the screen
                # scrollModStep is used when for adjusting y coordinate
                self.phone._touch.drawLine((screenWidth-defaultSideWidth,(screenHeight-60) - scrollModStep),(screenWidth-defaultSideWidth,scrollEndY))
                self.phone._run('Scrolling down "%s" from UI' % itemCommented, testStepReporting = False)
                self.phone.delay(500,False)
                result = self.phone.uiState.isItemSelectable(item, index=index, containerObject=containerObject, relatedAreaEnd=relatedAreaEnd)
                #If selected item visible return result to caller
                if result[0]==self.phone.uiState.VISIBLE:
                    return result

                # Check if we can safely scroll several times in a row
                distanceToScrollMore = screenHeight-result[1][1]
                scrolledDistance = distanceToScroll-distanceToScrollMore
                if abs(scrolledDistance) > 100:
                    sweepsRequired = int(distanceToScrollMore/scrolledDistance)
                    sweeps = min(sweepsRequired-2, 10)  # Max 10 sweeps in a row without any checks
                    if sweeps > 0:
                        for i in range(0,sweeps):
                            self.phone._touch.drawLine((screenWidth-defaultSideWidth,(screenHeight-60) - scrollModStep),(screenWidth-defaultSideWidth,scrollEndY))
                            self.phone._run('Scrolling down "%s" from UI' % itemCommented, testStepReporting = False)
                            self.phone.delay(500,False)
                        result = self.phone.uiState.isItemSelectable(item, index=index, containerObject=containerObject, relatedAreaEnd=relatedAreaEnd)
                        #If selected item visible return result to caller
                        if result[0]==self.phone.uiState.VISIBLE:
                            return result


            # Checking if item is outside of screen at up of screen
            if result[1][1]<=max(screenTop,(self.phone.uiState.statusbarHeight*2)):# Item must be scrolled lower than status bar
                #distance=abs(result[1][1])+self.phone.uiState.statusbarHeight #Distance from top of the screen to coordinate which is now negative
                distance=abs(result[1][1]-max(screenTop,self.phone.uiState.statusbarHeight)) #Distance from top of the screen to coordinate which is now negative
                distance += ((screenHeight-screenTop)/2)
                distanceToScroll = distance

                # y_start must be min. 20 pixels from screenTop to ensure that ntf-drawer is not opened
                y_start = max(screenTop,(self.phone.uiState.statusbarHeight*3), 20)

                # increase scrollModStep if we haven't been able to scroll
                # NOTE: This is done due to possible brightness adjust bar in settings list
                if previousScrollValue == 0:
                    previousScrollValue = distance
                elif previousScrollValue == distance:
                    scrollModStep += 40
                else:
                    previousScrollValue = 0
                    scrollModStep = 0

                if screenTop==0:
                    y_move = distance+(self.phone.uiState.statusbarHeight*3)
                else:
                    y_move = distance+screenTop

                if y_move>=screenHeight:
                    y_move = screenHeight-1

                # scrollModStep is used when for adjusting y coordinate
                self.phone._touch.drawLine((screenWidth-defaultSideWidth,y_start + scrollModStep),(screenWidth-defaultSideWidth,y_move))
                self.phone._run('Scrolling up "%s" from UI' % itemCommented, testStepReporting = False)
                self.phone.delay(500,False)
                result = self.phone.uiState.isItemSelectable(item, index=index, containerObject=containerObject, relatedAreaEnd=relatedAreaEnd)
                #If selected item visible return result to caller
                if result[0]==self.phone.uiState.VISIBLE:
                    return result

                # Check if we can safely scroll several times in a row
                distanceToScrollMore=abs(result[1][1]-max(screenTop,self.phone.uiState.statusbarHeight))
                distanceToScrollMore += ((screenHeight-screenTop)/2)
                scrolledDistance = distanceToScroll-distanceToScrollMore
                if abs(scrolledDistance) > 100:
                    sweepsRequired = int(distanceToScrollMore/scrolledDistance)
                    sweeps = min(sweepsRequired-2, 10)  # Max 10 sweeps in a row without any checks
                    if sweeps > 0:
                        for i in range(0,sweeps):
                            self.phone._touch.drawLine((screenWidth-defaultSideWidth,y_start + scrollModStep),(screenWidth-defaultSideWidth,y_move))
                            self.phone._run('Scrolling up "%s" from UI' % itemCommented, testStepReporting = False)
                            self.phone.delay(500,False)
                        result = self.phone.uiState.isItemSelectable(item, index=index, containerObject=containerObject, relatedAreaEnd=relatedAreaEnd)
                        #If selected item visible return result to caller
                        if result[0]==self.phone.uiState.VISIBLE:
                            return result

            # if phone UI has changed, let's not increase the counter
            if initialDump == self.currentState.toxml('utf-8'):
                counter=counter+1

            # give up when counter has maximum value or maximum time is up
            if counter == 10 or time.time() > startTime + maximumDuration/1000.0:
                self.phone.capture('Failed to scroll to item')
                #if initial dump and current dump are identical, phone UI is frozen -> fail testcase
                if initialDump == self.currentState.toxml('utf-8'):
                    self.phone.comment('KBD_KEY_KEYLOCK_TOGGLE pressed to check if phone UI is freezed or not')
                    self.phone._pressKey('KBD_KEY_KEYLOCK_TOGGLE')
                    self.phone._run('Press KBD_KEY_KEYLOCK_TOGGLE')
                    self.phone.delay(500, False)
                    self.getCurrentState(refresh = True)
                    #if initial and current dumps are identical after pressing KBD_KEY_BACK then UI is frozen
                    if initialDump == self.currentState.toxml('utf-8'):
                        errorString = 'Phone UI freeze detected, unable to scroll'
                        self.phone.fail(errorString)

                if containerObject:
                    self.phone.fail('Cannot scroll to item %s (related to %s)' % (self._getCommented(item), self._getCommented(containerObject)))
                else:
                    self.phone.fail('Cannot scroll to item %s' %self._getCommented(item))

        return result

    def _getCommented(self, items):  # TODO: move this method to more suitable place when possible (scripting base class)
        """ Returns a string (or list of strings) with comment of translation for given items
        Parameters:
            items (list | string)   :   List of strings or single string. Given strings will be translated from logical
        Returns:
            list | string           :   List or string formatted "'evo_options_indicator_anim.png' (options/indicator)"
                                        or "'Flight' (nmWg1oFvw7ZZNZv8FtxBAwz)
        """

        if isinstance(items, type(())):  # if attribute is tuple, it is coordinates. cast to string
            return str(items)

        # if attribute is int, cast to string
        if type(items) == types.IntType:
            items = str(items)

        if isinstance(items,type([])):
            isList = True
            items = items[:]  # do not modify original list of items, otherwise it cannot be used in verify multiple times
        elif items.find('//')>-1:
            items = items.split('//')
            isList = True
        else:
            isList = False
            items = [items]

        for i in range(len(items)):
            # empty string check
            if not len(items[i]):
                continue

            negate = False

            if items[i][0] == '!' and len(items[i]) > 1: # check if first char is ! and it's not the only char
                items[i] = items[i][1:]
                negate = True

            if items[i][0] == 'n': # if string could be a logical text id
                translation = self.phone.getTranslation(items[i])
                if translation != None:
                    items[i] = '%s (%s)' % (translation,items[i])

            if "/" in items[i]:    # if string could be an image
                imagefile = self._getImage(items[i])
                if items[i] != imagefile:
                    items[i] = '%s (%s)' % (imagefile, items[i])

            if negate == True:
                items[i] = '!' + items[i]

        if isList:
            return items

        return items[0]

    def _getText(self, item): # TODO: move this method to more suitable place when possible (scripting base class)
        """ Returns given string translated. If given string cannot be translated, it will be returned untouched

        Parameters:
            item (string)   :   Logical string that needs to be translated, e.g nmWg1oFvw7ZZNZv8FtxBAwz
        Returns:
            string          :   String translated to current phone language, e.g Flight
        """
        if not isinstance(item, basestring):
            return item

        translation = self.phone.getTranslation(item)
        if translation != None:
            return translation

        return item

    def _getImage(self, item): # TODO: move this method to more suitable place when possible (scripting base class)
        """ Returns given logical name as png-filename (example logical name: 'calllog/grid-menu')
        """
        # check that parameter is a string
        if not isinstance(item, basestring):
            return item
        elif not item.endswith('.png'):   # if already in png format, do not try to find

            # look up from image dictionary in phone module
            filename = self.phone.getImageFilename(item)
            if  filename != item:
                return filename

            # initialize test step so that we won't run any steps in previous test step
            self.phone._initTestStep()

            # if dictionary lookup failed, try asking with sx (fallback option & backward compatibility)
            id = item.split('/')  # split id to key / subkey
            if (len(id) > 1):
                filename = self.phone.sx('(get-meta-icon-name \'%s \'%s)' % (id[0], id[1]))
                file = os.path.split(filename)[1]
                if file != "":
                    # debug.brf('img id %s is %s' % (item, file))
                    self.phone.saveImageToDictionary(item, file)
                    return file

        return item  # if not found, return str untouched

class NGSelect(object):
    """
    classdocs
    """
    def __init__(self, phone):
        """
        Constructor
        """
        self.phone =phone

    def __call__(self, item, timeout=None, doNotReport=False, index=1, relatedTo=None, relatedAreaEnd=None, doNotSelect=False):
        """ Default select functionality

        Parameters:
            item(string|tuple)      :   item, key or coordinates to be selected
            timeout(int)            :   Wait timeout
            doNotReport(boolean)    :   Whether select is put to test report or not
            index(int)              :   Sequence number of the item to select
            relatedTo(string)       :   Specifies an object which need to be in the same container with searched object
            doNotSelect(bool)       :   If set to True item is only scrolled to screen without selecting it
        """
        if not doNotReport:
            self.phone.comment('select(%s)' % self.phone.uiState._getCommented(item))

        self.withTouch(item, timeout=timeout, index=index, containerObject=relatedTo, relatedAreaEnd=relatedAreaEnd, doNotSelect=doNotSelect)

    def long(self,item, length=1500, timeout=None, doNotReport=False, index=1, relatedTo=None, relatedAreaEnd=None):
        """ Long press to coordinates with default value
            or with given value if it is bigger than default value.

        Paramters:
            item(string|tuple)  :   item, key or coordinates to be selected
            length(int)         :   press length
            timeout(int)        :   wait timeout
            doNotReport(boolean):   Whether select is put to test report or not
            index(int)          :   Sequence number of the item to select
            relatedTo(string)   :   Specifies an object which need to be in the same container with searched object
        """
        if not doNotReport:
            self.phone.comment('select.long(%s)' % self.phone.uiState._getCommented(item))

        if length<1500:
            length=1500

        self.withTouch(item, length=length, timeout=timeout, index=index, containerObject=relatedTo, relatedAreaEnd=relatedAreaEnd)

    def withTouch(self, item, contentType=None, length=None, timeout=None, index=1, containerObject=None, relatedAreaEnd=None, doNotSelect=False):
        """ Select by using touch.

        Parameters:
            item(string|tuple)      :   Item, key or coordinates to be selected
            contentType(string)     :   Type of content to be selected. text|image
            length(int)             :   Length of the press
            timeout(int)            :   Wait timeout
            index(int)              :   Sequence number of the item to select
            containerObject(string) :   Specifies an object which need to be in the same container with searched object
            doNotSelect(bool)       :   If set to True item is only scrolled to screen without selecting it
        """
        # Press (x, y) coordinate point when item is tuple
        if isinstance(item, tuple):
            self.phone._touch.press(item,length)
            self.phone._run('Press to coordinates: %s,%s' % item)
            return

        # Press HW key
        if item.startswith('KBD_KEY_'):
            self.phone._pressKey(item, length)
            self.phone._run('Press (%s) key' % item)
            if item == 'KBD_KEY_KEYLOCK_TOGGLE':
                self.phone.delay(100, False)
            return

        touchType=False#Fix touchable not working with images ,must be set not to false

        coordinates = self.phone.uiState.revealItem(item,timeout, index=index, containerObject=containerObject, relatedAreaEnd=relatedAreaEnd)

        if coordinates:
            if not doNotSelect:
                itemCommented = self.phone.uiState._getCommented(item)  # get step commented here so teststep won't be messed up with sx queries

                if containerObject != None:
                    containerCommented = self.phone.uiState._getCommented(containerObject) # get container in commented format before touching
                    self.phone._touch.press(coordinates,length)
                    self.phone._run('select(%s) (on same area as %s)' % (itemCommented, containerCommented))
                else:
                    self.phone._touch.press(coordinates,length)
                    self.phone._run('select(%s)' % itemCommented)
        elif containerObject != None:
            self.phone.fail("Cannot select %s, no item found related to \"%s\"."%(self.phone.uiState._getCommented(item), self.phone.uiState._getCommented(containerObject)))
        else:
            self.phone.fail("Cannot select %s, item is not found from screen."%self.phone.uiState._getCommented(item))


class NGInput(object):
    """Class for inputing texts to phone."""
    def __init__(self, phone):
        """

        """
        self.phone = phone
        self.__shiftKey = ''
        self.blackBoxVkb = None

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
            if self.phone.isFullBlackBox(): # input using hardcoded settings
                if self.blackBoxVkb == None:
                    self.blackBoxVkb = BlackBoxVirtualKeyboard(self.phone)
                self.blackBoxVkb._writeBlackBox(text, mode=mode, orientation=orientation, delayBetweenPresses=delayBetweenPresses)
            else:
                self.write(text, defaultText,failsafe, timeout=timeout)
        else:
            self.phone.comment("Empty string given for input!")

    def __checkUpper(self,text,NumMode):
        """ Checking upper character or lower character

        FIXME!!! Add proper docstring
        """
        # check shift key
        shiftButtonNames = [self.phone.uiState._getImage('textinput-manager/k-shift'), self.phone.uiState._getImage('textinput-manager/k-shift-accent')]

        for shiftButtonName in shiftButtonNames:
            if self.phone.uiState.getCurrentState.find("//image-widget[ends-with(@image,'%s')]" % shiftButtonName):
                self.__shiftKey = shiftButtonName
                break

        assert self.__shiftKey, 'Unable to find shift key!'

        if text==text.upper() and not text.isdigit():
            if not NumMode:
                self.phone.comment('select upper')
                self.phone.select(self.__shiftKey)
                self.phone.select(text.upper())
                self.phone.select(self.__shiftKey)
                return True
            else:
                self.phone.select(text.upper())
                return True
        else:
            self.phone.select(text.upper())
            return True

    def write(self, text, defaultText='', failsafe=False, timeout=None, mode='Abc', orientation='portrait', delayBetweenPresses=None):
        """ Write using virtual keyboard

        Parameters:
            text(string)        :   Text to be written
            defaultText(string) :   Text already in input field
            failsafe(bool)      :   If set to true failsafe method is used(much slower)
            timeout(int)        :   Wait timeout
            mode(string)        :   Mode to be used in blackbox input
            orientation(string) :   Orientation to be used in blackbox input
            delayBetweenPresses :   Delay between each keypress (BlackBox mode)

        FIXME!!! Comment and fix failsafe functionality
        """
        assert self.phone.uiState.getCurrentState, 'Xml not found'

        self.phone.comment('input.write(%s)' % text)

        if not failsafe:
            self.phone.uiState.vkb._write(text, defaultText,timeout)
        else:
            self.phone.warn('Failsafe under construction, using normal write')
            self.phone.comment('Failsafe under construction, using normal write')
            self.phone.uiState.vkb._write(text, defaultText)
            return

            NumMode=False
            AbcMode=True
            ShiftMode=False
            self.phone.uiState.getCurrentState(True)
            for singlechar in text:
                Found=False
                if singlechar==' ':
                    self.phone.select('EN')
                else:
                    while not Found:
                        self.phone.uiState.getCurrentState(True)
                        for item in self.phone.uiState.getCurrentState().findall('//label'):
                            if item.getAttribute('text') == singlechar.upper() :
                                if self.__checkUpper(singlechar,NumMode):
                                    if NumMode:
                                        self.phone.select('abc')
                                        NumMode=False
                                        if ShiftMode:
                                            self.phone.select(self.__shiftKey)
                                            ShiftMode=False
                                    Found=True
                                    break

                        if not Found:
                            if NumMode:
                                self.phone.select(self.__shiftKey)
                                ShiftMode=True
                            else:
                                self.phone.select('123')
                                NumMode=True
                        if Found:
                            break

    def push(self, text, calledFromClear = False, label=None, order=None, textinputText=None):
        """Pushes the given string to first found text input with SX.
           If no label nor textinput text nor order has been given, text will be pushed to focused textinput field.

        Paramters:
            text(string)            :   Text to be pushed to input field
            calledFromClear(bool)   :   Set to true if called from clear functionality
            label(string)           :   Input field anchor (logical or clear text)
            order(string)           :   Numerical order of textinput field to input the text. Values:
                                        'car', 'first', 'second', 'third', 'fourth', 'fifth', 'sixth','seventh', 'eighth', 'ninth', 'tenth', 'last'
            textinputText(string)   :   Text attribute of textinput field to input the text (logical or clear text)
        """
        self.phone.comment('%s(%s)' % (calledFromClear and 'clear.sx' or 'input.push', text))

        # if label given as logical text, do translation
        if self.phone.isLogicalText(label):
            label = self.phone.getTranslation(label)
        # if textinputText has been given as logical
        elif self.phone.isLogicalText(textinputText):
            textinputText = self.phone.getTranslation(textinputText)

        text = scripting.escape(text)

        # if label is given as anchor, find all labels and their parents' childs with type textinput. if label match, use the input
        if label != None:
            sxString = \
            """
            (let ((labels (send primary-root-container get-children-by-type "label")))
                (for-each (lambda(x)
                                (when (equal? (send x get-text) "%s")
                                    (define parent (send x get-parent))
                                    (define textinputs (send parent get-children-by-type "textinput"))
                                    (when (pair? textinputs)
                                        (send (car textinputs) set-text "%s")
                                    )
                                )
                            )
                            labels
                    )
            )
            """ % (label, text)

        elif textinputText != None:
            # textinput text as anchor
            sxString = \
            """
            (let ((textinputs (send primary-root-container get-children-by-type "textinput")))
                (for-each (lambda(x)
                                (when (equal? (send x get-text) "%s")
                                    (send x set-text "%s")
                                )
                            )
                            textinputs
                    )
            )
            """ % (textinputText, text)
        elif order != None:
            # textinput field's order given
            valid = ['car', 'first', 'second', 'third', 'fourth', 'fifth', 'sixth','seventh', 'eighth', 'ninth', 'tenth', 'last']
            if not order in valid:
                self.phone.fail("Input push: Wrong argument for order. Valid ones: %s " % valid)

            sxString = \
            """
            (let ((textinputs (send primary-root-container get-children-by-type "textinput")))
                (when (pair? textinputs)
                    (send (%s textinputs) set-text "%s")
                    )
            )
            """ % (order, text)
        else:
            # if no label nor textinput text nor order has been given, text will be pushed to focused textinput field
            sxString = \
            """
            (let ((textinputs (send primary-root-container get-children-by-type "textinput")))
                (for-each (lambda(x)
                                (when (send x has-focus)
                                    (send x set-text "%s")
                                )
                            )
                            textinputs
                    )
            )
            """ % text

        self.phone.uiState.getCurrentState(refresh = True)

        # check that text input field is found
        if self.phone.uiState.getCurrentState().find('//textinput'):
            sxResp = self.phone.sx(sxString)

            if 'error' in sxResp:
                self.phone.fail('%s(%s) failed, SX error (%s)' % \
                    (calledFromClear and 'clear.sx' or 'input.push', text, sxResp))
        else:
            self.phone.fail('%s(%s) failed, text input field not found' % \
                (calledFromClear and 'clear.sx' or 'input.push', text))


class NGNavigate(object):
    """ Class to navigate in menu
    """
    def __init__(self, tc):
        """

        """
        self.phone = tc
        self.menu = None

    def __call__(self, item, doNotSelect=False,timeout=None, mode='portrait'):
        """ Default navigate functionality

        Parameters:
            item(string)        :   Name of the item where to navigate
            doNotSelect(bool)   :   If set to True item is only scrolled to screen without selecting it


            Returns True if navigating succeeded, False if not.
        """
        # use normal select for main phone navigate
        if self.phone.isFullBlackBox(): # navigate using hardcoded settings
            self.__loadMenuStructure()
            self.__hardNavigate(item, doNotSelect=doNotSelect, timeout=timeout, mode=mode, recursive=False)
        else:
            assert self.phone.menu, 'No menu xml available!'

            self.phone.comment('navigate(%s)' % self.phone.uiState._getCommented(item))

            path = []
            prevNodeName = ''

            # check whether we have logical text at hand and define node names to be used
            if self.phone.isLogicalText(item):
                mainMenuNodeName = 'id'
                settingMenuNodeName = 'title-string-id'
            else:
                mainMenuNodeName = settingMenuNodeName = 'title'

            for i in range(2):
                itemNode = self.phone.menu.find('//item[@%s="%s"]' % (mainMenuNodeName, item))
                if itemNode == None:
                    itemNode = self.phone.menu.find('//setting[@%s="%s"]' % (settingMenuNodeName, item))

                if itemNode is None:
                    # update menu xml if item is not found in the first round
                    self.phone.getMenu()
                else:
                    break

            if not itemNode==None:
                while 1:
                    nodeName = itemNode.getName()
                    attribute = nodeName == 'item' and mainMenuNodeName or settingMenuNodeName
                    if itemNode.getAttribute(attribute) and itemNode.getAttribute(attribute)!=prevNodeName:
                        prevNodeName = itemNode.getAttribute(attribute)
                        path.insert(0,prevNodeName)

                    if itemNode.parent().getName()=='mainmenu':
                        break
                    else:
                        itemNode = itemNode.parent()
            else:
                self.phone.capture('Navigating to item "%s" failed' %item)
                self.phone.fail('Cannot navigate to %s, item not found from menu'%item)
                return False

            # Display might be dimmed when selecting the first item so verify that application changes when selecting.
            appBefore = self.phone.uiState.getCurrentApplication()
            self.phone.select(path[0],timeout=timeout, doNotReport=True)
            #FIXME Change this when display update ntf messages have been fixed.
            for i in range(10):
                self.phone.delay(200, False)
                appAfter = self.phone.uiState.getCurrentApplication()
                if appBefore != appAfter:
                    break

            if appBefore==appAfter:
                self.phone.select(path[0],timeout=timeout, doNotReport=True)
                self.phone.delay(200, False)
                if appBefore == self.phone.uiState.getCurrentApplication():
                    self.phone.fail('Phone UI freeze: Cannot navigate to %s'%path[0])
                    return False
                else:
                    self.phone.warn('Navigate to %s succeed after second try' %path[0])

            if len(path)>1:
                for item in path[1:-1]:
                    self.phone.select(item,timeout=timeout, doNotReport=True)

                if doNotSelect:
                    if self.phone.uiState.revealItem(path[-1]):
                        self.phone.comment('navigate(%s), but do not select'%path[-1])
                    else:
                        self.phone.fail('Cannot navigate to %s, item not found from menu'%path[-1])
                else:
                    self.phone.select(path[-1],timeout=timeout, doNotReport=True)

        return True

    def jump(self, item):
        """ Navigate using jump method. Application is launched by using SX script

        Parameters:
            item(string)    :   Name of the item to be launched
        """
        self.phone.comment('navigate.jump(%s)' % str(item))

        # just return _launchApp's return value
        return self.phone._launchApp(item)

    def __hardNavigate(self, item, doNotSelect=False,timeout=None, mode='portrait', recursive=False):
        """ navigate using settings data (full blackbox mode) """

        if not recursive:
            self.phone.comment('Navigate to %s' % item)

        if not self.menu:
            raise Exception('Navigate: no navigation data loaded')

        if not self.menu.has_key(mode):
            raise Exception('Navigate: no mode named %s' % str(mode))

        if not self.menu[mode].has_key('main_apps'):
            raise Exception('Navigate: error with setting file, "main_apps" key not defined for mode %s' % str(mode))

        if not self.menu[mode].has_key('first') or \
            not self.menu[mode].has_key('h_span') or \
            not self.menu[mode].has_key('v_span') or \
            not self.menu[mode].has_key('columns'):
            raise Exception('Navigate: error with setting file, check that mode %s has keys "first", "h_span", "v_span", "columns"' % str(mode))

        first_coords = self.menu[mode]['first']
        applications = self.menu[mode]['main_apps']

        if not item in applications:
            raise Exception('Navigate: application %s not defined in navigation settings mode %s' % (item, mode))

        coords = {}

        for i in range(len(applications)):
            x = first_coords[0] + self.menu[mode]['h_span'] * ( i % self.menu[mode]['columns'])
            y = first_coords[1] + self.menu[mode]['v_span'] * ( int ( i / self.menu[mode]['columns']) )
            coords[applications[i]] = (x, y)

        screenHeight = self.phone.uiState.getScreenHeight()

        while coords[item][1] > screenHeight:
            debug.brf('Scroll down')
            scroll = self.menu[mode]['v_span']
            self.phone._touch.drawLine( (60, screenHeight - 20 ),
                                        (60, screenHeight - 20 - scroll ))
            self.phone._run('Scrolling down UI', testStepReporting = False)
            self.phone.delay(500,False)
            for k, v in coords.iteritems():
                coords[k] = [coords[k][0], coords[k][1] - scroll]

        debug.brf('Navigate: select%s ' % (tuple(coords[item]),) )
        self.phone.select(tuple(coords[item]), doNotReport=True)
        self.phone.delay(1000, False)

    def __loadMenuStructure(self):
        """ full blackbox needs to load the menu structure from settings """
        try:
            f = open(os.path.join(core.FW_conf['settings_dir'],'navigate.settings'), 'r')
            data = f.read()
            f.close()
            self.menu = json.loads(data)

        except Exception as e:
            debug.err('Error loading navigation data: %s' % e.message)

class NGExpect(object):
    """ Class to be used to verify status of screen objects

    """
    def __init__(self, phone):
        """

        """
        self.phone = phone
        self.called=True

    def __call__(self, params, timeout=None, called=False, findOnly='all', occurrence=None, fromArea=None, refresh=True, relatedTo=None, doNotReport=False, relatedAreaEnd=None):
        """ Tries to find text first and if not found then image and if not found then fails

        Parameters:
            params(string|list) :   List(or name of the single item) of items that are expected to be on the screen.
                                        Functionality can be reversed by leading exclamation mark(!). So this can be used
                                        to verify that something is not on screen.
            timeout(int)        :   Wait timeout
            called(bool)        :   Used in recursion
            findOnly(string)    :   Specifies content type to be inspected
            occurrence(int)     :   Number of matches expected
            fromArea(str|tuple) :   Image name or X, Y, Width, Height
            refresh(bool)       :   Whether dump is made or not
            relatedTo(string)   :   Specifies an object which need to be in the same container with searched object
            doNotReport(boolean):   Whether expect is put to test report or not
        """
        assert findOnly in ['all','text','image']
        assert isinstance(occurrence, int) or occurrence==None, "Parameter occurrence must be of type int or None, got %s instead!" % type(occurrence)
        assert fromArea==None or isinstance(fromArea, tuple) or isinstance(fromArea, basestring), \
            "Parameter fromArea must be tuple or string, got %s instead!" % type(fromArea)
        assert relatedTo==None or isinstance(relatedTo, tuple) or isinstance(relatedTo, basestring), \
            "Parameter relatedTo must be tuple or string, got %s instead!" % type(relatedTo)

        checkArea = False

        if not isinstance(params,type([])):
            params = [params]

        self.called=False
        if timeout==None:
            timeout=core.FW_conf['settings'].System.ExpectTimeout

        time_t1=time.time()
        currentItem = ""

        if not doNotReport and called == False:
            if relatedTo != None:
                self.phone.comment('expect%s("%s") (on same area as %s)' % (findOnly == 'text' and '.text' or findOnly == 'image' and '.image' or findOnly == 'all' and '', ','.join(self.phone.uiState._getCommented(params)), self.phone.uiState._getCommented(relatedTo)))
            else:
                self.phone.comment('expect%s("%s")' % (findOnly == 'text' and '.text' or findOnly == 'image' and '.image' or findOnly == 'all' and '', ', '.join(self.phone.uiState._getCommented(params))))

        while 1:
            alreadyRefreshed = False
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

                    if findOnly=='all' or findOnly=='text':
                        if refresh:
                            # set alreadyRefreshed to True so that we won't take another dump in __expectImage
                            alreadyRefreshed = True

                        result=not self.__expectText(itemName, timeout, occurrence=occurrence, area=fromArea, containerObject=relatedTo, refresh=refresh, relatedAreaEnd=relatedAreaEnd)
                    if findOnly=='image' or (findOnly=='all' and result==True):
                        result=not self.__expectImage(itemName, timeout, occurrence=occurrence, area=fromArea, containerObject=relatedTo, refresh=refresh and not alreadyRefreshed, relatedAreaEnd=relatedAreaEnd)

                    if result:
                        itemsFound+=1
                    else:
                        notFoundItemsList.append(currentItem)
                else:
                    if findOnly=='all' or findOnly=='text':
                        if refresh:
                            # set alreadyRefreshed to True so that we won't take another dump in __expectImage
                            alreadyRefreshed = True

                        result=self.__expectText(itemName,timeout, occurrence=occurrence, area=fromArea, containerObject=relatedTo, refresh=refresh, relatedAreaEnd=relatedAreaEnd)
                    if findOnly=='image' or (findOnly=='all' and result==False):
                        result=self.__expectImage(itemName,timeout, occurrence=occurrence, area=fromArea, containerObject=relatedTo, refresh=refresh and not alreadyRefreshed, relatedAreaEnd=relatedAreaEnd)

                    if result:
                        itemsFound+=1
                    else:
                        notFoundItemsList.append(currentItem)

            if itemsFound==len(params) or time.time()>time_t1+timeout/1000.0:
                result=bool(itemsFound==len(params))
                break

        if called==False:
            if result==False:
                #debug.vrb(self.phone.uiState.currentState.toprettyxml())

                commentList = []

                for item in notFoundItemsList:
                    strNot = ' not '
                    if item.startswith("!"):
                        strNot = " "
                        item = item[1:]
                    commentList.append('item "%s" is%sfound'%(item,strNot))

                commentString = ", ".join(commentList)

                if relatedTo != None:
                    self.phone.fail('expect("%s") failed, %s with relation to "%s"' % (', '.join(self.phone.uiState._getCommented(params)), commentString, self.phone.uiState._getCommented(relatedTo)))
                elif occurrence > 1 and fromArea != None:
                    self.phone.fail('expect("%s") failed, %s. occurence of %s within the area of "%s"' % (', '.join(self.phone.uiState._getCommented(params)), occurrence, commentString, fromArea))
                elif occurrence > 1:
                    self.phone.fail('expect("%s") failed, %s %s times' % (', '.join(self.phone.uiState._getCommented(params)), commentString, occurrence))
                elif fromArea != None:
                    self.phone.fail('expect("%s") failed, %s within the area of "%s"' % (', '.join(self.phone.uiState._getCommented(params)), commentString, fromArea))
                else:
                    self.phone.fail('expect("%s") failed, %s' % (', '.join(self.phone.uiState._getCommented(params)), commentString))
        return result

    def text(self, item, timeout=None, occurrence=None, fromArea=None, doNotReport=False):
        """ Method for checking texts

        Parameters:
            item(string)        :   Text to be checked
            timeout(int)        :   Wait timeout
            occurrence(int)     :   Number of matches expected
            fromArea(str|tuple) :   Image name or X, Y, Width, Height
            doNotReport(boolean):   Whether expect is put to test report or not
        """
        return self.__call__(item, timeout, findOnly='text', occurrence=occurrence, fromArea=fromArea, doNotReport=doNotReport)

    def image(self, item, timeout=None, occurrence=None, fromArea=None, doNotReport=False):
        """ Method for checking images

        Parameters:
            item(string)        :   Image to be checked
            timeout(int)        :   Wait timeout
            occurrence(int)     :   Number of matches expected
            area(str|tuple)     :   Image name | X, Y, Width, Height
            doNotReport(boolean):   Whether expect is put to test report or not
        """

        return self.__call__(item, timeout, findOnly='image', occurrence=occurrence, fromArea=fromArea, doNotReport=doNotReport)

    def __expectText(self, item, timeout=None, occurrence=1, area=None, containerObject=None, refresh=True, relatedAreaEnd=None):
        """ Tries to find text and fails if not found

        Parameters:
            item(string)        :   Text to be checked
            timeout(int)        :   Wait timeout
            occurrence(int)     :   Number of matches expected
            area(str|tuple)     :   Image name | X, Y, Width, Height
            containerObject     :   Object which needs to be in the same container with searched item
            refresh(bool)       :   Whether dump is made or not
        """

        touchType=False
        contentType='text'

        # related item: search image element and get its coordinates for the accepted area
        relatedItem = None

        if isinstance(area, basestring):
            imagePng = os.path.split(self.phone.uiState._getImage(area))[-1] # check and get image filename if given in app/imageid format
            relatedItem = self.phone.uiState.searchItem(imagePng, touchType=False, contentType='image', refresh=refresh)
            if not relatedItem:
                self.phone.fail('expect("%s") failed, related item "%s" is not found' % (item, area))
                return False
            else:
                area = [int(p) for p in relatedItem.getAttribute('coords').split(",")]

        escapedItem = scripting.escape(scripting.unescape(item)) # unescape is needed if user gives already escaped characters
        xmlStatus = self.phone.uiState.isItemVisible(escapedItem, touchType, contentType, index=occurrence, area=area, containerObject=containerObject, refresh=refresh, relatedAreaEnd=relatedAreaEnd)

        if xmlStatus[0]==self.phone.uiState.HIDDEN or xmlStatus[0]==self.phone.uiState.NOT_FOUND:
            result=False
        if xmlStatus[0]==self.phone.uiState.VISIBLE:
            result=True

        return result

    def __expectImage(self, item,timeout=None, occurrence=1, area=None, containerObject=None, refresh=True, relatedAreaEnd=None):
        """ Tries to find image and fails if image is not found

        Parameters:
            item(string)        :   Image to be checked
            timeout(int)        :   Wait timeout
            occurrence(int)     :   Number of matches expected
            area(str|tuple)     :   Image name | X, Y, Width, Height
            refresh(bool)       :   Whether dump is made or not
        """

        touchType=False
        contentType='image'

        # related item: search image element and get its coordinates for the accepted area
        relatedItem = None
        if isinstance(area, basestring):
            imagePng = os.path.split(self.phone.uiState._getImage(area))[-1] # check and get image filename if given in app/imageid format
            relatedItem = self.phone.uiState.searchItem(imagePng, touchType=False, contentType='image', refresh=refresh)
            if not relatedItem:
                self.phone.fail('expect("%s") failed, related item "%s" is not found' % (item, area))
                return False
            else:
                area = [int(p) for p in relatedItem.getAttribute('coords').split(",")]

        item = os.path.split(self.phone.uiState._getImage(item))[-1] # check and get image filename if given in app/imageid format
        xmlStatus = self.phone.uiState.isItemVisible(item, touchType, contentType, index=occurrence, area=area, containerObject=containerObject, refresh=refresh, relatedAreaEnd=relatedAreaEnd)
        if xmlStatus[0]==self.phone.uiState.HIDDEN or xmlStatus[0]==self.phone.uiState.NOT_FOUND:
            result=False
        if xmlStatus[0]==self.phone.uiState.VISIBLE:
            result=True

        return result


class NGNotExpect(object):
    """ Class used to check that some object is not on screen

    """
    def __init__(self, phone):
        """

        """
        self.phone = phone
        self.called=True

    def __call__(self, params, timeout=None, occurrence=None, fromArea=None, relatedTo=None, relatedAreaEnd=None):
        """ Use Expect-class to check that items in params are not on screen

        Parameters:
            occurrence(int)     :   Number of matches expected
            fromArea(str|tuple) :   Image name or X, Y, Width, Height
            relatedTo(string)   :   Specifies an object which need to be in the same container with searched object
        """

        if not isinstance(params,type([])):
            params = [params]

        newParams = []

        for name in params:
            if name.startswith("!"):
                newParams.append(name[1:])
            else:
                newParams.append("!"+name)

        if relatedTo != None:
            self.phone.comment('notExpect("%s") (on same area as %s)' % (','.join(self.phone.uiState._getCommented(params)), self.phone.uiState._getCommented(relatedTo)))
        else:
            self.phone.comment('notExpect("%s")' % ', '.join(self.phone.uiState._getCommented(params)))

        self.phone.expect(newParams, timeout, occurrence=occurrence, fromArea=fromArea, relatedTo=relatedTo, doNotReport=True, relatedAreaEnd=relatedAreaEnd)

    def text(self, item,timeout=None):
        """ Check that item is not on screen.

        See documentation of Expect.text
        """

        if not isinstance(params,type([])):
            params = [params]

        newParams = []

        for name in params:
            if name.startswith("!"):
                newParams.append(name[1:])
            else:
                newParams.append("!"+name)

        self.phone.comment('notExpect.text("%s")' % ', '.join(self.phone.uiState._getCommented(item)))

        self.phone.expect.text(newParams, timeout, doNotReport=True)

    def image(self, item,timeout=None):
        """ Check that item is not on screen.

        See documentation of Expect.image
        """

        if not isinstance(params,type([])):
            params = [params]

        newParams = []

        for name in params:
            if name.startswith("!"):
                newParams.append(name[1:])
            else:
                newParams.append("!"+name)

        self.phone.comment('notExpect.image("%s")' % ', '.join(self.phone.uiState._getCommented(item)))

        self.phone.expect.image(newParams, timeout, doNotReport=True)


class NGTryExpect(object):
    """ Check which one of the lists match the screen contents

    """
    def __init__(self,phone):
        self.phone = phone

    def __call__(self, params,timeout=None, occurrence=None, fromArea=None, refresh=True, relatedTo=None, doNotReport=False, relatedAreaEnd=None):
        """ Default TryExpect functionality

        Parameters:
            params(list of lists)   :   List of lists containing possible screen contents
            timeout(int)            :   Wait timeout
            occurrence(int)         :   Number of matches expected
            fromArea(str|tuple)     :   Image name or X, Y, Width, Height
            relatedTo(string)       :   Specifies an object which need to be in the same container with searched object
            doNotReport(boolean)    :   Whether tryExpect is put to test report or not

        Return value is list containing indexes of list which matched the screen.
        """
        if not doNotReport:
            self.phone.comment('tryExpect("%s")' % (isinstance(params,basestring) and params or ', '.join([str(x) for x in params])))

        returnValue = []
        if isinstance(params,str):
            params = [params]

        if timeout==None:
            timeout=core.FW_conf['settings'].System.ExpectTimeout

        duration=time.time()

        while True:
            i = 0

            for l in params:
                expectResult = False

                try:
                    # NOTE: dump is taken only when i == 0
                    expectResult = self.phone.expect(l, timeout=0, called=True, occurrence=occurrence, fromArea=fromArea, refresh = i == 0 and True or False, relatedTo=relatedTo, doNotReport=True, relatedAreaEnd=relatedAreaEnd) #Use zero timeout because timeout is handled already
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


class Gesture(object):
    """ Class to implement different gestures

    """
    def __init__(self,phone):
        """
        Constructor
        """
        self.phone =phone

    def swipe(self, fromPoint, toPoint,stepSize=20):
        """ Perform swipe gesture

        Parameters:
            fromPoint(tuple)    :   Coordinates of start point
            topoint(tuple)      :   Coordinates of end point
            stepSize(int)       :   Number of pixels between calculated intermediate points
        """
        self.phone.comment('gesture.swipe((%s,%s), (%s,%s))'%( str(fromPoint[0]), str(fromPoint[1]), str(toPoint[0]), str(toPoint[1])))

        self.phone._touch.drawLine(fromPoint, toPoint, stepSize = stepSize)
        self.phone._run('gesture.swipe(%s,%s)'%( str(fromPoint), str(toPoint)))
        self.phone.delay(200, False)

        self.phone.uiState.getCurrentState(refresh = True)

    def drag(self, item, endpoint, duration=None,timeout=None, relatedTo=None, relatedAreaEnd=None):
        """  Drag item to endpoint

        Parameters:
            item(str)       :   Start drag from this items midpoint
            endpoint(tuple) :   Endpoint coordinates
        """
        assert isinstance(endpoint,tuple), "Parameter endpoint must be tuple, got %s instead!"%type(endpoint)

        if relatedTo:
            self.phone.comment('gesture.drag(%s related to %s, (%s, %s))'%(self.phone.uiState._getCommented(item),self.phone.uiState._getCommented(relatedTo), str(endpoint[0]), str(endpoint[1])))
        else:
            self.phone.comment('gesture.drag(%s, (%s, %s))'%(self.phone.uiState._getCommented(item), str(endpoint[0]), str(endpoint[1])))

        coordinates = self.phone.uiState.revealItem(item,timeout=timeout, containerObject=relatedTo, relatedAreaEnd=relatedAreaEnd)

        if coordinates is not None:
            self.phone._touch.drawLine(coordinates, endpoint,duration=duration)

            if relatedTo:
                self.phone._run('gesture.drag(%s related to %s, %s)'%(item,relatedTo,endpoint))
            else:
                self.phone._run('gesture.drag(%s, %s)'%(item,endpoint))
        else:
            if relatedTo:
                self.phone.fail("Item %s (related to %s) not visible, cannot drag"% (self.phone.uiState._getCommented(item),self.phone.uiState._getCommented(relatedTo)) )
            else:
                self.phone.fail("Item %s not visible, cannot drag"%self.phone.uiState._getCommented(item))

    def pinchIn(self, size, duration=None, angle=0):
        """ Implements pinch in-gesture

        """
        self.__pinch(direction='in',size=size, duration=duration, angle=angle)

    def pinchOut(self, size, duration=None, angle=0):
        """ Implements pinch out-gesture

        """
        self.__pinch(direction='out',size=size, duration=duration, angle=angle)

    def __pinch(self, direction,size, duration=None, angle=0):
        """ Functionality for pinch-gesture

        Parameters:
            direction(str)  :   Direction of pinch-gesture
            size(int)       :   Distance which one finger moves
            duration(int)   :   Duration of gesture in milliseconds
            angle(int)      :   Angle of line drawn by fingers in degrees.
                                Value increases clockwise from top of the screen.
                                Maximum value is 180 degrees.
        """
        assert angle<=180, "Too high value for angle"
        angle = math.radians(angle)

        if duration and not duration%20:
             "Duration might not be accurate!"
        stepSize = 10

        self.phone.comment('gesture.pinch%s(%s, %s, %s)'%(direction.title(),size,duration,angle))

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

        if not duration:
            #Calculate steps required
            numSteps = int(size / stepSize)
        else:
            numSteps = int(duration/20)-1
            stepSize = size/numSteps

        #Add start/end point
        x1 = x2 = self.phone.uiState.getScreenWidth()/2
        y1 = y2 = self.phone.uiState.getScreenHeight()/2
        steps = [((x1,y1),(x2,y2))]

        #Create intermediate steps
        for ii in range(0, numSteps):
            x1 += x1Dir * stepSize * math.sin(angle)
            y1 += y1Dir * stepSize * math.cos(angle)
            x2 += x2Dir * stepSize * math.sin(angle)
            y2 += y2Dir * stepSize * math.cos(angle)
            steps.append(((int(x1),int(y1)),(int(x2),int(y2))))

        endPoint1 = ((x1Dir * size * math.sin(angle)+self.phone.uiState.getScreenWidth()/2),(y1Dir * size * math.cos(angle)+self.phone.uiState.getScreenHeight()/2))
        endPoint2 = ((x2Dir * size * math.sin(angle)+self.phone.uiState.getScreenWidth()/2),(y2Dir * size * math.cos(angle)+self.phone.uiState.getScreenHeight()/2))

        #Add end point
        if int(x1) != int(endPoint1[0]) or int(y1) != int(endPoint1[1]):
            steps.pop(-1)
            steps.append((endPoint1,endPoint2))

        debug.out(steps)
        for i in range(len(steps)):
            debug.out(str(steps[i][0][0])+ ";"+str(steps[i][0][1]) + ";;" +str(steps[i][1][0]) + ";" +str(steps[i][1][1]))
        if direction=='in':
            steps.reverse()
        self.phone._touch.pressPointMultiTouch(steps,duration)
        self.phone._run('gesture.pinch%s(%s, %s, %s)'%(direction.title(),size,duration,angle), testStepReporting=False)


    def flick(self, item=None, direction=None, relatedTo=None,timeout=None, relatedAreaEnd=None):
        """ Perform flick gesture

        Parameters:
            item(string|tuple)  :   Name of the item or coordinates where flick gesture is started
            direction(string)   :   direction of the flick

        """

        assert direction in ['up','down','left','right'], "Direction should be one of 'up','down','left' or'right', got %s instead"%direction

        if item:
            if relatedTo:
                self.phone.comment('gesture.flick(%s related to %s, %s)'%(self.phone.uiState._getCommented(item), self.phone.uiState._getCommented(relatedTo),direction))
            else:
                self.phone.comment('gesture.flick(%s, %s)'%(self.phone.uiState._getCommented(item),direction))

            if not isinstance(item,tuple):
                #self.phone.uiState.revealItem(item,timeout=None,containerObject=relatedTo, relatedAreaEnd=relatedAreaEnd)
                coordinates = self.phone.uiState.revealItem(item,timeout=timeout, containerObject=relatedTo, relatedAreaEnd=relatedAreaEnd)

                if coordinates is not None:
                    status = self.phone.uiState.VISIBLE
                    startPoint = coordinates
                else:
                    status = self.phone.uiState.NOT_FOUND
            else:
                status = self.phone.uiState.VISIBLE
                startPoint = item

            if status==self.phone.uiState.VISIBLE:
                if direction =='up':
                    endpoint = (startPoint[0],1)
                elif direction=='down':
                    endpoint = (startPoint[0],self.phone.uiState.getScreenHeight() - 1)
                elif direction=='left':
                    endpoint = (1,startPoint[1])
                elif direction=='right':
                    endpoint = (self.phone.uiState.getScreenWidth() - 1,startPoint[1])
            else:
                self.phone.fail("Item %s not visible, cannot flick"%item)

            #debug.brf('lick startpoint: %s' % (str(startPoint)))
            #debug.brf('lick endpoint: %s' % (str(endpoint)))

            self.phone._touch.drawLine(startPoint, endpoint,duration=None,holdPenToStopScroll=False)

            if relatedTo:
                self.phone._run('gesture.flick(%s related to %s, %s)'%(item,relatedTo,direction))
            else:
                self.phone._run('gesture.flick(%s, %s)'%(item,direction))
        else:
            self.phone.comment('gesture.flick(%s)'%direction)

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

            self.phone._touch.drawLine(startPoint, endpoint,duration=None,holdPenToStopScroll=False)
            self.phone._run('gesture.flick(%s)'%direction)

    def doubleTap(self, item, timeout=None, index=1, relatedTo=None, relatedAreaEnd=None):
        """ Perform double tap-gesture

        Parameters:
            item(string|tuple)      :   item or coordinates to be selected
            timeout(int)            :   Wait timeout
            index(int)              :   Sequence number of the item to select
            relatedTo(string)       :   Specifies an object which need to be in the same container with searched object

        """
        self.phone.comment('gesture.doubleTap(%s)'% ((isinstance(item, tuple) and ', '.join(str(x) for x in item)) or item))

        # Press (x, y) coordinate point when item is tuple
        if isinstance(item, tuple):
            self.phone._touch.press(item)
            self.phone._touch.press(item)
            self.phone._run('double tap to coordinates: %s,%s' % item)

            return

        # Request UI state to wait and scroll the item to the screen
        coordinates = self.phone.uiState.revealItem(item,timeout, index=index, containerObject=relatedTo, relatedAreaEnd=relatedAreaEnd)

        if coordinates:
            itemCommented = self.phone.uiState._getCommented(item)  # get step commented here so teststep won't be messed up with sx queries
            if relatedTo != None:
                containerCommented = self.phone.uiState._getCommented(relatedTo) # get container in commented format before touching

                self.phone._touch.press(coordinates)
                self.phone._touch.press(coordinates)
                self.phone._run('double tap(%s) (on same area as %s)' % (itemCommented, containerCommented))
            else:
                self.phone._touch.press(coordinates)
                self.phone._touch.press(coordinates)
                self.phone._run('double tap(%s)' % itemCommented)

        elif relatedTo != None:
            self.phone.fail("Cannot double tap %s, no item found related to \"%s\"."%(self.phone.uiState._getCommented(item), self.phone.uiState._getCommented(relatedTo)))
        else:
            self.phone.fail("Cannot double tap %s, item is not found from screen."%self.phone.uiState._getCommented(item))

class NGExit(object):
    """ Class to implement exit functionality

    """
    def __init__(self,phone):
        """
        Constructor
        """
        self.phone = phone
        self.__killCommand = '(send (send (get-app-manager) get-topmost-application) kill)'
        self.__appsThatCantBeKilled = ['evo-home', 'java', 'welcome', 'voice-call-application', 'powerup']
        self.__invalidPhoneStateCounter = 0

    def __followerExit(self):
        """ Tries to secure the idle state in followers
        """
        self.phone.select('KBD_KEY_KEYLOCK_TOGGLE', doNotReport=True)
        self.phone.delay(5000, False)
        self.phone.select('KBD_KEY_KEYLOCK_TOGGLE', doNotReport=True)
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

        motionCountBefore = core.FW_conf['blackbox'].getCountMotionFrames()

        # swipe a bit to see if it causes motion
        yCoordinate = int(self.phone.uiState.getScreenHeight()/1.5)
        self.phone._touch.drawLine((self.phone.uiState.getScreenWidth()-2, yCoordinate), (self.phone.uiState.getScreenWidth() - 100, yCoordinate), stepSize = 30)
        self.phone._run('Move screen a bit to see is UI freezed', testStepReporting = False)

        if motionCountBefore == core.FW_conf['blackbox'].getCountMotionFrames():
            #self.phonecomment('Possible UI Freeze. KBD_KEY_KEYLOCK_TOGGLE pressed to check if phone UI is freezed or not')

            try:
                self.phone.select('KBD_KEY_KEYLOCK_TOGGLE')
                self.phone.delay(3000, False)
                motionCountBefore = core.FW_conf['blackbox'].getCountMotionFrames() # screen lock might work, get motion count here
                self.phone.select('KBD_KEY_KEYLOCK_TOGGLE')
                self.phone.delay(3000, False)
            except:
                self.phone.comment('Failed to press keylock in %s mode' % (self.phone.isFullBlackBox() and 'full blackbox' or core.FW_conf['blackbox_enabled'] and 'blackbox' or 'whitebox'))

            if core.FW_conf['blackbox'].getCountMotionFrames() == motionCountBefore:

                dumpCheckOk = core.FW_conf['current_testcase'].checkQCRamdumps(True)[0] # releases ramdump mode, which corresponds to a freeze.
                if not dumpCheckOk: # if unable to fetch dumps, wait for boot up
                    if core.FW_conf['ramdump_method'] == "SDCARD": # if dumps are fetched from SDCARD, it might take more than 5 minutes
                        timeout = 360
                    else:
                        timeout = 50

                    self.phone.comment('Nothing happened with keylock toggle. Waiting %s seconds for motion..' % str(timeout))
                    for i in range(timeout):
                        self.phone.sendWaitMessageToGraniteGUI(1, 'Waiting UI motion for %s second' % 1)
                        self.phone.delay(1000, False)
                        if core.FW_conf['blackbox'].getCountMotionFrames() != motionCountBefore: # if motion detected, release loop
                            break

                if core.FW_conf['blackbox'].getCountMotionFrames() == motionCountBefore:
                    if core.FW_conf['should_stop']:
                        return
                    try:
                        self.phone.resetPhone('UI Freeze detected with external camera')
                    finally:
                        self.phone.comment('Sleeping %s seconds after phone reset' % str(50))
                        self.phone.sendWaitMessageToGraniteGUI(1, 'Waiting phone to boot up for %s second' % 1)
                        self.phone.delay(50000)
                        self.phone.fail('UI Freeze detected with external camera')
                else:
                    self.phone.comment('Motion detected, not a freeze. Continue..')
            else:
                self.phone.comment('Not a freeze. Continue..')

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
            raise Exception('Exit: No video camera available. Check settings.')

        mcStart = core.FW_conf['blackbox'].getCountMotionFrames()
        mcAfter = None

        self.inIdle = False

        #exitmethods = ['single back','3 back presses', 'swipe', 'keylock']

        for i in range(5):

#            for method in exitmethods:
            import sys
            sys.path.append('..')
            from override.Exit import ExitOverrides
            exitOverrides = ExitOverrides(self.phone)
            exitMethods = [m for m in dir(exitOverrides) if m.startswith('EXIT')]
            debug.brf(exitMethods)

            for method in exitMethods:

                mcBefore = core.FW_conf['blackbox'].getCountMotionFrames()

                if self._isInIdle():
                    continue

                self.phone.comment('Exit: Try %s to get idle..' % method)
                getattr(exitOverrides,method)()

                #if method == 'single back': # if in some application, this could close it
                #    self.phone.select.long('KBD_KEY_BACK',doNotReport=True)

                #elif method == '3 back presses': # if in some application, this could close it
                #    self.phone.select.long('KBD_KEY_BACK',doNotReport=True)
                #    self.phone.delay(1000)
                #    self.phone.select('KBD_KEY_BACK', doNotReport=True)
                #    self.phone.delay(1000)
                #    self.phone.select('KBD_KEY_BACK', doNotReport=True)

                #elif method == 'swipe':
                #    self.__backToIdleWithSwipe() # close application with swipe

                #elif method == 'keylock':
                #    self.phone.select('KBD_KEY_KEYLOCK_TOGGLE', doNotReport=True)

                #else:
                #    self.phone.fail('Exit: %s is not handled' % method)

                self.phone.delay(2000, False)

                if self._isInIdle():
                    continue

                mcAfter = core.FW_conf['blackbox'].getCountMotionFrames()
                if mcBefore != mcAfter:
                    #self.phone.comment('Exit: %s caused motion' % method)

                    if i >= 2: # keylock?
                        self.phone.input('201426\n', mode='pin', delayBetweenPresses=1000)
                        self.phone.delay(3000)
                        if self._isInIdle():
                            continue

                elif i > 3 and mcBefore == mcAfter: # enough tries, crash note might be on the screen
                    self.phone.comment('try closing crash note')
                    self.phone.select((260, 490))
                    self.phone.delay(3000)
                    mcAfter = core.FW_conf['blackbox'].getCountMotionFrames() # if nothing happened, check ui freeze
                    if mcBefore == mcAfter:
                        self._checkUiFreeze()

            if mcAfter == None and self.inIdle: # nothing was done, check freeze if phone has freezed in idle state
                self._checkUiFreeze()
                return True

            elif self.inIdle:
                return True

        self._checkUiFreeze()
        return False

    def __navigateToIdle(self):
        """ quickly to idle with back key
        """

        debug.brf('Navigate: Execute back presses to get to idle')
        self.phone.select.long('KBD_KEY_BACK',doNotReport=True)
        self.phone.select('KBD_KEY_BACK', doNotReport=True)
        self.phone.select('KBD_KEY_BACK', doNotReport=True)
        self.phone.delay(700, False)
        return

    def __call__(self):
        """ Default exit functionality

        """

        if self.phone.isLeader():
            self.phone.comment("follower exit()")
            self.__followerExit()
        elif self.phone.isFullBlackBox():
            self.phone.comment("Full BlackBox exit")
            if not self.__fullBlackBoxExit():
                self.phone.fail('Full blackbox exit failed')
            return
        else:
            self.phone.comment("exit()")

        # run __exit three times before giving up
        for i in range(3):
            exitValue = self.__exit(i)

            if exitValue or core.FW_conf['should_stop']:
                break
            elif i == 2:
                # try to take error capture before reset
                self.phone.takeCaptureFromFailure()

                self.phone.resetPhone('Exit: evo-home could not be reached')

    def back(self):
        """Perfoms back swipe .

            Returns True when in idle, False if not.
        """
        if self.phone.isFullBlackBox():
            self.__navigateToIdle()
            return True

        currentApplication = self.phone.uiState.getCurrentApplication()

        if currentApplication != 'evo-home':
            self.phone.comment('exit.back()')
            if currentApplication == 'ntf-drawer':
                self.__backToIdleWithBackPress()
            else:
                self.__backToIdleWithSwipe()
            self.phone.delay(300, False)
            self.phone.uiState.getCurrentState(True)
        else:
            self.phone.comment('exit.back() is not done for %s' % currentApplication)

    def kill(self):
        """Perfoms application kill .

            Returns True when in idle, False if not.
        """
        # get current application
        currentApplication = self.phone.uiState.getCurrentApplication()

        if not currentApplication in self.__appsThatCantBeKilled:
            self.phone.comment('exit.kill()')
            self.phone.sx(self.__killCommand)
            self.phone.delay(300, False)
            self.phone.uiState.getCurrentState(True)
        else:
           self.phone.warn('Not allowed to kill "%s" application using SX' % currentApplication)

    def __backToIdleWithBackPress(self, long = False):
        """ Performs KBD_KEY_BACK key press to reach idle state.


            Parameters

            long            long press (boolean)
        """
        if long:
            self.phone.select.long('KBD_KEY_BACK', doNotReport = True)
        else:
            self.phone.select('KBD_KEY_BACK', doNotReport = True)

    def __backToIdleWithSwipe(self):
        """ Performs swipe from right to left to reach idle state.

        """
        # NOTE: Don't grab from the very end coordinates, causes phone reset

        # If Virtual keyboard is on screen, do not swipe over it
        if self.phone.uiState.vkb.vkbOnScreen or self.phone.uiState.vkbTransitionInProgress:
            yCoordinate = self.phone.uiState.getScreenHeight()/5

            self.phone._touch.drawLine((self.phone.uiState.getScreenWidth()-2, yCoordinate), (2, yCoordinate), stepSize = 30)
        else:
            # swipe a bit below from the center of the screen to avoid hitting e.g usb-manager app in the background
            yCoordinate = int(self.phone.uiState.getScreenHeight()/1.5)

            self.phone._touch.drawLine((self.phone.uiState.getScreenWidth()-2, yCoordinate), (2, yCoordinate), stepSize = 30)

        self.phone._run('Go back to idle with touch swipe', testStepReporting = False)
        self.phone.delay(300, False)

    def __unlockPhone(self, secondCode=False):
        """ Unlocks phone lock from UI"""
        self.phone.comment('Enter lock code for enabling phone usage')
        code1 = '25057'
        code2 = '19841'

        try:
            # wait for numbers for a while
            self.phone.delay(1000, False)

            code = secondCode and code2 or code1

            # write security code
            for c in code:
                self.phone.select(c, doNotReport = True)
                self.phone.delay(200, False)

        except TestException, err:
            self.phone.warn('Error in entering phone lock code: %s' % str(err))
            debug.out('Error in Exit: %s' % str(err))
            # skip possible failure, Exit must be as robust as possible

    def __enterPIN(self, sim2=False):
        """ Enters PIN code in PIN query. """
        currentSIM = sim2 and '2' or '1'
        self.phone.comment('Entering PIN code for SIM%s' % currentSIM)

        # Check settings for SIM/PUK code
        pincode = pukcode = None
        if sim2:
            pincode = core.FW_conf['settings'].Main.SIM2PinCode
            pukcode = core.FW_conf['settings'].Main.SIM2Puk1Code
        else:
            pincode = core.FW_conf['settings'].Main.SIM1PinCode
            pukcode = core.FW_conf['settings'].Main.SIM1Puk1Code

        if not pincode:
            self.phone.fail('SIM code for SIM%s is missing from settings!' % currentSIM)

        enterPinItems = [['Give your PIN'],['2 tries left for PIN code'],['1 try left for PIN code'],['Give new PIN'],['Verify new PIN']]
        enterPukItems = [['PIN blocked. Give PUK.']]
        failItems = [['* left for PUK code']]
        pinItems = enterPinItems + enterPukItems + failItems

        retVal = self.phone.tryExpect(pinItems, doNotReport = True)
        while len(retVal):
            if pinItems[retVal[0]] in enterPinItems:
                # Write (new) PIN code
                # TODO: Update VKB to handle password service's numpad
                self.phone.input.push(pincode)
                self.phone.delay(200, False)
                self.phone.select('password-service/done', doNotReport = True)
                self.phone.delay(1000, False)
            elif pinItems[retVal[0]] in enterPukItems:
                if pukcode:
                    # Write PUK code
                    # TODO: Update VKB to handle password service's numpad
                    self.phone.input.push(pukcode)
                    self.phone.delay(200, False)
                    self.phone.select('password-service/done', doNotReport = True)
                    self.phone.delay(1000, False)
                else:
                    self.phone.fail('PUK code for SIM%s is missing from settings!' % currentSIM)
            elif pinItems[retVal[0]] in failItems:
                # Entering PIN and PUK codes failed.
                self.phone.fail('Wrong PUK code has been entered for SIM%s.' % currentSIM)

            # Check if PIN for SIM1 is entered successfully and we have moved to PIN query of SIM2
            if not sim2:
                if self.phone.check('password-service/sim2watermark', doNotReport=True, timeout=2000):
                    break

            retVal = self.phone.tryExpect(pinItems, doNotReport = True)

    def __exit(self, loopRound):
        """Goes back to evo-home.

            Returns True when in evo-home, False if evo-home could not be reached
        """
        useSecondSecurityCode = False

        for i in range(10):
            # get current application
            currentApplication = self.phone.uiState.getCurrentApplication()

            if currentApplication == 'evo-home':
                # both, history and menu views are 'evo-home', check also dialer grid icon so we get to menu
                dialer = self.phone.uiState.currentState.find('//image-widget[contains(@image,"%s")]' % self.phone.uiState._getImage('dialer/grid-menu'))
                if dialer:
                    x,y,w,h = [int(p) for p in dialer.getAttribute('coords').split(",")]

                    # if dialer not on screen width area, dialer is not visible
                    if x + w/2 < 0 or x + w/2 > self.phone.uiState.getScreenWidth():
                        dialer = None

                if dialer:
                    # check if we are in editing mode in evo-home
                    scrollContainerForMainMenu = self.phone.uiState.currentStateFull.find('//scroll-container[@name="main-menu-scroller"]')
                    if scrollContainerForMainMenu:
                        if scrollContainerForMainMenu.find('*/fast-menu') and scrollContainerForMainMenu.find('*/container[@visible="true"]'):
                            self.phone.comment('KBD_KEY_BACK pressed in order to return from editing state in evo-home')
                            if self.phone.isLeader():
                                self.__backToIdleWithBackPress(True)
                            else:
                                self.__backToIdleWithBackPress()

                    # we are in evo-home if dialer was found --> return from the __exit method with True
                    return True
                else:
                    if self.phone.isLeader():
                        self.__followerExit()
                    else:
                        # perform swipe to get back to menu
                        self.__backToIdleWithSwipe()
            # wait for a while if messaging-daemon is application is active
            elif currentApplication=='messaging-daemon':
                self.phone.delay(1000, False)
            elif currentApplication=='voice-call-application':
                # end possible reference call
                if self.phone.referencePhone != None and \
                   core.FW_conf['settings'].TestRun.AutomaticRejectCallForReferencePhone:
                    try:
                        debug.brf('Rejecting reference phone call in exit...')
                        self.phone.referencePhone.rejectCall(doNotReport = True)
                    except Exception, ex:
                        debug.err('Unable to reject reference phone call in exit: %s' % str(ex))

                # end call with reject button
                try:
                    if self.phone.check('voice-call-application/reject-call', doNotReport = True):
                        self.phone.select('voice-call-application/reject-call', doNotReport = True)
                        self.phone.delay(1000, False)
                except TestException, err:
                    debug.out('Error in rejecting call in Exit: %s' % str(err))
                    # skip possible failure, Exit must be as robust as possible

                if self.phone.isLeader():
                    self.__followerExit()
                else:
                    try:
                        # make sure that all phone calls are ended
                        self.phone.srv.call.end()
                    except TestException, err:
                        debug.out('Error in ending calls with SX in Exit: %s' % str(err))
                        # skip possible failure, Exit must be as robust as possible

                    # first we try to exit with swipe
                    self.__backToIdleWithSwipe()
            # handle welcome application by pressing values to it
            elif currentApplication=='welcome':
                # n0000000000000000000001 == "English"
                # nbcaaMNAsek1HQ8pr0u2obo == "Sign in later" Both added to welcomeAppItems because logical text is missing from Lanai SS 1330.20 SW
                # nzvP58DaYjU6BBq68WACfig == "Continue"
                # n6Vpdj39k8kO7BzxnrXOErg == "Done"
                # njaWEWAr3pkOaUtZxG70TpQ == "OK"
                # nv3QRA238SUKYbG-FDnpGTw == "Yes"
                # nFmoGfXMvT0OJ-PjvuK12NA == "Give your PIN"
                welcomeAppItems = [['n0000000000000000000001'],['nbcaaMNAsek1HQ8pr0u2obo'],['Sign in later'],['nzvP58DaYjU6BBq68WACfig'],['n6Vpdj39k8kO7BzxnrXOErg'],['njaWEWAr3pkOaUtZxG70TpQ'],
                                   ['GMT -11 Midway Island'],['nv3QRA238SUKYbG-FDnpGTw'],['YES'],["password-service/simwatermark"],
                                   ["password-service/sim1watermark"],['password-service/sim2watermark'],["Give your security code"]]
                retVal = self.phone.tryExpect(welcomeAppItems, doNotReport = True)

                if len(retVal):
                    # check if we need to enter security code (it's the last list item)
                    if welcomeAppItems[retVal[0]] == welcomeAppItems[-1]:
                        self.__unlockPhone(useSecondSecurityCode)
                        useSecondSecurityCode = True
                    # check if PIN code is required
                    elif welcomeAppItems[retVal[0]]==welcomeAppItems[-4] or welcomeAppItems[retVal[0]]==welcomeAppItems[-3]:
                        self.__enterPIN() #SIM1
                    elif welcomeAppItems[retVal[0]]==welcomeAppItems[-2]:
                        self.__enterPIN(sim2=True) #SIM2
                    else:
                        # try to select text which is currently visible
                        try:
                            if welcomeAppItems[retVal[0]][0]=='Sign in later' or welcomeAppItems[retVal[0]][0]=='nbcaaMNAsek1HQ8pr0u2obo':
                                itemCoords = self.phone.uiState.isItemVisible(welcomeAppItems[retVal[0]][0], refresh=False)[1]
                                self.phone.select((itemCoords[0]/2,itemCoords[1]), doNotReport = True) # Currently text width in xml dump is too wide
                            else:
                                self.phone.select(welcomeAppItems[retVal[0]][0], doNotReport = True)

                            # select "Continue" if "English" was selected before
                            if welcomeAppItems[retVal[0]][0] == 'n0000000000000000000001':
                                self.phone.select('nzvP58DaYjU6BBq68WACfig', doNotReport = True)
                        except TestException, err:
                            debug.out('Error in Exit: %s' % str(err))
                            # skip possible failure, Exit must be as robust as possible
                            pass
                else:
                    retVal = self.phone.tryExpect('dialogs/spinner-large-light', doNotReport = True)
                    if not retVal:
                        # try to exit with long back key press
                        self.__backToIdleWithBackPress(True)

                    # wait for a while just be sure that application changes
                    self.phone.delay(1000, False)

                    # in the last loop round we must exit from welcome application by force
                    if currentApplication == self.phone.uiState.getCurrentApplication() and loopRound == 2 and i == 9:
                        self.__handleJavaApplication(currentApplication)
            # check if ntf-drawer application has been activated
            elif currentApplication == "ntf-drawer":
                # check that are there item on the screen
                # if not, we must kill the application
                if not self.phone.isLeader() and \
                   len(self.phone.read(doNotReport = True)) == 0:
                    self.phone.warn('%s application was killed using SX' % currentApplication)
                    self.phone.sx(self.__killCommand)
                else:
                    # Press back key to deactivate ntf-drawer
                    self.__backToIdleWithBackPress()
                self.phone.delay(1000, False)
            # check if video-player application has been activated
            elif currentApplication == "video-player":
                # Press back key to deactivate video-player
                if self.phone.isLeader():
                    self.__backToIdleWithBackPress(True)
                else:
                    self.__backToIdleWithBackPress()
                    self.phone.delay(300, False)
            # keylock must be deactivated with swipe
            elif currentApplication == 'keylock':
                # press keylock key to activate touch
                if self.phone.isLeader():
                    self.__followerExit()
                else:
                    self.phone._pressKey('KBD_KEY_KEYLOCK_TOGGLE')
                    self.phone._run('Press keylock key to activate touch')
                    if self.phone.isLeader(): # if in leader mode, follower does not always swipe after keylock toggle
                        self.phone.delay(200, testStepReporting = False)
                    # go back to idle with touch swipe
                    self.__backToIdleWithSwipe()
            # manual deactivation of phonelock
            elif currentApplication == 'phonelock':
                self.__unlockPhone(useSecondSecurityCode)
                useSecondSecurityCode = True
                continue # Jump at the beginning of the loop to keep securityCode flag-value
            # java application (for example Twitter) can have 'No' button to press
            elif currentApplication == 'java':
                javaAppItems = [['No'],['NO'],['OK']]
                retVal = self.phone.tryExpect(javaAppItems, doNotReport = True)

                if len(retVal):
                    try:
                        # select text which is currently visible
                        self.phone.select(javaAppItems[retVal[0]][0], doNotReport = True)
                    except TestException, err:
                        debug.out('Error in Exit: %s' % str(err))
                        # skip possible failure, Exit must be as robust as possible
                else:
                    self.__handleJavaApplication(currentApplication)

                # wait for a while just be sure that application changes
                self.phone.delay(1000, False)
            # usb-manager (choose "Modem" if it's visible, otherwise kill the application)
            elif currentApplication == 'usb-manager':
                usbAppItems = [['n-bNuEfehnkav7TuxaBHeiA']] # Modem
                retVal = self.phone.tryExpect(usbAppItems, doNotReport = True)

                if len(retVal):
                    # select "Modem"
                    try:
                        self.phone.select(usbAppItems[retVal[0]][0], doNotReport = True)
                    except TestException, err:
                        debug.out('Error in Exit: %s' % str(err))
                        # skip possible failure, Exit must be as robust as possible

                    self.phone.delay(1000, False)
                    currentApplication = self.phone.uiState.getCurrentApplication()

                # kill the application if selecting didn't work or was not possible
                if currentApplication == 'usb-manager':
                    if self.phone.isLeader():
                        core.FW_conf['mail_sender'].holdExecutionAndSendMail(message="""
                        MTBF leader requests usb-manager kill via SX.
                        Execution is on hold""", subject='MTBF EXECUTION ON HOLD')
                    else:
                        self.phone.warn('%s application was killed using SX' % currentApplication)
                        self.phone.sx(self.__killCommand)

                # wait for a while just be sure that application changes
                self.phone.delay(1000, False)

            # check app-stack-container state if application was not found
            elif currentApplication is None:
                # try to get the app-stack-container. Execute the call in a try-catch clause
                # due to in a situaton like this, the xml-dump may be totally messed up
                appStackNode = None
                try:
                    appStackNode = self.phone.uiState.currentStateFull.find('//app-stack-container')
                except Exception:
                    pass

                # in the last loop round we must exit from this erroneous situation by force
                if not appStackNode or not appStackNode.getChildNodes() and loopRound == 2 and i == 9:
                    # try to take error capture before reset
                    self.phone.takeCaptureFromFailure()

                    self.__invalidPhoneStateCounter += 1

                    # if this would be the third time, let's just give up (result == NO RESULT)
                    if self.__invalidPhoneStateCounter == 3:
                        raise Exception('Invalid phone state detected: No running applications found!')
                    else:
                        self.phone.resetPhone('Invalid phone state detected: No running applications found!')

                # wait for a while to give time to the phone to recover
                self.phone.delay(2000, False)
            # some other application active
            else:
                # reset invalid phone state counter when we have valid application
                self.__invalidPhoneStateCounter = 0

                if self.phone.isLeader():
                    self.__followerExit()
                else:
                    # first we try to exit with swipe
                    self.__backToIdleWithSwipe()

                # wait for a while just be sure that application changes
                self.phone.delay(500, False)

                # get current application
                prevApplication = currentApplication
                currentApplication = self.phone.uiState.getCurrentApplication()

                longPress = True
                for i in range(2):
                    if currentApplication == prevApplication:
                        # try to exit with long and then with normal back key press
                        self.__backToIdleWithBackPress(longPress)
                        if longPress:
                            longPress = False

                        # wait for a while just be sure that application changes
                        self.phone.delay(1000, False)

                        # get current application
                        currentApplication = self.phone.uiState.getCurrentApplication()
                    else:
                        break

                # if swipe or long back key press don't work, we must kill the application with SX
                # we can't kill certain applications
                if currentApplication == prevApplication and \
                   not currentApplication in self.__appsThatCantBeKilled:
                   if self.phone.isLeader():
                       core.FW_conf['mail_sender'].holdExecutionAndSendMail(message="""
                       MTBF leader requests kill via SX: Swipe or long back did not work -> sx kill cannot be done in Leader mode. \
                       Execution is on hold""", subject='MTBF EXECUTION ON HOLD')

                   else:
                       self.phone.warn('%s application was killed using SX' % currentApplication)
                       self.phone.sx(self.__killCommand)

                       # wait for a while after killing application with SX
                       self.phone.delay(1000, False)

        # we could not reach evo-home
        return False

    def __handleJavaApplication(self, applicationName):
        """Handle exiting from java application (java, welcome)
        """
        # if phone is in invalid state for 30 seconds, kill java application
        # NOTE: This is done in order to recover from invalid phone state
        javaImages = ['widgets/screen-corner-tl',
                      'widgets/screen-corner-tr',
                      'widgets/screen-corner-bl',
                      'widgets/screen-corner-br']

        startTime = time.time()
        timeout = 30
        currentApplication = applicationName

        while True:
            # try to back swipe if screen has some content
            # NOTE: We can't back swipe if usb-manager application is in the background
            # NOTE2: back swipe has no effect in welcome application
            if currentApplication != 'welcome' and \
               (len(self.phone.read.texts(doNotReport = True)) != 0 or \
               self.phone.read.images(doNotReport = True) != javaImages) and \
               not self.phone.uiState.currentStateFull.find('//application[@name="usb-manager"]'):
                # try to exit from java with back swipe
                self.__backToIdleWithSwipe()

                # wait for a while just be sure that application changes
                self.phone.delay(1000, False)

            # check that did the application change
            currentApplication = self.phone.uiState.getCurrentApplication()

            if currentApplication == applicationName:
                # try to exit with long back key press
                self.__backToIdleWithBackPress(True)

                # wait for a while just be sure that application changes
                self.phone.delay(1000, False)

            if currentApplication != applicationName:
                break

            # press possible 'Yes' button blocking application exit
            javaAppItems = [['Yes'],['YES']]
            retVal = self.phone.tryExpect(javaAppItems, doNotReport = True)

            if len(retVal):
                try:
                    # select text which is currently visible
                    self.phone.select(javaAppItems[retVal[0]][0], doNotReport = True)
                except TestException, err:
                    debug.out('Error in Exit: %s' % str(err))
                    # skip possible failure, Exit must be as robust as possible

                # wait for a while just be sure that application changes
                self.phone.delay(1000, False)

                currentApplication = self.phone.uiState.getCurrentApplication()
                if currentApplication != applicationName:
                    break

            # after 30 seconds we must kill the application
            # welcome application can't be killed safefully, we must reset the phone instead
            if (time.time()-startTime) > timeout:
                if currentApplication == 'welcome':
                    # try to take error capture before reset
                    self.phone.takeCaptureFromFailure()

                    self.__invalidPhoneStateCounter += 1

                    # if this would be the third time, let's just give up (result == NO RESULT)
                    if self.__invalidPhoneStateCounter == 3:
                        raise Exception('Invalid phone state detected: No running applications found!')
                    else:
                        self.phone.resetPhone('Invalid phone state detected: No running applications found!')
                else:
                    self.phone.warn('%s application was killed using SX' % currentApplication)
                    self.phone.sx(self.__killCommand)

                break

            # get current application
            currentApplication = self.phone.uiState.getCurrentApplication()

class NGClear(object):
    """Class for clearing texts from phone."""
    def __init__(self, phone):
        """

        """
        self.phone = phone
        self.__input = NGInput(phone)
        self.blackBoxVkb = None

    def __call__(self,label=None, order=None, textinputText=None, time=3):
        """ Calls default input method. """

        if self.phone.isFullBlackBox():
            if not self.blackBoxVkb:
                self.blackBoxVkb = BlackBoxVirtualKeyboard(self.phone)
            self.blackBoxVkb.clear(time=time)
            return

        assert not self.phone.isLeader(), 'default clear is not allowed in Leader mode. Use clear.backspace instead!'

        self.sx(label, order, textinputText)

    def backspace(self, number=0, doNotReport = False):
        """ Clear text using backspace-button in virtual keyboard

        Parameters:
            number(int or string) :   Number of times to press backspace or string 'all' to clear all
        """
        if self.phone.isFullBlackBox():
            if not self.blackBoxVkb:
                self.blackBoxVkb = BlackBoxVirtualKeyboard(self.phone)
            self.blackBoxVkb.backspace(times=number)
            return

        if not doNotReport:
            self.phone.comment('clear.backspace(%s)' % (number != 0 and str(number) or ""))

        self.phone.failUnless(self.phone.uiState.vkb.waitForVKB(),"Keyboard not found!")

        backspaceButton = self.phone.uiState.vkb.getClearButtonCoordinates()
        if backspaceButton:
            # number 0 means single backspace
            if number == 0:
                number = 1

            elif number == 'all':
                # Get the length of the text
                sxString = \
                    """
                    (begin
                        (let ((textinputs (send primary-root-container get-children-by-type "textinput")))
                            (define retval "")
                            (for-each (lambda(x)
                                            (when (send x has-focus)
                                                (set! retval (send x get-text))
                                            )
                                        )
                                        textinputs
                            )
                            retval
                        )
                    )
                    """
                inputText = self.phone.sx(sxString, doNotReport=True)

                if not inputText or len(inputText)==0:
                    number = 0
                else:
                    number = len(inputText)

                    # Move cursor to the end of the text
                    nodeList = self.phone.uiState.getItemNodes(itemName=inputText, contentType='textinput')
                    for node in nodeList:
                        if node.getAttribute('has-global-focus') == 'true':
                            coords = (int(node.getAttribute('right'))-4, int(node.getAttribute('bottom'))-10)
                            self.phone.select(coords, doNotReport = True)
                            break

            for i in range(number):
                self.phone.select(backspaceButton, doNotReport = True)
        else:
            self.phone.fail('Unable to determine which backspace button needs to be pressed!')

    def sx(self,label=None, order=None, textinputText=None):
        """Clears the given string from first found text input with SX."""
        self.__input.push("",calledFromClear=True, label=label, order=order, textinputText=textinputText)


class Post(object):
    """Class for post verifying from phone."""
    def __init__(self, phone):
        """

        """
        self.phone = phone

    def verify(self, items):
        """
            parameters:
                items(String|List|NodeUtils)

            Note! Add support for UI verification classes
        """
        if isinstance(items,str) or isinstance(items, list) or isinstance(items, tuple) or isinstance(items, NodeUtils):
            pass
        else:
            assert 0, 'Type of items-attribute should be String, Class, List or NodeUtils! Got %s instead'%type(items)


class NGBack(object):
    """Class for back stepping."""
    def __init__(self, phone):
        """Initialize test case instance for class."""
        self.phone = phone

    def __call__(self, count = 1):
        """Executes default back stepping.

        Parameters:
            count(int)  :   times to press back-key
        """
        assert type(count) == types.IntType and count >= 1, \
               'Invalid count value (%s) given!' % count

        self.phone.comment('back(%s)' % (count != 1 and str(count) or ""))

        self.phone._pressKey('KBD_KEY_BACK', repeat = count)
        self.phone._run('Press back key for back stepping')

class NGCheck(object):
    """ Class for checking item without selecting it"""
    def __init__(self, phone):
        """Initialize test case instance for class."""
        self.phone = phone

    def __call__(self, item, timeout=None, occurrence=1, relatedTo=None, doNotReport=False, relatedAreaEnd=None):
        """ Executes check functionality

        Parameters:
            item(string)            :   Item to be checked
            timeout(int)            :   Timeout for check (default = None)
            occurrence(1)           :   Amount of occurences (default = 1)
            relatedTo(string)       :   Item, which is related to wanted item
            doNotReport(boolean)    :   Whether test step is put to test report or not
            relatedAreaEnd(string)  :   Definition of related area end

        Returns True if item was found, False if not
        """
        if not doNotReport:
            if relatedTo != None:
                self.phone.comment('check(%s) (on same area as %s)'%(self.phone.uiState._getCommented(item), self.phone.uiState._getCommented(relatedTo)))
            else:
                self.phone.comment('check(%s)'%self.phone.uiState._getCommented(item))

        try:
            result = self.phone.uiState.revealItem(item, timeout, index=occurrence,containerObject=relatedTo, relatedAreaEnd=relatedAreaEnd)
        except TestException:
            # when scrolling fails, we are just returning False
            result = False
        else:
            if result is None:
                result = False
            else:
                result = True

        return result


class NGRead(object):
    """Class for reading screen items"""
    def __init__(self, phone):
        """Initialize test case instance for class."""
        self.phone = phone

    def __call__(self, searchString=None, area=None, relatedTo=None, getLogicalIds=True, type=None, doNotReport=False, called = False, relatedAreaEnd=None, fullInfo=False):
        """Executes read screen

        Read returns list of screen images and texts

        Parameters:
            searchString (str)     :  Optional string containing wildcard(s). Only items matching this will be returned
            area(4-tuple of ints)  :  Area x,y,w,h where text is read from
            relatedTo (str)        :  Item which is needs to be related to item(s) read from screen
            getLogicalIds (bool)   :  By default, logical ids are used. Set to "false" to return translated texts and image png names
            type (str)             :  Type of the content, 'image' or 'text'. By default "None" which returns images and texts
            doNotReport(boolean)   :  Whether test step is put to test report or not
            called(boolean)        :  Whether __call__ is called or not

        Return:
            List of strings
        """
        assert isinstance(area, tuple) or area == None or area == 'full', 'Given area needs to be tuple of 4 integers!'
        assert (isinstance(type, str) and (type=='image' or type=='text')) or type == None, 'Given type needs to be "image" or "text"!'
        assert isinstance(relatedTo, str) or relatedTo == None, 'Given relatedTo param needs to be string!'
        if searchString != None:
            assert "*" in searchString or "?" in searchString or ("[" in searchString and "]" in searchString), 'Given searchString does not contain any wildcards'

        if not doNotReport and not called:
            self.phone.comment('read()')

        self.phone.uiState.getCurrentState(refresh=True)

        # by default, use visible screen area as area.
        if area == None:
            area = (0,0,self.phone.uiState.getScreenWidth(), self.phone.uiState.getScreenHeight())
        if area == 'full':
            area = None

        if type == 'image':
            content = ['image-widget']
        elif type == 'text':
            content = ['label', 'textinput']
        else:
            content = None

        foundItems = []
        nodes = self.phone.uiState.getItemNodes(contentType=content, area=area, relatedItem=relatedTo, relatedAreaEnd=relatedAreaEnd)

        for node in nodes:
            logicalName = None

            if node.getName() == 'image-widget':
                item = os.path.split(node.getAttribute('image'))[-1]
                if getLogicalIds:
                    logicalName = self.phone.getLogicalImageName(item)
                    if logicalName:
                        logicalName = logicalName[0]
            elif node.getName() == 'label' or node.getName() == 'textinput':
                item = node.getAttribute('text')
                if getLogicalIds:
                    logicalName = self.phone.getLogicalText(item)
            else:
                assert False, 'Something went wrong, could not get image or text nodes'

            if getLogicalIds and logicalName:
                item = logicalName

            if searchString != None and not fnmatch.fnmatch(item, searchString): # if searchstring is used, skip not wanted items
                continue
            if fullInfo:
                item = (item, (int(node.getAttribute("left")), int(node.getAttribute("top")), int(node.getAttribute("width")), int(node.getAttribute("heigth"))))
            foundItems.append(item)

        if not doNotReport:
            self.phone.comment('Screen contents read, %s items found' % len(foundItems))

        return foundItems

    def texts(self, searchString=None, area=None,relatedTo=None, getLogicalIds=True, doNotReport=False, relatedAreaEnd=None, fullInfo=False):
        """ Return screen texts """
        if not doNotReport:
            self.phone.comment('read.texts()')

        return self.__call__(searchString, area, relatedTo, getLogicalIds, type='text', doNotReport=doNotReport, called=True, relatedAreaEnd=relatedAreaEnd, fullInfo=fullInfo)

    def images(self, searchString=None, area=None,relatedTo=None, getLogicalIds=True, doNotReport=False, relatedAreaEnd=None, fullInfo=False):
        """ Return screen images """
        if not doNotReport:
            self.phone.comment('read.images()')

        return self.__call__(searchString, area, relatedTo, getLogicalIds, type='image', doNotReport=doNotReport, called=True, relatedAreaEnd=relatedAreaEnd, fullInfo=fullInfo)


class AdjustVolume(object):
    """ Class for selecting volume with volume keys"""
    def __init__(self, phone):
        """Initialize test case instance for class."""
        self.phone = phone
        self.currentMaximumVolume = 0 # this will be checked during volume set, if too high volume is wanted for volume control (e.g. 15 when 10 is maximum)


    def __findCurrentVolumeLevel(self):
        """ Finds the current volume level by pressing volume keys up and down.
            Note: this method cannot determine was the volume level maximum or maximum - 1 , actually this method will lower the volume from maximum to maximum - 1.
        """

        delay = 70 # initial delay to wait before trying to find volumebar
        firstVolumebarWidth = None # save width from first volumebar reading
        interval = 0 # attemp to read the interval from two volumebar readings

        for i in range(10):

            if firstVolumebarWidth == None: # on first reading, increase volume and find container width
                self.phone.select('KBD_KEY_VOL_UP', doNotReport=True)
            self.phone.delay(delay, False) # sleep awhile so volume bar will be shown on screen. A bit sensitive part..

            # uiChanged --> True so that dump will be taken by force
            # FIXME: Use event approach instead
            self.phone.uiState.setUIChanged(True)

            self.phone.uiState.getCurrentState(refresh=True)

            # get the containers in dialog-area node, volume bar should be a horizontal container
            containers = self.phone.uiState.currentStateFull.findall('//horizontal-container[@visible="true"]/ancestor::stacked-container[1][@name="dialog-area"]//horizontal-container[not(descendant::*)]')
            if containers:
                for container in containers:
                    try:
                        x,y,w,h = [int(p) for p in container.getAttribute('coords').split(",")]
                    except Exception:
                        #Skip item if coordinates are missing
                        continue

                    ## check against known intervals.
                    #for interv in intervals:
                    #    if w % interv == 0: # this could be the interval
                    #        temp_interval = interv
                    #        break
                    #    continue
                    #
                    #if temp_interval == 0:
                    #    continue # no correct container found, check next one
                    # if this was the first reading, save the volumebar width
                    if firstVolumebarWidth == None:
                        firstVolumebarWidth = w
                        w = None  # this will be checked when continuing to vol- press
                        break
                    else:
                        interval = int(math.fabs(firstVolumebarWidth - w))
                        break

            else:
                debug.out("volumebar refresh delay %s is NOT ok. Adding delay and trying again" % delay)
                #self.phone.delay(1000, False) # wait that volume bar disappears and start again
                if firstVolumebarWidth == None: # if this is true, up has been pressed once, return to original state
                    self.phone.select('KBD_KEY_VOL_DOWN', doNotReport=True)
                # reset found width to start again with increased delay
                firstVolumebarWidth = None
                delay += 50

            # if first attemp succeeded, next round will catch volumebar after down press. If this is attemp after vol- press, then w is not None
            if firstVolumebarWidth != None and w == None:
                self.phone.select('KBD_KEY_VOL_DOWN', doNotReport=True)

            if interval != 0: # if interval has got, break the loop
                break

        if interval == 0:
            self.phone.fail("Could not find volume bar")

        assert w % interval == 0, "Volume bar width does not match interval (width: %s, interval: %s)" % (w, interval)

        firstRoundVolume = int(firstVolumebarWidth / interval)
        currentVolume = int(w / interval)
        self.currentMaximumVolume = int(self.phone.uiState.getScreenWidth() / interval) # save current volume bar maximum value
        debug.out("current volume %s / %s" % (currentVolume, self.currentMaximumVolume))

        return (currentVolume, self.currentMaximumVolume)

    def __call__(self, level):
        """ Executes volume select functionality.

        Parameters:
            level(int)      :   Volume level to be selected (between 0 and current volume bar maximum)
        """
        import time

        currentVolume = self.__findCurrentVolumeLevel()[0]

        assert isinstance(level, int), "Given volume level is not integer (instead %s)" % type(level)
        if not (level <= self.currentMaximumVolume and level >= 0):
            self.phone.fail("adjustVolume: given level is not valid. Valid ones for this specific volume bar are 0 - %s)" % self.currentMaximumVolume)

        self.phone.comment("adjustVolume(%s)" % level)

        if level < currentVolume:
            while level < currentVolume:
                self.phone.delay(200, False)
                self.phone.select('KBD_KEY_VOL_DOWN')
                currentVolume -= 1

        elif level > currentVolume:
            while level > currentVolume:
                self.phone.delay(200, False)
                self.phone.select('KBD_KEY_VOL_UP')
                currentVolume += 1

        else: # volume level is now ok, pass
            pass

        return True

        ## TODO: current volume level should be asked from yapas

        #doCheck = False

        #if doCheck:
        #
        #    currentVolume = self.getCurrentVolumeLevel()
        #    assert currentVolume == level, "Adjusted volume, but the volume level is %s when it should be %s" % (currentVolume, level)

        #    debug.brf("Selected volume level %s and verified from UI" % level)
        #    return True
        #else:
        #    debug.brf("Selected volume level %s" % level)
        #    return True


class VirtualKeyboard(object):
    """ Class for virtual keyboard-component

    Note!!! THIS CLASS MEANT TO BE USED IN scripting.py ONLY!!!

    Format for the layout maps is:
    self.__layoutMaps[LAYOUT_ID][CHARACTER]=((x_center,y_center),flags_fo_ all_case_views_which_has_this_character,number_of_repeats_needed_to_input_character)
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
        self.getStatusSxString = """\
(begin
    (define/mutable (granite-get-input-status)
        (define s "{")
        (define focused (send (send (send primary-root-container get-focused) get-focused) get-focused))

        (when (member? 'get-status focused)
            (dictionary-for-each (send focused get-status)
                (lambda (key value)
                    (when (and (not (equal? key 'text))(not (equal? key 'autocase)) )
                        (set! s (string-append s "'" (send key ->string) "':'" (send value ->string) "'," )
                    )
                    )
                )
            )
        )

        (set! s (string-append s "}" ))
        s
    )
    (granite-get-input-status)
)
"""

        self.getLocaleFeaturesString = """\
(begin
    (define/mutable (granite-get-locale-features)
       (define s "[")

       (map (lambda (value)
               (set! s (string-append s "'" (send value ->string) "'," )))
           (send (send (get-input-locale-manager) get-current-locale) get-features)
       )
       (set! s (string-append s "]" ))
       s
    )
    (granite-get-locale-features)
)
"""

        self.getVKBModifierString = """\
(send
            (send
                (car
                    (send
                        (send
                            (send (get-app-manager) get-topmost-application)
                            get-topmost-screen
                        )
                        get-popup-list
                    )
                )
                get-keyboard
            )
            get-modifier
        )
"""

        self.isInputChangedString = """\
(begin
    (define/mutable (test-automation-is-input-changed)
        (define returnvalue #t)
        (set! returnvalue (not (eq? test-automation-input (send (send (send primary-root-container get-focused) get-focused) get-focused))))
        (set! test-automation-input (send (send (send primary-root-container get-focused) get-focused) get-focused))
        returnvalue
    )
    (test-automation-is-input-changed)
)
"""
    def getVKBLanguage(self):
        """ Get input language using sx"""

        return self.phone.sx('(send (send (get-input-locale-manager) get-current-locale) get-iso)', convertToString=False)

    def getVKBStatus(self):
        """ Get input status dictionary using sx"""
        inputStatus = self.phone.sx(self.getStatusSxString)
        if not inputStatus:
            return {}
        inputStatus = inputStatus.replace("\n","\\n").replace("\\","\\\\")

        try:
            returnValue = eval(inputStatus)
        except Exception, e:
            debug.err(e)
            raise TestException("Invalid response when getting keyboard status: %s"%str(e), self.phone)
        else:
            return returnValue

    def getVKBEditMode(self):
        """ Get edit mode state using sx.

        Returns state from text-editor-manager
        """
        return eval(self.phone.sx('(send (get-text-editor-manager) get-edit-mode)', convertToString=True).title())

    def getVKBIsTextInput(self):
        """ Returns True if widget which has focus is text-input """
        return eval(self.phone.sx('(send (send (send (send primary-root-container get-focused) get-focused) get-focused) is-textinput)', convertToString=True).title())

    def getVKBIsTextInputChanged(self):
        """ Returns True if widget which has focus has changed """
        return eval(self.phone.sx(self.isInputChangedString, convertToString=True, doNotReport=True).title())

    def getLocaleFeatures(self):
        localeFeatures = self.phone.sx(self.getLocaleFeaturesString)
        localeFeatures = localeFeatures.replace("\n","\\n").replace("\\","\\\\")
        try:
            returnValue = eval(localeFeatures)
        except Exception, e:
            debug.err(e)
            raise TestException("Invalid response when getting keyboard locale features: %s"%str(e), self.phone)
        else:
            return returnValue

    def getMajorMode(self):
        return self.phone.sx('(send (send (send (send primary-root-container get-focused) get-focused) get-focused) get-major-mode)', convertToString=True, doNotReport=True)

    def getVKBModifier(self):
        return self.phone.sx(self.getVKBModifierString, convertToString=True, doNotReport=True)

    def setPhone(self,phone):
        """ Set new phone instance to virtual keyboard-class

        Parameters:
            tc(Phone)  :   new phone-instance
        """
        self.phone = phone

    def _isVKBOnScreen(self, capture):
        """ Check if virtual keyboard is on the screen

        Parameters:
            capture(NodeUtils)  :   new UI state dump
        """

        vkbStatus = self.getVKBStatus()
        if not vkbStatus or not vkbStatus.has_key('minor-mode'):
            if self.vkbOnScreen:
                debug.out("********** Reset VKB **********")
                self.vkbOnScreen = False
                #self.modifierStatusDict["case"] = self.CASE_UPPER
                #self.modifierStatusDict["symbol"] = self.CASE_SYMBOLS_2
                self.__layoutMaps = {}
                self.__visitedViews = 0b0
                self.currentLayout = None
                self.orientation = None

            return

        # initialize button names here since in vkb initialization phase tc is not finished initialization
        if len(self.callbuttonNames) < 1 or self.searchstring == "" :
            self.shiftButtonNames = [self.phone.uiState._getImage('textinput-manager/k-shift'), self.phone.uiState._getImage('textinput-manager/k-shift-accent'),'1/2','2/2']
            self.numberModeNames = ['123', '?123','?12:)','ABC','12#']
            self.returnButtonNames = [self.phone.uiState._getImage('textinput-manager/k-enter')]
            self.callbuttonNames = [self.phone.uiState._getImage('voice-call-application/answer-call'), self.phone.uiState._getImage('dialer-service/calllog-button')]
            self.backspaceButtonNames = [self.phone.uiState._getImage('textinput-manager/k-clear')]

            # Create string for detecting VKB
            searchSubStrings = []
            buttonsToSearch = self.callbuttonNames + self.returnButtonNames + self.backspaceButtonNames
            for i in range(len(buttonsToSearch)):
                searchSubStrings.append('contains(@image,"%s")'%buttonsToSearch[i])

            self.searchstring = " or ".join(searchSubStrings)

        if self.__REentrantLock:
            return

        result = False
        # Virtual keyboard is on screen if image for enter-, return- or call-buttons is found
        #for imageNode in capture.findall('//image-widget'):
        vkbButtonNode = self.phone.uiState.currentStateFull.find('//evo-dynamic-keyboard[@bottom<="%s" and ./key[not(@visible) or @visible="true"]]' % self.phone.uiState.getScreenHeight())
        if not vkbButtonNode:
            vkbButtonNode = capture.find('//image-widget[@visible="true" and (%s)]'%self.searchstring)
        if vkbButtonNode:
            result = True
            # This temporary check is not needed after Granite server sends notifications when UI has changed
            if self.__checkLayout(getNewDump = False, buttonNode=vkbButtonNode) == False:
                result = False

        if not result and self.vkbOnScreen:
            debug.out("********** Reset VKB **********")
            self.vkbOnScreen = False
            #self.modifierStatusDict["case"] = self.CASE_UPPER
            #self.modifierStatusDict["symbol"] = self.CASE_SYMBOLS_2
            self.__layoutMaps = {}
            self.__visitedViews = 0b0
        elif result:
            self.vkbOnScreen = True

        self.__REentrantLock = False

    def __getCase(self, vkbNode=None):
        """ Resolve correct case using sx-calls and xml-dump

        """

        if self.phone.isFollower():
            debug.out('follower mode, no case check')
            return

        if not self.currentLayout:
            self.__checkLayout()

        if self.currentLayout&self.LAYOUT_DIALER or self.currentLayout&self.LAYOUT_NUMBER_MODE:
            return # Keep current case

        statusDict = self.getVKBStatus()
        if not statusDict or not statusDict.has_key("minor-mode") or not statusDict.has_key("caps-mode"):
            debug.err("Error, VKB status is invalid. Skipping __getCase()")
            self.phone.comment("Error, invalid VKB status: %s" % statusDict)   # TEMP comment for catching minor-mode related bug.
            self.phone.capture(onlyImage=True)
            return

        if statusDict["minor-mode"]=='symbol':
            modifier = self.getVKBModifier()
            if modifier:
                if self.currentLayout&self.LAYOUT_ITUT:
                    if modifier == 'base':
                        self.currentCase = self.CASE_SYMBOLS_1
                    elif modifier == 'sct_1':
                        self.currentCase = self.CASE_SYMBOLS_2
                    elif modifier == 'sct_2':
                        self.currentCase = self.CASE_SYMBOLS_3
                    else:
                        self.phone.fail("Unknown Keyboard modifier: %s"% modifier)
                else:
                    try:
                        self.currentCase = eval("self.CASE_SYMBOLS_%s"%modifier.replace("sct_",""))
                    except Exception, e:
                        self.phone.fail("Unknown Keyboard modifier: %s"% modifier)

        elif statusDict["minor-mode"]=='phonenumber':
                self.currentCase = self.CASE_ITUT_NUMBERS
                debug.out("__getCase: ITU-T numbers")
        else:
            self.currentCase = statusDict["caps-mode"] == 'uppercase' and self.CASE_UPPER or self.CASE_LOWER

            if self.currentCase==self.CASE_UPPER:
                # Cannot resolve correct case without xml-dump
                if not vkbNode:
                    try:
                        self.__REentrantLock = True
                        self.waitForVKB()
                    except Exception, e:
                        raise e
                    finally:
                        self.__REentrantLock = False
                    buttonNode = self.__getVKBNode()
                else:
                    buttonNode = vkbNode
                self.capsLockOn = bool(buttonNode.find("//image-widget[contains(@image,'%s')]" % self.phone.uiState._getImage('textinput-manager/k-shift')) )

            debug.out("__getCase: %s"%statusDict["caps-mode"])



    def __checkLayout(self, getNewDump = True, buttonNode=None):
        """ Check layout from display and add layouts to dict if needed

        Parameters:
            getNewDump(bool)    :   set to false if new dump from phone is not needed
        """

        if self.phone.isFollower():
            debug.out('follower mode, no layout check')
            return

        if self.__REentrantLock:
            return

        # Check if virtual keyboard is on screen
        if not buttonNode:
            try:
                self.__REentrantLock = True
                self.waitForVKB()
                buttonNode = self.__getVKBNode()
            except Exception, e:
                raise e
            finally:
                self.__REentrantLock = False


        self.inputLanguage = self.getVKBLanguage()

        if os.path.split(buttonNode.getAttribute('image'))[1] in self.callbuttonNames:
            # Dialler is visible
            vkbContainerNode = self.phone.uiState.currentState

            self.currentLayout = self.LAYOUT_DIALER
            self.currentCase = self.CASE_ITUT_NUMBERS
            if self.currentLayout not in self.__layoutMaps.keys():
                self.__layoutMaps[self.currentLayout] = {}

            # Add call- and contacts-buttons. No functionality to press buttons yet!
            for imageNode in self.phone.uiState.getCurrentState(refresh=getNewDump).findall('//image-widget'):
                if os.path.split(imageNode.getAttribute('image'))[1] in self.callbuttonNames:
                    x,y,w,h = [int(p) for p in imageNode.getAttribute('coords').split(",")]
                    xc = x+(w/2)
                    yc = y+(h/2)

                    self.__layoutMaps[self.currentLayout]['call']=((xc,yc),self.currentCase,1)
                if self.phone.uiState._getImage('dialer-service/contact-button') in imageNode.getAttribute('image'):
                    x,y,w,h = [int(p) for p in imageNode.getAttribute('coords').split(",")]
                    xc = x+(w/2)
                    yc = y+(h/2)

                    self.__layoutMaps[self.currentLayout]['contacts']=((xc,yc),self.currentCase,1)

            for characterNode in vkbContainerNode.findall('//label'):
                character = characterNode.getAttribute('text')
                x,y,w,h = [int(p) for p in characterNode.getAttribute('coords').split(",")]
                xc = x+(w/2)
                yc = y+(h/2)
                if len(character)==1 and character != '+': # +-character is added when *-character is found
                    self.__layoutMaps[self.currentLayout][character]=((xc,yc),self.currentCase,1)

                    # If keyboard uses native digits instead of arabic digits add both digits to layout map
                    originalCharacter = characterNode.getAttribute('original-text')
                    if originalCharacter:
                        self.__layoutMaps[self.currentLayout][originalCharacter]=((xc,yc),self.currentCase,1)

                    if character == '*':
                        self.__layoutMaps[self.currentLayout]['*']=((xc,yc),self.currentCase,1)
                        self.__layoutMaps[self.currentLayout]['+']=((xc,yc),self.currentCase,2)
                        self.__layoutMaps[self.currentLayout]['p']=((xc,yc),self.currentCase,3)
                        self.__layoutMaps[self.currentLayout]['w']=((xc,yc),self.currentCase,4)
                else:
                    if character == '*+':
                        self.__layoutMaps[self.currentLayout]['*']=((xc,yc),self.currentCase,1)
                        self.__layoutMaps[self.currentLayout]['+']=((xc,yc),self.currentCase,2)
                        self.__layoutMaps[self.currentLayout]['p']=((xc,yc),self.currentCase,3)
                        self.__layoutMaps[self.currentLayout]['w']=((xc,yc),self.currentCase,4)

            self.__REentrantLock = False
            return

        # Use evo-dynamic-keyboard-node
        elif buttonNode.getName() == 'evo-dynamic-keyboard':
            # virtual keyboard is visible
            vkbContainerNode = buttonNode

            self.majorMode = self.getMajorMode()
            localeFeatures = self.getLocaleFeatures()
            localeFeatures.sort()
            vkbStatus = self.getVKBStatus()
            if not vkbStatus.has_key("minor-mode"):
                self.__REentrantLock = False
                return False


            self.orientation = eval("self.LAYOUT_%s"%self.phone.sx("(send lcdmanager get-orientation)", convertToString=True).upper())

            if self.getVKBIsTextInputChanged() or (self.inputLanguage != self.prevLanguage) or (self.prevKBFeatures != localeFeatures) or self.currentLayout == None:
                if ('itu-t' in localeFeatures and self.orientation&self.LAYOUT_PORTRAIT):
                    self.currentLayout = self.LAYOUT_ITUT
                elif vkbStatus["minor-mode"]=='phonenumber':
                    self.currentLayout = self.LAYOUT_NUMBER_MODE
                    self.currentCase = self.CASE_ITUT_NUMBERS
                elif vkbStatus["minor-mode"]=='email':
                    self.currentLayout = self.LAYOUT_EMAIL
                elif self.majorMode=='recipient-list':
                    if vkbStatus["minor-mode"]=='email-or-recipient':
                        self.currentLayout = self.LAYOUT_EMAIL_OR_RECIPIENT
                    else:
                        self.currentLayout = self.LAYOUT_RECIPIENT_LIST
                elif self.majorMode == 'url':
                    self.currentLayout = self.LAYOUT_URL
                else:
                    if self.majorMode not in self.knownMajorModes and vkbStatus["minor-mode"] not in self.knownMinorModes:
                        self.phone.warn("Unknown modes for keyboard found! major=%s, minor=%s"%(self.majorMode,vkbStatus["minor-mode"]))
                    self.currentLayout = self.LAYOUT_QWERTY


                # Take this back in use when input for different languages is implemented
    #            if vkbContainerNode.find('//label[@text="EN"]'):
                self.currentLayout = self.currentLayout | self.LAYOUT_LANG_EN
    #            else:
    #                self.currentLayout = self.currentLayout | self.LAYOUT_LANG_CH

                self.currentLayout = self.currentLayout | self.orientation


            self.prevLanguage = self.inputLanguage
            self.prevKBFeatures = localeFeatures

            # Select correct string from dict by masking current layout and search for labels to indentify view
            #result = vkbContainerNode.find("//label[@text='%s']"%self.specialCharacterViewDetectionDict[self.currentLayout&self.BUTTONLAYOUT_MASK])
            self.__getCase(vkbContainerNode)

            debug.out("__checkLayout: %s"%self.currentCase)

            if self.currentLayout not in self.__layoutMaps.keys():
                self.__layoutMaps[self.currentLayout] = {}

            # Find coordinates for shift-key
            shiftNode = vkbContainerNode.find('//key[@name="k-shift"]')
            # Map page-key to shift with qwerty-layout
            if not shiftNode and not self.currentLayout&self.LAYOUT_ITUT:
                shiftNode = vkbContainerNode.find('//key[@name="k-page"]')
            if shiftNode:
                x,y,w,h = [int(p) for p in shiftNode.getAttribute('coords').split(",")]
                xc = x+(w/2)
                yc = y+(h/2)

                if self.currentLayout&self.BUTTONLAYOUT_MASK&self.LAYOUT_QWERTY or \
                    self.currentLayout&self.BUTTONLAYOUT_MASK&self.LAYOUT_EMAIL:
                    self.__layoutMaps[self.currentLayout]['shift']=((xc,yc),self.CASE_LOWER|self.CASE_UPPER|self.CASE_SYMBOLS_1|self.CASE_SYMBOLS_2,1)
                else:
                    self.__layoutMaps[self.currentLayout]['shift']=((xc,yc),self.currentCase,1)

            #ITU-T layout has page-key
            pageNode = vkbContainerNode.find('//key[@name="k-page"]')
            if pageNode:
                x,y,w,h = [int(p) for p in pageNode.getAttribute('coords').split(",")]
                xc = x+(w/2)
                yc = y+(h/2)

                self.__layoutMaps[self.currentLayout]['page']=((xc,yc),self.CASE_SYMBOLS_1|self.CASE_SYMBOLS_2|self.CASE_SYMBOLS_3,1)

            # Collect all characters from current view to dictionary
            for characterNode in vkbContainerNode.findall('//key[contains(@name,"k-key")]'):
                character = scripting.unescape(characterNode.getAttribute('text'))
                x,y,w,h = [int(p) for p in characterNode.getAttribute('coords').split(",")]
                xc = x+(w/2)
                yc = y+(h/2)

                if len(character) == 1 and character not in self.__layoutMaps[self.currentLayout].keys():
                    if character.isalpha():
                        # Upper- and lower-case alphabets are in same locations
                        self.__layoutMaps[self.currentLayout][character.lower()]=((xc,yc),self.CASE_LOWER,1)
                        self.__layoutMaps[self.currentLayout][character.upper()]=((xc,yc),self.CASE_UPPER,1)
                    elif character == '*':
                        if self.currentLayout&self.LAYOUT_ITUT or self.currentLayout&self.LAYOUT_NUMBER_MODE:
                            self.__layoutMaps[self.currentLayout]['*']=((xc,yc),self.currentCase,1)
                            self.__layoutMaps[self.currentLayout]['+']=((xc,yc),self.currentCase,2)
                            self.__layoutMaps[self.currentLayout]['p']=((xc,yc),self.currentCase,3)
                            self.__layoutMaps[self.currentLayout]['w']=((xc,yc),self.currentCase,4)
                        else:
                            self.__layoutMaps[self.currentLayout][character]=((xc,yc),self.currentCase,1)
#                    elif character=='.' or character==',':
                        # '.' and ',' are in the same location for every case
#                        self.__layoutMaps[self.currentLayout][character]=((xc,yc),self.CASE_LOWER|self.CASE_UPPER|self.CASE_SYMBOLS_1|self.CASE_SYMBOLS_2,1)
                    else:
                        self.__layoutMaps[self.currentLayout][character]=((xc,yc),self.currentCase,1)
                # ITU-T layout handling
                elif self.currentLayout&self.LAYOUT_ITUT or self.currentLayout&self.LAYOUT_NUMBER_MODE:
                    if character == '*+':
                        self.__layoutMaps[self.currentLayout]['*']=((xc,yc),self.currentCase,1)
                        self.__layoutMaps[self.currentLayout]['+']=((xc,yc),self.currentCase,2)
                        self.__layoutMaps[self.currentLayout]['p']=((xc,yc),self.currentCase,3)
                        self.__layoutMaps[self.currentLayout]['w']=((xc,yc),self.currentCase,4)

                    elif character == '+*':
                        self.__layoutMaps[self.currentLayout]['+']=((xc,yc),self.currentCase,1)
                        self.__layoutMaps[self.currentLayout]['*']=((xc,yc),self.currentCase,2)
                    else:
                        for i in range(len(character)):
                            self.__layoutMaps[self.currentLayout][character[i]]=((xc,yc),self.currentCase,i+1)
                            if character[i].isalpha():
                                self.__layoutMaps[self.currentLayout][character[i].lower()]=((xc,yc),self.CASE_LOWER,i+1)
                                self.__layoutMaps[self.currentLayout][character[i].upper()]=((xc,yc),self.CASE_UPPER,i+1)

                # If keyboard uses native digits instead of arabic digits add both texts to layout map
                originalCharacter = characterNode.getAttribute('original-text')
                if originalCharacter:
                    self.__layoutMaps[self.currentLayout][originalCharacter]=((xc,yc),self.currentCase,1)


            spaceButtonNode = vkbContainerNode.find('//key[@name="k-space"]')
            if spaceButtonNode:
                x,y,w,h = [int(p) for p in spaceButtonNode.getAttribute('coords').split(",")]
                xc = x+(w/2)
                yc = y+(h/2)
                if self.currentLayout&self.LAYOUT_ITUT:
                    self.__layoutMaps[self.currentLayout][' ']=((xc,yc),self.CASE_LOWER|self.CASE_UPPER,1)
                else:
                    self.__layoutMaps[self.currentLayout][' ']=((xc,yc),self.CASE_LOWER|self.CASE_UPPER|self.CASE_SYMBOLS_1|self.CASE_SYMBOLS_2,1)

            # ITU-T layout has separate buttons for symbol and number views
            numbermodeButtonNode = vkbContainerNode.find('//key[@name="k-mode"]')
#            if numbermodeButtonNode:
            #else:
            if not self.currentLayout&self.LAYOUT_ITUT and not numbermodeButtonNode:
                numbermodeButtonNode = vkbContainerNode.find('//key[@name="k-symbol" or @name="k-default"]')
#                symbolButtonNode = None

            if numbermodeButtonNode:
                x,y,w,h = [int(p) for p in numbermodeButtonNode.getAttribute('coords').split(",")]
                xc = x+(w/2)
                yc = y+(h/2)
                self.__layoutMaps[self.currentLayout]['number_mode']=((xc,yc),self.currentCase,1)
            elif not self.currentLayout&self.LAYOUT_ITUT:
                debug.out('Number mode-button not found:')
                debug.out(vkbContainerNode.toprettyxml())

            symbolButtonNode = vkbContainerNode.find('//key[@name="k-symbol"]')
            if symbolButtonNode:
                x,y,w,h = [int(p) for p in symbolButtonNode.getAttribute('coords').split(",")]
                xc = x+(w/2)
                yc = y+(h/2)
                self.__layoutMaps[self.currentLayout]['symbol']=((xc,yc),self.currentCase,1)

            if self.currentLayout&self.LAYOUT_ITUT:
                defaultmodeButtonNode = vkbContainerNode.find('//key[@name="k-default"]')
                if defaultmodeButtonNode:
                    x,y,w,h = [int(p) for p in defaultmodeButtonNode.getAttribute('coords').split(",")]
                    xc = x+(w/2)
                    yc = y+(h/2)

                    if self.currentCase&self.CASE_ITUT_NUMBERS:
                        self.__layoutMaps[self.currentLayout]['default_%s'%self.currentCase]=((xc,yc),self.currentCase,1)
                    else:
                        self.__layoutMaps[self.currentLayout]['default_%s'%(self.CASE_SYMBOLS_1|self.CASE_SYMBOLS_2|self.CASE_SYMBOLS_3)]=((xc,yc),self.CASE_SYMBOLS_1|self.CASE_SYMBOLS_2|self.CASE_SYMBOLS_3,1)


            # check that we have found space button
            if not self.__layoutMaps[self.currentLayout].has_key(' '):
                # search for space button from full dump
                # FIXME: Remove this temporary solution!!!

                for spaceCharacter in self.spaceButtonText[self.currentLayout&self.LANGUAGE_MASK]:
                    spaceNode = self.phone.uiState.currentStateFull.find("//label[@text='%s']" % spaceCharacter)
                    if spaceNode:
                        x,y,w,h = [int(p) for p in spaceNode.getAttribute('coords').split(",")]
                        xc = x+(w/2)
                        yc = y+(h/2)

                        self.__layoutMaps[self.currentLayout][' ']=((xc,yc),self.CASE_LOWER|self.CASE_UPPER|self.CASE_SYMBOLS_1|self.CASE_SYMBOLS_2,1)
                        break

            clearButtonNode = vkbContainerNode.find('//key[@name="k-clear"]')
            if clearButtonNode:
                x,y,w,h = [int(p) for p in clearButtonNode.getAttribute('coords').split(",")]
                xc = x+(w/2)
                yc = y+(h/2)
                self.__layoutMaps[self.currentLayout]['clear']=((xc,yc),self.CASE_LOWER|self.CASE_UPPER|self.CASE_SYMBOLS_1|self.CASE_SYMBOLS_2,1)

            enterButtonNode = vkbContainerNode.find('//key[@name="k-enter" or @name="k-accept"]')
            if enterButtonNode:
                x,y,w,h = [int(p) for p in enterButtonNode.getAttribute('coords').split(",")]
                xc = x+(w/2)
                yc = y+(h/2)
                self.__layoutMaps[self.currentLayout]['\n']=((xc,yc),self.CASE_LOWER|self.CASE_UPPER|self.CASE_SYMBOLS_1|self.CASE_SYMBOLS_2,1)

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

        statusDict = self.getVKBStatus()

        for i in range(len(string)):
            # Get coordinates for keys as long the case needs to be changed. FIXME! add switchCase to loop
            # no need to care about case in Email layout with other than alphabet characters
            if string[i] in self.__layoutMaps[self.currentLayout].keys() and \
               (self.__layoutMaps[self.currentLayout][string[i]][1]&self.currentCase):
                coords, case, repeat = self.__layoutMaps[self.currentLayout][string[i]]
                if self.currentLayout&self.LAYOUT_ITUT and len(coordinateList) and coords==coordinateList[-1]:
                    breakReason = 'delay'
                    break # To add some delay between characters on same button
                for r in range(repeat):
                    coordinateList.append(coords)
                if self.currentCase==self.CASE_UPPER and not self.capsLockOn:
                    self.currentCase = self.CASE_LOWER
                charactersEntered +=1
                # In common-noun mode, VKB changes to uppercase after dot character so break loop.
                if string[i]=='.' and statusDict['minor-mode']=='common-noun' and not self.capsLockOn:
                    self.currentCase = self.CASE_UPPER
                    break
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
        if self.currentLayout&self.LAYOUT_ITUT:
            layoutViews = layoutViews|self.CASE_ITUT_NUMBERS|self.CASE_SYMBOLS_3
        # FIXME: Don't use isalpha etc. Use case bit mask support in dict instead!

        # Search correct view for character if it is not found from layoutMap-dictionary and content of some view(s) are not known
        stopLoop = 0
        while (character not in self.__layoutMaps[self.currentLayout].keys()) and (self.__visitedViews!=layoutViews) and stopLoop < 10:
            #Change to symbol mode if characters is not alphabet and current case is either lower or upper
            if not character.isalpha() and self.currentCase&(self.CASE_LOWER|self.CASE_UPPER):
                if self.currentLayout&self.LAYOUT_ITUT and not character.isdigit():
                    self.phone._touch.press(self.__layoutMaps[self.currentLayout]['symbol'][0])
                else:
                    self.phone._touch.press(self.__layoutMaps[self.currentLayout]['number_mode'][0])

                if self.currentLayout&self.LAYOUT_ITUT and character.isdigit():
                    self.currentCase = self.CASE_ITUT_NUMBERS
                else:
                    self.currentCase = self.CASE_SYMBOLS_1
                self.phone._run('Switch case',testStepReporting=False)
            # Switch between symbol mode cases if character is not alphabet
            elif not character.isalpha() and self.currentCase&self.CASE_ALL_SYMBOLS:
                button = self.currentLayout&self.LAYOUT_ITUT and 'page' or 'shift'
                self.phone._touch.press(self.__layoutMaps[self.currentLayout][button][0])
                self.phone._run('Switch case',testStepReporting=False)
                if self.currentCase&self.CASE_SYMBOLS_1:
                    self.currentCase = self.CASE_SYMBOLS_2
                elif self.currentCase&self.CASE_SYMBOLS_2 and self.currentLayout&self.LAYOUT_ITUT:
                    self.currentCase = self.CASE_SYMBOLS_3
                else:
                    self.currentCase = self.CASE_SYMBOLS_1

            elif character.isalpha():
                if character.isalpha() and not self.currentCase&(self.CASE_LOWER|self.CASE_UPPER):
                    button = 'default_%s'%(self.currentCase&self.CASE_ITUT_NUMBERS and self.CASE_ITUT_NUMBERS or self.CASE_ALL_SYMBOLS)
                    self.phone._touch.press(self.__layoutMaps[self.currentLayout][button][0])


                    self.phone._run('Switch case',testStepReporting=False)
                    self.currentCase = self.CASE_LOWER
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
                    if self.currentLayout&self.LAYOUT_ITUT:
                        if character.isdigit() or (character in ['+','*','#'] and desiredCase&self.CASE_ITUT_NUMBERS):
                            #Switch from alpha to numbers
                            debug.out('Switch from alpha to number')
                            coordinates.append(self.__layoutMaps[self.currentLayout]['number_mode'][0])
                            self.currentCase = self.CASE_ITUT_NUMBERS
                        else:
                            #Switch from alpha to special character
                            debug.out('Switch from alpha to special character')
                            coordinates.append(self.__layoutMaps[self.currentLayout]['symbol'][0])
                            self.currentCase = self.CASE_SYMBOLS_1
                    else:
                        #Switch from alpha to special character
                        debug.out('Switch from alpha to special character')
                        coordinates.append(self.__layoutMaps[self.currentLayout]['number_mode'][0])
                        self.currentCase = self.CASE_SYMBOLS_1
            else:
                #Switch from special character state
                #With ITU-T layout this handles also transition from number- to alpha-mode
                if desiredCase&(self.CASE_LOWER|self.CASE_UPPER):
                    if self.currentLayout&self.LAYOUT_ITUT:
                        #Switch from special character to alpha
                        debug.out('Switch from special character to alpha')
                        button = 'default_%s'%(self.currentCase&self.CASE_ITUT_NUMBERS and self.CASE_ITUT_NUMBERS or self.CASE_ALL_SYMBOLS)
                        coordinates.append(self.__layoutMaps[self.currentLayout][button][0])

                    #if self.currentLayout&self.LAYOUT_EMAIL:
                    #    coordinates.append(self.__layoutMaps[self.currentLayout]['shift'][0])
                    else:
                        coordinates.append(self.__layoutMaps[self.currentLayout]['number_mode'][0])

                    self.currentCase = self.CASE_LOWER
                else:
                    if self.currentLayout&self.LAYOUT_ITUT:
                        if self.currentCase&self.CASE_ITUT_NUMBERS or desiredCase&self.CASE_ITUT_NUMBERS: #changing between number- and symbol-modes
                            debug.out('Switch from number- or symbol-mode to alpha-mode')
                            button = 'default_%s'%(self.currentCase&self.CASE_ITUT_NUMBERS and self.CASE_ITUT_NUMBERS or self.CASE_ALL_SYMBOLS)
                            coordinates.append(self.__layoutMaps[self.currentLayout][button][0])
                            self.currentCase = self.CASE_LOWER
                        else:
                            if self.currentCase&self.CASE_SYMBOLS_1:
                                coordinates.append(self.__layoutMaps[self.currentLayout]['shift'][0])
                                self.currentCase = self.CASE_SYMBOLS_2
                            elif self.currentCase&self.CASE_SYMBOLS_2 and self.currentLayout&self.LAYOUT_ITUT:
                                self.currentCase = self.CASE_SYMBOLS_3
                                coordinates.append(self.__layoutMaps[self.currentLayout]['shift'][0])
                            else:
                                self.currentCase = self.CASE_SYMBOLS_1
                                coordinates.append(self.__layoutMaps[self.currentLayout]['shift'][0])

                    else:
                        # Switch between first and second special character screens
                        debug.out('Switch between first and second special character screens')
                        coordinates.append(self.__layoutMaps[self.currentLayout]['shift'][0])
                        # Switch current case with bitwise XOR-operation
                        self.currentCase = self.currentCase ^ (self.CASE_SYMBOLS_1|self.CASE_SYMBOLS_2)

            if coordinates:
                self.phone._touch.press(coordinates)
                self.phone._run('Switch case',testStepReporting=False)

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

    def __getVKBNode(self):
        """ Return Virtual keyboard node from current state.

        """
        #FIXME!!! This seems to speed up handling too much, try again with ui update ntf-support with text_editing_rfa-cases
        #vkb = self.phone.uiState.currentStateFull.find('//evo-dynamic-keyboard[@bottom<="%s" and ./key[not(@visible) or @visible="true"]]'%scripting.SCREEN_HEIGHT)
        vkb = self.phone.uiState.currentStateFull.find('//evo-dynamic-keyboard[./key[not(@visible) or @visible="true"]]')
        if not vkb:
            vkb = self.phone.uiState.currentState.find('//image-widget[@visible="true" and (%s)]'%self.searchstring)
        else:
            # check evo-dynamic-keyboard coordinates
            # NOTE: when transition is ongoing, keyboard can be partly outside the screen
            if int(vkb.getAttribute('bottom')) > self.phone.uiState.getScreenHeight() or \
               not vkb.find('key[@bottom>"%s"]' % self.phone.uiState.getScreenHeight()) is None:
                return None

        return vkb

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

            # uiChanged --> True so that dump will be taken by force
            # FIXME: Use event approach instead
            self.phone.uiState.setUIChanged(True)
            self.phone.uiState.getCurrentState(refresh= True)

            if not self.__getVKBNode():
                if i==0:
                    self.phone.comment("Wait for virtual keyboard")
            else:
                statusDict = self.getVKBStatus()
                if len(statusDict)>0 and statusDict.has_key("minor-mode") and statusDict.has_key("caps-mode"):
                    returnValue = True
                else:
                    if not vkbErrorPrinted:
                        self.phone.comment("Error! Problem with VKB status dictionary: %s" % statusDict)
                        vkbErrorPrinted = True

            i+=1

        return returnValue

    def _write(self, string, defaultText='', timeout=None):
        """ Method for entering text using VKB.

        Parameters:
            string      :   string to be entered
            defaultText :   Text already in textinput-field
            timeout     :   Time to wait for keyboard to appear
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
            self.phone.sendWaitMessageToGraniteGUI( int(len(string) * 0.5 ), 'Writing with virtual keyboard. Wait %s seconds.' % ( int(len(string) * 0.5) ))
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
                self.__getCase()
            characterCoordinates = []

            #Switch to correct case
            self.__switchCase(splittedString[0])

            # Enter first charcter separately to verify correct case after it has been entered
            if (not self.currentLayout&self.LAYOUT_DIALER and not self.currentLayout&self.LAYOUT_NUMBER_MODE) or self.capsLockOn:
                # Get coordinates for keys. If empty list is returned text cannot be entered.
                characterCoordinates, charactersEntered, breakReason = self.__getCoordinateListForString(splittedString[0], defaultText=='' and charactersLeft==len(splittedString))
                self.phone.failUnless(charactersEntered,"Cannot write text: '%s'"%splittedString)

                charactersLeft -= charactersEntered

                debug.out("_write: %s"%characterCoordinates)
                debug.out('Enter first character "%s"'%splittedString[0])

                self.phone._touch.press(characterCoordinates)
                self.phone._run('Enter first character "%s"'%splittedString[0],testStepReporting=False)
                if breakReason == 'delay':
                    self.phone.delay(1000)

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
                        self.__getCase()

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
                self.phone.failUnless(charactersEntered,"Cannot write text: '%s'"%splittedString)

                charactersLeft -= charactersEntered

                debug.out("_write: %s"%characterCoordinates)
                debug.out('Enter characters "%s"'%splittedString[startIndex:len(splittedString)-charactersLeft])

                # With long texts it might be possible that message to server is too large.
                # Split too large messages by using maxStringLengthToServer-variable
                coordsLeft = len(characterCoordinates)
                coordsStartIndex = 0
                while coordsLeft:
                    if coordsLeft<self.maxStringLengthToServer:
                        debug.out("Writing from index %s to %s"%(coordsStartIndex,len(characterCoordinates)))
                        self.phone._touch.press(characterCoordinates[coordsStartIndex:], wait=self.inputInterval[core.FW_conf["settings"].System.InputInterval])
                        self.phone._run('Enter characters "%s"'%splittedString[startIndex:len(splittedString)-charactersLeft],testStepReporting=False)
                        coordsLeft = 0
                    else:
                        self.phone._touch.press(characterCoordinates[coordsStartIndex:(coordsStartIndex+self.maxStringLengthToServer)], wait=self.inputInterval[core.FW_conf["settings"].System.InputInterval])
                        self.phone._run('Enter characters "%s"'%splittedString[startIndex+coordsStartIndex:len(splittedString)-charactersLeft],testStepReporting=False)
                        coordsStartIndex += self.maxStringLengthToServer
                        coordsLeft = len(characterCoordinates)-coordsStartIndex
                        debug.out("coordsStartIndex: %s, coordsLeft: %s"%(coordsStartIndex,coordsLeft))
                if breakReason == 'delay':
                    self.phone.delay(1000)

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

class BlackBoxVirtualKeyboard(object):

    def __init__(self, phone):
        self.vkbSettings = None
        self.phone = phone
        self.coords = None
        self.mode = None # current mode
        self.orientation = None # current orientation
        self.defaultDelay = 10 # delay between keypresses

    def _pressSpecialKey(self, key, mode='Abc', orientation='portrait'):
        """ press shift, enter or other special key """
        assert key in ['shift', 'enter']
        self.phone.comment('Input special key %s' % key)
        self._loadVkbSettings()
        self._loadCoords(orientation, mode)
        if not key in self.coords.keys(): # check transition to different mode
            new_mode = self._findModeForChar(key)
            if not new_mode:
                raise Exception('Cannot find vkb mode where char %s is' % key)
        else:
            self.phone._touch.press(tuple(self.coords[key]),None, self.defaultDelay)
            self.phone._run('Press to coordinates: %s,%s' % tuple(self.coords[key]))

    def _writeBlackBox(self, string, mode='Abc', orientation='portrait', delayBetweenPresses=None):
        """ write text using black box """

        self.phone.comment('Input %s' % string)
        self._loadVkbSettings()

        if not self.vkbSettings:
            raise Exception('Mapped VirtualKeyboard: no settings data loaded')

        if not self.vkbSettings.has_key(orientation):
            raise Exception('Mapped VirtualKeyboard: no orientation mode named %s' % str(orientation))

        if not self.vkbSettings[orientation].has_key(mode):
            raise Exception('Mapped VirtualKeyboard: error with setting file, mode %s not defined for orientation %s' % (str(mode), orientation) )

        self._loadCoords(orientation, mode)

        if self.mode == 'Abc' or self.mode == 'ABC':
            caps = True
        else:
            caps = False

        if delayBetweenPresses == None:
            delayBetweenPresses = core.FW_conf['settings'].System.BlackBoxVKBDelayBetweenPresses

        for c in string:

            if caps and c.islower(): # if caps mode on and non-caps char written, press shift
                self.phone._touch.press(tuple(self.coords['shift']),None, self.defaultDelay)
                #self.phone._touch.press(tuple(self.coords['shift']),None, self.defaultDelay)
                self.phone._run('Press to coordinates: %s,%s' % tuple(self.coords['shift']))

            c = c.lower() # all chars in settings are lower
            if c == ' ':
                c = 'space'

            if not c in self.coords.keys(): # check transition to different mode
                new_mode = self._findModeForChar(c)
                if not new_mode:
                    raise Exception('Cannot find vkb mode where char %s is' % c)

                self._transition(new_mode)

            if type(self.coords[c][0]) == types.StringType: # if coord is a stringtype, it's a long press or key sequence
                if self.coords[c][0] == "long": # long press for key
                    key = self.coords[c][1]
                    debug.brf('long press %s' % key)
                    self.phone._touch.press(tuple(self.coords[key]),None, 1500)
                    self.phone._run('Press to coordinates: %s,%s' % tuple(self.coords[key]))
                else:
                    for key in self.coords[c]:
                        self.phone._touch.press(tuple(self.coords[key]),None, self.defaultDelay)
                        self.phone._run('Press to coordinates: %s,%s' % tuple(self.coords[key]))
            else:
                self.phone._touch.press(tuple(self.coords[c]),None, self.defaultDelay)
                self.phone._run('Press to coordinates: %s,%s' % tuple(self.coords[c]))

            if delayBetweenPresses:
                self.phone.delay(delayBetweenPresses, False)

            if self.mode != 'ABC':
                caps = False

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
        #    raise Exception('Blackbox VirtualKeyboard: error with setting file, check that orientation %s / mode %s has keys "h_span", "v_span" and "rows"' % (orientation, mode))
        if not self.vkbSettings[orientation].has_key(mode):
            raise Exception('Mapped VirtualKeyboard: mode %s not defined for orientation %s"' % (mode, orientation))
        layout = self.vkbSettings[orientation][mode]

        if layout.has_key('base') and layout['base'] != "":
            if not self.vkbSettings[orientation].has_key(layout['base']):
                raise Exception('Mapped VirtualKeyboard: %s orienation mode %s has unknown base layout %s"' % (orientation, mode, layout['base']))
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
                        raise Exception('Mapped VirtualKeyboard: %s is defined twice' % key)
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
            raise Exception('Mapped VirtualKeyboard: No transition defined for orientation %s mode %s -> %s' % (orientation, self.mode, new_mode))
        transitions = self.vkbSettings[orientation][self.mode]['transitions']

        found = False
        for value in transitions.values():
            if new_mode in value:
                found = True
                break

        if not found:
            raise Exception('No vkb transition info defined from %s to %s. Defined: %r' % (self.mode, new_mode, transitions))

        for k, v in transitions.iteritems():
            if new_mode in v:
                key = k

        debug.brf('press key %s to get to mode %s' % (key, new_mode))
        self.phone._touch.press(tuple(self.coords[key]), None, self.defaultDelay)
        self.phone._run('Press to coordinates: %s,%s' % tuple(self.coords[key]))
        self.mode = new_mode
        self._loadCoords()

    def clear(self, time=3, mode=None, orientation=None):
        """ press the backspace for defined amount of time """
        self._loadVkbSettings()
        self._loadCoords(orientation, mode)
        self.phone._touch.press(tuple(self.coords['backspace']), time*1000, self.defaultDelay)
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
            self.phone._touch.press(tuple(self.coords['backspace']),None, self.defaultDelay)
            self.phone._run('Press to coordinates: %s,%s' % tuple(self.coords['backspace']))


class NGDatePicker(object):
    """ Class for selecting date from date picker"""
    def __init__(self, phone):
        """Initialize test case instance for class."""
        self.phone = phone

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

        self.phone.uiState.getCurrentState(refresh=True)
        state = self.phone.uiState.currentStateFull

        picker_x_coords = []

        for node in state.findall('//label'):
            try: # process all texts which can be translated to integers
                date_number = int(node.getAttribute('text'))
                if date_number > 0:
                    (x,y,w,h) = [int(p) for p in node.getAttribute('coords').split(",")]
                    nodes = state.findall('//label[starts-with(@coords,"%s")]' % x)
                    if len(nodes) >= 3:  # assume that if there's more than 3 labels (int-castable) on same coords, it's datepicker
                        if x not in picker_x_coords:
                            picker_x_coords.append(x)
            except:
                continue

        if len(picker_x_coords) != 3:
            self.phone.fail("Date picker should have 3 selectors, found %s possible coordinates for date picker. Is date picker visible on screen?" % len(picker_x_coords))

        select_date = [yyyy, mm, dd]  # use time picker in this order
        # cannot read the max / min year from yapas, using fixed values
        max_values = [2050, 12, 29] # corresponding maximum values to be used
        min_values = [1900, 1, 1] # corresponding maximum values to be used

        # Check the phone date format and choose order of the
        dateformat = self.phone.sx('(send config-manager get-setting "./yapas/display/dateformat")')
        picker_x_coords.sort()

        # TODO: move 'short-date' to rigth place when date format works on EVO sw
        if dateformat in ['very-short-date-with-day', 'short-date','MM.DD.YYYY', 'MM/DD/YYYY', 'MM-DD-YYYY']:  # if date format has been month-first, then sort the picker coord list so that it will be used in yyyy-mm-dd order
            picker_x_coords = picker_x_coords[2], picker_x_coords[0], picker_x_coords[1]
        elif dateformat in ['YYYY/MM/DD','YYYY.MM.DD', 'YYYY-MM-DD']:
            pass
        else: # pickers in dd/mm/yyyy, reversing to match with select_date
            picker_x_coords.sort(reverse=True)


        i = 0
        success = False

        for picker_x_coord in picker_x_coords:
            # x marks d, m or y
            x = select_date[i]
            max = max_values[i]
            min = min_values[i]
            i += 1

            nodes = state.findall("//label[starts-with(@coords,'%s') and number(@text)=number(@text)]" % picker_x_coord)
            debug.out('nodes for center node detect: %s (all on x coordinate %s)' % (len(nodes), picker_x_coord))
            
            # index number of center node. (e.g. if 5 values visible, center index is 2, if 3 values visible, center index is 1..)
            center_node = (len(nodes) - 1) / 2
            debug.out('center_node index %s' % str(center_node))

            # calculate the step size in pixels on y-axis, use distance between two selections as the distance unit. constant to adjust against the sensitivity
            if max > 31: # when using year picker, use different constant to adjust the picker sensitivity
                constant = 1.5
            else:
                constant = 2.5

            step = int((int(nodes[center_node+1].getAttribute('coords').split(",")[1]) - int(nodes[center_node].getAttribute('coords').split(",")[1]) ) / constant)
            last_drag_direction = None # remember where the direction was dragged last time
            last_selected = None # last_selected value to save the current selected date value. If picker does not move, step size needs to be increased

            for count in range(attemps):

                #a = datetime.now()

                nodes = state.findall('//label[starts-with(@coords,"%s") and number(@text)=number(@text)]' % picker_x_coord)

                # currently selected d, m or y
                current_sel_center = int(nodes[center_node].getAttribute('coords').split(",")[0]) + int(nodes[center_node].getAttribute('coords').split(",")[2]) / 2, \
                                     int(nodes[center_node].getAttribute('coords').split(",")[1]) + int(nodes[center_node].getAttribute('coords').split(",")[3]) / 2
                current_sel = int(nodes[center_node].getAttribute('text'))
                debug.out('current selection %s' % str(current_sel))

                # hack: check if current value is smaller or bigger than max values, change them if seen (year column only (i=1)
                if i == 1:
                    if last_selected and last_drag_direction == 'up': # if picker was scrolled up, it might be possible that it went to minimum value. change min
                        if last_selected > current_sel:
                            debug.out("Picker went around. Changed min value from %s to %s" % (min, current_sel))
                            min = current_sel
                    elif last_selected and last_drag_direction == 'down': # if picker was scrolled up, it might be possible that it went to maximum value. change max
                        if last_selected < current_sel:
                            debug.out("Picker went around. Changed max value from %s to %s" % (max, current_sel))
                            max = current_sel
                    if current_sel > max:
                        debug.out("Selection is bigger than maximum value. Changed max value from %s to %s" % (max, current_sel))
                        max = current_sel
                    elif current_sel < min:
                        debug.out("Selection is smaller than minimum value. Changed min value from %s to %s" % (min, current_sel))
                        min = current_sel

                # if selected date did not change after, change step size
                if last_selected == current_sel:
                        step += 2
                        last_selected = None

                if current_sel > x:  # if current selection is bigger than wanted, count distances
                    distance_up = int( current_sel - x )    # distance_up is counted by numbers above current number
                    distance_down = int( (max - current_sel + 1) + (x - min) )   # distance to go around the picker: distance to maximum value + distance from minimum to wanted
                    debug.out("selection bigger than wanted value. current date: %s - getting to %d (max %s, min %s) distance_up: %s, distance_down: %s" % (current_sel, x, max, min, distance_up, distance_down ) )

                elif current_sel < x:
                    distance_up = int( current_sel - min + 1 + max - x) # distance to go around the picker: distance to minimum value + maximum value - wanted
                    distance_down = int( x - current_sel )
                    debug.out("selection smaller than wanted value. current date: %s - getting to %d (max %s, min %s) distance_up: %s, distance_down: %s" % (current_sel, x, max, min, distance_up, distance_down ) )

                else:
                    debug.brf("Select date: selected %s" % x)
                    success = True
                    break # if already selected

                if distance_up < distance_down:  # if scrolling up (dragging down)
                    if math.fabs(distance_up) > 3: multiplier = 3
                    else: multiplier = 1

                    self.phone._touch.drawLine(  current_sel_center, \
                                        (current_sel_center[0], current_sel_center[1] + int(step * multiplier)), 30)
                    self.phone._run('Swiping down time picker', testStepReporting = False)
                    debug.out('swiped down %s -> %s (date picker steps :%s)' % (current_sel_center, (current_sel_center[0], current_sel_center[1] + step), multiplier))
                    last_drag_direction='down'
                else: # if scrolling down (dragging up)
                    if math.fabs(distance_down) > 3: multiplier = 3
                    else: multiplier = 1
                    #elif distance_down == 0: multiplier = 1
                    #else: multiplier = distance_down
                    self.phone._touch.drawLine(  current_sel_center, \
                                        (current_sel_center[0], current_sel_center[1] - int(step * multiplier)), 30)
                    self.phone._run('Swiping up time picker', testStepReporting = False)
                    debug.out('swiped up %s -> %s (date picker steps :%s)' % (current_sel_center, (current_sel_center[0], current_sel_center[1] - step),multiplier))
                    last_drag_direction='up'

                self.phone.uiState.getCurrentState(refresh=True)
                state = self.phone.uiState.currentStateFull
                last_selected = current_sel

                #b = datetime.now()
                #debug.brf("time delta: %s" % (b-a))

            assert success == True, "Failed to select %s from picker on x-coordinate %s" % (x, picker_x_coord)
            success = False

        self.phone.comment("Selected date %s/%s/%s (yyyy/mm/dd)" % (yyyy,mm,dd))


class NGTimePicker(object):
    """ Class for selecting time from time picker"""
    def __init__(self, phone):
        """Initialize test case instance for class."""
        self.phone = phone

    def __call__(self, hours=None, minutes=None, ampm=None ):
        """ Executes timepicker functionality
            Supports setting 24h and 12h modes. If minute or hour cannot be set, will fail the case.

        Parameters:
            hours(int)      :   Hour to be selected
            minutes(int)    :   Minute to be selected
            ampm(string)    :   Optional. String "AM" or "PM". If given, then hours need to be between 1 and 12, else between 0 and 23.
        """
        if ampm != None:
            assert hours >= 1 and hours <= 12, "AM/PM time selection, but given hours are not between 1 and 12"
            # if ampm given as logical text, do translation
            if self.phone.isLogicalText(ampm):
                ampm = self.phone.getTranslation(ampm)
            else: # try getting AM/PM translated
                if ampm == "AM":
                    translated = self.phone.getTranslation('n4PLb8v5_KE2WCIh0eKo7Cw')
                    if translated != None:
                        ampm = translated
                elif ampm == "PM":
                    translated = self.phone.getTranslation('nQOWjTH6UiUCkRejTnWvQPg')
                    if translated != None:
                        ampm = translated

        elif hours != None:
            assert hours >= 0 and hours <= 23, "Hours are not between 0 and 23"

        if minutes != None:
            assert int(minutes) >= 0 and int(minutes) <=59, "Minutes are not between 0 and 59"

        # angle interval in degrees, affects how many points are calculated to circle.
        hour_interval = 15
        minute_interval = 15

        msg = ""
        c = min = hour = None
        minutes_set = False

        for i in range(4):  # try getting time picker icons 4 times
            # uiChanged --> True so that dump will be taken by force
            # FIXME: Use event approach instead
            self.phone.uiState.setUIChanged(True)

            if c == None:
                status, c = self.phone.uiState.isItemVisible('widgets/hour-background')[:2]

            if not status == self.phone.uiState.VISIBLE:
                msg = "timepicker center not visible"
                continue

            if minutes != None:
                status, min = self.phone.uiState.isItemVisible('widgets/minute-pointer', refresh=False)[:2]

                # check whether minutes are currently wanted ones
                item = self.phone.uiState.searchItem('widgets/minute-pointer', touchType=False, contentType='image', refresh=False)
                if item:
                    x,y,w,h = [int(p) for p in item.getAttribute('coords').split(",")]
                    t = self.phone.tryExpect("%02d" % minutes,refresh=False,timeout=0, fromArea=(x-2,y-2,x+w+2,y+h+2), doNotReport = True)
                    if len(t) > 0:  # minutes are already set
                        minutes_set = True

                    if not status == self.phone.uiState.VISIBLE:
                        msg = "minute picker not visible"
                        continue
                else:
                    msg = "minute picker not visible"
                    continue

            if hours != None:
                status, hour = self.phone.uiState.isItemVisible('widgets/hour-pointer', refresh=False)[:2]

                if not status == self.phone.uiState.VISIBLE:
                    msg = "hour picker not visible"
                    continue

            break

        if not msg == "":
            self.phone.fail(msg)

        success = False

        if minutes != None and not minutes_set :
            attemps = 8
            for i in range(attemps): # try to get to correct few times
                if i % 2 != 0:
                    debug.out('adjust')
                    angle_adjust = 0.07 # alter the angle radians a bit every second attemp (has effect on minutes 17, 37 etc.. )
                else:
                    angle_adjust = 0
                
                steps = self._getCirclePoints(c,min,self._getMinutesAngle(minutes)+angle_adjust,minute_interval)
                self.phone._touch.drawShape( steps )

                # uiChanged --> True so that dump will be taken by force
                # FIXME: Use event approach instead
                self.phone.uiState.setUIChanged(True)

                test = []
                test.append('%02d' % ((minutes-1+60) % 60))
                test.append('%02d' % (minutes))
                test.append('%02d' % ((minutes+1) % 60))

                # do exact checking with area that time has been set correctly
                item = self.phone.uiState.searchItem('widgets/minute-pointer', touchType=False, contentType='image')

                if not item:
                    debug.vrb("Could not find minute pointer..")
                    continue

                x,y,w,h = [int(p) for p in item.getAttribute('coords').split(",")]
                t = self.phone.tryExpect(test,refresh=False,timeout=0, fromArea=(x-2,y-2,w+2,h+2), doNotReport = True)

                if len(t) > 0:
                    if 1 in t: # tryExpect returns 0,1,2 - where 1 means that exact minutes was found
                        success = True
                        break

                # minute picker was not on correct position
                rand = random.randint(7,15)   # move time picker a random amount anticlockwise from current minutes
                if minutes > rand:
                    temp = minutes - rand
                else:
                    temp = (60-rand) + minutes

                if i == attemps-1: # if this was the last attemp, break the loop
                    break

                debug.vrb("Could not set minutes to %s, trying time setting again.. anticlockwise to %s and try again" % (minutes, temp))

                status, min = self.phone.uiState.isItemVisible('widgets/minute-pointer')[:2]
                steps = self._getCirclePoints(c,min,self._getMinutesAngle(temp),minute_interval)
                self.phone._touch.drawShape( steps )

                # uiChanged --> True so that dump will be taken by force
                # FIXME: Use event approach instead
                self.phone.uiState.setUIChanged(True)

                status, min = self.phone.uiState.isItemVisible('widgets/minute-pointer')[:2]

            if not success:
                self.phone.fail("Could not get minutes set")
            success = False

        if hours != None:
            attemps = 5
            for i in range(attemps): # try to get to correct time few times
                # add 2 additional degrees to wanted angle, usually exact hour is not in exact angle
                steps = self._getCirclePoints(c,hour,(self._getHoursAngle(hours)+math.radians(2)),6)
                self.phone._touch.drawShape( steps )

                # uiChanged --> True so that dump will be taken by force
                # FIXME: Use event approach instead
                self.phone.uiState.setUIChanged(True)

                test = []
                if ampm == None:
                    test.append('%02d' % ((hours-1+24) % 24))
                    test.append('%02d' % (hours))
                    test.append('%02d' % ((hours+1) % 24))
                else:
                    test.append('%02d' % ((hours-1+12) % 12))
                    test.append('%02d' % (hours))
                    test.append('%02d' % ((hours+1) % 12))

                if ampm == None:
                    temp_h = (hours + 12) % 24  # test also whether hour picker needs to be turned 360 degrees to get correct time
                    test.append('%02d' % (temp_h-1))
                    test.append('%02d' % (temp_h))
                    test.append('%02d' % (temp_h+1))
                    test_am = None

                # do exact checking with area that time has been set correctly
                item = self.phone.uiState.searchItem('widgets/hour-pointer', touchType=False, contentType='image')
                if not item:
                    debug.vrb("Could not find hour pointer..")
                    continue

                x,y,w,h = [int(p) for p in item.getAttribute('coords').split(",")]
                t = self.phone.tryExpect(test,refresh=False, timeout=0, fromArea=(x-2,y-2,w+2,h+2), doNotReport = True)
                if ampm != None:
                    test_am = self.phone.tryExpect(ampm, timeout=0, refresh=False, doNotReport = True)

                if len(t) > 0:
                    if 4 in t or (ampm != None and test_am == []):  # only when ampm is not enabled
                        # picker needs to be turned 360 degrees over
                        steps = self._getCirclePoints(c, steps[-1], self._getHoursAngle((hours + 4) % 24), hour_interval)
                        self.phone._touch.drawShape( steps )

                        # uiChanged --> True so that dump will be taken by force
                        # FIXME: Use event approach instead
                        self.phone.uiState.setUIChanged(True)

                        steps = self._getCirclePoints(c, steps[-1], self._getHoursAngle((hours + 8) % 24), hour_interval)
                        self.phone._touch.drawShape( steps )

                        # uiChanged --> True so that dump will be taken by force
                        # FIXME: Use event approach instead
                        self.phone.uiState.setUIChanged(True)

                        steps = self._getCirclePoints(c, steps[-1], (self._getHoursAngle(hours)+math.radians(2)), hour_interval)
                        self.phone._touch.drawShape( steps )

                        # uiChanged --> True so that dump will be taken by force
                        # FIXME: Use event approach instead
                        self.phone.uiState.setUIChanged(True)

                        item = self.phone.uiState.searchItem('widgets/hour-pointer', touchType=False, contentType='image')
                        if item:
                            x,y,w,h = [int(p) for p in item.getAttribute('coords').split(",")]
                            t = self.phone.tryExpect(test,refresh=False, timeout=0, fromArea=(x-2,y-2,w+2,h+2), doNotReport = True)

                    if 1 in t: # tryExpect returns 0,1,2 - where 1 means that exact hour was found
                        success = True
                        break

                # hour picker hit the wrong time, try again
                rand = random.randint(2,5)   # move time picker a random amount anticlockwise from current hour
                if hours > rand:
                    temp = hours - rand
                else:
                    temp = 12 - rand + hours

                if i == attemps-1: # this was final attemp, break the loop
                    break

                debug.vrb("Could not set hour to %s, trying time setting again.. anticlockwise to %s and try again" % (hours, temp))

                status, hour = self.phone.uiState.isItemVisible('widgets/hour-pointer')[:2]
                steps = self._getCirclePoints(c,hour,self._getHoursAngle(temp),hour_interval)
                self.phone._touch.drawShape( steps )

                # uiChanged --> True so that dump will be taken by force
                # FIXME: Use event approach instead
                self.phone.uiState.setUIChanged(True)

                status, hour = self.phone.uiState.isItemVisible('widgets/hour-pointer')[:2]

            if not success:
                self.phone.fail("Could not get hours set")
            success = False

        if hours != None:
            msg = "Selected time %02d:" % hours
        else:
            msg = "Selected time xx:"

        if minutes != None:
            msg += "%02d" % minutes
        else:
            msg += "xx"

        if ampm != None:
            msg += " %s" % ampm

        self.phone.comment(msg)

    def _getMinutesAngle(self, minutes):
        """ Returns angle to given minute value. xx:15 minutes treated as 0 angle
        """
        if minutes > 45:
            angle = - math.radians((60-minutes) * 6 + 90)
        else:
            angle = math.radians(minutes * 6 - 90)
        return angle

    def _getHoursAngle(self, hours):
        """ Returns angle to given minute value. 03:xx treated as 0 angle
        """
        if hours > 9:
            angle = - math.radians((12-hours) * 30 + 90)
        else:
            angle = math.radians(hours * 30 - 90)
        return angle

    def _getCirclePoints(self, center, from_point, to_angle, interval):
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
        x = int(round(radius*math.cos(to_angle) + center[0]))
        y = int(round(radius*math.sin(to_angle) + center[1]))
        points.append( (x,y) )

        # debug.brf("points %s" % points)
        return points

