# -*- coding: ascii -*-
# ============================================================================
#
#
# %full_filespec:   teststep_analyzer.py
#                   ----------------------------------------------------------
#                   Granite Python Module
#
#
# Copyright (c)     Nokia. All rights reserved.
#
# ----------------------------------------------------------------------------
"""UI Test Step Analyzer."""

# ============================================================================
# Module Setup

from copy import copy
import re, os, shutil

import core
from core import scripting, phone
from utils.nodeutils import NodeUtils
from utils import include

isi = include.Include('granite_p_isi.h')

# make global statusFlags dictionary
# NOTE: If new values are added, remember to change this!
statusFlags = {isi.GRN_STATUS_data: 'content', isi.GRN_STATUS_x: 'x',
               isi.GRN_STATUS_y: 'y', isi.GRN_STATUS_width: 'width',
               isi.GRN_STATUS_height: 'height',
               isi.GRN_STATUS_highlighted: 'highlighted',
               isi.GRN_STATUS_font: 'font',
               isi.GRN_STATUS_color: 'color',
               isi.GRN_STATUS_truncated: 'truncated',
               isi.GRN_STATUS_screen: 'screen',
               isi.GRN_STATUS_dimmed: 'dimmed',
               isi.GRN_STATUS_background: 'background'}

attributeList = ['content', 'screen', 'highlighted', 'dimmed', 'truncated',
                 'font', 'fg', 'bg', 'valid', 'background']

error_texts = {
    1: lambda name, area: "Expected %s not %s, please see actual " \
                          "display items." % \
                          (name, area and 'in zonearea' or 'on display'),
    2: lambda name, area: "Framework can't resolve which %s is " \
                          "right %s." % \
                          (name, area and 'in zonearea' or 'on display'),
    3: lambda area:       "%s not empty." % \
                          (area and 'Zonearea' or 'Display'),
    4: lambda name, area: "No %ss %s." % \
                          (name, area and 'in zonearea' or 'on display'),
    }

comment_texts = {
    1: lambda name, area: "Expected %s not valid %s." % \
                          (name, area and 'in zonearea' or 'on display'),
    2: lambda name, area: "No %ss %s." % \
                          (name, area and 'in zonearea' or 'on display')
    }

