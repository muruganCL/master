!function(e){Drupal.behaviors.commentFieldsetSummaries={attach:function(t){e("fieldset.comment-node-settings-form",t).drupalSetSummary(function(t){return Drupal.checkPlain(e(".form-item-comment input:checked",t).next("label").text())}),e("fieldset.comment-node-type-settings-form",t).drupalSetSummary(function(t){var m=[];m.push(e(".form-item-comment select option:selected",t).text());var n=e(".form-item-comment-default-mode input:checked",t).next("label").text();n&&m.push(n);var r=e(".form-item-comment-default-per-page select option:selected",t).val();return m.push(Drupal.t("@number comments per page",{"@number":r})),Drupal.checkPlain(m.join(", "))})}}}(jQuery);