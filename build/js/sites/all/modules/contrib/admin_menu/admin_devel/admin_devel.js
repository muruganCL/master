!function(e){jQuery.extend({debug:function(){if(window.debug=window.debug||[],args=jQuery.makeArray(arguments),"object"==typeof this)var e=args.length?args[0]:window.debug.length,n=this;else var e=args.length>1?args.pop():window.debug.length,n=args[0];return window.debug[e]=n,"undefined"!=typeof console&&console.log(e,n),this}}),jQuery.fn.debug=jQuery.debug}(jQuery);