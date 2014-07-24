#!/usr/bin/python
# -*- coding: utf-8 -*-
import core
from core import uitestcase

class InsertTestClassNameHere(uitestcase.UITestCase):

    subarea = "Insert Feature Group Here"
    feature = "Insert Feature Here"

    def InsertTestMethodNameHere(self):
        """ Insert brief description of the test case
        
        @tcId Insert test case name here
        """
        self.comment('Step1: Insert test step description')
        # Insert code to perform the first test step