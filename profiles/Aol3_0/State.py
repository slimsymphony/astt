# -*- coding: utf-8 -*-
class State(object):

    @classmethod
    def inMainMenu(profile, self, timeout = 1000, doNotReport = False):
        """Returns True if phone is in main menu, False if not.
        
            Parameters

            timeout             maximum timeout for wait in milliseconds
            doNotReport         whether action is not to be reported (default = False)
        """
        if not doNotReport:
            self.comment('state.inMainMenu() -- Aol3.0')

        # wait state to settle
        self.state.wait(timeout, doNotReport=True)
        
        if "com.nokia.homescreen:id/grid" in self.read.resourceId(doNotReport = True):
            return True
        else:
            return False

