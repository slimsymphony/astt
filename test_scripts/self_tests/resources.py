import core
from core import uitestcase

class testBed(uitestcase.UITestCase):

    subarea = "Self tests"
    feature = "Resources tests"

    def testResources(self):
        """
        @tcId Resources
        """
        self.comment('Step 1. Trying to find a resource')
        self.comment(resources('README.txt'))

    def testResourcesSubDirectory(self):
        """
        @tcId Resources sub directory
        """
        self.comment('Step 1. Trying to find a resource from a sub directory')
        self.comment(resources('capture.png'))

    def testResourcesNotFound(self):
        """
        @tcId Resources not found
        """
        self.comment('Step 1. Trying to find non existing resource')
        passed = False
        try:
            resources('NonExistingResource.empty')
        except IOError as err:
            if err.errno != 2:
                raise err
            else:
                self.comment('Resources command failed accordingly')
                passed = True

        if not passed:
            self.fail('Resources did not fail although the resource was not found')

    def testResourcesDoNotFail(self):
        """
        @tcId Resources do not fail
        """
        self.comment('Step 1. Trying to find non existing resource with failOnError=False')
        result = resources('NonExistingResource.empty', failOnError=False)
        self.comment('Resources command returned: %s' % result)