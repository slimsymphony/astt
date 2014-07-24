<?xml version="1.0" encoding="utf-8" ?>
<!--
    NOKIA
    MP SW Look&Feel
    S40 Development Tools, Testing Tools


                Test report javascript wrapper template
                ======================================
                Granite test report transformations

    Copyright (c) Nokia. All rights reserved.

    %full_filespec: test_report_stylesheets.xslt-2:sps:ou1iam#1 %

    %version:       2 %
    %date_created:  Tue Apr 07 12:54:20 2009 %
    %created_by:    sapousi %

    Reason:         Created
    Reference:      CM Synergy task: ou1iam#151035
    Description:    New CSS for memory leak report

    SVN version info:
    $Revision: 274 $
    $Id: test_report_javascript_wrapper.xslt 274 2006-06-15 09:22:00Z ripakane $

    Specification:

    Notes:

        Wrapper for test_report_javascript.xslt templates.

        Templates:
            - common_script
            - left_frame_script
            - activex_wrapper_script
            - testcase_array

        ***

        XSLT indentation 4 spaces.
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

        ***

-->
<xsl:stylesheet version = '1.0' xmlns:xsl='http://www.w3.org/1999/XSL/Transform'>
    <xsl:output method="html" media-type="text/html" encoding="UTF-8"/>
    <xsl:param name="testrun"/>
    <xsl:param name="startMode"/>
    <xsl:param name="transformFlag"/>
    <xsl:param name="transformMode"/>

    <xsl:variable name="framed-mode" select="$transformMode = 'framed-report'"/>
    <xsl:variable name="frameless-mode" select="$transformMode = 'frameless-report'"/>
    <xsl:variable name="email-testcase" select="$transformFlag = 'email-testcase'"/>
    <xsl:variable name="single-testcase" select="$transformFlag = 'single-testcase'"/>

    <xsl:include href="test_report_javascript.xslt"/>
    <xsl:include href="test_report_style_sheet.xslt"/>
    <xsl:include href="test_report_xml_to_html_frames.xslt"/>

    <xsl:template match="/">
        <xsl:choose>
            <xsl:when test="$startMode = 'main_frame'">
                <xsl:call-template name="main-frame"/>
            </xsl:when>
            <xsl:when test="$startMode = 'left_frame'">
                <xsl:call-template name="left-frame"/>
            </xsl:when>
            <xsl:when test="$startMode = 'common_script'">
                <xsl:call-template name="common-script"/>
            </xsl:when>
            <xsl:when test="$startMode = 'left_frame_script'">
                <xsl:call-template name="left-frame-script"/>
            </xsl:when>
            <xsl:when test="$startMode = 'activex_wrapper_script'">
                <xsl:call-template name="activex-wrapper-script"/>
            </xsl:when>
            <xsl:when test="$startMode = 'memory_info_wbscript'">
                <xsl:call-template name="memory-info-wbscript"/>
            </xsl:when>
            <xsl:when test="$startMode = 'memory_info_patch'">
                <xsl:choose>
                    <xsl:when test="number($testrun) > 1">
                        <xsl:value-of select="concat('@CScript ./script/merge_memory_info_', $testrun, '.vbs')"/>
                    </xsl:when>
                    <xsl:otherwise>
                        <xsl:value-of select="'@CScript ./script/merge_memory_info.vbs'"/>
                    </xsl:otherwise>
                </xsl:choose>
            </xsl:when>
            <xsl:when test="$startMode = 'dump_file_info_wbscript'">
                <xsl:call-template name="dump-file-info-wbscript"/>
            </xsl:when>
            <xsl:when test="$startMode = 'dump_file_info_patch'">
                <xsl:choose>
                    <xsl:when test="number($testrun) > 1">
                        <xsl:value-of select="concat('@CScript ./script/merge_dump_file_info', $testrun, '.vbs')"/>
                    </xsl:when>
                    <xsl:otherwise>
                        <xsl:value-of select="'@CScript ./script/merge_dump_file_info.vbs'"/>
                    </xsl:otherwise>
                </xsl:choose>
            </xsl:when>
            <xsl:when test="$startMode = 'testcase_array'">
                <xsl:call-template name="testcase-array"/>
            </xsl:when>
            <xsl:when test="$startMode = 'common_style'">
                <xsl:call-template name="common-style"/>
            </xsl:when>
            <xsl:when test="$startMode = 'frames_style'">
                <xsl:call-template name="frames-style"/>
            </xsl:when>
            <xsl:when test="$startMode = 'memleak_style'">
                <xsl:call-template name="memleak-style"/>
            </xsl:when>            
        </xsl:choose>
    </xsl:template>

</xsl:stylesheet>