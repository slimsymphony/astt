import core
import time, sys, os

import smtplib
from email.mime.text import MIMEText

import clr
clr.AddReference('System')
from System.Net import Dns

class EmailSender(object):
    def __init__(self):
        pass

    def sendEmail(self, message, subject):
        """ send e-mail to users defined in TestRun settings """ 

        recipients = []
        for i in core.FW_conf['settings'].TestRun.UserInformation.split(','):
            recipients.append(i.strip())
        
        if len(recipients) > 0:    
            msg = MIMEText(str(message))
            msg['To'] = core.FW_conf['settings'].TestRun.UserInformation
            msg['X-Priority'] = '1'
            _from = 'test.automation.robot@nokia.com'
            
            msg['From'] = _from
            try:
                msg['Subject'] = Dns.GetHostName() + ': ' + subject
            except:
                msg['Subject'] = subject
        
            try:
                s = smtplib.SMTP('smtp.nokia.com')
                debug.brf('Sending e-mail from %s to %s' % (_from, (recipients,)))
                s.sendmail(_from, recipients, msg.as_string() )
                s.quit()
            except Exception as e:
                debug.brf('e-mail sending failed: exception %s' % e.message)
        else:
            debug.brf('no recipients defined')

    def holdExecutionAndSendMail(self, message, subject=''):
        """ send e-mail to test engineer and hold the execution """ 

        lockfile = os.path.abspath(os.path.join(os.path.curdir, r'..\marble_lock.txt'))
        core.FW_conf['connection'].comment(str(message))

        msg = message + ". " + "Please remove lock file %s to continue the execution" % lockfile
        self.sendEmail(msg, subject)

        try:
            f = open(lockfile, 'w')
            f.close()
            core.FW_conf['connection'].comment('Execution is on pause. Remove the lockfile %s to continue' % lockfile)
        except:
            debug.err('Error, cannot pause the execution!')

        if core.FW_conf['settings'].TestRun.ExecutionMode == 'Leader':
            core.FW_conf['leader'].StopTest() # stop follower executions

        while True:
            core.FW_conf['connection'].sendWaitMessageToMarbleGUI(1, 'Test execution sleeping for 1 seconds')
            if not os.path.isfile(lockfile):
                return
            else:
                if core.FW_conf['should_stop']:
                    return
                time.sleep(1)
                