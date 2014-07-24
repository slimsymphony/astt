<?xml version="1.0" encoding="utf-8" ?>
<!--
    NOKIA
    MP S40 SW
    UI Testing Tools

                Test report gui summary template
                ===============================
                Granite test report transformations

    Copyright (c) Nokia. All rights reserved.

    %full_filespec: test_report_xml_to_html_summary.xslt-3:ascii:ou1iam#1 %

    %version:       3 %
    %date_created:  Wed Jun 11 13:59:53 2008 %
    %created_by:    teemukok %

    Reason:         Improvement
    Reference:      CM Synergy task: ou1iam#114821
    Description:    Renamed results according to QG/QC.

    SVN version info:
    $Revision: 209 $
    $Id: test_report_xml_to_html_summary.xslt 209 2006-05-18 09:21:51Z ripakane $

    Specification:

    Notes:
        Result XML indentation 4 spaces

-->
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output method="html" media-type="text/html" encoding="UTF-8"/>

    <!--

        Template: main-index-table

        Description:
            Creates a dynamic table containing
            subarea, feature and test case summaries.

            Test case labels are linked with the
            test case details.

        Scope: /testreport

        Parameters: none

        Output: HTML code <table>...</table>
    -->
    <xsl:template match="/testset">

        <xsl:variable name="subarea-selection" select="hierarchy"/>
        <xsl:variable name="testresults" select="hierarchy/hierarchy/testcase/testresult"/>

        <html>
            <head>
                <!-- Charset is already declared in <?xml ?> declaration, but
                to it here too for possible buggy browsers -->
                <meta http-equiv="Content-Type" content="text/html" charset="UTF-8"/>
                <link href="../style/test_report_common_style.css" rel="stylesheet" type="text/css"/>
                <script src="../script/test_report_activex_wrapper_script.js" type="text/javascript"></script>
                <script src="../script/test_report_common_script.js" type="text/javascript"></script>
