(function($, Drupal) {

  $(document).ready(function() {

    // add an error class to each row with an issue.
    $(Drupal.settings.lulzbot_store.errors).each(function(index, item) {
      var $quantity = $('#edit-edit-quantity-' + item.position);
      $quantity.closest('tr').addClass('form-error');
    });

  });

})(jQuery, Drupal);
