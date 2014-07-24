<?xml version="1.0" encoding="utf-8" ?>
<!--
    NOKIA
    MP S40 SW
    UI Testing Tools

            Test case properties template
            =============================
            Granite test report transformations

    Copyright (c) Nokia. All rights reserved.

    Specification:

    Notes:

        Templates for a test case properties generation.
        Includes product, general warnings, ignore flags and settings information.

        Templates:
            - testset-properties
            - product-info-rows
            - settings-table
            - general-warnings-table
            - ignore-flags-table

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

<!--
    estcase-properties

    This template generates a header for a test report.

    Following information is given:
        Test information:
            -Author, Date, Test group, Test group filter
        Main/remote product information:
            -Display, Imei, Name, Startup language, Style, System
        Main/remote version information:
            -SW-, HW- and ART-version
        Main/remote general warnings information:
        Main/remote ignore flags information:
        Settings information:

    Scope: testreport

    Parameters:-
-->
<xsl:template name="testset-properties">
    <div align="center">
        <xsl:choose>
            <xsl:when test="$single-testcase">
                <xsl:attribute name="style">
                    <xsl:value-of select="'display: none;'"/>
                </xsl:attribute>
                <xsl:attribute name="id">
                    <xsl:value-of select="'general-information'"/>
                </xsl:attribute>
                <xsl:attribute name="name">
                    <xsl:value-of select="'general-information'"/>
                </xsl:attribute>
                <h2 style="text-decoration: underline;">General information</h2>
            </xsl:when>
            <xsl:otherwise>
                <h1><u>Granite Test Report</u></h1><br/>
            </xsl:otherwise>
        </xsl:choose>
        <table class="info">
            <!-- Author and test information -->
            <xsl:for-each select="/testreport/@*">
                <xsl:sort select="name()" data-type="text"/>
                <xsl:variable name="name" select="concat( translate( substring( name(), 1, 1 ), 'abcdefghijklmnopqrstuvwxyz', 'ABCDEFGHIJKLMNOPQRSTUVWXYZ' ), substring( name(), 2, string-length( name() )))"/>
                <tr>
                    <td class="info" style="white-space: nowrap"><xsl:value-of select="translate( $name, '_', ' ' )"/></td>
                    <td class="info"><xsl:value-of select="."/></td>
                </tr>
            </xsl:for-each>

            <!-- Main product information -->
            <xsl:call-template name="product-info-rows">
                <xsl:with-param name="product" select="$main-product"/>
                <xsl:with-param name="text" select="'Main phone'"/>
            </xsl:call-template>

            <!-- Remote product information -->
            <xsl:call-template name="product-info-rows">
                <xsl:with-param name="product" select="$remote-product"/>
                <xsl:with-param name="text" select="'Remote phone'"/>
            </xsl:call-template>
        </table>
    </div>

    <!-- Creates main warnings table -->
    <xsl:call-template name="general-warnings-table">
        <xsl:with-param name="warnings" select="$main-warnings"/>
        <xsl:with-param name="key"  select="'general-warnings-main'"/>
    </xsl:call-template>

    <!-- Creates remote warnings table -->
    <xsl:call-template name="general-warnings-table">
        <xsl:with-param name="warnings" select="$remote-warnings"/>
        <xsl:with-param name="key"  select="'general-warnings-remote'"/>
    </xsl:call-template>

    <!-- Creates ignore flags table -->
    <xsl:call-template name="ignore-flags-table"/>
    <br/>

    <!-- Creates settings table -->
    <xsl:call-template name="settings-table"/>
    <br/>

</xsl:template>

<!--

    Template: product-info-rows

    Description:
        Creates rows for a table containing the product information.

    Scope: /testreport/product
           /testreport/testcase/remote/product

    Parameters:
        selection:
            product node set.

    Output: HTML code <tr><td>...</td></tr>