<!--            <script type="text/javascript"><xsl:call-template name="common-script"/></script> -->
            </head>

            <body>
                <xsl:attribute name="onLoad">
                    <xsl:value-of select="'defineGlobals();'"/>
                </xsl:attribute>
                <div>
                    <xsl:attribute name="align">
                        <xsl:value-of select="'center'"/>
                    </xsl:attribute>
                    <h2 style="text-decoration: underline;">
                        <xsl:value-of select="'Subarea and feature summaries'"/>
                    </h2>

                    <table class="info" id="main-index-table" style="font-weight: normal">
                        <tr class="indexHeader">
                            <!-- Fix the column widths so that they don't change
                            when features and test cases become visible -->
                            <th style="text-align: left; white-space: nowrap">Test subarea/feature/case</th>
                            <th style="text-align: left; white-space: nowrap">Passed</th>
                            <th style="text-align: left; white-space: nowrap">Failed</th>
                            <th style="text-align: left; white-space: nowrap">No Result</th>
                            <th style="text-align: left; white-space: nowrap">N/A</th>
                            <th style="text-align: left; white-space: nowrap">Total</th>
                            <th style="text-align: left">Note</th>
                        </tr>

                         <!-- Iterate through all subareas. -->
                        <xsl:for-each select="hierarchy">
                            <xsl:sort select="@name" data-type="text" order="ascending"/>

                            <!-- Call template to render a row for the current subarea -->
                            <xsl:call-template name="main-index-subarea-row"/>

                             <!-- Iterate through all features in this subarea. -->
                            <xsl:for-each select="hierarchy">
                                <xsl:sort select="@name" data-type="text" order="ascending"/>

                                <!-- Call template to render a row for the current feature -->
                                <xsl:call-template name="main-index-feature-row"/>

                                <!-- Iterate through all cases in this feature -->
                                <xsl:for-each select="testcase">
                                    <xsl:sort select="@name" data-type="text" order="ascending"/>

                                    <!-- Call template to render a current testcase -->
                                    <xsl:call-template name="main-index-test-case-row"/>

                                </xsl:for-each>

                            </xsl:for-each>

                            <!-- Add empty row between subareas -->
                            <tr>
                                <td class="index"></td>
                                <td class="index"></td>
                                <td class="index"></td>
                                <td class="index"></td>
                                <td class="index"></td>
                                <td class="index"></td>
                                <td class="index"></td>
                            </tr>

                        </xsl:for-each>

                        <!-- Create a total row for all test cases -->
                        <tr class="indexFooter">
                            <td style="border: none; font-weight: bold">Total</td>
                            <xsl:call-template name="insert-statistics-cells">
                                <xsl:with-param name="testresults" select="$testresults"/>
                            </xsl:call-template>
                        </tr>

                    </table>
                </div>
            </body>
        </html>

    </xsl:template>

    <!--
        Template: main-index-subarea-row

        Description:
            Creates a row for a subarea selector
            into the main index table.

            This row also contains statistics summaries
            for the subarea.

            By clicking the subarea text you can open
            features under the subarea.

        Scope: any

        Parameters:
            selection:
                subarea node set we are using.

        Output: HTML code <tr>...</tr>
    -->
    <xsl:template name="main-index-subarea-row">

        <xsl:variable name="testresults" select="hierarchy/testcase/testresult"/>

        <!-- Begin the row -->
        <tr>
            <td style="color: black; border: none;">

                <!-- Call cell-hide-toggle template to create a handler
                for the dynamic cell showing/hiding -->
                <xsl:call-template name="cell-hide-toggle">
                    <xsl:with-param name="tableid" select="'main-index-table'"/>
                    <xsl:with-param name="idmark" select="@name"/>
                    <xsl:with-param name="text" select="@name"/>
                    <xsl:with-param name="state" select="true()"/>

                    <!-- Set the default color to red if this subarea contains failed or unknown cases -->
                    <xsl:with-param name="defaultClass">
                        <xsl:choose>
                            <xsl:when test="$testresults/@result = 'Failed' or
                                            $testresults/@result = 'Failed in tearDown' or
                                            $testresults/@result = 'Failed in setUp' or
                                            $testresults/@result = 'Remote failed' or
                                            $testresults/@result = 'No Result'">
                                <xsl:text>selectorRed</xsl:text>
                            </xsl:when>
                            <xsl:when test="$testresults[@result='N/A']">
                                <xsl:text>selectorBlue</xsl:text>
                            </xsl:when>
                            <xsl:otherwise>
                                <xsl:text>selectorGreen</xsl:text>
                            </xsl:otherwise>
                        </xsl:choose>
                    </xsl:with-param>

                    <xsl:with-param name="hooverClass" select="'selectorHoover'"/>
                </xsl:call-template>
            </td>

            <!-- Call template to calculate statistics information
            and create cells for them -->
            <xsl:call-template name="insert-statistics-cells">
                <xsl:with-param name="testresults" select="$testresults"/>
            </xsl:call-template>
        </tr>
    </xsl:template>

    <!--

        Template: main-index-feature-row

        Description:
            Creates a row for a feature selector
            in to the main index table.

            This row also contains statistics summaries
            for the feature.

            By clicking the feature text you can open
            test cases under the feature.

        Scope: any

        Parameters:
            selection:
                feature node set we are using.

        Output: HTML code <tr>...</tr>
    -->
    <xsl:template name="main-index-feature-row">

        <xsl:variable name="testresults" select="testcase/testresult"/>

        <!-- Begin the row -->
        <tr style="display: none">

            <!-- Features are shown without opening by default -->
            <xsl:attribute name="style"></xsl:attribute>

            <!-- Create an id which is used in dynamic cell showing/hiding -->
            <xsl:attribute name="id">
                <xsl:value-of select="../@name"/>
            </xsl:attribute>

            <td style="color: black; border: none; padding-left: 20px">

                <!-- Call cell-hide-toggle template to create a handler
                for the dynamic cell showing/hiding -->
                <xsl:call-template name="cell-hide-toggle">

                    <!-- The main index table id -->
                    <xsl:with-param name="tableid" select="'main-index-table'"/>

                    <!-- Id mark for the test cases under this feature -->
                    <xsl:with-param name="idmark" select="concat(../@name, '-', @name)"/>

                    <!-- The user visible text -->
                    <xsl:with-param name="text" select="@name"/>

                    <!-- Set the default color to red if this feature contains failed or unknown cases -->
                    <xsl:with-param name="defaultClass">
                        <xsl:choose>
                            <xsl:when test="$testresults/@result = 'Failed' or
                                            $testresults/@result = 'Failed in tearDown' or
                                            $testresults/@result = 'Failed in setUp' or
                                            $testresults/@result = 'Remote failed' or
                                            $testresults/@result = 'No Result'">
                                <xsl:text>selectorRed</xsl:text>
                            </xsl:when>
                            <xsl:when test="$testresults[@result='N/A']">
                                <xsl:text>selectorBlue</xsl:text>
                            </xsl:when>
                            <xsl:otherwise>
                                <xsl:text>selectorGreen</xsl:text>
                            </xsl:otherwise>
                        </xsl:choose>
                    </xsl:with-param>

                    <xsl:with-param name="hooverClass" select="'selectorHoover'"/>
                </xsl:call-template>
            </td>

            <!-- Call template to calculate statistics information
            and create cells for them -->
            <xsl:call-template name="insert-statistics-cells">
                <xsl:with-param name="testresults" select="$testresults"/>
            </xsl:call-template>
        </tr>
    </xsl:template>

    <!--

        Template: main-index-test-case-row

        Description:
            Creates a row for a single test case
            in to the main index table.

        Scope: any

        Parameters:
            selection:
                test case node we are using.

        Output: HTML code <tr><a>...</a></tr>
    -->
    <xsl:template name="main-index-test-case-row">

        <!-- Begin the index row for a test case-->
        <tr style="display: none">

            <!-- Create an id which is used in dynamic cell showing/hiding -->
            <xsl:attribute name="id">
                <xsl:value-of select="concat(../../@name, '-', ../@name)"/>
            </xsl:attribute>

            <!-- Create id cell -->
            <td style="border: none; padding-left: 45px; white-space: nowrap;">
                <a>
                    <!-- Set color according to the test result using CSS style attribute -->
                    <xsl:attribute name="style">
                        <xsl:choose>
                            <xsl:when test="testresult/@result = 'Failed' or
                                            testresult/@result = 'Failed in tearDown' or
                                            testresult/@result = 'Failed in setUp' or
                                            testresult/@result = 'Remote failed' or
                                            testresult/@result = 'No Result'">
                                <xsl:value-of select="'color: red'"/>
                            </xsl:when>
                            <xsl:when test="testresult/@result = 'N/A'">
                                <xsl:value-of select="'color: blue'"/>
                            </xsl:when>
                            <xsl:otherwise>
                                <xsl:value-of select="'color: green'"/>
                            </xsl:otherwise>
                        </xsl:choose>
                    </xsl:attribute>

                    <!-- Create attributes for linking testcases -->
                    <xsl:attribute name="onclick">
                        <xsl:value-of select="concat('creatorWindow.remoteOpen(&quot;', @name, '&quot;, &quot;', testresult/@result, '&quot;);')"/>
                    </xsl:attribute>
                    <xsl:attribute name="onmouseover">
                        <xsl:value-of select="'this.className=&quot;onHooverClass&quot;'"/>
                    </xsl:attribute>
                    <xsl:attribute name="onmouseout">
                        <xsl:value-of select="'this.className = &quot;&quot;'"/>
                    </xsl:attribute>

                    <!-- Insert user visible text -->
                    <xsl:value-of select="@name"/>
                </a>
            </td>

            <!-- Mark the spot in the result column under which this case belongs to -->
            <td style="border: none; color: green; text-align: left">
                <xsl:if test="testresult/@result = 'Passed'">+</xsl:if>
            </td>

            <td style="border: none; color: red; text-align: left">
                <xsl:if test="testresult/@result = 'Failed' or
                              testresult/@result = 'Failed in tearDown' or
                              testresult/@result = 'Failed in setUp' or
                              testresult/@result = 'Remote failed'">+</xsl:if>
            </td>

            <td style="border: none; color: red; text-align: left">
                <xsl:if test="testresult/@result = 'No Result'">+</xsl:if>
            </td>

            <td style="border: none; color: blue; text-align: left">
               <xsl:if test="testresult/@result = 'N/A'">+</xsl:if>
            </td>

            <td style="border: none; color: black; text-align: left"/>

        </tr>
    </xsl:template>

    <!--
        Template: insert-statistics-cells

        Description:
            Calculates statistics information
            for the given node set and outputs
            it as table columns.

        Scope: any

        Parameters:
            selection:
                node set we use for statistics calculations.

        Output: HTML code <td>...</td> <td>...</td> ...
    -->
    <xsl:template name="insert-statistics-cells">
        <xsl:param name="testresults"/>

        <!-- Calculate test result totals -->
        <xsl:variable name="failed-count" select="count($testresults[@result = 'Failed' or
                                                                     @result = 'Failed in tearDown' or
                                                                     @result = 'Failed in setUp' or
                                                                     @result = 'Remote failed'])"/>
        <xsl:variable name="unknown-count" select="count($testresults[@result = 'No Result'])"/>
        <xsl:variable name="skipped-count" select="count($testresults[@result = 'N/A'])"/>
        <xsl:variable name="passed-count" select="count($testresults[@result = 'Passed'])"/>
        <xsl:variable name="total-count" select="count($testresults)"/>

        <!-- Calculate relative amounts -->
        <xsl:variable name="failed-percent" select="$failed-count * 100 div $total-count"/>
        <xsl:variable name="unknown-percent" select="$unknown-count * 100 div $total-count"/>
        <xsl:variable name="skipped-percent" select="$skipped-count * 100 div $total-count"/>
        <xsl:variable name="passed-percent" select="$passed-count * 100 div $total-count"/>
        <xsl:variable name="total-percent" select="$failed-percent + $unknown-percent + $skipped-percent + $passed-percent"/>

        <!-- Create table cells for calculated numbers -->
        <td style="color: green; border: none; white-space: nowrap">
            <xsl:value-of select="$passed-count"/>
            <xsl:text> (</xsl:text>
            <xsl:value-of select="round($passed-percent)"/>
            <xsl:text>%)</xsl:text>
        </td>

        <td style="color: red; border: none; white-space: nowrap">
            <xsl:value-of select="$failed-count"/>
            <xsl:text> (</xsl:text>
            <xsl:value-of select="round($failed-percent)"/>
            <xsl:text>%)</xsl:text>
        </td>

        <td style="color: red; border: none; white-space: nowrap">
            <xsl:value-of select="$unknown-count"/>
            <xsl:text> (</xsl:text>
            <xsl:value-of select="round($unknown-percent)"/>
            <xsl:text>%)</xsl:text>
        </td>

        <td style="color: blue; border: none; white-space: nowrap">
            <xsl:value-of select="$skipped-count"/>
            <xsl:text> (</xsl:text>
            <xsl:value-of select="round($skipped-percent)"/>
            <xsl:text>%)</xsl:text>
        </td>

        <td style="color: black; border: none; white-space: nowrap">
            <xsl:value-of select="$total-count"/>
            <!-- no need to show 100%, it is confusing -->
            <!-- <xsl:text> (</xsl:text>
            <xsl:value-of select="round($total-percent)"/>
            <xsl:text>%)</xsl:text> -->
        </td>

        <td style="color: black; border: none; white-space: nowrap"/>

    </xsl:template>

    <xsl:template name="cell-hide-toggle">
        <xsl:param name="text"/>
        <xsl:param name="tableid"/>
        <xsl:param name="state" select="false()"/>
        <xsl:param name="idmark"/>
        <xsl:param name="defaultClass"/>
        <xsl:param name="hooverClass"/>

        <span>
            <!-- Add id marker attribute to identify this dynamic text section -->
            <xsl:attribute name="class">
                <xsl:value-of select="$defaultClass"/>
            </xsl:attribute>

            <xsl:attribute name="onclick">

                <!--
                    Following forms a statement:

                    toggle_rows_visiblity("$tableid", "$idmark")
                    toggle_rows_visibility("main-index-table", "Python Component")

                    This statement calls a javascript function which
                    switches between the visibility states of all rows
                    whose id contain a word $idmark.
                  -->
                <xsl:text>toggle_rows_visibility(this, </xsl:text>
                <xsl:value-of select="concat('&quot;', $tableid, '&quot;')"/>
                <xsl:text>, </xsl:text>
                <xsl:value-of select="concat('&quot;', $idmark, '&quot;')"/>
                <xsl:text>)</xsl:text>
            </xsl:attribute>

            <!-- Highlight item when mouse is above it -->
            <xsl:attribute name="onmouseover">
                <xsl:text>this.className = '</xsl:text><xsl:value-of select="$hooverClass"/><xsl:text>'</xsl:text>
            </xsl:attribute>

            <!-- Dehighlight when mouse moves away from the item -->
            <xsl:attribute name="onmouseout">
                <xsl:text>this.className = '</xsl:text><xsl:value-of select="$defaultClass"/><xsl:text>'</xsl:text>
            </xsl:attribute>

            <!-- Do not take actions when user is selecting text.
                 Showing/hiding blocks during selection breaks UI. -->
            <xsl:attribute name="onselectstart">
                <xsl:text>event.returnValue = false;</xsl:text>
            </xsl:attribute>

            <xsl:call-template name="char-toggle">
                <xsl:with-param name="state" select="$state"/>
            </xsl:call-template>
            <!-- Insert user visible text -->
            <xsl:value-of select="$text"/>
        </span>
    </xsl:template>

    <xsl:template name="char-toggle">
        <xsl:param name="id"/>
        <xsl:param name="state"/>

        <font class="arrows">
            <xsl:if test="$id">
                <xsl:attribute name="id">
                    <xsl:value-of select="$id"/>
                </xsl:attribute>
            </xsl:if>
            <xsl:choose>
                <xsl:when test="$state">
                    <!-- '&#128;'(Wingdings 3), &#8681; (Unicode) -->
                    <xsl:text>&#54;</xsl:text>
                </xsl:when>
                <xsl:otherwise>
                    <!-- '&#125;'(Wingdings 3), &#8680; (Unicode) -->
                    <xsl:text>&#52;</xsl:text>
                </xsl:otherwise>
            </xsl:choose>
        </font>
    </xsl:template>

</xsl:stylesheet>
