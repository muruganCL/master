!function(t){Drupal.behaviors.autocomplete={attach:function(e,i){var s=[];t("input.autocomplete",e).once("autocomplete",function(){var e=this.value;s[e]||(s[e]=new Drupal.ACDB(e));var i=t("#"+this.id.substr(0,this.id.length-13)).attr("autocomplete","OFF").attr("aria-autocomplete","list");t(i[0].form).submit(Drupal.autocompleteSubmit),i.parent().attr("role","application").append(t('<span class="element-invisible" aria-live="assertive"></span>').attr("id",i.attr("id")+"-autocomplete-aria-live")),new Drupal.jsAC(i,s[e])})}},Drupal.autocompleteSubmit=function(){return 0==t("#autocomplete").each(function(){this.owner.hidePopup()}).length},Drupal.jsAC=function(e,i){var s=this;this.input=e[0],this.ariaLive=t("#"+this.input.id+"-autocomplete-aria-live"),this.db=i,e.keydown(function(t){return s.onkeydown(this,t)}).keyup(function(t){s.onkeyup(this,t)}).blur(function(){s.hidePopup(),s.db.cancel()})},Drupal.jsAC.prototype.onkeydown=function(t,e){switch(e||(e=window.event),e.keyCode){case 40:return this.selectDown(),!1;case 38:return this.selectUp(),!1;default:return!0}},Drupal.jsAC.prototype.onkeyup=function(t,e){switch(e||(e=window.event),e.keyCode){case 16:case 17:case 18:case 20:case 33:case 34:case 35:case 36:case 37:case 38:case 39:case 40:return!0;case 9:case 13:case 27:return this.hidePopup(e.keyCode),!0;default:return t.value.length>0&&!t.readOnly?this.populatePopup():this.hidePopup(e.keyCode),!0}},Drupal.jsAC.prototype.select=function(e){this.input.value=t(e).data("autocompleteValue"),t(this.input).trigger("autocompleteSelect",[e])},Drupal.jsAC.prototype.selectDown=function(){if(this.selected&&this.selected.nextSibling)this.highlight(this.selected.nextSibling);else if(this.popup){var e=t("li",this.popup);e.length>0&&this.highlight(e.get(0))}},Drupal.jsAC.prototype.selectUp=function(){this.selected&&this.selected.previousSibling&&this.highlight(this.selected.previousSibling)},Drupal.jsAC.prototype.highlight=function(e){this.selected&&t(this.selected).removeClass("selected"),t(e).addClass("selected"),this.selected=e,t(this.ariaLive).html(t(this.selected).html())},Drupal.jsAC.prototype.unhighlight=function(e){t(e).removeClass("selected"),this.selected=!1,t(this.ariaLive).empty()},Drupal.jsAC.prototype.hidePopup=function(e){this.selected&&(e&&46!=e&&8!=e&&27!=e||!e)&&this.select(this.selected);var i=this.popup;i&&(this.popup=null,t(i).fadeOut("fast",function(){t(i).remove()})),this.selected=!1,t(this.ariaLive).empty()},Drupal.jsAC.prototype.populatePopup=function(){var e=t(this.input),i=e.position();this.popup&&t(this.popup).remove(),this.selected=!1,this.popup=t('<div id="autocomplete"></div>')[0],this.popup.owner=this,t(this.popup).css({top:parseInt(i.top+this.input.offsetHeight,10)+"px",left:parseInt(i.left,10)+"px",width:e.innerWidth()+"px",display:"none"}),e.before(this.popup),this.db.owner=this,this.db.search(this.input.value)},Drupal.jsAC.prototype.found=function(e){if(!this.input.value.length)return!1;var i=t("<ul></ul>"),s=this;for(key in e)t("<li></li>").html(t("<div></div>").html(e[key])).mousedown(function(){s.hidePopup(this)}).mouseover(function(){s.highlight(this)}).mouseout(function(){s.unhighlight(this)}).data("autocompleteValue",key).appendTo(i);this.popup&&(i.children().length?(t(this.popup).empty().append(i).show(),t(this.ariaLive).html(Drupal.t("Autocomplete popup"))):(t(this.popup).css({visibility:"hidden"}),this.hidePopup()))},Drupal.jsAC.prototype.setStatus=function(e){switch(e){case"begin":t(this.input).addClass("throbbing"),t(this.ariaLive).html(Drupal.t("Searching for matches..."));break;case"cancel":case"error":case"found":t(this.input).removeClass("throbbing")}},Drupal.ACDB=function(t){this.uri=t,this.delay=300,this.cache={}},Drupal.ACDB.prototype.search=function(e){var i=this;if(this.searchString=e,e=e.replace(/^\s+|\.{2,}\/|\s+$/g,""),!(e.length<=0||","==e.charAt(e.length-1))){if(this.cache[e])return this.owner.found(this.cache[e]);this.timer&&clearTimeout(this.timer),this.timer=setTimeout(function(){i.owner.setStatus("begin"),t.ajax({type:"GET",url:i.uri+"/"+Drupal.encodePath(e),dataType:"json",success:function(t){("undefined"==typeof t.status||0!=t.status)&&(i.cache[e]=t,i.searchString==e&&i.owner.found(t),i.owner.setStatus("found"))},error:function(t){alert(Drupal.ajaxError(t,i.uri))}})},this.delay)}},Drupal.ACDB.prototype.cancel=function(){this.owner&&this.owner.setStatus("cancel"),this.timer&&clearTimeout(this.timer),this.searchString=""}}(jQuery);