import core
from core import uitestcase


class ExampleTest(uitestcase.UITestCase):

    subarea = "Test subarea"
    feature = "Test feature"

    def takeCaptures(self):
        """Test case for taking captures

        @tcId Take captures
        """
        import time

        for i in range(5):
            time.sleep(1)
            self.capture()

    def testSelect(self):
        """

        @tcId Test selection
        """
        self.navigate('Settings')
        self.back()
        return
        self.select('Messaging')


    def testNavigate(self):
        """

        @tcId Test navigate
        """

        apps = ["Phone", "Messaging", "People",
                  "Gallery", "Music", "Store", "Calculator",
                  "Settings", "Downloads"]
        self.comment('Navigate to apps: %r' % apps)
        for i in range(len(apps)):

            self.navigate(apps[len(apps)-1-i])
            self.back()
