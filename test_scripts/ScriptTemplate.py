#!/usr/bin/python
# -*- coding: utf-8 -*-
import core
from core import uitestcase

class InsertTestClassNameHere(uitestcase.UITestCase):

    subarea = "Insert Feature Group Here"
    feature = "Insert Feature Here"

    def setUp(self):
        """ Insert brief description of the setup logic."""
        # Insert code to perform pre-condition steps

    def tearDown(self):
        """ Insert brief description of the teardown logic."""
        # Insert code to perform clean up operations

    def InsertTestMethodNameHere(self):
        """ Insert brief description of the test case

        1. Insert test step description here
        2. Insert test step description here
        3. Insert test step description here

        @tcId Insert test case name here
        """
        self.comment('Step1: Insert test step description')
        # Insert code to perform the first test step

        self.comment('Step2: Insert test step description')
        # Insert code to perform the second test step

        self.comment('Step3: Insert test step description')
        # Insert code to perform the third test step

    def InsertTestMethod2NameHere(self):
        """ Insert brief description of the second test case

        1. Insert test steps here

        @tcId Insert name of the second test case here
        """
        # Insert code to execute steps of the second test case