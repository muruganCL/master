!function(e){function t(t,i){$elem=e(t,i),$elem.attr("checked")?$elem.closest(".form-item",i).addClass("highlight"):$elem.closest(".form-item",i).removeClass("highlight")}function i(e,t,i){var s=parseFloat(e.val(),10),a=e.parents("div.views-widget").next(".bef-slider").slider("values",0),n=e.parents("div.views-widget").next(".bef-slider").slider("values",1);null!=t?(0==t&&s>n&&(s=n),1==t&&a>s&&(s=a),isNaN(s)&&(s=e.parents("div.views-widget").next(".bef-slider").slider("values",t))):isNaN(s)&&(s=e.parents("div.views-widget").next(".bef-slider").slider("value")),s=parseFloat(s,10),null!=t?e.parents("div.views-widget").next(".bef-slider").slider("values",t,s):e.parents("div.views-widget").next(".bef-slider").slider("value",s)}Drupal.behaviors.betterExposedFilters={attach:function(i){e(".bef-tree input[type=checkbox], .bef-checkboxes input[type=checkbox]").change(function(){t(this,i)}).filter(":checked").closest(".form-item",i).addClass("highlight")}},Drupal.behaviors.betterExposedFiltersSelectAllNone={attach:function(i){var s=e(".form-checkboxes.bef-select-all-none:not(.bef-processed)");if(s.length){var a=Drupal.t("Select All"),n=Drupal.t("Select None"),r=e('<a class="bef-toggle" href="#">'+a+"</a>");r.click(function(s){s.preventDefault(),s.stopPropagation(),a==e(this).text()?e(this).html(n).siblings(".bef-checkboxes, .bef-tree").find(".form-item input:checkbox").each(function(){e(this).attr("checked",!0),t(this,i)}).end().find("input[type=checkbox]:first").change():e(this).html(a).siblings(".bef-checkboxes, .bef-tree").find(".form-item input:checkbox").each(function(){e(this).attr("checked",!1),t(this,i)}).end().find("input[type=checkbox]:first").change()}),s.addClass("bef-processed").each(function(t){var i=r.clone(!0);i.insertBefore(e(".bef-checkboxes, .bef-tree",this)),e("input:checkbox:checked",this).length==e("input:checkbox",this).length&&i.click()})}var l=Drupal.settings.better_exposed_filters;if(l&&l.datepicker&&l.datepicker_options&&e.fn.datepicker){var c=[];e.each(l.datepicker_options,function(e,t){e&&t&&(c[e]=JSON.parse(t))}),e(".bef-datepicker").datepicker(c)}}},Drupal.behaviors.betterExposedFiltersAllNoneNested={attach:function(t,i){e(".form-checkboxes.bef-select-all-none-nested li").has("ul").once("bef-all-none-nested",function(){var t=e(this),i=t.parents("form").submit;t.parents("form").submit=null,t.find("input.form-checkboxes:first").click(function(){e(this).parents("li:first").find("ul input.form-checkboxes").attr("checked",e(this).attr("checked")),t.parents("form").submit=i,t.parents("form").trigger("submit")}).end().find("ul input.form-checkboxes").click(function(){var t=e(this).attr("checked"),i=e(this).parents("ul:first").find("input.form-checkboxes:not(:checked)").size();t&&i||e(this).parents("li:first").parents("li:first").find("input.form-checkboxes:first").attr("checked",t)})})}},Drupal.behaviors.better_exposed_filters_slider={attach:function(t,s){var a=s.better_exposed_filters;a&&a.slider&&a.slider_options&&e.each(a.slider_options,function(t,s){var a="#"+s.viewId+" #edit-"+s.id+"-wrapper .views-widget",n=e(a);n.length||(a="#"+s.viewId+" .bef-slider-wrapper",n=e(a)),n.once("slider-filter",function(){var t=e(this).find("input[type=text]");if(2==t.length){var n,r,l=t.parent().find("input#edit-"+s.id+"-min"),c=t.parent().find("input#edit-"+s.id+"-max");if(!l.length||!c.length)return;n=parseFloat(""==l.val()?s.min:l.val(),10),r=parseFloat(""==c.val()?s.max:c.val(),10),l.val(n),c.val(r),l.parents(a).after(e('<div class="bef-slider"></div>').slider({range:!0,min:parseFloat(s.min,10),max:parseFloat(s.max,10),step:parseFloat(s.step,10),animate:s.animate?s.animate:!1,orientation:s.orientation,values:[n,r],slide:function(e,t){l.val(t.values[0]),c.val(t.values[1])},change:function(e,t){l.val(t.values[0]),c.val(t.values[1])},stop:function(t,i){e(this).parents("form").find(".ctools-auto-submit-click").click()}})),l.blur(function(){i(e(this),0,s)}),c.blur(function(){i(e(this),1,s)})}else{if(1!=t.length)return;if(t.attr("id")!="edit-"+s.id)return;var o=parseFloat(""==t.val()?s.min:t.val(),10);t.val(o),t.parents(a).after(e('<div class="bef-slider"></div>').slider({min:parseFloat(s.min,10),max:parseFloat(s.max,10),step:parseFloat(s.step,10),animate:s.animate?s.animate:!1,orientation:s.orientation,value:o,slide:function(e,i){t.val(i.value)},change:function(e,i){t.val(i.value)},stop:function(t,i){e(this).parents("form").find(".ctools-auto-submit-click").click()}})),t.blur(function(){i(e(this),null,s)})}})})}},Drupal.behaviors.better_exposed_filters_select_as_links={attach:function(t,i){e(".bef-select-as-links",t).once(function(){var t=e(this);if("undefined"!=typeof i.views&&"undefined"!=typeof i.views.ajaxViews){var s=!1;e.each(i.views.ajaxViews,function(e,i){var a=i.view_name.replace(/_/g,"-"),n=i.view_display_id.replace(/_/g,"-"),r="views-exposed-form-"+a+"-"+n,l=t.parents("form").attr("id");return l==r?void(s=!0):void 0}),s&&e(this).find("a").click(function(t){var i=e(this).parents(".bef-select-as-links"),s=i.find("select option");t.preventDefault(),t.stopPropagation(),i.find("select option").removeAttr("selected");var a=e(this).text();$selected=s.filter(function(){return e(this).text()==a}),$selected.attr("selected","selected"),i.find(".bef-new-value").val($selected.val()),i.find("a").removeClass("active"),e(this).addClass("active"),i.parents("form").find(".views-submit-button *[type=submit]").click()})}})}},Drupal.behaviors.betterExposedFiltersRequiredFilter={attach:function(t,i){e(".bef-select-as-checkboxes",t).once("bef-required-filter").ajaxComplete(function(t,s,a){var n=e(this);if("undefined"!=typeof i.views&&"undefined"!=typeof i.views.ajaxViews){var r,l,c=!1;e.each(i.views.ajaxViews,function(e,t){r=t.view_name,l=t.view_display_id;var i="views-exposed-form-"+r.replace(/_/g,"-")+"-"+l.replace(/_/g,"-"),s=n.parents("form").attr("id");return s==i?(c=!0,!1):void 0});var o=e("input",this).attr("name").slice(0,-2);Drupal.settings.better_exposed_filters.views[r].displays[l].filters[o].required&&0==e("input:checked",this).length&&e("input",this).prop("checked",!0)}})}}}(jQuery);