# ============================================================================
class UITestStepAnalyzer:
    """Class for analyzing failed test step.

        Parses failed display items from testRespRoot.
    """
    def __init__(self):
        self.zonearea = None
        self.respFailedExpect = []
        self.unknownItemList, self.usedUnknownIdxList = [], []
        self.captureBitmaps = []
        self.reqPassedItems, self.reqFailedItems, self.respFailedItems = [], [], []
        self.parsedSummary = NodeUtils('summary', makeNewNode = True)

    def parseResp(self, testRespRoot, testReqRoot, spXmlNode):
        """Parses wbxml response data. Called from srv_granite.py.

            Parameters

            testRespRoot        test response from Granite server (NodeUtils instance)
            testReqRoot         test request which was executed (NodeUtils instance)
            spXmlNode           parsed SP XML node (NodeUtils instance)
        """
        displayWidth, displayHeight = None, None
        
        # get visible items from SP xml node
        if spXmlNode:
            # image-widget nodes have images
            animations =  [animation for animation in spXmlNode.findall('image-widget') if animation['image']]
            
            # label and textinput nodes have texts
            texts = [text for text in spXmlNode.findall('label') if text.getAttribute('text')]
            texts += [text for text in spXmlNode.findall('textinput') if text.getAttribute('text')]
                        
            # get display width and heigth       
            displayWidth = core.FW_conf['remote_connection'].uiState.getScreenWidth()
            displayHeight = core.FW_conf['remote_connection'].uiState.getScreenHeight()
        else:
            animations, texts = [], []
                    
        displays = testReqRoot.findall('//display')
        captures = testReqRoot.findall('//capture')
        #sxTags = testReqRoot.findall('//sx')

        # Copy captured images if needed
        self.__copyCaptures(captures)

        respBitmaps = testRespRoot.findall('//bitmap')
        
        respCapture = None        
        for cap in testRespRoot.findall('//capture'):
            if cap.getAttribute('id'):
                respCapture = cap
                break
                        
        testRespRoot.setAttribute('id',testReqRoot.getAttribute('id'))
        testRespRoot.setAttribute('name',testReqRoot.getAttribute('name'))
        testRespRoot.setAttribute('stepId',testReqRoot.getAttribute('stepId'))

        if len(displays):
            expectNode = NodeUtils('expect',True)
            expectNode.setAttribute('id',testReqRoot.find('//expect').getAttribute('id'))
        else:
            expectNode = None

        for display in captures + displays:
            if not respCapture:
                screenItems = NodeUtils(display.getName(), True)                
                screenItems.setAttribute('id',display.getAttribute('id'))
                screenItems.setAttribute('name',display.getAttribute('name'))

            for animation in animations:                    
                animNode = NodeUtils('animation',True)
                #animNode.setAttribute('name',animation['image'])
                # take only image name, leave path out
                animationName = os.path.split(animation['image'])[-1]
                
                # add logical id of image to image name
                # NOTE: When taking capture for capture tool, this can't be done
                if not 'phone_display_capture' in testReqRoot.getAttribute('name'):
                    try:
                        logicalAnimName = phone.getLogicalImageName(animationName)
                        if logicalAnimName:
                            logicalAnimName = ' (%s)' % (len(logicalAnimName) == 1 and logicalAnimName[0] or logicalAnimName)
                        else:
                            logicalAnimName = ""
                    except:
                        logicalAnimName = ""
                else:
                    logicalAnimName = ""

                animNode.setAttribute('name', '%s%s' % (animationName, logicalAnimName))
                                
                try:
                    x, y, width, height = animation['coords'].split(",")
                                        
                    # skip items outside of the screen (up, left)
                    if (int(x) < 0 and (int(width) - abs(int(x))) <= 0) or \
                       (int(y) < 0 and (int(height) - abs(int(y))) <= 0):
                        continue

                    # skip items outside of the screen (down, right)
                    if (displayWidth and int(x) > int(displayWidth)) or \
                       (displayHeight and int(y) > int(displayHeight)):
                        continue
                except:
                    x, y, width, height = 0, 0, 0, 0
                    
                animNode.setAttribute('x', x)
                animNode.setAttribute('y', y)
                animNode.setAttribute('width', width)
                animNode.setAttribute('height', height)

                if respCapture:
                    respCapture.append(animNode)
                else:
                    screenItems.append(animNode)

            for text in texts:                    
                textNode = NodeUtils('text',True)
                textNode['text'] = text.getAttribute('text')
                
                try:
                    x, y, width, height = text['coords'].split(",")
                    
                    # skip items outside of the screen (up, left)
                    if (int(x) < 0 and (int(width) - abs(int(x))) <= 0) or \
                       (int(y) < 0 and (int(height) - abs(int(y))) <= 0):
                        continue

                    # skip items outside of the screen (down, right)
                    if (displayWidth and int(x) > int(displayWidth)) or \
                       (displayHeight and int(y) > int(displayHeight)):
                        continue
                except:
                    x, y, width, height = 0, 0, 0, 0
                    
                textNode.setAttribute('x', x)
                textNode.setAttribute('y', y)
                textNode.setAttribute('width', width)
                textNode.setAttribute('height', height)

                if respCapture:
                    respCapture.append(textNode)
                else:
                    screenItems.append(textNode)
                
            if display.getName() == 'capture' and not respCapture:
                for respBitmap in respBitmaps:
                    screenItems.append(respBitmap)
                    
                testRespRoot.append(screenItems)
            elif expectNode:
                if respCapture:
                    expectNode.append(respCapture)
                else:
                    expectNode.append(screenItems)
                
        if len(displays) and expectNode:
            testRespRoot.append(expectNode)

        """
        <text background="no" bg="0" dimmed="no" fg="16777215" font="PIXEL_14-REGULAR" height="16" highlighted="no" id="unknown" screen="1" truncated="no" width="36" x="204" y="1">16:09</text>
        <label name="" coords="0,0,0,18" alignments="start,center" visible="true" has-local-focus="false" has-global-focus="false" text="" fore-color="1.0,1.0,1.0,1.0" font-style="normal" font-weight="regular" font-family="sans" text-size="medium" text-align="start" />

        <animation animation_id="2147485162" background="no" dimmed="no" height="56" highlighted="no" id="unknown" name="qgn_menu_grid_organizer" screen="1" width="56" x="18" y="43"/>
        <image-widget name="" coords="7,0,23,8" alignments="start,start" visible="true" has-local-focus="false" has-global-focus="false" image="file:///customer-resources/themes/viking/Common/apps/idle/unselected_dot.png" image-size="23,8" />
        """
        
