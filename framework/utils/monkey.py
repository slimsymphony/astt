"""
Granite Monkey tester module
@author Mika Mikkela

"""

import core
from core import debug, uitestcase, testcase, scripting
from core.testcase_exceptions import TestException, StopTestException

import sys, os, time, imp, random, time, inspect, types
from utils.phone_file_dumper import CommonFileDumper
import re

import clr
clr.AddReference('System.Xml')
from System.Xml import XmlDocument
clr.AddReference('System.Web')
from System.Web import HttpUtility # for decoding strings in xml
debugMode = True

class MonkeyException(Exception):
    listMonkeyExceptions = {}
    def __init__(self, value):
        self.value = value
        MonkeyException.listMonkeyExceptions[id(self)] = 1 # list to keep track of monkey exceptions
    def __str__(self):
        return repr(self.value)
    def __del__(self):
        del MonkeyException.listMonkeyExceptions[id(self)]

class MonkeyTarget(object):
    """ a class to contain properties of the found target """
    TYPE_UIOBJECT, TYPE_EVENT = 0, 1
    xmlTextDecoder = HttpUtility()
    listMonkeyTargets = {}

    def __init__(self, monkeyTargetType, targetNodeType=None, targetImageOrText=None, targetNode=None, weight=1.0, targetMainNode=None, settingIndex=None, method=None):
        
        # for tracing monkey targets usage
        MonkeyTarget.listMonkeyTargets[id(self)] = 1

        self.monkeyTargetType = monkeyTargetType      # TYPE_UIOBJECT or TYPE_EVENT
        self.targetImageOrText = targetImageOrText  # image.png or text for this target
        self.targetNodeType = targetNodeType        # image-widget/label/textinput
        self.settingIndex = settingIndex            # if there's more than 1 setting defined for this target, this specifies the index of the target
        self.targetNode = targetNode                # reference to target node (image-widget/label/textinput)
        self.targetMainNode = targetMainNode        # reference to node where this target is in
        self.weight = weight                        # target weight. defaults to 1 in initialization
        self.method = method

        self.__coords = None
        
    def __del__(self):
        del MonkeyTarget.listMonkeyTargets[id(self)] # for keeping list of monkey targets. whenever target is deleted, it will be removed from the list

    def getTargetMainNode(self):
        """ Return the node where this specific target was found from """
        if self.monkeyTargetType == MonkeyTarget.TYPE_UIOBJECT:
            return self.targetMainNode
        else:
            debug.err('Cannot return coordinates for MonkeyTarget.TYPE_EVENT')

    def getTargetNode(self):
        """ Return the target node, image-widget / label / textinput """
        if self.monkeyTargetType == MonkeyTarget.TYPE_UIOBJECT:
            return self.targetNode
        else:
            debug.err('Cannot return coordinates for MonkeyTarget.TYPE_EVENT')

    def getTargetCoords(self):
        """ Return the coordinates of this target """
        if self.monkeyTargetType == MonkeyTarget.TYPE_UIOBJECT:
            if not self.__coords:
                self.__setTargetCoords()
            return self.__coords
        else:
            return (None, None) # MonkeyTarget.TYPE_EVENT

    def getTargetTextOrImage(self):
        """ Return the target image or text """
        if self.monkeyTargetType == MonkeyTarget.TYPE_UIOBJECT:
            if self.targetImageOrText == None:
                self.__setTargetImageOrText()
            return self.targetImageOrText
        else:
            debug.err('Cannot return target image / text for MonkeyTarget.TYPE_EVENT')

    def __setTargetTextOrImage(self):
        """ if target text or image has not been set, this will do it """
        if self.targetNodeType in ['label', 'textinput']:
            self.targetImageOrText = MonkeyTarget.xmlTextDecoder.HtmlDecode(targetNode.getAttribute('text')) # decode text with HtmlDecode to get rid of &#xA; etc..
        elif self.targetNodeType == 'image-widget':
            self.targetImageOrText = os.path.split(targetNode.getAttribute('image'))[-1]
        else:
            self.targetImageOrText = None

    def __setTargetCoords(self):
        """ Set the coordinates of this target """
        if self.targetNode:
            try:
                self.__coords = int(self.targetNode.getAttribute('left')) + int(self.targetNode.getAttribute('width')) / 2, \
                                int(int(self.targetNode.getAttribute('top')) + int(self.targetNode.getAttribute('heigth')) / 2)
            except:
                self.__coords = None, None
        else:
            self.__coords = None, None

class CommandHistory(object):
    """ class to keep track of executed commands """

    def __init__(self, value):
        self.lastTarget = None
        self.lastAction = None
        self.lastActionParam = None
        self.lastActionParamValue = None

    def last(self):
        return True

    def append(self, target, action):
        pass

    def wasExecutedLast(self, target, action):
        
        if len(action) > 0:
           self.lastAction = action[0]
        else:
            self.lastAction = None

        if len(action) > 1:
            self.lastActionParam = action[1]
        else:
            self.lastActionParam = None

        if len(action) > 2:
            self.lastActionParamValue = action[2]
        else:
            self.lastActionParamValue = None

