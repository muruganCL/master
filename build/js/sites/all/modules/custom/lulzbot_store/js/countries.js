!function(e,t){e(document).ready(function(){e("#country-actions").on("select change",function(t){var a=e(t.target),l=a.val(),s=e("table tbody :checkbox:checked");s.each(function(t){var a=e(this),s=a.closest("tr");"enable"==l||"disable"==l?s.find("select.country-status").val("enable"==l?"enabled":"hidden"):"all"===l?(s.find('select.warehouses option[value!="0"]').attr("selected","selected"),s.find('select.warehouses option[value="0"]').attr("selected",!1)):"none"===l&&(s.find('select.warehouses option[value!="0"]').attr("selected",!1),s.find('select.warehouses option[value="0"]').attr("selected","selected"))}),a.val("")}),e("table :checkbox").on("change",function(t){var a=e(t.target),l=a.parent().hasClass("select-all"),s="disable";if(l&&a.is(":checked"))s="enable";else if(!l){var c=e("table :checkbox:checked");c.length>0&&(s="enable")}return"enable"===s?void e("#country-actions").removeAttr("disabled").closest(".form-item").removeClass("form-disabled"):void e("#country-actions").attr("disabled","disabled").closest(".form-item").addClass("form-disabled")})})}(jQuery,Drupal);