##        for oCaptureItem in animations:
##            self.__setAnimationName(oCaptureItem)
##
##
##        self.parsedSummary.append(respDisplay.clone())

        for display in testReqRoot.findall('//display'):
            elementNotFound = False
            for element in display.getChildNodes():
                if element.getName()=='text':
                    if (element.getAttribute('valid')!='no' and element['text'] not in [text['text'] for text in texts] ) or \
                     (element.getAttribute('valid')=='no' and element['text'] in [text['text'] for text in texts]):
                        #debug.out('**************')
                        #debug.out(element['text'])
                        #debug.out('**************')
                        elementNotFound = True
                        break
                else:
                    if (element.getAttribute('valid')!='no' and element.getAttribute('id') not in [anim.getAttribute('image') for anim in animations]) or \
                     (element.getAttribute('valid')=='no' and element.getAttribute('id') in [anim.getAttribute('image') for anim in animations]):
                        elementNotFound = True
                        break
            if elementNotFound:
                #testRespRoot.remove(testRespRoot.find('//display[@name="%s"]'%display.getAttribute('name')))
                nodeToBeRemoved = testRespRoot.find('//display[@name="%s"]'%display.getAttribute('name'))
                #debug.out('*****nodeToBeRemoved******')
                #debug.out(nodeToBeRemoved.toprettyxml())
                #debug.out('*****nodeToBeRemoved******')
                nodeToBeRemoved.parent().remove(nodeToBeRemoved)
            else:
                respDisplay = testRespRoot.find('//display[@name="%s"]'%display.getAttribute('name'))
                for child in [child for child in respDisplay.getChildNodes()]:
                    #debug.out('**************remove child from respDisplay****************')
                    #debug.out(child.toprettyxml())
                    #debug.out('**************remove child from respDisplay****************')
                    respDisplay.remove(child)

        #debug.out('*********testRespRoot***********')
        #debug.out(testRespRoot.toprettyxml())
        #debug.out('*********testRespRoot***********')

        # testReqRoot, document element created in uitestcase, comes here via srv_granite.py.
        self.parsedSummary['id'] = testReqRoot['id']
        self.parsedSummary['name'] = testReqRoot['name']

        # It includes also captures
        respDisplays = testRespRoot.findall('//display')
        captures = testRespRoot.findall('//capture')
        respDisplays.extend(captures)

        # Organize tags to ascending order by id value
        #respDisplays = self.__organiseTagList(respDisplays) # No need for this with evo

##        debug.out('*************************')
##        debug.out(testReqRoot.toprettyxml())
##        debug.out('*************************')

        # Parse response teststep.
        for respDisplay in respDisplays:
            if respDisplay.getName() == 'display':

                if 'id' in respDisplay.getAttributes():
                    respDisplayID = respDisplay['id']
                    reqDisplay = testReqRoot.lookup('id', respDisplayID, 1)
                    respDisplay['name'] = reqDisplay['name']

                    if respDisplay.getChildNodes():
                        # check if respDisplay child has a result attribute
                        # if it does clone respDisplay directly to self.respFailedExpect
                        for oChild in respDisplay.getChildNodes():
                            if 'result' in oChild.getAttributes():
                                # Clone respDisplay to self.respFailedExpect
                                # Only 1 expect can be failed.
                                if not self.respFailedExpect:
                                    self.respFailedExpect = NodeUtils('expect', makeNewNode = True)
                                    self.respFailedExpect['id'] = respDisplay.parent()['id']
                                self.respFailedExpect.append(respDisplay.clone())
                                break
                            elif 'training' in oChild.getAttributes():
                                self.parsedSummary.append(respDisplay.parent().clone())
                                break
                    else:
                        # Now we are 100% sure that this step has succeeded.
                        # Note! Only 1 display in expect == ok.
                        # Append displays parent which is the expect tag.
                        # (includes display)
                        #debug.out(respDisplay.toprettyxml())
                        self.parsedSummary.append(respDisplay.parent().clone())
                else:
                    # Unknown display
                    # A display with all items is always returned when an error has occurred.
                    # These items are put to unknownItem list.
                    # Direct DOM commands!
                    self.unknownItemList = respDisplay.findall('text')
                    self.unknownItemList.extend(respDisplay.findall('animation'))
                    self.captureBitmaps = respDisplay.findall('bitmap')

            elif respDisplay.getName() == 'capture':
                # Added capture
