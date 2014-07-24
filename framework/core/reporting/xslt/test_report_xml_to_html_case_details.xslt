<?xml version="1.0" encoding="utf-8" ?>
<!--
    NOKIA
    Devices
    GTES, Testing Tools

    Test Report XML to HTML Converter Test Case Detail Implementation
    =================================================================
    Granite test report transformations

    Copyright (c) Nokia. All rights reserved.

    %full_filespec: test_report_xml_to_html_case_details.xslt-ou1s40#43:ascii:ou_isasw#1 %

    %version:       ou1s40#43 %
    %date_created:  Tue Aug 17 12:54:02 2010 %
    %created_by:    janpernu %

    Reason:         Improvement
    Reference:      CM Synergy task: ou1s40#63396
    Description:    Update- and rejectReference calls modified to pass 'bitmap db' setting value.

    SVN version info:
    $Revision: 274 $
    $Id: test_report_xml_to_html_case_details.xslt 274 2006-06-15 09:22:00Z ripakane $

    Notes:

        The purpose of this module is translate test case internals to
        a human readable form.

        There is no good way to select ISI message tags, because
        XPath doesn't support wildcards in tag name selection.

        All XPath selections and tests must be hardcoded.
        Example:

            <xsl:value-of select="isi_req|isi_resp|isi_ntf|isi_ind|extra_msg">

        Templates in this module (in the order of apperance):

            - test-report               Sort testcases by result
            - test-report-phones        Process main/remote testcases
            - test-report-testcase      Process testcase information

            - testcase-properties       Process/visualize testcase properties
            - testcase-description      Process/visualize testcase descriptions
            - testcase-comment          Process/visualize testcase comments
            - testcase-component        Process/visualize components
            - testcase-warnings         Process/visualize testcase warnings (@reason='Warning!')
            - testcase-teststep         Process teststep information
            - testcase-summary          Process testcase summary information
            - testcase-error            Process/visualize testcase errors
            - testcase-dump-files       Process/visualize testcase dumped files

            - teststep-expect           Process teststep/expect information
            - teststep-layout           Process/visualize teststep/expect/display/@layout information
            - teststep-expect-display   Process teststep/expect/display information
            - teststep-capture          Process teststep/capture information
            - teststep-isi-msg          Process isi message information

            - expect-display-bitmap     Process teststep/expect/display/bitmap information

            - display-deviation         Process/visualize display deviation information
            - isi-msg-deviation         Process/visualize isi message deviation information

            - teststep-visualizer       Visualize detailed teststep information
            - display-visualizer        Visualize detailed display information
            - bitmap-visualizer         Visualize detailed bitmap information
            - bitmap-verify-visualizer  Visualize detailed bitmap verify information
            - capture-visualizer        Visualize detailed capture information
            - isi-msg-visualizer        Visualize detailed isi message information

            - select-bitmap-attributes  select bitmap attributes
            - set-bitmap-attributes     set bitmap attributes

        ***

        XSLT indentation 4 spaces.
        Page width 140 characters.

        ***

        For every XSLT template, comment at least:
            - short description
            - scope (a tag name where processing happens)
            - parameters (type tag/text)
            - output (the style of output, like HTML code/plaintext/number)

        ***

        Comprehensive XSLT documentation can be found in MSXML 4.0 on-line help,
        downloadable at http://msdn.microsoft.com

        XSLT Tutorial: http://www.w3schools.com/xsl/xsl_transformation.asp

        Good, free XSLT editor for Win32 platform:
        http://www.xmlcooktop.com/

        ***
-->

<xsl:stylesheet version='1.0' xmlns:xsl='http://www.w3.org/1999/XSL/Transform'>

<!--

    Template: test-report

    Description:

        Generates test case detailed information as HTML output

        Walkthrough:

        - Add test case name and categroy information
        - Add bookmark anchor for this test case
        - Add test case description (orignally from docstring)
        - Add following into hideable block
            - Test case type (scripted)
            - Test case steps/comments/errors/summaries
            - Unknown tags are informed to an user
            - NOTE: If test case is passed all summary nodes are automatically
              hidden since they don't contain any important information

        Test steps & co. are displayed in the order they are executed.
        "Dummy" summaries between test steps are skipped. Dummy means
        that summary contains display information which test passed correctly through ,
        not any error information.

        Summaries are displayed only if
            - Summary is an error summary (we have awful logic there to figure it out)

        When summary is an error summary, it is marked as a red error and
        error message is displayed instead of "Summary" text.

        Logic to figure out if a summary is an error summary:
        - The name of the node following the summary node is 'error'
        - The name of the node following the summary node is 'comment'
          and the next node is 'error'

    Scope: testreport/testcase

    Parameters: none

    Output: HTML code <p> .... </p>

-->
<xsl:template name="test-report">
    <xsl:param name="testcases" select="$testcases-main"/>

    <xsl:if test="not($single-testcase)">
        <hr size="3"/>
        <h2 align="center"><a name="details">Detailed test case information</a></h2>
    </xsl:if>

    <!-- Show all 'Failed' cases. -->
    <xsl:for-each select="$testcases[@result = 'Failed']">
        <xsl:call-template name="test-report-phones"/>
    </xsl:for-each>

    <!-- Show all 'Failed in tearDown' cases. -->
    <xsl:for-each select="$testcases[@result = 'Failed in tearDown']">
        <xsl:call-template name="test-report-phones"/>
    </xsl:for-each>

    <!-- Show all 'Failed in setUp' cases. -->
    <xsl:for-each select="$testcases[@result = 'Failed in setUp']">
        <xsl:call-template name="test-report-phones"/>
    </xsl:for-each>

    <!-- Show all 'Remote failed' cases. -->
    <xsl:for-each select="$testcases[@result = 'Remote failed']">
        <xsl:call-template name="test-report-phones"/>
    </xsl:for-each>

    <!-- Show all 'Expected fail' cases. -->
    <xsl:for-each select="$testcases[@result = 'Expected fail']">
        <xsl:call-template name="test-report-phones"/>
    </xsl:for-each>

    <!-- Show all 'No Result' cases. -->
    <xsl:for-each select="$testcases[@result = 'No Result']">
        <xsl:call-template name="test-report-phones"/>
    </xsl:for-each>

    <!-- Show all 'Skipped' cases. -->
    <xsl:for-each select="$testcases[@result = 'N/A']">
        <xsl:call-template name="test-report-phones"/>
    </xsl:for-each>

    <!-- Show all 'Passed' cases. -->
    <xsl:for-each select="$testcases[@result = 'Passed']">
        <xsl:call-template name="test-report-phones"/>
    </xsl:for-each>

    <xsl:if test="not($single-testcase)">
        <hr size="3"/>
    </xsl:if>

</xsl:template>

<!--

    Template: test-report-phones

    Description: Process testcase phones.

    Scope: testreport/testcase
           testreport/testcase/remote/testcase

    Parameters:

    Output: HTML code

-->
<xsl:template name="test-report-phones">
    <xsl:variable name="main-phone" select="."/>
    <xsl:variable name="remote-phone" select="remote/testcase"/>
    <!-- Create an id for this test case used in dynamic hiding -->
    <xsl:variable name="testcase-anchor" select="generate-id(current())"/>

    <xsl:call-template name="testcase-properties">
        <xsl:with-param name="testcase-anchor" select="$testcase-anchor"/>
    </xsl:call-template>

    <xsl:call-template name="test-report-testcase">
        <xsl:with-param name="phone" select="'main'"/>
        <xsl:with-param name="selection" select="$main-phone"/>
        <xsl:with-param name="testcase-anchor" select="$testcase-anchor"/>
    </xsl:call-template>
    <xsl:if test="$remote-phone">
        <xsl:call-template name="test-report-testcase">
            <xsl:with-param name="phone" select="'remote'"/>
            <xsl:with-param name="selection" select="$remote-phone"/>
            <xsl:with-param name="testcase-anchor" select="$testcase-anchor"/>
        </xsl:call-template>
    </xsl:if>
</xsl:template>

<!--

    Template: test-report-testcase

    Description: Process testcase details.

    Scope: testreport/testcase
           testreport/testcase/remote/testcase

    Parameters:

    Output: HTML code

-->
<xsl:template name="test-report-testcase">
    <xsl:param name="phone"/>
    <xsl:param name="selection"/>
    <xsl:param name="testcase-anchor"/>

    <div>
        <xsl:if test="not($single-testcase)">
            <xsl:attribute name="style">
                <xsl:value-of select="'margin-left: 2%'"/>
            </xsl:attribute>
        </xsl:if>

        <!-- Call to create dynamic show/hide toggler for test case details.
        Note that pure $testcase-anchor is already the name/id of bookmark anchor object.
        This is because IE seems to confuse <a name=""> and <div id=""> -->
        <xsl:call-template name="hide-toggle-header">
            <xsl:with-param name="text" select="concat('TEST EXECUTION (', $phone, ')')"/>
            <xsl:with-param name="id" select="concat($phone, '-', $testcase-anchor)"/>
            <xsl:with-param name="state" select="true()"/>
        </xsl:call-template>

        <!-- Dynamic block, in this case test case details -->
        <div style="margin-left: 2%">

            <xsl:attribute name="class">
                <xsl:value-of select="'showBlockClass'"/>
            </xsl:attribute>

            <xsl:attribute name="id">
                <xsl:value-of select="concat($phone, '-', $testcase-anchor)"/>
            </xsl:attribute>

            <!-- Add a handler to open all test steps once -->
            <xsl:call-template name="all-test-steps-toggler">
                <xsl:with-param name="text" select="'[Open teststep details]'"/>
                <xsl:with-param name="parentid" select="concat($phone, '-', $testcase-anchor)"/>
            </xsl:call-template>

            <!-- Test steps / summaries / exceptions in the order they come -->
            <xsl:for-each select="$selection/*">
                <xsl:choose>

                    <!-- Teststep tag -->
                    <xsl:when test="name() = 'teststep'">
                        <xsl:call-template name="testcase-teststep"/>
                    </xsl:when>

                    <!-- Summary tag -->
                    <xsl:when test="name() = 'summary'">
                        <!-- error or capture summary or bitmap verify(training) -->
                        <xsl:call-template name="testcase-summary"/>
                    </xsl:when>

                    <!-- Remote(processed later) -->
                    <xsl:when test="name() = 'remote'"/>

                    <!-- Comment -->
                    <xsl:when test="name() = 'comment'">
                        <xsl:call-template name="testcase-comment"/>
                    </xsl:when>

                    <!-- Error -->
                    <xsl:when test="name() = 'error'">

                        <!-- The previous tag could be an error summary,
                        it is handled as an special case in the summary handling and thus we
                        do not need to show this error message twice.

                        We need to also ensure that summary/display is not empty (has text/animations).
                        If it is empty, summary is not shown and then error is not shown. This happens
                        e.g. in ART self test and the error message would completely disappear
                        without this extra check since empty summaries are not shown.

                        Note that display elements can be also under summary/expect/restart/display,
                        not only summary/expect/display.

                        -->
                        <xsl:choose>
                            <!-- No traceback output if error reason is 'NOTEXPECTED RESULT'. -->
                            <xsl:when test="@reason = 'NOTEXPECTED RESULT' or contains(traceback, 'NOTEXPECTED RESULT') or contains(traceback, 'Remote: Failed')"/>
                            <!-- Output traceback message. -->
                            <xsl:otherwise>
                                <xsl:call-template name="testcase-error"/>
                                <br style="line-height: 50%"/>
                            </xsl:otherwise>
                        </xsl:choose>
                    </xsl:when>

                    <!-- Component -->
                    <xsl:when test="name() = 'component'">
                        <xsl:call-template name="testcase-component"/>
                    </xsl:when>

                    <!-- Description(already handled) -->
                    <xsl:when test="name() = 'description'"/>

                    <!-- dump_files -->
                    <xsl:when test="name() = 'dump_files'">
                        <xsl:call-template name="testcase-dump-files"/>
                    </xsl:when>
                    
                    <!-- Other (unknown) tags -->
                    <xsl:otherwise>
                        <!-- Call template to output warning messages
                             about unknown tags. -->
                        <xsl:call-template name="unknown-tag">
                            <xsl:with-param name="tag" select="name()"/>
                        </xsl:call-template>
                    </xsl:otherwise>

                </xsl:choose>

            </xsl:for-each>
        </div>
    </div>
    <div class="newLine"/>
    <br/>

</xsl:template>

<!--

    Template: testcase-properties

    Description: Process/visualize testcase properties.

    Scope: testreport/testcase
           testreport/testcase/remote/testcase

    Parameters:

    Output: HTML code

