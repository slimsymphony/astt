<?xml version="1.0" encoding="utf-8" ?>
<!--
    NOKIA
    R&D Oulu
    Austin
                        Pretty Printing
                        ===============
                    Using XSLT to indent XML

    Copyright (c) Nokia. All rights reserved.

    %full_filespec: prettyprint.xslt-ou1iam#2:ascii:ou_ui#1 %

    %version:       ou1iam#2 %
    %date_created:  Wed Jan 12 10:27:24 2005 %
    %created_by:    panttine %

    Reason:         Created
    Reference:      Continuus task: ou1iam#22651
    Description:    Fixed whitespace output.

    Specification:

    Notes:
        Result XML indentation 4 spaces

-->

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output method="xml" indent="yes"/>
    <xsl:template match="node() | @*">
        <xsl:call-template name="padder">
            <xsl:with-param name="depth" select="count(ancestor::*)"/>
        </xsl:call-template>
        <xsl:copy>
            <xsl:apply-templates select="node() | @*"/>
            <xsl:if test="*">
                <xsl:call-template name="padder">
                    <xsl:with-param name="depth" select="count(ancestor::*)"/>
                </xsl:call-template>
            </xsl:if>
        </xsl:copy>
    </xsl:template>
    <xsl:template name="padder">
        <xsl:param name="depth"/>
        <xsl:param name="afterFirst">no</xsl:param>
        <xsl:if test="$depth &gt; 0">
            <xsl:if test="$afterFirst ='no' and (* or . = '' or text())">
                <!-- Line feed -->
                <xsl:value-of select="'&#10;'"/>
            </xsl:if>
            <xsl:if test="* or . = '' or text()">
                <!-- four spaces (tab: &#09;) -->
                <xsl:value-of select="'&#32;&#32;&#32;&#32;'"/>
            </xsl:if>
            <xsl:call-template name="padder">
                <xsl:with-param name="depth" select="$depth - 1"/>
                <xsl:with-param name="afterFirst" select="'yes'"/>
            </xsl:call-template>
        </xsl:if>
    </xsl:template>
</xsl:stylesheet>
