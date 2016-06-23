var logger = require('./logger'),
    log = logger.log,
    $ = require('jquery');

var responsiveVideo = function() {

  var self = {
    init: function() {
      $.each($('iframe'), function() {
        var $this = $(this);
        var src = $this.attr('src');

        if (src.indexOf('youtube.com') >= 0) {
          $this.wrap('<div class="video-wrapper"></div>');
        }
      });
    },
  };

  return self;
}

module.exports = responsiveVideo();
