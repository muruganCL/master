!function(t){Drupal.behaviors.contentTypes={attach:function(e){t("fieldset#edit-submission",e).drupalSetSummary(function(e){var i=[];return i.push(Drupal.checkPlain(t("#edit-title-label",e).val())||Drupal.t("Requires a title")),i.join(", ")}),t("fieldset#edit-workflow",e).drupalSetSummary(function(e){var i=[];return t("input[name^='node_options']:checked",e).parent().each(function(){i.push(Drupal.checkPlain(t(this).text()))}),t("#edit-node-options-status",e).is(":checked")||i.unshift(Drupal.t("Not published")),i.join(", ")}),t("fieldset#edit-display",e).drupalSetSummary(function(e){var i=[];return t("input:checked",e).next("label").each(function(){i.push(Drupal.checkPlain(t(this).text()))}),t("#edit-node-submitted",e).is(":checked")||i.unshift(Drupal.t("Don't display post information")),i.join(", ")})}}}(jQuery);