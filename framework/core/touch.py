# -*- coding: ascii -*-
# ============================================================================
#
#
# %full_filespec:   touch.py-ou1s40#A2_19:ascii:ou1iam#1 %
#                   ----------------------------------------------------------
#                   Granite Module - Python
#
#
# Copyright (c) Nokia. All rights reserved.
#
# ----------------------------------------------------------------------------
"""Touch module which provides interfaces for pressing touch keys
   and writing characters with touch.
"""
import os, time, string, cPickle, re, math, types, core
from copy import copy
from zipfile import ZipFile, ZIP_DEFLATED

#from d_product import touchKeyAreas, capacitiveTouchKeys, PRODUCT_DISPLAY_INFO
import core
from core.testcase_exceptions import TestException
from utils.nodeutils import NodeUtils


def _isTextInCollector(text, collector):
    """
    Try to match *, ? in text
    1. Translate (, ) to [(], [)]
    2. Translate ? to .
    3. Translate * to .+
    """
    text = translateText(text)
    if '*' in text or '?' in text:
        text = re.sub('\(', '[(]', text)
        text = re.sub('\)', '[)]', text)
        text = re.sub('\?', '.', text)
        text = re.sub('\*', '.*', text)
        text = re.sub('\+', '.', text)
        text = re.sub('\$', '.', text)
        for _item in collector:
            if re.match(text, _item):
                return _item
    else:
        if text in collector: return text

    return False