-->
<xsl:template name="testcase-properties">
    <xsl:param name="testcase-anchor"/>

    <!-- Description -->
    <xsl:call-template name="testcase-description">
        <xsl:with-param name="testcase-anchor" select="$testcase-anchor"/>
    </xsl:call-template>

    <div>
        <xsl:if test="not($single-testcase)">
            <xsl:attribute name="style">
                <xsl:value-of select="'margin-left: 2%;'"/>
            </xsl:attribute>
        </xsl:if>
        <table class="description">
            <!-- result, id, subarea and feature information -->
            <xsl:for-each select="@*">
                <xsl:choose>
                    <xsl:when test="name() = 'id'"/>
                    <xsl:when test="name() = 'result'">
                        <tr>
                            <td style="border: None; white-space: nowrap">
                                <xsl:value-of select="'Test run result:'"/>
                            </td>
                            <td style="border: None">
                                <xsl:call-template name="test-result-color-write">
                                    <xsl:with-param name="text" select="."/>
                                </xsl:call-template>
                            </td>
                        </tr>
                    </xsl:when>
                    <xsl:otherwise>
                        <xsl:variable name="name" select="concat( translate( substring( name(), 1, 1 ), 'abcdefghijklmnopqrstuvwxyz', 'ABCDEFGHIJKLMNOPQRSTUVWXYZ' ), substring( name(), 2, string-length( name() )), ':')"/>
                        <tr>
                            <td style="border: None; white-space: nowrap">
                                <xsl:value-of select="translate( $name, '_', ' ' )"/>
                            </td>
                            <xsl:choose>
                                <xsl:when test="name() = 'video'">
                                    <td style="border: None">
                                        <a>
                                            <xsl:attribute name="href">
                                                <xsl:value-of select="concat('../camera/', .)"/>
                                            </xsl:attribute>
                                            <xsl:value-of select="."/>
                                        </a>
                                    </td>
                                </xsl:when>
                                <xsl:otherwise>
                                    <td style="border: None">
                                        <xsl:value-of select="."/>
                                    </td>
                                </xsl:otherwise>
                            </xsl:choose>
                        </tr>
                    </xsl:otherwise>
                </xsl:choose>
            </xsl:for-each>
        </table>
        <font style="font-weight: bold; cursor: help;" class="arrows">
            <xsl:attribute name="onmouseover">
                <xsl:value-of select="'togglePopup(&quot;testRunResultPopup&quot;, event);'"/>
            </xsl:attribute>
            <xsl:attribute name="onmouseout">
                <xsl:value-of select="'togglePopup(&quot;testRunResultPopup&quot;, event);'"/>
            </xsl:attribute>
            <xsl:text>&#105;</xsl:text>
        </font>
    </div>
    <div class="newLine"/>
    <br/>

</xsl:template>

<!--

    Template: testcase-description

    Description: Process/visualize testcase descriptions.

    Scope: testreport/testcase/description

    Parameters: none

    Output: HTML code

-->
<xsl:template name="testcase-description">
    <xsl:param name="testcase-anchor"/>

    <div class="tcHeading">
        <xsl:attribute name="onmouseover">
            <xsl:value-of select="'togglePopup(&quot;testcasePopup&quot;, event);'"/>
        </xsl:attribute>
        <xsl:attribute name="onmouseout">
            <xsl:value-of select="'togglePopup(&quot;testcasePopup&quot;, event);'"/>
        </xsl:attribute>
        <xsl:call-template name="test-result-color-write">
            <xsl:with-param name="text" select="@id"/>
        </xsl:call-template>
    </div>
    <br/>
    <div id="testcasePopup" style="padding: 5px;" class="hiddenPopup">
        <pre style="font-weight: bold" class="showWs">
            <xsl:value-of select="description"/>
        </pre>
    </div>
    <div class="newLine"/>
    <br/>

</xsl:template>

<!--

    Template: testcase-comment

    Description: Process/visualize testcase comments.

    Scope: testreport/testcase/comment

    Parameters: none

    Output: HTML code

-->
<xsl:template name="testcase-comment">
    <div class="comment">
        <xsl:choose>
            <xsl:when test="@reason='Warning!'">
                <xsl:attribute name="style">
                    <xsl:text>color: red;</xsl:text>
                </xsl:attribute>
                <xsl:value-of select="concat('Warning: ', .)"/>
            </xsl:when>
            <xsl:otherwise>
                <xsl:attribute name="style">
                    <xsl:text>color: green;</xsl:text>
                </xsl:attribute>
                <xsl:value-of select="concat('Comment: ', @reason)"/>
            </xsl:otherwise>
        </xsl:choose>
    </div>
    <div class="newLine"/>
</xsl:template>

<!--

    Template: testcase-component

    Description: Process/visualize testcase components.

    Scope: testreport/testcase/component

    Parameters: none

    Output: HTML code

-->
<xsl:template name="testcase-component">
    <div class="component">
        <xsl:value-of select="concat('Component: ', @name, ', ', @type, ': ', .)"/>
    </div>
    <div class="newLine"/>
</xsl:template>

<!--

    Template: testcase-warnings

    Description: Process/visualize testcase warnings.

    Scope: testreport/testcase/comment[@reason='Warning!']
           testreport/testcase/remote/testcase/comment[@reason='Warning!']

    Parameters:

    Output: HTML code

-->
<xsl:template name="testcase-warnings">
    <!-- Create an id for this test case used in dynamic hiding -->
    <xsl:variable name="testcase-anchor" select="generate-id(current())"/>
    <xsl:variable name="testcases" select=".|remote/testcase"/>

    <xsl:call-template name="testcase-properties">
        <xsl:with-param name="testcase-anchor" select="$testcase-anchor"/>
    </xsl:call-template>

    <xsl:for-each select="$testcases">
        <div style="margin-left: 4%">
            <xsl:for-each select="*">
                <!-- Comment -->
                <xsl:if test="name() = 'comment'">
                    <xsl:choose>
                        <xsl:when test="not(@reason='Warning!')"/>
                        <xsl:otherwise>
                            <xsl:call-template name="testcase-comment"/>
                        </xsl:otherwise>
                    </xsl:choose>
                </xsl:if>
            </xsl:for-each>
        </div>
    </xsl:for-each>

</xsl:template>

<!--

    Template: testcase-teststep

    Description: Process testcase teststep information.

    Scope: testreport/testcase/teststep

    Parameters: none

    Output: HTML code

-->
<xsl:template name="testcase-teststep">

    <xsl:variable name="teststep" select="."/>
    <xsl:variable name="teststep-nodes" select="*"/>
    <xsl:variable name="summary" select="following-sibling::summary[@name=current()/@name][1]"/>
    <!-- This id is needed in dynamic show/hide block scripts for this test step -->
    <xsl:variable name="teststep-id" select="generate-id(current())"/>
    <xsl:variable name="do-display" select="boolean($summary/expect/display/*)"/>
    <xsl:variable name="do-restart" select="boolean($summary/expect/restart/display/*)"/>
    <xsl:variable name="do-isi" select="$summary/expect/isi_resp or $summary/expect/isi_ntf or
                                        $summary/expect/isi_ind or $summary/expect/outcome"/>
    <xsl:variable name="do-extra_msg" select="$summary/extra_msg"/>
    <xsl:variable name="do-input" select="$summary/input"/>
    <!--
        Create toggler which shows test step id and allows
        the user to show and hide details by clicking -->
    <xsl:call-template name="hide-toggle-header">
        <xsl:with-param name="id" select="$teststep-id"/>
        <xsl:with-param name="text" select="concat('Teststep ', @name)"/>
        <xsl:with-param name="state" select="$do-display or $do-restart or $do-isi"/>
    </xsl:call-template>

    <div style="margin-left: 2%">

        <!-- Dynamic content goes here -->
        <xsl:choose>
            <!-- unexpected, last expectation is shown -->
            <xsl:when test="$do-display or $do-restart or $do-isi">
                <xsl:for-each select="expect[@id=$summary/expect/@id]">
                    <xsl:choose>
                        <xsl:when test="position() = last()">
                            <div class="showBlockClass">
                                <xsl:call-template name="teststep-visualizer">
                                    <xsl:with-param name="nodes" select="$teststep-nodes[@id &lt;= number(current()/@id)]"/>
                                    <xsl:with-param name="timeout" select="$teststep/@timeout"/>
                                    <xsl:with-param name="duration" select="$summary/@duration"/>
                                    <xsl:with-param name="teststep-id" select="$teststep-id"/>
                                    <xsl:with-param name="status" select="'exception'"/>
                                </xsl:call-template>
                            </div>
                        </xsl:when>
                    </xsl:choose>
                </xsl:for-each>
            </xsl:when>
            <xsl:when test="$do-extra_msg">
                <xsl:for-each select="extra_msg[@id=$summary/extra_msg/@id]">
                    <xsl:choose>
                        <xsl:when test="position() = last()">
                            <div class="showBlockClass">
                                <xsl:call-template name="teststep-visualizer">
                                    <xsl:with-param name="nodes" select="$teststep-nodes[@id &lt;= current()/@id]"/>
                                    <xsl:with-param name="timeout" select="$teststep/@timeout"/>
                                    <xsl:with-param name="duration" select="$summary/@duration"/>
                                    <xsl:with-param name="teststep-id" select="$teststep-id"/>
                                    <xsl:with-param name="status" select="'exception'"/>
                                </xsl:call-template>
                            </div>
                        </xsl:when>
                    </xsl:choose>
                </xsl:for-each>
            </xsl:when>
            <xsl:when test="$do-input">
                <xsl:for-each select="input[@id=$summary/input/@id]">
                    <xsl:choose>
                        <xsl:when test="position() = last()">
                            <div class="showBlockClass">
                                <xsl:call-template name="teststep-visualizer">
                                    <xsl:with-param name="nodes" select="$teststep-nodes[@id &lt;= current()/@id]"/>
                                    <xsl:with-param name="timeout" select="$teststep/@timeout"/>
                                    <xsl:with-param name="duration" select="$summary/@duration"/>
                                    <xsl:with-param name="teststep-id" select="$teststep-id"/>
                                    <xsl:with-param name="status" select="'exception'"/>
                                </xsl:call-template>
                            </div>
                        </xsl:when>
                    </xsl:choose>
                </xsl:for-each>
            </xsl:when>
            <!-- expected,  successful teststeps is hidden -->
            <xsl:otherwise>
                <div class="hideBlockClass">
                    <xsl:call-template name="teststep-visualizer">
                        <xsl:with-param name="teststep-id" select="$teststep-id"/>
                        <xsl:with-param name="duration" select="$summary/@duration"/>
                        <xsl:with-param name="status" select="'expected'"/>
                    </xsl:call-template>
                </div>
            </xsl:otherwise>
        </xsl:choose>
        <div class="newLine"/>

    </div>

</xsl:template>

<!--

    Template: testcase-summary

    Description: Process testcase summary information.

        Inside expect show all:
        - display tags
        - isi message tags (isi*)
        - outcome

        If the summary is empty (all ok) then
        omit "summary" line between output teststeps
        (in that case this method doesn't run code
        inside if blocks).

        If a display tag containing child elements
        (texts & animations) is found under an expect node,
        create two paragraphs, one for errors (summary)
        and one for the orignal (teststep).

    Scope: testreport/testcase/summary

    Parameters:
        error-msg:
            If this string is not null, the summary is an error summary.
            Set summay color to red and set error-msg to user visible
            summary name.

    Output: HTML code

-->
<xsl:template name="testcase-summary">

    <!-- Create id used in dynamic visibility -->
    <xsl:variable name="summary-id" select="generate-id(current())"/>

    <!-- These are tests if various supported summary types exists in
    this summary. Several cases can exist in one summary
    simultaneously. -->

    <!-- NOTE: display must contain children nodes in order
    to be meaningfully for the test report reader.

    UI test cases produce childless display tags showing only the
    chosen test path, which already is highlighted in the previous test step section.
    -->

    <!-- We don't need display captures here if they were
    already handled in <teststep>. However, <teststep>
    is not always available and if there is no <teststep> / <capture>
    display <capture> in <summary> -->

    <xsl:variable name="do-display" select="expect/display/text or expect/display/animation"/>
    <xsl:variable name="do-bitmap" select="boolean(expect/display/bitmap/@checksum)"/>
    <xsl:variable name="do-capture" select="capture and not(../teststep)"/>
    <xsl:variable name="do-restart" select="boolean(expect/restart)"/>
    <xsl:variable name="do-isi" select="expect/isi_resp or expect/isi_ntf or expect/isi_ind or extra_msg or expect/outcome or input"/>
    <xsl:variable name="error-reason" select="following-sibling::error[1]/@reason"/>

    <!-- Test if we have a supported summary type -->
    <xsl:if test="$do-display or $do-capture or $do-restart or $do-isi">

        <!--
            Create Summary keyword which is used to show/hide
            detailed summary information
        -->
        <xsl:choose>
            <xsl:when test="$do-display or $do-isi or $do-restart">
                <xsl:call-template name="hide-toggle-header">
                    <xsl:with-param name="id" select="$summary-id"/>
                    <xsl:with-param name="text" select="'NOT EXPECTED RESULT'"/>
                    <xsl:with-param name="style" select="'color: red'"/>
                    <xsl:with-param name="state" select="true()"/>
                </xsl:call-template>
            </xsl:when>
            <xsl:when test="$do-capture">
                <xsl:call-template name="hide-toggle-header">
                    <xsl:with-param name="id" select="$summary-id"/>
                    <xsl:with-param name="text" select="concat('Capture from teststep ', @name)"/>
                    <xsl:with-param name="state" select="true()"/>
                </xsl:call-template>
            </xsl:when>
            <xsl:otherwise>
                <xsl:call-template name="hide-toggle-header">
                    <xsl:with-param name="id" select="$summary-id"/>
                    <xsl:with-param name="text" select="concat('Summary of ', @name)"/>
                 </xsl:call-template>
            </xsl:otherwise>
        </xsl:choose>

        <!-- Dynamic show/hide summary information goes into this block -->
        <div style="margin-left: 4%; padding-bottom: 10px" class="showBlockClass">

            <xsl:attribute name="id">
                <xsl:value-of select="$summary-id"/>
            </xsl:attribute>

            <xsl:attribute name="status">
                <xsl:value-of select="'exception'"/>
            </xsl:attribute>

            <!-- Display tag must contain child tags in order to be visible in summary -->
            <xsl:if test="$do-display">

                <!--
                    The following code goes through all
                    - display nodes containing child nodes (child nodes =
                      display errors found)
                    - captures

                    Captures are not shown in summary if there are teststeps available.

                    They are sorted according to their id.

                    For display nodes, an error difference comparison against
                    previous test step expections is created.
                -->
                <xsl:variable name="summary-items" select="expect/display[./*]"/>
                <xsl:for-each select="$summary-items">
                    <xsl:sort select="@id" data-type="number"/>
                    <xsl:call-template name="display-deviation">
                        <xsl:with-param name="bitmap-verify" select="$do-bitmap"/>
                        <xsl:with-param name="expect-count" select="count($summary-items)"/>
                    </xsl:call-template>
                </xsl:for-each>

            </xsl:if>

            <xsl:if test="$do-capture">
                <xsl:for-each select="capture">
                    <xsl:sort select="@id" data-type="number"/>
                    <xsl:call-template name="capture-visualizer"/>
                </xsl:for-each>
            </xsl:if>

            <!-- If there are ISI message nodes, create difference comparing section
            for them -->
            <xsl:if test="$do-isi">
                <xsl:call-template name="isi-msg-deviation"/>
            </xsl:if>

            <!-- Visualize summary/expect/restart tags -->
            <xsl:if test="$do-restart">
                <xsl:for-each select="expect/restart">
                    <!--
                        Display screen which should have been booted.
                        NOTE: only one should be present but do it
                        for many just in case.
                    -->
                    <div style="text-align:left; font-weight: bold;">Expected restart, but got a following display:</div>
                    <xsl:for-each select="display">
                        <xsl:sort select="@id" data-type="number"/>
                        <xsl:call-template name="teststep-expect-display">
                            <xsl:with-param name="display-elements" select="text|animation"/>
                            <xsl:with-param name="bitmap-elements" select="bitmap"/>
                            <xsl:with-param name="status" select="true()"/>
                        </xsl:call-template>
                    </xsl:for-each>
                </xsl:for-each>
            </xsl:if>

        </div> <!-- Summary hideable paragraph -->
        <div class="newLine"/>


    </xsl:if> <!-- Do dummary test -->

