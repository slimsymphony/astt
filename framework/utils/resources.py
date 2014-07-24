"""Provides access to resources used in test scripts. """
import os
import errno

class Resources(object):
    """Resources provider class."""
    def __init__(self):
        """Initialization"""
        self.__scriptFolder = ''

    def __call__(self, resourceName, failOnError = True):
        """Returns file path of given resource.

            Parameters

            resourceName            resource name in string
            failOnError             whether Exception will be thrown if resource is not found
                                    (default = True)

            Returns file path if found, otherwise empty string.
        """
        filePath = self.__scriptFolder

        if self.__scriptFolder and os.path.isdir(self.__scriptFolder):
            while True:
                for fileObject in os.listdir(filePath):
                    fileObjectPath = os.path.join(filePath, fileObject)

                    if fileObject == 'resources' and os.path.isdir(fileObjectPath):
                        for directory, folder, files in os.walk(fileObjectPath):
                            if resourceName in files:
                                # resource found --> return full absolute path
                                resourcePath = os.path.normpath(os.path.join(directory, resourceName))
                                debug.brf('Using resource: %s' % resourcePath)

                                return resourcePath

                newFilePath = os.path.split(filePath)[0]

                if newFilePath != filePath:
                    filePath = newFilePath
                else:
                    break

        if failOnError:
            # not found --> raise IOError with ENOENT = No such file or directory
            raise IOError(errno.ENOENT,'Could not find resource: %s' % resourceName, resourceName)
        else:
            return ''

    def _setScriptFolder(self, scriptFolder):
        """Sets test script folder where resource finding will be started from."""
        self.__scriptFolder = scriptFolder

