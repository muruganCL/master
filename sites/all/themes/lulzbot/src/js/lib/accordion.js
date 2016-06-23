//
// Accordion
//

'use strict';

var logger = require('./logger'),
    log = logger.log,
    $ = require('jquery'),
    uniqueId = require('lodash/utility/uniqueId'),
    velocity = require('velocity-animate');

    var events = require('events');
    var eventEmitter = new events.EventEmitter();

class Accordion {

  /**
   * Expand an accordian.
   */
  expandAccordian($accordian) {
    $accordian.velocity(
      "slideDown",
      {
        duration: 200,
        display: 'block'
    });
  };

  /**
   * Collapse an Accordian.
   */
  collapseAccordian($accordian) {
    $accordian.velocity(
      "slideUp",
      {
        duration: 200,
        display: 'none'
    });
  };

  /**
   * Setup accordian functionality
   */
  setupAccordian(accordion) {
    var $oldMenu = $(accordion);
    // We clone the original menu to make it easy to replace after processing.
    var $newMenu = $oldMenu.clone();
    let self = this;

    $newMenu.find('.toggle').each(function(i) {
      var $this = $(this).addClass('has-toggle');
      var $panel = $this.next('div');
      var $toggle = $this;
      var panelId = uniqueId('panel--');
      var toggleId = uniqueId('toggle--');

      // Add the panel attributes.
      $panel.attr({
        'id': panelId,
        'aria-expanded': false
      });

      // Add the toggle attributes.
      $toggle.attr({
        'id': toggleId,
        'aria-controls': panelId,
        'aria-expanded': false
      });

      // $toggle.on('click', function() {
      //   log($this.parent().siblings().children('.toggle'));
      //   self.collapseAccordian($this.parent().siblings().children('.toggle'));
      //   self.expandAccordian($this);
      // });

    });

    $oldMenu.replaceWith($newMenu);
  };

  /**
   * Setup accordian functionality
   */
  setupAccordians() {
    var menus = [];
    var _this = this;

    $('.accordion').each(function(){
      menus.push($(this));
    });

    menus.forEach(function(e, i) {
      _this.setupAccordian(e);
    });
  };

  init() {
    log('Accordion.init()');

    this.setupAccordians();
  };

};

module.exports = new Accordion;