</xsl:template>

<!--

    Template: testcase-error

    Description: Process/visualize testcase errors.

    Scope: testreport/testcase/error

    Parameters: none

    Output: HTML code

-->
<xsl:template name="testcase-error">
    <xsl:variable name="testcase-error-id" select="generate-id(current())"/>

    <xsl:choose>
<!--    <xsl:when test="@reason = 'Remote: Failed'">
            <xsl:value-of select="@reason"/>
        </xsl:when>
        <xsl:when test="substring(@reason, 0, 25) = 'Failed to synchronize to'">
            <xsl:value-of select="@reason"/>
        </xsl:when> -->
        <xsl:when test="not(. = '')">
            <div class="error">
              <xsl:value-of select="concat('ERROR REASON: ', @reason)"/>
            </div>
            <xsl:call-template name="hide-toggle-header">
                <xsl:with-param name="text" select="'ERROR TRACEBACK'"/>
                <xsl:with-param name="id" select="concat('traceback', $testcase-error-id)"/>
                <xsl:with-param name="state" select="true()"/>
                <xsl:with-param name="style" select="'color: red'"/>
            </xsl:call-template>
            <div class="showBlockClass">
                <xsl:attribute name="id">
                    <xsl:value-of select="concat('traceback', $testcase-error-id)"/>
                </xsl:attribute>
                <xsl:attribute name="status">
                    <xsl:value-of select="'exception'"/>
                </xsl:attribute>
                <div class="traceBack">
                    <xsl:call-template name="add-traceback-links">
                        <xsl:with-param name="text" select=".|./traceback"/>
                    </xsl:call-template>
                </div>
            </div>
        </xsl:when>
        <xsl:otherwise>
            <div class="error">
                <xsl:value-of select="concat('Error: ', @reason)"/>
            </div>
        </xsl:otherwise>
    </xsl:choose>
</xsl:template>

<!--

    Template: testcase-dump-files

    Description: Process/visualize testcase dump file information.

    Scope: testreport/testcase/dump_files

    Parameters: none

    Output: HTML code

-->
<xsl:template name="testcase-dump-files">
    <xsl:variable name="dump-file-id" select="generate-id(current())"/>

    <xsl:call-template name="hide-toggle-header">
        <xsl:with-param name="id" select="$dump-file-id"/>
        <xsl:with-param name="text" select="concat('Dump files ', @comment)"/>
        <xsl:with-param name="style" select="'color: red'"/>
        <xsl:with-param name="state" select="False"/>
    </xsl:call-template>

    <div class="showBlockClass" style="margin-left: 2%">
        <xsl:attribute name="id">
            <xsl:value-of select="$dump-file-id"/>
        </xsl:attribute>
        <!-- Mulder / Scully -->
        <xsl:if test="x_file">
            <table class="display">
                <tr class="indexHeader">
                    <td>#</td>
                    <td>Mulder</td>
                    <xsl:if test="x_file/@scully">
                        <td>Scully</td>
                    </xsl:if>
                    <td>Reset reason</td>
                </tr>
                <xsl:for-each select="x_file">
                    <tr>
                        <td><xsl:value-of select="position()"/></td>
                        <td>
                            <a>
                                <xsl:attribute name="href">
                                    <xsl:value-of select="concat('../x_files', ../@phone, '/', @mulder)"/>
                                </xsl:attribute>
                                <xsl:value-of select="@mulder"/>
                            </a>
                        </td>
                        <xsl:if test="@scully">
                            <td>
                                <a>
                                    <xsl:attribute name="href">
                                        <xsl:value-of select="concat('../x_files/', ../@phone, '/', @scully)"/>
                                    </xsl:attribute>
                                    <xsl:value-of select="@scully"/>
                                </a>
                            </td>
                        </xsl:if>
                        <td><xsl:value-of select="@reset_reason"/></td>
                    </tr>
                </xsl:for-each>
            </table>
        </xsl:if>

        <!-- Stack (All Time High) -->
        <xsl:if test="ath_file">
            <table class="display">
                <tr class="indexHeader">
                    <td>#</td>
                    <td>Stack(All Time High)</td>
                </tr>
                <xsl:for-each select="ath_file">
                    <tr>
                        <td><xsl:value-of select="position()"/></td>
                        <td>
                            <a>
                                <xsl:attribute name="href">
                                    <xsl:value-of select="concat('../ath_files/', ../@phone, '/', @name)"/>
                                </xsl:attribute>
                                <xsl:value-of select="@name"/>
                            </a>
                        </td>
                    </tr>
                </xsl:for-each>
            </table>
        </xsl:if>
    </div>

</xsl:template>

<!--

    Template: teststep-expect

    Description: Process teststep expect information.

    Scope: testreport/testcase/teststep/expect

    Parameters: none

    Output: HTML code

-->
<xsl:template name="teststep-expect">

    <xsl:variable name="summary" select="../following-sibling::summary[@name=current()/../@name][1]"/>
    <xsl:variable name="summary-expect" select="$summary/*[@id = current()/@id]"/>

    <!-- This id is needed in dynamic show/hide block scripts for this test step expect -->
    <xsl:variable name="expect-id" select="generate-id(current())"/>

    <xsl:variable name="do-display" select="boolean($summary-expect/display/*)"/>
    <xsl:variable name="do-restart" select="boolean($summary-expect/restart/display/*)"/>
    <xsl:variable name="do-isi" select="$summary-expect/isi_resp or $summary-expect/isi_ntf or $summary-expect/isi_ind or
                                        $summary-expect/extra_msg or $summary-expect/outcome or $summary-expect/input"/>

    <xsl:variable name="text">
        <xsl:choose>
            <xsl:when test="@length">
                <xsl:value-of select="concat('Expectation ', '(timeout: ', @timeout, ', length: ', @length, ')')"/>
            </xsl:when>
            <xsl:otherwise>
                <xsl:value-of select="concat('Expectation ', '(timeout: ', @timeout, ')')"/>
            </xsl:otherwise>
        </xsl:choose>
    </xsl:variable>

    <xsl:call-template name="hide-toggle-header">
        <xsl:with-param name="id" select="$expect-id"/>
        <xsl:with-param name="text" select="$text"/>
        <xsl:with-param name="state" select="$do-display or $do-restart or $do-isi"/>
    </xsl:call-template>

    <!-- Indent opening text -->
    <div style="margin-left: 2%; padding-bottom: 10px">
        <!-- Dynamic content goes here -->
        <xsl:choose>
            <xsl:when test="$summary-expect">
                <xsl:variable name="expect-items" select="./*[@id=$summary-expect/*/@id]"/>
                <xsl:for-each select="$expect-items">
                    <xsl:variable name="summary-item" select="$summary-expect/*[@id = current()/@id]"/>
                    <xsl:choose>
                        <xsl:when test="$summary-item and name() = 'display'">
                            <xsl:choose>
                                <xsl:when test="$summary-item/*">
                                    <xsl:if test="position() = 1">
                                        <xsl:attribute name="class">
                                            <xsl:value-of select="'showBlockClass'"/>
                                        </xsl:attribute>
                                        <!-- Create id used in dynamic visibility -->
                                        <xsl:attribute name="id">
                                            <xsl:value-of select="$expect-id"/>
                                        </xsl:attribute>
                                        <!-- special dummy attribute 'status' to identify items -->
                                        <xsl:attribute name="status">
                                            <xsl:value-of select="'exception'"/>
                                        </xsl:attribute>
                                    </xsl:if>
                                    <xsl:call-template name="teststep-expect-display">
                                        <xsl:with-param name="display-elements" select="text|animation"/>
                                        <xsl:with-param name="bitmap-elements" select="bitmap"/>
                                        <xsl:with-param name="status" select="true()"/>
                                        <xsl:with-param name="expect-count" select="count($expect-items)"/>
                                    </xsl:call-template>
                                </xsl:when>
                                <xsl:otherwise>
                                    <xsl:if test="position() = 1">
                                        <xsl:attribute name="class">
                                            <xsl:value-of select="'hideBlockClass'"/>
                                        </xsl:attribute>
                                        <!-- Create id used in dynamic visibility -->
                                        <xsl:attribute name="id">
                                            <xsl:value-of select="$expect-id"/>
                                        </xsl:attribute>
                                        <!-- special dummy attribute 'status' to identify items -->
                                        <xsl:attribute name="status">
                                            <xsl:value-of select="'ts-expected'"/>
                                        </xsl:attribute>
                                    </xsl:if>
                                    <xsl:call-template name="teststep-expect-display">
                                        <xsl:with-param name="display-elements" select="text|animation"/>
                                        <xsl:with-param name="bitmap-elements" select="bitmap"/>
                                    </xsl:call-template>
                                </xsl:otherwise>
                            </xsl:choose>
                        </xsl:when>
                        <xsl:when test="$summary-item and name() = 'restart'">
                            <xsl:choose>
                                <xsl:when test="$summary-item">
                                    <xsl:attribute name="class">
                                        <xsl:value-of select="'showBlockClass'"/>
                                    </xsl:attribute>
                                    <!-- special dummy attribute 'status' to identify items -->
                                    <xsl:attribute name="status">
                                        <xsl:value-of select="'exception'"/>
                                    </xsl:attribute>
                                </xsl:when>
                                <xsl:otherwise>
                                    <xsl:attribute name="class">
                                        <xsl:value-of select="'hideBlockClass'"/>
                                    </xsl:attribute>
                                    <!-- special dummy attribute 'status' to identify items -->
                                    <xsl:attribute name="status">
                                        <xsl:value-of select="'ts-expected'"/>
                                    </xsl:attribute>
                                </xsl:otherwise>
                            </xsl:choose>
                            <xsl:attribute name="id">
                                <xsl:value-of select="$expect-id"/>
                            </xsl:attribute>
                            <b>RESTART</b>
                        </xsl:when>
                        <xsl:when test="substring(name(), 0, 5) = 'isi_' or name() = 'extra_msg' or name() = 'outcome' or name() = 'input'">
                            <xsl:choose>
                                <xsl:when test="$summary-item">
                                    <xsl:if test="position() = 1">
                                        <xsl:attribute name="class">
                                            <xsl:value-of select="'showBlockClass'"/>
                                        </xsl:attribute>
                                        <!-- Create id used in dynamic visibility -->
                                        <xsl:attribute name="id">
                                            <xsl:value-of select="$expect-id"/>
                                        </xsl:attribute>
                                        <!-- special dummy attribute 'status' to identify items -->
                                        <xsl:attribute name="status">
                                            <xsl:value-of select="'exception'"/>
                                        </xsl:attribute>
                                    </xsl:if>
                                    <xsl:call-template name="isi-msg-visualizer">
                                        <xsl:with-param name="teststep-isi" select="."/>
                                        <xsl:with-param name="status" select="true()"/>
                                    </xsl:call-template>
                                </xsl:when>
                                <xsl:otherwise>
                                    <xsl:if test="position() = 1">
                                        <xsl:attribute name="class">
                                            <xsl:value-of select="'hideBlockClass'"/>
                                        </xsl:attribute>
                                        <!-- Create id used in dynamic visibility -->
                                        <xsl:attribute name="id">
                                            <xsl:value-of select="$expect-id"/>
                                        </xsl:attribute>
                                        <!-- special dummy attribute 'status' to identify items -->
                                        <xsl:attribute name="status">
                                            <xsl:value-of select="'ts-expected'"/>
                                        </xsl:attribute>
                                    </xsl:if>
                                    <xsl:call-template name="isi-msg-visualizer">
                                        <xsl:with-param name="teststep-isi" select="."/>
                                    </xsl:call-template>
                                </xsl:otherwise>
                            </xsl:choose>
                        </xsl:when>
                    </xsl:choose>
                </xsl:for-each>
            </xsl:when>
            <!-- expectation blocks in same teststep which have not been processed(after NOT EXPECTED RESULT) -->
            <xsl:otherwise>
                <xsl:for-each select="*">
                    <xsl:choose>
                        <xsl:when test="name() = 'display'">
                            <xsl:if test="position() = 1">
                                <xsl:attribute name="class">
                                    <xsl:value-of select="'hideBlockClass'"/>
                                </xsl:attribute>
                                <!-- Create id used in dynamic visibility -->
                                <xsl:attribute name="id">
                                    <xsl:value-of select="$expect-id"/>
                                </xsl:attribute>
                                <!-- special dummy attribute 'status' to identify items -->
                                <xsl:attribute name="status">
                                    <xsl:value-of select="'ts-expected'"/>
                                </xsl:attribute>
                            </xsl:if>
                            <xsl:call-template name="teststep-expect-display">
                                <xsl:with-param name="display-elements" select="text|animation"/>
                                <xsl:with-param name="bitmap-elements" select="bitmap"/>
                            </xsl:call-template>
                        </xsl:when>
                        <xsl:when test="name() = 'restart'">
                            <xsl:attribute name="class">
                                <xsl:value-of select="'hideBlockClass'"/>
                            </xsl:attribute>
                            <xsl:attribute name="id">
                                <xsl:value-of select="$expect-id"/>
                            </xsl:attribute>
                            <!-- special dummy attribute 'status' to identify items -->
                            <xsl:attribute name="status">
                                <xsl:value-of select="'ts-expected'"/>
                            </xsl:attribute>
                            <b>RESTART</b>
                        </xsl:when>
                        <xsl:when test="substring(name(), 0, 5) = 'isi_' or name() = 'extra_msg' or name() = 'outcome' or name() = 'input'">
                            <xsl:if test="position() = 1">
                                <xsl:attribute name="class">
                                    <xsl:value-of select="'hideBlockClass'"/>
                                </xsl:attribute>
                                <!-- Create id used in dynamic visibility -->
                                <xsl:attribute name="id">
                                    <xsl:value-of select="$expect-id"/>
                                </xsl:attribute>
                                <!-- special dummy attribute 'status' to identify items -->
                                <xsl:attribute name="status">
                                    <xsl:value-of select="'ts-expected'"/>
                                </xsl:attribute>
                            </xsl:if>
                            <xsl:call-template name="isi-msg-visualizer">
                                <xsl:with-param name="teststep-isi" select="."/>
                            </xsl:call-template>
                        </xsl:when>
                    </xsl:choose>
                </xsl:for-each>
            </xsl:otherwise>
        </xsl:choose>
    </div>

