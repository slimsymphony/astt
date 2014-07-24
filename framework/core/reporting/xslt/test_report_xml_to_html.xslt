<?xml version="1.0" encoding="utf-8" ?>
<!--
    NOKIA
    MP S40 SW
    UI Testing Tools

            Test report XML to HTML converter main template
            ===============================================
                Granite test report transformations

    Copyright (c) Nokia. All rights reserved.

    Specification:

    Notes:

        This file serves as the launching point of test reporting XML to
        HTML transformation. It includes other XSLT stylesheets and
        defines the global properties of the transform, including
        CSS class definitions.

        Walkthrough:
            - Initiate main template
            - Generate HTML header
                - topic
                - CSS style definition
            - Create test report header (test_report_xml_to_html_header.xslt)
                - Test author
                - Product info
                - Test result total summary
                - Table of contents
            - Create index by severity (test_report_xml_to_html_header.xslt)
            - Create index by execution order (test_report_xml_to_html_header.xslt)
            - Create index by subarea/feature, add summaries per subarea
              (test_report_xml_to_html_header.xslt)
            - List test case details (test_report_xml_to_html_case_details.xslt)

        And the end of this module there is some errorneus XSLT
        to test the XSLT transform engine error output.

        In this file a method called "The Muenchian Method" is used
        for grouping items by an attribute. Grouping (making list
        of an unique nodes/attribute) is a common problem in XSLT.
        For more information about The Muenchian Method, see:

        http://www.jenitennison.com/xslt/grouping/muenchian.html

        ***

        XSLT indentation 4 spaces
        Page width 140 characters.

        ***

        For every template, comment at least:
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
    Set outpuut encoding.

    NOTE: Twice <META> tags are created. One by MSXML itself,
    one by us. Our tag is the latter one with correctly
    UTF-8 specified as encoding.

    This might introduce problems with the future browsers,
    because this is not 100% correct HTML. IE 5.5 &
    Netscape 7 accept it and removing extra <META> would
    require manual post-processing of a generated HTML
    file.
-->
<xsl:output method="html" media-type="text/html" encoding="UTF-8"/>
<xsl:param name="transformFlag" select="'single-testcase'"/>
<xsl:param name="transformMode" select="'frameless-report'"/>

<xsl:strip-space elements="*"/>

<!-- Look-up keys needed for grouping subareas and features using The Muenchian Method.
These keys are also used in the module test_report_xml_to_html_summary.xslt. -->
<xsl:key name="general-warnings-main" match="general_warnings/warning" use="."/>
<xsl:key name="general-warnings-remote" match="testcase/remote/general_warnings/warning" use="."/>

<xsl:variable name="framed-mode" select="$transformMode = 'framed-report'"/>
<xsl:variable name="frameless-mode" select="$transformMode = 'frameless-report'"/>
<xsl:variable name="email-testcase" select="$transformFlag = 'email-testcase'"/>
<xsl:variable name="single-testcase" select="$transformFlag = 'single-testcase'"/>

<xsl:variable name="main-product" select="/testreport/product"/>
<xsl:variable name="main-warnings" select="/testreport/general_warnings"/>

<xsl:variable name="traces-on" select="/testreport/testcase/@trace = 'on'"/>
<xsl:variable name="remote-phone" select="/testreport/testcase/remote"/>
<xsl:variable name="remote-product" select="$remote-phone[position() = 1]/product"/>
<xsl:variable name="remote-warnings" select="$remote-phone/general_warnings"/>

<xsl:variable name="settings" select="/testreport/settings"/>
<xsl:variable name="ignore-flags" select="/testreport/ignore_flags"/>

