var categoryToggle = require('./lib/categoryToggle');

(function($, categoryToggle) {
  $(document).ready(function() {
    categoryToggle.init({
      ui: require('./templates/categoryToggle.nunj').render({
        categories: {
          printers: 'Printers',
          filament: 'Filament',
          'tool-heads': 'Tool Heads',
          parts: 'Parts',
          merchandise: 'Merchandise'
        }
      })
    });

    $('#content')
      .on('category-toggle-empty', function() {
        if ($('#category-toggle-empty').length !== 0) {
          $('#category-toggle-empty').show();
          return;
        }
        $('<div id="#category-toggle-empty"><p>' + Drupal.t('No categories selected.') + '</p></div>').insertBefore('#content .block-bean:first');
      })
      .on('category-toggle-not-empty', function() {
        $('#category-toggle-empty').hide();
      });
  });
})(jQuery, categoryToggle);
