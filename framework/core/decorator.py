import os, json, fnmatch, imp, time
from core.testcase_exceptions import StopTestException

functions = {}

def checkConfigurations(phone):
    """ Check that configurations are unambiguous."""
    phoneInfo = phone.deviceInfo(doNotReport = True)

    profilesDir = os.path.abspath(os.path.join(os.path.curdir, "..\\profiles\\"))
    profiles = [os.path.join(dirpath, f)
        for dirpath, dirnames, files in os.walk(profilesDir)
        for f in fnmatch.filter(files, '*profile*.json')]

    foundDirs = []
    for profile in profiles:
        pr = json.load(open(profile))
        for conf in pr:
            if len(conf.items()):
                shared_items = set(phoneInfo.items()) & set(conf.items())
                if len(shared_items) == len(conf.items()):
                    foundDirs.append(os.path.split(profile)[0])
    if len(foundDirs) == 1:
        return True
    elif len(foundDirs) > 1:
        commonPath = os.path.abspath(os.path.commonprefix(foundDirs))
        if len(commonPath) == len(profilesDir):
            message = "Several UI styles match the phone info: "
            message += ', '.join(foundDirs)
            raise AssertionError(message)
        else:
            return True
    else:
        debug.brf('No profiles found for connected device, using defaults.')
        # Do not raise exception if default methods are taken in use!
        #raise AssertionError("No matching UI styles for the phone found")

def override(func):
    global functions

    def overrideResolver(*args,**kwargs):
        #t = time.time()
        # Resolve correct profile
        phone = args[0].phone
        phoneInfo = phone.deviceInfo(doNotReport = True)

        profilesDir = os.path.abspath(os.path.join(os.path.curdir, "..\\profiles\\"))
        profiles = [os.path.join(dirpath, f)
            for dirpath, dirnames, files in os.walk(profilesDir)
            for f in fnmatch.filter(files, '*profile*.json')]

        foundDirs = []
        for profile in profiles:
            #debug.brf('profile %s' % profile)
            pr = json.load(open(profile))
            for conf in pr:
                #debug.brf('conf %s' % conf)
                if len(conf.items()):
                    shared_items = set(phoneInfo.items()) & set(conf.items())
                    if len(shared_items) == len(conf.items()):
                        #debug.brf('appending %s' % os.path.split(profile)[0])
                        foundDirs.append(os.path.split(profile)[0])

        # Import package and cache function
        funcName = func.func_name
        funcClass = args[0].__class__.__name__
        fullFuncName = funcClass + "." + funcName

        if not fullFuncName in functions.keys():
            if len(foundDirs) == 1:
                #debug.brf('loading funcClass: %s' % funcClass)
                if os.path.exists(os.path.join(foundDirs[0], funcClass) + ".py"):
                    try:
                        funcPackage = imp.load_source(foundDirs[0].replace(profilesDir,"").replace(os.sep, ".").lstrip(".") + "." + funcClass.lower(), \
                            os.path.join(foundDirs[0], funcClass) + ".py")
                    except Exception as ex:
                        raise AssertionError("Cannot load module: %s type(%s)" % (ex.message, type(ex)))
                    else:
                        if getattr(funcPackage,funcClass, False):
                            function = getattr(getattr(funcPackage,funcClass),funcName, False)
                            if function:
                                functions[fullFuncName] = function
            elif len(foundDirs) > 1:
                # Several directories found
                #debug.brf('found directories %s' % str(foundDirs))
                packages = []
                for d in foundDirs:
                    if os.path.exists(os.path.join(d, funcClass) + ".py"):
                        funcPackage = imp.load_source(d.replace(profilesDir,"").replace(os.sep, ".").lstrip(".") + "." + funcClass.lower(), \
                            os.path.join(d, funcClass) + ".py")
                        if getattr(funcPackage,funcClass, False):
                            function = getattr(getattr(funcPackage,funcClass),funcName, False)
                            if function:
                                packages.append(function)
                if len(packages) != 1:
                    if len(packages) > 1: raise AssertionError("Too many possible profiles found! Check profiles from %s"%str(foundDirs))
                    else: 
                        pass
                        # raise AssertionError("No profiles found!") # Do not raise exception if default methods are taken in use!
                else:
                    functions[fullFuncName] = packages[0]
            else:
                # Do not raise exception if default methods are taken in use!
                #raise AssertionError("No profiles found!")
                pass
                
        #else:
        #    debug.brf("Using cached function")

        #debug.brf('override resolve took %s' % str(time.time() - t))
        # Execute function
        if not functions.has_key(fullFuncName):
            #debug.brf("Override not found for %s.%s. Using default!"%(funcClass,funcName))
            return func(*args,**kwargs)
        else:
            #debug.brf("Using overridden version of %s.%s"%(funcClass,funcName))
            return functions[fullFuncName](*args,**kwargs)

    return overrideResolver

