!function(e){Drupal.behaviors.mediaAdmin={attach:function(i){if(e(".tabs.secondary a").once("media-admin").bind("click",function(){return 0!=e(":checkbox:checked",e(".file-entity-admin-file-form")).length?confirm(Drupal.t("If you switch views, you will lose your selection.")):void 0}),e(".media-display-thumbnails").length&&!e(".media-thumbnails-select").length){var a=e('<a href="#">'+Drupal.t("all")+"</a>").click(function(){return e(".media-display-thumbnails",e(this).parents("form")).find(":checkbox").attr("checked",!0).change(),!1}),n=e('<a href="#">'+Drupal.t("none")+"</a>").click(function(){return e(".media-display-thumbnails",e(this).parents("form")).find(":checkbox").attr("checked",!1).change(),!1});e('<div class="media-thumbnails-select" />').append("<strong>"+Drupal.t("Select")+":</strong> ").append(a).append(", ").append(n).prependTo(".media-display-thumbnails"),e(".media-item").bind("click",function(i){if(!e(i.target).is("img, a")){var a=e(this).parent().find(":checkbox");a.is(":checked")?a.attr("checked",!1).change():a.attr("checked",!0).change()}}),e(".media-display-thumbnails :checkbox").each(function(){var i=e(this);i.is(":checked")&&e(i.parents("li").find(".media-item")).addClass("selected"),i.bind("change.media",function(){i.is(":checked")?e(i.parents("li").find(".media-item")).addClass("selected"):e(i.parents("li").find(".media-item")).removeClass("selected")})})}}}}(jQuery);