!function($){$.extend({tablesorter:new function(){function benchmark(t,e){log(t+","+((new Date).getTime()-e.getTime())+"ms")}function log(t){"undefined"!=typeof console&&"undefined"!=typeof console.debug?console.log(t):alert(t)}function buildParserCache(t,e){if(t.config.debug)var r="";var i=t.tBodies[0].rows;if(t.tBodies[0].rows[0])for(var s=[],a=i[0].cells,n=a.length,o=0;n>o;o++){var d=!1;$.metadata&&$(e[o]).metadata()&&$(e[o]).metadata().sorter?d=getParserById($(e[o]).metadata().sorter):t.config.headers[o]&&t.config.headers[o].sorter&&(d=getParserById(t.config.headers[o].sorter)),d||(d=detectParserForColumn(t,a[o])),t.config.debug&&(r+="column:"+o+" parser:"+d.id+"\n"),s.push(d)}return t.config.debug&&log(r),s}function detectParserForColumn(t,e){for(var r=parsers.length,i=1;r>i;i++)if(parsers[i].is($.trim(getElementText(t.config,e)),t,e))return parsers[i];return parsers[0]}function getParserById(t){for(var e=parsers.length,r=0;e>r;r++)if(parsers[r].id.toLowerCase()==t.toLowerCase())return parsers[r];return!1}function buildCache(t){if(t.config.debug)var e=new Date;for(var r=t.tBodies[0]&&t.tBodies[0].rows.length||0,i=t.tBodies[0].rows[0]&&t.tBodies[0].rows[0].cells.length||0,s=t.config.parsers,a={row:[],normalized:[]},n=0;r>n;++n){var o=t.tBodies[0].rows[n],d=[];a.row.push($(o));for(var c=0;i>c;++c)d.push(s[c].format(getElementText(t.config,o.cells[c]),t,o.cells[c]));d.push(n),a.normalized.push(d),d=null}return t.config.debug&&benchmark("Building cache for "+r+" rows:",e),a}function getElementText(t,e){if(!e)return"";var r="";return r="simple"==t.textExtraction?e.childNodes[0]&&e.childNodes[0].hasChildNodes()?e.childNodes[0].innerHTML:e.innerHTML:"function"==typeof t.textExtraction?t.textExtraction(e):$(e).text()}function appendToTable(t,e){if(t.config.debug)var r=new Date;for(var i=e,s=i.row,a=i.normalized,n=a.length,o=a[0].length-1,d=$(t.tBodies[0]),c=[],u=0;n>u;u++)if(c.push(s[a[u][o]]),!t.config.appender)for(var l=s[a[u][o]],f=l.length,h=0;f>h;h++)d[0].appendChild(l[h]);t.config.appender&&t.config.appender(t,c),c=null,t.config.debug&&benchmark("Rebuilt table:",r),applyWidget(t),setTimeout(function(){$(t).trigger("sortEnd")},0)}function buildHeaders(t){if(t.config.debug)var e=new Date;for(var r=($.metadata?!0:!1,[]),i=0;i<t.tHead.rows.length;i++)r[i]=0;return $tableHeaders=$("thead th",t),$tableHeaders.each(function(e){this.count=0,this.column=e,this.order=formatSortingOrder(t.config.sortInitialOrder),(checkHeaderMetadata(this)||checkHeaderOptions(t,e))&&(this.sortDisabled=!0),this.sortDisabled||$(this).addClass(t.config.cssHeader),t.config.headerList[e]=this}),t.config.debug&&(benchmark("Built headers:",e),log($tableHeaders)),$tableHeaders}function checkCellColSpan(t,e,r){for(var i=[],s=t.tHead.rows,a=s[r].cells,n=0;n<a.length;n++){var o=a[n];o.colSpan>1?i=i.concat(checkCellColSpan(t,headerArr,r++)):(1==t.tHead.length||o.rowSpan>1||!s[r+1])&&i.push(o)}return i}function checkHeaderMetadata(t){return $.metadata&&$(t).metadata().sorter===!1?!0:!1}function checkHeaderOptions(t,e){return t.config.headers[e]&&t.config.headers[e].sorter===!1?!0:!1}function applyWidget(t){for(var e=t.config.widgets,r=e.length,i=0;r>i;i++)getWidgetById(e[i]).format(t)}function getWidgetById(t){for(var e=widgets.length,r=0;e>r;r++)if(widgets[r].id.toLowerCase()==t.toLowerCase())return widgets[r]}function formatSortingOrder(t){return"Number"!=typeof t?i="desc"==t.toLowerCase()?1:0:i=1==t?t:0,i}function isValueInArray(t,e){for(var r=e.length,i=0;r>i;i++)if(e[i][0]==t)return!0;return!1}function setHeadersCss(t,e,r,i){e.removeClass(i[0]).removeClass(i[1]);var s=[];e.each(function(t){this.sortDisabled||(s[this.column]=$(this))});for(var a=r.length,n=0;a>n;n++)s[r[n][0]].addClass(i[r[n][1]])}function fixColumnWidth(t,e){var r=t.config;if(r.widthFixed){var i=$("<colgroup>");$("tr:first td",t.tBodies[0]).each(function(){i.append($("<col>").css("width",$(this).width()))}),$(t).prepend(i)}}function updateHeaderSortCount(t,e){for(var r=t.config,i=e.length,s=0;i>s;s++){var a=e[s],n=r.headerList[a[0]];n.count=a[1],n.count++}}function multisort(table,sortList,cache){if(table.config.debug)var sortTime=new Date;for(var dynamicExp="var sortWrapper = function(a,b) {",l=sortList.length,i=0;l>i;i++){var c=sortList[i][0],order=sortList[i][1],s="text"==getCachedSortType(table.config.parsers,c)?0==order?"sortText":"sortTextDesc":0==order?"sortNumeric":"sortNumericDesc",e="e"+i;dynamicExp+="var "+e+" = "+s+"(a["+c+"],b["+c+"]); ",dynamicExp+="if("+e+") { return "+e+"; } ",dynamicExp+="else { "}var orgOrderCol=cache.normalized[0].length-1;dynamicExp+="return a["+orgOrderCol+"]-b["+orgOrderCol+"];";for(var i=0;l>i;i++)dynamicExp+="}; ";return dynamicExp+="return 0; ",dynamicExp+="}; ",eval(dynamicExp),cache.normalized.sort(sortWrapper),table.config.debug&&benchmark("Sorting on "+sortList.toString()+" and dir "+order+" time:",sortTime),cache}function sortText(t,e){return e>t?-1:t>e?1:0}function sortTextDesc(t,e){return t>e?-1:e>t?1:0}function sortNumeric(t,e){return t-e}function sortNumericDesc(t,e){return e-t}function getCachedSortType(t,e){return t[e].type}var parsers=[],widgets=[];this.defaults={cssHeader:"header",cssAsc:"headerSortUp",cssDesc:"headerSortDown",sortInitialOrder:"asc",sortMultiSortKey:"shiftKey",sortForce:null,sortAppend:null,textExtraction:"simple",parsers:{},widgets:[],widgetZebra:{css:["even","odd"]},headers:{},widthFixed:!1,cancelSelection:!0,sortList:[],headerList:[],dateFormat:"us",decimal:".",debug:!1},this.benchmark=benchmark,this.construct=function(t){return this.each(function(){if(this.tHead&&this.tBodies){var e,r,i,s;this.config={},s=$.extend(this.config,$.tablesorter.defaults,t),e=$(this),r=buildHeaders(this),this.config.parsers=buildParserCache(this,r),i=buildCache(this);var a=[s.cssDesc,s.cssAsc];fixColumnWidth(this),r.click(function(t){e.trigger("sortStart");var n=e[0].tBodies[0]&&e[0].tBodies[0].rows.length||0;if(!this.sortDisabled&&n>0){var o=($(this),this.column);if(this.order=this.count++%2,t[s.sortMultiSortKey])if(isValueInArray(o,s.sortList))for(var d=0;d<s.sortList.length;d++){var c=s.sortList[d],u=s.headerList[c[0]];c[0]==o&&(u.count=c[1],u.count++,c[1]=u.count%2)}else s.sortList.push([o,this.order]);else{if(s.sortList=[],null!=s.sortForce)for(var l=s.sortForce,d=0;d<l.length;d++)l[d][0]!=o&&s.sortList.push(l[d]);s.sortList.push([o,this.order])}return setTimeout(function(){setHeadersCss(e[0],r,s.sortList,a),appendToTable(e[0],multisort(e[0],s.sortList,i))},1),!1}}).mousedown(function(){return s.cancelSelection?(this.onselectstart=function(){return!1},!1):void 0}),e.bind("update",function(){this.config.parsers=buildParserCache(this,r),i=buildCache(this)}).bind("sorton",function(t,e){$(this).trigger("sortStart"),s.sortList=e;var n=s.sortList;updateHeaderSortCount(this,n),setHeadersCss(this,r,n,a),appendToTable(this,multisort(this,n,i))}).bind("appendCache",function(){appendToTable(this,i)}).bind("applyWidgetId",function(t,e){getWidgetById(e).format(this)}).bind("applyWidgets",function(){applyWidget(this)}),$.metadata&&$(this).metadata()&&$(this).metadata().sortlist&&(s.sortList=$(this).metadata().sortlist),s.sortList.length>0&&e.trigger("sorton",[s.sortList]),applyWidget(this)}})},this.addParser=function(t){for(var e=parsers.length,r=!0,i=0;e>i;i++)parsers[i].id.toLowerCase()==t.id.toLowerCase()&&(r=!1);r&&parsers.push(t)},this.addWidget=function(t){widgets.push(t)},this.formatFloat=function(t){var e=parseFloat(t);return isNaN(e)?0:e},this.formatInt=function(t){var e=parseInt(t);return isNaN(e)?0:e},this.isDigit=function(t,e){var r="\\"+e.decimal,i="/(^[+]?0("+r+"0+)?$)|(^([-+]?[1-9][0-9]*)$)|(^([-+]?((0?|[1-9][0-9]*)"+r+"(0*[1-9][0-9]*)))$)|(^[-+]?[1-9]+[0-9]*"+r+"0+$)/";return RegExp(i).test($.trim(t))},this.clearTableBody=function(t){function e(){for(;this.firstChild;)this.removeChild(this.firstChild)}$.browser.msie?e.apply(t.tBodies[0]):t.tBodies[0].innerHTML=""}}}),$.fn.extend({tablesorter:$.tablesorter.construct});var ts=$.tablesorter;ts.addParser({id:"text",is:function(t){return!0},format:function(t){return $.trim(t.toLowerCase())},type:"text"}),ts.addParser({id:"digit",is:function(t,e){var r=e.config;return $.tablesorter.isDigit(t,r)},format:function(t){return $.tablesorter.formatFloat(t)},type:"numeric"}),ts.addParser({id:"currency",is:function(t){return/^[£$€?.]/.test(t)},format:function(t){return $.tablesorter.formatFloat(t.replace(new RegExp(/[^0-9.]/g),""))},type:"numeric"}),ts.addParser({id:"ipAddress",is:function(t){return/^\d{2,3}[\.]\d{2,3}[\.]\d{2,3}[\.]\d{2,3}$/.test(t)},format:function(t){for(var e=t.split("."),r="",i=e.length,s=0;i>s;s++){var a=e[s];r+=2==a.length?"0"+a:a}return $.tablesorter.formatFloat(r)},type:"numeric"}),ts.addParser({id:"url",is:function(t){return/^(https?|ftp|file):\/\/$/.test(t)},format:function(t){return jQuery.trim(t.replace(new RegExp(/(https?|ftp|file):\/\//),""))},type:"text"}),ts.addParser({id:"isoDate",is:function(t){return/^\d{4}[\/-]\d{1,2}[\/-]\d{1,2}$/.test(t)},format:function(t){return $.tablesorter.formatFloat(""!=t?new Date(t.replace(new RegExp(/-/g),"/")).getTime():"0")},type:"numeric"}),ts.addParser({id:"percent",is:function(t){return/\%$/.test($.trim(t))},format:function(t){return $.tablesorter.formatFloat(t.replace(new RegExp(/%/g),""))},type:"numeric"}),ts.addParser({id:"usLongDate",is:function(t){return t.match(new RegExp(/^[A-Za-z]{3,10}\.? [0-9]{1,2}, ([0-9]{4}|'?[0-9]{2}) (([0-2]?[0-9]:[0-5][0-9])|([0-1]?[0-9]:[0-5][0-9]\s(AM|PM)))$/))},format:function(t){return $.tablesorter.formatFloat(new Date(t).getTime())},type:"numeric"}),ts.addParser({id:"shortDate",is:function(t){return/\d{1,2}[\/\-]\d{1,2}[\/\-]\d{2,4}/.test(t)},format:function(t,e){var r=e.config;return t=t.replace(/\-/g,"/"),"us"==r.dateFormat?t=t.replace(/(\d{1,2})[\/\-](\d{1,2})[\/\-](\d{4})/,"$3/$1/$2"):"uk"==r.dateFormat?t=t.replace(/(\d{1,2})[\/\-](\d{1,2})[\/\-](\d{4})/,"$3/$2/$1"):("dd/mm/yy"==r.dateFormat||"dd-mm-yy"==r.dateFormat)&&(t=t.replace(/(\d{1,2})[\/\-](\d{1,2})[\/\-](\d{2})/,"$1/$2/$3")),$.tablesorter.formatFloat(new Date(t).getTime())},type:"numeric"}),ts.addParser({id:"time",is:function(t){return/^(([0-2]?[0-9]:[0-5][0-9])|([0-1]?[0-9]:[0-5][0-9]\s(am|pm)))$/.test(t)},format:function(t){return $.tablesorter.formatFloat(new Date("2000/01/01 "+t).getTime())},type:"numeric"}),ts.addParser({id:"metadata",is:function(t){return!1},format:function(t,e,r){var i=e.config,s=i.parserMetadataName?i.parserMetadataName:"sortValue";return $(r).metadata()[s]},type:"numeric"}),ts.addWidget({id:"zebra",format:function(t){if(t.config.debug)var e=new Date;$("tr:visible",t.tBodies[0]).filter(":even").removeClass(t.config.widgetZebra.css[1]).addClass(t.config.widgetZebra.css[0]).end().filter(":odd").removeClass(t.config.widgetZebra.css[0]).addClass(t.config.widgetZebra.css[1]),t.config.debug&&$.tablesorter.benchmark("Applying Zebra widget",e)}})}(jQuery);