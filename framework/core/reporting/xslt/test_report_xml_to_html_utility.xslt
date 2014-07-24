<?xml version="1.0" encoding="utf-8" ?>
<!--
    NOKIA
    MP S40 SW
    UI Testing Tools

           Test report XML to HTML converter utility templates
           ===================================================
           Granite test report transformations

    Copyright (c) Nokia. All rights reserved.

    %full_filespec: test_report_xml_to_html_utility.xslt-ou1iam#15:ascii:ou_isasw#1 %

    %version:       ou1iam#15 %
    %date_created:  Wed Jun 11 13:59:55 2008 %
    %created_by:    teemukok %

    Reason:         Improvement
    Reference:      CM Synergy task: ou1iam#114821
    Description:    Renamed results according to QG/QC.

    SVN version info:
    $Revision: 274 $
    $Id: test_report_xml_to_html_utility.xslt 274 2006-06-15 09:22:00Z ripakane $

    Specification:

    Notes:

        This module contains utility templates that are generally used in
        XML to HTML test report transforming XSL files.

        Utility templates in this module:
        - test-result-color-write
        - test-report-link
        - test-result-colored-link
        - hide-toggle-header
        - cell-hide-toggle
        - output-warning-message
        - unknown-tag
        - attribute-table
        - char-toggle
        - br-replace
        - extract-from-path
        - add-traceback-links
        - add-padding
        - dec-to-hex

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

<!--

    Template: test-result-color-write

    Description: Writes out a text entered as a parameter.
                 Text color is choosed according to a text case result.
                 Passed tests make green color, other make red.

    Scope: testcase

    Parameters: text
                    type: plaintext to write out


    Output: <font color="">text</font>

-->
<xsl:template name="test-result-color-write">
    <xsl:param name="text"/>

    <xsl:choose>
        <xsl:when test="@result = 'Passed' or $text = 'Passed'">
            <font color="green">
                <xsl:value-of select="$text"/>
            </font>
        </xsl:when>
        <xsl:when test="@result = 'N/A' or $text = 'N/A'">
            <font color="blue">
                <xsl:value-of select="$text"/>
            </font>
        </xsl:when>
        <xsl:otherwise>
            <font color="red">
                <xsl:value-of select="$text"/>
            </font>
        </xsl:otherwise>
    </xsl:choose>
</xsl:template>


<!--

    Template: test-report-link

    Description:
        Creates non-underlined link to use in test report
        index tables and in the other sections of test report.


    Scope: testcase

    Parameters:
        text:
            The text which acts as a link.
        href:
            Customized link reference. By default,
            link reference equals to # + text (HTML page
            internal link).

    Output: <a href="link">name</a>

-->
<xsl:template name="test-report-link">
    <xsl:param name="text"/>
    <xsl:param name="href"/>

    <a style="text-decoration: none">
        <!-- Create href attribute -->
        <xsl:attribute name="href">
            <xsl:choose>
                <xsl:when test="$href = ''">
                    <xsl:text>#</xsl:text><xsl:value-of select="$text"/>
                </xsl:when>
                <xsl:otherwise>
                    <xsl:value-of select="$href"/>
                </xsl:otherwise>
            </xsl:choose>
        </xsl:attribute>

        <!-- Link text -->
        <xsl:value-of select="$text"/>
    </a>
</xsl:template>

<!--

    Template: test-result-colored-link

    Description:
        Creates a link to $href. Link has no underlining
        and the color of the link is choosed according
        to testcase result attribute (See test-result-color-write).

    Scope: testcase

    Parameters:
        text:
            The text which acts as a link.
        href:
            Customized link reference. By default,
            link reference equals to # + text (HTML page
            internal link).

    Output: <a href="link">name</a>

-->
<xsl:template name="test-result-colored-link">
    <xsl:param name="text"/>
    <xsl:param name="title"/>
    <xsl:param name="href"/>

    <a style="text-decoration: none">
        <!-- Create href attribute -->
        <xsl:attribute name="href">
            <xsl:choose>
                <xsl:when test="$href = ''">
                    <xsl:text>#</xsl:text><xsl:value-of select="$text"/>
                </xsl:when>
                <xsl:otherwise>
                    <xsl:value-of select="$href"/>
                </xsl:otherwise>
            </xsl:choose>
        </xsl:attribute>
        <xsl:if test="$title">
            <xsl:attribute name="title">
                <xsl:value-of select="$title"/>
            </xsl:attribute>
        </xsl:if>
        <!-- Link text -->
        <xsl:call-template name="test-result-color-write">
            <xsl:with-param name="text" select="$text"/>
        </xsl:call-template>
    </a>
