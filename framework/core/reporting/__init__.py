"""Initialization file for core/reporting."""
import os

reporting_path = __path__[0]
XSLT_FOLDER = os.path.join(reporting_path, 'xslt')

DATA_FOLDER = os.path.join(reporting_path, 'bindata')

pretty_printing_xslt_path = \
                        os.path.join(XSLT_FOLDER, 'prettyprint.xslt')