#                captureID = respDisplay['id']
#                reqCapture = testReqRoot.lookup('id', captureID, 1)
#                respDisplay['name'] = reqCapture['name']

                for oCaptureItem in respDisplay.getChildNodes():
                    self.__setAnimationName(oCaptureItem)

                self.parsedSummary.append(respDisplay.clone())
                
        # parse failed items
        if self.respFailedExpect:
            self.parseFailItems(testReqRoot)

    def passedDisplaysAndCaptures(self):
        """Return display names and captures of passed test step.

            Called from srv_granite.py.
        """
        items = {}
        displays = self.parsedSummary.findall('//display')
        captures = self.parsedSummary.findall('//capture')

        for display in displays:
            name = display['name']

            if not name in items:
                items[name] = 0
            else:
                items[name] += 1

        for capture in captures:
            name, valueList = self.__getCaptures(capture)
            items[name] = valueList

        return items

    def parseFailItems(self, testReqRoot):
        """Parser only for an error case.
        """
        # Go through all error displays.
        for oRespFailedDisplay in self.respFailedExpect.getChildNodes():
            self.usedUnknownIdxList = []

            # parse result attribute(status flags)
            for oFailedItem in oRespFailedDisplay.getChildNodes():
                self.__parseStatusFlag(oFailedItem, testReqRoot)

            # Get passed, failed teststep and error (test response)
            # items from display.
            self.reqPassedItems, self.reqFailedItems, \
                self.respFailedItems = self.__getItems(testReqRoot, oRespFailedDisplay)

            # Parse passed teststep display items.
            for reqPassedItem in self.reqPassedItems:
                if reqPassedItem.getName() in ('text', 'animation'):
                    result = self.__handleSameElement(reqPassedItem, False)
                    self.__appendPassed(result, reqPassedItem, oRespFailedDisplay)
                elif reqPassedItem.getName() == 'bitmap':
                    pass

            # Parse failed teststep display items.
            for reqFailedItem in self.reqFailedItems:
                if reqFailedItem.getName() in ('text', 'animation'):
                    result = self.__handleSameElement(reqFailedItem, True)
                    self.__appendFailed(result, reqFailedItem, oRespFailedDisplay)
                elif reqFailedItem.getName() == 'bitmap':
                    self.__appendFailedBitmap(reqFailedItem, oRespFailedDisplay)

            otherItems = self.__appendUnknown(oRespFailedDisplay)
            if otherItems:
                self.__appendOther(otherItems, oRespFailedDisplay)

        # Only 1 expect can be failed.
        self.parsedSummary.append(self.respFailedExpect.clone())

    def __getCaptures(self, captureTag):
        """Return capture name and all items.
        """
        name = captureTag['name']
        values = captureTag.getChildNodes()
        return name, values

    def __setAnimationName(self, oDisplayItem):
        """Get/set animation name attribute from the given tag.
        """
        if oDisplayItem.getName() == 'animation':
            animName = oDisplayItem['name']

            if animName:
                oDisplayItem['name'] = animName
            else:
                oDisplayItem['name'] = 'unknown'

    def __parseStatusFlag(self, errorItem, testStep):
        """Extract failed attributes from result attribute value.
            replace result attribute with failed attribute names.
            Note: Modifies errorItem, which is a DOM object.

            FIXME: More space can be made to result attribute by
                   removing x, y, w and h.
        """
        status = int(errorItem['result'])
        statusFlagsOn = [flag for flag in statusFlags.keys() if flag & status]

        # Check if result has all flag attributes on (valid = 'no').
        flagStates = map(lambda key: bool(key & status), statusFlags.keys())
        allOn = reduce(lambda x, y: x & y, flagStates)

        # Check if testcase item has valid attribute.
        errorItemID = errorItem['id']
        tcItem = testStep.lookup('id', errorItemID, 1)
        tcValid = 'valid' in tcItem.getAttributes()

        if allOn and tcValid:
            errorItem['errorItems'] = 'valid'
        else:
            attrNames = ','.join(map(lambda flag: statusFlags.get(flag), statusFlagsOn))
            errorItem['errorItems'] = attrNames

        errorItem.removeAttribute('result')

    def __organiseTagList(self, tagList):
        """Organize tags to ascending order by id value.
            Tags with unknown id area appended at the end of the list.
        """
        knownList = [oTag for oTag in tagList if 'id' in oTag.getAttributes()]
        unknownList = [oTag for oTag in tagList if not 'id' in oTag.getAttributes()]

        itemIds = map(lambda l: l['id'], knownList)
        tagDict = dict(zip(itemIds, knownList))
        itemIds.sort()

        # Organise items with ids.
        tagList = []

        for itemId in itemIds:
            tagList.append(tagDict.get(itemId))

        # Adding items without ids.
        tagList.extend(unknownList)

        return tagList

    def __getItems(self, testReqRoot, oRespFailedDisplay):
        """Get passed, failed teststep items and test response error items.

            Parameters

            testReqRoot         test request root
            oRespFailedDisplay  the list of failed items

            Returns passed items.
            FIXME: Change errorItems to responseItems
        """
        displayID = oRespFailedDisplay['id']

        # Get error(test response) display items.
        respFailedItems = oRespFailedDisplay.findall('text')
        respFailedItems.extend(oRespFailedDisplay.findall('animation'))
        respFailedItems.extend(oRespFailedDisplay.findall('bitmap'))
        respFailedItems = self.__organiseTagList(respFailedItems)

        # Get failed teststep display items.
        respFailedItemsIds = map(lambda l: l['id'], respFailedItems)
        reqFailedItems = map(lambda l: testReqRoot.lookup('id', l, 1),
                          respFailedItemsIds)

        # Get passed teststep display items.
        reqDisplay = testReqRoot.lookup('id', displayID, 1)

        reqPassedItems = reqDisplay.findall('text')
        reqPassedItems.extend(reqDisplay.findall('animation'))
        reqPassedItems.extend(reqDisplay.findall('bitmap'))
        reqPassedItems = [item for item in reqPassedItems \
                       if item['id'] not in respFailedItemsIds]

        return reqPassedItems, reqFailedItems, respFailedItems

    def __handleSameElement(self, reqItem, isFailed):
        """Find out which items from the unknown items list are inside
            expected zonearea in teststep item.
        """
        attrList = []
        sameZoneList = []
        zoneAttributes = ['x', 'y', 'width', 'height']

        tsX, tsY, tsWidth, tsHeight = \
        	map(lambda l: reqItem[l], zoneAttributes)

        self.zonearea = (tsX or tsY) and True or False

        # If width is given without x, width is item property.
        if not(tsX) and tsWidth:
            attrList.append('width')

        # If height is given without y, height is item property.
        if not(tsY) and tsHeight:
            attrList.append('height')

        for unknownItem in self.unknownItemList:
            ukX, ukY, ukWidth, ukHeight = \
            	map(lambda l: unknownItem[l], zoneAttributes)
            # Check which unknown items are in the same zonearea.
            if self.zonearea:
                if unknownItem.getName() == reqItem.getName():
                    if tsX and not(int(tsX) <= int(ukX)):
                        continue
                    if tsY and not(int(tsY) <= int(ukY)):
                        continue
                    if (tsX and tsWidth) and not(int(tsX) + int(tsWidth)) >= \
                                                (int(ukX) + int(ukWidth)):
                        continue
                    if (tsY and tsHeight) and not(int(tsY) + int(tsHeight)) >= \
                                                 (int(ukY) + int(ukHeight)):
                        continue
                    # Append item located in same zonearea.
                    sameZoneList.append(unknownItem)
            # Zonearea not defined in teststep display item.
            else:
                if unknownItem.getName() == reqItem.getName():
                    sameZoneList.append(unknownItem)

        if isFailed:
            result = self.__handleFailedItems(reqItem, sameZoneList, attrList)
        else:
            result = self.__handlePassedItems(reqItem, sameZoneList, attrList)

        return result

    def __handlePassedItems(self, reqItem, sameZoneList, attrList):
        """Determines which return value is right for the passed item.
            Special cases are checked before proceeding to the attribute
            checking.
        """
        attrList = copy(attributeList) + attrList
        nodeName = reqItem.getName()

        if reqItem['valid']:
            return comment_texts[1](nodeName, self.zonearea)
        elif nodeName == 'text' and \
             not reqItem['text']:
            return comment_texts[2](nodeName, self.zonearea)
        elif nodeName == 'animation' and \
             reqItem['animation_id'] == "0":
            return comment_texts[2](nodeName, self.zonearea)
        elif sameZoneList:
            # Check which unknown items have same attributes.
            sameContentList = self.__checkAttributes(reqItem,
                                                     sameZoneList,
                                                     attrList)
            if len(sameContentList) >= 1:
                # Return the first matching item.
                return self.unknownItemList.index(sameContentList[0])
            else:
                return "Unexpected error in parsing passed items."
        else:
            return "Unexpected error in parsing passed items."

    def __handleFailedItems(self, reqItem, sameZoneList, attrList):
        """Concludes which return value is right for the failed item.
            if items have been found from the same zonearea, attributes
            are compared.
        """
        oErrorItem = self.respFailedItems[self.reqFailedItems.index(reqItem)]
        attrList = self.__handleAttributeList(oErrorItem) + attrList
        nodeName = reqItem.getName()

        if nodeName == 'text' and \
           not reqItem['text']:
            return error_texts[3](self.zonearea)
        elif nodeName == 'animation' and \
             reqItem['animation_id'] == "0":
            return error_texts[3](self.zonearea)
        elif sameZoneList:
            # Check which unknown items have same attributes.
            sameContentList = self.__checkAttributes(reqItem,
                                                     sameZoneList,
                                                     attrList)
            if len(sameContentList) == 1:
                return self.unknownItemList.index(sameContentList[0])
            elif len(sameContentList) > 1:
                if nodeName == 'text':
                    return self.__levenshtein(sameContentList, reqItem)
                else:
                    return error_texts[2](nodeName, self.zonearea)
            else:
                return error_texts[1](nodeName, self.zonearea)
        else:
            return error_texts[4](nodeName, self.zonearea)

    def __levenshtein(self, sameContentList, reqItem):
        """ Levenshtein distance is a string metric which is one way to
            measure edit distance e.g. to determine how similar two strings are.
        """
        results = []
        t = reqItem['text']
        sameContentTexts = [sameContent['text'] for sameContent in sameContentList]

        for s in sameContentTexts:
            m, n = len(s), len(t)
            d = [range(n + 1)]
            d += [[i] for i in range(1, m + 1)]
            for i in range(0, m):
                for j in range(0, n):
                    cost = 1
                    if s[i] == t[j]: cost = 0
                    d[i + 1].append(min(d[i][j + 1] + 1, # deletion
                                    d[i + 1][j] + 1,     # insertion
                                    d[i][j] + cost))     # substitution

            error_metric = float(d[m][n]) / max(m, n)
            results.append(error_metric)

        # Value 0.0 correspond to a perfect match.
        # Value 1.0 correspond to complete mismatch where no characters
        # are in common.
        minResult = min(results)
        if minResult <= 0.5: # Strings are a close match.
            # Get index of string with most characters in common.
            minIdx = results.index(minResult)
            return self.unknownItemList.index(sameContentList[minIdx])
        else:
            return error_texts[2](reqItem.getName(), self.zonearea)

    def __checkAttributes(self, reqItem, sameZoneList, attrList):
        """Loops through item attributes to find the right match
            for the passed/failed teststep items from unknown items list.
        """
        sameContentList = copy(sameZoneList)

        if 'background' not in reqItem.getAttributes():
            reqItem['background'] = 'no'

        # Check which unknown items have same attribute values.
        for respUnknownItem in sameZoneList:
            for attrName in attrList:
                if attrName == 'content':
                    if reqItem.getName() == 'text':
                        result = self.__compareTextValues(\
                                                reqItem['text'],
                                                respUnknownItem['text'])
                        if not result:
                            sameContentList.remove(respUnknownItem)
                            break
                    elif reqItem.getName() == 'animation':
                        if reqItem['animation_id'] != \
                           respUnknownItem['animation_id']:
                            sameContentList.remove(respUnknownItem)
                            break
                elif attrName == 'font':
                    if 'font' in reqItem.getAttributes():
                        expectFont = reqItem['font']
                        unknownFont = respUnknownItem['font']

                        if self.__getFontValue(expectFont) != \
                           self.__getFontValue(unknownFont):
                            sameContentList.remove(respUnknownItem)
                            break
                elif attrName in ['width', 'height']:
                    if int(reqItem[attrName]) < int(respUnknownItem[attrName]):
                        sameContentList.remove(respUnknownItem)
                        break
                elif attrName in reqItem.getAttributes():
                    if reqItem[attrName] != respUnknownItem[attrName]:
                        sameContentList.remove(respUnknownItem)
                        break

        return sameContentList

    def __getFontValue(self, fontValue):
        fontName, fontType = fontValue.split('-')

        # FIXME: Uncomment these when font handling has been upgraded
        # NOTE: Currently server checks only font name and ignores font type.
        #       This is the reason.
