!function(l){Drupal.CTools||(Drupal.CTools={}),Drupal.CTools.Collapsible={state:{},stateLoaded:!1,stateChanged:!1,cookieString:"ctools-collapsible-state=",getState:function(l){return this.stateLoaded||this.loadCookie(),this.state[l]},setState:function(o,s){this.stateLoaded||this.loadCookie(),this.state[o]=s,this.stateChanged||(this.stateChanged=!0,l(window).unload(this.unload))},loadCookie:function(){if(document.cookie.length>0&&(offset=document.cookie.indexOf(this.cookieString),-1!=offset)){offset+=this.cookieString.length;var l=document.cookie.indexOf(";",offset);-1==l&&(l=document.cookie.length);var o=unescape(document.cookie.substring(offset,l));if(""!=o)for(var s=o.split(","),t=0;t<s.length;t++){var e=s[t].split(":");this.state[e[0]]=e[1]}}this.stateLoaded=!0},storeCookie:function(){var l="";for(i in this.state)""!=l&&(l+=","),l+=i+":"+this.state[i];document.cookie=this.cookieString+escape(l)+";path=/"},unload:function(){Drupal.CTools.Collapsible.storeCookie()}},Drupal.CTools.CollapsibleCallbacks=[],Drupal.CTools.CollapsibleCallbacksAfterToggle=[],Drupal.CTools.bindCollapsible=function(){var o=l(this);if(o.hasClass("ctools-no-container")&&o.attr("id"))var s=o,t=l("#"+o.attr("id")+"-content");else var s=o.children(".ctools-collapsible-handle"),t=o.children("div.ctools-collapsible-content");if(t.length){var e=l('<span class="ctools-toggle"></span>');if(s.before(e),o.hasClass("ctools-collapsible-remember")&&o.attr("id")){var a=Drupal.CTools.Collapsible.getState(o.attr("id"));1==a?o.removeClass("ctools-collapsed"):-1==a&&o.addClass("ctools-collapsed")}o.hasClass("ctools-collapsed")&&(e.toggleClass("ctools-toggle-collapsed"),t.hide());var c=function(){if(Drupal.CTools.CollapsibleCallbacksAfterToggle)for(i in Drupal.CTools.CollapsibleCallbacksAfterToggle)Drupal.CTools.CollapsibleCallbacksAfterToggle[i](o,s,t,e)},n=function(){if(Drupal.CTools.CollapsibleCallbacks)for(i in Drupal.CTools.CollapsibleCallbacks)Drupal.CTools.CollapsibleCallbacks[i](o,s,t,e);if(o.is("table")?t.toggle(0,c):t.slideToggle(100,c),o.toggleClass("ctools-collapsed"),e.toggleClass("ctools-toggle-collapsed"),o.hasClass("ctools-collapsible-remember")&&o.attr("id")){var l=e.hasClass("ctools-toggle-collapsed")?-1:1;Drupal.CTools.Collapsible.setState(o.attr("id"),l)}return!1};e.click(n),s.click(n)}},Drupal.behaviors.CToolsCollapsible={attach:function(o){l(".ctools-collapsible-container",o).once("ctools-collapsible",Drupal.CTools.bindCollapsible)}}}(jQuery);