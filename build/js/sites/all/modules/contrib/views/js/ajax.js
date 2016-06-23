!function(e){Drupal.ajax.prototype.commands.viewsSetForm=function(t,i,a){var s=Drupal.settings.views.ajax.title,r=Drupal.settings.views.ajax.id,o=Drupal.settings.views.ajax.popup;if(e(s).html(i.title),e(r).html(i.output),e(o).dialog("open"),Drupal.attachBehaviors(e(o),t.settings),i.url){var l=e("input[type=submit], button",r);l.click(function(e){this.form.clk=this}),l.mousedown(function(e){this.form.clk=this}),e("form",r).once("views-ajax-submit-processed").each(function(){var t={url:i.url,event:"submit",progress:{type:"throbber"}},a=e(this),s=a.attr("id");Drupal.ajax[s]=new Drupal.ajax(s,this,t),Drupal.ajax[s].form=a})}Drupal.viewsUi.resizeModal()},Drupal.ajax.prototype.commands.viewsDismissForm=function(t,i,a){Drupal.ajax.prototype.commands.viewsSetForm({},{title:"",output:Drupal.settings.views.ajax.defaultForm}),e(Drupal.settings.views.ajax.popup).dialog("close")},Drupal.ajax.prototype.commands.viewsHilite=function(t,i,a){e(".hilited").removeClass("hilited"),e(i.selector).addClass("hilited")},Drupal.ajax.prototype.commands.viewsAddTab=function(t,i,a){var s="#views-tab-"+i.id;e("#views-tabset").viewsAddTab(s,i.title,0),e(s).html(i.body).addClass("views-tab");var r=s.replace("#views-tab-","");e("#preview-display-id").append('<option selected="selected" value="'+r+'">'+i.title+"</option>"),Drupal.attachBehaviors(s);var o=e.viewsUi.tabs.instances[e("#views-tabset").get(0).UI_TABS_UUID];e("#views-tabset").viewsClickTab(o.$tabs.length)},Drupal.ajax.prototype.commands.viewsShowButtons=function(t,i,a){e("div.views-edit-view div.form-actions").removeClass("js-hide"),i.changed&&e("div.views-edit-view div.view-changed.messages").removeClass("js-hide")},Drupal.ajax.prototype.commands.viewsTriggerPreview=function(t,i,a){e("input#edit-displays-live-preview").is(":checked")&&e("#preview-submit").trigger("click")},Drupal.ajax.prototype.commands.viewsReplaceTitle=function(t,i,a){var s=parent.document,r=s.title,o=i.siteName.replace(/[-[\]{}()*+?.,\\^$|#\s]/g,"\\$&"),l=new RegExp(".+ (.) "+o);s.title=r.replace(l,i.title+" $1 "+i.siteName),e("h1.page-title").text(i.title),e("h1#overlay-title").text(i.title)},Drupal.theme.tableDragChangedWarning=function(){return[]},Drupal.behaviors.livePreview={attach:function(t){e("input#edit-displays-live-preview",t).once("views-ajax-processed").click(function(){e(this).is(":checked")&&e("#preview-submit").click()})}},Drupal.behaviors.syncPreviewDisplay={attach:function(t){e("#views-tabset a").once("views-ajax-processed").click(function(){var t=e(this).attr("href"),i=t.substr(11);e("#views-live-preview #preview-display-id").val(i)}).addClass("views-ajax-processed")}},Drupal.behaviors.viewsAjax={collapseReplaced:!1,attach:function(t,i){if(i.views){var a=e(i.views.ajax.popup,t);a.dialog({autoOpen:!1,dialogClass:"views-ui-dialog",modal:!0,position:"center",resizable:!1,width:750});var s={event:"click",progress:{type:"throbber"}};e("a.views-ajax-link",t).once("views-ajax-processed").each(function(){var t=s;e(this).attr("href")&&(t.url=e(this).attr("href"));var i=e(this).attr("id");Drupal.ajax[i]=new Drupal.ajax(i,this,t)}),e("div#views-live-preview a").once("views-ajax-processed").each(function(){if(!e(this).attr("href"))return!0;var t=s;if(t.url=e(this).attr("href"),"admin/structure/views"!=Drupal.Views.getPath(t.url).substring(0,21))return!0;t.wrapper="views-live-preview",t.method="html";var i=e(this).attr("id");Drupal.ajax[i]=new Drupal.ajax(i,this,t)}),e("div#views-live-preview input[type=submit]").once("views-ajax-processed").each(function(t){e(this).click(function(){return this.form.clk=this,!0});var i=s;if(i.url=e(this.form).attr("action"),"admin/structure/views"!=Drupal.Views.getPath(i.url).substring(0,21))return!0;i.wrapper="views-live-preview",i.method="html",i.event="click";var a=e(this).attr("id");Drupal.ajax[a]=new Drupal.ajax(a,this,i)}),!this.collapseReplaced&&Drupal.collapseScrollIntoView&&(this.collapseReplaced=!0,Drupal.collapseScrollIntoView=function(t){for(var i=e(t);i.get(0)!=document&&0!=i.size();i=i.parent())if("scroll"==i.css("overflow")||"auto"==i.css("overflow"))return void(Drupal.viewsUi.resizeModal&&e(".views-ui-dialog").height()<parseInt(.8*e(window).height())&&Drupal.viewsUi.resizeModal("",!0));var a=document.documentElement.clientHeight||document.body.clientHeight||0,s=document.documentElement.scrollTop||document.body.scrollTop||0,r=e(t).offset().top,o=55;r+t.offsetHeight+o>a+s&&(t.offsetHeight>a?window.scrollTo(0,r):window.scrollTo(0,r+t.offsetHeight-a+o))})}}}}(jQuery);