(function($, Drupal) {

  $(document).ready(function() {
    $('#country-actions').on('select change', function(event) {
      var $target = $(event.target);

      // figure out the action
      var action = $target.val();

      var $selected = $('table tbody :checkbox:checked');
      $selected.each(function(elem) {
        var $element = $(this);
        var $row = $element.closest('tr');
        if (action == 'enable' || action == 'disable') {
          $row.find('select.country-status')
            .val(action == 'enable' ? 'enabled' : 'hidden');
        }
        else if (action === 'all') {
          $row.find('select.warehouses option[value!="0"]').attr('selected', 'selected');
          $row.find('select.warehouses option[value="0"]').attr('selected', false);
        }
        else if (action === 'none') {
          $row.find('select.warehouses option[value!="0"]').attr('selected', false);
          $row.find('select.warehouses option[value="0"]').attr('selected', 'selected');
        }
      });

      // reset the action selection
      $target.val('');

    });

    $('table :checkbox').on('change', function(event) {
      // figure out the event target and check if it is the select all checkbox
      var $target = $(event.target);
      var isSelectAll = $target.parent().hasClass('select-all');
      var state = 'disable';

      // if this is the select all checkbox, we may need to enable before all
      // the checkboxes are checked.
      if (isSelectAll && $target.is(':checked')) {
        state = 'enable';
      }
      else if (!isSelectAll) {
        var $checked = $('table :checkbox:checked');
        if ($checked.length > 0) {
          state = 'enable';
        }
      }

      // enable/disable the actions dropdown
      if (state === 'enable') {
        $('#country-actions').removeAttr('disabled')
          .closest('.form-item').removeClass('form-disabled');
        return;
      }

      $('#country-actions').attr('disabled', 'disabled')
        .closest('.form-item').addClass('form-disabled');
    });
  });

})(jQuery, Drupal);