</xsl:template>

<!--

    Template: hide-toggle-header

    Description:
        Creates a pararagh which can be used dynamically hide and
        show parts of HTML code.



    Scope: Any

    Parameters:
        id:
            The object id which visibility is toggled.
            It can be created by generate-id function.
        text:
            The paragraph text
        hideBlock:
            The CSS class name for the hidden paragraphs
            Default: hideBlockClass
        showBlock:
            The CSS class name for the shown paragraphs
            Default: showBlockClass
        defaultClass:
            The CSS class name for inactive link
            Default: defaultToggleClass
        hooverClass:
            The CSS class name for mouse over link
            Default: hooverToggleClass

    Output: <div onmouseover="...">text</div>

-->
<xsl:template name="hide-toggle-header">
    <xsl:param name="id"/>
    <xsl:param name="text"/>
    <xsl:param name="style"/>
    <xsl:param name="state"/>
    <xsl:param name="hideBlock" select="'hideBlockClass'"/>
    <xsl:param name="showBlock" select="'showBlockClass'"/>
    <xsl:param name="defaultClass" select="'defaultToggleClass'"/>
    <xsl:param name="hooverClass" select="'hooverToggleClass'"/>

    <div>
        <!-- Add id marker attribute to identify this dynamic text section -->
        <xsl:attribute name="class">
            <xsl:value-of select="$defaultClass"/>
        </xsl:attribute>

        <xsl:attribute name="onclick">

            <!--
                Following forms a statement:

                if(document.all.id123.className == '$showBlock')
                    document.all.id123.className = '$hideBlock';
                 else
                    document.all.id123.className == '$showBlock';

                 This statement switches between target showBlock and hideBlock modes on a mouse click.
              -->

            <xsl:text>flipVisibility(this, '</xsl:text>
            <xsl:value-of select="$id"/>
            <xsl:text>','</xsl:text>
            <xsl:value-of select="$showBlock"/>
            <xsl:text>','</xsl:text>
            <xsl:value-of select="$hideBlock"/>
            <xsl:text>')</xsl:text>

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

        <xsl:if test="$style">
            <xsl:attribute name="style"><xsl:value-of select="$style"/></xsl:attribute>
        </xsl:if>

        <!-- Insert user visible text -->
        <xsl:choose>
            <xsl:when test="$id = 'subarea-summaries' or $id = 'severity' or $id = 'order' or $id = 'settings'">
                <div style="font-size: 24px;">
                    <xsl:call-template name="char-toggle">
                        <xsl:with-param name="id" select="concat('image', $id)"/>
                        <xsl:with-param name="state" select="$state"/>
                    </xsl:call-template>
                    <xsl:value-of select="$text"/>
                </div>
            </xsl:when>
            <xsl:when test="substring($id, 0, 5) = 'desc'">
                <div style="margin-left: 2%; font-size: 20px;">
                    <xsl:call-template name="char-toggle">
                        <xsl:with-param name="id" select="concat('image', $id)"/>
                        <xsl:with-param name="state" select="$state"/>
                    </xsl:call-template>
                    <u>
                        <xsl:call-template name="test-result-color-write">
                            <xsl:with-param name="text" select="$text"/>
                        </xsl:call-template>
                    </u>
                </div>
            </xsl:when>
            <xsl:otherwise>
                <xsl:call-template name="char-toggle">
                    <xsl:with-param name="id" select="concat('image', $id)"/>
                    <xsl:with-param name="state" select="$state"/>
                </xsl:call-template>
                <xsl:value-of select="$text"/>
            </xsl:otherwise>
        </xsl:choose>
    </div>
    <div class="newLine"/>
</xsl:template>

<!--

    Template: show-all-toggle-header

    Description:
        Creates a link style pararagh which opens
        all dynamically hidden paragraphs
        under a certain node when clicked.

        This template creates a onlick handler
        which calls open_all_paragraphs
        javascript function.

    Scope: Any

    Parameters:
        parentid:
            The id of the parent node which contains
            dynamically hidden paragraps
        text:
            The user visible link text
        hideClass:
            The CSS class name for hidden paragraphs
        showClass:
            The CSS class name for shown paragraphs
        defaultClass:
            The CSS class name for inactive link
        hooverClass:
            The CSS class name for mouse over link

    Output: <div onmouseover="...">text</div>

-->
<xsl:template name="all-test-steps-toggler">
    <xsl:param name="parentid"/>
    <xsl:param name="text"/>
    <xsl:param name="hideClass" select="'hideBlockClass'"/>
    <xsl:param name="showClass" select="'showBlockClass'"/>
    <xsl:param name="defaultClass" select="'defaultToggleClass'"/>
    <xsl:param name="hooverClass" select="'hooverToggleClass'"/>

    <div class="defaultToggleClass" style="color: red; margin-bottom: 3px; margin-top: 3px;">
        <xsl:attribute name="onclick">

            <!--
                Following forms a statement:

                open_all_paragraphs('$parentid', '$showClass', '$hideClass')

                The expression is divided to several rows for better maintainability.
              -->

            <xsl:variable name="r1" select="concat('toggle_all_test_steps(this, &quot;', $parentid, '&quot;,&quot;')"/>
            <xsl:variable name="r2" select="concat($showClass, '&quot;,&quot;', $hideClass)"/>
            <xsl:variable name="r3" select="concat('&quot;' , ')' )"/>

            <xsl:value-of select="concat($r1, $r2, $r3)"/>

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

        <!-- Insert user visible text -->
        <xsl:value-of select="$text"/>
    </div>
    <div class="newLine"/>

</xsl:template>


<!--

    Template: cell-hide-toggle

    Description:
        Creates a text span which can be used to dynamically
        hide and show rows of a HTML table.

        The template utilizes toggle_rows_visibility
        javascript function.

    Scope: Any

    Parameters:
        table:
            The id attibute of table which rows we are looking.
            Required.
        idmark:
            All rows to toggle contain this word in their id attribute.
            Required.
        text:
            The span text
            Required.
        defaultClass:
            The CSS style class for the default state.
            Required.
        hooverClass:
            The CSS style class for the mouse over the item state.
            Required.

    Output: <span onmouseover="...">text</span>

-->
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


<!--

    Template: output-warning-message

    Description:
        Writes error message to a console, not into HTML.
        Works on Python 4Suite translator, no output in MSXML 4.0.

    Scope: Any

    Parameters:
        text:
            The message text

    Output: A warning message to a XSLT parser console.

-->
<xsl:template name="output-warning-message">
    <xsl:param name="text"/>

    <xsl:message><xsl:value-of select="$text"/></xsl:message>

</xsl:template>

<!--

    Template: unknown-tag

    Description:
        Call this template to output a warning
        about an unknown tag in input XML.

        Warning message to a console is written,
        including the tag name.

        Warning message into HTML code is written,
        including the tag name and the current node
        text contents.

    Scope: Any

    Parameters:
        tag:
            Tag name.

    Output:
        A warning message to a XSLT parser console and
        HTML code to output.

-->
<xsl:template name="unknown-tag">
    <xsl:param name="tag"/>

       <!-- Unknown tag, create error message into HTML -->
        <font color="#ff0000">
            <br/>
            <xsl:text>Unknown summary tag for XSLT process:</xsl:text>
            <xsl:value-of select="$tag"/><xsl:text>:</xsl:text><xsl:value-of select="."/>
            <br/>
        </font>

        <!-- Unknown tag, output error message to console  -->
        <xsl:call-template name="output-warning-message">
            <xsl:with-param name="text">Unknown summary tag in XML:<xsl:value-of select="$tag"/></xsl:with-param>
        </xsl:call-template>

</xsl:template>


<!--

    Template: attribute-table

    Description:
        Creates a table from node attributes. The table
        headers are attribute names and the cell contents
        are attribute values. If the node has contents,
        the actual contents of the node is placed to the
        last column.

        The CSS class of the table is "display".
        See test_report_xml_to_html.xslt

    Scope: Any

    Output:
        HTML code <table>...</table>

-->
<xsl:template name="attribute-table">
    <table class="display">
        <tr>
            <!-- Map attribute names to column names -->
            <xsl:for-each select="@*">
                <th class="display">
                    <xsl:value-of select="name()"/>
                </th>
            </xsl:for-each>
            <!-- If we have some contents, add contents column -->
            <xsl:if test=".">
                <th>Contents</th>
            </xsl:if>
        </tr>
        <tr>
            <xsl:for-each select="@*">
                <td>
                    <xsl:value-of select="."/>
                </td>
            </xsl:for-each>
            <!-- If we have contents, add contents column -->
            <xsl:if test=".">
                <td><xsl:value-of select="."/></td>
            </xsl:if>
        </tr>
    </table>
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

<!--

    Template: global-replace

    Description:
        General-purpose string replacement template

    Scope: Any

    Output:
        text
-->
<xsl:template name="global-replace">
    <xsl:param name="outputString"/>
    <xsl:param name="target"/>
    <xsl:param name="replacement"/>

    <xsl:choose>
        <xsl:when test="contains($outputString, $target)">
            <xsl:value-of select="concat(substring-before($outputString, $target), $replacement)"/>
            <xsl:call-template name="global-replace">
                <xsl:with-param name="outputString" select="substring-after($outputString, $target)"/>
                <xsl:with-param name="target" select="$target"/>
                <xsl:with-param name="replacement" select="$replacement"/>
            </xsl:call-template>
        </xsl:when>
        <xsl:otherwise>
            <xsl:value-of select="$outputString"/>
        </xsl:otherwise>
    </xsl:choose>
</xsl:template>

<!--

    Template: br-replace

    Description:
        Replaces new lines in a string with html <br> tags

    Scope: Any

    Output:
        substring(1)<br/>substring(2)<br/>substring(3)<br/>....
-->
<xsl:template name="br-replace">
    <xsl:param name="text"/>
    <xsl:variable name="cr" select="'&#xa;'"/>
    <xsl:choose>
        <!-- If the value of the $text parameter contains a carriage return... -->
        <xsl:when test="contains($text,$cr)">
            <!-- Return the substring of $text before the carriage return -->
            <xsl:value-of select="substring-before($text,$cr)"/>
            <!-- And construct a <br/> element -->
            <br/>
            <!--
             | Then invoke this same br-replace template again, passing the
             | substring *after* the carriage return as the new "$text" to
             | consider for replacement
             +-->
            <xsl:if test="not(string-length(normalize-space(substring-after($text,$cr))) = 0)">
                <xsl:call-template name="br-replace">
                    <xsl:with-param name="text" select="substring-after($text,$cr)"/>
                </xsl:call-template>
            </xsl:if>
        </xsl:when>
        <xsl:otherwise>
            <xsl:text>#</xsl:text>
            <xsl:value-of select="$text"/>
        </xsl:otherwise>
    </xsl:choose>
</xsl:template>

<!--

    Template: extract-from-path

    Description:
        Extracts filename of folder from path.

        Supported node types in selection:
            any

    Scope:  any

    Parameters:
        file_name:
            absolute or relative path
        state:
            true():  extracts filename from the path
            false(): extracts folder from the path
            Default: true()
        separator:
            separator used in the path definition
            Default: '\\'

    Output:
        filename of for folder

-->
<xsl:template name="extract-from-path">
    <xsl:param name="path"/>
    <xsl:param name="state" select="true()"/>
    <xsl:param name="separator" select="'/'"/>
    <xsl:param name="original-path" select="$path"/>

    <xsl:choose>
        <xsl:when test="contains($path, $separator)">
            <xsl:call-template name="extract-from-path">
                <xsl:with-param name="path" select="substring-after($path, $separator)"/>
                <xsl:with-param name="state" select="$state"/>
                <xsl:with-param name="original-path" select="$original-path"/>
                <xsl:with-param name="separator" select="$separator"/>
            </xsl:call-template>
        </xsl:when>
        <xsl:otherwise>
            <xsl:choose>
                <xsl:when test="$state">
                    <!-- outputs filename -->
                    <xsl:value-of select="$path"/>
                </xsl:when>
                <xsl:otherwise>
                    <!-- outputs folder -->
                    <xsl:value-of select="substring-before($original-path, $path)"/>
                </xsl:otherwise>
            </xsl:choose>
        </xsl:otherwise>
    </xsl:choose>
</xsl:template>

<!--

    Template: add-traceback-links

    Description:
        Adds links to traceback lines.

        Supported node types in selection:
            error/traceback

    Scope:  any

    Parameters:
        text:
            Traceback lines reparated with 'cr'.

    Output:
        Traceback lines with link.

-->
<xsl:template name="add-traceback-links">
    <xsl:param name="text"/>

    <xsl:variable name="cr" select="'&#xa;'"/>
    <xsl:variable name="char_0x22" select="'&#x22;'"/>

    <xsl:choose>
        <!-- If the value of the $text parameter contains a carriage return... -->
        <xsl:when test="contains($text, $cr)">
            <!-- Return the substring of $text before the carriage return -->
            <xsl:variable name="line" select="normalize-space(translate(substring-before($text, $cr), '\\', '/'))"/>
            <xsl:variable name="param" select="translate($line, $char_0x22, '')"/>
            <xsl:choose>
                <xsl:when test="starts-with($line, 'File ')">
                    <div class="traceBackToggleClass">
                        <xsl:attribute name="onclick">
                            <xsl:value-of select="concat('oFileSystem.invokeEditor(&quot;', $param, '&quot;,&quot;', $preferred_editor, '&quot;)')"/>
                        </xsl:attribute>
                        <xsl:value-of select="$line"/>
                    </div>
                </xsl:when>
                <xsl:otherwise>
                    <div>
                        <xsl:value-of select="$line"/>
                    </div>
                </xsl:otherwise>
            </xsl:choose>
            <xsl:if test="not(string-length(normalize-space(substring-after($text, $cr))) = 0)">
                <xsl:call-template name="add-traceback-links">
                    <xsl:with-param name="text" select="substring-after($text, $cr)"/>
                </xsl:call-template>
            </xsl:if>
        </xsl:when>
        <xsl:otherwise>
            <div>
                <xsl:value-of select="$text"/>
            </div>
        </xsl:otherwise>
    </xsl:choose>
</xsl:template>

<!--

    Template: add-padding

    Description:
        Adds desired padding to string.

        Supported node types in selection:
            any

    Scope:  any

    Parameters:
        value:
            Value tag.
        padding-char:
            Character used for padding.
        padding-length:
            Desired string length.

    Output:
        Padded value.

-->
<xsl:template name="add-padding">
    <xsl:param name="value"/>
    <xsl:param name="padding-char" select="'0'"/>
    <xsl:param name="padding-length" select="8"/>

    <xsl:variable name="padding" select="translate('##########', '#', $padding-char)"/>

    <xsl:variable name="pad-length" select="$padding-length - string-length($value)"/>
    <xsl:choose>
        <xsl:when test="$pad-length > 0">
            <xsl:value-of select="concat(substring($padding, 1, $pad-length), $value)"/>
        </xsl:when>
        <xsl:otherwise>
            <xsl:value-of select="$value"/>
        </xsl:otherwise>
    </xsl:choose>
</xsl:template>

<!--

    Template: dec-to-hex

    Description:
        Converts decimal string to hex decimal string.

        Supported node types in selection:
            any

    Scope:  any

    Parameters:
        number:
            Number tag.

    Output:
        Hex decimal value.

-->
<xsl:template name="dec-to-hex">
    <xsl:param name="number"/>

    <xsl:variable name="low">
        <xsl:value-of select="number($number) mod 16"/>
    </xsl:variable>

    <xsl:variable name="high">
        <xsl:value-of select="floor(number($number) div 16)"/>
    </xsl:variable>

    <xsl:choose>
        <xsl:when test="$high &gt; 0">
            <xsl:call-template name="dec-to-hex">
                <xsl:with-param name="number">
                    <xsl:value-of select="$high"/>
                </xsl:with-param>
            </xsl:call-template>
        </xsl:when>
    </xsl:choose>

    <xsl:choose>
        <xsl:when test="$low &lt; 10">
            <xsl:value-of select="$low"/>
        </xsl:when>
        <xsl:otherwise>
            <xsl:variable name="temp">
                <xsl:value-of select="$low - 10"/>
            </xsl:variable>
            <xsl:value-of select="translate($temp, '012345', 'ABCDEF')"/>
        </xsl:otherwise>
    </xsl:choose>

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
    <xsl:param name="step-id" select="'trace'"/>
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