##        fontName = getattr(font, 'FONT_NAME_' + fontName, None)
##        fontType = getattr(font, 'FONT_TYPE_' + fontType, None)
##        if fontName != None and fontType != None:
##            fontId = (fontName << 16) | fontType
##        else:
##            fontId = fontValue

        # FIXME: Remove this when font handling has been upgraded
        fontId = fontName

        return fontId

    def __checkDisplayUnknownItem(self):
        """Remove 'used' items from self.unknownItemList.
            Processing copy of self.unknownItemList, because there mighty
            be other displays which need the original unknown item list.
        """
        unknownItemList = copy(self.unknownItemList)
        # Get unique indexes
        usedIdx = [item for item in self.usedUnknownIdxList if item != None]
        usedIdx = dict(zip(usedIdx, usedIdx)).keys()

        for idx in usedIdx:
            oItem = self.unknownItemList[idx]
            unknownItemList.remove(oItem)

        return unknownItemList

    def __handleAttributeList(self, oErrorItem):
        """Removes failed attributes from the attribute list,
            which is looped through for finding the right match
            for the failed items from unknown items list.
        """
        attrList = copy(attributeList)

        if oErrorItem.getName() == 'bitmap':
            attrList = ['content']
        else:
            for attr in oErrorItem['errorItems'].split(','):
                if attr == 'color':
                    attrList.remove('fg')
                    attrList.remove('bg')
                elif attr in ['content', 'screen', 'highlighted','dimmed',
                              'truncated', 'font', 'valid', 'background']:
                    attrList.remove(attr)

        return attrList

    def __compareTextValues(self, teststepText, unknownText):
        """Compares text item contents(strings).
            Regular expression used for charatesrs with special meaning
            (wildcard characters).
        """
        reExp = re.compile(r'([\\\'"[^$.|+()])')
        # replace metacharacters
        reText = reExp.sub(r'\\\1', teststepText)
        # replace wildcards
        reText = reText.replace('*','.*').replace('?','.{1}')
        reExp = re.compile('^%s$' % reText)
        result = bool(reExp.match(unknownText))

        return result

    def __appendPassed(self, result, reqPassedItem, respFailedDisplay):
        """Creates summary tags for passed items.
            if result attribute is integer, only one match is found from
            unknown items list.
            if result is a string a comment attribute is added.
        """
        if isinstance(result, int):
            # Clone matching passed item from self.unknownItemList.
            oPassedItem = self.unknownItemList[result].clone()
            # Copying item id from teststep expect item.
            oPassedItem['id'] = reqPassedItem['id']
            # Set animation name attribute.
            self.__setAnimationName(oPassedItem)
            # Update used unknown indexes.
            self.usedUnknownIdxList.append(result)
        elif isinstance(result, (str, unicode)):
            oPassedItem = NodeUtils(reqPassedItem.getName(), makeNewNode = True)
            oPassedItem['id'] = reqPassedItem['id']
            oPassedItem['comment'] = result

        respFailedDisplay.append(oPassedItem)

    def __appendFailed(self, result, reqFailedItem, respFailedDisplay):
        """Creates summary tags for failed items.
            if result attribute is integer, only one match is found from
            unknown items list.
            if result is a string an error attribute is added.
        """
        oErrorItem = self.respFailedItems[self.reqFailedItems.index(reqFailedItem)]

        if isinstance(result, int):
            # Clone matching failed item from self.unknownItemList.
            oFailedItem = self.unknownItemList[result].clone()
            # Copy item id from teststep expect item.
            oFailedItem['id'] = reqFailedItem['id']
            oFailedItem['errorItems'] = oErrorItem['errorItems']
            # Set animation name attribute.
            self.__setAnimationName(oFailedItem)
            # Set valid attribute.
            errorItems = oErrorItem['errorItems'].split(',')
            if 'valid' in errorItems:
                oFailedItem['valid'] = 'yes'
            # Update used unknown indexes.
            self.usedUnknownIdxList.append(result)
        elif isinstance(result, (str, unicode)):
            oFailedItem = NodeUtils(reqFailedItem.getName(), makeNewNode = True)
            oFailedItem['id'] = reqFailedItem['id']
            oFailedItem['error'] = result

        respFailedDisplay.replaceChild(oErrorItem, oFailedItem)

    def __appendFailedBitmap(self, reqFailedItem, respFailedDisplay):
        oErrorItem = self.respFailedItems[self.reqFailedItems.index(reqFailedItem)]

        # Clone matching failed bitmap from self.respFailedItems.
        oFailedBitmap = oErrorItem.clone()
        # Copy item id from teststep expect item.
        oFailedBitmap['id'] = reqFailedItem['id']
        oFailedBitmap['errorItems'] = oErrorItem['errorItems']

        respFailedDisplay.replaceChild(oErrorItem, oFailedBitmap)

    def __appendUnknown(self, respFailedDisplay):
        """Creates summary tags for the rest of the unknown display items.
        """
        nonDisplayItems = []

        # Get unused unknown items list.
        leftUnknowns = self.__checkDisplayUnknownItem()

        for unknownItem in leftUnknowns:
            # Clone unknown item.
            oUnknownItem = unknownItem.clone()
            # Set unknown item id.
            oUnknownItem['id'] = 'unknown'
            # Set animation name attribute.
            self.__setAnimationName(oUnknownItem)

            if respFailedDisplay.getName() != 'display':
                nonDisplayItems.append(oUnknownItem)
            else:
                respFailedDisplay.append(oUnknownItem)

        for captureBitmap in self.captureBitmaps:
            respFailedDisplay.append(captureBitmap.clone())

        return nonDisplayItems

    def __appendOther(self, otherItems, respFailedDisplay):
        """Creates summary tags for other items.
        """
        displayOther = NodeUtils('display', makeNewNode = True)

        for oOther in otherItems:
            displayOther.append(oOther)

        respFailedDisplay.append(displayOther)

    def __removeDuplicateDisplayTexts(self, testRespRoot):
        """Removes dublicate unknown display texts from the response data.
        """
        # get all display tags
        oDisplays = testRespRoot.findall('//display')

        # lists for display text tags
        uniqueItemList, duplicateItemList = [], []

        for oDisplay in oDisplays:
            # unknown item display lacks id attribute
            if not 'id' in oDisplay.getAttributes():
                for oDisplayItem in oDisplay.getChildNodes():
                    valueDict = {}
                    if oDisplayItem.getName() == 'text':
                        valueDict['text'] = oDisplayItem['text']
                        for attrName in oDisplayItem.getAttributes():
                            valueDict[attrName] = oDisplayItem[attrName]
                        if not valueDict in uniqueItemList:
                            uniqueItemList.append(valueDict)
                        # put item to duplicate list if same item already exists
                        else:
                            duplicateItemList.append(oDisplayItem)

        # remove obsolete childs
        for oDisplayItem in duplicateItemList:
            oDisplayItem.parent().remove(oDisplayItem)

    def __copyCaptures(self, captures):
        """ Copy captures if save path has been set in capture-call

        """
        for capture in captures:
            if capture.getAttribute('save'):
                savePath = capture.getAttribute('save')
                imageSrcDir = os.path.join(core.FW_conf['test_result_dir'],
                        "captured bitmaps")
                if not os.path.isdir(savePath):
                    os.mkdir(savePath)
                from interfaces.wbxml_parser import captureIndex
                shutil.copy2(os.path.join(imageSrcDir, "capture_%s.png" % str(captureIndex)),savePath)
                capture.removeAttribute('save')