<xsl:variable name="main-md-width" select="substring-before($main-product/@main_display, 'X')"/>
<xsl:variable name="main-md-height" select="substring-after($main-product/@main_display, 'X')"/>
<xsl:variable name="main-sd-width" select="substring-before(substring-after($main-product/@second_display, 'SD'), 'X')"/>
<xsl:variable name="main-sd-height" select="substring-after($main-product/@second_display, 'X')"/>
<xsl:variable name="remote-md-width" select="substring-before($remote-product/@main_display, 'X')"/>
<xsl:variable name="remote-md-height" select="substring-after($remote-product/@main_display, 'X')"/>
<xsl:variable name="remote-sd-width" select="substring-before(substring-after($remote-product/@second_display, 'SD'), 'X')"/>
<xsl:variable name="remote-sd-height" select="substring-after($remote-product/@second_display, 'X')"/>
<xsl:variable name="preferred_editor" select="/testreport/settings/setting[@name='USER_PREFERRED_EDITOR']"/>

<xsl:variable name="testcases-main" select="/testreport/testcase"/>

<!--
    Including child XSLT files.

    Note that including order is fixed. In XSLT, template can call only
    templates implemented before the caller. Also, XSLT cannot
    handle double includes (two XSL files include a same file). This is why
    you should never put include directivies to child XSL files.
-->
<xsl:include href="test_report_xml_to_html_utility.xslt"/>
<xsl:include href="test_report_xml_to_html_case_properties.xslt"/>
<xsl:include href="test_report_xml_to_html_case_details.xslt"/>
<xsl:include href="test_report_javascript.xslt"/>
<xsl:include href="test_report_style_sheet.xslt"/>

<!--

    Template: Main template

    Description: Generates test report HTML from XML input

    Scope: /testreport

    Parameters: none

    Output: HTML report <html>...</html>

