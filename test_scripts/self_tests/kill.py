import core
from core import uitestcase

class testBed(uitestcase.UITestCase):

    subarea = "Self tests"
    feature = "Kill tests"

    def testKill(self):
        """
        @tcId Kill
        """
        self.killHelper('self.kill()')

    def testKillForced(self):
        """
        @tcId Kill (forced)
        """
        self.killHelper('self.kill(forced=True)')

    def testKillSpecificApplication(self):
        """
        @tcId Kill specific application
        """
        self.killHelper('self.kill(app)', 'com.android.dialer')

    def testKillSpecificApplicationForced(self):
        """
        @tcId Kill specific application (forced)
        """
        self.killHelper('self.kill(app, True)', 'com.android.dialer')

    def testKillTopmost(self):
        """
        @tcId Kill topmost
        """
        self.killHelper('self.kill.topmost()')

    def testKillTopmostForced(self):
        """
        @tcId Kill topmost (forced)
        """
        self.killHelper('self.kill.topmost(True)')

    def killHelper(self, methodCall, app='com.android.settings'):
        """
        Helper method for testing kill commands.
        Launches an application and tries to shutdown it with given kill command.
        Fails the test case if application is left running.

        Parameters:
        methodCall  str     kill command to execute with exec
        app         str     application to launch and kill

        Returns None
        """

        self.comment('1. Launching ' + app)
        self.navigate.jump(app)
        if not self.ensureAppLaunch(app):
            self.fail('Could not launch ' + app)

        self.comment('2. Killing ' + app)
        appsBefore = set(self.device.getRunningPackages())
        exec(methodCall)
        if not self.ensureAppShutdown(app):
            self.fail('Could not shutdown ' + app)

        # Print all killed applications
        appsAfter = set(self.device.getRunningPackages())
        killedApps = ''
        for app in appsBefore:
            if app not in appsAfter:
                killedApps += app + ', '

        if killedApps:
            self.comment('Apps killed: ' + killedApps.rstrip(', '))

        # Print all started applications
        startedApps = ''
        for app in appsAfter:
            if app not in appsBefore:
                startedApps += app + ', '

        if startedApps:
            self.comment('Apps started: ' + startedApps.rstrip(', '))


    def ensureAppLaunch(self, app='com.android.settings'):
        """
        Ensures that given application is running (timeout = 5 sec.)

        Returns True if application is running otherwise False.
        """
        self.comment('Ensuring launch of ' + app)
        maxWait = 5000
        currentWait = 0
        while (not app in self.device.getRunningPackages() and currentWait < maxWait):
            currentWait += 500
            self.delay(500)

        return app in self.device.getRunningPackages()

    def ensureAppShutdown(self, app='com.android.settings'):
        """
        Ensures that given application is not running (timeout = 5 sec.)

        Returns True if application is not running otherwise False.
        """
        self.comment('Ensuring shutdown of ' + app)
        maxWait = 5000
        currentWait = 0
        while (app in self.device.getRunningPackages() and currentWait < maxWait):
            currentWait += 500
            self.delay(500)

        return not app in self.device.getRunningPackages()