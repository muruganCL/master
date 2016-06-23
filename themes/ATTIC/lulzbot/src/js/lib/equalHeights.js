'use strict';

var logger = require('./logger'),
  log = logger.log,
  $ = require('jquery'),
  matchHeight = require('jquery-match-height');


export class EqualHeight {
  /**
   * Initializes class
   *
   * @method     init
   */
  init() {
    $('.compare--description').matchHeight();
    $('.compare--printer-info').matchHeight();
  }
}
