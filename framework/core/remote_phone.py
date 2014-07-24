"""FW <-> Remote phone controller module.

   Contains functions for controlling the remote phone.
"""
import core, types

from core.testcase_exceptions import RemotePhoneException, SkipTestException
from core.leader import needsEvaluation

import clr
clr.AddReference('System')
from System import Collections
from System.Collections.Generic import Dictionary, List

class RemotePhoneManager(object):
    """ Manager-class for remote phones

    """

    def __init__(self):
        from core import remote_phone

        self.remoteConnStrings = []
        self.__remotePhones = []
        self.currentTc = None

        remote_phone.remotePhone = self

        if core.FW_conf['settings'].Remote.Connection:
            self.remoteConnStrings.append(core.FW_conf['settings'].Remote)
            
            try:
                i = 2
                while 1: # Break with exception or when connection is empty
                    remoteConn = eval("core.FW_conf['settings'].Remote%s"%i)
                    if not remoteConn.Connection:
                        break
                    self.remoteConnStrings.append(remoteConn)
                    i += 1
            except Exception, e:
                pass

    def connect(self):
        """ Connect all remote phones at once

        """
        # import NGPhone only when needed, because it will import then all lower level NG phone connection modules
        if self.remoteConnStrings:
            from core.ng_phone import NGPhone

        i = 1
        for connString in self.remoteConnStrings:
            remotePhone = NGPhone(connString)
            remotePhone.setName("Remote%s"%i)
            self.append(remotePhone)
            remotePhone.createConnection()
            i +=1


    def __call__(self, funcName, *args, **kwargs):
        """ Access first remote phone directly by calling manager instance.
        
            parameters:
                funcName : name of the method in remote_phone-module to be called
        
        """
        if not len(self.__remotePhones):
            raise SkipTestException('Remote phone not found!')

        return self.__remotePhones[0](funcName, *args, **kwargs)

    def __len__(self):
        """ Add support for len()-call"""
        return len(self.__remotePhones)

    def __iter__(self):
        return self.__remotePhones

    def __getitem__(self, key):
        """ Add support for accessing remote phone instances by using indexes."""
        assert isinstance(key, int) and key > 0, 'Remote phone index must be above zero!'

        # minus one so that we use correct indexes
        key = key-1

        if key>len(self.__remotePhones)-1:
            raise SkipTestException('Remote phone %s not found!'%(key+1))

        return self.__remotePhones[key]

    def ___setitem__(self, key, value):
        """ Add support for setting remote phone instance by using index"""
        self.__remotePhones[key] = value

    def __delitem__(self, key):
        """ Add support for deleting items"""
        self.__remotePhones.pop(key)

    def __wrapper(self, attr, *args, **kw):
        """ wraps the remote calls in a callable class 
            so leader can get the arguments
        """

        class wrapper(object):
            def __init__(self, outside):
                self.wrapped = outside
                self.call_chain = []
                self.call_chain2 = []
        
            def __call__(self, *args, **kwargs):
                debug.out('Remote wrapped call chain: %s, args: %s, kwargs %s' % (self.call_chain, args, kwargs))

                followerArgs = List[object]()
                for a in args:
                    if type(a) == types.TupleType: # tuples cannot be serialized over wcf, pass them as string
                        followerArgs.Add(str(a))
                    else:
                        followerArgs.Add(a)
                
                arglist = followerArgs
                kwdict = Dictionary[object, object](kwargs)
                argEvalIndex = List[int]()
                kwargEvalIndex = List[int]()

                # check arguments which needs to be evaluated in follower. array will contain index numbers of to-be-evaluated args
                for i in range(len(args)):
                    ret = needsEvaluation(args[i])
                    if ret and ret[1]:
                        debug.brf('Parameter %s will be evaluated in Follower' % ret[1])
                        argEvalIndex.Add(i)
                        arglist[i] = ret[1]
                
                for i in range(len(kwargs)):
                    ret = needsEvaluation(kwargs.values()[i])
                    if ret and ret[1]:
                        debug.brf('Keyword parameter %s will be evaluated in Follower' % ret[1])
                        kwargEvalIndex.Add(i)
                        kwdict[k] = ret[1]

                core.FW_conf['leader'].currentTestStep = 'self.remote.' + '.'.join(self.call_chain) + '(%s, %s)' % (args, kwargs)
                core.FW_conf['leader'].RemotePhoneExecute('.'.join(self.call_chain), arglist, argEvalIndex, kwdict, kwargEvalIndex, core.FW_conf['settings'].TestRun.EvaluateSettings)

                return self.call_chain2[-1](*args, **kwargs)
                        
            def __getattr__(self, attr):
                r = wrapper(self)
                r.call_chain = self.call_chain
                r.call_chain.append(attr)
                r.call_chain2 = self.call_chain2
                r.call_chain2.append( getattr(r.call_chain2[-1], attr) )
                return r
                
        r = wrapper(self)
        r.call_chain.append(attr)
        r.call_chain2.append( self.__remotePhones[0].__getattribute__(attr) ) 
        return r

    def __getattr__(self, attr, *args, **kwargs):
        """ Create access to first remote phone instance"""
        if not attr in dir(self):
            if len(self.__remotePhones):
                if core.FW_conf['settings'].TestRun.ExecutionMode == 'Leader': # Leader mode will send the remote method/parameters to follower, create wrapper
                    return self.__wrapper(attr, *args, **kwargs)
                else:
                    return self.__remotePhones[0].__getattribute__(attr)
            else:
                raise RemotePhoneException('No remote phones found.')
        else:
            return getattr(self, attr)

    def append(self, item):
        self.__remotePhones.append(item)

    def __contains__(self, item):
        return self.__remotePhones.__contains__(item)
    
    def index(self, item):
        return self.__remotePhones.index(item)

    def closeConnections(self, forced = False):
        for remote in self.__remotePhones:

            remote.closeConnection(forced)

    def setResult(self, result):
        """ Set result instance to all remote phones

        """
        for remote in self.__remotePhones:
            remote.setResult(result)

    def setupRemotePhonesForUITesting(self):
        """ Call helper for all remote phones"""
        for remote in self.__remotePhones:
            remote.setupPhoneForUITesting()

remotePhone = None