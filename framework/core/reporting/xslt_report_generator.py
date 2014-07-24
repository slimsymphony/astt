# ============================================================================
#                            XSLT Test Report Generator
#                            --------------------------
# ----------------------------------------------------------------------------

# ============================================================================
#   1   ABSTRACT
#
#   1.1 Module type
#
#       Test utility
#
#   1.2 Description
#
#       This module implements necessary classes to convert ART testresult or
#       GUI testset XML to human-readable HTML using provided XSL templates
#       for conversion.
#
#   1.3 Notes
#
#       This module uses MSXML engine to create HTML reports.
#
#       The test report can be generated in three different modes,
#       in a tester, developer and merge modes. The tester and merge modes
#       are intended for testing usage, developer mode is intended for test
#       case developers.
#
#       For stylesheet development, use 4xslt.exe to transform stylesheets
#       manually since 4xslt reports error much better than MSXML 4.0.
#
#       e.g.
#           4xslt common_automated_frt.xml test_report_xml_to_html.xslt
#       ***
#
#       For information about XML, XSLT, DOM and transforming, see
#       MSXML SDK documentation files (windows help format).
#
# ----------------------------------------------------------------------------

# ============================================================================
#   2   CONTENT
#
#       1   ABSTRACT
#       1.1 Module type
#       1.2 Description
#       1.3 Notes
#
#       2   CONTENT
#
#       3   MODULE CODE
#       3.1 Module initialization
#       3.2 XSLTTestReportGeneratorException class
#       3.4 XSLTTestReportGenerator class
#       3.5 Command-line utility code
#
# ----------------------------------------------------------------------------


# ============================================================================
#   3   MODULE CODE
# ----------------------------------------------------------------------------

# ----------------------------------------------------------------------------
#       3.1 Module initialization
# ----------------------------------------------------------------------------
import os, sys, shutil, traceback, getopt, time, types

import core

if __name__ == '__main__':
    # append dll path when running standalone
    sys.path.append(os.path.join(os.path.split(os.path.dirname(core.__file__))[0], 'dlls'))

from utils.nodeutils import NodeUtils
from utils.file_utils import updateFile, getFileList, filterValidFilename, filterValidPath
from core.reporting import XSLT_FOLDER, DATA_FOLDER
from core.settings.settings_data import test_set_template_name

commonFiles = ['test_report_xml_to_html.xslt',
               'test_report_xml_to_html_utility.xslt',
               'test_report_xml_to_html_case_properties.xslt',
               'test_report_xml_to_html_case_details.xslt',
               'test_report_javascript.xslt',
               'test_report_style_sheet.xslt',
               'test_report_xml_highlight.xslt']

memLeakFiles = ['mem_leak_xml_to_html.xslt', 'test_report_memleak_main.xslt']

commonDataFiles = ['arrow_ascending.gif', 'arrow_descending.gif',
 'memoryleak_logo.jpg', 'headerbg.jpg', 'headerbg_top.jpg','backgr.jpg', 'backgrtop.jpg','dl.gif']

