# -*- coding: utf-8 -*-
"""Middleware Test Case module.

    Utility functions and a base class to be used in middleware test cases.
"""

# ============================================================================
# Module Setup

import core, middlewaretestcase
from core.testcase import TestCase


# ============================================================================
class MiddlewareTestCase(TestCase):
# ----------------------------------------------------------------------------
    """Common base class for middleware test scripts.
    """
    def __init__(self, methodName = None, tcId = ""):
        TestCase.__init__(self, methodName, tcId)
        self.__testStepNameIndex = 1
        self.__captureNameIndex = 1

    def _setUp(self):
        """Setup step called before a middleware test case is run.

            This method does not activate the Granite server so that test 
            scripts for e.g. engine sw can be run.
        """
        TestCase._setUp(self, graniteServerEnabled=False)


    def _tearDown(self):
        """Steps which are executed after middleware test case run."""
        TestCase._tearDown(self)
        