-->
<xsl:template name="product-info-rows">
    <xsl:param name="product"/>
    <xsl:param name="text"/>

    <xsl:if test="$product">
        <tr>
            <th colspan="2" class="indexHeader">
                <xsl:value-of select="$text"/>
            </th>
        </tr>
        <xsl:for-each select="$product/@*">
            <!-- <xsl:sort select="name()" data-type="text"/> -->
            <xsl:variable name="name" select="concat( translate( substring( name(), 1, 1 ), 'abcdefghijklmnopqrstuvwxyz', 'ABCDEFGHIJKLMNOPQRSTUVWXYZ' ), substring( name(), 2, string-length( name() )))"/>
            <tr>
                <td class="info" style="white-space: nowrap"><xsl:value-of select="translate( $name, '_', ' ' )"/></td>
                <td class="info"><xsl:value-of select="."/></td>
            </tr>
        </xsl:for-each>
        <!-- Version information -->
        <xsl:for-each select="$product/version">
            <xsl:variable name="type" select="translate( @type, 'abcdefghijklmnopqrstuvwxyz', 'ABCDEFGHIJKLMNOPQRSTUVWXYZ' )"/>
            <tr>
                <td class="info" style="white-space: nowrap"><xsl:value-of select="concat($type, ' ', name())"/></td>
                <td class="info"><xsl:value-of select="."/></td>
            </tr>
        </xsl:for-each>
    </xsl:if>

</xsl:template>

<!--

    Template: settings-table

    Description:
        Creates rows for a table settings information.

    Scope: /testreport/settings

    Parameters:
        selection:
            product node set.

    Output: HTML code
-->
<xsl:template name="settings-table">

    <xsl:if test="$settings">
        <xsl:if test="not($single-testcase)">
            <!-- Dynamic hider toggle -->
            <xsl:call-template name="hide-toggle-header">
                <xsl:with-param name="id" select="'settings'"/>
                <xsl:with-param name="text" select="'Settings'"/>
            </xsl:call-template>
        </xsl:if>

        <div>
            <xsl:choose>
                <xsl:when test="$single-testcase">
                    <xsl:attribute name="align">
                        <xsl:value-of select="'center'"/>
                    </xsl:attribute>
                    <xsl:attribute name="style">
                        <xsl:value-of select="'display: none;'"/>
                    </xsl:attribute>
                    <xsl:attribute name="id">
                        <xsl:value-of select="'settings'"/>
                    </xsl:attribute>
                    <xsl:attribute name="name">
                        <xsl:value-of select="'settings'"/>
                    </xsl:attribute>
                    <h2 style="text-decoration: underline;">Settings</h2>
                </xsl:when>
                <xsl:otherwise>
                    <xsl:attribute name="class">
                        <xsl:value-of select="'hideBlockClass'"/>
                    </xsl:attribute>
                    <xsl:attribute name="style">
                        <xsl:value-of select="'margin-left: 3%;'"/>
                    </xsl:attribute>
                    <!-- Create id used in dynamic visibility -->
                    <xsl:attribute name="id">
                        <xsl:value-of select="'settings'"/>
                    </xsl:attribute>
                </xsl:otherwise>
            </xsl:choose>

            <table class="settings">
                <xsl:for-each select="$settings/*">
                    <tr>

                        <!-- Colorize row backrounds for better readability -->

                        <xsl:if test="position() mod 4 = 1">
                            <xsl:attribute name="style">background: #eeEEee</xsl:attribute>
                        </xsl:if>

                        <xsl:if test="position() mod 4 = 2">
                            <xsl:attribute name="style">background: #ddDDdd</xsl:attribute>
                        </xsl:if>

                        <xsl:if test="position() mod 4 = 3">
                            <xsl:attribute name="style">background: #eeEEee</xsl:attribute>
                        </xsl:if>

                        <!-- Setting name -->

                        <td class="settings">
                            <div style="font-weight: bold; padding-right: 20px">
                                <xsl:value-of select="@name"/>
                            </div>
                        </td>

                        <!-- Setting value -->

                        <td class="settings">
                            <xsl:value-of select="."/>
                        </td>
                    </tr>
                </xsl:for-each>
            </table>
        </div>
    </xsl:if>

</xsl:template>