commonDocs = \
    {
    'test_report_common_script.js': {
        'style-sheet':  'test_report_stylesheets.xslt',
        'parameters':   lambda test_run: {
            'testrun':          str(test_run),
            'startMode':        'common_script',
            'transformFlag':    'single-testcase',
            'transformMode':    'framed-report'
            },
        'folder-path':  lambda root_folder:
            os.path.join(root_folder, 'script'),
        'file-name':    lambda test_run:
            'test_report_common_script.js'
        },
    'test_report_left_frame_script.js': {
        'style-sheet':  'test_report_stylesheets.xslt',
        'parameters':   lambda test_run: {
            'testrun':          str(test_run),
            'startMode':        'left_frame_script',
            'transformFlag':    'single-testcase',
            'transformMode':    'framed-report'
            },
        'folder-path':  lambda root_folder:
            os.path.join(root_folder, 'script'),
        'file-name':    lambda test_run:
            'test_report_left_frame_script.js'
        },
    'test_report_activex_wrapper_script.js': {
        'style-sheet':  'test_report_stylesheets.xslt',
        'parameters':   lambda test_run: {
            'testrun':          str(test_run),
            'startMode':        'activex_wrapper_script',
            'transformFlag':    'single-testcase',
            'transformMode':    'framed-report'
            },
        'folder-path':  lambda root_folder:
            os.path.join(root_folder, 'script'),
        'file-name':    lambda test_run:
            'test_report_activex_wrapper_script.js'
        },
    'test_report_activex_wrapper_script_x.js': {
        'style-sheet':  'test_report_stylesheets.xslt',
        'parameters':   lambda test_run: {
            'testrun':          str(test_run),
            'startMode':        'activex_wrapper_script',
            'transformFlag':    'single-testcase',
            'transformMode':    'frameless-report'
            },
        'folder-path':  lambda root_folder:
            os.path.join(root_folder, 'script'),
        'file-name':    lambda test_run:
            'test_report_activex_wrapper_script_x.js'
        },
    'test_report_common_style.css': {
        'style-sheet':  'test_report_stylesheets.xslt',
        'parameters':   lambda test_run: {
            'startMode':        'common_style'
            },
        'folder-path':  lambda root_folder:
            os.path.join(root_folder, 'style'),
        'file-name':    lambda test_run:
            'test_report_common_style.css'
        },
    'test_report_frames_style.css': {
        'style-sheet':  'test_report_stylesheets.xslt',
        'parameters':   lambda test_run: {
            'startMode':        'frames_style'
            },
        'folder-path':  lambda root_folder:
            os.path.join(root_folder, 'style'),
        'file-name':    lambda test_run:
            'test_report_frames_style.css'
        },
    'test_report_memleak_style.css': {
        'style-sheet':  'test_report_stylesheets.xslt',
        'parameters':   lambda test_run: {
            'startMode':        'memleak_style'
            },
        'folder-path':  lambda root_folder:
            os.path.join(root_folder, 'style'),
        'file-name':    lambda test_run:
            'test_report_memleak_style.css'
        }
    }

specificDocs = \
    {
    'test_report_main.html':
        {
        'style-sheet':  'test_report_stylesheets.xslt',
        'parameters':   lambda test_run: {
            'testrun':          str(test_run),
            'startMode':        'main_frame'
            },
        'folder-path':  lambda root_folder: root_folder,
        'file-name':    lambda test_run:
            'test_report_main%s.html' % \
                (test_run > 1 and '_' + str(test_run) or '')
        },
    'test_report_left_frame.html':
        {
        'style-sheet':  'test_report_stylesheets.xslt',
        'parameters':   lambda test_run: {
            'testrun':          str(test_run),
            'startMode':        'left_frame'
            },
        'folder-path':  lambda root_folder:
            os.path.join(root_folder, 'html'),
        'file-name':    lambda test_run:
            'test_report_left_frame%s.html' % \
                (test_run > 1 and '_' + str(test_run) or '')
        },
    'test_report_summary.html':
        {
        'style-sheet':  'test_report_xml_to_html_summary.xslt',
        'parameters':   lambda test_run: {
            'test_run':         str(test_run)
            },
        'folder-path':  lambda root_folder:
            os.path.join(root_folder, 'html'),
        'file-name':    lambda test_run:
            'test_report_summary%s.html' % \
                (test_run > 1 and '_' + str(test_run) or '')
        },
    'test_report_testcase_array.js':
        {
        'style-sheet':  'test_report_stylesheets.xslt',
        'parameters':   lambda test_run: {
            'testrun':          str(test_run),
            'startMode':        'testcase_array'
            },
        'folder-path':  lambda root_folder:
            os.path.join(root_folder, 'script'),
        'file-name':    lambda test_run:
            'test_report_testcase_array%s.js' % \
                (test_run > 1 and '_' + str(test_run) or '')
        },
    }

