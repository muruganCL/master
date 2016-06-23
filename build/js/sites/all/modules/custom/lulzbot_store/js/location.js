var userLocation={selectors:{},availability:{},initialized:!1,setLocation:!1,state:null,log:function(){"undefined"!=typeof console&&"undefined"!=typeof console.log&&"undefined"!=typeof console.log.apply&&console.log.apply(console,arguments)},changeLocation:function(t){t.preventDefault();var e=userLocation;return e.setStateNeedLocation(),e.setLocation=!1,!1},updateAllSelects:function(t){var e=jQuery(this).val(),o=!1;userLocation.isValidCountrySelected(e)||(o=!0),userLocation.selectors.checkAvailabilityButton.attr("disabled",o),userLocation.selectors.countrySelection.val(e)},isValidCountrySelected:function(t){return t||(t=userLocation.selectors.countrySelection.val()),/^[A-Z]+/.test(t)},checkAvailability:function(t){t.preventDefault();var e=userLocation;if(!e.isValidCountrySelected())return void e.selectors.countrySelection.addClass("error");e.selectors.countrySelection.removeClass("error");var o=e.selectors.countrySelection.val();e.selectors.userLocation.find("span").data("country",o).text(Drupal.t("Viewing availability for ")+e.selectors.countrySelection.first().find("option:selected").text()),jQuery("#add-to-cart-user-location").val(o),e.selectors.checkAvailabilityButton.text(Drupal.t("Checking availability"));var a=jQuery(t.target).closest("form").find('input[name="product_id"],select[name="product_id"]').val();jQuery.ajax({url:"/ajax/store/location",data:{location:o,product_id:a},type:"GET"}).always(function(t){userLocation.selectors.checkAvailabilityButton.text(Drupal.t("Check availability"));var a="disabled",i="Unavailable";if(t.is_available&&(a=!1,i="Add to Cart"),jQuery("form.commerce-add-to-cart").removeClass("disabled").removeClass("in-stock").addClass("unavailable"),jQuery('form.commerce-add-to-cart input[type="submit"]').removeClass("form-button-disabled").attr("disabled",a).val(Drupal.t(i)).show(),e.setStateHaveLocation(),Drupal.settings.hasOwnProperty("filamentSkuColorMap")&&t.hasOwnProperty("related_availability")){var n=[];for(var l in t.related_availability)t.related_availability.hasOwnProperty(l)&&t.related_availability[l]&&t.related_availability[l].hasOwnProperty(o)&&t.related_availability[l][o]>0&&n.push(l);var r=[];for(var s in Drupal.settings.filamentSkuColorMap)if(Drupal.settings.filamentSkuColorMap.hasOwnProperty(s))for(var c=0;c<Drupal.settings.filamentSkuColorMap[s].length;c++)-1!=n.indexOf(Drupal.settings.filamentSkuColorMap[s][c])&&r.push(parseInt(s,10));jQuery(".link--filament-color").each(function(){var t=jQuery(this),e=t.closest("li");-1!=r.indexOf(parseInt(t.data("color"),10))?e.removeClass("unavailable"):e.addClass("unavailable")})}}),Drupal.settings.lulzbot_store.location=o,e.setLocation=!0},hideAddToCartButton:function(){var t="form.commerce-add-to-cart input[type=submit]";jQuery(t).show(),0!==arguments.length&&arguments[0]||(t="form.commerce-add-to-cart.disabled input[type=submit]"),jQuery(t).hide()},init:function(){var t=userLocation;t.initSelectors(),t.setStateHaveLocation();var e=Drupal.settings.hasOwnProperty("lulzbot_store"),o=e&&Drupal.settings.lulzbot_store.hasOwnProperty("location")&&Drupal.settings.lulzbot_store.location;e&&!o&&(t.setStateNeedLocation(),userLocation.selectors.checkAvailabilityButton.attr("disabled",!0)),t.hideAddToCartButton(),jQuery("body").on("change",".form-item-countries select",t.updateAllSelects).off("click","#lulzbot-store-check-availability").on("click","#lulzbot-store-check-availability",t.checkAvailability).off("click","a.link--change-location").on("click","a.link--change-location",t.changeLocation).off("click",".notify-btn").on("click",".notify-btn",t.showModal).off("click","#lulzbot-store-notify-me").on("click","#lulzbot-store-notify-me",t.notify),t.initialized=!0},initSelectors:function(){userLocation.selectors={userLocation:jQuery(".location"),checkAvailabilityButton:jQuery(".button--check-availability"),changeLocationLink:jQuery("a.link--change-location"),countrySelect:jQuery(".country-selection"),countrySelection:jQuery(".form-item-countries select"),notify:jQuery(".form-item-notify-me :input"),notifyButton:jQuery("#lulzbot-store-notify-me"),notifyDescription:jQuery(".notify-me .form-item-description")}},showModal:function(){swal.setDefaults({confirmButtonColor:"#c1d640"});var t={title:"E-mail Notification",text:Drupal.t("Enter your email address to receive an email when this product becomes available."),allowOutsideClick:!0,type:"input",inputType:"email",inputPlaceholder:"email@example.com",confirmButtonText:"Notify Me",showCancelButton:!0,closeOnConfirm:!1,showLoaderOnConfirm:!0,animation:"slide-from-top"};userLocation.selectors.notify.val()&&(t.inputValue=userLocation.selectors.notify.val()),swal(t,function(t){return t===!1?!1:""===t?(sweetAlert.showInputError("Please enter your email."),!1):(userLocation.selectors.notify.val(t),void userLocation.notify(t,function(t){sweetAlert(Drupal.t("Thank You"),t)}))})},notify:function(t,e){if(userLocation.selectors.notify.val()){var o=t,a=userLocation.selectors.notify.closest("form"),i=a.find('input[name="notify_token"]').val(),n={notify_me:o,form_token:i,product_id:parseInt(a.find('input[name="product_id"],select[name="product_id"]').val(),10)};jQuery.ajax({type:"POST",url:"/ajax/store/notify",data:n}).done(function(t){userLocation.log("done"),jQuery('<div class="message">'+Drupal.t("You will be notified when this product becomes available.")+"</div>").insertAfter("fieldset.notify-me"),e(Drupal.t("You will be notified when this product becomes available.")),jQuery("fieldset.notify-me").hide(),jQuery(".notify-btn").hide()}).fail(function(){userLocation.log("fail"),jQuery("fieldset.notify-me").prepend('<div class="message error">Could not add notification right now. Please try again later.</div>'),e(Drupal.t("Could not add notification right now. Please try again later."))})}},setStateHaveLocation:function(){var t=userLocation;t.log("setStateHaveLocation"),t.selectors.countrySelect.hide(),t.selectors.checkAvailabilityButton.hide(),t.selectors.userLocation.show(),t.hideAddToCartButton(),t.selectors.checkAvailabilityButton.attr("disabled","disabled"),t.state="have_location"},setStateNeedLocation:function(){var t=userLocation;t.log("setStateNeedLocation"),t.selectors.userLocation.hide(),t.hideAddToCartButton(!0),t.selectors.countrySelect.show(),t.selectors.checkAvailabilityButton.show(),t.selectors.checkAvailabilityButton.attr("disabled",!1),t.state="need_location"}};Drupal.behaviors.userLocation={attach:function(){userLocation.init()}};