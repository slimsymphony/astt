# -*- coding: utf-8 -*-

# Marble imports
import core

class ExitOverrides(object):

    def __init__(self, phone):
        self.phone = phone

    def __getattr__(self, attr, *args, **kwargs):
        """ Map phone to self """
        return getattr(self.phone,attr)

    def FullBlackBoxExit(self):
        """ uses external video camera to detect idle state
            return True if Idle could be reached, otherwise False
        """
        maxAttemps = 5
        for i in range(maxAttemps):
            if i >= maxAttemps-1:
                debug.err("FullBlackBoxExit: maximum iteration of exit attempts reached")
                return False

            if not self.__pressBackInLoop():
                self.__closeLastAppFromAppSwitcher()

            core.FW_conf['connection'].home()
            core.FW_conf['connection'].delay(4000)

            core.FW_conf['connection'].comment('Swipe a bit..')
            for i in range(2):
                yCoordinate = int(self.__getScreenDimensions()[0] / 2)
                fromPoint= (2, yCoordinate)
                toPoint = (40 , yCoordinate)
                core.FW_conf['connection']._touch.drawLine(fromPoint, toPoint)
                core.FW_conf['connection']._run('FullBlackBoxExit: gesture.swipe(%s,%s)'%( str(fromPoint), str(toPoint)))
                core.FW_conf['connection'].delay(1000)
                core.FW_conf['connection']._touch.drawLine(fromPoint, toPoint)
                core.FW_conf['connection']._run('FullBlackBoxExit: gesture.swipe(%s,%s)'%( str(fromPoint), str(toPoint)))
                if i == 0: 
                    core.FW_conf['connection'].delay(1000)
                    motionFramesStart = core.FW_conf['blackbox'].getCountMotionFrames()

            core.FW_conf['connection'].delay(1000)
            debug.brf('moves: %s' % str(core.FW_conf['blackbox'].getCountMotionFrames() - motionFramesStart))
            if core.FW_conf['blackbox'].getCountMotionFrames() - motionFramesStart >= 8: # @home
                return True

            # lock screen?
            core.FW_conf['connection'].select('KEYCODE_POWER')
            core.FW_conf['connection'].delay(5000) # phone should be either on glance screen or standby screen
            motionFramesStart = core.FW_conf['blackbox'].getCountMotionFrames()
            core.FW_conf['connection'].select('KEYCODE_BACK')
            core.FW_conf['connection'].delay(2000)

            if motionFramesStart == core.FW_conf['blackbox'].getCountMotionFrames():
                # in glance screen, press lock again
                core.FW_conf['connection'].comment('Glance screen..')
                core.FW_conf['connection'].select('KEYCODE_POWER')
                core.FW_conf['connection'].delay(1000)
                core.FW_conf['connection'].select('KEYCODE_BACK')
                core.FW_conf['connection'].delay(1000)

            # not (anymore) in glance screen, flick up and enter code
            core.FW_conf['connection'].comment('Flick up')
            xCoordinate = int(self.__getScreenDimensions()[1] / 2)
            fromPoint = (xCoordinate, self.__getScreenDimensions()[0] - 10)
            toPoint = (xCoordinate, 10)
            core.FW_conf['connection']._touch.drawLine(fromPoint, toPoint)
            core.FW_conf['connection']._run('FullBlackBoxExit: gesture.swipe(%s,%s)'%( str(fromPoint), str(toPoint)))

            core.FW_conf['connection'].delay(500)
            #if core.FW_conf['settings'].MTBF.PhoneLockEnabled:
            core.FW_conf['connection'].input.write('201426', mode='pin')

            core.FW_conf['connection'].delay(1000)

    def __pressBackInLoop(self, presses=10):
        """ Press back until no movement in screen 
            Param
                presses :     how many times at maximum back will be pressed
            Return:
                True    :     no movement after n back presses
                False   :     maximum presses reached and still movement
        
        """

        for i in range(presses):
            motionFramesStart = core.FW_conf['blackbox'].getCountMotionFrames()
            core.FW_conf['connection'].comment('Back press..')
            core.FW_conf['connection']._pressKey('KEYCODE_BACK', waitUntilNoUIevents=False)
            core.FW_conf['connection']._run('fullBlackBoxExit: back press')
            core.FW_conf['connection'].delay(500)
            if core.FW_conf['blackbox'].getCountMotionFrames() == motionFramesStart: # no movement
                return True

        return False

    def __closeLastAppFromAppSwitcher(self):
        """ open app switcher and close last application """
        # open app switcher
        core.FW_conf['connection'].comment('Closing last application from application switcher')
        core.FW_conf['connection'].comment('Long back press..')
        core.FW_conf['connection']._pressKey('KEYCODE_BACK', 1500, waitUntilNoUIevents=False)
        core.FW_conf['connection']._run('fullBlackBoxExit: long back press')
        core.FW_conf['connection'].delay(1000)
        # swipe to close last app
        core.FW_conf['connection'].comment('Swipe to close last app..')
        y = self.__getScreenDimensions()[0] - 10
        core.FW_conf['connection']._touch.drawLine( (10, y), (self.__getScreenDimensions()[1] -2, y) )
        core.FW_conf['connection']._run('fullBlackBoxExit: gesture.swipe')
        core.FW_conf['connection'].comment('Back press..')
        core.FW_conf['connection']._pressKey('KEYCODE_BACK', 500, waitUntilNoUIevents=False)
        core.FW_conf['connection']._run('fullBlackBoxExit: back press')

    def __getScreenDimensions(self):
        """ return height and width of the screen """
        return (800, 480)

        """ return height and width of the screen """
        return (800, 480)

        for i in range(presses):
            motionFramesStart = core.FW_conf['blackbox'].getCountMotionFrames()
            core.FW_conf['connection'].comment('Back press..')
            core.FW_conf['connection']._pressKey('KEYCODE_BACK', waitUntilNoUIevents=False)
            core.FW_conf['connection']._run('__fullBlackBoxExit: back press')
            core.FW_conf['connection'].delay(500)
            if core.FW_conf['blackbox'].getCountMotionFrames() == motionFramesStart: # no movement
                return True

        return False