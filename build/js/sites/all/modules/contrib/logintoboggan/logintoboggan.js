!function(g){Drupal.behaviors.LoginToboggan={attach:function(o,n){g("#toboggan-login",o).once("toggleboggan_setup",function(){g(this).hide(),Drupal.logintoboggan_toggleboggan()})}},Drupal.logintoboggan_toggleboggan=function(){g("#toboggan-login-link").click(function(){return g("#toboggan-login").slideToggle("fast"),this.blur(),!1})}}(jQuery);