import string
from random import randrange


# -*- coding: utf-8 -*-
class Navigate(object):
    """ implementation of navigate method """

    @classmethod
    def navigate(profile, self, item, doNotSelect=False, fromRecent=None):
        """ Navigate

            Parameters:
                item (string)        :   Name of the item where to navigate
                doNotSelect (bool)   :   If set to True item is only scrolled to screen without selecting it
                fromRecent (bool)    :   When True, application is launched from recent apps if found
                                         When False, application is removed from recent apps before navigate
                                         When None, normal navigate is in use (default)

            Returns True if navigating succeeded, False if not.
        """
        commentString = self._convertToReport(item)
        if doNotSelect == True:
            if fromRecent == True:
                raise Exception('Cannot use doNotSelect and fromRecent == True together!')

            commentString += ', doNotSelect'
        if fromRecent != None:
            commentString += ', fromRecent=%s' % str(fromRecent)

        self.comment('navigate(%s) -- AoL2.0' % commentString)

        return profile.__navigate(self, item, doNotSelect=doNotSelect, fromRecent=fromRecent)

    @classmethod
    def fromAppList(profile, self, item, doNotSelect=False, fromRecent=None):
        """ Navigate from app list.
        
            Parameters:
                item(string)         :   Name of the item
                doNotSelect (bool)   :   If set to True item is only scrolled to screen without selecting it
                fromRecent (bool)    :   When True, application is launched from recent apps if found
                                         When False, application is removed from recent apps before navigate
                                         When None, normal navigate is in use (default)
        """
        commentString = self._convertToReport(item)
        if doNotSelect == True:
            if fromRecent == True:
                raise Exception('Cannot use doNotSelect and fromRecent == True together!')

            commentString += ', doNotSelect'
        if fromRecent != None:
            commentString += ', fromRecent=%s' % str(fromRecent)

        self.comment('navigate.fromAppList(%s) -- AoL2.0' % commentString)

        return profile.__navigate(self, item, doNotSelect=doNotSelect, fromRecent=fromRecent, fromAppList=True)

    @classmethod
    def search(profile, self, item, doNotSelect=False, fromRecent=None):
        """ Navigate using app list search.
        
            Parameters:
                item(string)         :   Name of the item
                doNotSelect (bool)   :   If set to True item is only scrolled to screen without selecting it
                fromRecent (bool)    :   When True, application is launched from recent apps if found
                                         When False, application is removed from recent apps before navigate
                                         When None, normal navigate is in use (default)
        """
        commentString = self._convertToReport(item)
        if doNotSelect == True:
            commentString += ', doNotSelect'
        if fromRecent != None:
            commentString += ', fromRecent=%s' % str(fromRecent)
            
        self.comment('navigate.search(%s) -- AoL2.0' % commentString)
        
        # from recent apps functionality
        if fromRecent == True:
            if profile.__fromRecent(self, item, fromRecent):
                # NOTE: Application already launched so returning
                return True
        elif fromRecent == False:
            profile.__fromRecent(self, item, fromRecent)

        self.comment('navigate.search --> exit()')
        self.exit()

        # swipe to app list
        self.comment('Swiping to app list...')

        for i in range(5):
            self.swipe.viewSwipe()

            if not self.state.inMainMenu(timeout = 500, doNotReport = True):
                break
            else:
                if i == 4:
                    self.fail('Swiping to app list failed in navigate!')
                else:
                    self.warn('Swiping to app list failed! Trying again...')
                    time.sleep(0.5)

        searchNode = self.getItem.resourceId('*search_view', doNotReport = True)

        if searchNode:
            searchNode.select(doNotReport = True)
            self.comment('navigate.search --> input.push()')
            self.input.push(item)
                        
            foundNodes = self.getItems(item, doNotReport = True)
            
            # swipe screen a bit if not found at first
            if len(foundNodes) < 2:
                self.comment('navigate.search --> swipe screen to reveal more items')
                xCoord = self.uiState.getScreenWidth() / 2
                self.swipe((xCoord, self.uiState.getScreenHeight() / 2), (xCoord, 10))
                foundNodes = self.getItems(item, doNotReport = True)

            if len(foundNodes) < 2:
                self.fail('navigate.search: cannot find item "%s" by searching' % item)
            elif not doNotSelect:
                # loop for finding actual item that search found
                for foundNode in foundNodes:
                    if foundNode.getAttribute('text') == item and \
                       not foundNode.getResourceId().endswith('search_src_text'):
                        self.select(foundNode.getCenterPoint(), doNotReport = True)
                        break
        else:
            self.fail('navigate.search: cannot find "Search" item')

    @classmethod
    def random(profile, self, item, fromRecent=None):
        """Randomizes navigation method.
        
            Parameters:
                item (string)        :   Name of the item where to navigate
                fromRecent (bool)    :   When True, application is launched from recent apps if found
                                         When False, application is removed from recent apps before navigate
                                         When None, parameter value will be randomized.

            Returns True if navigating succeeded, False if not.
        """
        # if item's first letter is not ascii, navigate.letter and navigate.fast can't be executed
        if item[0] in string.ascii_uppercase:
            methodList = [self.navigate, self.fromAppList, self.search, self.letter, self.fast]
        else:
            methodList = [self.navigate, self.fromAppList, self.search]

        if fromRecent != None:
            assert fromRecent in [True, False], 'fromRecent can only be True/False with navigate.random!'
        else:
            valueList = [None, True, False]
            fromRecent = valueList[randrange(0, len(valueList))]

        self.comment('navigate.random(%s) -- AoL2.0' % self._convertToReport(item))

        # randomize used navigate method and call it
        navigateMethod = methodList[randrange(0, len(methodList))]
        return navigateMethod(item, fromRecent = fromRecent)

    @classmethod
    def __navigate(profile, self, item, doNotSelect=False, fromRecent=None, fromAppList=False):
        """ Navigate functionality
            Called from navigate and fromAppList methods

            Parameters:
                item (string)        :   Name of the item where to navigate
                doNotSelect (bool)   :   If set to True item is only scrolled to screen without selecting it
                fromRecent (bool)    :   When True, application is launched from recent apps if found
                                         When False, application is removed from recent apps before navigate
                                         When None, normal navigate is in use (default)
                fromAppList (bool)   :   When True, application is directly searched from application list
                                         When False, application is firstly searched from my space and then from application list (default)

            Returns True if navigating succeeded, False if not.
        """
        # from recent apps functionality
        if fromRecent == True:
            if profile.__fromRecent(self, item, fromRecent):
                # NOTE: Application already launched so returning
                return True
        elif fromRecent == False:
            profile.__fromRecent(self, item, fromRecent)
            
        coords = None
        
        # don't search node if fromAppList is True and we are in my space
        if not (fromAppList and self.state.inMainMenu(timeout = 500, doNotReport = True)):
            # NOTE: No need to wait for item here so setting timeout to 0
            coords = self.check(item, timeout = 0, doNotReport=True, getCoordinates=True)

        # check that if we are in idle, swipe to app list and try again
        if not coords and self.state.inMainMenu(timeout = 500, doNotReport = True):
            if not fromAppList:
                self.comment('Swiping to app list and searching "%s" again...' % self._convertToReport(item))
            else:
                self.comment('Swiping to app list and searching "%s"' % self._convertToReport(item))

            for i in range(5):
                self.swipe.viewSwipe()

                if not self.state.inMainMenu(timeout = 500, doNotReport = True):
                    break
                else:
                    if i == 4:
                        self.fail('Swiping to app list failed in navigate!')
                    else:
                        self.warn('Swiping to app list failed! Trying again...')
                        self.delay(500, False)

            if not coords:
                # NOTE: No need to wait for item here so setting timeout to 0
                coords = self.check(item, timeout = 0, doNotReport=True, getCoordinates=True)

        if coords:
            if not doNotSelect:
                self.select(coords, doNotReport=True)
            return True
        else:
            self.fail('Cannot navigate to %s, item not found!' % self._convertToReport(item))

            return False

    @classmethod
    def __fromRecent(profile, self, item, mode):
        """From recent apps functionality for navigate. Called from __navigate.

            Parameters

            item (string)        :   Name of the item where to navigate
            mode (bool)          :   When True, application is launched from recent apps
                                     When False, application is removed from recent apps before navigate

            Returns True if execution succeeded, False if not
        """
        success = False

        try:
            self.exit()
            self.select.long('KEYCODE_BACK')

            newLayout = False
            if self.check.resourceId('com.android.systemui:id/delete_button', doNotReport=True, doNotScroll=True):
                newLayout = True

                textList = []

                for i in range(100):
                    try:
                        self.getItem.description(item, area = (90, 190, 300, 500), doNotReport = True)
                    # exception means that item was not found
                    except Exception:
                        if not textList or textList != self.read.text(doNotReport = True):
                            textList = self.read.text(doNotReport = True)
                            self.swipe.viewSwipe(reverse = True, fromMiddle = True)
                        else:
                            break
                    else:
                        break

            if self.check.description(item, doNotScroll = newLayout):
                if mode == True:
                    self.comment('Launching "%s" from recent apps' % self._convertToReport(item))
                    self.select.description(item)

                    success = True
                else:
                    self.comment('Removing "%s" from recent apps' % self._convertToReport(item))

                    if newLayout:
                        self.select.resourceId('com.android.systemui:id/delete_button')
                    else:
                        self.select.long(item, withAttribute = 'description')
                        self.select('Remove')

                    self.exit()

                    success = True
            else:
                self.comment('Cannot find "%s" from recent apps' % self._convertToReport(item))
                self.exit()
        except Exception, err:
            # run exit in case of exception
            self.exit()
            debug.err('Failure in navigate from recent: %s' % self._convertToReport(err))

        return success

