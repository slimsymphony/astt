<?xml version="1.0" encoding="utf-8" ?>
<!--
    NOKIA
    MP S40 SW
    UI Testing Tools

            Memory leak XML loader main template
            ===============================================
            Granite test report transformations

    Copyright (c) Nokia. All rights reserved.

    %full_filespec: test_report_memleak_main.xslt-2:ascii:ou1iam#1 %

    %version:       2 %
    %date_created:  Thu May 14 14:30:14 2009 %
    %created_by:    sapousi %

    Reason:         Created
    Reference:      CM Synergy task: ou1iam#145890
    Description:    Added export to Excel function.
                    Copy to clipboard format improvements.

    Specification:

    Notes:

        This file serves as the launching point of test reporting XML to
        HTML transformation.

        Walkthrough:
            - Initiate main template
            - Generate HTML header
                - topic
                - CSS style definition
            - Create index by memory set (test_report_xml_to_html_header.xslt)
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

<!-- <xsl:stylesheet version='1.0' xmlns:xsl='http://www.w3.org/1999/XSL/Transform'> -->
<xsl:stylesheet 
  xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
  xmlns:exslt="http://exslt.org/common"
  xmlns:msxsl="urn:schemas-microsoft-com:xslt"
  extension-element-prefixes="msxsl"
  exclude-result-prefixes="exslt msxsl"
  version="1.0">
  

<xsl:output method="html" media-type="text/html" encoding="UTF-8"/>
<xsl:param name="filename"/>
<xsl:strip-space elements="*"/>



<!--

    Template: Main template

    Description: Generates test report HTML from XML input

    Scope: /testreport

    Parameters: none

    Output: HTML report <html>...</html>

-->
<msxsl:script language="JScript" implements-prefix="exslt">
 this['node-set'] =  function (x) {
  return x;
  }
</msxsl:script>


<xsl:template match="/">
    <!-- Begin HTML file generation -->

