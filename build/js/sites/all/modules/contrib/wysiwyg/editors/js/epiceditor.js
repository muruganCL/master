!function(e){function t(t,n){var r=!1;return t===n?!0:(e(t).parents().each(function(e,t){return t===n?(r=!0,!1):void 0}),r)}function n(e){return e=e.replace(/</g,"&lt;"),e=e.replace(/>/g,"&gt;"),e=e.replace(/\n/g,"<br>"),e=e.replace(/\s\s/g," &nbsp;")}Drupal.wysiwyg.editor.attach.epiceditor=function(t,n,r){var i=e("#"+n.field),a=n.field+"-epiceditor",o=i.val(),c=e('<div id="'+a+'" />');i.hide().after(c),r.height||(r.height=e("#"+n.field).height()),c.height(r.height),r.container=a,r.file={defaultContent:o},r.theme={preview:"/themes/preview/preview-dark.css",editor:"/themes/editor/"+r.theme+".css"};var s=new EpicEditor(r).load();i.data("epiceditor",s)},Drupal.wysiwyg.editor.detach.epiceditor=function(t,n,r){var i=e();if("undefined"!=typeof n)i.push(e("#"+n.field));else{var a=e(".wysiwyg-processed",t);a.each(function(){var t=e(this);t.data("epiceditor")||i.push(t)})}i.each(function(){var t=e(this),n=t.data("epiceditor");t.val(n.exportFile()),"serialize"!==r&&(n.unload(function(){t.show(),e("#"+t.attr("id")+"-epiceditor").remove()}),t.removeData("epiceditor"))})},Drupal.wysiwyg.editor.instance.epiceditor={insert:function(e){var r=this.getInstance(),i=r.getElement("editor").body;if(document.selection){var a=i.selection;range=a.createRange(),t(range.parentElement(),i)?(range.pasteHTML(e),range.select(),range.collapse(!1)):i.innerHTML+=n(e)}else{var a=i.ownerDocument.getSelection();if(a.getRangeAt?a.rangeCount>0&&(range=a.getRangeAt(0)):(range=i.ownerDocument.createRange(),range.setStart(a.anchorNode,a.anchorOffset),range.setEnd(a.focusNode,userSeletion.focusOffset)),0==a.rangeCount||!t(range.commonAncestorContainer,i))return void(i.innerHTML+=n(e));var o=i.ownerDocument.createDocumentFragment(),c=i.ownerDocument.createElement("div");for(c.innerHTML=n(e);c.firstChild;)o.appendChild(c.firstChild);var s=i.ownerDocument.createElement("span");o.appendChild(s),range.deleteContents(),range.insertNode(o),range.setStartBefore(s),range.setEndBefore(s),a.removeAllRanges(),a.addRange(range),s.parentNode.removeChild(s)}},setContent:function(e){this.getInstance().importFile(null,e)},getContent:function(){return this.getInstance().exportFile()},isFullscreen:function(){return this.getInstance().is("fullscreen")},getInstance:function(){return this.editorInstance||(this.editorInstance=e("#"+this.field).data("epiceditor")),this.editorInstance}}}(jQuery);