!function(i){Drupal.behaviors.inlineEntityForm={attach:function(n){Drupal.file&&i("input.ief-entity-submit",n).unbind("mousedown",Drupal.file.disableFields)},detach:function(n){Drupal.file&&i("input.form-submit",n).bind("mousedown",Drupal.file.disableFields)}}}(jQuery);