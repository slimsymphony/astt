"""Initialization file for settings_data."""
import os
settings_data_path = __path__[0]

test_set_template_name = os.path.abspath( \
            os.path.join(settings_data_path, 'testset_template.xml'))