</xsl:template>

<!--

    Template: teststep-layout

    Description: Visualize layout(collapsed if multible valid expect blocks).

    Scope: testreport/testcase/teststep/expect/display
           testreport/testcase/remote/testcase/teststep/expect/display

    Parameters:
        expect-count: valid expect block count

-->
<xsl:template name="teststep-layout">
    <xsl:param name="display-elements"/>
    <xsl:param name="display-id"/>
    <xsl:param name="expect-count"/>
    <xsl:param name="status"/>

    <xsl:choose>
        <xsl:when test="$expect-count > 1">
            <xsl:choose>
                <xsl:when test="$display-elements/../@layoutName">
                    <xsl:call-template name="hide-toggle-header">
                        <xsl:with-param name="id" select="$display-id"/>
                        <xsl:with-param name="text" select="concat('Layout name: ', $display-elements/../@layoutName)"/>
                        <xsl:with-param name="state" select="$status"/>
                    </xsl:call-template>
                </xsl:when>
                <xsl:when test="@layoutName">
                    <xsl:call-template name="hide-toggle-header">
                        <xsl:with-param name="id" select="$display-id"/>
                        <xsl:with-param name="text" select="concat('Layout name: ', @layoutName)"/>
                        <xsl:with-param name="state" select="$status"/>
                    </xsl:call-template>
                </xsl:when>
                <xsl:otherwise>
                    <xsl:call-template name="hide-toggle-header">
                        <xsl:with-param name="id" select="$display-id"/>
                        <xsl:with-param name="text" select="''"/>
                        <xsl:with-param name="state" select="$status"/>
                    </xsl:call-template>
                </xsl:otherwise>
            </xsl:choose>
        </xsl:when>
        <xsl:otherwise>
            <xsl:choose>
                <xsl:when test="$display-elements/../@layoutName">
                    <div style="text-align:left; font-weight: bold;">Layout name: <xsl:value-of select="$display-elements/../@layoutName"/></div>
                </xsl:when>
                <xsl:when test="@layoutName">
                    <div style="text-align:left; font-weight: bold;">Layout name: <xsl:value-of select="@layoutName"/></div>
                </xsl:when>
            </xsl:choose>
        </xsl:otherwise>
    </xsl:choose>

</xsl:template>

<!--

    Template: teststep-expect-display

    Description:

        <display> & <capture> node visualization core.

        Plots out a table containing display text and animation elements.

        The set of elements must be given as a parameter since it is
        required to make a difference between mismatched and
        unexpected elements in an error summary (missing elements
        vs. unexpected elements). This is achieved
        by making two calls to this fuction with inverse display
        node selections from summary display visualizer.

        For <teststep>/<display> this code ASSUMES
        that the corresponding summary node follows
        immediately after the test step node. There is no other clever
        way to assing a summary node to a teststep node.

    Scope:  testreport/testcase/teststep/expect/display or
            testreport/testcase/summary/expect/display or
            testreport/testcase/summary/expect/capture

    Parameters:

    Output: HTML code

-->
<xsl:template name="teststep-expect-display">
    <xsl:param name="display-elements"/>
    <xsl:param name="bitmap-elements"/>
    <xsl:param name="status" select="false()"/>
    <xsl:param name="bitmap-verify" select="false()"/>
    <xsl:param name="expect-count" select="1"/>

    <xsl:variable name="display-id" select="generate-id(current())"/>

    <!-- Visualize layout -->
    <xsl:call-template name="teststep-layout">
        <xsl:with-param name="display-elements" select="$display-elements"/>
        <xsl:with-param name="display-id" select="$display-id"/>
        <xsl:with-param name="expect-count" select="$expect-count"/>
        <xsl:with-param name="status" select="$status"/>
    </xsl:call-template>

    <div>
        <xsl:if test="$expect-count > 1">
            <xsl:attribute name="class">
                <xsl:value-of select="'showBlockClass'"/>
            </xsl:attribute>
           <xsl:attribute name="id">
                <xsl:value-of select="$display-id"/>
            </xsl:attribute>
        </xsl:if>

        <xsl:if test="not($bitmap-verify)">
            <xsl:call-template name="display-visualizer">
                <xsl:with-param name="display-elements" select="$display-elements"/>
            </xsl:call-template>
        </xsl:if>

    </div>

    <!-- Visualize bitmaps -->
    <xsl:if test="$expect-count = 1 or $expect-count > 1 and position() = last()">
        <xsl:call-template name="expect-display-bitmap">
            <xsl:with-param name="bitmap" select="$bitmap-elements"/>
        </xsl:call-template>
    </xsl:if>

</xsl:template>

<!--

    Template: teststep-capture

    Description: Process teststep capture information.

    Scope: testreport/testcase/teststep/capture

    Parameters: none

    Output: HTML code

-->
<xsl:template name="teststep-capture">

    <!-- This id is needed in dynamic show/hide block scripts for this test step capture -->
    <xsl:variable name="capture-id" select="generate-id(current())"/>

    <xsl:call-template name="hide-toggle-header">
        <xsl:with-param name="id" select="$capture-id"/>
        <xsl:with-param name="text" select="'Capture(s)'"/>
        <xsl:with-param name="state" select="true()"/>
    </xsl:call-template>

    <!-- Indent opening text -->
    <div style="margin-left: 2%">
        <!-- Dynamic content goes here -->
        <div class="showBlockClass">

            <!-- Create id used in dynamic visibility -->
            <xsl:attribute name="id">
                <xsl:value-of select="$capture-id"/>
            </xsl:attribute>
            <!-- special dummy attribute 'status' to identify items -->
            <xsl:attribute name="status">
                <xsl:value-of select="'capture'"/>
            </xsl:attribute>

            <!-- Visualize displays we went through -->
            <xsl:variable name="summary" select="../following-sibling::summary[@name=current()/../@name][1]"/>
            <xsl:for-each select="$summary/capture[@id=current()/@id]">
                <xsl:call-template name="capture-visualizer"/>
            </xsl:for-each>
        </div>
    </div>
</xsl:template>

<!--

    Template: teststep-isi-msg

    Description: Process teststep isi message information.

    Scope:  testreport/testcase/teststep/expect/isi_req
            testreport/testcase/summary/expect/isi_resp
            testreport/testcase/summary/expect/isi_ntf
            testreport/testcase/summary/expect/isi_ind
            testreport/testcase/summary/expect/extra_msg
            testreport/testcase/summary/expect/input
            testreport/testcase/summary/expect/outcome

    Parameters: none

    Output: HTML code

-->
<xsl:template name="teststep-isi-msg">

    <!-- This id is needed in dynamic show/hide block scripts for this test step expect -->
    <xsl:variable name="isi-msg-id" select="generate-id(current())"/>

    <xsl:call-template name="hide-toggle-header">
        <xsl:with-param name="id" select="$isi-msg-id"/>
        <xsl:with-param name="text" select="'ISI message'"/>
    </xsl:call-template>

    <!-- Indent opening text -->
    <div style="margin-left: 2%">

        <!-- Visualize ISI messages if found -->
        <div>
            <xsl:attribute name="class">
                <xsl:value-of select="'hideBlockClass'"/>
            </xsl:attribute>
            <xsl:attribute name="id">
                <xsl:value-of select="$isi-msg-id"/>
            </xsl:attribute>
            <!-- special dummy attribute 'status' to identify items -->
            <xsl:attribute name="status">
                <xsl:value-of select="'ts-expected'"/>
            </xsl:attribute>

            <!-- Check if message nodes are present in the current node contents -->
            <xsl:call-template name="isi-msg-visualizer">
                <xsl:with-param name="teststep-isi" select="."/>
            </xsl:call-template>
        </div>
    </div>

</xsl:template>

<!--

    Template: expect-display-bitmap

    Description: Process teststep bitmap information.

    Scope:  testreport/testcase/teststep/expect/display/bitmap
            testreport/testcase/remote/testcase/teststep/expect/display/bitmap
            testreport/testcase/teststep/capture/bitmap
            testreport/testcase/remote/testcase/teststep/capture/bitmap
            testreport/testcase/summary/expect/display/bitmap
            testreport/testcase/remote/testcase/summary/expect/display/bitmap

    Parameters:
        bitmap: bitmap node selection

-->
<xsl:template name="expect-display-bitmap">
    <xsl:param name="bitmap"/>

    <xsl:choose>
        <!-- Teststep node -->
        <xsl:when test="name($bitmap/../../..) = 'teststep'">
            <xsl:if test="$bitmap/@checksum">
                <xsl:choose>
                    <!-- Trained bitmap(s) -->
                    <xsl:when test="$bitmap/@checksum = '4294967295'">
                        <xsl:variable name="id" select="generate-id(current())"/>
                        <xsl:for-each select="$bitmap">
                            <xsl:variable name="summary" select="../../../following-sibling::summary[@name=current()/../../../@name][1]"/>
                            <xsl:call-template name="bitmap-visualizer">
                                <xsl:with-param name="bitmap-id" select="$id"/>
                                <xsl:with-param name="selection" select="$summary/expect[@id = current()/../../@id]/display[@id = current()/../@id]/bitmap[@id = current()/@id]"/>
                            </xsl:call-template>
                        </xsl:for-each>
                        <div class="description" style="display: none; white-space: nowrap;">
                            <xsl:attribute name="id">
                                <xsl:value-of select="concat($id, '-info')"/>
                            </xsl:attribute>
                            <div></div><div></div><div></div>
                        </div>
                        <div class="newLine"/>
                    </xsl:when>
                    <!-- Verified(successful) bitmap(s) -->
                    <xsl:otherwise>
                        <xsl:for-each select="$bitmap">
                            <xsl:call-template name="bitmap-verify-visualizer"/>
                        </xsl:for-each>
                    </xsl:otherwise>
                </xsl:choose>
            </xsl:if>
        </xsl:when>
        <!-- Summary node -->
        <!-- Error/captured/verified(unsuccessful) bitmap(s) -->
        <xsl:otherwise>
            <xsl:variable name="id" select="generate-id(current())"/>
            <xsl:for-each select="$bitmap">
                <xsl:call-template name="bitmap-visualizer">
                    <xsl:with-param name="bitmap-id" select="$id"/>
                </xsl:call-template>
            </xsl:for-each>
            <xsl:if test="$bitmap/@checksum">
                <div class="description" style="display: none; white-space: nowrap;">
                    <xsl:attribute name="id">
                        <xsl:value-of select="concat($id, '-info')"/>
                    </xsl:attribute>
                    <div></div><div></div><div></div>
                </div>
                <div class="newLine"/>
            </xsl:if>
        </xsl:otherwise>
    </xsl:choose>

</xsl:template>

<!--

    Template: display-deviation

    Description: Display deviation of expected and actual display elements.

    Scope: testreport/testcase/remote/testcase/summary/expect/display

    Parameters:
        bitmap-verify:
            boolean [ true / false ]
        expect-count:
            Valid expect block count

    Output: HTML code

-->
<xsl:template name="display-deviation">
    <xsl:param name="bitmap-verify" select="false()"/>
    <xsl:param name="expect-count" select="1"/>

    <!-- Non unexpect (mismatching) items -->
    <xsl:call-template name="teststep-expect-display">
        <xsl:with-param name="display-elements" select="text|animation"/>
        <xsl:with-param name="bitmap-elements" select="bitmap"/>
        <xsl:with-param name="status" select="true()"/>
        <xsl:with-param name="bitmap-verify" select="$bitmap-verify"/>
        <xsl:with-param name="expect-count" select="$expect-count"/>
    </xsl:call-template>

