!function(e){Drupal.wysiwyg.editor.attach.none=function(t,a,r){if(a.resizable){var i=e("#"+a.field,t).parents(".form-textarea-wrapper:first");i.addClass("resizable"),Drupal.behaviors.textarea&&Drupal.behaviors.textarea.attach(t)}},Drupal.wysiwyg.editor.detach.none=function(t,a,r){if("undefined"!=typeof a&&"serialize"!=r){var i=e("#"+a.field,t).parents(".form-textarea-wrapper:first");i.removeOnce("textarea").removeClass(".resizable-textarea").removeClass("resizable").find(".grippie").remove()}},Drupal.wysiwyg.editor.instance.none={insert:function(e){var t=document.getElementById(this.field);if(document.selection){t.focus();var a=document.selection.createRange();a.text=e}else if(t.selectionStart||"0"==t.selectionStart){var r=t.selectionStart,i=t.selectionEnd;t.value=t.value.substring(0,r)+e+t.value.substring(i,t.value.length)}else t.value+=e},setContent:function(t){e("#"+this.field).val(t)},getContent:function(){return e("#"+this.field).val()}}}(jQuery);