class Monkey(object):

    def __init__(self, tc, settingsFile=None):

        self.tc = tc
        
        self.__settingsPath = os.path.normpath(os.path.join(core.FW_conf['startup_path'], '../settings'))

        if settingsFile == None:
            self.__settingsFile = "Monkey.xml"
        else:
            self.__settingsFile = settingsFile

        self.commands = []
        self.commandhistory = []

        self.blacklist = [] # blacklist of items not to touch
        self.weightDict = [] # weighting dictionary (image/text as keys, weight as value)

        self.reloadActionLimit = True
        self.getTargetCounter = 0
        debugMode = True

        self.__fileDumper = None
        self.__xmlTextDecoder = HttpUtility()
        
        self.settings = None
        self.targets_xpath = None
        self.triggers_xpath = None
        
        self._eventMethods = []
        self._eventsLoaded = False
        self._macrosLoaded = False
        self.__macroPath = os.path.normpath(os.path.join(core.FW_conf['startup_path'], r'../test_scripts/monkey'))
        self.__recordPath = None
        sys.path.append(self.__macroPath)

        # import macros/events if available
        if os.path.isfile(os.path.join(self.__macroPath, 'monkey_events.py')):
            global monkey_events
            import monkey_events
        if os.path.isfile(os.path.join(self.__macroPath, 'monkey_macros.py')):
            global monkey_macros
            import monkey_macros
    
        self.recorded_scriptfile = None

        self.__tempPath = r"c:\temp"

    def __getRandomListItem(self, list):
        """ get random object from given list of objects. 
        
        TODO: 
            - use weighting 
            - give ignore elements list
        
        """
        if list:
            return list[random.randint(0,len(list)-1)]
        else:
            return None

    def __getRandomAction(self, list):
        """ go through the list and seek the unique actions. """

        actionDict = {}

        if list:
            for item in list:
                if len(item) == 3 and item[0] != "":
                    if not actionDict.has_key(item[0]):
                        actionDict[item[0]] = [[item[1], item[2]]]
                    else:
                        if not [item[1],item[2]] in actionDict[item[0]]:
                            actionDict[item[0]].append([item[1],item[2]])

            randomkey = actionDict.keys()[random.randint(0, len(actionDict.keys())-1)]
            randomparam = actionDict[randomkey][random.randint(0,len(actionDict[randomkey])-1)]
            return [randomkey, randomparam[0], randomparam[1]]
        else:
            return None
        
    def __getTranslatedName(self, value):

        # if '/' in value: # if this is possibly a logical image name, try get the png name
        value = self.tc.uiState._getImage(value)
                                    
        if 'n' in value[0]: # possible a logicalstring
            translation = self.tc.getTranslation(value)
            if translation != None:
                value = translation
        
        return value

    def __generateQuery(self, nodeName):
        """ generate Query from nodes with given nodeName

        """
        
        init_query = '//*/*['
        query = init_query

        for node in self.settings.SelectNodes(nodeName):

            # node should be either target or trigger. There should be child nodes defining the params
            if not node.HasAttribute('name'):
                continue

            # ignore nodes with empty name
            if node.GetAttribute('name') == "":
                continue

            # if no attributes in node, skip
            if not node.HasChildNodes:
                continue

            # check if this is not the first query
            if query != init_query:
                query += ' or '

            if node.GetAttribute('name').ToString() != 'key': # vkb items don't have visible-flag
                query += '(self::%s and @visible="true" and @width>"0" and @heigth>"0" and @center-x>="0" and @center-x<="%s" and not(ancestor::*[@visible="false" or @width<="0" or @heigth<="0"])' % (node.GetAttribute('name').ToString(), self.tc.uiState.getScreenWidth())
            else:
                query += '(self::%s and @width>"0" and @heigth>"0" and @center-x>="0" and @center-x<="%s" and not(ancestor::*[@visible="false" or @width<="0" or @heigth<="0"])' % (node.GetAttribute('name').ToString(), self.tc.uiState.getScreenWidth())

            #query += '(self::%s and @visible="true"' % node.GetAttribute('name').ToString()
                
            # start going through the parameters
            for arg in node.ChildNodes.GetEnumerator():
                    
                node_name = arg.Name.ToString() # node should be either 'require' or 'exclude'

                if node_name == 'require' or node_name == 'exclude' or node_name == 'optional':  # handle required, optional and excluded attributes
                    
                    if node_name == 'optional': # optional ones will be gathered inside brackets
                        first = True

                    if not arg.HasChildNodes: # if no attributes, skip
                        continue

                    for req in arg.ChildNodes.GetEnumerator():

                        if not req.HasAttribute('name'):  # require name from attribute
                            continue

                        if req.GetAttribute('name') != "": # require name from attribute

                            if req.HasAttribute('value'):

                                if node_name == 'optional' and first:
                                    query += ' and ('
                                    first = False
                                elif node_name == 'optional':
                                    query += ' or '

                                value = req.GetAttribute('value').ToString()

                                if value != "": # non-empty values 
                                    # if this value is possible to translate or get logical id
                                    value = self.__getTranslatedName(value)

                                    if node_name == 'require':
                                        query += ' and contains(@%s,"%s")' % (req.GetAttribute('name').ToString(), value.ToString())
                                    elif node_name == 'optional':
                                        query += 'contains(@%s,"%s")' % (req.GetAttribute('name').ToString(), value.ToString())
                                    else: # node_name should be "exclude"
                                        query += ' and not(contains(@%s,"%s"))' % (req.GetAttribute('name').ToString(), value.ToString())

                                else: # empty values
                                    if node_name == 'require':
                                        query += ' and @%s="%s"' % (req.GetAttribute('name').ToString(), value.ToString())
                                    elif node_name == 'optional':
                                        query += '@%s="%s"' % (req.GetAttribute('name').ToString(), value.ToString())
                                    else: # node_name should be "exclude"
                                        query += ' and @%s!=""' % (req.GetAttribute('name').ToString())
                                            
                            elif req.HasAttribute('flexvalue'):  # handle values, which needs to be evaluated

                                if req.GetAttribute('flexvalue') != "":
                                    if node_name == 'require':
                                        query += ' and @%s="%s"' % (req.GetAttribute('name').ToString(), eval(req.GetAttribute('flexvalue').ToString()))
                                    elif node_name == 'optional':
                                        query += '@%s="%s"' % (req.GetAttribute('name').ToString(), eval(req.GetAttribute('flexvalue').ToString()))
                                    else: # node_name should be "exclude"
                                        query += ' and @%s!="%s"' % (req.GetAttribute('name').ToString(), eval(req.GetAttribute('flexvalue').ToString()))

                    if node_name == 'optional': # optional ones will be gathered inside brackets
                        query += ')'

                        
            query += ')' # close single target / trigger query

        query += ']' # close entire query

        for i in range(2):
            try:
                self.tc.uiState.currentStateFull.findall(query) # validate xpath
                return query
            except:
                if i == 0: # in case query failed, try once after state refresh
                    self.tc.uiState.getCurrentState(refresh=True)
                    continue
                self.message("invalid query (%s) : %s" % (nodeName, query))
                for i in query.split('self::'):
                    self.message(i)
                return None
            
    def __dumpXmlDocument(self, xmlDoc):
    
        pass

    def __loadConfiguration(self):
        """ Loads XML configuration and macro files.
        """ 

        # load xml configuration
        if os.path.isfile(os.path.join(self.__settingsPath, self.__settingsFile)):
            
            new_targets = {}
            #try:
            
            settings = XmlDocument()
            f = open(os.path.join(self.__settingsPath, self.__settingsFile))
            settings.LoadXml(f.read())

            self.settings = settings

            f.close()
    
        else:
            self.message("Could not find settings")


        # load macro and event file
        if os.path.isdir(self.__macroPath):

            for (path, directory, files) in os.walk(self.__macroPath,):

                for file in files:

                    if os.path.split(file)[1] == 'monkey_events.py':
                        self._eventMethods = []
                        reload(monkey_events)

                        if not self._eventsLoaded:
                            self._eventsLoaded = True
                                                        
                        for member in dir(monkey_events):
                            if isinstance(monkey_events.__dict__.get(member), types.FunctionType):
                                #self.message('method %s' % member)
                                self._eventMethods.append(member)
                                
                    if os.path.split(file)[1] == "monkey_macros.py": 
                        reload(monkey_macros)
                        if not self._macrosLoaded:
                            self._macrosLoaded = True
                        
        # generate xpath queries.. 
        targetQuery = self.__generateQuery('//target')
        if targetQuery == None:
            if self.targets_xpath != None:
                self.message("Could not load target selection settings, using old ones..")
            else:
                self.tc.fail("Could not load target selection settings")
        else:
            self.targets_xpath = targetQuery
            
        triggerQuery = self.__generateQuery('//trigger')
        if triggerQuery == None:
            if self.triggers_xpath != None:
                self.message("Could not load triggering selection settings, using old ones..")
            else:
                self.tc.fail("Could not load triggering settings")
        else:
            self.triggers_xpath = triggerQuery
            
        # generate blacklist dictionary.. 
        blacklist = []
        try:
            for blacklistedItem in self.settings.SelectNodes('//blacklisted'):
                blacklist.append(self.__getTranslatedName(blacklistedItem.GetAttribute('item')))
            if self.blacklist != blacklist:
                self.message("New blacklist loaded.")
                self.blacklist = blacklist
        except Exception as e:
            if self.blacklist:
                self.message("error in blacklist creation, using old blacklist")
            else:
                debug.brf('perse: %s' % str(e.message))
                self.tc.fail("Could not create blacklist: %e" % str(e.message))
                
        # generate image/label weighting dictionary.. 
        weights = {}
        try:
            for weightNode in self.settings.SelectNodes('//weight'):
                weights[self.__getTranslatedName(weightNode.GetAttribute('item'))] = weightNode.GetAttribute('weight')
            if self.weightDict != weights:
                self.message("New weights loaded.")
                self.weightDict = weights
        except:
            if self.weightDict:
                self.message("error in weighting dictionary creation, using old weighting dictionary")
            else:
                self.tc.fail("Could not create weighting dictionary.")

    def __isInVisibleDump(self, _type, target):
        """ checks that given target (tuple of type and image/text) is in visible dump """
        nodes = None

        try:
            if _type in ['label', 'textinput']:
                if target != "":  # all empty texts will be ignored
                    nodes = self.tc.uiState.currentState.findall('//%s[@text="%s"]' % (_type, target))
            else:
                if target != "":
                    nodes = self.tc.uiState.currentState.findall('//%s[contains(@image,"%s")]' % (_type, target))
        except:
            self.logError('_isInVisibleDump failed with type (%s) target (%s)' % (_type, target))
            
        if nodes:
            return True
        else:
            return False

    def __getTargetMainNodeWeight(self, targetNode):
        """ get index and weight defined in settings for given node """
        
        weight = 1 # this is the default weight if no other weight has been found
        index = 0  # index number of the found target in settings xml
        foundTarget = None # find corresponding target from settings. There might be more than 1 target with same name
        firstTarget = None
        success = False # when correct node has been found

        i = 0
        
        #self.message("getTargetNodeWeight: for targets named %s" % targetNode.getName())    
        
        # go through all target nodes in settings with name of given targetNode
        for target in self.settings.SelectNodes('//target[@name="%s"]' % targetNode.getName() ).GetEnumerator():

            if target.SelectSingleNode('require'): # check required attributes to see if this is the correct target

                for req in target.SelectSingleNode('require').ChildNodes.GetEnumerator():
                    name = value = None
                    try:
                        name = req.GetAttribute('name')
                        value = req.GetAttribute('value')
                        value = self.__getTranslatedName(value)
                    except:
                        pass
                    else:
                        # self.message("check %s <-> %s" % (value, targetNode.getAttribute(name)))
                        if (name != '' or name != None) and value in targetNode.getAttribute(name):
                            #self.message("found target %s with requirements %s=%s" % (targetNode.getName(), name, value))
                            foundTarget, index = target, i # this required attribute was ok
                            success = True
                        else:
                            #self.message("not matching target (%s), next.." % targetNode.getName())
                            foundTarget, index = None, None
                            success = False
                            break # this was not correct target, get next one
                
                if success:
                    #self.message("break loop %s (foundTarget %s)" % (i, targetNode.getName()))
                    break

            elif foundTarget == None: # if correct target has not been already found, select the first node without requirements
                #self.message("using %s %s" % (targetNode.getName(), i))
                firstTarget, index = target, i

            i += 1

        if foundTarget:
            if foundTarget.HasAttribute('weight'):
                weight = float(foundTarget.GetAttribute('weight'))
        elif firstTarget:
            if firstTarget.HasAttribute('weight'):
                weight = float(firstTarget.GetAttribute('weight'))

        #self.message("returning weight %s, index %s" % (weight, index))

        return weight, index

    def __getTargetWeight(self, targetName):
        """ get weight defined in settings for given target (image/text) """
        
        weight = None # if no weight found from settings, return None

        if self.weightDict.has_key(targetName):
            return float(self.weightDict[targetName])
        else:
            return None

    def __getAllTargetsFromNodes(self, targetNodes):
        """
        1. targetNodes can contain containers or image-widget/label/textinput
            - targetNodes will be extracted to image-widgets/labels/textinputs
        2. validate image/text found from target 2 times:
            - not blacklisted
            - in visible dump
        3. if seeking targets in container
            - get container weight from settings
            - use same weight for targets inside if no weight defined for target
        4. return a list of MonkeyTargets

        """
        
        targetList = []
        checkingDict = {} # dictionary to check any duplicates

        if debugMode:
            f = r'c:\temp\all_current_targets.txt'
            self.logToFile("targetnodes in total: %s" % len(targetNodes), f, 'w' )
            
        for targetNode in targetNodes:
            
            _type = targetNode.getName()
            target = None
            coords = itemWeight = None
            nodeWeight, settingIndex = self.__getTargetMainNodeWeight(targetNode) # defaults to 1, None
            if debugMode:
                self.logToFile("targetnode type: %s weight %s" % (_type, nodeWeight), f)
            
            # if current target node is not itself a image or text, extract it
            if not _type in ['image-widget', 'label', 'textinput']:
                targets = targetNode.findall('.//*[(self::image-widget or self::label or self::textinput) and @visible="true"]')
            else:
                targets = [targetNode]

            for item in targets:
                _type = item.getName()

                if _type in ['label', 'textinput']:
                    target = self.__xmlTextDecoder.HtmlDecode(item.getAttribute('text')) # decode text with HtmlDecode to get rid of &#xA; etc..
                else:
                    target = os.path.split(item.getAttribute('image'))[1]

                if not self.__isBlackListed(target) and self.__isInVisibleDump(_type, target):
                    
                    targetWeight = self.__getTargetWeight(target)
                    if targetWeight != None:
                        itemWeight = targetWeight
                    else:
                        itemWeight = nodeWeight
                    
                    # check that have we already added this specific target to targets list
                    if checkingDict.has_key(target):
                        if checkingDict[target].weight >= itemWeight:  # if existing target has higher or same weight, ignore this target
                            continue
                        
                    monkeyTgt = MonkeyTarget(MonkeyTarget.TYPE_UIOBJECT, _type, target, item, itemWeight, targetNode, settingIndex)
                    targetList.append(monkeyTgt)
                    checkingDict[target] = monkeyTgt
                        
                    if debugMode:
                        self.logToFile('%s, %s, weight %s, settingIndex %s' % (_type, target, itemWeight, settingIndex), f)
                
        return targetList

    def __getRandomMonkeyTarget(self, list):
        """ param list is a list of MonkeyTargets
            weight will be used when picking the item from the list
        """

        if len(list) < 1:
            return None

        weights = []
        for monkeyTarget in list:
            weights.append(monkeyTarget.weight)
            
        if debugMode:
            try:
                f = open(r'c:\temp\targets_in_weighted_select.txt', 'w')
                for i in range(len(weights)):
                    if list[i].monkeyTargetType == MonkeyTarget.TYPE_EVENT:
                        f.write("Event %s, weight %s\n" % (list[i].method, list[i].weight))
                    else:
                        x,y = list[i].getTargetCoords()
                        f.write("%s, target %s, coords, (%s, %s), weight %s, index of target %s\n" % (list[i].targetNodeType, str(list[i].targetImageOrText), x,y, list[i].weight, list[i].settingIndex))
                    if weights[i] != list[i].weight:
                        self.broadcast("ERROR IN WEIGHTING!")
                f.close()
            except:
                pass

        # get object with weight
        rnd = random.random() * sum(weights)
        for i, w in enumerate(weights):
            rnd -= w
            if rnd < 0:
                return list[i]

    def __getEventTargets(self):
        """ Return list of event type of monkeyTargets 
        """
        eventTargetList = []
        for eventMethod in self._eventMethods:
            eventTargetList.append(MonkeyTarget(MonkeyTarget.TYPE_EVENT, method=eventMethod))
            #eventTargetList.append(MonkeyTarget(MonkeyTarget.TYPE_EVENT, method=eventMethod, weight=10000))
        return eventTargetList


    def __getTarget(self):
        """ return one randomly selected available MonkeyTarget

        Return (MonkeyTarget)   :   Instance of Monkey Target

        """
        
        # refresh the UI and find all matching targets
        if self.tc.uiState.currentStateFull == None:
            self.tc.uiState.getCurrentState(refresh=True)

        targetNodes = self.tc.uiState.currentStateFull.findall(self.targets_xpath)
        
        if targetNodes:

            monkeyTargetList = self.__getAllTargetsFromNodes(targetNodes) # get list of targets

            if monkeyTargetList: # only if there's UI type of targets, use event type of targets. TODO: should events be launched without actual targets as well?
                monkeyTargetList += self.__getEventTargets()

            # print targets if settings defined
            if self.settings.SelectSingleNode('//printtargets') != None:
                p = self.settings.SelectSingleNode('//printtargets').GetAttribute('value')
                if p.lower() == "true":
                    tgtsMsg = 'Available targets: '
                    for i in range(len(monkeyTargetList)):
                        if monkeyTargetList[i].targetImageOrText:
                            tgtsMsg = tgtsMsg + monkeyTargetList[i].targetImageOrText + ' -- '
                        else:
                            tgtsMsg = tgtsMsg + 'event: ' + monkeyTargetList[i].method + ' -- '
                        if i > 0 and i % 7 == 0: # split to fit output better
                            tgtsMsg = tgtsMsg + '\n'
                    
                    self.message(tgtsMsg)

            if self.settings.SelectSingleNode('//savestate') != None:
                p = self.settings.SelectSingleNode('//savestate').GetAttribute('value')
                if p.lower() == "true":
                    self.message('state saved as %s' % self.tc.capture())
            
            if monkeyTargetList:
                self.getTargetCounter += 1
                return self.__getRandomMonkeyTarget(monkeyTargetList)
            else:
                # if no target 
                self.message("failed to get target")
                if debugMode:
                    self.saveCurrentState("notargets_from_validate")
                return None

        else:
            self.message("No targets found")
            if debugMode:
                self.saveCurrentState("notargets")
            return None

    def __isBlackListed(self, item):
        """ check if item (image, text) is blacklisted """
        
        if debugMode:
            try:
                onlyAllowedTargets = []
                for tgt in self.settings.SelectNodes('//onlytarget'): # in debug mode, all the other targets except these are "blacklisted"
                    if tgt.GetAttribute('name') != "":
                        onlyAllowedTargets.append(tgt.GetAttribute('name'))

                if onlyAllowedTargets:
                    if item in onlyAllowedTargets:
                        return False
                    else:
                        return True
            except:
                pass
        if item in self.blacklist:
            return True
        else:
            return False
        
    def __getMonkeyAction(self, monkeyTarget):
        """ Get an action for a monkeyTarget using the monkey configuration

            Parameter:
            monkeyTarget (MonkeyTarget) :   Monkey Target
            
            Return:
            actions (3 item list)   :   [0]: action name (select, gesture.flick, ...)
                                        [1]: parameter name (direction, ...)
                                        [2]: parameter value('up', '172', ...)
        """
        
        actions = []
        targetSettingNode = self.settings.SelectNodes('//target[@name="%s"]' % monkeyTarget.targetMainNode.getName())[monkeyTarget.settingIndex]
        
        if targetSettingNode.HasChildNodes:
            for actionNode in targetSettingNode.SelectNodes('.//action'):
                if actionNode.HasChildNodes: # parameters for action
                    if actionNode.HasChildNodes and actionNode.GetAttribute('name').ToString() != "":
                        for p in actionNode.ChildNodes.GetEnumerator():
                            if p.GetAttribute('value').ToString() != "":
                                tempAction = [actionNode.GetAttribute('name').ToString(), p.GetAttribute('name').ToString(), p.GetAttribute('value').ToString()]
                                if tempAction not in actions:
                                    actions.append(tempAction)
                            elif p.GetAttribute('variable').ToString() != "":
                                tempAction = [actionNode.GetAttribute('name').ToString(), p.GetAttribute('name').ToString(), eval(p.GetAttribute('variable').ToString())]
                                if tempAction not in actions:
                                    actions.append(tempAction)
                    else:
                        tempAction = [actionNode.GetAttribute('name').ToString(), None, None]
                        if tempAction not in actions:
                            actions.append(tempAction)

                else:
                    actions.append([actionNode.GetAttribute('name').ToString(),None,None])

        if actions:
            #self.message('%s actions found:' % len(actions))
            #for a in actions:
            #    self.message(a)
            return self.__getRandomAction(actions)

    def debug(self, message):
        """ Output a debug message """
        if debugMode:
            self.message(message)
        
    def message(self, message):
        """ Output a message
        """
        try:
            self.tc.comment("%s: %s" % (self.__class__.__name__, str(message)))
        except:
            try:
                self.logError("Error with message write. msg > \n%s" % str(message))
            except:
                self.logError("Error with message write!")
        
    def logError(self, message):
        t = time.localtime(time.time())
        now = "%d-%02d-%02d %02d:%02d:%02d" % (t.tm_year, t.tm_mon, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec)
        try:
            f = open(r'c:\temp\monkey_errors.log', 'a')
            f.write("%s > %s\n" % (now, repr(message)))
            f.close
        except:
            self.broadcast('Could not open error log file', True)

    def logToFile(self, message, filename=r'c:\temp\monkey.log', mode='a'):
        t = time.localtime(time.time())
        now = "%d-%02d-%02d %02d:%02d:%02d" % (t.tm_year, t.tm_mon, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec)
        try:
            f = open(filename, mode)
            f.write("%s %s\n" % (now, repr(message)))
            f.close()
        except:
            self.broadcast('Could not write to log file %s' % filename, True)

    def broadcast(self, message, onlyMessages=False):
        # put message to error log, output and scriptfile
        self.message(message)
        self.__commentToScriptFile(message)
        self.tc.comment(message)
        if not onlyMessages:
            self.logError(message)
        
    def saveCurrentState(self, msg=None, addToDump=None):
        """ saves current state to a dump file
            msg(string)         :       file identifier to be added
            addToDump(string)   :       string to be added to dump file
        """
        try:
            if msg == None:
                f = open(os.path.join(self.__tempPath, r'monkey_savedstate_%s.xml' % self.getTargetCounter), 'w')
                f2 = open(os.path.join(self.__tempPath, r'monkey_savedstate_visible_%s.xml' % self.getTargetCounter), 'w')
            else:
                f = open(os.path.join(self.__tempPath, r'monkey_%s.xml' % msg), 'w')
                f2 = open(os.path.join(self.__tempPath, r'monkey_visible_%s.xml' % msg), 'w')

            f.write(self.tc.uiState.currentStateFull.toprettyxml())
            f2.write(self.tc.uiState.currentState.toprettyxml())
        
            if addToDump:
                f.write(addToDump)
                f2.write(addToDump)
        except:
            self.logError('Could not write dump. Msg: %s. addToDump: %s' % (msg, addToDump))
        finally:
            f.close
            f2.close

    def __collectCrashInfo(self):
        """ method for collecting x-files or other crash info """
        try:
            dumpFiles = self.__fileDumper.extractDumpFiles()
            if dumpFiles:
                try:
                    self.message("Found dump files")
                    if self.commandhistory:
                        message = "Dumpfiles found. Last command %s / %s / %s" % (self.commandhistory[-1].values()[0], self.commandhistory[-1].keys()[0], self.commandhistory[-1].values() )
                        self.broadcast(message)
                        
                except:
                    self.broadcast("Found x-files, but cannot get last command")

                try:
                    self.__fileDumper.removeDumpFiles()
                except:
                    self.tc.warn('Removing X-files failed')

        except:
            self.broadcast('Getting X-files failed')
            try:
                self.tc.warn('Getting X-files failed')
            except:
                pass

    def __execute(self, action=None, target=None):
        """ Execute an command. Create script step if command went ok

            Parameters:
            command(string)         :       Command to be executed (e.g. self.tc.select('Notes', relatedTo='Foo'))
            action(3-item list)     :       Action to be executed (e.g. action[0] = "select.long" action[1] = None / "length", action[2] = "17" / None
            target(string)          :       Object to perform the action to ('image.png', 'Contacts', 'Clock', etc.)

        """
        if action[0] in ['delay']:
            try:  # try converting string value to integer
                value = int(target)
                target = value
            except:
                pass
            
        if target != None and target != "" and action[0] not in ['delay']:
            # get logical id for target image or text
            if ".png" in target:
                logicalId = self.tc.getLogicalImageName(target)
                if logicalId:
                    target = logicalId[0]
            else:
                logicalId = self.tc.getLogicalText(target)
                if logicalId and type(logicalId) is str:
                    target = logicalId
                elif logicalId and type(logicalId) is list:
                    target = logicalId[0]
            
            """
            example of command history
            self.commandhistory = [ 
                                    {'foo.png': 
                                        ['gesture.flick', 'direction', 'down']
                                    }, 

                                    {'Messages': 
                                        ['select', None, None]
                                    }
                                  ]

                => self.commandhistory[-2].keys() => 'foo.png'
                        <foo.png>.values() => [['gesture.flick', 'direction', 'down']]
                        <foo.png>.values()[0] => ['gesture.flick', 'direction', 'down']
                        <foo.png>.values()[0][0] => ['gesture.flick']

            """

            # check from command history have this same action/target been executed
            if self.commandhistory and len(self.commandhistory) > 1:
                # self.message("%s(%s) - %s(%s)" % (self.commandhistory[-2].values()[0][0],self.commandhistory[-2].keys()[-1], action[0], target))
                if self.commandhistory[-2].keys()[-1] == target:
                    if self.commandhistory[-2][target][0] == action[0]:
                        # same command has been executed just, don't execute
                        raise MonkeyException("Skip action %s(%s), last action/target was the same" % (action[0], target))
                    else:
                        pass
                else:
                    pass

        if len(action) > 1 and action[1] != None: # if there's parameters for action

            try:  # try converting string value to integer
                value = int(action[1])
                action[1] = value
            except:
                pass
            
            if len(action) > 2:
                try:  # try converting string value to integer
                    value = int(action[2])
                    action[2] = value
                except:
                    pass

                if isinstance(action[2], int) or isinstance(action[2], float) : # if param is int or float, no quotation
                    parameter = "%s=%s" % (action[1], action[2])
                else:
                    parameter = "%s='%s'" % (action[1], action[2])
            else: 
                parameter = "%s" % action[1]

            if isinstance(target, int) or isinstance(target, float): # if target is int or float, no quotation
                cmd = "self.tc.%s(%s, %s)" % (action[0], target, parameter)
            else:
                cmd = "self.tc.%s('%s', %s)" % (action[0], target, parameter)

        else: # if no parameters for action
            if target:
                if isinstance(target, int) or isinstance(target, float) or isinstance(target, tuple):
                    cmd = "self.tc.%s(%s)" % (action[0], target)
                else:
                    cmd = "self.tc.%s('%s')" % (action[0], target)
            else:
                cmd = "self.tc.%s()" % (action[0])

        try:
            
            try:
                if action[0] != 'delay':
                    translation = self.tc.getTranslation(target)
                    if translation != None:
                        self.__commentToScriptFile("Execute %s (%s)" % (cmd.replace('.tc.', '.'), translation))
                    else:
                        self.__commentToScriptFile("Execute %s" % cmd.replace('.tc.', '.'))
            except:
                self.broadcast("Could not create script comment")
            
            # command might contain line feed characters, which will cause problem with eval. change all line feeds to \\n    
            cmd = "\\n".join(cmd.split("\n"))
            eval(cmd)

        except TestException as e:
            self.__commentToScriptFile("failed to execute command %s (reason %s), item might not be anymore visible on screen" % (cmd, e.message))
            self.tc.comment("Could not execute command '%s' (reason %s), item might not be anymore visible on screen" % (cmd, e.message))
            self.__collectCrashInfo()
        except:
            self.__commentToScriptFile("failed to execute command %s" % cmd)
            self.tc.comment("Could not execute command '%s'" % cmd)
            # self.saveCurrentState("execution_failed_%s" % self.getTargetCounter)
            self.__collectCrashInfo()
            
        else:
            self.commandhistory.append({target: action})
            try:
                f = open(os.path.join(self.__recordPath, self.recorded_scriptfile), "a")
                f.write("        %s\n" % cmd.replace('self.tc.', 'self.'))
                f.close()
            except:
                self.broadcast('Failed to put entry to saved script')

    def __executeDelay(self, length = 1000):
        " execute delay step. len in secs. """

        cmd = 'delay(%s, False)' % str(length)
        #cmd = 'delay(%s)' % str(length)
        self.__executeStringCommand(cmd)
        
    def __executeStringCommand(self, command):
        """ extract string to target / action and execute """
        action = []
        
        m = re.search('(.*?)\((.*)\).*', command)
        if m:
            action.append(m.group(1))
            args = m.group(2)

            if not ('(' in args and ')' in args) : # when arg is not tuple for sure
                m = re.search('(.*), *(.*)', args)
                if m:
                    target = m.group(1).replace('"', '').replace("'", '')
                    arg2 = m.group(2).replace('"', '').replace("'", '')
                    if "=" in arg2: # this needs to be splitted still
                        m = re.search('(.*)=(.*)', arg2)
                        if m:
                            action.append(m.group(1))
                            action.append(m.group(2))
                    else:
                        action.append(arg2)
                else:
                    target = args.replace('"', '').replace("'", '')

            else: # target might be a tuple
                target = args.replace('"', '').replace("'", '')
        else:
            self.message("Cannot parse action from string %s" % command)
            self.logError("Cannot parse action from string %s" % command)
            return

        try:
            self.__execute(action, target)
        except:
            self.logError('executeStringCommand failed (%s)' % command)

    def __executeEvent(self, method):
        """ execute script from Event module
        
        Parameters:
        eventMethod (string)    :     Name of the method to be executed

        """

        if self._eventsLoaded:
            self.message("execute event: %s" % method)
            
            try:
                getattr(monkey_events, method)(self.tc) # call for event
                self.commandhistory.append({'event': [method]})
                self.__stepToScriptFile('monkey_events.%s(self)' % method)

            except Exception as e:
                self.broadcast("Could not execute event %s: %s" % (method, e.message))
                
    def __executeMacro(self, method):
        """ Execute a macro from monkey macros module 
        
        Parameters
        method (string)     :      Name of the macro to be executed
        """
        
        if not self._macrosLoaded:
            self.message('tried to execute macro %s but macros are not loaded!')
            return

        self.message("execute macro: %s" % method)

        try:
            getattr(monkey_macros, method)(self.tc) # call for macro
            self.commandhistory.append({'event': [method]})
            self.__stepToScriptFile('monkey_macros.%s(self)' % method)
                
        except Exception as e:
            self.broadcast("Could not execute macro %s, %s" % (method, e.message))
            
    def __checkTriggers(self):

        # vkb detection. vkb can be used with a macro
        # if self.tc.uiState.vkb.vkbOnScreen == True:
            # pass 
            
        if self.triggers_xpath == None: # if no triggering query generated, return
            return False
        commands = []
        methods = []

        # nodes in current state which will match the triggers query
        triggers = self.tc.uiState.currentStateFull.findall(self.triggers_xpath)
        
        if triggers:
            
            if len(triggers) > 1:
                self.message("Warning, state consist %s parts that match the trigger" % len(triggers))
                self.message(self.triggers_xpath)
            
            for trigger in triggers: # loop as many times there's triggers found, append to commands/methods
                #debug.brf(trigger.toprettyxml())
                # go through the trigger definitions to check which matches with the found target
                for triggerSetting in self.settings.SelectNodes('//trigger[@name="%s"]' % trigger.getName() ):
                    
                    # check that do we have correct trigger definition node at hand
                    matchingReq=False
                    if triggerSetting.HasChildNodes:
                        matchingTriggers = []

                        # 2 parts checking: 1) optional (one match is enough) 2) required (each one need to be ok)
                        for req in triggerSetting.SelectNodes('./optional/*'): # if one of these is true, append the trigger
                            if ".png" in trigger.getAttribute(req.GetAttribute('name')):
                                attrName = os.path.split(trigger.getAttribute(req.GetAttribute('name')))[1]
                            else:
                                attrName = trigger.getAttribute(req.GetAttribute('name'))

                            attrValue = self.__getTranslatedName(req.GetAttribute('value'))
                            #debug.brf('bar %s - %s' % (attrName, attrValue))
                            if attrName == attrValue:
                                matchingReq = True
                                break
                            else:
                                matchingReq = False

                        for req in triggerSetting.SelectNodes('./require/*'): # Loop through all required attributes of this trigger setting, see if it matches
                            # if trigger in has the attribute named in the settings and corresponding value, then it's a match. 
                            if ".png" in trigger.getAttribute(req.GetAttribute('name')):
                                attrName = os.path.split(trigger.getAttribute(req.GetAttribute('name')))[1]
                            else:
                                attrName = trigger.getAttribute(req.GetAttribute('name'))

                            attrValue = self.__getTranslatedName(req.GetAttribute('value'))
                            #debug.brf('foo %s - %s' % (attrName, attrValue))
                            if attrName == attrValue:
                                matchingReq = True
                            else:
                                matchingReq = False

                        if matchingReq: # if all required attributes were ok, append the trigger to matching ones
                            matchingTriggers.append(triggerSetting)
                            
                        if matchingTriggers: 
                            #debug.brf('jou %s' % len(matchingTriggers))   
                            for matchingTrigger in matchingTriggers:
                                for ta in matchingTrigger.SelectNodes('./actions/action'):  # check trigger actions
                                    for p in ta.ChildNodes.GetEnumerator():
                                        if p.HasAttribute('name') and p.GetAttribute('name') != "":

                                            if p.Name == "method":
                                                #debug.brf('adding method %s' % p.GetAttribute('name'))
                                                methods.append(p.GetAttribute('name'))
                                            elif p.Name == "command": ## TODO: these nodes are not named properly yet, cannot be named "action" because parent node is "action"
                                                #debug.brf('adding command %s' % p.GetAttribute('name'))
                                                commands.append(p.GetAttribute('name'))
                                    
                                            # todo: handle parameters
                                            #if p.GetAttribute('param').ToString() != "":
                                            #    tempAction = [ta.GetAttribute('name').ToString(), p.GetAttribute('name').ToString(), p.GetAttribute('value').ToString()]
                                            #    actions.append(tempAction)

            # select by random between commands and methodss
            command = None
            method = None

            if len(commands) + len(methods) > 1:
                self.message('Trigger: random select from commands %s / methods %s' % (commands, methods))

            if commands:
                command = self.__getRandomListItem(commands)
                if not methods:
                    self.message('trigger: executing %s' % command)
                    self.__executeStringCommand(command)
                    return True
            if methods:
                method = self.__getRandomListItem(methods)
                if not commands:
                    self.message('trigger: executing macro %s' % method)
                    self.__executeMacro(method)
            if command and method:
                r = random.randint(0,1)
                if r == 0:
                    self.message('trigger: executing macro %s' % method)
                    self.__executeMacro(method)
                else:
                    self.message('trigger: executing %s' % command)
                    self.__executeStringCommand(command)
                return True
           
        return False

    def __initializeScriptFile(self):
        """ initialize recorded script """

        self.__recordPath = os.path.normpath(os.path.join(core.FW_conf['test_result_dir'], 'monkey'))
        if not os.path.isdir(self.__recordPath):
            os.makedirs(self.__recordPath)

        t = time.localtime(time.time())
        now = "%d%02d%02d_%02d%02d%02d" % (t.tm_year, t.tm_mon, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec)
        self.recorded_scriptfile = r'monkey_recorded_execution_%s.py' % now
        self.message('Recording to %s' % os.path.join(self.__recordPath, self.recorded_scriptfile))
        
        # if events and macros module exists, add imports
        imports = '\n# Note: change the macro path according to your environment.'
        if os.path.isfile(os.path.join(self.__macroPath, 'monkey_events.py')) or \
            os.path.isfile(os.path.join(self.__macroPath, 'monkey_macros.py')):
            imports += '\nimport sys\n'
            imports += 'sys.path.append(r\'%s\')\n' % self.__macroPath

        if os.path.isfile(os.path.join(self.__macroPath, 'monkey_events.py')):
            imports += 'import monkey_events\n'
        if os.path.isfile(os.path.join(self.__macroPath, 'monkey_macros.py')):
            imports += 'import monkey_macros\n'

        if not os.path.isfile(os.path.join(self.__recordPath, self.recorded_scriptfile)):

            f = open( os.path.join(self.__recordPath, self.recorded_scriptfile), "w")
            f.write("""import core 
from core import uitestcase %s
class testBed(uitestcase.UITestCase):

    subarea = "Recorded"
    feature = "Monkey testing"

    def recorded_%s(self):
        \"\"\"Recorded script from Monkey execution

        %s started on %s
        \"\"\"
""" % (imports, now, '@tcId', now))
            f.close()
        else:

            f = open( os.path.join(self.__recordPath, self.recorded_scriptfile), "a")
            f.write("""
    def recorded_%s(self):
        \"\"\"Recorded script from Monkey execution

        @tcId started on %s
        \"\"\"
""" % (now, now))
            f.close()

    def __stepToScriptFile(self, stepString):
        try:
            f = open(os.path.join(self.__recordPath, self.recorded_scriptfile), "a")
            f.write("        %s\n" % stepString)
            f.close()
        except Exception as e:
            self.message("Error adding step to scriptfile: %s" % e.message)

    def __commentToScriptFile(self, message):
        try:
            f = open(os.path.join(self.__recordPath, self.recorded_scriptfile), "a")
            f.write("        # %s\n" % message)
            f.close()
        except Exception as e:
            self.message("Error with script file commenting: %s" % e.message)

    def createBlacklistXML(self, filepath):
        """ helper function to create a xml blacklist node of items in the current screen """

        images = self.tc.uiState.currentStateFull.findall('.//image-widget[@visible="true"]')
        labels = self.tc.uiState.currentStateFull.findall('.//label[@visible="true"]')
        for node in self.tc.uiState.currentStateFull.findall('.//textinput[@visible="true"]'):
            labels.append(node)
        
        try:
            f = open(filepath, "w")
            f.write("  <blacklist>\n")
        
            for image in images:
                try:
                    f.write('    <blacklisted item="%s"/>\n' % os.path.split(image.getAttribute('image'))[1])
                except:
                    pass
            for label in labels:
                try:
                    f.write('    <blacklisted item="%s"/>\n' % label.getAttribute('text'))
                except:
                    pass
            f.write(r"  </blacklist>\n")
            f.close()
        except IOError:
            self.message("could not open file. %s" % file)
        except Exception as e:
            self.message("could not create blacklist xml. error: %s" % e.message)

    def execute(self, app=None, actions=None, minutes=None):
        self.spank(app, actions, minutes)

    def spank(self, app=None, actions=None, minutes=None):
        """ Main method for executing the Monkey.
            
        """

        self.message("Starting monkey testing...")
        
        if self.__fileDumper == None:
           self.__fileDumper = CommonFileDumper(self.tc)

        self.__initializeScriptFile()
        self.message("Reading settings..")
        self.__loadConfiguration()

        if actions == None:
            actionLimit = int(self.settings.SelectSingleNode('//monkeyactions').GetAttribute('value'))
        else: # limits received from start method
            self.reloadActionLimit = False # don't load action limits from xml configuration
            actionLimit = actions

        if actionLimit == 0 or minutes != None:
            if minutes == None:
                timeLimitSeconds = int(self.settings.SelectSingleNode('//testingtime').GetAttribute('seconds'))
                timeLimitMinutes = int(self.settings.SelectSingleNode('//testingtime').GetAttribute('minutes'))
                timeLimitHours = int(self.settings.SelectSingleNode('//testingtime').GetAttribute('hours'))
                if timeLimitSeconds != 0:
                    forTime = timeLimitSeconds
                    self.message("Testing for %s seconds" % timeLimitSeconds)
                elif timeLimitMinutes != 0:
                    forTime = float(timeLimitMinutes) * 60
                    self.message("Testing for %s minutes" % timeLimitMinutes)
                elif timeLimitHours != 0:
                    forTime = float(timeLimitHours) * 3600
                    self.message("Testing for %s hours" % timeLimitHours)

            else: # limit received from monkey startup
                forTime = float(minutes) * 60
                actionLimit = 0
                self.message("Testing for %s minutes" % minutes)
                self.reloadActionLimit = False # don't load actions limit from xml
        else:
            forTime = 0
            self.message("Testing for %s steps" % actionLimit)

        actionCounter = 0
        actionsBeforeCounterReset = 0

        currentApp = None
        targetApp = None
        applicationHitCounter = 0

        startTime = time.clock()

        if app != None:
            self.message('Running exit and starting application %s' % app)
            self.tc.exit()
            self.tc.navigate(app)
        else:
            self.tc.uiState.getCurrentState(refresh=True)

        while True:

            if self.settings.SelectSingleNode('//pause') != None:
                pause = self.settings.SelectSingleNode('//pause').GetAttribute('value')
                if pause.lower() == "true":
                    self.tc.capture()
                    self.message("Execution paused. Change 'pause' value from settings xml to continue..")
                    while pause.lower() == "true":
                        self.tc.delay(2000, False)
                        self.__loadConfiguration()
                        pause = self.settings.SelectSingleNode('//pause').GetAttribute('value')

            if self.__checkTriggers():
                self.__executeDelay()
                self.tc.uiState.getCurrentState(refresh=True)
                
            targetNode = None
            monkeyTarget = None
            action = None
            command = None
            
            if currentApp != None:

                # ntf-drawer or notify apps does not affect on the current application counter. evo-home does not count
                if (currentApp == self.tc.uiState.currentApplication or self.tc.uiState.currentApplication == 'ntf-drawer' or self.tc.uiState.currentApplication == 'notify') and (currentApp != 'evo-home'):

                    applicationHitCounter += 1 # count how many hits for current application there is

                    if app == None:

                        if self.settings.SelectSingleNode('//applicationactionlimit') != None:

                            if applicationHitCounter > int(self.settings.SelectSingleNode('//applicationactionlimit').GetAttribute('value')) and int(self.settings.SelectSingleNode('//applicationactionlimit').GetAttribute('value')) != 0:

                                self.message("Action limit for this application reached. Exit.")
                                command = "exit()"
                                self.__executeStringCommand(command)
                                continue

                else:
                    if app != None: # if testing specific application, we have gone out from it. try getting back.
                        self.message("Application has changed (%s -> %s) Trying back press.." % (targetApp, self.tc.uiState.currentApplication))
                        self.tc.select('KBD_KEY_BACK')
                        self.tc.delay(1000)
                        self.tc.uiState.getCurrentState(refresh=True)
                        if self.tc.uiState.currentApplication != targetApp:
                            self.message("Could not get back to target application (%s). Exit and navigate." % app)
                            self.tc.exit()
                            self.tc.navigate(app)
                            self.tc.uiState.getCurrentState(refresh=True)
                        
                    else: 
                        currentApp = self.tc.uiState.currentApplication
                        applicationHitCounter = 0
            else:
                currentApp = self.tc.uiState.currentApplication
                applicationHitCounter = 1
                if app != None: # if testing only one application, save the application name on first round
                    targetApp = currentApp

            # get monkeyTarget and action for it
            for i in range(int(self.settings.SelectSingleNode('//gettargetattemps').GetAttribute('value'))): # try getting targetNode and actions few times
                
                monkeyTarget = self.__getTarget()

                if monkeyTarget and monkeyTarget.monkeyTargetType == MonkeyTarget.TYPE_UIOBJECT:
                    action = self.__getMonkeyAction(monkeyTarget)
                    # if all ok, break the loop
                    if action != None:
                        break

                elif monkeyTarget and monkeyTarget.monkeyTargetType == MonkeyTarget.TYPE_EVENT: # event type of monkey target
                    break

                # If no targetNode or no actions/target, wait a bit and get current state again
                self.__executeDelay(1000)
                try:
                    if currentApp == 'video-player': # in case it's videoplayer, try tapping screen to get items visible
                        self.message('Video player active and no targets available, trying tapping with coordinates')
                        self.__execute(['select'], (20,20))
                        #command = "select((20,20))"
                        #self.__executeStringCommand(command)
                        self.__executeDelay(100)

                    self.tc.uiState.getCurrentState(refresh=True)
                except:
                    self.broadcast("Failed to refresh the state!")
            
            if monkeyTarget != None and monkeyTarget.monkeyTargetType == MonkeyTarget.TYPE_EVENT:
                self.__executeEvent(monkeyTarget.method)

            elif monkeyTarget != None and action != None:

                try:
                    self.__execute(action, monkeyTarget.targetImageOrText)
                    self.__executeDelay()
                            
                except MonkeyException as e:
                    self.message('%s' % e.value)
                    pass # ignore MonkeyException for now
                except:
                    self.broadcast("Failed to execute (%s, %s)" % (action, monkeyTarget.targetImageOrText))
                    
                
            else: # if no actions are available, do either action from settings or default back-key press
                
                if self.settings.SelectSingleNode('//notargetsaction') != None:
                    command = self.settings.SelectSingleNode('//notargetsaction').GetAttribute('value')
                    if command == "":
                        command = "select('KBD_KEY_BACK')"
                    
                else:
                    command = "select('KBD_KEY_BACK')"

                if monkeyTarget:
                    self.message("No actions available for target (%s)" % (monkeyTarget.targetImageOrText))
                else:
                    self.message("No targets available")

                self.__executeStringCommand(command)
            # reload configuration
            self.__loadConfiguration()

            # if action limit has changed, zero counters and start again
            if self.reloadActionLimit and actionLimit != int(self.settings.SelectSingleNode('//monkeyactions').GetAttribute('value')):
                try:
                    actionLimit = int(self.settings.SelectSingleNode('//monkeyactions').GetAttribute('value'))
                    actionsBeforeCounterReset += actionCounter
                    actionCounter = 0
                    self.message("Action counter was reseted during execution. New target: %s" % actionLimit)
                except:
                    self.message("Could not read action limit from settings. Please check the setting.")
            
            actionCounter += 1

            # check if monkey testing can be finished
            if actionLimit != 0 and actionCounter >= actionLimit:
                self.message("Done testing (action limited). Actions in total %s" % str(actionCounter + actionsBeforeCounterReset))
                break
            elif time.clock() - startTime > forTime and forTime != 0:
                self.message("Done testing (time limited). Actions in total %s" % str(actionCounter + actionsBeforeCounterReset))
                break
            
            self.tc.uiState.getCurrentState(refresh=True) # refresh for next round

            #debug.brf('monkey targets %s' % len(MonkeyTarget.listMonkeyTargets.keys()))
            #debug.brf('monkey exceptions %s' % len(MonkeyException.listMonkeyExceptions.keys()))
            
        # end of execution

           