-->
<xsl:template match="/testreport">
    <!-- Begin HTML file generation -->
    <html>
        <head>
            <title>
                <xsl:text>Granite test report </xsl:text>
                <xsl:value-of select="@date"/>
           </title>

            <!-- Charset is already declared in <?xml ?> declaration, but
            to it here too for possible buggy browsers -->
            <meta http-equiv="Content-Type" content="text/html" charset="UTF-8"/>

            <!-- IE5.0 doesn't seem to support this,
            define CSS style classes in the body.
            <style>
            </style>
            -->

            <!-- Following section contains global javascript functions -->
            <xsl:choose>
                <xsl:when test="$email-testcase">
                    <script type="text/javascript">
                        <xsl:call-template name="activex-wrapper-script"/>
                    </script>
                    <script type="text/javascript">
                        <xsl:call-template name="common-script">
                            <xsl:with-param name="email-testcase" select="true()"/>
                        </xsl:call-template>
                    </script>
                </xsl:when>
                <xsl:otherwise>
                    <script>
                        <xsl:attribute name="src">
                            <xsl:value-of select="'../script/test_report_activex_wrapper_script_x.js'"/>
                        </xsl:attribute>
                        <xsl:attribute name="type">
                            <xsl:value-of select="'text/javascript'"/>
                        </xsl:attribute>
                    </script>
                    <script>
                        <xsl:attribute name="src">
                            <xsl:value-of select="'../script/test_report_common_script.js'"/>
                        </xsl:attribute>
                        <xsl:attribute name="type">
                            <xsl:value-of select="'text/javascript'"/>
                        </xsl:attribute>
                    </script>
                </xsl:otherwise>
            </xsl:choose>
        </head>

        <!-- Initialize dynamic hide/show code after parsing HTML -->
        <body>
            <!--
                CSS style definitions used later with various HTML elements
               through a class attribute.

                IE5.0 hackaround:
                IE5.0 doesn't detect <style> defined in <head>.
                The correct way would be put the style section into the head section.
            -->
            <xsl:choose>
                <xsl:when test="$traces-on">
                    <xsl:attribute name="onLoad">
                        <xsl:value-of select="'defineGlobals();parent.frames[&quot;left_frame&quot;].checkTraceData();'"/>
                    </xsl:attribute>
                </xsl:when>
                <xsl:otherwise>
                    <xsl:attribute name="onLoad">
                        <xsl:value-of select="'defineGlobals();parent.frames[&quot;left_frame&quot;].hideTraceDataExt();'"/>
                    </xsl:attribute>
                </xsl:otherwise>
            </xsl:choose>
            <xsl:choose>
                <xsl:when test="$email-testcase">
                    <style type="text/css">
                        <xsl:call-template name="common-style"/>
                    </style>
                </xsl:when>
                <xsl:otherwise>
                    <link>
                        <xsl:attribute name="href">
                            <xsl:value-of select="'../style/test_report_common_style.css'"/>
                        </xsl:attribute>
                        <xsl:attribute name="rel">
                            <xsl:value-of select="'stylesheet'"/>
                        </xsl:attribute>
                        <xsl:attribute name="type">
                            <xsl:value-of select="'text/css'"/>
                        </xsl:attribute>
                    </link>
                </xsl:otherwise>
            </xsl:choose>
            <xsl:if test="$single-testcase">
                <!-- IE5.5+/Win - this is more specific than the IE 5.0 version -->
                <xsl:comment><![CDATA[[if gte IE 5.5]>
                        <![if lt IE 8]>
                            <style type="text/css">
                                div#fixedArrow {
                                    right: auto; bottom: auto;
                                    left: expression( ( -20 - fixedArrow.offsetWidth + ( document.documentElement.clientWidth ? document.documentElement.clientWidth : document.body.clientWidth ) + ( ignoreMe2 = document.documentElement.scrollLeft ? document.documentElement.scrollLeft : document.body.scrollLeft ) ) + 'px' );
                                    top: expression( ( -10 - fixedArrow.offsetHeight + ( document.documentElement.clientHeight ? document.documentElement.clientHeight : document.body.clientHeight ) + ( ignoreMe = document.documentElement.scrollTop ? document.documentElement.scrollTop : document.body.scrollTop ) ) + 'px' );
                                }
                            </style>
                        <![endif]>
                    <![endif]]]></xsl:comment>
                <div id="fixedArrow">
                    <a>
                        <xsl:attribute name="onclick">
                            <xsl:value-of select="'parent.frames[&quot;left_frame&quot;].loopTests(&quot;previous&quot;)'"/>
                        </xsl:attribute>
                        <xsl:value-of select="'&#055;'"/>
                    </a>
                    <a>
                        <xsl:attribute name="onclick">
                            <xsl:value-of select="'parent.frames[&quot;left_frame&quot;].loopTests(&quot;next&quot;)'"/>
                        </xsl:attribute>
                        <xsl:value-of select="'&#056;'"/>
                    </a>
                </div>
            </xsl:if>

             <!-- Create detailed testcase information -->
            <xsl:choose>
                <xsl:when test="$single-testcase">
                    <xsl:call-template name="test-report"/>
                    <xsl:call-template name="testset-properties"/>
                </xsl:when>
                <xsl:otherwise>
                    <xsl:call-template name="testset-properties"/>
                    <xsl:call-template name="test-report"/>
                </xsl:otherwise>
            </xsl:choose>

            <div id="testRunResultPopup" style="padding: 5px;" class="hiddenPopup">
                <pre style="font-weight: bold" class="showWs">
                    <xsl:value-of select='concat("Test run result comes from Granite automated", "&#010;", "test run and can", "&#039;", "t be edited.")'/>
                </pre>
            </div>

            <div id="displayInfoPopup" class="hiddenPopup">
                <table width="240" class="displayHelp">
                    <tr>
                        <td width="6%" style="background-color: #ccFFcc;"></td><td>Matching attributes</td>
                    </tr>
                    <tr>
                        <td width="6%" style="background-color: #FFccCC;"></td><td>Mismatching attributes</td>
                    </tr>
                    <tr>
                        <td width="6%" style="background-color: #EEeeEE;"></td>
                        <td>Other items, which were not expected</td>
                    </tr>
                </table>
            </div>

        </body>
   </html>

    <!-- End HTML file generation -->
</xsl:template>

<!--
    Invalid XSLT for self testing.
    The following causes a parse time error.
-->
<!--
<xsl:attribute name="kosh">
</xsl:xxx>
-->

<!--
    Invalid XSLT for self testing.
    The following causes a run time error
    in MSXML 4.0.
-->
<!--
<xsl:template>
</xsl:template>
-->

</xsl:stylesheet>
