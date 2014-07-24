<?xml version="1.0" encoding="utf-8" ?>
<!--
    NOKIA
    MP SW Look&Feel
    S40 Development Tools, Testing Tools


                Test report javascript template
                ===============================
                Granite test report transformations

    Copyright (c) Nokia. All rights reserved.

    %full_filespec: test_report_javascript.xslt-ou1s40#26:ascii:ou1iam#1 %

    Notes:
        Result XML indentation 4 spaces

-->
<xsl:stylesheet version = '1.0' xmlns:xsl='http://www.w3.org/1999/XSL/Transform'>
    <xsl:output method="html" media-type="text/html" encoding="UTF-8"/>

    <xsl:template name="common-script">
        <xsl:comment>
        /*
            Array.indexOf(value, begin, strict)
            Return index of the first element that matches value
        */
        Array.prototype.indexOf = function(v, b, s) {
            for(var i = +b || 0, l = this.length; i &lt; l; i++) {
                if(this[i]===v || s &amp;&amp; this[i]==v)
                    return i;
            }
            return -1;
        };

        /*
            Array.unique(strict)
            Remove duplicate values
        */
        Array.prototype.unique = function(b) {
            var a = [], l = this.length;
            for(var i=0; i&lt;l; i++) {
                if(a.indexOf(this[i], 0, b) &lt; 0)
                    a.push(this[i]);
            }
            return a;
        };

        /*
            Setups browser specific variables

            Needed for dynamic showing and hiding
            Supports IE4, IE5, IE6, IE7, IE8, NS4, NS6, MAC
        */
        function BrowserChecker() {
            this.ver   = navigator.appVersion;
            this.agent = navigator.userAgent.toUpperCase();
            this.dom   = document.getElementById ? 1 : 0;

            this.NS4   = (document.layers &amp;&amp; !this.dom) ? 1 : 0;
            this.NS6   = (this.dom &amp;&amp; parseInt(this.ver) >= 5 ) ? 1 : 0;
            this.IE4   = (document.all &amp;&amp; !this.dom) ? 1 : 0;
            this.IE5   = (this.ver.indexOf("MSIE 5") > -1 &amp;&amp; this.dom) ? 1 : 0;
            this.IE6   = (this.ver.indexOf("MSIE 6") > -1 &amp;&amp; this.dom) ? 1 : 0;
            this.IE7   = (this.ver.indexOf("MSIE 7") > -1 &amp;&amp; this.dom) ? 1 : 0;
            this.IE8   = (this.ver.indexOf("MSIE 8") > -1 &amp;&amp; this.dom) ? 1 : 0;
            this.IE    = this.IE4 || this.IE5 || this.IE6 || this.IE7 || this.IE8;
            this.MAC   = this.agent.indexOf( "MAC") ? 0 : 1;
            this.OPERA = window.opera

            return this;
        }

        /*
            Get document object with id / layerName.
        */
        function getLayerHandle(layerName) {
            if(browserIS.IE5 || browserIS.IE6 || browserIS.IE7 || browserIS.IE8 || browserIS.NS6) {
                return eval('document.getElementById("' + layerName + '")');
            }  else if(browserIS.IE4) {
                return eval('document.all("' + layerName + '")');
            } else if(browserIS.NS4) {
                return eval('document.layers["' + layerName + '"]');
            } else {
                alert("Unsupported browser or document isn't fully loaded yet!");
                return none;
            }
        }

        /*
            Initialize global definitions.
        */
        function defineGlobals(testRun) {
            tPrefix = (testRun &gt; 1) ? '_' + testRun.toString(): '';
            // Check browser.
            browserIS = new BrowserChecker();
            styleSwitch = (browserIS.NS4) ? "" : ".style";
            visibleSwitch = (browserIS.NS4) ? "'show'" : "'visible'";
            hiddenSwitch = (browserIS.NS4) ? "'hide'" : "'hidden'";
            offsetxpoint = 8, offsetypoint = 8;

            // Define regular expressions.
            rExpShy = /&amp;shy;/g;
            rExpNbsp = /&amp;nbsp;/g;
            rExpText = /&lt;pre class="?showWs"?&gt;([\s\S]*)&lt;\/pre&gt;/i;
            rExpTraceBack = /(\w.[\/].+?)[,].*?(\d+).*/;
            rExpTraceBack2 = /[\/]/g;
            rExpBackSlash = /[\\]/g;
            rExpTraceBack3 = /['](.*)['].*['](.*)[']/;
            oTraceArray = {'main': {'status': null, 'object': null}, 'remote': {'status': null, 'object': null}}
        <xsl:choose>
            <xsl:when test="$email-testcase">
            rExpImageAbsPath = /[(](.*)[)]/;
            oDocumentModel = null;
            </xsl:when>
            <xsl:otherwise>
            rExpImageAbsPath = /[(][.][.][\/](.*)[)]/;
            </xsl:otherwise>
        </xsl:choose>
            // Other definitions.
            tSubarea = ''; tFeature = ''; tTestcase = ''; tSelectionType = 'subarea';
            defXmlPath = ''; defHtmlPath = '';
            // Create instances of FileSystem object.
            try {
                oFileSystem = creatorWindow.oFileSystem;
            } catch(er) {
                oFileSystem = new fileSystemConstructor();
            }
        <xsl:if test="$email-testcase">
            // Move bitmaps.
            oFileSystem.moveObjects();
        </xsl:if>
        }

        /*
            This function dynamically shows or hides table
            cells according to following rules:

            When we open items we open items only directly below
            this level (click the primary level, only the second level opens).

            When we close items we close all items below this level
            recursively (click the primary level, every thing below it is
            hidden).

            This behavior is created using exact id string match for
            opening (idmark==id) and substring id match (idmark found in id)
            for close.
        */
        function toggle_rows_visibility(toggler, tableid, idmark) {
            var visibility;
            aTR = new Array();

            oTR = toggler.parentNode
            while(!/tr/i.test(oTR.nodeName))
                oTR = oTR.parentNode

            oTR = oTR.nextSibling
            while(!/tr/i.test(oTR.nodeName))
                oTR = oTR.nextSibling

            while(oTR.id.indexOf(idmark) != -1) {
                aTR.push(oTR)
                oTR = oTR.nextSibling
                while(!/tr/i.test(oTR.nodeName))
                    oTR = oTR.nextSibling
            }

            visibility = (eval("aTR[0]" + styleSwitch + ".display == ''")) ? false : true;
            while(aTR.length) {
                oTR = aTR.pop()
                status = visibility ? '' : 'none';
                toggler.getElementsByTagName("font")[0].innerHTML = visibility ? '&#54;' : '&#52;';
                if(oTR.id == idmark) {
                    eval("oTR" + styleSwitch + ".display = status");
                    oFont = oTR.getElementsByTagName("font")
                    if(visibility == false &amp;&amp; oFont.length &amp;&amp; oFont[0].className == 'arrows')
                        oFont[0].innerHTML = '&#52;';
                }
                else if(visibility == false) eval("oTR" + styleSwitch + ".display = status");
            }
        }

        /*
            This function cycles through three different stages
            to open details.

            After the operation the text of the toggler
            object is changed.

            Test step div tags need to have their status attribute
            set to "expected", "exception", "ts-expected" and "capture".
            Othetwise it would be very difficult to separate different dynamic
            test steps blocks.

            Parameters:
                toggler: "this" pointer to the toggler object
                parentid: the id attribute of the parent node
                showClass: CSS visible class name
                hideClass: CSS hidden class name
        */
        function toggle_all_test_steps(toggler, parentid, showClass, hideClass) {
            var status, objFont;
            var item = getLayerHandle(parentid);
            if (!item) return;
            var oDiv = item.getElementsByTagName("div");
            var oFont = item.getElementsByTagName("font");

            switch (toggler.innerHTML) {
                case "[Open teststep details]":
                    toggler.innerHTML = "[Open all teststep details]";
                    for(var i=0; i&lt;oDiv.length; i++) {
                        status = oDiv[i].getAttribute("status");
                        if(status == "expected" || status == "capture" || status == "exception") {
                            oDiv[i].className = showClass;
                            objFont = eval("oFont.image" + oDiv[i].id);
                            objFont.innerHTML = '&#54;';
                        }
                    }
                    break;
                case "[Open all teststep details]":
                    toggler.innerHTML = "[Close all teststep details]";
                    for(var i=0; i&lt;oDiv.length; i++) {
                        status = oDiv[i].getAttribute("status");
                        if(status == "ts-expected") {
                            oDiv[i].className = showClass;
                            objFont = eval("oFont.image" + oDiv[i].id);
                            objFont.innerHTML = '&#54;';
                        }
                    }
                    break;
                default:
                    toggler.innerHTML = "[Open teststep details]";
                    for(var i=0; i&lt;oDiv.length; i++) {
                        status = oDiv[i].getAttribute("status");
                        if(status == "expected" || status == "ts-expected" || status == "capture") {
                            oDiv[i].className = hideClass;
                            objFont = eval("oFont.image" + oDiv[i].id);
                            objFont.innerHTML = '&#52;';
                        }
                    }
                    break;
            }
        }

        /*
            Switches between showing and hiding of sinle div.

            Parameters:
                id: div id
                showBlock: CSS class name for visible section
                hideBlock: CSS class name for invisible section
        */
        function flipVisibility(toggler, id, showBlock, hideBlock) {
            var status, objFont;
            var item = getLayerHandle(id)
            if (!item) return;
            var oDiv = item.getElementsByTagName("div");
            var oFont = item.getElementsByTagName("font");

            switch (item.className) {
                case showBlock:
                    toggler.getElementsByTagName("font")[0].innerHTML = '&#52;';
                    item.className = hideBlock;
                    for(var i=0; i&lt;oDiv.length; i++) {
                        status = oDiv[i].getAttribute("status");
                        if(status == "exception" || status == "capture") {
                            oDiv[i].className = hideBlock;;
                            objFont = eval("oFont.image" + oDiv[i].id);
                            objFont.innerHTML = '&#52;';
                        }
                    }
                    break;
                case hideBlock:
                    toggler.getElementsByTagName("font")[0].innerHTML = '&#54;';
                    item.className = showBlock;
                    for(var i=0; i&lt;oDiv.length; i++) {
                        status = oDiv[i].getAttribute("status");
                        if(status == "exception" || status == "capture") {
                            oDiv[i].className = showBlock;
                            objFont = eval("oFont.image" + oDiv[i].id);
                            objFont.innerHTML = '&#54;';
                        }
                    }
                    break;
            }
        }

        /*
        */
        function getTraceData(toggler, fileName, stepName, stepId) {
            var oTraceDocument = new documentModelConstructor();
            var xPath = "//step[@stepId = '" + stepId + "']";
            var traceDataPath = '../traces/' + escape(fileName);
            oTraceDocument.loadDocuments(traceDataPath, '../xslt/test_report_xml_highlight.xslt', false)
            // Hack for IE, to get unique Ids for xml-highlight collapsing functionality.
            var transformed = oTraceDocument.xsltTransformer(xPath, {'step-id': stepId});
            if (transformed)
                toggler.innerHTML = transformed;

            toggler.setAttribute('onclick', '');
            toggler.setAttribute('onmouseover', '');
        }

        /*
        */
        function flipElement(toggler, elementId) {
            var oElement = getLayerHandle(elementId)

            switch (toggler.innerHTML) {
                case '+':
                    toggler.innerHTML = '-';
                    oElement.style.display = 'block';
                    break;
                case '-':
                    toggler.innerHTML = '+';
                    oElement.style.display = 'none';
                    break;
            }
        }

        /*
        */
        function highLightRow(toggler, class_name, image_id, row_id) {
            var oRow = getLayerHandle(row_id)

            if (oRow)
                toggler.className = oRow.className = class_name
            else
                toggler.className = class_name

            if (image_id) {
                var state = (class_name) ? true : false;
                highLightZone(toggler, image_id, state);
            }
        }

        /*
        */
        function highLightZone(toggler, image_id, state) {
            var oDim = new Object();
            var oImg = getLayerHandle(image_id)
            oDim.x = 0, oDim.y = 0, oDim.width = 0, oDim.height = 0
            imageWidth = eval("oImg" + styleSwitch + ".width").replace('px', '')
            imageHeight = eval("oImg" + styleSwitch + ".height").replace('px', '')

            var oTD = toggler.getElementsByTagName("td")
            for(var i=0; i&lt;oTD.length; i++) {
                var oName = oTD[i].getAttribute("name")
                if(oName) {
                    if (oTD[i].innerHTML != 'n/a' &amp;&amp; oTD[i].innerHTML != '')
                        eval("oDim." + oName + " = " + oTD[i].innerHTML)
                    else {
                        break;
                    }
                }
            }

            if (!oDim.width) {
                oDim.width = imageWidth - oDim.x
            }
            if (!oDim.height) {
                oDim.height = imageHeight - oDim.y
            }

            for(var i=0; i&lt;oImg.childNodes.length; i++) {
                if(oImg.childNodes[i].className == 'transBox')
                    oTransBox = oImg.childNodes[i];
            }

            eval("oImg" + styleSwitch + ".paddingLeft = '" + oDim.x.toString() + "px'");
            eval("oImg" + styleSwitch + ".paddingTop = '" + oDim.y.toString() + "px'");

            if (oDim.width) {
                eval("oTransBox" + styleSwitch + ".width = '" + oDim.width.toString() + "px'");
                eval("oTransBox" + styleSwitch + ".height = '" + oDim.height.toString() + "px'");
            } else {
                eval("oTransBox" + styleSwitch + ".width = oImg" + styleSwitch + ".width");
                eval("oTransBox" + styleSwitch + ".height = oImg" + styleSwitch + ".height");
            }

            if(state)
                eval("oTransBox" + styleSwitch + ".display = 'block'")
            else
                eval("oTransBox" + styleSwitch + ".display = 'none'")
        }

        /*
        */
        function dec2Hex(decimal) {
            var hexChars = "0123456789abcdef";
            var low, high;
            var hex = new Array();

            while(decimal) {
                low = (decimal % 256) % 16;
                high = ((decimal % 256) - low) / 16;
                hex.push(hexChars.charAt(high) + hexChars.charAt(low))
                decimal = (decimal - (decimal % 256)) / 256;
            }
            return hex.reverse().toString().replace(',', '');
        }

        /*
        */
        function ucHexDump(toggler) {
            var uc_code = '', utf8_str = '';
            var tHidden = toggler.getAttribute("hidden_str");
            var oVisible = toggler.innerHTML.match(rExpText);

            if(oVisible) {
                tVisible = oVisible[1].replace(rExpNbsp, '\xa0').replace(rExpShy, '\xad')
                if(tHidden == null) {
                    for(var i=0; i&lt;tVisible.length; i++) {
                        uc_code = tVisible.charCodeAt(i)
                        utf8_str += dec2Hex(uc_code);
                        if (i&lt;tVisible.length - 1) utf8_str += ((i+1) % 20) ? ',': ',\n';
                        tHidden = utf8_str;
                    }
                }
                toggler.setAttribute('hidden_str', tVisible);
                toggler.innerHTML = '&lt;pre class="showWs"&gt;' + tHidden + '&lt;/pre&gt;';
            }
        }

        /*
        */
        function ietruebody() {
            return (document.compatMode &amp;&amp; document.compatMode != "BackCompat") ? document.documentElement : document.body
        }

        /*
        */
        function positiontip(e) {
            var winX = (browserIS.NS4 || browserIS.NS6) ? e.clientX : event.clientX;
            var winY = (browserIS.NS4 || browserIS.NS6) ? e.clientY : event.clientY;
            var winW = (browserIS.NS4 || browserIS.NS6) ? document.body.offsetWidth : ietruebody().clientWidth;
            var winH = (browserIS.NS4 || browserIS.NS6) ? document.body.offsetHeight : ietruebody().clientHeight;
            var curX = (browserIS.NS4 || browserIS.NS6) ? e.pageX + offsetxpoint : event.clientX + ietruebody().scrollLeft + offsetxpoint;
            var curY = (browserIS.NS4 || browserIS.NS6) ? e.pageY + offsetypoint : event.clientY + ietruebody().scrollTop + offsetypoint;

            // Test to see if default position too close to the edges of window/frame and adjust if necessary.
            var dx = winW - winX - offsetxpoint - oElement.offsetWidth;
            var dy = winH - winY - offsetypoint - oElement.offsetHeight;
            var newX = (dx &lt; 0) ? Math.max(curX - oElement.offsetWidth - offsetxpoint, 0) : Math.max(curX + offsetxpoint, 0);
            var newY = (dy &lt; 0) ? Math.max(curY - oElement.offsetHeight - offsetypoint, 0) : Math.max(curY + offsetypoint, 0);

            // Position the horizontal position of the menu where the mouse is positioned.
            eval("oElement" + styleSwitch + ".left = '" + newX.toString() + "px'");
            eval("oElement" + styleSwitch + ".top = '"  + newY.toString() + "px'");
            eval("oElement" + styleSwitch + ".visibility = " + visibleSwitch);
        }

        /*
        */
        function togglePopup(popupName, e) {
            oElement = getLayerHandle(popupName);

            if (e.type == "mouseover") {
                document.onmousemove = positiontip
            }
            else if (e.type == "mouseout") {
                document.onmousemove = 'none';
                eval("oElement" + styleSwitch + ".visibility = " + hiddenSwitch);
            }
        }

        /*
        */
        function flipUnknown(toggler) {
            var oElem = toggler
            while(!/table/i.test(oElem.nodeName))
                oElem = oElem.parentNode

            var oTR = oElem.getElementsByTagName("tr");
            switch (toggler.innerHTML) {
                case "[Show other items found on foreground]":
                    toggler.innerHTML = "[Show other items found on foreground/background]";
                    for(var i=0; i&lt;oTR.length; i++) {
                        var oStyle = eval("oTR[i]" + styleSwitch)
                        switch (oTR[i].id) {
                            case "unknown-fg":
                                oStyle.display = '';
                                break;
                            case "unknown-bg":
                                oStyle.display = 'none';
                                break;
                        }
                    }
                    break;
                case "[Show other items found on foreground/background]":
                    toggler.innerHTML = "[Hide other items]";
                    for(var i=0; i&lt;oTR.length; i++) {
                        var oStyle = eval("oTR[i]" + styleSwitch)
                        switch (oTR[i].id) {
                            case "unknown-fg":
                            case "unknown-bg":
                                oStyle.display = '';
                                break;
                        }
                    }
                    break;
                case "[Hide other items]":
                    toggler.innerHTML = "[Show other items found on foreground]";
                    for(var i=0; i&lt;oTR.length; i++) {
                        var oStyle = eval("oTR[i]" + styleSwitch)
                        switch (oTR[i].id) {
                            case "unknown-fg":
                            case "unknown-bg":
                                oStyle.display = 'none';
                                break;
                        }
                    }
                    break;
            }
        }
        </xsl:comment>
    </xsl:template>

    <xsl:template name="left-frame-script">
        <xsl:comment>
        /*
        */
        function populateList(name, tSubarea, tFeature) {
            var oSelection, newListItems;
            var rCount = /[(](\d*)[)]/;
            switch (name) {
                case 'feature':
                    oSelection = document.forms['feature'].elements[0];
                    newListItems = featureArray[tSubarea];
                    break;
                case 'testcase':
                    oSelection = document.forms['testcase'].elements[0];
                    newListItems = testcaseArray[tSubarea][tFeature];
                    break;
            }
            var oText = oSelection.previousSibling.previousSibling;

            for(var i=oSelection.options.length-1; i>0; i=i-1) {
                oSelection.options[i] = null;
            }

            var i = 0;
            for(var item in newListItems) {
                oSelection.options[i] = new Option(item, item);
                switch (name) {
                    case 'feature':
                        state = newListItems[item];
                        break;
                    case 'testcase':
                        state = newListItems[item][0];
                        break;
                }
                switch(state) {
                    case 'skipped':
                        oSelection.options[i].style.color = 'blue';
                    case 'passed':
                        oSelection.options[i].style.background = '#ccFFcc';
                        break;
                    case 'both':
                        oSelection.options[i].style.color = 'blue';
                    case 'failed':
                        oSelection.options[i].style.background = '#FFccCC';
                        break;
                }
                i = i + 1;
            }
            oSelection.options[0].selected = true;

            oText.innerHTML = oText.innerHTML.replace(rCount, "(" + i.toString() + ")");
            return oSelection.options[0];
        }

        /*
        */
        function selectFromList(oTag, selection) {
            var oSelected;

            with (oTag) {
                for(var i=0; i&lt;options.length; i=i+1) {
                    if (options[i].text == selection) {
                        oSelected = oTag.options[i];
                        oSelected.selected = true
                        break;
                    }
                }
            }
            return oSelected;
        }

        /*
        */
        function resetSelectionLists(state) {
            for(var i=0; i&lt;document.forms.length; i++) {
                switch (document.forms[i].name) {
                    case state:
                    case 'subarea':
                    case 'feature':
                    case 'testcase':
                        break;
                    default:
                        document.forms[i].elements[0].options[0].selected = true;
                        break;
                }
           }
        }

        /*
        */
        function refreshDocument() {
            var oSelection = document.forms[tSelectionType].elements[0];
            openDocument(oSelection, tSelectionType);
        }

        /*
        */
        function openDocument(toggler, state) {
            var all, idx;
            var oAll, oSubarea, oFeature, oTestcase, oSelected;

            if (toggler.options[toggler.selectedIndex].disabled)
                return;

            switch (state) {
                case "subarea":
                    resetSelectionLists(null);
                    oSubarea = toggler.options[toggler.selectedIndex];
                    tSubarea = oSubarea.text;
                    oFeature = populateList('feature', tSubarea);
                    tFeature = oFeature.text;
                    oTestcase = populateList('testcase', tSubarea, tFeature);
                    tTestcase = oTestcase.text;
                    tSelectionType = 'testcase';
                    break;
                case "feature":
                    resetSelectionLists(null);
                    oSubarea = document.forms['subarea'].elements[0];
                    idx = oSubarea.selectedIndex;
                    tSubarea = oSubarea.options[idx].text;
                    oFeature = toggler.options[toggler.selectedIndex];
                    tFeature = toggler.options[toggler.selectedIndex].text;
                    oTestcase = populateList('testcase', tSubarea, tFeature);
                    tTestcase = oTestcase.text;
                    tSelectionType = 'testcase';
                    break;
                case "testcase":
                    resetSelectionLists(null);
                    oSubarea = document.forms['subarea'].elements[0];
                    idx = oSubarea.selectedIndex;
                    tSubarea = oSubarea.options[idx].text;
                    oFeature = document.forms['feature'].elements[0];
                    idx = oFeature.selectedIndex;
                    tFeature = oFeature.options[idx].text;
                    tTestcase = toggler.options[toggler.selectedIndex].text;
                    tSelectionType = 'testcase';
                    break;
                default:
                    resetSelectionLists(state);
                    oAll = toggler.options[toggler.selectedIndex];
                    all = oAll.value.split("|")
                    oSubarea = document.forms['subarea'].elements[0];
                    tSubarea = all[0];
                    oSelected = selectFromList(oSubarea, tSubarea);
                    oFeature = populateList('feature', tSubarea).parentNode;
                    tFeature = all[1];
                    oSelected = selectFromList(oFeature, tFeature);
                    oTestcase = populateList('testcase', tSubarea, tFeature).parentNode;
                    tTestcase = toggler.options[toggler.selectedIndex].text;
                    selectFromList(oTestcase, tTestcase);
                    tSelectionType = state;
                    break;
            }
            defXmlPath = '../' + escape(testcaseArray[tSubarea][tFeature][tTestcase][1]);

            if (!browserIS.NS4 &amp;&amp; !browserIS.NS6) {
                var oDocumentModel = new documentModelConstructor();
                oDocumentModel.loadDocuments(defXmlPath, '../xslt/test_report_xml_to_html.xslt', false)
                var transformed = oDocumentModel.xsltTransformer(null, {'transformMode': 'framed-report'});
                oDocumentModel.openTestcase(transformed);
            } else {
                parent.frames['main_frame'].location = defXmlPath;
            }

        }

        /*
        */
        function searchTestcase() {
            var rCount = /[(](\d*)[)]/;
            var rMeta = /(\$|\(|\)|\*|\+|\.|\[|\]|\?|\\|\^|\{|\}|\|\1)/g;
            var sSearch = document.getElementsByName('search-string')[0].value;
            var oSearch = document.forms['search-results'].elements[0];
            var oText = getLayerHandle("search-headline");
            if (!sSearch) return;
            sSearch = sSearch.replace(rMeta, "\\$1");
            var rSearch = eval('/' + sSearch + '/i');

            while (oSearch.options.length) {
                oSearch.options[oSearch.options.length - 1] = null;
            }

            for(var subarea in featureArray) {
                oFeatures = featureArray[subarea]
                for(var feature in oFeatures) {
                    oTestcases = testcaseArray[subarea][feature]
                    for(var testcase in oTestcases) {
                        oResult = oTestcases[testcase][0]
                        // oPath = oTestcases[testcase][1]
                        if (testcase.match(rSearch)) {
                            var idx = oSearch.options.length
                            oSearch.options[idx] = new Option(testcase, testcase);
                            oSearch.options[idx].text = testcase
                            oSearch.options[idx].value = subarea + '|' + feature
                            switch(oResult) {
                                case 'skipped':
                                    oSearch.options[idx].style.color = 'blue';
                                    break;
                                case 'passed':
                                    oSearch.options[idx].style.background = '#ccFFcc';
                                    break;
                                case 'failed':
                                    oSearch.options[idx].style.background = '#FFccCC';
                                    break;
                            }
                        }
                    }
                }
            }

            if (oSearch.options.length > 0) {
                oText.innerHTML = oText.innerHTML.replace(rCount, "(" + (idx + 1).toString() + ")");
                oSearch.options[0].selected = true;
                openDocument(oSearch, 'search-results');
            } else {
                oText.innerHTML = oText.innerHTML.replace(rCount, "(0)");
            }
        }

        /*
        */
        function loopTests(direction) {
            var idxFirst = (tSelectionType == 'testcase') ? 0 : 1;
            var oSelection = document.forms[tSelectionType].elements[0];
            switch (direction) {
                case 'previous':
                    if (oSelection.selectedIndex &gt; idxFirst) {
                        oSelection.selectedIndex -= 1;
                        refreshDocument();
                    }
                    break;
                case 'next':
                    if (oSelection.selectedIndex &lt; (oSelection.length - 1)) {
                        oSelection.selectedIndex += 1;
                        refreshDocument();
                    }
                    break;
            }
        }

        /*
        */
        function openProperties(toggler) {
            var sName = toggler.options[toggler.selectedIndex].value;
            var sFeatures = 'toolbar=no, scrollbars=yes, resizable=yes';
            var oSummary = parent.frames['main_frame'].document.getElementsByName(sName);

            if (sName == "subarea-feature-summaries") {
                newWindow = window.open('test_report_summary' + tPrefix + '.html', '', sFeatures);
                newWindow.creatorWindow = self;
            } else if (sName == "email-test-case") {
                oFileSystem.sendEmail();
            } else if (oSummary.length) {
                switch (sName) {
                    case "general-information":
                        sFeatures += ', width=1000, height=450';
                        openNewWindow(sFeatures, oSummary);
                        break;
                    case "settings":
                        openNewWindow(sFeatures, oSummary);
                        break;
                    case "general-warnings":
                    case "ignore-flags":
                        sFeatures += ', width=600, height=400';
                        openNewWindow(sFeatures, oSummary);
                        break;
                }
            }
            toggler.options[0].selected = true;
        }

        /*
        */
        function openNewWindow(sFeatures, oSummary) {
            var tSummary = '';
            for(var i=0; i&lt;oSummary.length; i++)
                tSummary += oSummary[i].innerHTML;
            newWindow = window.open('', '', sFeatures);
            var oSummaryDoc = newWindow.document.open("text/html", "replace");
            newWindow.creatorWindow = self;
            var sContent = "&lt;html&gt;&lt;head&gt;";
            sContent += "&lt;meta http-equiv='Content-Type' content='text/html' charset='UTF-8'&gt;";
            sContent += "&lt;link href='../style/test_report_common_style.css' rel='stylesheet' type='text/css'&gt;";
            sContent += "&lt;script src='../script/test_report_activex_wrapper_script.js' type='text/javascript'&gt;&lt;/script&gt;";
            sContent += "&lt;script src='../script/test_report_common_script.js' type='text/javascript'&gt;&lt;/script&gt;";
            sContent += "&lt;/head&gt;&lt;body onload='defineGlobals();'&gt;&lt;div align='center'&gt;" + tSummary + "&lt;div&gt;&lt;/body&gt;&lt;/html&gt;";
            oSummaryDoc.write(sContent);
            oSummaryDoc.close();
        }

        /*
        */
        function openTraceWindow(tTraceData) {
            var newWindow = window.open('', '', 'toolbar=no, scrollbars=yes, resizable=yes');
            var oSummaryDoc = newWindow.document.open("text/html", "replace");
            var sContent = "&lt;html&gt;&lt;head&gt;";

            sContent += "&lt;meta http-equiv='Content-Type' content='text/html' charset='UTF-8'&gt;";
            sContent += "&lt;link href='../style/test_report_common_style.css' rel='stylesheet' type='text/css'&gt;";
            sContent += "&lt;script src='../script/test_report_common_script.js' type='text/javascript'&gt;&lt;/script&gt;";
            sContent += "&lt;/head&gt;&lt;body class='xmlDefaultClass' style='border: none' onload='defineGlobals();'&gt;" + tTraceData + "&lt;/body&gt;&lt;/html&gt;";
            oSummaryDoc.write(sContent);
            oSummaryDoc.close();
        }

        /*
        */
        function remoteOpen(sId, sResult) {
            var selectionType;

            switch (sResult) {
                case 'No Result':
                    selectionType = 'error'
                    break;
                case 'Failed in setUp':
                case 'Failed in tearDown':
                case 'Remote failed':
                    selectionType = 'failed'
                    break;
                default:
                    selectionType = sResult.toLowerCase()
                    break;
            }
            var oSelection = document.forms[selectionType].elements[0];
            selectFromList(oSelection, sId);
            openDocument(oSelection, selectionType);
        }

        /*
        */
        function checkTraceData() {
            for(var phone in oTraceArray) {
                if (!oTraceArray[phone]['status']) {
                    try {
                        var oTraceDocument = new documentModelConstructor();
                        var traceXMLPath = '../traces/' + escape('art2_traces_' + phone + '.xml');
                        var result = oTraceDocument.loadDocuments(traceXMLPath, '../xslt/test_report_xml_highlight.xslt', true);
                    } catch(er) {
                        var result = false;
                    } finally {
                        if (result) {
                            var oElement = getLayerHandle('art2-' + phone + '-trace');
                            oElement.style.display = 'block';
                            oTraceArray[phone]['object'] = oTraceDocument;
                        }
                        oTraceArray[phone]['status'] = true;
                    }
                } else if (oTraceArray[phone]['object'] != null) {
                    var oElement = getLayerHandle('art2-' + phone + '-trace');
                    oElement.style.display = 'block';
                }
            }
        }

        /*
        */
        function getTraceDataExt(phone) {
            if (oTraceArray[phone]['object'] != null) {
                var tTransformed = oTraceArray[phone]['object'].xsltTransformer(null, null);
                if (tTransformed)
                    openTraceWindow(tTransformed);
            }
        }
        /*
        */
        function hideTraceDataExt() {
            for(var phone in oTraceArray) {
                var oElement = getLayerHandle('art2-' + phone + '-trace');
                if (oElement.style.display == 'block')
                    oElement.style.display = 'none';
            }
        }
        </xsl:comment>
    </xsl:template>

    <xsl:template name="activex-wrapper-script">
        <xsl:comment>
        /*
        */
        function fileSystemConstructor() {
        <xsl:choose>
            <xsl:when test="$framed-mode">
            var rExpAbsPath = /(\w:[\\\/].*)[\\\/]html.*$/;
            </xsl:when>
            <xsl:otherwise>
                <xsl:choose>
                    <xsl:when test="$email-testcase">
            var rExpAbsPath = /(\w:[\\\/].*)[\\\/].*$/;
                    </xsl:when>
                    <xsl:otherwise>
            var rExpAbsPath = /(\w:[\\\/].*)[\\\/]xml.*$/;
                    </xsl:otherwise>
                </xsl:choose>
            </xsl:otherwise>
        </xsl:choose>
            this.rootFolder = unescape(window.location.pathname).match(rExpAbsPath)[1]
            // For IE based browsers.
            if (window.ActiveXObject) {
                // Create 'Scripting.FileSystemObject' activeX object.
                try {
                    this.fso = new ActiveXObject('Scripting.FileSystemObject');
                } catch(er) {
                    this.fso = null;
                }
                // Create 'Outlook.Application' activeX object.
                try {
                    this.outLook = new ActiveXObject("Outlook.Application");
                } catch(er) {
                    this.outLook = null;
                }
                // Create 'Wscript.Shell' activeX object.
                try {
                    this.shell = new ActiveXObject("Wscript.Shell");
                } catch(er) {
                    this.shell = null;
                }
            }
            // For Mozilla based (standards compliant) browsers.
            else if (document.implementation &amp;&amp; document.implementation.createDocument) {
                this.fso = this.outLook = this.shell = null;
            }
            // Other browsers.
            else {
                this.fso = this.outLook = this.shell = null;
            }
            // Assign methods according to found activeX objects.
            this.saveDocument = (this.fso) ? saveDocument : showAlert;
            this.sendEmail = (this.fso &amp;&amp; this.outLook) ? sendEmail : showAlert;
            this.moveObjects = (this.fso) ? moveObjects : showAlert;
            this.getPngObjects = (this.fso) ? getPngObjects : showAlert;
            this.getPngPaths = (this.fso) ? getPngPaths : showAlert;
            this.invokeEditor = (this.fso &amp;&amp; this.shell) ? invokeEditor : showAlert;
            this.updateReference = (this.fso) ? updateReference : showAlert;
            this.rejectReference = (this.fso) ? rejectReference : showAlert;
        }

        /*
        */
        function showAlert() {
            alert("This functionality is NOT supported in this browser!!!")
        }

        /*
        */
        function invokeEditor(line, editor_param) {
            try {
                var results, path, line_nbr, exec_name, title_txt;

                results = line.match(rExpTraceBack);
                path = results[1].replace(rExpTraceBack2, '\\');
                line_nbr = results[2];

                results = editor_param.match(rExpTraceBack3);
                exec_name = results[1] + ' ';
                title_txt = results[2];

                if(this.fso.FileExists(path)) {
                    if(this.shell.AppActivate(title_txt)) {
                        this.shell.SendKeys("^o");
                        this.shell.SendKeys(path);
                        this.shell.SendKeys("{ENTER}");
                        this.shell.SendKeys("^g");
                        this.shell.SendKeys(line_nbr);
                        this.shell.SendKeys("{ENTER}");
                    } else {
                        this.shell.Run(exec_name + path, 9, false);
                    }
                } else {
                    alert("File doesn't exist!");
                }
            } catch(er) {
                alert(er);
            }
        }

        /*
        */
        function updateReference(toggler, error_bm_path, ref_bm_path, elem_id, dbFolder) {
        <xsl:choose>
            <xsl:when test="$framed-mode">
            var styleSwitch = parent.frames['main_frame'].styleSwitch;
            var oImagesInfo = parent.frames['main_frame'].getLayerHandle(elem_id + "-info");
            </xsl:when>
            <xsl:otherwise>
            var oImagesInfo = getLayerHandle(elem_id + "-info");
            </xsl:otherwise>
        </xsl:choose>
            if (!oImagesInfo) return;
            var oImagesInfoText = oImagesInfo.getElementsByTagName("div");
            var index, pathSplit, ref_file_name;

            var refPath = this.fso.BuildPath(this.rootFolder, ref_bm_path);
            var errPath = this.fso.BuildPath(this.rootFolder, error_bm_path);

            try {
                if (this.fso.FileExists(refPath)) {
                    this.fso.DeleteFile(refPath, true);
                    pathSplit = ref_bm_path.split("/");
                } else {
                    pathSplit = error_bm_path.replace('error bitmaps', 'reference bitmaps').split("/")
                }

                ref_file_name = pathSplit.pop();
                var refFolder = this.rootFolder;
                var dbPath = dbFolder;

                for(var i=0; i&lt;pathSplit.length; i++) {
                    refFolder = this.fso.BuildPath(refFolder, pathSplit[i]);
                    if (!this.fso.FolderExists(refFolder))
                        this.fso.CreateFolder(refFolder);
                    dbPath = this.fso.BuildPath(dbPath, pathSplit[i]);
                    if (!this.fso.FolderExists(dbPath))
                        this.fso.CreateFolder(dbPath);
                    }

                if (this.fso.FileExists(dbPath))
                    this.fso.DeleteFile(dbPath, true);
                this.fso.CopyFile(errPath, dbPath + '\\');

                this.fso.CopyFile(errPath, refFolder + '\\');
        <xsl:choose>
            <xsl:when test="$framed-mode">
                var oReference = parent.frames['main_frame'].getLayerHandle(elem_id + "-reference");
            </xsl:when>
            <xsl:otherwise>
                var oReference = getLayerHandle(elem_id + "-reference");
            </xsl:otherwise>
        </xsl:choose>
                if (!oReference) return;
                var oReferenceDivs = oReference.getElementsByTagName("div");
                var oReferenceBitmap = oReferenceDivs[0];

                index = 0;
                while(!/bitmap/i.test(oReferenceBitmap.className)) {
                    index += 1;
                    oReferenceBitmap = oReferenceDivs[index];
                }

                oReferenceBitmap = oReferenceBitmap.firstChild;
                eval("oReferenceBitmap" + styleSwitch + ".background = oReferenceBitmap" + styleSwitch + ".background");
        <xsl:choose>
            <xsl:when test="$framed-mode">
                var oError = parent.frames['main_frame'].getLayerHandle(elem_id + "-error");
            </xsl:when>
            <xsl:otherwise>
                var oError = getLayerHandle(elem_id + "-error");
            </xsl:otherwise>
        </xsl:choose>
                if (!oError) return;
                var oErrorDivs = oError.getElementsByTagName("div");
                var oErrorBitmap = oErrorDivs[0];

                index = 0;
                while(!/bitmap/i.test(oErrorBitmap.className)) {
                    index += 1;
                    oErrorBitmap = oErrorDivs[index];
                }

                eval("oErrorBitmap" + styleSwitch + ".backgroundColor = '#ccFFcc'");
                eval("oImagesInfo" + styleSwitch + ".display = 'block'");
                eval("oImagesInfoText[0]" + styleSwitch + ".color = 'green'");
                oImagesInfoText[0].innerHTML = 'Bitmap succesfully updated...'
                oImagesInfoText[1].innerHTML = 'CAPTURED: ' + errPath.replace(rExpBackSlash, '/')
                oImagesInfoText[2].innerHTML = 'REFERENCE: ' + refPath.replace(rExpBackSlash, '/')
            }
            catch(er) {
                eval("oImagesInfo" + styleSwitch + ".display = 'block'");
                eval("oImagesInfoText[0]" + styleSwitch + ".color = 'red'");
                oImagesInfoText[0].innerHTML = 'Bitmap NOT succesfully updated !!!'
                oImagesInfoText[1].innerHTML = 'CAPTURED: ' + errPath.replace(rExpBackSlash, '/')
                oImagesInfoText[2].innerHTML = 'REFERENCE: ' + refPath.replace(rExpBackSlash, '/')
            }
        }

        /*
        */
        function rejectReference(toggler, ref_bm_path, elem_id, dbFolder) {
        <xsl:choose>
            <xsl:when test="$framed-mode">
            var styleSwitch = parent.frames['main_frame'].styleSwitch;
            var oImagesInfo = parent.frames['main_frame'].getLayerHandle(elem_id + "-info");
            </xsl:when>
            <xsl:otherwise>
            var oImagesInfo = getLayerHandle(elem_id + "-info");
            </xsl:otherwise>
        </xsl:choose>
            if (!oImagesInfo) return;
            var oImagesInfoText = oImagesInfo.getElementsByTagName("div");
            var index, ref_bm_path;
            var refPath = this.fso.BuildPath(this.rootFolder, ref_bm_path);
            
            try {
        <xsl:choose>
            <xsl:when test="$framed-mode">
                var oError = parent.frames['main_frame'].getLayerHandle(elem_id + "-error");
            </xsl:when>
            <xsl:otherwise>
                var oError = getLayerHandle(elem_id + "-error");
            </xsl:otherwise>
        </xsl:choose>
                if (!oError) return;
        <xsl:choose>
            <xsl:when test="$framed-mode">
                var oReference = parent.frames['main_frame'].getLayerHandle(elem_id + "-reference");
            </xsl:when>
            <xsl:otherwise>
                var oReference = getLayerHandle(elem_id + "-reference");
            </xsl:otherwise>
        </xsl:choose>
                if (!oReference) return;
                var oErrorDivs = oError.getElementsByTagName("div");
                var oReferenceDivs = oReference.getElementsByTagName("div");
                var oErrorBitmap = oErrorDivs[0];
                var oReferenceBitmap = oReferenceDivs[0];

                index = 0;
                while(!/bitmap/i.test(oReferenceBitmap.className)) {
                    index += 1;
                    oReferenceBitmap = oReferenceDivs[index];
                }
                if (this.fso.FileExists(refPath))
                    this.fso.DeleteFile(refPath);
                    
                var dbPath = this.fso.BuildPath(dbFolder, ref_bm_path);                    
                if (this.fso.FileExists(dbPath))
                    this.fso.DeleteFile(dbPath);                
                
                oImagesInfoText[0].innerHTML = 'Rejected(delete) reference bitmap...';

                oReferenceBitmap = oReferenceBitmap.firstChild;
                eval("oReferenceBitmap" + styleSwitch + ".background = oReferenceBitmap" + styleSwitch + ".background");

                oImagesInfoText[2].innerHTML = '';

                index = 0;
                while(!/bitmap/i.test(oErrorBitmap.className)) {
                    index += 1;
                    oErrorBitmap = oErrorDivs[index];
                }

                eval("oErrorBitmap" + styleSwitch + ".backgroundColor = '#FFccCC'");

                eval("oImagesInfo" + styleSwitch + ".display = 'block'");
                eval("oImagesInfoText[0]" + styleSwitch + ".color = 'green'");
            }
            catch(er) {
                eval("oImagesInfo" + styleSwitch + ".display = 'block'");
                eval("oImagesInfoText[0]" + styleSwitch + ".color = 'red'");
                oImagesInfoText[0].innerHTML = 'Reference bitmap NOT succesfully deleted !!!';
            }
        }

        /*
        */
        function moveObjects() {
        <xsl:if test="$framed-mode">
            var styleSwitch = parent.frames['main_frame'].styleSwitch;
        </xsl:if>
            var pngPaths = this.getPngPaths(false).unique();
            for(var i=0; i&lt;pngPaths.length; i++) {
                var absFolder = this.rootFolder;
                var file = this.fso.GetFileName(pngPaths[i]);
                var sourcePath = this.fso.BuildPath(this.rootFolder, file);
                var targetPath = this.fso.BuildPath(this.rootFolder, pngPaths[i]);
                var subFolders = this.fso.GetParentFolderName(pngPaths[i]).split('/');
                if (this.fso.FileExists(sourcePath) &amp;&amp; !this.fso.FileExists(targetPath)) {
                    for(var j=0; j&lt;subFolders.length; j++) {
                        var absFolder = this.fso.BuildPath(absFolder, subFolders[j]);
                        if (!this.fso.FolderExists(absFolder))
                            this.fso.CreateFolder(absFolder);
                    }
                    this.fso.MoveFile(sourcePath, targetPath);
                }
            }

            var oPngs = this.getPngObjects();
            for(var i=0; i&lt;oPngs.length; i++)
                eval("oPngs[" + i + "]" + styleSwitch + ".background = oPngs[" + i + "]" + styleSwitch + ".background");
        }

        /*
        */
        function getPngPaths(absolute) {
            var pngPaths = new Array();

            var oPngs = getPngObjects();
            for(var i=0; i&lt;oPngs.length; i++) {
                relPath = unescape(oPngs[i].style.background.match(rExpImageAbsPath)[1]);
                if (absolute) {
                    pngPaths.push(this.fso.BuildPath(this.rootFolder, relPath));
                } else {
                    pngPaths.push(relPath);
                }
            }
            return pngPaths
        }

        /*
        */
        function getPngObjects() {
            var oPngs = new Array();
        <xsl:choose>
            <xsl:when test="$framed-mode">
            var oPng = parent.frames['main_frame'].document.all("copy-image");
            </xsl:when>
            <xsl:otherwise>
            var oPng = document.all("copy-image");
            </xsl:otherwise>
        </xsl:choose>

            if (oPng) {
                if (oPng.length) {
                    for(var i=0; i&lt;oPng.length; i++) {
                        for(var j=0; j&lt;oPng[i].childNodes.length; j++) {
                            if(oPng[i].childNodes[j].className == 'image')
                                oPngs.push(oPng[i].childNodes[j]);
                        }
                    }
                } else {
                    for(var j=0; j&lt;oPng.childNodes.length; j++) {
                        if(oPng.childNodes[j].className == 'image')
                            oPngs.push(oPng.childNodes[j]);
                    }
                }
            }
            return oPngs
        }

        /*
        */
        function saveDocument(path, oDocument, xml) {
            var oFile = this.fso.CreateTextFile(path, true, true);
            var tDocument = (xml) ? oDocument.xml : oDocument;
            oFile.Write(tDocument);
            oFile.Close();

            return oFile;
        }

        /*
        */
        function sendEmail() {
            var oEmailDocument = new documentModelConstructor();
            var defTempFolder = this.fso.GetSpecialFolder(2)
            var baseName = tSubarea + '-' + tFeature + tPrefix;
            var htmlPathTemp = this.fso.BuildPath(defTempFolder, baseName + '.html');
            oEmailDocument.loadDocuments(defXmlPath, '../xslt/test_report_xml_to_html.xslt', false)
            var transformed = oEmailDocument.xsltTransformer(null, {'transformFlag': 'email-testcase'});
            this.saveDocument(htmlPathTemp, transformed, false);

            var oMail = this.outLook.createitem(0);

            oMail.subject = tTestcase;
            oMail.body = '\n\n';

            var pngPaths = this.getPngPaths(true).unique();
            for(var i=0; i&lt;pngPaths.length; i++) {
                if (this.fso.FileExists(pngPaths[i]))
                    oMail.attachments.add(pngPaths[i]);
            }

            oMail.attachments.add(htmlPathTemp);
            oMail.display();
            oMail.Activate;
        }

        function documentModelConstructor() {
            // For IE based browsers.
            if (window.ActiveXObject) {
                // Create DOM Document object.
                this.oXMLDocument = new ActiveXObject('Msxml2.DOMDocument.4.0');

                // Create and load XSLT stylesheet (must be free threaded).
                this.oFTDocument = new ActiveXObject('MSXML2.FreeThreadedDOMDocument.4.0');

                // Create XSLTemplate object and compile stylesheet into it.
                this.oXSLTemplate = new ActiveXObject('Msxml2.XSLTemplate.4.0');

                // Select XLS transform function.
                this.xsltTransformer = msxmlTransform;
                this.loadDocuments = msxmlLoader;
                this.transformDocument = msxmlTransformer;
            }
            // For Mozilla based (standards compliant) browsers.
            else if (document.implementation &amp;&amp; document.implementation.createDocument) {
                // Create DOM Document object.
                this.oXMLDocument = document.implementation.createDocument('', 'doc', null);

                var oXPath = new XPathEvaluator();

                this.oXMLDocument.selectSingleNode = function (xPath) {
                    var oNode = oXPath.evaluate(xPath, this.documentElement, this.documentElement.namespaceURI, 9, null).singleNodeValue;
                    if (oNode != null) {
                        oNode.text = oNode.firstChild ? oNode.firstChild.nodeValue : "";
                    }
                    return oNode;
                };

                this.oXMLDocument.selectNodes = function (xPath) {
                    var oResult = oXPath.evaluate(xPath, this.documentElement, this.documentElement.namespaceURI, 7, null);
                    var i, oNodes = [];
                    for (i=0; i&lt;oResult.snapshotLength; i++) {
                        oNodes[i] = oResult.snapshotItem(i);
                        oNodes[i].text = oNodes[i].firstChild ? oNodes[i].firstChild.nodeValue : "";
                    }
                    return oNodes;
                };

                this.oXMLDocument.loadXML = function (tDocument) {
                    var oParser = new DOMParser();
                    var oDocument = oParser.parseFromString(tDocument, "text/xml");
                    return oDocument
                }

                // Create and load XSLT stylesheet
                this.oXSLDocument = document.implementation.createDocument('', 'doc', null);

                // Select XLS transform function.
                this.xsltTransformer = geckoTransform;
                this.loadDocuments = geckoLoader;
                this.transformDocument = geckoTransformer;
            }
            this.openTestcase = openTestcase;
        }

        /*
        */
        function openTestcase(transformed) {
            parent.frames['main_frame'].document.open()
            parent.frames['main_frame'].creatorWindow = self;
            parent.frames['main_frame'].document.write(transformed);
            parent.frames['main_frame'].document.close()
        }

        /*
        */
        function msxmlTransform(xPath, transformFlags) {
            var tTransformed = ''
            var myErr;

            // Select node.
            if (xPath) {
                var oNodes = this.oXMLDocument.selectNodes(xPath);
                for(var i=0; i&lt;oNodes.length; i++) {
                    if (oNodes[i].xml != '') {
                        var oXPDocument = new documentModelConstructor();
                        oXPDocument.oXSLTemplate = this.oXSLTemplate;
                        oXPDocument.oXMLDocument.loadXML(oNodes[i].xml);
                        tTransformed += oXPDocument.transformDocument(transformFlags);
                    } else {
                        return "Node " + xPath + " NOT found"
                    }
                }
            } else {
                tTransformed = this.transformDocument(transformFlags);
            }

            // Return tranformation result in textual format.
            return tTransformed
        }

        /*
        */
        function msxmlLoader(xmlPath, xslPath, boolean) {
            // Load the XML file.
            if (xmlPath) {
                this.oXMLDocument.async = false;
                if (!this.oXMLDocument.load(xmlPath)) {
                    return boolean ? false : 'Load of ' + xmlPath + ' failed';
                }
            }
            if (this.oXMLDocument.parseError.errorCode != 0) {
                myErr = this.oXMLDocument.parseError;
                return boolean ? false : 'XML parse error: ' + myErr.reason;
            }

            // Load XSLT document.
            if (xslPath) {
                this.oFTDocument.async = false;
                if (!this.oFTDocument.load(xslPath)) {
                    return boolean ? false : 'Load of ' + xslPath + ' failed';
                }
            }
            if (this.oFTDocument.parseError.errorCode != 0) {
                myErr = this.oFTDocument.parseError;
                return boolean ? false : 'XSLT parse error: ' + myErr.reason;
            }
            this.oXSLTemplate.stylesheet = this.oFTDocument;

            return true;
        }

        /*
        */
        function msxmlTransformer(transformFlags) {
            var oXSLTProcessor;

            // Make XSL transformation.
            oXSLTProcessor = this.oXSLTemplate.createProcessor();
            oXSLTProcessor.input = this.oXMLDocument;
            if (transformFlags) {
                for(var flag in transformFlags) {
                    oXSLTProcessor.addParameter(flag, transformFlags[flag]);
                }
            }
            oXSLTProcessor.transform();

            // Return tranformation result in textual format.
            return oXSLTProcessor.output;
        }

        /*
        */
        function geckoTransform(xPath, transformFlags) {
            var tTransformed = ''
            var oSerializer = new XMLSerializer();

            // Select node.
            if (xPath) {
                var oNodes = this.oXMLDocument.selectNodes(xPath);
                for(var i=0; i&lt;oNodes.length; i++) {
                    var tNode = oSerializer.serializeToString(oNodes[i]);
                    if (tNode != '') {
                        var oXPDocument = new documentModelConstructor();
                        oXPDocument.oXSLDocument = this.oXSLDocument;
                        oXPDocument.oXMLDocument = oXPDocument.oXMLDocument.loadXML(tNode);
                        tTransformed += oXPDocument.transformDocument(transformFlags);
                    } else {
                        return 'Node ' + xPath + ' NOT found';
                    }
                }
            } else {
                tTransformed = this.transformDocument(transformFlags);
            }

            // Return tranformation result in textual format.
            return tTransformed;
        }

        /*
        */
        function geckoLoader(xmlPath, xslPath, boolean) {
            // Load the XML file.
            if (xmlPath) {
                this.oXMLDocument.async = false;
                if (!this.oXMLDocument.load(xmlPath)) {
                    return boolean ? false : 'Load of ' + xmlPath + ' failed';
                }
            }

            // Load XSLT document.
            if (xslPath) {
                this.oXSLDocument.async = false;
                if (!this.oXSLDocument.load(xslPath)) {
                    return boolean ? false : 'Load of ' + xslPath + ' failed';
                }
            }

            return true;
        }

        /*
        */
        function geckoTransformer(transformFlags) {
            var oXSLTProcessor = new XSLTProcessor();

            // Import XSL stylesheet.
            oXSLTProcessor.importStylesheet(this.oXSLDocument);

            if (transformFlags) {
                for(var flag in transformFlags) {
                    // Set XSL transformation parameters.
                    oXSLTProcessor.setParameter(null, flag, transformFlags[flag]);
                }
            }

            // Make XSL transformation.
            var oTransformed = oXSLTProcessor.transformToDocument(this.oXMLDocument);

            // Remove all stylesheets and parameters.
            // Put the processor back into its initial state.
            oXSLTProcessor.reset()

            // Return tranformation result in textual format.
            return oTransformed.documentElement.innerHTML;
        }
        </xsl:comment>
    </xsl:template>

    <xsl:template name="memory-info-wbscript">
        <xsl:text disable-output-escaping="yes">
        Set objFileSys = CreateObject("Scripting.FileSystemObject")
        Set objMemInfoDoc = CreateObject("Msxml2.DOMDocument.4.0")

        Set objRemote = New RegExp
        objRemote.Pattern = "[#]{0,}\d{0,}#REMOTE$"

        If (objFileSys.FolderExists("./memory")) Then
            Set objFolder = objFileSys.GetFolder("./memory")
        Else
            strMessage = "No memory info folder found !"
            Call Wscript.Echo(strMessage)
            MsgBox strMessage, 48, "Memory Info Merge Tool"
            Wscript.Quit(1)
        End If

        strMessage = "Separate MAIN and REMOTE phone memory info ?"
        intButton = MsgBox (strMessage, 35, "Memory Info Merge Tool")
        Select Case intButton
            Case vbCancel
                Wscript.Quit(1)
            Case vbYes
                Set objMainMergeDoc = CreateObject("Msxml2.DOMDocument.4.0")
                Set objRemoteMergeDoc = CreateObject("Msxml2.DOMDocument.4.0")
            Case vbNo
                Set objAllMergeDoc = CreateObject("Msxml2.DOMDocument.4.0")
        End Select

        intMainIndex = 0
        intRemoteIndex = 0
        Call Wscript.Echo("Merging memory info...")
        For Each strFilePath in objFolder.Files
            strBase = objFileSys.GetBaseName(strFilePath)
            blnResult = objRemote.Test(strBase)
            Select Case intButton
                Case vbYes
                    If blnResult Then
                        Call MergeResults(strFilePath, intRemoteIndex, objRemoteMergeDoc)
                    Else
                        Call MergeResults(strFilePath, intMainIndex, objMainMergeDoc)
                    End If
                Case vbNo
                    Call MergeResults(strFilePath, intMainIndex, objAllMergeDoc)
            End Select
        Next

        If intButton = 6 Then
            strMessage = PrintResults(objMainMergeDoc, intMainIndex, "main")
            strMessage = strMessage &amp; PrintResults(objRemoteMergeDoc, intRemoteIndex, "remote")
        Else
            strMessage = PrintResults(objAllMergeDoc, intMainIndex, "all")
        End If

        Call Wscript.Echo(strMessage)
        MsgBox strMessage, 64, "Memory Info Merge Tool"

        Sub MergeResults(strFilePath, intIndex, objMergeDoc)
            strExt = objFileSys.GetExtensionName(strFilePath)
            strFileName = objFileSys.GetFileName(strFilePath)

            If strExt = "xml" Then
                If intIndex = 0 Then
                    objMergeDoc.load("./memory/" &amp; strFileName)
                    objMergeDoc.setProperty "SelectionLanguage", "XPath"
                Else
                    objMemInfoDoc.load("./memory/" &amp; strFileName)
                    objMemInfoDoc.setProperty "SelectionLanguage", "XPath"
                    Set objTests = objMemInfoDoc.selectNodes("//test")
                    Set objMergeRoot = objMergeDoc.selectSingleNode("/memory_report")
                    For Each objTest in objTests
                        objMergeRoot.appendChild(objTest)
                    Next
                End If
                intIndex = intIndex + 1
            Else
                Call Wscript.Echo("Skipping " &amp; strFileName &amp; " !")
            End If
        End Sub

        Function PrintResults(objMergeDoc, intIndex, strPhone)
            If strPhone = "all" Then
                strDebug = ""
            Else
                strDebug = " " &amp; UCase(strPhone) &amp; " phone"
            End If

            strFileName = "memory_info_" &amp; LCase(strPhone) &amp; ".xml"
            If intIndex = 0 Then
                PrintResults = "No" &amp;  strDebug &amp; " memory info files found !" &amp; vbCRLF
                Exit Function
            Else
                objMergeDoc.save strFileName
                PrintResults = CStr(intIndex) &amp; strDebug &amp; " files merged." &amp; vbCRLF &amp; _
                                "File saved to " &amp; strFileName &amp; "." &amp; vbCRLF
            End If
        End function
        </xsl:text>
    </xsl:template>

    <xsl:template name="dump-file-info-wbscript">
        <xsl:text disable-output-escaping="yes">
        Set objShell = CreateObject("WScript.Shell")
        Set objExcel = CreateObject("Excel.Application")
        Set objFileSys = CreateObject("Scripting.FileSystemObject")
        Set objTestCaseDoc = CreateObject("Msxml2.DOMDocument.4.0")
        Set objSubareaDict = CreateObject("Scripting.Dictionary")
        objSubareaDict.CompareMode = 1

        Set objColorsDict = CreateObject("Scripting.Dictionary")
        objColorsDict.add "Passed", 32768
        objColorsDict.add "Expected fail", 32768
        objColorsDict.add "N/A", 16711680
        objColorsDict.add "Failed", 255
        objColorsDict.add "Failed in tearDown", 255
        objColorsDict.add "Failed in setUp", 255
        objColorsDict.add "Remote failed", 255
        objColorsDict.add "No Result", 16711808

        Dim columnArray
        columnArray = Array("A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N")

        Const xlContinuous = 1
        Const xlEdgeTop = 8
        Const xlEdgeBottom = 9
        Const xlEdgeRight = 10
        Const xlDouble = -4119
        Const xlInsideVertical = 11

        objExcel.Visible = False
        objExcel.DisplayAlerts = True
        Set objXlBook = objExcel.Workbooks.Add()
        Set objXFSheet = objXlBook.Worksheets("Sheet1")
        Set objATHSheet = objXlBook.Worksheets("Sheet2")
        objXFSheet.Name = "X-files"
        objATHSheet.Name = "ATH-files"

        Set objPathSeparator = New RegExp
        objPathSeparator.Global = True
        objPathSeparator.Pattern = "\\"

        Set objBracket = New RegExp
        objBracket.Global = True
        objBracket.Pattern = "[()]"

        If (objFileSys.FolderExists("./xml")) Then
            Set objFolder = objFileSys.GetFolder("./xml")
        Else
            strMessage = "No xml folder found !"
            Call Wscript.Echo(strMessage)
            MsgBox strMessage, 48, "Dump File Merge Tool"
            mergeResult = 1
        End If

        Call Wscript.Echo("Merging dump file info...")

        ' Enable error handling
        On Error Resume Next

        ' Merge results
        Call MergeResults(objFolder, strFilePath)
        Call CreateStyleSheet(objXFSheet)
        Call CreateStyleSheet(objATHSheet)

        If Err.number &lt;&gt; 0 Then
            objXlBook.Close False
            Call Wscript.Echo("XLS not saved!")
            Call Wscript.Echo(Err.Description &amp; ": " &amp;  Err.Number)
        Else
            SavePath = objFileSys.BuildPath(objFileSys.GetFolder("."), "dump_file_report.xls")
            SavePath = objPathSeparator.Replace(SavePath, "/")
            objXlBook.Close True, SavePath
            Call Wscript.Echo("File saved to " &amp; SavePath &amp; "...")
        End If

        ' Reset error handling
        On Error Goto 0

        objExcel.Quit()
        If (objFileSys.FileExists(SavePath)) Then
            objShell.Run SavePath
        End If
        Wscript.Quit(1)

        Function MergeResults(objFolder, strFilePath)
            For Each strFilePath in objFolder.Files
                strExt = objFileSys.GetExtensionName(strFilePath)
                strFileName = objFileSys.GetFileName(strFilePath)

                If strExt = "xml" Then
                    objTestCaseDoc.load("./xml/" &amp; strFileName)
                    objTestCaseDoc.setProperty "SelectionLanguage", "XPath"

                    Set objId = objTestCaseDoc.selectSingleNode("//testcase/@id")
                    Set objSubarea = objTestCaseDoc.selectSingleNode("//testcase/@subarea")
                    Set objFeature = objTestCaseDoc.selectSingleNode("//testcase/@feature")

                    If Not objSubareaDict.Exists(objSubarea.text) Then
                        Set objFeatureDict = CreateObject("Scripting.Dictionary")
                        objFeatureDict.CompareMode = 1
                        objSubareaDict.add objSubarea.text, objFeatureDict
                    Else
                        Set objFeatureDict = objSubareaDict.Item(objSubarea.text)
                    End If

                    If Not objFeatureDict.Exists(objFeature.text) Then
                        Set objIdDict = CreateObject("Scripting.Dictionary")
                        objIdDict.CompareMode = 1
                        objFeatureDict.add objFeature.text, objIdDict
                    Else
                        Set objIdDict = objFeatureDict.Item(objFeature.text)
                    End If

                    If Not objIdDict.Exists(objId.text) Then
                        Call ParseDumpFiles(objTestCaseDoc, objId, objIdDict)
                    End If

                Else
                    Call Wscript.Echo("Skipping " &amp; strFileName &amp; " !")
                End If
            Next
        End Function

        Function ParseDumpFiles(objTestCaseDoc, objId, objIdDict)
            Set objResultDict = CreateObject("Scripting.Dictionary")

            Set objResult = objTestCaseDoc.selectSingleNode("//testcase/@result")
            objResultDict.add "Result", objResult.text

            intIdx = 0
            Dim XFArray()
            Set objXFileSet = objTestCaseDoc.selectNodes("//x_file")

            If CInt(objXFileSet.length) Then
                ReDim XFArray(CInt(objXFileSet.length) - 1)
                For Each objXFile in objXFileSet
                    Set objPhone = objXFile.selectSingleNode("../@phone")
                    Set objComment = objXFile.selectSingleNode("../@comment")
                    Set objXFDict = CreateObject("Scripting.Dictionary")
                    objXFDict.add "comment", objBracket.Replace(objComment.text, "")
                    objXFDict.add "phone", objPhone.text
                    For Each objAttr in objXFile.selectNodes("@*")
                        If Not IsNothing(objAttr) Then
                            If Not StrComp(objAttr.text, "", 1) = 0 Then
                                objXFDict.add objAttr.name, objAttr.value
                            Else
                                objXFDict.add objAttr.name, "*"
                            End If
                        Else
                            objXFDict.add objAttr.name, "*"
                        End If
                    Next
                    Set XFArray(intIdx) = objXFDict
                    intIdx = intIdx + 1
                Next
                objResultDict.add "x_files", XFArray
            End If

            intIdx = 0
            Dim ATHArray()
            Set objATHFileSet = objTestCaseDoc.selectNodes("//ath_file")

            If CInt(objATHFileSet.length) Then
                ReDim ATHArray(CInt(objATHFileSet.length) - 1)
                For Each objATHFile in objATHFileSet
                    Set objPhone = objATHFile.selectSingleNode("../@phone")
                    Set objComment = objATHFile.selectSingleNode("../@comment")
                    Set objATHDict = CreateObject("Scripting.Dictionary")
                    objATHDict.add "comment", objBracket.Replace(objComment.text, "")
                    objATHDict.add "phone", objPhone.text
                    For Each objAttr in objATHFile.selectNodes("@*")
                        If Not IsNothing(objAttr) Then
                            If Not StrComp(objAttr.text, "", 1) = 0 Then
                                objATHDict.add objAttr.name, objAttr.value
                            Else
                                objATHDict.add objAttr.name, "*"
                            End If
                        Else
                            objATHDict.add objAttr.name, "*"
                        End If
                    Next
                    Set ATHArray(intIdx) = objATHDict
                    intIdx = intIdx + 1
                Next
                objResultDict.add "ath_files", ATHArray
            End If

            If Not objIdDict.Exists(objId.text) Then
                objIdDict.add objId.text, objResultDict
            Else
                Call Wscript.Echo("Skipping duplicate test case: " &amp; objId.text)
            End If
        End Function

        Function CreateStyleSheet(objSheet)
            Dim MyArray, subarea, feature, testcase, rowIndex, intIdx, tcIndex

            rowIndex = 1
            If objSheet.Name = "X-files" Then
                MyArray = Array("Feature group", "Feature", "Test case", "Result", "Phone", "State", "Reset reason", "Mulder", "Scully")
            ElseIf objSheet.Name = "ATH-files" Then
                MyArray = Array("Feature group", "Feature", "Test case", "Result", "Phone", "State", "Stack (All time high)")
            End If

            strLastCol = columnArray(UBound(MyArray))
            objSheet.Rows(CStr(rowIndex)).Font.Bold = True
            objSheet.Rows(CStr(rowIndex)).Font.Italic = True
            objSheet.Range("A" &amp; CStr(rowIndex) &amp; ":" &amp; strLastCol &amp; CStr(rowIndex)).Value = MyArray
            objSheet.Range("A" &amp; CStr(rowIndex) &amp; ":" &amp; strLastCol &amp; CStr(rowIndex)).Borders(xlEdgeBottom).LineStyle = xlDouble
            rowIndex = rowIndex + 1

            SortDictionary objSubareaDict, 0
            For Each subarea In objSubareaDict.Keys()
                objSheet.Range("A" &amp; CStr(rowIndex)).Value = subarea
                rowIndex = rowIndex + 1
                SortDictionary objSubareaDict.Item(subarea), 0
                For Each feature In objSubareaDict.Item(subarea).Keys()
                    objSheet.Range("B" &amp; CStr(rowIndex)).Value = feature
                    rowIndex = rowIndex + 1
                    SortDictionary objSubareaDict.Item(subarea).Item(feature), 0
                    For Each testcase In objSubareaDict.Item(subarea).Item(feature).Keys()
                        Set resultDict = objSubareaDict.Item(subarea).Item(feature).Item(testcase)
                        strResult = resultDict.Item("Result")
                        objSheet.Range("C" &amp; CStr(rowIndex)).Value = testcase
                        objSheet.Range("D" &amp; CStr(rowIndex) &amp; ":D" &amp; CStr(rowIndex)).Value = strResult
                        If objSheet.Name = "X-files" Then
                            If resultDict.Exists("x_files") Then
                                xfileArray = resultDict.Item("x_files")
                                For intIdx = 0 To UBound(xfileArray)
                                    objSheet.Range("E" &amp; CStr(rowIndex) &amp; ":E" &amp; CStr(rowIndex)).Value = xfileArray(intIdx).Item("phone")
                                    objSheet.Range("F" &amp; CStr(rowIndex) &amp; ":F" &amp; CStr(rowIndex)).Value = xfileArray(intIdx).Item("comment")
                                    objSheet.Range("G" &amp; CStr(rowIndex) &amp; ":G" &amp; CStr(rowIndex)).Value = xfileArray(intIdx).Item("reason")
                                    objSheet.Range("H" &amp; CStr(rowIndex) &amp; ":H" &amp; CStr(rowIndex)).Value = xfileArray(intIdx).Item("mulder")
                                    objSheet.Range("I" &amp; CStr(rowIndex) &amp; ":I" &amp; CStr(rowIndex)).Value = xfileArray(intIdx).Item("scully")
                                    If abs(tcIndex) mod 2 = 0 Then
                                        objSheet.Range("A" &amp; CStr(rowIndex) &amp; ":" &amp; strLastCol &amp; CStr(rowIndex)).Interior.ColorIndex = 15
                                    End If
                                    objSheet.Rows(rowIndex).Font.Color = objColorsDict.Item(strResult)
                                    rowIndex = rowIndex + 1
                                Next
                            Else
                                MyArray = Array("*", "*", "*", "*", "*")
                                objSheet.Range("F" &amp; CStr(rowIndex) &amp; ":" &amp; strLastCol &amp; CStr(rowIndex)).Value = MyArray
                                If abs(tcIndex) mod 2 = 0 Then
                                    objSheet.Range("A" &amp; CStr(rowIndex) &amp; ":" &amp; strLastCol &amp; CStr(rowIndex)).Interior.ColorIndex = 15
                                End If
                                objSheet.Rows(rowIndex).Font.Color = objColorsDict.Item(strResult)
                                rowIndex = rowIndex + 1
                            End If
                        ElseIf objSheet.Name = "ATH-files" Then
                            If resultDict.Exists("ath_files") Then
                                athfileArray = resultDict.Item("ath_files")
                                For intIdx = 0 To UBound(athfileArray)
                                    objSheet.Range("E" &amp; CStr(rowIndex) &amp; ":E" &amp; CStr(rowIndex)).Value = athfileArray(intIdx).Item("phone")
                                    objSheet.Range("F" &amp; CStr(rowIndex) &amp; ":F" &amp; CStr(rowIndex)).Value = athfileArray(intIdx).Item("comment")
                                    objSheet.Range("G" &amp; CStr(rowIndex) &amp; ":G" &amp; CStr(rowIndex)).Value = athfileArray(intIdx).Item("name")
                                    If abs(tcIndex) mod 2 = 0 Then
                                        objSheet.Range("A" &amp; CStr(rowIndex) &amp; ":" &amp; strLastCol &amp; CStr(rowIndex)).Interior.ColorIndex = 15
                                    End If
                                    objSheet.Rows(rowIndex).Font.Color = objColorsDict.Item(strResult)
                                    rowIndex = rowIndex + 1
                                Next
                            Else
                                MyArray = Array("*", "*", "*")
                                objSheet.Range("F" &amp; CStr(rowIndex) &amp; ":" &amp; strLastCol &amp; CStr(rowIndex)).Value = MyArray
                                If abs(tcIndex) mod 2 = 0 Then
                                    objSheet.Range("A" &amp; CStr(rowIndex) &amp; ":" &amp; strLastCol &amp; CStr(rowIndex)).Interior.ColorIndex = 15
                                End If
                                objSheet.Rows(rowIndex).Font.Color = objColorsDict.Item(strResult)
                                rowIndex = rowIndex + 1
                            End If
                        End If
                        tcIndex = tcIndex + 1
                    Next
                    objSheet.Range("A" &amp; CStr(rowIndex) &amp; ":" &amp; strLastCol &amp; CStr(rowIndex)).Borders(xlEdgeTop).LineStyle = xlContinuous
                Next
                objSheet.Range("A" &amp; CStr(rowIndex) &amp; ":" &amp; strLastCol &amp; CStr(rowIndex)).Borders(xlEdgeTop).LineStyle = xlDouble
            Next
            objSheet.Range("A1:" &amp; strLastCol &amp; CStr(rowIndex - 1)).Borders(xlInsideVertical).LineStyle = xlContinuous
            objSheet.Range("A1:" &amp; strLastCol &amp; CStr(rowIndex - 1)).Borders(xlEdgeRight).LineStyle = xlContinuous
            objSheet.Columns("A:" &amp; strLastCol).EntireColumn.AutoFit()
        End Function

        Function IsNothing(Obj)
            If Obj Is Nothing Then
                IsNothing = True
            Else
                IsNothing = False
            End If
        End Function

        ' Sorting of the dictionary:
        Function SortDictionary(objDict, intSort)
            ' declare our variables
            Dim strDict()
            Dim objKey
            Dim strKey, strItem
            Dim X, Y, Z

            ' get the dictionary count
            Z = objDict.Count

            ' we need more than one item to warrant sorting
            If Z &gt; 1 Then
                ' create an array to store dictionary information
                ReDim strDict(Z, 2)

                X = 0
                ' populate the string Array
                For Each key In objDict.Keys()
                    strDict(X, 0)  = CStr(key)
                    If IsObject(objDict(key)) Then
                        Set strDict(X, 1) = objDict(key)
                    Else
                        strDict(X, 1) = objDict(key)
                    End If
                    X = X + 1
                Next

                ' perform a a shell sort of the string array
                For X = 0 To (Z - 2)
                    For Y = X To (Z - 1)
                        If StrComp(strDict(X, intSort), strDict(Y, intSort), 1) &gt; 0 Then
                            strKey  = strDict(X, 0)
                            If IsObject(strDict(X, 1)) Then
                                Set strItem = strDict(X, 1)
                            Else
                                strItem = strDict(X, 1)
                            End if
                            strDict(X, 0)  = strDict(Y, 0)
                            If IsObject(strDict(Y, 1)) Then
                                Set strDict(X, 1) = strDict(Y, 1)
                            Else
                                strDict(X, 1) = strDict(Y, 1)
                            End if
                            strDict(Y, 0)  = strKey
                            If IsObject(strItem) Then
                                Set strDict(Y, 1) = strItem
                            Else
                                strDict(Y, 1) = strItem
                            End If
                        End If
                    Next
                Next

                ' erase the contents of the dictionary object
                objDict.RemoveAll

                ' repopulate the dictionary with the sorted information
                For X = 0 To (Z - 1)
                    objDict.Add strDict(X, 0), strDict(X, 1)
                Next
            End if
        End Function
        </xsl:text>
    </xsl:template>

    <xsl:template name="testcase-array">
        <xsl:comment>
             <!-- Create featureArray. -->
            <xsl:value-of select="'&#10;var featureArray = {&#10;'"/>
             <!-- Iterate through all subareas. -->
            <xsl:for-each select="testset/hierarchy">
                <xsl:sort select="@name" data-type="text" order="ascending"/>
                <!-- Iterate all unique features in this subarea. Select one random case per feature. -->
                <xsl:value-of select="concat('&#9;&quot;', @name, '&quot;: {&#10;')"/>
                 <!-- Iterate through all features in this subarea. -->
                <xsl:for-each select="hierarchy">
                    <xsl:sort select="@name" data-type="text" order="ascending"/>
                    <!-- Iterate through all testresults in this feature. -->
                    <xsl:variable name="failed" select="testcase/testresult/@result = 'Failed'"/>
                    <xsl:variable name="failed-in-teardown" select="testcase/testresult/@result = 'Failed in tearDown'"/>
                    <xsl:variable name="failed-in-setup" select="testcase/testresult/@result = 'Failed in setUp'"/>
                    <xsl:variable name="remote-failed" select="testcase/testresult/@result = 'Remote failed'"/>
                    <xsl:variable name="error" select="testcase/testresult/@result = 'No Result'"/>
                    <xsl:variable name="skipped" select="testcase/testresult/@result = 'N/A'"/>
                    <xsl:choose>
                        <xsl:when test="boolean($failed) or boolean($failed-in-teardown) or boolean($failed-in-setup) or boolean($remote-failed) or boolean($error)">
                            <xsl:choose>
                                <xsl:when test="boolean($skipped)">
                                    <xsl:value-of select="concat('&#9;&#9;&quot;', @name, '&quot;: &quot;both&quot;')"/>
                                </xsl:when>
                                <xsl:otherwise>
                                    <xsl:value-of select="concat('&#9;&#9;&quot;', @name, '&quot;: &quot;failed&quot;')"/>
                                </xsl:otherwise>
                            </xsl:choose>
                        </xsl:when>
                        <xsl:when test="boolean($skipped)">
                            <xsl:value-of select="concat('&#9;&#9;&quot;', @name, '&quot;: &quot;skipped&quot;')"/>
                        </xsl:when>
                        <xsl:otherwise>
                            <xsl:value-of select="concat('&#9;&#9;&quot;', @name, '&quot;: &quot;passed&quot;')"/>
                        </xsl:otherwise>
                    </xsl:choose>
                    <xsl:choose>
                        <xsl:when test="not(position() = last())">
                            <xsl:value-of select="',&#10;'"/>
                        </xsl:when>
                        <xsl:otherwise>
                            <xsl:value-of select="'&#10;'"/>
                        </xsl:otherwise>
                    </xsl:choose>
                </xsl:for-each>
                <xsl:choose>
                    <xsl:when test="not(position() = last())">
                        <xsl:value-of select="'&#9;},&#10;'"/>
                    </xsl:when>
                    <xsl:otherwise>
                        <xsl:value-of select="'&#9;}&#10;'"/>
                    </xsl:otherwise>
                </xsl:choose>
            </xsl:for-each>
            <xsl:value-of select="'};&#10;'"/>

             <!-- Create testcaseArray. -->
            <xsl:value-of select="'&#10;var testcaseArray = {&#10;'"/>
             <!-- Iterate through all subareas. -->
            <xsl:for-each select="testset/hierarchy">
                <xsl:sort select="@name" data-type="text" order="ascending"/>
                <!-- Iterate all unique features in this subarea. Select one random case per feature. -->
                <xsl:value-of select="concat('&#9;&quot;', @name, '&quot;: {&#10;')"/>
                 <!-- Iterate through all features in this subarea. -->
                <xsl:for-each select="hierarchy">
                    <xsl:sort select="@name" data-type="text" order="ascending"/>
                    <xsl:value-of select="concat('&#9;&#9;&quot;', @name, '&quot;: {&#10;')"/>
                    <!-- Iterate through all testresults in this feature. -->
                    <xsl:for-each select="testcase">
                        <xsl:variable name="failed" select="testresult/@result = 'Failed'"/>
                        <xsl:variable name="failed-in-teardown" select="testresult/@result = 'Failed in tearDown'"/>
                        <xsl:variable name="failed-in-setup" select="testresult/@result = 'Failed in setUp'"/>
                        <xsl:variable name="remote-failed" select="testresult/@result = 'Remote failed'"/>
                        <xsl:variable name="error" select="testresult/@result = 'No Result'"/>
                        <xsl:variable name="skipped" select="testresult/@result = 'N/A'"/>
                        <xsl:variable name="result-file" select="translate(art2testscript/art2testresult[position()=last()]/@report_file, '&#92;', '&#47;')"/>
                        <xsl:choose>
                            <xsl:when test="boolean($failed) or boolean($failed-in-teardown) or boolean($failed-in-setup) or boolean($remote-failed) or boolean($error)">
                                <xsl:value-of select="concat('&#9;&#9;&#9;&quot;', @name, '&quot;: new Array(&quot;failed&quot;, &quot;', $result-file, '&quot;)')"/>
                            </xsl:when>
                            <xsl:when test="boolean($skipped)">
                                <xsl:value-of select="concat('&#9;&#9;&#9;&quot;', @name, '&quot;: new Array(&quot;skipped&quot;, &quot;', $result-file, '&quot;)')"/>
                            </xsl:when>
                            <xsl:otherwise>
                                <xsl:value-of select="concat('&#9;&#9;&#9;&quot;', @name, '&quot;: new Array(&quot;passed&quot;, &quot;', $result-file, '&quot;)')"/>
                            </xsl:otherwise>
                        </xsl:choose>
                        <xsl:choose>
                            <xsl:when test="not(position() = last())">
                                <xsl:value-of select="',&#10;'"/>
                            </xsl:when>
                            <xsl:otherwise>
                                <xsl:value-of select="'&#10;'"/>
                            </xsl:otherwise>
                        </xsl:choose>
                    </xsl:for-each>
                    <xsl:choose>
                        <xsl:when test="not(position() = last())">
                            <xsl:value-of select="'&#9;&#9;},&#10;'"/>
                        </xsl:when>
                        <xsl:otherwise>
                            <xsl:value-of select="'&#9;&#9;}&#10;'"/>
                        </xsl:otherwise>
                    </xsl:choose>
                </xsl:for-each>
                <xsl:choose>
                    <xsl:when test="not(position() = last())">
                        <xsl:value-of select="'&#9;},&#10;'"/>
                    </xsl:when>
                    <xsl:otherwise>
                        <xsl:value-of select="'&#9;}&#10;'"/>
                    </xsl:otherwise>
                </xsl:choose>
            </xsl:for-each>
            <xsl:value-of select="'};&#10;'"/>
        </xsl:comment>

    </xsl:template>

</xsl:stylesheet>
