/*
 * toggle.js
 */
var logger = require('./logger'),
    log = logger.log,
    $ = require('jquery');

var toggle = function() {

  /**
   * Expand an accordian.
   */
  function expandAccordian($accordian) {
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
  function collapseAccordian($accordian) {
    $accordian.velocity(
      "slideUp",
      {
        duration: 200,
        display: 'none'
    });
  };

  /**
   * Get Panel from toggle.
   */
  function getTogglePanel($toggle) {
    var $panel = $('#' + $toggle.attr('aria-controls'));
    return $panel.length > 0 ? $panel : false;
  };

  /**
   * Click Handler.
   */
  function onToggleClick(event) {
    var $target = $(event.target);
    $target.trigger($target.attr('aria-expanded') === 'true' ? 'collapse' : 'expand');

    if ($target.attr('aria-expanded') === 'true') {
      onToggleCollapse($target);
    } else {
      onToggleExpand($target);
    }

    event.preventDefault();
  };

  /**
   * Collapse Handler.
   */
  function onToggleCollapse(event) {
    var $target = $(event.target),
        $panel = getTogglePanel($target);

    // Update this toggle's state.
    $target.attr('aria-expanded', 'false');
    // Collapse this panel.
    if ($panel) {
      $panel.velocity(
        "slideUp",
        {
          duration: 200,
          display: 'none'
      });
      $panel.trigger('collapse');
    };
  };

  /**
   * Expand Handler.
   */
   function onToggleExpand(event) {
    var $target = $(event.target),
        $panel = getTogglePanel($target);

    // Update this toggle's state.
    $target.attr('aria-expanded', 'true');
    // Expand this panel.
    if ($panel) {
      $panel.velocity(
        "slideDown",
        {
          duration: 200,
          display: 'block'
      });
     $panel.trigger('expand');
    };
  };

  /**
   * Bind Toggles.
   */
  function bindUi() {
    var toggle = this,
        $body = $('body');

    $body.on('click.toggle', '.toggle[aria-controls]', onToggleClick);
    $body.on('expand.toggle', onToggleExpand);
    $body.on('collapse.toggle', onToggleCollapse);
  };

  return {
    init: function() {
      var toggle = this;

      log('toggle.init()');
      bindUi();
    }
  };
};

module.exports = toggle();
