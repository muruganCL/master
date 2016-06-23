'use strict';

var logger = require('./logger'),
    log = logger.log,
    $ = require('jquery'),
    toggle = require('./toggle'),
    throttle = require('lodash/function/throttle'),
    accordion = require('./accordion'),
    drawer = require('./drawer');

    var events = require('events');
    var eventEmitter = new events.EventEmitter();

var UiInteractions = function() {

  var self = {
    getElements: function() {

      const elements = {
        $body: $('body'),
        $window: $(window),
        $drawer: $('#header-drawer'),
        $overlay: $('#header-overlay'),
      };

      return elements;
    },

    bindUi: function() {
      var $window = $(window);
      var $body = $('body');
      var $header = $('#header').height();
      var lastScrollTop = 0;

      $(window).resize(throttle(drawer.onWindowResize, 1000/30));

      $window.on('scroll', function() {
        var scroll = $(this).scrollTop();

        // If scroll position is past header height, add 'nav-up' to body
        if(scroll > $header) {
          $body.addClass('nav-up nav-below');
        }

        // Else remove 'nav-up'
        else {
          $body.removeClass('nav-up nav-below');
        }

        // If scrolling up, remove 'nav-up' from body
        if(scroll < lastScrollTop) {
          $body.removeClass('nav-up');
        }

        // Update last scroll position
        lastScrollTop = scroll;
      });

      // Bind the main mobile navigation toggle.
      // $('body').on({
      //   'collapse.toggle': log('hello'),
      //   'expand.toggle': log('hi')
      // }, '.product-toggle');

      // Menu toggle
      $('.header-toggle').click(function(e) {
        const $this = $(this);

        if ($this.attr('aria-expanded') === 'true') {
          drawer.onNavCollapse(self.getElements())
        } else if ($this.attr('aria-expanded') === 'false') {
          drawer.onNavExpand(self.getElements())
        }
      });

    },

    init: function() {
      log('UiInteractions.init()');

      self.bindUi();
      // toggle.init();
      drawer.onWindowResize();
      accordion.init();
    },
  }

  return self;
}

module.exports = new UiInteractions;