<!--

    Template: general-warnings-table

    Description:
        Creates table containing general warnings information.

    Scope: /testreport/general_warnings
           /testreport/testcase/remote/general_warnings

    Parameters:
        selection:
            general warnings node set.

    Output: HTML code
-->
<xsl:template name="general-warnings-table">
    <xsl:param name="warnings"/>
    <xsl:param name="key"/>

    <xsl:variable name="warning-selection" select="$warnings/warning[generate-id(.) = generate-id(key($key, .)[1])]"/>

    <xsl:if test="$warnings">
        <div align="center">
            <xsl:if test="$single-testcase">
                <xsl:attribute name="style">
                    <xsl:value-of select="'display: none;'"/>
                </xsl:attribute>
                <xsl:attribute name="id">
                    <xsl:value-of select="'general-warnings'"/>
                </xsl:attribute>
                <xsl:attribute name="name">
                    <xsl:value-of select="'general-warnings'"/>
                </xsl:attribute>
            </xsl:if>
            <h2>
                <xsl:if test="$single-testcase">
                    <xsl:attribute name="style">
                        <xsl:value-of select="'text-decoration: underline;'"/>
                    </xsl:attribute>
                </xsl:if>
                <xsl:value-of select="concat('General warnings', ' (',substring-after($key, 'general-warnings-'), ')')"/>
            </h2>
            <table style="border: 2pt dashed red">
                <xsl:for-each select="$warning-selection">
                    <tr>
                        <td style="border: none">
                            <div class="error">
                                <xsl:number value="position()" format="1. "/>
                                <xsl:value-of select="concat(., ' (', count(key($key, .)), ')')"/>
                            </div>
                        </td>
                    </tr>
                </xsl:for-each>
            </table>
        </div>
        <br/>
    </xsl:if>

</xsl:template>

<!--

    Template: ignore-flags-table

    Description:
        Creates table containing ignore flags information.

    Scope: /testreport/ignore_flags

    Parameters:
        selection:
            general warnings node set.

    Output: HTML code
-->
<xsl:template name="ignore-flags-table">
    <xsl:variable name="ignore-texts" select="$ignore-flags/ignore_flag/@text"/>

    <xsl:if test="boolean($ignore-flags/*[@state='True'])">
        <div align="center">
            <xsl:if test="$single-testcase">
                <xsl:attribute name="style">
                    <xsl:value-of select="'display: none;'"/>
                </xsl:attribute>
                <xsl:attribute name="id">
                    <xsl:value-of select="'ignore-flags'"/>
                </xsl:attribute>
                <xsl:attribute name="name">
                    <xsl:value-of select="'ignore-flags'"/>
                </xsl:attribute>
            </xsl:if>
            <h2>
                <xsl:if test="$single-testcase">
                    <xsl:attribute name="style">
                        <xsl:value-of select="'text-decoration: underline;'"/>
                    </xsl:attribute>
                </xsl:if>
                <xsl:value-of select="'Ignore flags'"/>
            </h2>
            <table class="settings">
                <tr class="indexHeader" style="text-align: center;">
                    <th>Name</th>
                    <th>State</th>
                    <xsl:if test="$ignore-texts">
                        <th>Texts</th>
                    </xsl:if>
                </tr>
                <xsl:for-each select="$ignore-flags/*">
                    <tr>
                        <xsl:if test="@state = 'False'">
                            <xsl:attribute name="style">color: #aaAAaa; font-style: italic;</xsl:attribute>
                        </xsl:if>
                        <xsl:if test="@state = 'True'">
                            <xsl:attribute name="style">background: #ddDDdd;</xsl:attribute>
                        </xsl:if>
                        <td style="font-weight: bold;"><xsl:value-of select="@name"/></td>
                        <td><xsl:value-of select="@state"/></td>
                        <xsl:if test="$ignore-texts">
                            <td><xsl:value-of select="@text"/></td>
                        </xsl:if>
                    </tr>
                </xsl:for-each>
            </table>
        </div>
        <br/>
    </xsl:if>
</xsl:template>

</xsl:stylesheet>
