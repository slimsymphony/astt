import core, random
from core import uitestcase, debug

class testBed(uitestcase.UITestCase):

    subarea = "GUI tests"
    feature = "All cases"

    def printPhonenumbers(self):
        """
        @tcId Print phone numbers
        """
        debug.brf(self.settings.Main.SIM1PhoneNumber)
        debug.brf(self.settings.Main.SIM2PhoneNumber)

    def failCase(self):
        """
        @tcId Fails case
        """
        self.fail('Fail')

    def errorCase(self):
        """
        @tcId Error case
        """
        kissa = 1 / 0

    def randomCase(self):
        """
        @tcId Random result
        """
        random.seed()
        value = random.randint(0, 2)
        if value == 0:
            return
        elif value == 1:
            self.fail('Fail')
        elif value == 2:
            error = 1 / 0

    def emptyCase1(self):
        """
        @tcId Empty 1
        """
        pass

    def emptyCase2(self):
        """
        @tcId Empty 2
        """
        pass

    def emptyCase3(self):
        """
        @tcId Empty 3
        """
        pass

    def emptyCase4(self):
        """
        @tcId Empty 4
        """
        pass
