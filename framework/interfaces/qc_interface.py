import clr

clr.AddReference("GraniteQCIntegration")

from Nokia.Granite.QC import GraniteQCInterface
from core.testcase_exceptions import TestException

class QCInterface(object):

    qcAddressess = {'Training database' : "https://qc11qa.nokia.com/qcbin/",
                    'Production database' : "https://qc11.nokia.com/qcbin/"}

    CICredentials = {
                     'username':'qc_alm_granite',
                     'password':'yf!g2)4%[A><suh;'
                    }

    def __init__(self):
        """ """
        self.qcInterface = None
        self.username = ""
        self.password = ""
    
    def connect(self, url, username=None,password=None):
        """ """
        self.qcInterface = GraniteQCInterface()

        if username and password:
            self.username = username
            self.password = password
        else:
            self.username = self.CICredentials['username']
            self.password = self.CICredentials['password']

        try:
            return self.qcInterface.Authenticate(self.username,self.password,self.qcAddressess[url])
        except Exception,e:
            return e

    def getTestSet(self, domain,project,testSetId,path):
        """ """
        graniteTestSet = self.qcInterface.GetTestSet(domain,project,testSetId,path)
        if graniteTestSet:
            self.qcInterface.LogOut()
            return graniteTestSet
        else:
            raise TestException("Empty test set generated from QC/ALM!")

    def sendResults(self, testSetPath):
        return self.qcInterface.SendResults(testSetPath, self.username, self.password)
