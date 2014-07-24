<?xml version="1.0" encoding="utf-8" ?>
<!--
    NOKIA
    MP S40 SW
    UI Testing Tools


                Test report stylesheet(CSS) template
                ====================================
                Granite test report transformations

    Copyright (c) Nokia. All rights reserved.

    %full_filespec: test_report_style_sheet.xslt-9:ascii:ou1iam#1 %

    %version:       9 %
    %date_created:  Tue Apr 07 08:53:47 2009 %
    %created_by:    sapousi %

    Reason:         Improvement
    Reference:      CM Synergy task: ou1iam#151035
    Description:    New styles for memory leak report
    
    SVN version info:
    $Revision: 209 $
    $Id: test_report_style_sheet.xslt 209 2006-05-18 09:21:51Z ripakane $

    Specification:

    Notes:
        CSS style definitions used later with various HTML elements
        through a class attribute.

        IE5.0 hackaround:
        IE5.0 doesn't detect <style> defined in <head>.
        The correct way would be put the style section into the head section.

-->
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="html" media-type="text/html" encoding="UTF-8"/>

<xsl:template name="common-style">
    <!--
       Netscape7 & IE 5.5 compability issue:
        Netscape7 requires cursor: pointer
        IE 5.5 requires cursor: hand
    -->
    body                        { background: #eeFFff; }
    <!-- These are used in the main index table -->
    span.selectorGreen          { cursor: pointer; cursor: hand; color: green; font-weight: bold }
    span.selectorRed            { cursor: pointer; cursor: hand; color: red; font-weight: bold }
    span.selectorBlue           { cursor: pointer; cursor: hand; color: blue; font-weight: bold }
    span.selectorHoover         { cursor: pointer; cursor: hand; color: orange; font-weight: bold;}
    span.featureSelectorNormal  { cursor: pointer; cursor: hand; color: blue; font-weight: bold; margin-left: 5% }
    span.featureSelectorRed     { cursor: pointer; cursor: hand; color: red; font-weight: bold; margin-left: 5% }
    span.featureSelectorHoover  { cursor: pointer; cursor: hand; color: orange; font-weight: bold; margin-left: 5% }
    pre.showWs                  { font-family: verdana; font-size: 10px; margin-bottom: 0px; margin-top: 0px; }

    div.defaultToggleClass      { cursor: pointer; cursor: hand; color: blue; font-weight: bold; float:left; clear: both;
                                  padding: 1px; }
    div.hooverToggleClass       { cursor: pointer; cursor: hand; color: blue; font-weight: bold; float:left; clear: both;
                                  border: 1px solid black; background-color: white; }
    div.traceBackToggleClass    { cursor: pointer; cursor: hand; color: red; font-weight: bold; padding: 1px; }
    div.showBlockClass  { display: block; clear: both; }
    div.hideBlockClass  { display: none; clear: both; }
    <!-- Misc test step blocks -->
    div.error           { color: red; font-weight: bold; float:left; clear: both; }
    div.comment         { font-weight: bold; float:left; clear: both; }
    div.component       { color: magenta; font-weight: bold; float:left; clear: both; }
    <!-- Block Formatting element for captured bitmaps -->
    div.bitmap          { border-style: ridge; background-color: #ddDDdd; padding: 20px; width: 128px; height: 128px; }
    div.image           { padding-left: 0px; padding-top: 0px; background: no-repeat; width: 128px; height: 128px; }
    div.transBox        { display: none; width: 0px; height: 0px; position: relative; background-color: #222222;
                          filter:alpha(opacity=40); -moz-opacity:0.4; opacity: 0.4; }
    <!-- Block Formatting element for error descriptions -->
    .description        { background-color: #ffffcc; border-style: ridge; text-align: left; font-weight: bold; font-size: 11px;
                          font-family: verdana, helvetica, arial, sans-serif; color: black; padding: 5px; float:left; clear: both; }
    <!-- Block Formatting element for captured items -->
    div.capture         { padding-bottom: 10px; }
    <!-- Block Formatting element for error tracebacks -->
    div.traceBack       { margin-left: 1%; margin-bottom: 10px; background-color: black; border-collapse: collapse;
                          border-color: red; border-style: ridge; text-align: left; font-weight: bold; font-size: 11px; color: white;
                          font-family: verdana, helvetica, arial, sans-serif; padding: 5px; float:left; clear: both; }
    <!-- Block Formatting element for error key input sequences -->
    div.keyInput        { background-color: #ccCCff; padding-left: 5px; padding-right: 5px; border-style: groove;
                          float:left; font-family: verdana; font-size: 10px; }
    tinybr              { line-height: 50% }
    <!-- Default table style -->
    table               { border: none; }
    <!-- Expect/display table style -->
    table.display       { color: black; background-color: #EEeeEE; border-collapse: collapse; border-style: ridge;
                          font-family: verdana; font-size: 10px;}
    <!-- Info/summary table style -->
    table.info          { background-color: white; border-collapse: collapse; font-weight: bold; padding: 10px;
                          border: 2px solid black; width: 70%; }
    <!-- Settings table style -->
    table.settings      { border-collapse: collapse; padding: 10px; border: 2px solid black; background: white; }
    <!-- Properties table style -->
    table.testCaseIndex { color: black; background-color: white; border-collapse: collapse; padding: 10px;
                          border: 2px solid black; width: 90%; }
    <!-- Default header cell style. Used in e.g. expect/display tables -->
    th                  { border: none; font-weight: bold; padding-right: 10px; }
    tr.hooverDisplay    { background-color: #ccCCff; }
    tr.hooverCaseIdx    { cursor: pointer; cursor: hand; background-color: #ccCCff;}
    <!-- Default cell style. Used in e.g. expect/display tables -->
    td                  { border: 1px solid black; padding-left: 2px; padding-right: 2px; }
    <!-- Default no border cell -->
    td.noborder         { border: none; }
    <!-- Test case index table styles -->
    <!-- Cell style for index tables -->
    td.index            { border-top: none; border-left: none; border-right: none; padding-left: 10px; padding-right: 10px; }
    <!-- Cell style for mismatching expected item when errors are highlighted -->
    td.error            { background-color: #FFccCC; }
    <!-- The column header style in index tables -->
    <!-- Info table (summary & header) cell style -->
    td.info             { border: 1px solid black; text-align: left; }
    td.settings         { border: none; }
    .onHooverClass      { cursor: pointer; cursor: hand; text-decoration: underline; }
    font.arrows         { font-family: webdings; font-size: 110%; color: blue; text-align: center; margin-right: -3px;}
    <!-- The common style in tables headers/footers -->
    .indexHeader        { border: none; text-align: center; font-weight: bold; color: white; background-color: #000080;
                          padding-left: 10px; padding-right: 10px; }
    .indexFooter        { text-align: left; font-weight: bold; background-color: #ddDDdd; padding-left: 10px; padding-right: 10px; }
    .newLine            { clear: both; margin: 0; padding: 0; border: 0.1px solid #eeFFff; }
    <!-- Netscape 4, IE 4.x-5.0/Win and other lesser browsers will use this -->
    #fixedArrow         { position: absolute; right: 20px; bottom: 10px; font-family: webdings; font-size: 200%; text-align: center; cursor: pointer; cursor: hand; }
    <!-- used by Opera 5+, Netscape6+/Mozilla, Konqueror, Safari, OmniWeb 4.5+, iCab, ICEbrowser -->
    body <xsl:text disable-output-escaping="yes">&gt;</xsl:text> div#fixedArrow { position: fixed; }
    div.tcHeading       { font-size: 120%; margin: 0.2%; float: left; text-decoration: underline; cursor: help; }
    div.hiddenPopup     { background-color: #ffffcc; border-style: ridge; text-align: left; font-weight: bold; font-family: verdana; font-size: 11px;
                          z-index: 4; visibility: hidden; width: auto; position: absolute; filter: progid:DXImageTransform.Microsoft.Shadow(color = gray, direction = 135); }
    table.displayHelp   { font-size: 11px; font-weight: bold; font-family: Arial; background-color: #ccCCff; border: 1pt solid black; white-space: nowrap; }
    <!-- XML highlight styles -->
    .xmlDefaultClass    { cursor: pointer; cursor: hand; color: red; padding: 5px; border: 1px solid black; font: MessageBox; font: Message-Box; background: #ffffcc; float:left; clear: both; }
    .xmlHooverClass     { cursor: pointer; cursor: hand; color: red; padding: 5px; border: 1px solid black; font: MessageBox; font: Message-Box; background-color: white; float:left; clear: both; }
    .xmlElement         { color: blue; padding-left: 24px; }
    .xmlElementName     { color: DarkRed; }
    .xmlAttribName      { color: red; }
    .xmlAttribValue     { color: blue; }
    .xmlElementToggle   { color: red; cursor: pointer; cursor: hand; }
    .xmlText            { color: WindowText; padding-left: 0px; }
    .xmlCdataContent    { color: WindowText; font-family: Courier New; white-space: pre; display: block; border-left: 1px solid gray; padding-left: 24px; }
    .xmlComment         { color: blue; padding-left: 24px; }
    .xmlDocType         { color: blue; padding-left: 24px; }
    .xmlCommentContent  { white-space: pre; font-family: Courier New; color: green; }

</xsl:template>

<xsl:template name="frames-style">

    body                { background: #58C6D8; }
    input               { margin-top: 0px; margin-bottom: 0px }
    form                { margin-top: 5px; margin-bottom: 5px }
    select              { width: 95% }
    pre.showWs          { font-family: verdana; font-size: 10px; margin-bottom: 0px; margin-top: 0px; }
    font.webdings       { font-family: webdings; font-size: 110%; color: blue; text-align: center; margin-right: -3px;}
    div.select-group    { background-color: #72dbea; border: 5px; border-style: ridge; }
    div.header          { font-family: verdana, helvetica, arial, sans-serif; font-weight: bold; font-size: 90%; text-align: center; }
    div.left-headline   { font-family: verdana, helvetica, arial, sans-serif; font-weight: bold; font-size: 80%; text-align: center; background-color: #ccCCff; border-bottom: 4px ridge;}
    div.left-headline2  { font-family: verdana, helvetica, arial, sans-serif; font-weight: bold; font-size: 80%; text-align: center; background-color: #ccCCff; border-top: 4px ridge; border-bottom: 4px ridge; }
    div.hiddenPopup     { background-color: #ffffcc; border-style: ridge; text-align: left; font-weight: bold; font-family: verdana; font-size: 10px; padding: 5px;
                          z-index: 4; visibility: hidden; width: auto; position: absolute; filter: progid:DXImageTransform.Microsoft.Shadow(color = gray, direction = 135); }
    .search-button      { margin-left: 4px; height: 22px; width: 22px }
    .passed             { background-color: #ccFFcc; }
    .failed             { background-color: #FFccCC; }
    .search             { background-color: #ccCCff; }
    .skipped-passed     { background-color: #ccFFcc; color: blue; }
    .skipped-failed     { background-color: #FFccCC; color: blue; }
    .xmlOut             { margin-top: 15px; text-align: center; display: none; clear: both; }
    .defaultClass       { cursor: pointer; cursor: hand; color: red; padding: 5px; border: 1px solid black; font: MessageBox; font: Message-Box; background: #ffffcc; }
    .hooverClass        { cursor: pointer; cursor: hand; color: red; padding: 5px; border: 1px solid black; font: MessageBox; font: Message-Box; background-color: white; }
</xsl:template>

<xsl:template name="memleak-style">
    table{
        text-align: left;
        font-family: Verdana;
        font-weight: normal;
        font-size: 11px;
        background: #6F6F6f;
    } 
    table.bgtable{
        text-align: left;
        background: #efefef
        font-family: Verdana;
        font-weight: normal;
        cellspacing: 0
        border: 0
        font-size: 11px;
        width: 98%;   
    }      
    td {
    	border-left: 0px solid #E5E5E5;
    	border-bottom: 1px solid #E5E5E5;
    	background: #ffffff;
    	padding: 6px 6px 6px 12px;
    	height: 24px;
    	color: #4f6b72;
    }
    td.back {
    	border-left: 0px solid #E5E5E5;
    	border-bottom: 0px solid #E5E5E5;
    	background: #6F6F6f;
    	padding: 2px 2px 2px 2px;
    	color: #4f6b72;
    }
    td.rowodd {
    	border-left: 0px solid #efefef;
    	border-bottom: 1px solid #E5E5E5;
    	background: #f5f5f5;
    	padding: 1px 1px 1px 1px;
    	color: #4f6b72;
    }
    td.roweven {
    	background: #ffffff;
    	padding: 1px 1px 1px 1px;
    	color: #4f6b72;
    }    
    td.rowodd_mod {
    	border-left: 1px solid #efefef;
    	border-bottom: 1px solid #E5E5E5;
    	background: #F5F5E0;
    	padding: 1px 1px 1px 1px;
    	color: #4f6b72;
    }    
    td.roweven_mod {
    	background: #FFFFEf;
    	padding: 1px 1px 1px 1px;
    	color: #4f6b72;
    }  
    th {
    
    	color: #343434;
    	border-lef: 1px solid #6D6D72;
    	border-bottom: 1px solid #6D6D72;
    	border-top: 0px solid #6D6D72;
    	letter-spacing: 2px;
    	text-transform: uppercase;
    	height: 24px;
    	text-align: left;
    	padding: 4px 6px 6px 6px;
    	background: #6F6F6f url(../data/headerbg.jpg) repeat-x;
    }
    th.top {
    	font: bold;
    	color: #efefef;
    	border-right: 0px;
    	border-bottom: 0px;
    	border-top: 0px;
    	height: 23px;
    	letter-spacing: 4px;
    	text-transform: uppercase;
    	text-align: left;
    	padding: 4px 6px 6px 6px;
    	background: #6F6F6f url(../data/headerbg_top.jpg) no-repeat;
    }
    th.nobg {
    	border-top: 0;
    	border-left: 0;
    	height: 24px;
    	border-right: 1px solid #ADDBFF;
    	background: none;
    }   
    td.nobg {
    	border: 0;	
    	background: none;
    }    
    td.logotop {
    	border: 0;
    	height:56px;
    	background: #234B9B url(../data/memoryleak_logo.jpg) no-repeat;
    }
    td.logobgtable {
    	border: 0;
    	height:24px;
    	background: #efefef url(../data/backgrtop.jpg) repeat-y;
    }
    td.background {
    	border: 0;
    	background: #efefef url(../data/backgr.jpg) repeat-y;
    }    
    h2 {
    	font-family: Verdana;
    	font-size: 15pt;
    	color: #343434;
    	padding-top: 12px;
    	padding-bottom: 3px;
    }
    body{ 
    background: #234B9B;
    }


</xsl:template>

</xsl:stylesheet>
