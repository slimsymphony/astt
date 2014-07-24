<?xml version="1.0" encoding="utf-8" ?>
<!--
    NOKIA
    MP S40 SW
    UI Testing Tools

           XML highlight from HTML template
           ================================
           Granite test report transformations

    Copyright (c) Nokia. All rights reserved.

    %full_filespec: test_report_xml_highlight.xslt-1:ascii:ou1iam#1 %

    Specification:

    Notes:

        This stylesheet contains xml highlight for html templates.

        Templates in this module:
        - highlight-xml
        - highlight-xml-attributes">
        - highlight-xml-comment">

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

        Good, free XSLT editor for Win32 platform:
        http://www.xmlcooktop.com/


        ***

-->

<xsl:stylesheet version='1.0' xmlns:xsl='http://www.w3.org/1999/XSL/Transform'>
<xsl:output method="html" media-type="text/html" encoding="UTF-8"/>
<xsl:param name="step-id" select="'trace'"/>

<xsl:template match="/">
    <div>
        <xsl:call-template name="highlight-xml">
            <xsl:with-param name="step-id" select="$step-id"/>
        </xsl:call-template>
    </div>
</xsl:template>

<!--

    Template: highlight-xml

    Description:
        Converts selection to highlighted xml representation.

        Supported node types in selection:
            any

    Scope:  any

    Parameters:
        selection:
            Node selection.
        collapse:
            Collapse flag.

    Output:
        HTML code of selected xml block.

-->
<xsl:template name="highlight-xml">
    <xsl:param name="step-id"/>
    <xsl:param name="selection" select="*"/>
    <xsl:param name="collapse" select="false()"/>

    <xsl:for-each select="$selection">
        <xsl:variable name="element-id" select="concat($step-id, '-', generate-id(current()))"/>

        <!-- Comment -->
        <xsl:if test="comment()">
            <xsl:call-template name="highlight-xml-comment">
                <xsl:with-param name="comment" select="comment()"/>
            </xsl:call-template>
        </xsl:if>

        <xsl:choose>
            <xsl:when test="node()">
                <div>
                    <xsl:choose>
                        <xsl:when test="$collapse or count(..|/) = 1">
                            <xsl:attribute name="class">
                                <xsl:value-of select="'xmlRootElement'"/>
                            </xsl:attribute>
                        </xsl:when>
                        <xsl:otherwise>
                            <xsl:attribute name="class">
                                <xsl:value-of select="'xmlElement'"/>
                            </xsl:attribute>
                        </xsl:otherwise>
                    </xsl:choose>
                    <!-- Element start -->
                    <xsl:choose>
                        <xsl:when test="text()">
                            <xsl:value-of select="'&lt;'"/>
                        </xsl:when>
                        <xsl:otherwise>
                            <span class="xmlElementToggle">
                                <xsl:attribute name="onclick">
                                    <xsl:value-of select="concat('flipElement(this, &quot;', $element-id, '&quot;);')"/>
                                </xsl:attribute>
                                <xsl:choose>
                                    <xsl:when test="$collapse">
                                        <xsl:value-of select="'+'"/>
                                    </xsl:when>
                                    <xsl:otherwise>
                                        <xsl:value-of select="'-'"/>
                                    </xsl:otherwise>
                                </xsl:choose>
                            </span>
                            <xsl:value-of select="'&lt;'"/>
                        </xsl:otherwise>
                    </xsl:choose>
                    <span class="xmlElementName">
                        <xsl:value-of select="name()"/>
                    </span>
                    <!-- Attributes -->
                    <xsl:call-template name="highlight-xml-attributes">
                        <xsl:with-param name="selection" select="@*"/>
                    </xsl:call-template>
                    <xsl:value-of select="'&gt;'"/>
                    <!-- Text -->
                    <span>
                        <xsl:choose>
                              <xsl:when test="text()">
                                <xsl:attribute name="style">
                                    <xsl:value-of select="'display: block, block: none'"/>
                                </xsl:attribute>
                                <span class="xmlText">
                                    <xsl:value-of select="text()"/>
                                </span>
                            </xsl:when>
                          <xsl:otherwise>
                                <xsl:attribute name="style">
                                    <xsl:choose>
                                        <xsl:when test="$collapse">
                                            <xsl:value-of select="'display: none'"/>
                                        </xsl:when>
                                        <xsl:otherwise>
                                            <xsl:value-of select="'display: block'"/>
                                        </xsl:otherwise>
                                    </xsl:choose>
                                </xsl:attribute>
                                <xsl:attribute name="id">
                                    <xsl:value-of select="$element-id"/>
                                </xsl:attribute>
                            </xsl:otherwise>
                        </xsl:choose>
                        <!-- Child nodes -->
                        <xsl:call-template name="highlight-xml">
                            <xsl:with-param name="step-id" select="$step-id"/>
                            <xsl:with-param name="selection" select="*"/>
                            <xsl:with-param name="collapse" select="false()"/>
                        </xsl:call-template>
                        <!-- Element end -->
                        <xsl:value-of select="'&lt;&#47;'"/>
                        <span class="xmlElementName">
                            <xsl:value-of select="name()"/>
                        </span>
                        <xsl:value-of select="'&gt;'"/>
                    </span>
                </div>
            </xsl:when>
            <xsl:otherwise>
                <div>
                    <xsl:choose>
                        <xsl:when test="$collapse or count(..|/) = 1">
                            <xsl:attribute name="class">
                                <xsl:value-of select="'xmlRootElement'"/>
                            </xsl:attribute>
                        </xsl:when>
                        <xsl:otherwise>
                            <xsl:attribute name="class">
                                <xsl:value-of select="'xmlElement'"/>
                            </xsl:attribute>
                        </xsl:otherwise>
                    </xsl:choose>
                    <!-- Element start -->
                    <xsl:value-of select="'&lt;'"/>
                    <span class="xmlElementName">
                        <xsl:value-of select="name()"/>
                    </span>
                    <!-- Attributes -->
                    <xsl:call-template name="highlight-xml-attributes">
                        <xsl:with-param name="selection" select="@*"/>
                    </xsl:call-template>
                    <!-- Element end -->
                    <xsl:value-of select="'&#47;&gt;'"/>
                </div>
            </xsl:otherwise>
        </xsl:choose>
    </xsl:for-each>
</xsl:template>

<!--

    Template: highlight-xml-attributes

    Description:
        Converts attributes to highlighted xml representation.
        Helper template for above highlight-xml template.

        Supported node types in selection:
            any

    Scope:  any

    Parameters:
        selection:
            Node selection.

    Output:
        HTML code of selected node attributes.

-->
<xsl:template name="highlight-xml-attributes">
    <xsl:param name="selection"/>

    <xsl:for-each select="$selection">
        <span class="xmlAttribName">
            <xsl:value-of select="concat(' ', name())"/>
        </span>
        <span class="xmlAttribValue">
            <xsl:value-of select="concat('=&#34;',  ., '&#34;')"/>
        </span>
    </xsl:for-each>
</xsl:template>

<!--

    Template: highlight-xml-comment

    Description:
        Converts comment to highlighted xml representation.
        Helper template for above highlight-xml template.

        Supported node types in selection:
            comment element

    Scope:  comment element

    Parameters:
        comment:
            comment element.

    Output:
        HTML code of selected comment element.

-->
<xsl:template name="highlight-xml-comment">
    <xsl:param name="comment"/>

    <div class="xmlComment">
        <span class="xmlCommentContent">
            <xsl:value-of select="concat('&lt;!--', $comment, '--&gt;')"/>
        </span>
    </div>
</xsl:template>

</xsl:stylesheet>
