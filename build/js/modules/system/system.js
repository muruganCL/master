!function(e){Drupal.hideEmailAdministratorCheckbox=function(){e("#edit-update-status-module-1").is(":checked")?e(".form-item-update-status-module-2").show():e(".form-item-update-status-module-2").hide(),e("#edit-update-status-module-1").change(function(){e(".form-item-update-status-module-2").toggle()})},Drupal.behaviors.cleanURLsSettingsCheck={attach:function(a,t){if(e("#edit-clean-url").length&&!e("#edit-clean-url.install").once("clean-url").length){var o=t.basePath+"admin/config/search/clean-urls/check";e.ajax({url:location.protocol+"//"+location.host+o,dataType:"json",success:function(){location=t.basePath+"admin/config/search/clean-urls"}})}}},Drupal.cleanURLsInstallCheck=function(){var a=location.protocol+"//"+location.host+Drupal.settings.basePath+"admin/config/search/clean-urls/check";e.ajax({async:!1,url:a,dataType:"json",success:function(){e("#edit-clean-url").attr("value",1)}})},Drupal.behaviors.copyFieldValue={attach:function(a,t){for(var o in t.copyFieldValue)e("#"+o,a).once("copy-field-values").bind("blur",function(){var a=t.copyFieldValue[o];for(var c in a){var n=e("#"+a[c]);""==n.val()&&n.val(this.value)}})}},Drupal.behaviors.dateTime={attach:function(a,t){for(var o in t.dateTime)t.dateTime.hasOwnProperty(o)&&!function(t,o){var c="#edit-"+o,n=c+"-suffix";e("input"+c,a).once("date-time").keyup(function(){var a=e(this),o=t.lookup+(/\?/.test(t.lookup)?"&format=":"?format=")+encodeURIComponent(a.val());e.getJSON(o,function(a){e(n).empty().append(" "+t.text+": <em>"+a+"</em>")})})}(t.dateTime[o],o)}},Drupal.behaviors.pageCache={attach:function(a,t){e("#edit-cache-0",a).change(function(){e("#page-compression-wrapper").hide(),e("#cache-error").hide()}),e("#edit-cache-1",a).change(function(){e("#page-compression-wrapper").show(),e("#cache-error").hide()}),e("#edit-cache-2",a).change(function(){e("#page-compression-wrapper").show(),e("#cache-error").show()})}}}(jQuery);