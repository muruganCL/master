!function(e){Drupal.behaviors.ViewsAjaxView={},Drupal.behaviors.ViewsAjaxView.attach=function(){Drupal.settings&&Drupal.settings.views&&Drupal.settings.views.ajaxViews&&e.each(Drupal.settings.views.ajaxViews,function(e,t){Drupal.views.instances[e]=new Drupal.views.ajaxView(t)})},Drupal.views={},Drupal.views.instances={},Drupal.views.ajaxView=function(t){var i=".view-dom-id-"+t.view_dom_id;this.$view=e(i);var s=Drupal.settings.views.ajax_path;-1!=s.constructor.toString().indexOf("Array")&&(s=s[0]);var a=window.location.search||"";if(""!==a){var a=a.slice(1).replace(/q=[^&]+&?|&?render=[^&]+/,"");""!==a&&(a=(/\?/.test(s)?"&":"?")+a)}this.element_settings={url:s+a,submit:t,setClick:!0,event:"click",selector:i,progress:{type:"throbber"}},this.settings=t,this.$exposed_form=e("#views-exposed-form-"+t.view_name.replace(/_/g,"-")+"-"+t.view_display_id.replace(/_/g,"-")),this.$exposed_form.once(jQuery.proxy(this.attachExposedFormAjax,this)),this.$view.filter(jQuery.proxy(this.filterNestedViews,this)).once(jQuery.proxy(this.attachPagerAjax,this));var r=this.element_settings;r.event="RefreshView",this.refreshViewAjax=new Drupal.ajax(this.selector,this.$view,r)},Drupal.views.ajaxView.prototype.attachExposedFormAjax=function(){var t=e("input[type=submit], button[type=submit], input[type=image]",this.$exposed_form);t=t[0],this.exposedFormAjax=new Drupal.ajax(e(t).attr("id"),t,this.element_settings)},Drupal.views.ajaxView.prototype.filterNestedViews=function(){return!this.$view.parents(".view").size()},Drupal.views.ajaxView.prototype.attachPagerAjax=function(){this.$view.find("ul.pager > li > a, th.views-field a, .attachment .views-summary a").each(jQuery.proxy(this.attachPagerLinkAjax,this))},Drupal.views.ajaxView.prototype.attachPagerLinkAjax=function(t,i){var s=e(i),a={},r=s.attr("href");e.extend(a,this.settings,Drupal.Views.parseQueryString(r),Drupal.Views.parseViewArgs(r,this.settings.view_base_path)),e.extend(a,Drupal.Views.parseViewArgs(r,this.settings.view_base_path)),this.element_settings.submit=a,this.pagerAjax=new Drupal.ajax(!1,s,this.element_settings)},Drupal.ajax.prototype.commands.viewsScrollTop=function(t,i,s){for(var a=e(i.selector).offset(),r=i.selector;0==e(r).scrollTop()&&e(r).parent();)r=e(r).parent();a.top-10<e(r).scrollTop()&&e(r).animate({scrollTop:a.top-10},500)}}(jQuery);