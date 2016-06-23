
'use strict';
var logger = require('./logger'),
    log = logger.log,
    $ = require('jquery'),
    flexisel = require('flexisel');


var Carousel = function() {
  var self = {
    init: function(container, items, clone, cb) {
      log('Carousel.init()');
      let count = !items ? 3 : items;

      container.flexisel({
        visibleItems: count,
        clone: clone,
        enableResponsiveBreakpoints: true,
        responsiveBreakpoints: {
          mobile: {
            changePoint: 480,
            visibleItems: 1,
          },
          mobileWide: {
            changePoint: 600,
            visibleItems: 1,
          },
          tablet: {
            changePoint: 800,
            visibleItems: 2,
          },
          desktop: {
            changePoint: 1185,
            visibleItems: !items ? 3 : Math.round(items/1.5),
          }
        }
      });

      cb();
    },
  };
  return self;
}

module.exports = Carousel();