<html>
<head>
<script>
<![CDATA[
function loadXMLDoc(fname)
{
  var xmlDoc;
  // code for IE
  if (window.ActiveXObject)
  {
    xmlDoc=new ActiveXObject("Microsoft.XMLDOM");
  }
  // code for Mozilla, Firefox, Opera, etc.
  else if (document.implementation
  && document.implementation.createDocument)
  {
    xmlDoc=document.implementation.createDocument("","",null);
   }
  else
  {
    alert('Your browser cannot handle this script');
  }
xmlDoc.async=false;
xmlDoc.load(fname);
return(xmlDoc);
}

// Flush the Excel activeX object
function Cleanup() {
    window.clearInterval(idTmr);
    CollectGarbage();
 }

// Separate the filename from the filepath
function splitCallerPath(caller)
{
    var callerPathArray = caller.split("/");
    var returnString = "";
    if (callerPathArray.length > 0)
    returnString = callerPathArray[callerPathArray.length-1];
    return returnString;
} 
 
function copyToClipBoard() //task, set, address, size, callers)
{
    var copyString = "";
    var paramNames=new Array(12);
    paramNames[0] = "Task";
    paramNames[1] = "Set";
    paramNames[2] = "Address";
    paramNames[3] = "Size";
    paramNames[4] = "Caller1";
    paramNames[5] = "Caller2";
    paramNames[6] = "Caller3";
    paramNames[7] = "Caller4";
    paramNames[8] = "Caller5";
    paramNames[9] = "Caller6";
    paramNames[10] = "Caller7";
    paramNames[11] = "Caller8";
    
    for (i=0;i<copyToClipBoard.arguments.length;i++)
    {
        copyString = copyString + paramNames[i] + ": " + splitCallerPath(copyToClipBoard.arguments[i]) + "\n";
    }
    window.clipboardData.setData('text',copyString);
}

function exportIntoExcel()
{
    if (document.implementation && document.implementation.createDocument)
    {
        xmlDoc = document.implementation.createDocument("", "", null);
        xmlDoc.onload = createTable;
    }
    else if (window.ActiveXObject)
    {
        xmlDoc = new ActiveXObject("Microsoft.XMLDOM");
    }
    else
    {
        alert('Your browser can\'t handle this script');
        return;
    }
    xmlDoc.load("]]><xsl:copy-of  select="$filename" /><![CDATA[.xml");

    Excel = new ActiveXObject("Excel.Application"); 
    objFileSys = new ActiveXObject("Scripting.FileSystemObject");
    var testCase = xmlDoc.getElementsByTagName('test_case');
    Excel.Application.SheetsInNewWorkbook = testCase.length;
    Book = Excel.Workbooks.Add();

    for (i=0;i<testCase.length;i++)
        {
        sheet = Book.Worksheets("Sheet"+(i+1));
        sheet.Cells(1,1).Value = testCase[i].getAttribute("name");
        sheet.Cells(2,1).Value = "Task";
        sheet.Cells(2,2).Value = "Set";
        sheet.Cells(2,3).Value = "Address";
        sheet.Cells(2,4).Value = "Size";        
        sheet.Cells(2,5).Value = "Caller1";
        sheet.Cells(2,6).Value = "Caller2";
        sheet.Cells(2,7).Value = "Caller3";
        sheet.Cells(2,8).Value = "Caller4";
        sheet.Cells(2,9).Value = "Caller5";
        sheet.Cells(2,10).Value = "Caller6";
        sheet.Cells(2,11).Value = "Caller7";
        sheet.Cells(2,12).Value = "Caller8";
        var lineNumber = 3;
        
        for (leakCount=0;leakCount<testCase[i].childNodes.length;leakCount++)
        {   
            for (stampCount=0;stampCount<testCase[i].childNodes[leakCount].childNodes.length;stampCount++)                
                if (testCase[i].childNodes[leakCount].childNodes[stampCount].tagName == "time_stamp")
                    {
                    sheet.Cells(lineNumber,1).Value = testCase[i].childNodes[leakCount].getAttribute("task");
                    sheet.Cells(lineNumber,2).Value = testCase[i].childNodes[leakCount].childNodes[stampCount].getAttribute("set");
                    sheet.Cells(lineNumber,3).Value = testCase[i].childNodes[leakCount].getAttribute("ptr");
                    sheet.Cells(lineNumber,4).Value = testCase[i].childNodes[leakCount].childNodes[stampCount].getAttribute("size");                    
                    for (callerCount=0;callerCount<testCase[i].childNodes[leakCount].childNodes.length;callerCount++)
                        {

                            if (testCase[i].childNodes[leakCount].childNodes[callerCount].tagName == "caller")
                            {
                                var callerPath = testCase[i].childNodes[leakCount].childNodes[callerCount].getAttribute("filePath");
                                var caller_array=callerPath.split("/");
                                sheet.Cells(lineNumber,5+callerCount).Value = caller_array[caller_array.length -1] + ":" + testCase[i].childNodes[leakCount].childNodes[callerCount].getAttribute("function");                                
                            }                            
                        } 
                    lineNumber = lineNumber +1;                        
                    }
        }
        sheet.Columns('B:H').EntireColumn.autofit();
        sheet.Rows(1).Font.Size = 15;
        sheet.Rows(2).Font.Bold = 1;

    }
    SavePath = objFileSys.BuildPath(objFileSys.GetFolder("."), "MemLeakReport.xls");

    Book.SaveAs(SavePath); 

    Excel.visible = true;
    idTmr = window.setInterval("Cleanup();",1);
}

function displayResult(sortKey, sortOrder)
{
// code for IE
if (window.ActiveXObject)
  {
    var xslt = new ActiveXObject("Msxml2.XSLTemplate.3.0");
    var xsldoc = new ActiveXObject("Msxml2.FreeThreadedDOMDocument.3.0");
    var xslproc;
    xsldoc.async = false;
    xsldoc.load("xslt/mem_leak_xml_to_html.xslt");
    if (xsldoc.parseError.errorCode != 0) {
       var myErr = xsldoc.parseError;
       document.getElementById("example").innerHTML="You have error " + myErr.reason;
    } else {
       xslt.stylesheet = xsldoc;
       var xmldoc = new ActiveXObject("Msxml2.DOMDocument.3.0");
       xmldoc.async = false;
       xmldoc.load("]]><xsl:copy-of  select="$filename" /><![CDATA[.xml");
       if (xmldoc.parseError.errorCode != 0) {
          var myErr = xmldoc.parseError;
          document.getElementById("example").innerHTML="You have error " + myErr.reason;
       } else {
          xslproc = xslt.createProcessor();
          xslproc.input = xmldoc;
          xslproc.addParameter("sortKey",sortKey);
          xslproc.addParameter("sortOrder",sortOrder);
          xslproc.transform();
          document.getElementById("example").innerHTML=xslproc.output
       }      
    }    
  }
  // code for Mozilla, Firefox, Opera, etc.
  else if (document.implementation  
  && document.implementation.createDocument)
  {
    document.getElementById("example").innerHTML="<b>Sorry, but only Internet Expolorer is supported.</b>"
  }
}
]]>

</script>
<link rel="stylesheet" href="style/test_report_memleak_style.css" type="text/css" />
</head>
<body id="example" onLoad="displayResult('date', 'ascending')">


</body>
</html>



    <!-- End HTML file generation -->
</xsl:template>
</xsl:stylesheet>