</xsl:template>

<!--

    Template: isi-msg-deviation

    Description: Display deviation of expected and actual isi message elements.

    Scope: testreport/testcase/summary/expect/isi_resp
           testreport/testcase/summary/expect/isi_ntf
           testreport/testcase/summary/expect/isi_ind
           testreport/testcase/summary/expect/extra_msg
           testreport/testcase/summary/expect/input
           testreport/testcase/summary/expect/outcome

    Parameters:

    Output: HTML code

-->
<xsl:template name="isi-msg-deviation">

    <xsl:attribute name="status">
        <xsl:value-of select="'exception'"/>
    </xsl:attribute>
    <xsl:attribute name="title">
        <xsl:value-of select="'By comparing this table to the table above(expectation) you should see what went wrong. GREEN: matching attributes, RED: mismatching attributes, GRAY: Other texts/animations in display.'"/>
    </xsl:attribute>

    <!-- Select previous node as a test step -->
    <xsl:variable name="teststep" select="preceding-sibling::teststep[@name=current()/@name][1]"/>

    <!-- Unexpect (mismatching) items -->
    <xsl:call-template name="isi-msg-visualizer">
        <xsl:with-param name="teststep-isi" select="$teststep/expect/*[@id=current()/expect/*/@id]"/>
        <xsl:with-param name="highlight-errors" select="true()"/>
        <xsl:with-param name="status" select="true()"/>
    </xsl:call-template>

</xsl:template>

<!--

    Template: teststep-visualizer

    Description: Visualize teststep information.

    Scope: testreport/testcase/teststep
           testreport/testcase/remote/testcase/teststep

    Parameters:

    Output: HTML code

-->
<xsl:template name="teststep-visualizer">
    <xsl:param name="nodes" select="*"/>
    <xsl:param name="timeout" select="@timeout"/>
    <xsl:param name="duration"/>
    <xsl:param name="teststep-id"/>
    <xsl:param name="status"/>

    <!-- Create id used in dynamic visibility -->
    <xsl:attribute name="id">
        <xsl:value-of select="$teststep-id"/>
    </xsl:attribute>

    <!-- special dummy attribute 'status' to identify items -->
    <xsl:attribute name="status">
        <xsl:value-of select="$status"/>
    </xsl:attribute>

    <!-- Add timeout attribute to output if it is present -->
    <xsl:if test="$timeout">
        <div style="text-align:left; font-weight: bold;">Timeout: <xsl:value-of select="$timeout"/></div>
    </xsl:if>

    <!-- Add duration attribute to output if it is present -->
    <xsl:if test="$duration">
        <div style="text-align:left; font-weight: bold;">Duration: <xsl:value-of select="$duration"/></div>
    </xsl:if>

    <!--
        Test if testcase contains ISI messages and create a table for them.
        NOTE: Test case cannot contain ISI messages and user actions mixed!.

        It is ugly to get ISI messages out of following loop, but due to
        the format of current test report XML other implementations
        would be painful.
    -->

    <!-- Repeat visualization actions over all non-isi message teststep elements -->
    <xsl:for-each select="$nodes">

        <xsl:choose>
            <!-- Key input tag -->
            <xsl:when test="name() = 'key_in'">
                <div style="font-weight:bold">Key input sequence:</div>
                <!-- Repeat for each keypress -->
                <div style="margin-left: 2%;">
                    <xsl:for-each select="keypress">
                        <!-- Add key name -->
                        <div class="keyInput">
                            <xsl:value-of select="@key"/>
                        </div>
                        <!-- Add repeat value if required -->
                        <xsl:if test="@repeat">
                            <div class="keyInput">
                                <xsl:text> repeat:</xsl:text>
                                <xsl:value-of select="@repeat"/>
                            </div>
                        </xsl:if>
                        <!-- Add length if not dafault value -->
                        <xsl:if test="@length">
                            <div class="keyInput">
                                <xsl:text> length:</xsl:text>
                                <xsl:value-of select="@length"/>
                                <xsl:text>ms</xsl:text>
                            </div>
                        </xsl:if>
                        <!-- Add wait if not dafault value -->
                        <xsl:if test="@wait">
                            <div class="keyInput">
                                <xsl:text> wait:</xsl:text>
                                <xsl:value-of select="@wait"/>
                                <xsl:text>ms</xsl:text>
                            </div>
                        </xsl:if>
                        <!-- Add hold if required -->
                        <xsl:if test="@hold">
                            <div class="keyInput">
                                <xsl:text> hold:</xsl:text>
                                <xsl:value-of select="@hold"/>
                                <xsl:text>ms</xsl:text>
                            </div>
                        </xsl:if>
                        <!-- Add action if required -->
                        <xsl:if test="@action">
                            <div class="keyInput">
                                <xsl:value-of select="@action"/>
                            </div>
                        </xsl:if>
                        <div class="newLine"/>
                    </xsl:for-each>
                </div>
            </xsl:when>

            <!-- ISI messages already handled in ISI message table case -->
            <xsl:when test="name()= 'isi_req' or name() = 'isi_resp' or name()='isi_ntf' or
                            name()='isi_ind' or name() = 'extra_msg' or name() = 'input' or
                            name() = 'outcome'">
                <xsl:call-template name="teststep-isi-msg"/>
            </xsl:when>

            <!-- Delay tag -->
            <xsl:when test="name() = 'delay'">
                <div style="text-align:left; font-weight: bold;">Delay: <xsl:value-of select="@wait"/></div>
            </xsl:when>

            <!-- Capture -->
            <xsl:when test="name() = 'capture'">
                <xsl:call-template name="teststep-capture"/>
            </xsl:when>

            <!-- Config -->
            <xsl:when test="name() = 'config'">
                <!-- No output -->
            </xsl:when>
            
            <xsl:when test="name() = 'sx'">
                <div style="text-align:left; font-weight: bold;">SX script: <xsl:value-of select="text()"/></div>
            </xsl:when>

            <!-- Expect tag -->
            <xsl:when test="name() = 'expect'">
                <xsl:call-template name="teststep-expect"/>
            </xsl:when>
            
            <!-- Other (unknown) tags -->
            <xsl:otherwise>
                <!-- Call template to output warning messages
                     about unknown tags. -->
                <xsl:call-template name="unknown-tag">
                    <xsl:with-param name="tag" select="name()"/>
                </xsl:call-template>
            </xsl:otherwise>
        </xsl:choose>
    </xsl:for-each>

    <xsl:if test="$nodes/../../@trace">
        <xsl:variable name="ts_name">
            <xsl:choose>
                <xsl:when test="contains($nodes/../@name, '&quot;')">
                    <xsl:call-template name="global-replace">
                        <xsl:with-param name="outputString" select="$nodes/../@name"/>
                        <xsl:with-param name="target" select="'&quot;'"/>
                        <xsl:with-param name="replacement" select="'\&quot;'"/>
                    </xsl:call-template>
                </xsl:when>
                <xsl:otherwise>
                    <xsl:value-of select="$nodes/../@name"/>
                </xsl:otherwise>
            </xsl:choose>
        </xsl:variable>
        <div class="xmlDefaultClass">
            <xsl:attribute name="onclick">
                <xsl:value-of select="concat('getTraceData(this, &quot;', $nodes/../../@trace, '&quot;, &quot;', $ts_name, '&quot;, &quot;', $nodes/../@stepId, '&quot;)')"/>
            </xsl:attribute>
            <xsl:attribute name="onmouseover">
                <xsl:value-of select="'this.className = &quot;xmlHooverClass&quot;'"/>
            </xsl:attribute>
            <xsl:attribute name="onmouseout">
                <xsl:value-of select="'this.className = &quot;xmlDefaultClass&quot;'"/>
            </xsl:attribute>
            <xsl:value-of select="'[Open trace data]'"/>
        </div>
    </xsl:if>

</xsl:template>

<!--

    Template: display-visualizer

    Description: Visualize display items in element.


    Scope:  testreport/testcase/teststep/expect/display or
            testreport/testcase/summary/expect/display or
            testreport/testcase/summary/expect/capture

    Parameters:

    Output: HTML code

