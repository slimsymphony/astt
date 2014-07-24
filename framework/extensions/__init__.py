"""External utilities and enhancements to standard Python distribution.

    This package contains extension packages and modules for the standard
    Python distribution. To avoid the installation need, the module modifies
    the sys.path to include absolute path.
"""
import sys, os.path

import core

extensionsPath = os.path.join(core.FW_conf['startup_path'], 'extensions')

# Make sure the extensions is part of the sys.path
if not extensionsPath in sys.path:
    sys.path.insert(0, extensionsPath)
