var filaments = {};
(function($, Drupal) {
  filaments.init = function() {
    $('.link--filament-color').on('click', function(event) {
      event.preventDefault();
      var $this = $(this);
      var $form = $this.closest('form');
      $form.find('input[name="attributes[field_product_filament_colors]"]').val(parseInt($this.data('color'), 10));
      $form.find('select:first').change();
    });
  };

})(jQuery, Drupal);

Drupal.behaviors.lulzbotFilament = {
  attach: function() {
    filaments.init();
  }
};