-->
<xsl:template name="display-visualizer">
    <xsl:param name="display-elements"/>

    <!-- Determines which display item attributes are present -->
    <xsl:variable name="show-id" select="$display-elements/@id"/>
    <xsl:variable name="show-text" select="$display-elements/."/>
    <xsl:variable name="show-name" select="$display-elements/@name"/>
    <xsl:variable name="show-animation-id" select="$display-elements/@animation_id"/>
    <xsl:variable name="show-x" select="$display-elements/@x"/>
    <xsl:variable name="show-y" select="$display-elements/@y"/>
    <xsl:variable name="show-width" select="$display-elements/@width"/>
    <xsl:variable name="show-height" select="$display-elements/@height"/>
    <xsl:variable name="show-font" select="$display-elements/@font"/>
    <xsl:variable name="show-fg-color" select="$display-elements/@fg"/>
    <xsl:variable name="show-bg-color" select="$display-elements/@bg"/>
    <xsl:variable name="show-highlighted" select="$display-elements/@highlighted"/>
    <xsl:variable name="show-dimmed" select="$display-elements/@dimmed"/>
    <xsl:variable name="show-truncated" select="$display-elements/@truncated"/>
    <xsl:variable name="show-valid" select="$display-elements/@valid"/>
    <xsl:variable name="show-zoneName" select="$display-elements/@zoneName"/>
    <xsl:variable name="show-screen" select="$display-elements/@screen"/>
    <xsl:variable name="show-background" select="$display-elements/@background"/>

    <!-- Begin display items table -->
    <table class="display">
        <!-- If there were errors, use red background, otherwise green -->
        <xsl:if test="name($display-elements/../../..) = 'summary'">
            <xsl:attribute name="style">
               <xsl:value-of select="'cursor: help;'"/>
            </xsl:attribute>
            <xsl:attribute name="onmouseover">
               <xsl:value-of select="'togglePopup(&quot;displayInfoPopup&quot;, event);'"/>
            </xsl:attribute>
            <xsl:attribute name="onmouseout">
                <xsl:value-of select="'togglePopup(&quot;displayInfoPopup&quot;, event);'"/>
            </xsl:attribute>
        </xsl:if>

        <!-- Create footer row for dynamically hidden unknown display items -->
        <xsl:if test="$display-elements/@id = 'unknown'">
            <tfoot>
                <tr>
                    <td style="text-align: center;" colspan="20">
                        <span style="color: blue;" class="onHooverClass" onclick="flipUnknown(this);">[Show other items found on foreground]</span>
                    </td>
                </tr>
            </tfoot>
        </xsl:if>

        <!-- Create display items table header -->
        <tr class="indexHeader">
            <xsl:if test="$show-id"><td>Id</td></xsl:if>
            <xsl:if test="$display-elements"><td>Type</td></xsl:if>
            <xsl:if test="$show-name or $show-text"><td>Text/Anim. Name</td></xsl:if>
            <xsl:if test="$show-animation-id"><td>Anim. Id</td></xsl:if>
            <xsl:if test="$show-highlighted"><td>Highl.</td></xsl:if>
            <xsl:if test="$show-dimmed"><td>Dimm.</td></xsl:if>
            <xsl:if test="$show-truncated"><td>Trunc.</td></xsl:if>
            <xsl:if test="$show-valid"><td>Valid</td></xsl:if>
            <xsl:if test="$show-fg-color"><td>FG Color</td></xsl:if>
            <xsl:if test="$show-bg-color"><td>BG Color</td></xsl:if>
            <xsl:if test="$show-font"><td>Font</td></xsl:if>
            <xsl:if test="$show-zoneName"><td>Zone name</td></xsl:if>
            <xsl:if test="$show-x"><td>X</td></xsl:if>
            <xsl:if test="$show-y"><td>Y</td></xsl:if>
            <xsl:if test="$show-width"><td>W</td></xsl:if>
            <xsl:if test="$show-height"><td>H</td></xsl:if>
            <xsl:if test="$show-screen"><td>Scr.</td></xsl:if>
            <xsl:if test="$show-background"><td>Layer</td></xsl:if>
        </tr>

        <xsl:for-each select="$display-elements">
            <xsl:sort select="@id" data-type="number"/>
            <xsl:sort select="@screen" data-type="number"/>
            <xsl:sort select="@background" data-type="text"/>

            <!-- Label display items with TXT, ANI or  N/A -->
            <xsl:variable name="item-type">
                <xsl:choose>
                    <xsl:when test="@error">
                        <xsl:value-of select="'N/A'"/>
                    </xsl:when>
                    <xsl:when test="name() = 'text'">
                        <xsl:value-of select="'TXT'"/>
                    </xsl:when>
                    <xsl:when test="name() = 'animation'">
                        <xsl:value-of select="'ANI'"/>
                    </xsl:when>
                </xsl:choose>
            </xsl:variable>

            <tr>
                <xsl:call-template name="display-highlight-row"/>

                <!-- text/animation id -->
                <xsl:if test="@id">
                    <td>
                        <xsl:value-of select="@id"/>
                    </td>
                </xsl:if>

                <!-- item type -->
                <td>
                    <xsl:value-of select="$item-type"/>
                </td>

                <xsl:choose>
                    <!-- text/animation error -->
                    <xsl:when test="@error">
                        <xsl:apply-templates select="@error"/>
                    </xsl:when>
                    <!-- text/animation comment -->
                    <xsl:when test="@comment">
                        <xsl:apply-templates select="@comment"/>
                    </xsl:when>
                    <!-- visualize text/animation attributes -->
                    <xsl:otherwise>
                        <!-- text value, animation name -->
                        <xsl:if test="$show-text">
                            <xsl:choose>
                                <xsl:when test="name() = 'text'">
                                    <xsl:call-template name="display-text"/>
                                </xsl:when>
                                <xsl:otherwise>
                                    <xsl:choose>
                                        <xsl:when test="@name">
                                            <xsl:apply-templates select="@name"/>
                                        </xsl:when>
                                        <xsl:otherwise>
                                            <td></td>
                                        </xsl:otherwise>
                                    </xsl:choose>
                                </xsl:otherwise>
                            </xsl:choose>
                        </xsl:if>

                        <!-- animation id -->
                        <xsl:if test="$show-animation-id">
                            <xsl:choose>
                                <xsl:when test="@animation_id">
                                    <xsl:apply-templates select="@animation_id"/>
                                </xsl:when>
                                <xsl:otherwise>
                                    <td></td>
                                </xsl:otherwise>
                            </xsl:choose>
                        </xsl:if>

                        <!-- text/animation highlighted -->
                        <xsl:if test="$show-highlighted">
                            <xsl:choose>
                                <xsl:when test="@highlighted">
                                    <xsl:apply-templates select="@highlighted"/>
                                </xsl:when>
                                <xsl:otherwise>
                                    <td></td>
                                </xsl:otherwise>
                            </xsl:choose>
                        </xsl:if>

                        <!-- text/animation dimmed -->
                        <xsl:if test="$show-dimmed">
                            <xsl:choose>
                                <xsl:when test="@dimmed">
                                    <xsl:apply-templates select="@dimmed"/>
                                </xsl:when>
                                <xsl:otherwise>
                                    <td></td>
                                </xsl:otherwise>
                            </xsl:choose>
                        </xsl:if>

                        <!-- text truncated -->
                        <xsl:if test="$show-truncated">
                            <xsl:choose>
                                <xsl:when test="@truncated">
                                    <xsl:apply-templates select="@truncated"/>
                                </xsl:when>
                                <xsl:otherwise>
                                    <td></td>
                                </xsl:otherwise>
                            </xsl:choose>
                        </xsl:if>

                        <!-- text/animation valid -->
                        <xsl:if test="$show-valid">
                            <xsl:choose>
                                <xsl:when test="@valid">
                                    <xsl:apply-templates select="@valid"/>
                                </xsl:when>
                                <xsl:otherwise>
                                    <td></td>
                                </xsl:otherwise>
                            </xsl:choose>
                        </xsl:if>

                        <!-- text foreground color -->
                        <xsl:if test="$show-fg-color">
                            <xsl:choose>
                                <xsl:when test="@fg">
                                    <xsl:apply-templates select="@fg"/>
                                </xsl:when>
                                <xsl:otherwise>
                                    <td></td>
                                </xsl:otherwise>
                            </xsl:choose>
                        </xsl:if>

                        <!-- text background color -->
                        <xsl:if test="$show-bg-color">
                            <xsl:choose>
                                <xsl:when test="@bg">
                                    <xsl:apply-templates select="@bg"/>
                                </xsl:when>
                                <xsl:otherwise>
                                    <td></td>
                                </xsl:otherwise>
                            </xsl:choose>
                        </xsl:if>

                        <!-- text font -->
                        <xsl:if test="$show-font">
                            <xsl:choose>
                                <xsl:when test="@font">
                                    <xsl:apply-templates select="@font"/>
                                </xsl:when>
                                <xsl:otherwise>
                                    <td></td>
                                </xsl:otherwise>
                            </xsl:choose>
                        </xsl:if>

                        <!-- text/animation zoneName -->
                       <xsl:if test="$show-zoneName">
                            <xsl:choose>
                                <xsl:when test="@zoneName">
                                    <xsl:apply-templates select="@zoneName"/>
                                </xsl:when>
                                <xsl:otherwise>
                                    <td></td>
                                </xsl:otherwise>
                            </xsl:choose>
                        </xsl:if>

                        <!-- text/animation x cordinate -->
                        <xsl:if test="$show-x">
                            <xsl:choose>
                                <xsl:when test="@x">
                                    <xsl:apply-templates select="@x"/>
                                </xsl:when>
                                <xsl:otherwise>
                                    <td></td>
                                </xsl:otherwise>
                            </xsl:choose>
                        </xsl:if>

                        <!-- text/animation y cordinate -->
                        <xsl:if test="$show-y">
                            <xsl:choose>
                                <xsl:when test="@y">
                                    <xsl:apply-templates select="@y"/>
                                </xsl:when>
                                <xsl:otherwise>
                                    <td></td>
                                </xsl:otherwise>
                            </xsl:choose>
                        </xsl:if>

                        <!-- text/animation width -->
                        <xsl:if test="$show-width">
                            <xsl:choose>
                                <xsl:when test="@width">
                                    <xsl:apply-templates select="@width"/>
                                </xsl:when>
                                <xsl:otherwise>
                                    <td></td>
                                </xsl:otherwise>
                            </xsl:choose>
                        </xsl:if>

                        <!-- text/animation height -->
                        <xsl:if test="$show-height">
                            <xsl:choose>
                                <xsl:when test="@height">
                                    <xsl:apply-templates select="@height"/>
                                </xsl:when>
                                <xsl:otherwise>
                                    <td></td>
                                </xsl:otherwise>
                            </xsl:choose>
                        </xsl:if>

                        <!-- text/animation screen -->
                        <xsl:if test="$show-screen">
                            <xsl:choose>
                                <xsl:when test="@screen">
                                    <xsl:apply-templates select="@screen"/>
                                </xsl:when>
                                <xsl:otherwise>
                                    <td></td>
                                </xsl:otherwise>
                            </xsl:choose>
                        </xsl:if>

                        <!-- text/animation screen -->
                        <xsl:if test="$show-background">
                            <xsl:choose>
                                <xsl:when test="@background">
                                    <xsl:apply-templates select="@background"/>
                                </xsl:when>
                                <xsl:otherwise>
                                    <td>FG</td>
                                </xsl:otherwise>
                            </xsl:choose>
                        </xsl:if>
                    </xsl:otherwise>
                </xsl:choose>
            </tr>
        </xsl:for-each>
    </table>

</xsl:template>

<xsl:template name="display-text">

    <td style="white-space: nowrap">
        <xsl:if test="contains(@errorItems, 'content')">
            <xsl:variable name="expect-value" select="../../../preceding-sibling::teststep[@name=current()/../../../@name][1]/expect/display/*[@id = current()/@id]"/>
            <xsl:attribute name="class">
                <xsl:value-of select="'error'"/>
            </xsl:attribute>
            <xsl:attribute name="title">
                <xsl:value-of select="concat('Expected text: ', '&quot;', $expect-value/., '&quot;')"/>
            </xsl:attribute>
        </xsl:if>
        <xsl:if test=". != ''">
            <xsl:attribute name="onclick">
                <xsl:value-of select="'ucHexDump(this)'"/>
            </xsl:attribute>
        </xsl:if>
        <pre class="showWs">
            <xsl:choose>
                <xsl:when test=". != ''">
                    <xsl:value-of select="."/>
                </xsl:when>
                <xsl:otherwise>
                    <i><xsl:value-of select="'(Empty string)'"/></i>
                </xsl:otherwise>
            </xsl:choose>
        </pre>
    </td>

</xsl:template>

<xsl:template match="@error">
    <td style="white-space: nowrap; text-align: center; font-style: italic" colspan="20">
        <xsl:value-of select="."/>
    </td>
</xsl:template>

<xsl:template match="@comment">
    <td style="white-space: nowrap; text-align: center; font-style: italic" colspan="20">
        <xsl:value-of select="."/>
    </td>
</xsl:template>

<xsl:template match="@name">

    <td style="white-space: nowrap">
        <xsl:if test="contains(../@errorItems, 'content')">
            <xsl:variable name="expect-value" select="../../../../preceding-sibling::teststep[@name=current()/../../../../@name][1]/expect/display/*[@id = current()/../@id]"/>
            <xsl:attribute name="class">
                <xsl:value-of select="'error'"/>
            </xsl:attribute>
            <xsl:attribute name="title">
                <xsl:value-of select="concat('Expected: ', '&quot;', $expect-value/@name, '&quot;')"/>
            </xsl:attribute>
        </xsl:if>
        <xsl:value-of select="."/>
    </td>

</xsl:template>

<xsl:template match="@highlighted|@dimmed|@truncated|@valid|@font|@zoneName|@x|@y|@width|@height|@screen">

    <td style="white-space: nowrap">
        <xsl:if test="contains(../@errorItems, name())">
            <xsl:variable name="expect-value" select="../../../../preceding-sibling::teststep[@name=current()/../../../../@name][1]/expect/display/*[@id = current()/../@id]"/>
            <xsl:attribute name="class">
                <xsl:value-of select="'error'"/>
            </xsl:attribute>
            <xsl:attribute name="title">
                <xsl:value-of select="concat('Expected: ', $expect-value/@*[name() = name(current())])"/>
            </xsl:attribute>
        </xsl:if>
         <xsl:if test="name() = 'x' or name() = 'y' or name() = 'width' or name() = 'height'">
            <xsl:attribute name="name">
                <xsl:value-of select="name()"/>
            </xsl:attribute>
        </xsl:if>
        <xsl:value-of select="."/>
    </td>

</xsl:template>

<xsl:template match="@background">

    <td style="white-space: nowrap">
        <xsl:if test="contains(../@errorItems, name())">
            <xsl:attribute name="class">
                <xsl:value-of select="'error'"/>
            </xsl:attribute>
            <xsl:choose>
                <xsl:when test=". = 'yes'">
                    <xsl:attribute name="title">
                        <xsl:value-of select="'Expected: FG'"/>
                    </xsl:attribute>
                </xsl:when>
                <xsl:when test=". = 'no'">
                    <xsl:attribute name="title">
                        <xsl:value-of select="'Expected: BG'"/>
                    </xsl:attribute>
                </xsl:when>
            </xsl:choose>
        </xsl:if>

        <xsl:choose>
            <xsl:when test=". = 'all'">
                <xsl:value-of select="'FG/BG'"/>
            </xsl:when>
            <xsl:when test=". = 'yes'">
                <xsl:value-of select="'BG'"/>
            </xsl:when>
            <xsl:when test=". = 'no'">
                <xsl:value-of select="'FG'"/>
            </xsl:when>
        </xsl:choose>
    </td>

</xsl:template>

<xsl:template match="@animation_id|@fg|@bg">

    <xsl:variable name="error-name">
        <xsl:choose>
            <xsl:when test="name() = 'animation_id'">
                <xsl:value-of select="'content'"/>
            </xsl:when>
            <xsl:otherwise>
                <xsl:value-of select="name()"/>
            </xsl:otherwise>
        </xsl:choose>
    </xsl:variable>

    <td style="white-space: nowrap">
        <xsl:if test="contains(../@errorItems, $error-name)">
            <xsl:variable name="expect-value" select="../../../../preceding-sibling::teststep[@name=current()/../../../../@name][1]/expect/display/*[@id = current()/../@id]"/>
            <xsl:attribute name="class">
                <xsl:value-of select="'error'"/>
            </xsl:attribute>
            <xsl:attribute name="title">
                <xsl:value-of select="'Expected: '"/>
                <xsl:call-template name="add-padding">
                    <xsl:with-param name="value">
                        <xsl:call-template name="dec-to-hex">
                            <xsl:with-param name="number" select="$expect-value/@*[name() = name(current())]"/>
                        </xsl:call-template>
                    </xsl:with-param>
                </xsl:call-template>
            </xsl:attribute>
        </xsl:if>
        <xsl:call-template name="add-padding">
            <xsl:with-param name="value">
                <xsl:call-template name="dec-to-hex">
                    <xsl:with-param name="number" select="."/>
                </xsl:call-template>
            </xsl:with-param>
       </xsl:call-template>
    </td>

</xsl:template>

