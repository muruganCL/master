!function(o){Drupal.CTools=Drupal.CTools||{},Drupal.CTools.Stylizer={},Drupal.CTools.Stylizer.addFarbtastic=function(e){function t(o,e,t){if(o=h.RGBToHSL(h.unpack(o)),o[0]+=t[0]-e[0],0==e[1]||0==t[1])o[1]=t[1];else{var s=e[1]/t[1];s>1?o[1]/=s:o[1]=1-(1-o[1])*s}if(0==e[2]||0==t[2])o[2]=t[2];else{var s=e[2]/t[2];s>1?o[2]/=s:o[2]=1-(1-o[2])*s}return h.pack(h.HSLToRGB(o))}function s(e,i,c,r){if(o(e).css({backgroundColor:i,color:h.RGBToHSL(h.unpack(i))[2]>.5?"#000":"#fff"}),e.value&&e.value!=i){if(e.value=i,c){var a=e.i;for(j=a+1;d[j-1]&&!o(d[j-1]).is(".unlocked");++j){var u=t(i,reference[e.key],reference[n[j].key]);s(n[j],u,!1)}for(j=a-1;d[j]&&!o(d[j]).is(".unlocked");--j){var u=t(i,reference[e.key],reference[n[j].key]);s(n[j],u,!1)}}r||l()}}function l(){o("#edit-scheme",r).each(function(){this.selectedIndex=this.options.length-1})}function c(){var e=this;u&&o(u).unbind("keyup",h.updateValue).unbind("keyup",l).parent().removeClass("item-selected"),u=this,h.linkTo(function(o){s(e,o,!0,!1)}),h.setColor(this.value),o(u).keyup(h.updateValue).keyup(l).parent().addClass("item-selected")}if(!o("ctools_stylizer_color_scheme_form .color-form.Stylizer-processed").size()){var r=o(".color-form",e),n=[],a=[],d=[],u=null;o(r).prepend('<div id="placeholder"></div>').addClass("color-processed");var h=o.farbtastic("#placeholder");o("#edit-scheme",r).change(function(){var o=this.options[this.selectedIndex].value;if(""!=o){o=o.split(",");for(i in o)s(n[i],o[i],!1,!0)}}),o("#palette input.form-text",r).each(function(){this.key=this.id.substring(13),h.linkTo(function(){}).setColor("#000").linkTo(this);var e=n.length;if(n.length){var t=o('<div class="lock"></div>').toggle(function(){o(this).addClass("unlocked"),o(a[e-1]).attr("class",d[e-2]&&o(d[e-2]).is(":not(.unlocked)")?"hook up":"hook"),o(a[e]).attr("class",d[e]&&o(d[e]).is(":not(.unlocked)")?"hook down":"hook")},function(){o(this).removeClass("unlocked"),o(a[e-1]).attr("class",d[e-2]&&o(d[e-2]).is(":not(.unlocked)")?"hook both":"hook down"),o(a[e]).attr("class",d[e]&&o(d[e]).is(":not(.unlocked)")?"hook both":"hook up")});o(this).after(t),d.push(t)}var s=o(this),i=o('<div class="hook"></div>');s.after(i),a.push(i),s.parent().find(".lock").click(),this.i=e,n.push(this)}).focus(c),o("#palette label",r),c.call(n[0])}},Drupal.behaviors.CToolsColorSettings={attach:function(){o(".ctools-stylizer-color-edit:not(.ctools-color-processed)").addClass("ctools-color-processed").each(function(){Drupal.CTools.Stylizer.addFarbtastic("#"+o(this).attr("id"))}),o("div.form-item div.ctools-style-icon:not(.ctools-color-processed)").addClass("ctools-color-processed").click(function(){$widget=o("input",o(this).parent()),$widget.attr("checked",!$widget.attr("checked")||$widget.is("input[type=radio]"))})}}}(jQuery);