!function(e){Drupal.behaviors.redirectAdmin={attach:function(t){e("table.redirect-list-tableselect tbody input:checkbox").bind("change",function(t){var i=e("table.redirect-list-tableselect input:checkbox:checked").length;i?e("fieldset.redirect-list-operations").slideDown():e("fieldset.redirect-list-operations").slideUp()}),e("table.redirect-list-tableselect th.select-all input:checkbox").bind("change",function(t){var i=e(this,t).attr("checked");i?e("fieldset.redirect-list-operations").slideDown():e("fieldset.redirect-list-operations").slideUp()}),e("fieldset.redirect-list-operations").hide()}}}(jQuery);