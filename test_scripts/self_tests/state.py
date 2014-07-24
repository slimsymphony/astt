import core
from core import uitestcase

class testBed(uitestcase.UITestCase):

    subarea = "Self tests"
    feature = "State tests"

    def testState(self):
        """
        @tcId State
        """
        self.comment('Step 1. Test current state')
        currentState = self.state()
        self.comment('Current state is ' + currentState)
        if not currentState:
            self.fail('Failed to get current state from the phone')
        if currentState != 'com.nokia.homescreen':
            self.fail('Current state not com.nokia.homescreen')

        self.comment('Step 2. Test few other states')
        states = ['Alarms', 'Calculator', 'Phone', 'Music']
        for state in states:
            self.navigate.jump(state)
            currentState = self.state.get()
            if not currentState:
                self.fail('Failed to get current state from the phone (%s)' % state)

    def testStateInMainMenu(self):
        """
        @tcId State inMainMenu
        """
        self.comment('Step 1. Test success')
        if not self.state.inMainMenu():
            self.fail('Phone not in main menu. Current state is ' + self.state())

        self.comment('Step 2. Test not success')
        self.navigate.jump('Alarms')
        if self.state.inMainMenu():
            self.fail('Current state is %s but inMainMenu() returns True' % self.state())