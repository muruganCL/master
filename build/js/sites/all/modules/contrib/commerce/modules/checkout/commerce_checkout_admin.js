!function(e){Drupal.behaviors.paneDrag={attach:function(a,t){if("undefined"!=typeof Drupal.tableDrag&&"undefined"!=typeof Drupal.tableDrag.panes){var r=e("table#panes"),s=Drupal.tableDrag.panes;s.row.prototype.onSwap=function(e){n(r,this)},Drupal.theme.tableDragChangedWarning=function(){return'<div class="messages warning">'+Drupal.theme("tableDragChangedMarker")+" "+Drupal.t("Changes to the checkout panes will not be saved until the <em>Save configuration</em> button is clicked.")+"</div>"},s.onDrop=function(){dragObject=this;var a=e(dragObject.rowObject.element).prev("tr").get(0),t=a.className.replace(/([^ ]+[ ]+)*page-([^ ]+)-message([ ]+[^ ]+)*/,"$2"),r=e("select.checkout-pane-page",dragObject.rowObject.element);if(e(dragObject.rowObject.element).prev("tr").is(".page-message")){var s=e("select.checkout-pane-weight",dragObject.rowObject.element),n=s[0].className.replace(/([^ ]+[ ]+)*checkout-pane-weight-([^ ]+)([ ]+[^ ]+)*/,"$2");r.is(".checkout-pane-page-"+t)||(r.removeClass("checkout-pane-page-"+n).addClass("checkout-pane-page-"+t),s.removeClass("checkout-pane-weight-"+n).addClass("checkout-pane-weight-"+t),r.val(t))}},e("select.checkout-pane-page",a).once("checkout-pane-page",function(){e(this).change(function(a){var t=e(this).parents("tr:first"),o=e(this);s.rowObject=new s.row(t),e("tr.page-message",r).each(function(){e(this).is(".page-"+o[0].value+"-message")&&(e(this).after(t),s.updateFields(t.get(0)),s.rowObject.changed=!0,s.oldRowElement&&e(s.oldRowElement).removeClass("drag-previous"),s.oldRowElement=t.get(0),s.restripeTable(),s.rowObject.markChanged(),s.oldRowElement=t,e(t).addClass("drag-previous"))}),n(r,t),o.get(0).blur()})});var n=function(a,t){e("tr.page-message",a).each(function(){e(this).prev("tr").get(0)==t.element&&("keyboard"!=t.method||"down"==t.direction)&&t.swap("after",this),e(this).next("tr").is(":not(.draggable)")||0==e(this).next("tr").length?e(this).removeClass("page-populated").addClass("page-empty"):e(this).is(".page-empty")&&e(this).removeClass("page-empty").addClass("page-populated")})}}}}}(jQuery);