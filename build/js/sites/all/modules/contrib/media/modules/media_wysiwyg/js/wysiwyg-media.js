!function(e){Drupal.media=Drupal.media||{},Drupal.wysiwyg.plugins.media={isNode:function(i){return e(i).is("img[data-media-element]")},invoke:function(t,a,r){if("html"==t.format){var n=new i(r);if(this.isNode(t.node)){var l=Drupal.media.filter.extract_file_info(e(t.node));n.onSelect([l])}else n.prompt(a.global)}},attach:function(e,i,t){return e=Drupal.media.filter.replaceTokenWithPlaceholder(e)},detach:function(e,i,t){return e=Drupal.media.filter.replacePlaceholderWithToken(e)}};var i=function(e){return this.instanceId=e,this};i.prototype={prompt:function(i){Drupal.media.popups.mediaBrowser(e.proxy(this,"onSelect"),i)},onSelect:function(i){this.mediaFile=i[0],Drupal.media.popups.mediaStyleSelector(this.mediaFile,e.proxy(this,"insert"),{})},insert:function(e){var i=Drupal.media.filter.create_element(e.html,{fid:this.mediaFile.fid,view_mode:e.type,attributes:e.options,fields:e.options}),t=Drupal.media.filter.getWysiwygHTML(i);Drupal.wysiwyg.instances[this.instanceId].insert(t)}}}(jQuery);