<xsl:template name="display-highlight-row">

    <!-- Create a row for the attribute table for this txt/animation item -->
    <!-- Highlighting functionality for comparing results -->
    <xsl:variable name="bitmap-name">
        <xsl:choose>
            <xsl:when test="name(../../..) = 'teststep'">
                <!-- Assign ids for rows in last expectation before NOT EXPECTED RESULT -->
                <xsl:value-of select="../../../following-sibling::summary[@name=current()/../../../@name][1]/expect/display[@id=current()/../@id]/bitmap[@screen=current()/@screen]/@name"/>
            </xsl:when>
            <xsl:when test="name(../../..) = 'summary'">
                <!-- Assign onmouseover, onmouseout functions for rows in NOT EXPECTED RESULT -->
                <xsl:value-of select="../../display[@id=current()/../@id]/bitmap[@screen=current()/@screen]/@name"/>
            </xsl:when>
            <xsl:otherwise>
                <!-- Assign onmouseover, onmouseout functions for rows in CAPTURE -->
                <xsl:value-of select="../bitmap[@screen=current()/@screen]/@name"/>
            </xsl:otherwise>
        </xsl:choose>
    </xsl:variable>

    <xsl:variable name="reference-id">
        <xsl:choose>
            <xsl:when test="name(../../..) = 'teststep'">
                <!-- Assign ids for rows in last expectation before NOT EXPECTED RESULT -->
                <xsl:value-of select="generate-id(../../../following-sibling::summary[@name=current()/../../../@name][1]/expect/display/*[@id=current()/@id])"/>
            </xsl:when>
            <xsl:when test="name(../../..) = 'summary' and @id != 'unknown'">
                <!-- Assign onmouseover, onmouseout functions for rows in NOT EXPECTED RESULT -->
                <xsl:value-of select="generate-id(../../../preceding-sibling::teststep[@name=current()/../../../@name][1]/expect/display/*[@id=current()/@id])"/>
            </xsl:when>
        </xsl:choose>
    </xsl:variable>

    <xsl:choose>
        <xsl:when test="$reference-id != ''">
            <xsl:attribute name="id">
                <xsl:value-of select="generate-id(current())"/>
            </xsl:attribute>
        </xsl:when>
       <xsl:when test="@id = 'unknown' and @background = 'yes'">
            <xsl:attribute name="id">
                <xsl:value-of select="'unknown-bg'"/>
            </xsl:attribute>
            <xsl:attribute name="style">
                <xsl:value-of select="'display: none;'"/>
            </xsl:attribute>
        </xsl:when>
       <xsl:when test="@id = 'unknown' and @background = 'no'">
            <xsl:attribute name="id">
                <xsl:value-of select="'unknown-fg'"/>
            </xsl:attribute>
            <xsl:attribute name="style">
                <xsl:value-of select="'display: none;'"/>
            </xsl:attribute>
        </xsl:when>
    </xsl:choose>

    <xsl:attribute name="bgcolor">
        <xsl:choose>
            <xsl:when test="name(../../..) = 'teststep'">
                <xsl:value-of select="'#CCffCC'"/>
            </xsl:when>
            <xsl:when test="name(../../..) = 'summary'">
                <xsl:choose>
                    <xsl:when test="@id = 'unknown'">
                        <xsl:value-of select="'#EEeeEE'"/>
                    </xsl:when>
                    <xsl:when test="@error">
                        <!-- RED row background color error text/animation -->
                        <xsl:value-of select="'#FFccCC'"/>
                    </xsl:when>
                    <xsl:otherwise>
                        <!-- GREEN row background color text/animation -->
                         <xsl:value-of select="'#CCffCC'"/>
                    </xsl:otherwise>
                </xsl:choose>
            </xsl:when>
            <xsl:otherwise>
                <xsl:value-of select="'#EEeeEE'"/>
            </xsl:otherwise>
        </xsl:choose>
    </xsl:attribute>

    <xsl:if test="$bitmap-name != '' or @error or @comment">
        <xsl:variable name="bitmap-id" select="substring-before($bitmap-name, '.png')"/>
        <xsl:attribute name="onmouseover">
            <xsl:value-of select="concat('highLightRow(this, &quot;hooverDisplay&quot;, &quot;', $bitmap-id, '&quot;, &quot;', $reference-id, '&quot;)')"/>
        </xsl:attribute>
        <xsl:attribute name="onmouseout">
            <xsl:value-of select="concat('highLightRow(this, &quot;&quot;, &quot;', $bitmap-id, '&quot;, &quot;', $reference-id, '&quot;)')"/>
        </xsl:attribute>
    </xsl:if>

</xsl:template>

<!--

    Template: bitmap-visualizer

    Description: Visualize error, reference, trained or captured bitmap(s).

    Scope:  testreport/testcase/summary/expect/display/bitmap
            testreport/testcase/remote/testcase/summary/expect/display/bitmap

    Parameters:

    Output:
        HTML code <td><table>...</table></td>.

-->
<xsl:template name="bitmap-visualizer">
    <xsl:param name="bitmap-id"/>
    <xsl:param name="selection" select="."/>

    <xsl:if test="$selection/@error_name">
        <xsl:variable name="error-id" select="concat($bitmap-id, '-error')"/>
        <xsl:variable name="reference-id" select="concat($bitmap-id, '-reference')"/>
        <xsl:variable name="reference-name" select="concat('reference bitmaps', substring-after($selection/@error_name, 'error bitmaps'))"/>
        <xsl:variable name="bitmapDB" select="$settings/setting[@name='FRAMEWORK_CONFIGURATION_BITMAP_DB']"/>
        <div style="float:left">
            <xsl:attribute name="id">
                <xsl:value-of select="$reference-id"/>
            </xsl:attribute>
            <div style="text-align: left; font-weight: bold;">
                <xsl:value-of select="'Reference bitmap:'"/>
            </div>
            <!-- Draw captured bitmaps -->
            <xsl:choose>
                <xsl:when test="$selection/@training">
                    <xsl:call-template name="select-bitmap-attributes">
                        <xsl:with-param name="file-name" select="$reference-name"/>
                        <xsl:with-param name="existing" select="false()"/>
                    </xsl:call-template>
                </xsl:when>
                <xsl:otherwise>
                    <xsl:call-template name="select-bitmap-attributes">
                        <xsl:with-param name="file-name" select="$selection/@reference_name"/>
                    </xsl:call-template>
                </xsl:otherwise>
            </xsl:choose>
        </div>
        <div style="margin-top: 70px; margin-left: 20px; margin-right: 20px; float:left; text-align: center;">
            <p><input style="margin-bottom: 5px;">
                <xsl:attribute name="type">
                    <xsl:value-of select="'button'"/>
                </xsl:attribute>
                <xsl:choose>
                    <xsl:when test="$selection/@training">
                        <xsl:attribute name="value">
                            <xsl:value-of select="'Accept'"/>
                        </xsl:attribute>
                        <xsl:attribute name="onclick">
                            <xsl:value-of select="concat('oFileSystem.updateReference(this, ', '&quot;', $selection/@error_name, '&quot;', ', &quot;', $reference-name, '&quot;', ', &quot;', $bitmap-id, '&quot;', ', &quot;', translate($bitmapDB, '\\', '/'), '&quot;)')"/>
                        </xsl:attribute>
                    </xsl:when>
                    <xsl:otherwise>
                        <xsl:attribute name="value">
                            <xsl:value-of select="'Update reference'"/>
                        </xsl:attribute>
                        <xsl:attribute name="onclick">
                            <xsl:value-of select="concat('oFileSystem.updateReference(this, ', '&quot;', $selection/@error_name, '&quot;', ', &quot;', $selection/@reference_name, '&quot;', ', &quot;', $bitmap-id, '&quot;', ', &quot;', translate($bitmapDB, '\\', '/'), '&quot;)')"/>
                        </xsl:attribute>
                    </xsl:otherwise>
                </xsl:choose>
                <xsl:attribute name="title">
                        <xsl:value-of select="'Accept(copy) captured image as reference'"/>
                </xsl:attribute>
            </input>
            <br/>
            <input>
                <xsl:attribute name="type">
                    <xsl:value-of select="'button'"/>
                </xsl:attribute>
                <xsl:choose>
                    <xsl:when test="$selection/@training">
                        <xsl:attribute name="value">
                            <xsl:value-of select="'Reject'"/>
                        </xsl:attribute>
                        <xsl:attribute name="title">
                                <xsl:value-of select="'Reject captured image as reference'"/>
                        </xsl:attribute>
                        <xsl:attribute name="onclick">
                            <xsl:value-of select="concat('oFileSystem.rejectReference(this, ', '&quot;', $reference-name, '&quot;', ', &quot;', $bitmap-id, '&quot;)')"/>
                        </xsl:attribute>
                    </xsl:when>
                    <xsl:otherwise>
                        <xsl:attribute name="value">
                            <xsl:value-of select="'Delete reference'"/>
                        </xsl:attribute>
                        <xsl:attribute name="title">
                                <xsl:value-of select="'Delete current reference bitmap'"/>
                        </xsl:attribute>
                        <xsl:attribute name="onclick">
                            <xsl:value-of select="concat('oFileSystem.rejectReference(this, ', '&quot;', $selection/@reference_name, '&quot;', ', &quot;', $bitmap-id, '&quot;', ', &quot;', translate($bitmapDB, '\\', '/'), '&quot;)')"/>
                        </xsl:attribute>
                    </xsl:otherwise>
                </xsl:choose>
            </input></p>
        </div>
        <div style="float:left">
            <xsl:attribute name="id">
                <xsl:value-of select="$error-id"/>
            </xsl:attribute>
            <div style="text-align: left; font-weight: bold;">
                <xsl:value-of select="'Captured bitmap:'"/>
            </div>
            <!-- Draw captured bitmaps -->
            <xsl:call-template name="select-bitmap-attributes">
                <xsl:with-param name="file-name" select="$selection/@error_name"/>
            </xsl:call-template>
            <div style="text-align: left; font-weight: bold;">
                <xsl:call-template name="extract-from-path">
                    <xsl:with-param name="path" select="$selection/@error_name"/>
                </xsl:call-template>
                <xsl:value-of select="concat(' (', $selection/@checksum, ')')"/>
            </div>
        </div>
        <div class="newLine"/>
    </xsl:if>
    <xsl:if test="$selection/@name">
        <div style="text-align: left; font-weight: bold;">
            <xsl:value-of select="'Captured bitmap:'"/>
        </div>
        <!-- Draw captured bitmaps -->
        <xsl:choose>
            <xsl:when test="starts-with($selection/@name, 'error') or starts-with($selection/@name, 'remote_error')">
                <xsl:call-template name="select-bitmap-attributes">
                    <xsl:with-param name="file-name" select="concat('error%20bitmaps/', $selection/@name)"/>
                    <xsl:with-param name="error-capture" select="true()"/>
                </xsl:call-template>
            </xsl:when>
            <xsl:otherwise>
                <xsl:call-template name="select-bitmap-attributes">
                    <xsl:with-param name="file-name" select="concat('captured%20bitmaps/', $selection/@name)"/>
                    <xsl:with-param name="error-capture" select="true()"/>
                </xsl:call-template>
            </xsl:otherwise>
        </xsl:choose>
        <div style="text-align: left; font-weight: bold;">
            <xsl:value-of select="$selection/@name"/>
        </div>
        <div class="newLine"/>
    </xsl:if>

</xsl:template>

<!--

    Template: bitmap-verify-visualizer

    Description: Visualize bitmap verify attributes.

    Scope:  testreport/testcase/teststep/expect/display/bitmap
            testreport/testcase/remote/testcase/teststep/expect/display/bitmap

    Parameters:

    Output:
        HTML code <table>...</table> or no code if the selection
        set is empty.

-->
<xsl:template name="bitmap-verify-visualizer">

    <!-- Create table for ISI messages -->
    <table class="display">
        <!-- GREEN table background color -->
        <xsl:attribute name="style">background-color: #ccFFcc</xsl:attribute>
        <!-- Create text table header -->
        <tr class="indexHeader">
            <xsl:if test="@checksum"><td>Checksum</td></xsl:if>
            <xsl:if test="@screen"><td>Screen</td></xsl:if>
        </tr>
        <!-- Create a row for the item table for this bitmap element -->
        <tr>
            <!-- GREEN row background color -->
            <xsl:attribute name="bgcolor">#ccFFcc</xsl:attribute>
            <xsl:for-each select="@*">
                <!-- bitmap verify length -->
                <xsl:if test="name()='checksum'">
                    <td><xsl:value-of select="."/></td>
                </xsl:if>
                <!-- bitmap verify gap -->
                <xsl:if test="name()='screen'">
                    <td><xsl:value-of select="."/></td>
                </xsl:if>
            </xsl:for-each>
        </tr>
    </table>

</xsl:template>

<!--

    Template: capture-visualizer

    Description: Visualize teststep captures.

        Gets capture id. With this id looks up capture information in
        summary and renders with through teststep-expect-display.

    Scope:  testreport/testcase/teststep/capture
            testreport/testcase/remote/testcase/teststep/capture

    Output: HTML code

-->
<xsl:template name="capture-visualizer">

    <!-- Choose matching <capture> under <summary>.
    This contains the actual contents of a capture. -->

    <div class="capture">
        <div style="text-align:left; font-weight: bold;">Capture name: <xsl:value-of select="@name"/></div>
        <!-- Left side, text and animation -->
        <xsl:if test="text or animation or bitmap">
            <!-- When called from summary/display or summary/capture,
            we don't have layout name. In that case do not print layout label. -->
            <!-- Align left/right labels with an empty line-->
            <!-- <br/> -->
            <xsl:call-template name="teststep-expect-display">
                <xsl:with-param name="display-elements" select="text|animation"/>
                <xsl:with-param name="bitmap-elements" select="bitmap"/>
            </xsl:call-template>
        </xsl:if>
    </div>

</xsl:template>

<!--

    Template: isi-msg-visualizer

    Description: Visualize ISI message attributes.

        *Input & outcome needs special attentation - they
        have more attributes than others.

    Scope:  testreport/testcase/teststep/expect/isi_req
            testreport/testcase/summary/expect/isi_resp
            testreport/testcase/summary/expect/isi_ntf
            testreport/testcase/summary/expect/isi_ind
            testreport/testcase/summary/expect/extra_msg
            testreport/testcase/summary/expect/input
            testreport/testcase/summary/expect/outcome

    Parameters:
        selection:
            description:
                The node set of isi messages for the table.
                If the node set is empty, no table is produced.
            default value:
                none - the parameter is mandatory
            example:
                isi_req|isi_resp|isi_ntf|isi_ind|extra_msg

    Output:
        HTML code <table>...</table> or no code if the selection
        set is empty.

