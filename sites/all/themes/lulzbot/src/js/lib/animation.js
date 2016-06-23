var logger = require('./logger'),
    log = logger.log,
    $ = require('jquery'),
    velocity = require('velocity-animate');

class Animation() {

  // Expand an accordian.
  expandAccordian($accordian) {
    $accordian.velocity(
      "slideDown",
      {
        duration: 200,
        display: 'block'
    });
  };

  // Collapse an accordian.
  collapseAccordian($accordian) {
    $accordian.velocity(
      "slideUp",
      {
        duration: 200,
        display: 'none'
    });
  };

  onNavToggleCollapse(e) {
    var $target = $(e.target);

    // Handle the top level toggle in the header different.
    if ($target.is('#header--desktop .nav-toggle:not(.header-nav .header-nav .nav-toggle)')) {
      onDropdownToggleCollapse(e);
      return;
    }

    var $panel = getPanelFromToggle($target);

    collapseAccordian($panel);
  };
}

module.exports = new Animation;