class Touch(object):
    """Touch component."""
    def __init__(self, phoneInstance):
        self._phone = phoneInstance

        # *** get copy of product's touch key areas
        #self.touchKeyAreas = copy(touchKeyAreas)

    def __pressPoint(self, x, y, length=None, wait=None, waitUntilNoUIevents=True):
        """Delivers press and release events of given point."""
        self.__serverPressPoint(x=x, y=y, length=length, wait=wait, waitUntilNoUIevents=waitUntilNoUIevents)

    def __getPortraitCoordinates(self, x, y):
        """Return portrait coordinates.

            Parameters

            x       x coordinate
            y       y coordinate
        """
        if self._phone.uiState.screenOrientation == self._phone.uiState.LANDSCAPE:
            # store original y value
            yValue = y

            # flip x and y and calculate x
            y = x
            x = self._phone.uiState.getScreenHeight() - yValue

        return x, y

    def touchFromFile(self, filePath):
        """Unzip and unpickle script_data.art from given file and
           deliver touch events to the phone.
        """
        zipped = ZipFile(filePath, 'r', ZIP_DEFLATED)
        fileData = None
        touchList = []

        for fileName in zipped.namelist():
            if fileName.endswith('script_data.art'):
                fileData = zipped.read(fileName)
                break

        if fileData:
            scriptData = cPickle.loads(fileData)

            for data in scriptData:
                touchList.append({'x':data[0], 'y':data[1]})

            self.__serverPressPoint(events=touchList)

        time.sleep(1)   # wait so that character will be recognized

    def write(self, touchString):
        """Write all characters from given string with touch."""
        assert 0, 'Not implemented!'

    def press(self, pressArea, length=None, wait=20, waitUntilNoUIevents=True):
        """Press given area or point with touch."""
        if type(pressArea) in [str, unicode]:
            result = re.match('\(\d+,\s*\d+\s*\)', pressArea)
            if result:
                pressArea = eval(result.group(0))

        if not isinstance(pressArea, list):
            pressArea = [pressArea]

        #if type(pressArea) in [str, unicode]:
        #    if pressArea in self.touchKeyAreas:
        #        # self._phone.comment('"%s" (%s, %s) pressed with touch' % \
        #            # (pressArea, self.touchKeyAreas[pressArea][0], self.touchKeyAreas[pressArea][1]))
        #        pressArea = self.touchKeyAreas[pressArea]
        #    else:
        #        raise AssertionError('No area "%s" found from press area dictionary!' % repr(pressArea))
        # else:
            # self._phone.comment('point (%s, %s) pressed with touch' % (pressArea[0], pressArea[1]))

        for point in pressArea:
            x, y = point
            #self._phone.comment('press: (%s,%s)'%(pressArea[0], pressArea[1]))
            self.__pressPoint(x, y, length=length, wait=wait, waitUntilNoUIevents=waitUntilNoUIevents)

    def scroll(self, fromPoint, toPoint, delay=None, addLength=20, stepSize=40, holdPenToStopScroll=True):
        """Scroll the screen by the amount indicated by the coordinate points.

        Can make very long scrolls that normal users aren't able to because of the limited display size.

        Parameters:
        fromPoint           tuple with two int values, (x,y)
                            x and y coordinates from where to start the scrolling

        toPoint             tuple with two int values, (x,y)
                            x and y coordinates indicating the end of the scroll

        delay               int value. defines the delay after each touch event in milliseconds
                            defines the scroll speed, larger delay makes the scrolling slower

        addLength           int value, default = 0
                            amount of length to be added to the original length of the scroll.
                            this is not added to diagonal scrolls.
                            compensates for the scrolls to be too short otherwise.
                            since by phone design scrolling isn't started before
                            pen is moved atleast 20 pixels. This can change?

        stepSize            int value, default = 40
                            units (pixels) to travel before forming a new intermediate tuple
                            must be factor of 20 i.e. 1, 2, 4, 5, 10, 20

        holdPenToStopScroll Boolean, True = holding the pen at the end point to stop scrolling
                                     False = lets the screen srcoll after reaching the end point

        """

        #if only horizontal scrolling add addLength amount to x coordinate of the end point.
        if fromPoint[1] == toPoint[1]:
            if fromPoint[0] > toPoint[0]:
                newX = toPoint[0] - addLength
            else:
                newX = toPoint[0] + addLength
            toPoint = (newX, toPoint[1])

        #if only vertical scrolling add addLength amount to y coordinate of the end point.
        elif fromPoint[0] == toPoint[0]:
            if fromPoint[1] > toPoint[1]:
                newY = toPoint[1] - addLength
            else:
                newY = toPoint[1] + addLength
            toPoint = (toPoint[0], newY)

        self.drawLine(fromPoint, toPoint, delay, stepSize, holdPenToStopScroll)

    def drawShape(self, steps, holdPenToStopScroll=False, delay=None):
        """ Draws a shape from given points
        Parameters:

        steps               List of coordinate tuples

        holdPenToStopScroll To prevent scrolling at the end of drawing, keep "pen" down on last coords

        delay               int value. defines the delay after each touch event in milliseconds
                            defines the scroll speed, larger delay makes the scrolling slower
        """

        touchEvents = []
        #Start drawing
        #Move pen through each step (from start to end)
        for step in steps:
            #Move pen while pressed down
            touchEvents.append({'x':step[0], 'y':step[1],'length': delay})

        #Hold the pen so the drawing isn't continued further than wanted
        if holdPenToStopScroll:
            for ii in range(0,5):
                touchEvents.append({'x':steps[-1][0], 'y':steps[-1][1],'length': delay})

        #Release pen
        touchEvents.append({'x':steps[-1][0], 'y':steps[-1][1],'length': delay})
        # self._phone.comment('drawShape: %s'%touchEvents)
        self.__serverPressPoint(events=touchEvents)


    def drawLine(self, fromPoint, toPoint, delay=None, stepSize=40, holdPenToStopScroll=True, duration=None, dragHold=False, wait=20):
        """Simulates drawing a line with a Touch pen.

        Can be used for example to scroll the screen.
        Can draw very long lines that normal users aren't able to because of the limited display size.

        Parameters:
        fromPoint           tuple with two int values, (x,y)
                            x and y coordinates from where to start drawing

        toPoint             tuple with two int values, (x,y)
                            x and y coordinates indicating the end of the line

        delay               int value. defines the delay after each touch event in milliseconds
                            defines the scroll speed, larger delay makes the scrolling slower

        stepSize            int value, default = 40
                            units (pixels) to travel before forming a new intermediate tuple

        holdPenToStopScroll Boolean, True = holding the pen at the end point to stop scrolling
                                     False = lets the screen srcoll after reaching the end point

        dragHold            long delay after first step in order to simulate drag
                            (default = False)

        wait                how long we'll wait between coordinate points
                            int value, default = 20
        """
        #Calculate route for scrolling (ensures proper diagonal scrolling)
        steps = self._calcRoute(fromPoint, toPoint, stepSize, duration)

        touchEvents = []
        #Start drawing
        #Move pen through each step (from start to end)

        for step in steps:
            touchDict = {'x':step[0], 'y':step[1],'length': delay}

            #Move pen while pressed down
            touchEvents.append(touchDict)

        #Hold the pen so the drawing isn't continued further than wanted
        if holdPenToStopScroll:
            for ii in range(7):
                touchEvents.append({'x':toPoint[0], 'y':toPoint[1]})

        #Release pen. Wait 200 ms for scroll to stop
        touchEvents.append({'x':toPoint[0], 'y':toPoint[1],'wait': 200})
        #self._phone.comment('drawLine: %s'%touchEvents)
        #debug.brf('drawLine: %s'%touchEvents)

        self.__serverPressPoint(events=touchEvents, wait=wait, dragHold=dragHold)

    def _calcRoute(self, fromPoint, toPoint, stepSize=40, duration=None):
        """Creates a route for drawing a line.

        Generates a list of coordinate tuples to form a route between two points.
        Intermediate steps are located stepSize apart from each other.
        Ensures proper diagonal scrolling.

        Parameters:
        fromPoint   tuple with two int values, (x,y)
                    x and y coordinates from where to travel

        toPoint     tuple with two int values, (x,y)
                    x and y coordinates indicating the end of the trip

        stepSize    int value, default = 40
                    units (pixels) to travel before forming a new intermediate tuple
                    must be factor of 20 i.e. 1, 2, 4, 5, 10, 20 if used with Touch.scroll

        Returns:
        A list of coordinate tuples forming a route from start to end point.
        """
        # Override delay and stepsize if duration is given
        if duration:
            assert duration>=0.10, "Too small duration given: %s"%duration

        #Define direction to travel
        xDir = fromPoint[0] > toPoint[0] and -1 or 1
        yDir = fromPoint[1] > toPoint[1] and -1 or 1

        #Calculate distance for x and y
        Ax = float(abs(fromPoint[0]-toPoint[0]))
        Ay = float(abs(fromPoint[1]-toPoint[1]))

        #Calculate direct distance
        length = (Ax**2+Ay**2)**0.5
        #Calculate angle
        if Ax != 0:
            angle = math.atan(Ay/Ax)
        else:
            angle = math.pi/2

        if not duration:
            #Calculate steps required
            numSteps = int(length / stepSize)
        else:
            numSteps = int(duration/100)-2

        a = fromPoint[0]
        b = fromPoint[1]
        #Add start point
        steps = [(a,b)]

        #Create intermediate steps
        for ii in range(0, numSteps):
            a += xDir * stepSize * math.cos(angle)
            b += yDir * stepSize * math.sin(angle)
            steps.append((int(a),int(b)))

        #Add end point
        if int(a) != toPoint[0] or int(b) != toPoint[1]:
            steps.append((toPoint[0],toPoint[1]))

        return steps

    def __serverPressPoint(self, **params):
        """ Touch screen interactions

            parameters for single point touch:
                x           x-coorinate
                y           y-coordinate
                length      length for whole touch event
                wait        wait after touch
                dragHold    long delay after first step in order to simulate drag
                            (default = False)

            example:
                self.touch('x':123, 'y':54)
                self.touch([{'x':123, 'y':54},{'x':133, 'y':54},{'x':143, 'y':54}])
        """
        point = {
                     'x': 0,
                     'y': 0,
                     'length':50,
                     'wait':20}

        # update length parameter
        if params.has_key('length') and params['length']:
            length = params['length']
        else:
            length = point['length']

        # update wait parameter
        if params.has_key('wait') and params['wait']:
            wait = params['wait']
        else:
            wait = point['wait']

        # update the parameters for single point touch
        if params.has_key('x') and params.has_key('y'):
            point.update(params)

        # Multiple point touch
        elif params.has_key('events'):
            point = params['events']
        else:
            assert 0, "No valid touch points given"

        if type(point) != types.ListType:
            point = [point]

        # When there are multiple coordinates in one touch
        # div the touch length to all events
        length = length / len(point)

        # minimum length is the touch panel refresh rate 1sec/50hz = 20ms
        if length < 20:
            length = 20

        touchItem = NodeUtils('touch', makeNewNode = True)
        # set wait for ui events value for touch item
        if params.has_key('waitUntilNoUIevents'):
            touchItem['waitUntilNoUIevents'] = params['waitUntilNoUIevents']

        # set dragHold value for touch item
        if params.has_key('dragHold'):
            touchItem['dragHold'] = params['dragHold']

        for i in range(len(point)):
            item = point[i]

            # get portrait coordinates for NG phones
            # because Touchpad needs coordinates in portrait-mode
            if not 'Main' in self._phone.getName():
                x, y = self.__getPortraitCoordinates(int(item['x']), int(item['y']))
            else:
                x, y = int(item['x']), int(item['y'])

            # First item is always press
            if i == 0:
                touchPoint = NodeUtils('press', makeNewNode = True)
                touchPoint['x'] = x
                touchPoint['y'] = y
                touchPoint['touch_id'] = 0
                # use given wait if available
                touchPoint['wait'] = (item.has_key('wait') and item['wait'] != None) and item['wait'] or wait
                touchPoint['length'] = (params.has_key('dragHold') and params['dragHold']) and 1500 or length
                touchItem.append(touchPoint)

            # last item is release. If there is only one touch point, then
            # first and last coordinate are the same
            if i == len(point)-1:
                touchPoint = NodeUtils('release', makeNewNode = True)
                touchPoint['x'] = x
                touchPoint['y'] = y
                touchPoint['touch_id'] = 0
                touchPoint['wait'] = wait
                touchPoint['length'] = length
                touchItem.append(touchPoint)

            else:
                if i > 0: #do not generate another touch event for first coordinates (press, move in the same coordinates)
                    touchPoint = NodeUtils('move', makeNewNode = True)
                    touchPoint['x'] = x
                    touchPoint['y'] = y
                    touchPoint['touch_id'] = 0
                    touchPoint['wait'] = wait
                    touchPoint['length'] = length
                    touchItem.append(touchPoint)

        self._phone.keyPresses.append(touchItem)

    def pressPointMultiTouch(self, steps, duration):
        """ Touch screen interactions


        """
        if self._phone.getName() != 'Main':
            assert self.server_version['yyy']>3 or \
                (self.server_version['yyy']>=3 and self.server_version['xxx']>=2), "Multitouch is supported from Granite server version 1.3.2 onwards"

        if duration:
            length = duration/len(steps)
        else:
            length = 20
        wait = 200

        touchItem = NodeUtils('touch', makeNewNode = True)
        for i in range(len(steps)):
            item = steps[i]

            for ii in range(len(item)):
                point = item[ii]
                # First item is always press
                if i == 0:
                    touchPoint = NodeUtils('press', makeNewNode = True)
                elif i == len(steps)-1:
                    touchPoint = NodeUtils('release', makeNewNode = True)
                else:
                    touchPoint = NodeUtils('move', makeNewNode = True)

                touchPoint['x'] = str(int(point[0]))
                touchPoint['y'] = str(int(point[1]))
                touchPoint['touch_id'] = ii
                touchPoint['wait'] = (i == len(steps)-1 and ii==len(item)-1 and wait) or (ii==len(item)-1 and length) or 0
                touchPoint['length'] = length
                touchItem.append(touchPoint)

        self._phone.keyPresses.append(touchItem)

    def tapZoneArea(self, zoneName, layoutName='QLN_ZNE_COMMON2', length=100):
        zoneData = layouts.calculateZone([[layoutName, zoneName],])

        x = zoneData[0]+zoneData[2]/2
        y = zoneData[1]+zoneData[3]/2

        self._phone.pressKey((x,y), length=length)

    def tapTextItem(self, text, zoneName=None, layoutName='QLN_ZNE_COMMON2', zoneData=None, length=None):
        if not zoneName is None and zoneData is None:
            zoneData = layouts.calculateZone([[layoutName, zoneName],])

        for i in range(0,10):
            self._phone.captureTexts(name='safe_browse_text', zoneData=zoneData)

            safe_browse_result = self._phone.run('Touch.tapTextItem: Capture texts in current screen', \
                testStepReporting=False)

            if safe_browse_result['safe_browse_text']: break
        else:
            self._phone.fail('Touch.tapTextItem: Cannot capture item in current view')

        curTextList = [item['text'] for item in safe_browse_result['safe_browse_text']]

        _text = _isTextInCollector(text, curTextList)

        if _text: text = _text
        else:
            self._phone.setExpectTimes(10)
            self._phone.expectText(text, zoneName=zoneName, layoutName=zoneName and layoutName or None)
            self._phone.run('Find appointed text in current screen')
            self._phone.fail('Touch.tapTextItem: Cannot find "%s" in current screen' % text)

        _backup = None
        for item in safe_browse_result['safe_browse_text']:
            if item['text'] == text and item['background'] == 'no':
                x=int(item['x'])
                y=int(item['y'])
                w=int(item['width'])
                h=int(item['height'])

                if y > PRODUCT_DISPLAY_INFO['height'] or x > PRODUCT_DISPLAY_INFO['width']:
                    _backup = (x, y, w, h)
                else:
                    break
        else:
            if _backup is None:
                self._phone.fail('Touch.tapTextItem: Cannot find "%s" in current screen' % text)
            else:
                self._phone.warn('Touch.tapTextItem: Captured area exceed screen size. It is %s' % repr(_backup))
                x, y, w, h = _backup

        x = x+w/2
        y = y+h/2
        self._phone.pressKey((x,y), length=length)

    def tapAnimItem(self, anim, zoneName=None, layoutName='QLN_ZNE_COMMON2', zoneData=None, length=None):
        if not zoneName is None and zoneData is None:
            zoneData = layouts.calculateZone([[layoutName, zoneName],])

        for i in range(0,10):
            self._phone.captureAnimations(name='safe_browse_anim', zoneData=zoneData)

            safe_browse_result = self._phone.run('Touch.tapAnimItem: Capture Animations in current screen', \
                testStepReporting=False)

            if safe_browse_result['safe_browse_anim']: break
        else:
            self._phone.fail('Touch.tapAnimItem: Cannot capture item in current view')

        for item in safe_browse_result['safe_browse_anim']:
            if item['name'].lower() == anim.lower():
                x=int(item['x'])
                y=int(item['y'])
                w=int(item['width'])
                h=int(item['height'])
                break
        else:
            self._phone.fail('Touch.tapAnimItem: Cannot find item %s' % anim)

        x = x+w/2
        y = y+h/2

        self._phone.pressKey((x,y), length=length)

