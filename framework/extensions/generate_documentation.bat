ECHO OFF
cd epydoc
python.exe epydoc/cli.py -q --parse-only --docformat restructuredtext ..\..\%1 -o ..\..\%1_doc