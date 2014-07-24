<?xml version="1.0" encoding="utf-8" ?>
<!--
    NOKIA
    MP S40 SW
    UI Testing Tools

                Test report frames template
                ===========================
                Granite test report transformations

    Copyright (c) Nokia. All rights reserved.

    Specification:

    Notes:
        Result XML indentation 4 spaces

-->
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output method="html" media-type="text/html" encoding="UTF-8"/>

    <xsl:template name='main-frame'>
        <html>
        <head>
        <title>Granite Test Execution Report</title>
        </head>
        <xsl:choose>
            <xsl:when test="number($testrun) > 1">
                <frameset cols="20%,*">
                    <frame name="left_frame">
                        <xsl:attribute name="src">
                            <xsl:value-of select="concat('html/test_report_left_frame_', $testrun, '.html')"/>
                        </xsl:attribute>
                    </frame>
                    <frame src="" name="main_frame"/>
                </frameset>
            </xsl:when>
            <xsl:otherwise>
                <frameset cols="20%,*">
                    <frame src="html/test_report_left_frame.html" name="left_frame"/>
                    <frame src="" name="main_frame"/>
                </frameset>
            </xsl:otherwise>
        </xsl:choose>
        </html>
    </xsl:template>

    <xsl:template name="left-frame">

        <xsl:variable name="subarea-selection" select="/testset/hierarchy"/>
        <xsl:variable name="testcase-selection" select="/testset/hierarchy/hierarchy/testcase"/>

        <!-- Total test result counts -->
        <xsl:variable name="total-count" select="count($testcase-selection)"/>
        <xsl:variable name="passed-count" select="count($testcase-selection/art2testscript/art2testresult[@result = 'Passed'])"/>
        <xsl:variable name="failed-count" select="count($testcase-selection/art2testscript/art2testresult[@result = 'Failed' or
                                                                                       @result = 'Failed in setUp' or
                                                                                       @result = 'Failed in tearDown' or
                                                                                       @result = 'Remote failed'])"/>
        <xsl:variable name="error-count" select="count($testcase-selection/art2testscript/art2testresult[@result = 'No Result'])"/>
        <xsl:variable name="skipped-count" select="count($testcase-selection/art2testscript/art2testresult[@result = 'N/A'])"/>

        <html>
            <head>
                <!-- Charset is already declared in <?xml ?> declaration, but
                to it here too for possible buggy browsers -->
                <meta http-equiv="Content-Type" content="text/html" charset="UTF-8"/>
                <link href="../style/test_report_frames_style.css" rel="stylesheet" type="text/css"/>
                <script src="../script/test_report_testcase_array.js" type="text/javascript"></script>
                <script src="../script/test_report_common_script.js" type="text/javascript"></script>
                <script src="../script/test_report_activex_wrapper_script.js" type="text/javascript"></script>
                <script src="../script/test_report_left_frame_script.js" type="text/javascript"></script>
            </head>
            <body>
                <xsl:attribute name="onLoad">
                    <xsl:value-of select="concat('defineGlobals(&quot;', $testrun, '&quot;);refreshDocument();')"/>
                </xsl:attribute>
                <div id="testResultsPopup" class="hiddenPopup">
                    <pre style="font-weight: bold" class="showWs">
                        <xsl:value-of select="'Testcase results correspond to results &#010;which have been edited in Granite GUI.'"/>
                    </pre>
                </div>
                <div class="header">
                    <xsl:value-of select="'Testcases:'"/>
                    <font style="cursor: help;" class="webdings">
                        <xsl:attribute name="onmouseover">
                            <xsl:value-of select="'togglePopup(&quot;testResultsPopup&quot;, event);'"/>
                        </xsl:attribute>
                        <xsl:attribute name="onmouseout">
                            <xsl:value-of select="'togglePopup(&quot;testResultsPopup&quot;, event);'"/>
                        </xsl:attribute>
                        <xsl:text>&#105;</xsl:text>
                    </font>
                </div>
                <div class="select-group">
                    <div class="left-headline">in running order:</div>
                    <form name="all">
                        <div align="center">
                            <b><xsl:value-of select="concat('(', $total-count, ') ', 'All:')"/></b>
                            <br/>
                            <select onChange="openDocument(this, 'all');">
                                <!-- Testcases in execution order -->
                                <option disabled=""><xsl:value-of select="'Select testcase'"/></option>
                                <xsl:for-each select="$testcase-selection">
                                    <option>
                                        <xsl:choose>
                                            <xsl:when test="art2testscript/art2testresult/@result = 'Failed' or
                                                            art2testscript/art2testresult/@result = 'Failed in tearDown' or
                                                            art2testscript/art2testresult/@result = 'Failed in setUp' or
                                                            art2testscript/art2testresult/@result = 'Remote failed' or
                                                            art2testscript/art2testresult/@result = 'No Result'">
                                                <xsl:attribute name="class">
                                                    <xsl:value-of select="'failed'"/>
                                                </xsl:attribute>
                                            </xsl:when>
                                            <xsl:when test="art2testscript/art2testresult/@result = 'N/A'">
                                                <xsl:attribute name="class">
                                                    <xsl:value-of select="'skipped-passed'"/>
                                                </xsl:attribute>
                                            </xsl:when>
                                            <xsl:otherwise>
                                                <xsl:attribute name="class">
                                                    <xsl:value-of select="'passed'"/>
                                                </xsl:attribute>
                                            </xsl:otherwise>
                                        </xsl:choose>
                                        <xsl:variable name="result-file" select="translate(art2testscript/art2testresult[position()=last()]/@report_file, '&#92;', '&#47;')"/>
                                        <xsl:attribute name="value">
                                            <!-- subarea | feature | result file path -->
                                            <xsl:value-of select="concat(../../@name, '|', ../@name, '|', $result-file)"/>
                                        </xsl:attribute>
                                        <!-- testcase id -->
                                        <xsl:value-of select="@name"/>
                                    </option>
                                </xsl:for-each>
                            </select>
                        </div>
                    </form>
                    <div class="left-headline2">by result:</div>
                    <!-- Passed testcases -->
                    <form name="passed">
                        <div align="center">
                            <b><xsl:value-of select="concat('(', $passed-count, ') ', 'Passed:')"/></b>
                            <br/>
                            <select onChange="openDocument(this, 'passed');">
                                <option disabled=""><xsl:value-of select="'Select testcase'"/></option>
                                <xsl:for-each select="$testcase-selection/art2testscript/art2testresult[@result = 'Passed']">
                                    <option>
                                        <xsl:attribute name="class">
                                            <xsl:value-of select="'passed'"/>
                                        </xsl:attribute>
                                        <xsl:variable name="result-file" select="translate(../../art2testscript/art2testresult[position()=last()]/@report_file, '&#92;', '&#47;')"/>
                                        <xsl:attribute name="value">
                                            <!-- subarea | feature | result file path -->
                                            <xsl:value-of select="concat(../../../../@name, '|', ../../../@name, '|', $result-file)"/>
                                        </xsl:attribute>
                                        <!-- testcase id -->
                                        <xsl:value-of select="../../@name"/>
                                    </option>
                                </xsl:for-each>
                            </select>
                        </div>
                    </form>
                    <!-- Failed testcases -->
                    <form name="failed">
                        <div align="center">
                            <b><xsl:value-of select="concat('(', $failed-count, ') ', 'Failed:')"/></b>
                            <br/>
                            <select onChange="openDocument(this, 'failed');">
                                <option disabled=""><xsl:value-of select="'Select testcase'"/></option>
                                <xsl:for-each select="$testcase-selection/art2testscript/art2testresult[@result = 'Failed' or
                                                                                     @result = 'Failed in tearDown' or
                                                                                     @result = 'Failed in setUp' or
                                                                                     @result = 'Remote failed']">
                                    <option>
                                        <xsl:attribute name="class">
                                            <xsl:value-of select="'failed'"/>
                                        </xsl:attribute>
                                        <xsl:variable name="result-file" select="translate(../../art2testscript/art2testresult[position()=last()]/@report_file, '&#92;', '&#47;')"/>
                                        <xsl:attribute name="value">
                                            <!-- subarea | feature | result file path -->
                                            <xsl:value-of select="concat(../../../../@name, '|', ../../../@name, '|', $result-file)"/>
                                        </xsl:attribute>
                                        <!-- testcase id -->
                                        <xsl:value-of select="../../@name"/>
                                    </option>
                                </xsl:for-each>
                            </select>
                        </div>
                    </form>
                    <!-- No Result testcases -->
                    <form name="error">
                        <div align="center">
                            <b><xsl:value-of select="concat('(', $error-count, ') ', 'No Result:')"/></b>
                            <br/>
                            <select onChange="openDocument(this, 'error');">
                                <option disabled=""><xsl:value-of select="'Select testcase'"/></option>
                                <xsl:for-each select="$testcase-selection/art2testscript/art2testresult[@result = 'No Result']">
                                    <option>
                                        <xsl:attribute name="class">
                                            <xsl:value-of select="'failed'"/>
                                        </xsl:attribute>
                                        <xsl:variable name="result-file" select="translate(../../art2testscript/art2testresult[position()=last()]/@report_file, '&#92;', '&#47;')"/>
                                        <xsl:attribute name="value">
                                            <!-- subarea | feature | result file path -->
                                            <xsl:value-of select="concat(../../../../@name, '|', ../../../@name, '|', $result-file)"/>
                                        </xsl:attribute>
                                        <!-- testcase id -->
                                        <xsl:value-of select="../../@name"/>
                                    </option>
                                </xsl:for-each>
                            </select>
                        </div>
                    </form>
                    <!-- Failed + No Result testcases -->
                    <form name="failed-error">
                        <div align="center">
                            <b><xsl:value-of select="concat('(', $failed-count + $error-count, ') ', 'Failed + Error:')"/></b>
                            <br/>
                            <select onChange="openDocument(this, 'failed-error');">
                                <option disabled=""><xsl:value-of select="'Select testcase'"/></option>
                                <xsl:for-each select="$testcase-selection/art2testscript/art2testresult[@result = 'Failed' or
                                                                                     @result = 'Failed in setUp' or
                                                                                     @result = 'Failed in tearDown' or
                                                                                     @result = 'Remote failed' or
                                                                                     @result = 'No Result']">
                                    <option>
                                        <xsl:attribute name="class">
                                            <xsl:value-of select="'failed'"/>
                                        </xsl:attribute>
                                        <xsl:variable name="result-file" select="translate(../../art2testscript/art2testresult[position()=last()]/@report_file, '&#92;', '&#47;')"/>
                                        <xsl:attribute name="value">
                                            <!-- subarea | feature | result file path -->
                                            <xsl:value-of select="concat(../../../../@name, '|', ../../../@name, '|', $result-file)"/>
                                        </xsl:attribute>
                                        <!-- testcase id -->
                                        <xsl:value-of select="../../@name"/>
                                    </option>
                                </xsl:for-each>
                            </select>
                        </div>
                    </form>
                    <!-- Skipped testcases -->
                    <form name="skipped">
                        <div align="center">
                            <b><xsl:value-of select="concat('(', $skipped-count, ') ', 'N/A:')"/></b>
                            <br/>
                            <select onChange="openDocument(this, 'skipped');">
                                <option disabled=""><xsl:value-of select="'Select testcase'"/></option>
                                <xsl:for-each select="$testcase-selection/art2testscript/art2testresult[@result = 'N/A']">
                                    <option>
                                        <xsl:attribute name="class">
                                            <xsl:value-of select="'skipped-passed'"/>
                                        </xsl:attribute>
                                        <xsl:variable name="result-file" select="translate(../../art2testscript/art2testresult[position()=last()]/@report_file, '&#92;', '&#47;')"/>
                                        <xsl:attribute name="value">
                                            <!-- subarea | feature | result file path -->
                                            <xsl:value-of select="concat(../../../../@name, '|', ../../../@name, '|', $result-file)"/>
                                        </xsl:attribute>
                                        <!-- testcase id -->
                                        <xsl:value-of select="../../@name"/>
                                    </option>
                                </xsl:for-each>
                            </select>
                        </div>
                    </form>
                    <div class="left-headline2">by subarea/feature:</div>
                    <!-- Subareas -->
                    <form name="subarea">
                        <div align="center">
                            <b><xsl:value-of select="concat('(', count($subarea-selection), ') ', 'Subarea:')"/></b>
                            <br/>
                            <select onChange="openDocument(this, 'subarea');">
                                <xsl:for-each select="$subarea-selection">
                                     <!-- Iterate through all subareas. -->
                                    <xsl:sort select="@name" data-type="text" order="ascending"/>
                                    <xsl:variable name="failed" select="hierarchy/testcase/art2testscript/art2testresult[@result = 'Failed' or
                                                                                                      @result = 'Failed in setUp' or
                                                                                                      @result = 'Failed in tearDown' or
                                                                                                      @result = 'Remote failed' or
                                                                                                      @result = 'No Result']"/>
                                    <xsl:variable name="skipped" select="hierarchy/testcase/art2testscript/art2testresult[@result = 'N/A']"/>
                                    <option>
                                        <xsl:choose>
                                            <xsl:when test="$failed">
                                                <xsl:attribute name="class">
                                                    <xsl:choose>
                                                        <xsl:when test="not($skipped)">
                                                            <xsl:value-of select="'failed'"/>
                                                        </xsl:when>
                                                        <xsl:otherwise>
                                                            <xsl:value-of select="'skipped-failed'"/>
                                                        </xsl:otherwise>
                                                    </xsl:choose>
                                                </xsl:attribute>
                                            </xsl:when>
                                            <xsl:otherwise>
                                                <xsl:attribute name="class">
                                                    <xsl:choose>
                                                        <xsl:when test="not($skipped)">
                                                            <xsl:value-of select="'passed'"/>
                                                        </xsl:when>
                                                        <xsl:otherwise>
                                                            <xsl:value-of select="'skipped-passed'"/>
                                                        </xsl:otherwise>
                                                    </xsl:choose>
                                                </xsl:attribute>
                                            </xsl:otherwise>
                                        </xsl:choose>
                                        <xsl:attribute name="value">
                                            <xsl:value-of select="@name"/>
                                        </xsl:attribute>
                                        <xsl:value-of select="@name"/>
                                    </option>
                                </xsl:for-each>
                            </select>
                        </div>
                    </form>
                    <!-- Features -->
                    <form name="feature">
                        <div align="center">
                           <b><xsl:value-of select="concat('(', ') ', 'Features in subarea:')"/></b>
                            <br/>
                           <select onChange="openDocument(this, 'feature');"/>
                        </div>
                    </form>
                    <!-- Testcase -->
                    <form name="testcase">
                        <div align="center">
                            <b><xsl:value-of select="concat('(', ') ', 'Testcases in feature:')"/></b>
                            <br/>
                            <select onChange="openDocument(this, 'testcase');"/>
                        </div>
                    </form>
                </div>
                <br/>
                <div class="select-group">
                    <div class="left-headline">Testcase info:</div>
                    <div align="center">
                        <form name="summary">
                            <select onChange="openProperties(this);">
                                <option disabled="">
                                    <xsl:value-of select="'Select'"/>
                                </option>
                                <option>
                                    <xsl:attribute name="value">
                                        <xsl:value-of select="'general-information'"/>
                                    </xsl:attribute>
                                    <xsl:value-of select="'General'"/>
                                </option>
                                <option>
                                    <xsl:attribute name="value">
                                        <xsl:value-of select="'settings'"/>
                                    </xsl:attribute>
                                    <xsl:value-of select="'Settings'"/>
                                </option>
                                <option>
                                    <xsl:attribute name="value">
                                        <xsl:value-of select="'ignore-flags'"/>
                                    </xsl:attribute>
                                    <xsl:value-of select="'Ignore flags'"/>
                                </option>
                                <option>
                                    <xsl:attribute name="value">
                                        <xsl:value-of select="'general-warnings'"/>
                                    </xsl:attribute>
                                    <xsl:value-of select="'Warnings (general)'"/>
                                </option>
                            </select>
                        </form>
                    </div>
                    <div class="left-headline2">Miscellaneous:</div>
                    <div align="center">
                        <form name="other">
                            <select onChange="openProperties(this);">
                                <option disabled="">
                                    <xsl:value-of select="'Select'"/>
                                </option>
                                <option>
                                    <xsl:attribute name="value">
                                        <xsl:value-of select="'subarea-feature-summaries'"/>
                                    </xsl:attribute>
                                    <xsl:value-of select="'Subarea and feature summary'"/>
                                </option>
                                <option>
                                    <xsl:attribute name="value">
                                        <xsl:value-of select="'email-test-case'"/>
                                    </xsl:attribute>
                                    <xsl:value-of select="'E-Mail testcase'"/>
                                </option>
                            </select>
                        </form>
                    </div>
                    <div class="left-headline2">Search:</div>
                    <!-- Searched testcases -->
                    <div align="center">
                        <b>String:</b>
                        <input style="width: 90%" name="search-string" value=""/>
                        <input class="search-button" type="button" value=">" onclick="searchTestcase();"/>
                    </div>
                    <div align="center">
                        <form name="search-results">
                            <b id="search-headline">() Results:</b>
                            <select onChange="openDocument(this, 'search-results');">
                                <option disabled="">Select testcase</option>
                            </select>
                        </form>
                    </div>
                </div>
                <!-- Granite main trace data -->
                <div id="art2-main-trace" class="xmlOut">
                    <xsl:attribute name="onclick">
                        <xsl:value-of select="'getTraceDataExt(&quot;main&quot;);'"/>
                    </xsl:attribute>
                    <a class="defaultClass">
                        <xsl:attribute name="onmouseover">
                            <xsl:value-of select="'this.className = &quot;hooverClass&quot;'"/>
                        </xsl:attribute>
                        <xsl:attribute name="onmouseout">
                            <xsl:value-of select="'this.className = &quot;defaultClass&quot;'"/>
                        </xsl:attribute>
                        <xsl:value-of select="'[Open main trace data]'"/>
                    </a>
                </div>
                <!-- Granite remote trace data -->
                <div id="art2-remote-trace" class="xmlOut">
                    <xsl:attribute name="onclick">
                        <xsl:value-of select="'getTraceDataExt(&quot;remote&quot;);'"/>
                    </xsl:attribute>
                    <a class="defaultClass">
                        <xsl:attribute name="onmouseover">
                            <xsl:value-of select="'this.className = &quot;hooverClass&quot;'"/>
                        </xsl:attribute>
                        <xsl:attribute name="onmouseout">
                            <xsl:value-of select="'this.className = &quot;defaultClass&quot;'"/>
                        </xsl:attribute>
                        <xsl:value-of select="'[Open remote trace data]'"/>
                    </a>
                </div>
            </body>
        </html>
    </xsl:template>

</xsl:stylesheet>