# ----------------------------------------------------------------------------
#       3.2 XSLTTestReportGeneratorException class
# ----------------------------------------------------------------------------
class XSLTTestReportGeneratorException(Exception):
    """Exception class for XSLT test report generation exceptions.
    """
    def __init__(self, errorString = None):
        Exception.__init__(self)
        if errorString:
            self._errorString = errorString
        else:
            et, ev, tb = sys.exc_info()
            self._errorString = \
                            ''.join(traceback.format_exception(et, ev, None))

    def __unicode__(self):
        return '%s' % self._errorString

# ----------------------------------------------------------------------------
#       3.4 XSLTTestReportGenerator class
# ----------------------------------------------------------------------------
class XSLTTestReportGenerator:
    """
    Transforms test report XML to human-readable HTML using
    MSXML 4.0 XSLT transform engine.

    Calls to MSXML 4.0 are made through
    COM API, thus working Python win32 extensions are required.
    """
    def __init__(self):
        self.testRun = 1

    def createTempTestsetXML(self, source):
        """
        Create temporary GUI test set model instance to be used in
        XSLT transformations.

        Parameters:

            - source:
                list of detailed test result xml files

        Returns
            test set NodeUtils instance
        """
        hierarchyAttrs = {'failed'      : "0",
                         'na'          : "0",
                         'noresult'    : "0",
                         'norun'       : "0",
                         'open'        : "True",
                         'passed'      : "0",
                        }

        testcaseAttrs = {'leak_run'     : "False",
                         'priority'     : "",
                         'repeats'      : "1",
                         'retest_on'    : "False",
                         'ucid'         : "",
                        }

        testscriptAttrs = {'class'     : "",
                           'directory' : "",
                           'file'      : "",
                           'method'    : "",
                          }

        testsetDoc = NodeUtils(test_set_template_name)

        for detailedReport in source:
            reportNode = NodeUtils(detailedReport)

            testcaseNode = reportNode.find('//testcase')

            # if test case node is not found, we can't process the result
            if not testcaseNode:
                continue

            subarea = testcaseNode.getAttribute('subarea')
            feature = testcaseNode.getAttribute('feature')

            # SUBAREA LEVEL
            subareaNode = testsetDoc.find('hierarchy[@name="%s"]' % subarea)

            if not subareaNode:
                subareaNode = NodeUtils('hierarchy', True)

                for key, value in hierarchyAttrs.iteritems():
                    subareaNode.setAttribute(key, value)

                subareaNode.setAttribute('name', subarea)

                subareaFound = False
            else:
                subareaFound = True

            # FEATURE LEVEL
            featureNode = subareaNode.find('hierarchy[@name="%s"]' % feature)

            if not featureNode:
                featureNode = NodeUtils('hierarchy', True)

                for key, value in hierarchyAttrs.iteritems():
                    featureNode.setAttribute(key, value)

                featureNode.setAttribute('name', feature)

                featureFound = False
            else:
                featureFound = True

            # TEST CASE LEVEL
            tcNode = NodeUtils('testcase', True)

            for key, value in testcaseAttrs.iteritems():
                tcNode.setAttribute(key, value)

            tcNode.setAttribute('name', testcaseNode.getAttribute('id'))

            # TEST SCRIPT LEVEL
            scriptNode = NodeUtils('art2testscript', True)

            for key, value in testscriptAttrs.iteritems():
                scriptNode.setAttribute(key, value)

            # TEST RESULT LEVEL
            resultNode = NodeUtils('art2testresult', True)
            resultNode.setAttribute('report_file', 'xml\%s' % os.path.split(detailedReport)[-1])
            resultNode.setAttribute('result', testcaseNode.getAttribute('result'))
            resultNode.setAttribute('test_type', 'UI Test')

            scriptNode.append(resultNode)
            tcNode.append(scriptNode)
            featureNode.append(tcNode)

            if not featureFound:
                subareaNode.append(featureNode)

            if not subareaFound:
                testsetDoc.append(subareaNode)

        return testsetDoc

    def getTargetPath(self, targetPath, fixedBase = None):
        """
        Returns folder path and file basename from given path.

        Parameters:

            - targetPath:
                file or folder path of the target.

            - fixedBase:
                Fixed basename.

        Return value:
            Folder path, file basename.
        """
        # Get absolute path.
        if not os.path.isabs(targetPath):
            targetPath = os.path.join(os.getcwd(), targetPath)

        targetPath = os.path.normpath(targetPath)
        baseName, extension = os.path.splitext(targetPath)

        if extension:
            folderPath = os.path.dirname(baseName)
            fileBase = os.path.basename(baseName)
        else:
            folderPath = baseName
            fileBase = fixedBase or "report_%s" % time.strftime("%Y-%m-%d")

        return folderPath, fileBase

    def createReport(self, source, targetPath):
        """ Wrapper for generating all XHTML reports.

        Parameters:

            - source:
                list of detailed test result xml files

            - targetPath:
                Absolute/relative file/folder path where files are saved.
        """
        folderPath, fileBase = self.getTargetPath(targetPath)

        # Transform to test result XML to GUI testset XML.
        testSetSource = self.createTempTestsetXML(source)

        self.setDetailedXMLsToTestSet(source, testSetSource, folderPath)

        # Copy common files.
        self.copyCommonFiles(folderPath)

        # Create specifiec test report files.
        self.createDocuments(testSetSource, folderPath, specificDocs, False)
        print "HTML report saved to %r." % folderPath

    def createDocuments(self, source, targetRoot, targetDocs, checkFile):
        """
        Common method for executing XML -> XHTML XSL transformations.

        Parameters:

            - source:
                MSXML DOM Document object of GUI testset XML.

            - targetRoot:
                Folder path where JavaScript files are saved.

            - targetDocs:
                Dictionary of files to be transformed.

            - checkFile:
                Boolean value to checked if file transformation is needs.
                - target file already existing
                - source and target meodification times are same
        """
        for document, parameters in targetDocs.items():
            # Get style sheet path.
            xsltPath = os.path.join(XSLT_FOLDER,
                                    parameters.get('style-sheet'))
            # Get target folder.
            targetFolder = parameters.get('folder-path')(targetRoot)
            # Create target folders.
            if not os.path.isdir(targetFolder):
                os.makedirs(targetFolder)
            # Get transform parameters.
            param = parameters.get('parameters')(self.testRun)
            # Get target filename.
            targetFile = parameters.get('file-name')(self.testRun)
            # Get target path.
            targetPath = os.path.join(targetFolder, targetFile)
            # Check file transforming/updating necessity.
            if checkFile:
                updateItem = updateFile(xsltPath, targetPath, False)
            else:
                updateItem = True
            # Transform/update files in necessary.
            if updateItem:
                # Transform JavaScript files.
                source.transform(styleSheet = xsltPath,
                                 targetFile = targetPath,
                                 **param)
                try:
                    # Copy file properties from assosiated XSLT file to
                    # transformed file.
                    shutil.copystat(xsltPath, targetPath)
                    # Change access permissions to read and write.
                    os.chmod(targetPath, 0666)
                except IOError, err:
                    raise XSLTTestReportGeneratorException( \
                        "Error in copying file properties: %s" % err)
                except OSError, err:
                    raise XSLTTestReportGeneratorException( \
                        "Error in changing access permissions: %s" % err)

    def copyCommonFiles(self, targetRoot = None):
        """
        Copies common(xslt, css, javascript) files under given 'targetRoot'
        location or 'C:\\Documents and Settings\\All Users\\.art2shared'
        folder.

        Parameters:

            - targetRoot:
                Root folder path of target location.
        """
        if not targetRoot:
            # Generate target root folder path.
            allUsers = os.getenv("HOMEPATH"). \
                                replace(os.getenv("USERNAME"), 'All Users')
            targetRoot = \
                os.path.join(os.getenv('HOMEDRIVE'), allUsers, '.art2shared')

        # Create absolute paths from hardcoded XSLT files.
        sourcePaths = [os.path.join(XSLT_FOLDER, item) for item in commonFiles]

        # Generate target subfolder paths.
        xsltTarget = os.path.join(targetRoot, 'xslt')

        # Create target folders if not already existing.
        if not os.path.isdir(xsltTarget):
            os.makedirs(xsltTarget)

        # Check modification times agains existing target files
        # and replace if it differs. Make a backup from the previous one.
        for sourcePath in sourcePaths:
            targetPath = \
                    os.path.join(xsltTarget, os.path.basename(sourcePath))
            updateFile(sourcePath, targetPath)
            # Change access permissions to read and write.
            os.chmod(targetPath, 0666)

        # Create common test report files.
        dummySource = NodeUtils('dummy', True)
        self.createDocuments(dummySource, targetRoot, commonDocs, True)

        dataTarget = os.path.join(targetRoot, 'data')

        # Create target folders if not already existing.
        if not os.path.isdir(dataTarget):
            os.makedirs(dataTarget)


        dataSourcePaths = [os.path.join(DATA_FOLDER, item) for item in commonDataFiles]
        for sourcePath in dataSourcePaths:
            targetPath = \
                    os.path.join(dataTarget, os.path.basename(sourcePath))
            updateFile(sourcePath, targetPath)
            # Change access permissions to read and write.
            os.chmod(targetPath, 0666)


    def copyMemLeakFiles(self, targetRoot = None):
        """
        Copies memory leak specific files under given 'targetRoot'
        location or 'C:\\Documents and Settings\\All Users\\.art2shared'
        folder.

        Parameters:

            - targetRoot:
                Root folder path of target location.
        """
        if not targetRoot:
            # Generate target root folder path.
            allUsers = os.getenv("HOMEPATH"). \
                                replace(os.getenv("USERNAME"), 'All Users')
            targetRoot = \
                os.path.join(os.getenv('HOMEDRIVE'), allUsers, '.art2shared')

        # Create absolute paths from hardcoded XSLT files.
        sourcePaths = [os.path.join(XSLT_FOLDER, item) for item in memLeakFiles]

        # Generate target subfolder paths.
        xsltTarget = os.path.join(targetRoot, 'xslt')

        # Create target folders if not already existing.
        if not os.path.isdir(xsltTarget):
            os.makedirs(xsltTarget)

        # Check modification times agains existing target files
        # and replace if it differs. Make a backup from the previous one.
        for sourcePath in sourcePaths:
            targetPath = \
                    os.path.join(xsltTarget, os.path.basename(sourcePath))
            updateFile(sourcePath, targetPath)
            # Change access permissions to read and write.
            os.chmod(targetPath, 0666)


    def setDetailedXMLsToTestSet(self, resultSource, guiSource, targetPath):
        """
        Set detailed xml file paths to test set.

        Parameters:

            - resultSource:
                list of detailed test result xml files

            - guiSource:
                MSXML DOM Document object of GUI testset XML.

            - targetPath:
                Absolute folder path where XML files are to be splitted.
        """
        # Create folder for splitted XML files.
        xmlFolder = os.path.join(targetPath, 'xml')
        if not os.path.isdir(xmlFolder):
            os.makedirs(xmlFolder)

        for detailedReport in resultSource:
            resultPath = 'xml/%s' % os.path.basename(detailedReport)

            reportNode = NodeUtils(detailedReport)
            testcaseNode = reportNode.find('/testreport/testcase')

            if testcaseNode:
                # Set report_file attribute value of GUI testset XML.
                oGuiResult = \
                    guiSource.find('/testset/hierarchy[@name="%s"]/hierarchy[@name="%s"]/testcase[@name="%s"]/art2testscript/art2testresult' % \
                        (testcaseNode.getAttribute("subarea"), testcaseNode.getAttribute("feature"), testcaseNode.getAttribute("id")))

                if oGuiResult:
                    # change from absolute to relative
                    oGuiResult.setAttribute("report_file", resultPath)
                else:
                    print 'ERROR: Report "%s" generating failed' % detailedReport


    def createMemLeakReport(self, source, target):
        """ Creates memory leak report """
        folderPath = getTargetPath(target)[0]

        # Copy common files.
        self.copyMemLeakFiles(folderPath)

        # Copy common files.
        self.copyCommonFiles(folderPath)


        xsltPath = os.path.join(XSLT_FOLDER,'test_report_memleak_main.xslt')
        updateItem = updateFile(xsltPath, target, False)
        # Set filename without .xml extension as a parameter to XSLT conversion
        xmlFilename = source.split('.xml')[0].split('\\')[-1]
        params = {'filename': xmlFilename}
        # Transform/update files in necessary.
        if updateItem:
            # Transform JavaScript files.
            #Use dummy XML-file
            dummySource = NodeUtils('dummy', True)
            dummySource.transform(styleSheet = xsltPath,
                             targetFile = target, **params)
            try:
                # Copy file properties from assosiated XSLT file to
                # transformed file.
                shutil.copystat(xsltPath, target)
                # Change access permissions to read and write.
                os.chmod(target, 0666)
            except IOError, err:
                raise XSLTTestReportGeneratorException( \
                    "Error in copying file properties: %s" % err)
            except OSError, err:
                raise XSLTTestReportGeneratorException( \
                    "Error in changing access permissions: %s" % err)

        print "Memory leak HTML report saved to %r." % folderPath


    def executeFromCLI(self):
        """ Parse Command line.
        """
        try:
            opts, args = getopt.getopt(sys.argv[1:], "ht:r:g:")
        except getopt.GetoptError, error:
            raise XSLTTestReportGeneratorException(error)

        options = dict(opts)

        # Print Command-line help.
        if options.has_key('-h'):
            self.printUsage()
            os._exit(1)

        # Parse arguments.
        if len(args) == 2:
            sourcePath, targetPath = args
        else:
            raise XSLTTestReportGeneratorException("Not enough arguments!")

        if len(sourcePath.split(';')) > 1:
            fileList = sourcePath.split(';')
        else:
            fileList = getFileList(sourcePath, fileExt = '.xml')

        if not fileList:
            raise XSLTTestReportGeneratorException("Cannot locate XML File(s)!")

        if len(fileList) == 1 and \
           fileList[0].split(';') > 1:
            source = fileList[0].split(';')
        else:
            source = fileList

        # remove generated folders from result dir if found
        try:
            for dirName in ['data', 'html', 'script', 'style', 'xslt']:
                removedDir = os.path.join(targetPath, dirName)
                if os.path.isdir(removedDir):
                    shutil.rmtree(removedDir)
        except Exception:
            print 'Unable to remove temporary files!'

        self.createReport(source, targetPath)

    def printUsage(self):
        """ Command-line help """
        print('*' * 80)
        print( """
Usage:
    xslt_report_generator.py <report_dir>/<xml report>/<list of xml reports> <result_dir>

Example:
    xslt_report_generator.py test_results/xml test_results
        - creates HTML test report from all xml files in test_results/xml to test_results folder

    xslt_report_generator.py test_results/xml/test.xml test_results
        - creates HTML test report from test.xml file to test_results folder

    xslt_report_generator.py test_results/xml/test.xml;test_results/xml/test2.xml test_results
        - creates HTML test report from both test.xml and test2.xml files to test_results folder
        """)
        print('*' * 80)

    def printTraceBack(self):
        """ Prints traceback information.
        """
        print('#' * 80)
        et, ev, tb = sys.exc_info()
        print ''.join(traceback.format_exception(et, ev, tb))
        print('#' * 80)

# ----------------------------------------------------------------------------
#       3.5 Command-line utility code
# ----------------------------------------------------------------------------
if __name__ == '__main__':
    # Initialize XSLTTestReportGenerator.
    generator = XSLTTestReportGenerator()

    try:
        generator.executeFromCLI()
    except Exception, error:
        generator.printUsage()
        generator.printTraceBack()