-->
<xsl:template name="isi-msg-visualizer">
    <xsl:param name="teststep-isi"/>
    <xsl:param name="highlight-errors" select="false()"/>
    <xsl:param name="status" select="false()"/>

    <!-- Do nothing if we have empty node set as the teststep-isi -->
    <xsl:if test="$teststep-isi">

        <!-- From isimessage.py:

            input & outcome contains following attributes:

            basic_fields = ['media', 'recv_dev', 'send_dev', 'resource', 'length',
                       'recv_obj', 'send_obj', 'utid', 'msg_id']

            isi_* and extra_msg don't have all of them (srvtestcase.py)

            Don't show extra columns unless needed.
        -->

        <xsl:variable name="id" select="$teststep-isi/@id"/>
        <xsl:variable name="msg_type" select="name($teststep-isi)"/>
        <xsl:variable name="msg_id" select="$teststep-isi/@msg_id"/>
        <xsl:variable name="resource" select="$teststep-isi/@resource"/>
        <xsl:variable name="utid" select="$teststep-isi/@utid"/>
        <xsl:variable name="timeout" select="$teststep-isi/@timeout"/>
        <xsl:variable name="media" select="$teststep-isi/@media"/>
        <xsl:variable name="recv_dev" select="$teststep-isi/@recv_dev"/>
        <xsl:variable name="send_dev" select="$teststep-isi/@send_dev"/>
        <xsl:variable name="send_obj" select="$teststep-isi/@send_obj"/>
        <xsl:variable name="length" select="$teststep-isi/@length"/>
        <xsl:variable name="data" select="$teststep-isi/."/>

        <!-- $extra-columns contain non-null value if input/outcome extra columns are needed.
        This is detected using the timeout attribute as a bate. -->
        <xsl:variable name="extra-columns" select="$teststep-isi/@timeout"/>

        <!-- Create table for ISI messages -->
        <table class="display">

            <!-- GREEN table background color -->
            <xsl:attribute name="style">background-color: #ccFFcc</xsl:attribute>

            <!-- Create text table header -->
            <tr class="indexHeader">
                <xsl:if test="$id"><td>Id</td></xsl:if>
                <xsl:if test="$msg_type"><td>Msg. type</td></xsl:if>
                <xsl:if test="$msg_id"><td>Msg. ID</td></xsl:if>
                <xsl:if test="$resource"><td>Resource</td></xsl:if>
                <xsl:if test="$utid"><td>UTID</td></xsl:if>
                <xsl:if test="$timeout"><td>Timeout</td></xsl:if>
                <xsl:if test="$media"><td>Media</td></xsl:if>
                <xsl:if test="$recv_dev"><td>Recv. dev.</td></xsl:if>
                <xsl:if test="$send_dev"><td>Send. dev.</td></xsl:if>
                <xsl:if test="$send_obj"><td>Send. obj.</td></xsl:if>
                <xsl:if test="$length"><td>Length</td></xsl:if>
                <xsl:if test="$data"><td>Data</td></xsl:if>
            </tr>

            <xsl:for-each select="$teststep-isi">
                <!-- teststep name attribute not present in isi message summaries -->
                <xsl:variable name="summary" select="../../following-sibling::summary[@name=current()/../../@name][1]"/>
                <xsl:variable name="summary-message" select="$summary/expect/*[@id = current()/@id]"/>

                <!-- isi messages attributes -->
                <xsl:variable name="unexp-msg_type" select="name($summary-message)"/>
                <xsl:variable name="unexp-msg_id" select="$summary-message/@msg_id"/>
                <xsl:variable name="unexp-resource" select="$summary-message/@resource"/>
                <xsl:variable name="unexp-utid" select="$summary-message/@utid"/>
                <xsl:variable name="unexp-timeout" select="$summary-message/@timeout"/>
                <xsl:variable name="unexp-media" select="$summary-message/@media"/>
                <xsl:variable name="unexp-recv_dev" select="$summary-message/@recv_dev"/>
                <xsl:variable name="unexp-send_dev" select="$summary-message/@send_dev"/>
                <xsl:variable name="unexp-send_obj" select="$summary-message/@send_obj"/>
                <xsl:variable name="unexp-length" select="$summary-message/@length"/>
                <xsl:variable name="unexp-data" select="$summary-message/."/>

                <!-- Create a row for the item table for this txt/anim element -->
                <tr>
                    <!-- GREEN row background color -->
                    <xsl:attribute name="bgcolor">#ccFFcc</xsl:attribute>

                    <!-- id -->
                    <td>
                        <xsl:value-of select="@id"/>
                    </td>

                    <!-- isi message type -->
                    <xsl:if test="$msg_type">
                        <xsl:choose>
                            <xsl:when test="$highlight-errors and  not($msg_type = $unexp-msg_type)">
                                <td class="error"><xsl:value-of select="$unexp-msg_type"/></td>
                            </xsl:when>
                            <xsl:otherwise>
                                <td><xsl:value-of select="name()"/></td>
                            </xsl:otherwise>
                        </xsl:choose>
                    </xsl:if>

                    <!-- isi message id -->
                    <xsl:if test="$msg_id">
                        <xsl:choose>
                            <xsl:when test="$highlight-errors and $unexp-msg_id">
                                <td class="error"><xsl:value-of select="$unexp-msg_id"/></td>
                            </xsl:when>
                            <xsl:otherwise>
                                <td><xsl:value-of select="@msg_id"/></td>
                            </xsl:otherwise>
                        </xsl:choose>
                    </xsl:if>

                    <!-- isi message resource -->
                    <xsl:if test="$resource">
                        <xsl:choose>
                            <xsl:when test="$highlight-errors and $unexp-resource">
                                <td class="error"><xsl:value-of select="$unexp-resource"/></td>
                            </xsl:when>
                            <xsl:otherwise>
                                <td><xsl:value-of select="@resource"/></td>
                            </xsl:otherwise>
                        </xsl:choose>
                    </xsl:if>

                    <!-- isi message unique transaction id -->
                    <xsl:if test="$utid">
                        <xsl:choose>
                            <xsl:when test="$highlight-errors and $unexp-utid">
                                <td class="error"><xsl:value-of select="$unexp-utid"/></td>
                            </xsl:when>
                            <xsl:otherwise>
                                <td><xsl:value-of select="@utid"/></td>
                            </xsl:otherwise>
                        </xsl:choose>
                    </xsl:if>

                    <!-- isi message timeout -->
                    <xsl:if test="$timeout">
                        <xsl:choose>
                            <xsl:when test="$highlight-errors and $unexp-timeout">
                                <td class="error"><xsl:value-of select="$unexp-timeout"/></td>
                            </xsl:when>
                            <xsl:otherwise>
                                <td><xsl:value-of select="@timeout"/></td>
                            </xsl:otherwise>
                        </xsl:choose>
                    </xsl:if>

                    <!-- isi message media -->
                    <xsl:if test="$media">
                        <xsl:choose>
                            <xsl:when test="$highlight-errors and $unexp-media">
                                <td class="error"><xsl:value-of select="$unexp-media"/></td>
                            </xsl:when>
                            <xsl:otherwise>
                                <td><xsl:value-of select="@media"/></td>
                            </xsl:otherwise>
                        </xsl:choose>
                    </xsl:if>

                    <!-- isi message receiver device -->
                    <xsl:if test="$recv_dev">
                        <xsl:choose>
                            <xsl:when test="$highlight-errors and $unexp-recv_dev">
                                <td class="error"><xsl:value-of select="$unexp-recv_dev"/></td>
                            </xsl:when>
                            <xsl:otherwise>
                                <td><xsl:value-of select="@recv_dev"/></td>
                            </xsl:otherwise>
                        </xsl:choose>
                    </xsl:if>

                    <!-- isi message sender device -->
                    <xsl:if test="$send_dev">
                        <xsl:choose>
                            <xsl:when test="$highlight-errors and $unexp-send_dev">
                                <td class="error"><xsl:value-of select="$unexp-send_dev"/></td>
                            </xsl:when>
                            <xsl:otherwise>
                                <td><xsl:value-of select="@send_dev"/></td>
                            </xsl:otherwise>
                        </xsl:choose>
                    </xsl:if>

                    <!-- isi message sender object -->
                    <xsl:if test="$send_obj">
                        <xsl:choose>
                            <xsl:when test="$highlight-errors and $unexp-send_obj">
                                <td class="error"><xsl:value-of select="$unexp-send_obj"/></td>
                            </xsl:when>
                            <xsl:otherwise>
                                <td><xsl:value-of select="@send_obj"/></td>
                            </xsl:otherwise>
                        </xsl:choose>
                    </xsl:if>

                    <!-- isi message length -->
                    <xsl:if test="$length">
                        <xsl:choose>
                            <xsl:when test="$highlight-errors and $unexp-length">
                                <td class="error"><xsl:value-of select="$unexp-length"/></td>
                            </xsl:when>
                            <xsl:otherwise>
                                <td><xsl:value-of select="@length"/></td>
                            </xsl:otherwise>
                        </xsl:choose>
                    </xsl:if>

                    <!-- isi message data -->
                    <xsl:if test="$data">
                        <xsl:choose>
                            <xsl:when test="$highlight-errors and $unexp-data">
                                <td class="error"><xsl:value-of select="$unexp-data"/></td>
                            </xsl:when>
                            <xsl:otherwise>
                                <td><xsl:value-of select="."/></td>
                            </xsl:otherwise>
                        </xsl:choose>
                    </xsl:if>

                </tr>
            </xsl:for-each>

        </table>
    </xsl:if>
</xsl:template>

<!--

    Template: select-bitmap-attributes

    Description:
        Select main/remote bitmap attributes.

    Scope:  testreport/testcase/summary/expect/display/bitmap
            testreport/testcase/remote/testcase/summary/expect/display/bitmap

    Parameters:

    Output:

-->
<xsl:template name="select-bitmap-attributes">
    <xsl:param name="file-name"/>
    <xsl:param name="error-capture" select="false()"/>
    <xsl:param name="existing" select="true()"/>

    <xsl:variable name="remote-phone" select="name(../../../../..) = 'remote' or name(../../../../../..) = 'remote'"/>

    <xsl:choose>
        <xsl:when test="$remote-phone">
            <xsl:call-template name="set-bitmap-attributes">
                <xsl:with-param name="file-name" select="$file-name"/>
                <xsl:with-param name="error-capture" select="$error-capture"/>
                <xsl:with-param name="existing" select="$existing"/>
                <xsl:with-param name="md-width" select="$remote-md-width"/>
                <xsl:with-param name="md-height" select="$remote-md-height"/>
                <xsl:with-param name="sd-width" select="$remote-sd-width"/>
                <xsl:with-param name="sd-height" select="$remote-sd-height"/>
            </xsl:call-template>
        </xsl:when>
        <xsl:otherwise>
            <xsl:call-template name="set-bitmap-attributes">
                <xsl:with-param name="file-name" select="$file-name"/>
                <xsl:with-param name="error-capture" select="$error-capture"/>
                <xsl:with-param name="existing" select="$existing"/>
                <xsl:with-param name="md-width" select="$main-md-width"/>
                <xsl:with-param name="md-height" select="$main-md-height"/>
                <xsl:with-param name="sd-width" select="$main-sd-width"/>
                <xsl:with-param name="sd-height" select="$main-sd-height"/>
            </xsl:call-template>
        </xsl:otherwise>
    </xsl:choose>
</xsl:template>

<!--

    Template: set-bitmap-attributes

    Description:
        Set bitmap attributes.

    Scope:  testreport/testcase/summary/expect/display/bitmap
            testreport/testcase/remote/testcase/summary/expect/display/bitmap

    Parameters:

    Output:
        HTML code <div><div>...</div></div>.

-->
<xsl:template name="set-bitmap-attributes">
    <xsl:param name="file-name"/>
    <xsl:param name="error-capture"/>
    <xsl:param name="existing"/>
    <xsl:param name="md-width"/>
    <xsl:param name="md-height"/>
    <xsl:param name="sd-width"/>
    <xsl:param name="sd-height"/>

    <div class='bitmap'>
        <xsl:if test="($single-testcase or $email-testcase) and $existing">
            <xsl:attribute name="id">
                <xsl:value-of select="'copy-image'"/>
            </xsl:attribute>
        </xsl:if>
        <xsl:attribute name="style">
            <xsl:choose>
                <xsl:when test="@screen = '2'">
                    <xsl:if test="$sd-width">
                        <xsl:value-of select="concat('width: ', $sd-width, 'px; ')"/>
                        <xsl:value-of select="concat('height: ', $sd-height, 'px;')"/>
                    </xsl:if>
                </xsl:when>
                <xsl:otherwise>
                    <xsl:value-of select="concat('width: ', $md-width, 'px; ')"/>
                    <xsl:value-of select="concat('height: ', $md-height, 'px;')"/>
                </xsl:otherwise>
            </xsl:choose>
        </xsl:attribute>
        <div class="image">
            <xsl:if test="$error-capture">
                <xsl:attribute name="id">
                    <xsl:value-of select="substring-before(@name, '.png')"/>
                </xsl:attribute>
            </xsl:if>
            <xsl:variable name="file-path">
                <xsl:choose>
                    <xsl:when test="$email-testcase">
                        <xsl:value-of select="$file-name"/>
                    </xsl:when>
                    <xsl:otherwise>
                        <xsl:value-of select="concat('../', $file-name)"/>
                    </xsl:otherwise>
                </xsl:choose>
            </xsl:variable>
            <xsl:attribute name="style">
                <xsl:choose>
                    <xsl:when test="@screen = '2'">
                        <xsl:value-of select="concat('background: url(&quot;', $file-path, '&quot;) no-repeat;')"/>
                        <xsl:if test="$sd-width">
                            <xsl:value-of select="concat('width: ', $sd-width, 'px; ')"/>
                            <xsl:value-of select="concat('height: ', $sd-height, 'px;')"/>
                        </xsl:if>
                    </xsl:when>
                    <xsl:otherwise>
                        <xsl:value-of select="concat('background: url(&quot;', $file-path, '&quot;) no-repeat;')"/>
                        <xsl:value-of select="concat('width: ', $md-width, 'px; ')"/>
                        <xsl:value-of select="concat('height: ', $md-height, 'px;')"/>
                    </xsl:otherwise>
                </xsl:choose>
            </xsl:attribute>
            <xsl:if test="$error-capture">
                <div class="transBox"><FONT style="font-size: 1px;"></FONT></div>
            </xsl:if>
        </div>
    </div>

</xsl:template>

</xsl:stylesheet>