# ----------------------------------------------------------------------------
def evaluateTestStep(teststep, lastTagID = None):
    """Test step evaluator."""
    runnedTags = teststep.findall('//display')
    otherTags = teststep.findall('//capture')

    for tag in otherTags:
        if len(runnedTags) > 0:
            for display in runnedTags[:]:
                if int(tag['id']) < int(display['id']):
                    runnedTags.insert(runnedTags.index(display), tag)
                    break
                else:
                    if display == runnedTags[-1]:
                        runnedTags.append(tag)
        else:
            runnedTags.append(tag)

    # Remove childNodes
    for tag in runnedTags:
        if tag.getChildNodes() and tag.getName() != 'capture':
            for child in tag.getChildNodes()[:]:
                tag.remove(child)

    # Remove all not runned tags.
    if lastTagID:
        for tag in runnedTags[:]:
            if int(tag['id']) > lastTagID:
                del runnedTags[runnedTags.index(tag)]

    if len(runnedTags) > 0:
        summary = NodeUtils('summary', makeNewNode = True)

        for tag in runnedTags:
            if tag.getName() == 'capture':
                summary.append(tag.clone())
            else:
                for attribute in tag.parent().getAttributes():
                    if not attribute in ['id', 'name']:
                        tag.parent().removeAttribute(attribute)
                summary.append(tag.parent().clone())

        return summary

    return None

#  Self test
# ----------------------------------------------------------------------------
if __name__ == '__main__':
    import unittest

    class SelfTest(unittest.TestCase):
        def testSelfTest(self):
            pass

    unittest.main()
