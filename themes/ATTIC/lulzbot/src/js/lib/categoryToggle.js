/**
 * Store category toggle functionality.
 */

var $ = require('jquery');

var categoryToggle = {
  isEmpty: false,

  /**
   * Initialize the functionality.
   */
  init: function(options) {
    categoryToggle.initUI(options);
    $('input.category-toggle').on('change', categoryToggle.toggle);
    $('#content').on('category-toggle', function() {
      var visible = $('#content .block-bean:visible').length;
      if (visible === 0) {
        categoryToggle.isEmpty = true;
        $('#content').trigger('category-toggle-empty');
      }
      else if (visible !== 0 && categoryToggle.isEmpty) {
        categoryToggle.isEmpty = false;
        $('#content').trigger('category-toggle-not-empty');
      }
    });
  },

  /**
   * Initialize the UI controls.
   */
  initUI: function(options) {
    $(options.ui).prependTo('#content');
  },

  /**
   * Toggle the category.
   */
  toggle: function(event) {
    var $checkbox = $(event.target);
    var selector = '#block-bean-' + $checkbox.val();
    var headerSelector = '#block-bean-' + $checkbox.val() + '-heading';
    var $selector = $(selector + ',' + headerSelector);
    $selector.toggle();
    $('#content').trigger('category-toggle', $selector);
  }
};

module.exports = categoryToggle;
