!function(e){Drupal.behaviors.nodeFieldsetSummaries={attach:function(t){e("fieldset.node-form-revision-information",t).drupalSetSummary(function(t){var n=e(".form-item-revision input",t);return n.is(":checked")||!n.length&&e(".form-item-log textarea",t).length?Drupal.t("New revision"):Drupal.t("No revision")}),e("fieldset.node-form-author",t).drupalSetSummary(function(t){var n=e(".form-item-name input",t).val()||Drupal.settings.anonymous,r=e(".form-item-date input",t).val();return r?Drupal.t("By @name on @date",{"@name":n,"@date":r}):Drupal.t("By @name",{"@name":n})}),e("fieldset.node-form-options",t).drupalSetSummary(function(t){var n=[];return e("input:checked",t).parent().each(function(){n.push(Drupal.checkPlain(e.trim(e(this).text())))}),e(".form-item-status input",t).is(":checked")||n.unshift(Drupal.t("Not published")),n.join(", ")})}}}(jQuery);