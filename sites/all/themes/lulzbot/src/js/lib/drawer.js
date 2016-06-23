var logger = require('./logger'),
    log = logger.log,
    $ = require('jquery'),
    velocity = require('velocity-animate');

class Drawer {

  fitDrawerToScreen() {

  };

  onWindowResize() {
    const $window = $(window);
    const $header = $('#header')

    $('#header-drawer').css('min-height', $window.height() - $header.outerHeight() - $header.offset().top);
  };

  onNavCollapse(e) {
    $('html').removeClass("prevent-scroll");
    this.hideDrawer(e.$drawer);
    this.hideOverlay(e.$overlay);
  };

  onNavExpand(e) {
    $('html').addClass("prevent-scroll");
    this.showDrawer(e.$drawer);
    this.showOverlay(e.$overlay);
  };

  hideDrawer($drawer) {
    $drawer.velocity({
        translateX: [0, '-100%']
      },
      {
        duration: 400,
        display: 'none'
    });
  };

  showDrawer($drawer) {
    $drawer.velocity({
        translateX: ['-100%', 0]
      },
      {
        duration: 400,
        display: 'block'
    });
  };

  showOverlay($overlay) {
    $overlay.velocity({
        opacity: ['.4', 0]
      },
      {
        duration: 400,
        display: 'block'
    });
  };

  hideOverlay($overlay) {
    $overlay.velocity({
        opacity: [0, '.4']
      },
      {
        duration: 400,
        display: 'none'
    });
  };
}

module.exports = new Drawer;
