# -*- coding: utf-8 -*-
class Exit(object):

    @classmethod
    def exit(profile,self):
        """Goes to phone's main menu.

            Returns True if main menu was reached, False if not
        """

        self.comment("self.exit() - AoL 2.1")
        
        okPressCount = 0

        # NOTE: When changing range, remember to change home key pressing conditions!!!
        for i in range(12):
            # just return if test execution is stopping
            if self.isStopping():
                return False

            if not self.state.inMainMenu(doNotReport = True):
            
                # don't press back in keyguard and FirstTimeUse
                package = self.state.get(timeout = 500, doNotReport = True, waitUntilNoUIevents=False)
                if package not in ['com.android.keyguard', 'com.nokia.FirstTimeUse']:
                    self.select('KEYCODE_BACK', doNotReport = True)
                    
                # if back has no effect, try back swipe
                if not self.state.inMainMenu(doNotReport = True) and \
                    self.state.get(timeout = 500, doNotReport = True, waitUntilNoUIevents=False) == "com.nokia.homescreen" and \
                    not "com.nokia.homescreen:id/grid" in self.read.resourceId(refreshDump=False, doNotReport = True):
                    
                    # reverse back swipe from application list
                    if "android.widget.ExpandableListView" in self.read.className(refreshDump=False, doNotReport = True):
                        self.swipe.viewSwipe(reverse = True)
                    else: # back swipe from fastlane
                        self.swipe.viewSwipe()

                    # continue to next loop round
                    continue
                    
                # get visible texts (dump is refreshed by previous step)
                visibleTexts = self.read.text(doNotReport = True, refreshDump=False)
                resourceId = self.read.resourceId(doNotReport = True, refreshDump=False)
                package = self.state.get(timeout = 500, doNotReport = True, waitUntilNoUIevents=False)
                
                # open glance screen if found
                if package == 'com.nokia.glancescreen':
                    self.select('KEYCODE_POWER')
                    continue

                # handle Ok pressing and count how many times it is pressed
                okText = ['Ok', 'OK', 'ok']
                if len(set(visibleTexts).intersection(okText)):
                    if okPressCount > 5: # if Ok pressed multiple times, time to try back few times
                        self.comment('Ok pressed %s times, trying back presses..' % str(okPressCount))
                        for i in range(3):
                            self.select('KEYCODE_BACK')
                        okPressCount = 0

                    else:
                        okPressCount += 1
                        # press Ok
                        for ok in okText:
                            if ok in visibleTexts:
                                coords = self.check(ok, doNotReport=True, getCoordinates=True)
                                self.select(coords, doNotReport=True)
                                self.comment('"%s" pressed in exit' % ok)
                                break

                    continue # next round, refresh state etc..
                
                # if there's close, continue or Done button, just press it                  
                pressThese = ['close', 'Close', 'Continue', 'Done']
                if len(set(visibleTexts).intersection(pressThese)):
                    for text in pressThese:
                        if text in visibleTexts:
                            coords = self.check(text, doNotReport=True, getCoordinates=True)
                            self.select(coords, doNotReport=True)
                            self.comment('"%s" pressed in exit' % text)
                            break
                    continue
                    
                # Microsoft account in FirstTimeUse
                if package=="com.nokia.FirstTimeUse" and \
                    'Microsoft account' in visibleTexts:
                    if 'Sign in' in visibleTexts:
                        self.comment('Press back to skip sign in..')
                        self.select('KEYCODE_BACK', doNotReport=True)
                    try:
                        self.select('Yes', doNotReport=True)
                        self.comment('"Yes" pressed to end signing in..')
                    except:
                        pass
                    continue
                
                # check if we have (whole) keyguard visible
                if 'com.android.keyguard:id/keyguard_status_view' in resourceId:
                    # if keyguard buttons are not on screen, upswipe
                    if not ("com.android.keyguard:id/keyguard_pin_view" in resourceId and \
                            "com.android.keyguard:id/key9" in resourceId):
                            self.swipe.upSwipe()
                            continue
                    else:
                        clearPrevious = False
                        if self.check.resourceId('com.android.keyguard:id/delete_button', timeout = 0, doNotReport = True, doNotScroll = True):
                            clearPrevious = True
                        profile.enterSecurityCode(self, clearPrevious=clearPrevious)
                
                # Home key press if nothing else helps
                elif not self.state.inMainMenu(doNotReport = True) and i > 5:
                    if i < 11:
                        self.select('KEYCODE_HOME', doNotReport = True)
                        self.comment('Home key pressed in exit in order to return to main menu')
                    # within two last iterations press long home
                    else:
                        self.select.long('KEYCODE_HOME', doNotReport = True)
                        self.warn('Long home key press in exit in order to return to main menu!')
                
                # wait that UI stabilizes before next loop round
                self.state.wait(doNotReport=True)
                
            else:
                # in setup phase press home key to ensure that we are not in my space's edit mode
                if self.isInSetup():
                    self.select('KEYCODE_HOME', doNotReport = True)
                    self.comment('Home key pressed in exit when running setup')
                return True

        return False

    @classmethod
    def enterSecurityCode(profile, self, clearPrevious):
       # clear previous code
        if clearPrevious:
            self.select.long('com.android.keyguard:id/delete_button', withAttribute = 'resourceId', doNotReport = True, doNotScroll = True)
        
        # get the security code for the device
        securityCode = None
        try:
            securityCode = eval("self.settings.%s.SecurityCode" % self.getName())
        finally:
            if not securityCode or securityCode == '12345':
                securityCode = '201426'

        # input code
        for d in securityCode:
            self.select.resourceId('com.android.keyguard:id/key%s' % d, doNotReport = True, doNotScroll = True, doNotWait = True)

        if self.check.resourceId('com.android.keyguard:id/key_enter', timeout = 0, doNotReport = True, doNotScroll = True):
            self.select.resourceId('com.android.keyguard:id/key_enter', doNotReport = True, doNotScroll = True)
