'use strict';

var logger = require('./logger'),
    log = logger.log,
    $ = require('jquery'),
    enquire = require('enquire.js');

export class Compare {
  init() {
    enquire.register("screen and (max-width:992px)", {
      match: this.compareHeaderMobile,
      unmatch: this.compareHeaderDesktop,
    });
  };

  compareHeaderMobile() {
    $('.node-type-page .compare--primary').prependTo('.mini-printer-specs');
    $('.node-type-page .compare--secondary').prependTo('.taz-printer-specs');
  };

  compareHeaderDesktop() {
    $('.node-type-page .compare--primary').prependTo('.compare--header');
    $('.node-type-page .compare--secondary').appendTo('.compare--header');
  };
}
