'use strict';

var gallery = require('./lib/gallery');
var responsiveVideo = require('./lib/responsiveVideo');
var uiInteractions = require('./lib/uiInteractions');
var toggle = require('./lib/toggle');
var numeric = require('./lib/plugins/jquery.numeric.js');
var tooltip = require('tooltip');
var mdrnizr = require('./lib/modernizr');
const stacktable = require('stacktable');

import {Compare} from './lib/compare';
import {EqualHeight} from './lib/equalHeights';

const compare = new Compare();
const equalHeight = new EqualHeight();

(function($, toggle, gallery, responsiveVideo, uiInteractions) {
  $(document).ready(function() {

    uiInteractions.init();
    toggle.init();
    responsiveVideo.init();
    gallery.init('.product-gallery');
    tooltip({
      showDelay: 0,
      throttle: 0,
      offset: {
        x: 0,
        y: 10
      },
      style: {
        border: 0,
        transition: 'none',
        background: '#565656',
        padding: 25
      }
    });

    compare.init();
    equalHeight.init();

    console.log(stacktable);
    $('.views-table').stacktable();

    $('.form-text.quantity').numeric(false);

  });
})(jQuery, toggle, gallery, responsiveVideo, uiInteractions);
