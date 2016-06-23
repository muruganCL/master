var userLocation = {
  selectors: {},
  availability: {},

  initialized: false,
  setLocation: false,
  state: null,

  log: function() {
    if (typeof console !== 'undefined' && typeof console.log !== 'undefined' && typeof console.log.apply !== 'undefined') {
      console.log.apply(console, arguments);
    }
  },

  /**
   * Change location event handler.
   */
  changeLocation: function(event) {
    event.preventDefault();
    var self = userLocation;
    self.setStateNeedLocation();
    self.setLocation = false;

    return false;
  },

  /**
   * Update all country select's if multiple
   */
  updateAllSelects: function(event) {
    var selected = jQuery(this).val();
    var disabled = false;
    if (!userLocation.isValidCountrySelected(selected)) {
      disabled = true;
    }

    userLocation.selectors.checkAvailabilityButton.attr('disabled', disabled);
    userLocation.selectors.countrySelection.val(selected);
  },

  /**
   * Check if a valid country is selected.
   */
  isValidCountrySelected: function(value) {
    if (!value) {
      value = userLocation.selectors.countrySelection.val();
    }
    return /^[A-Z]+/.test(value);
  },

  /**
   * Check the avalability event handler.
   */
  checkAvailability: function(event) {
    event.preventDefault();
    var self = userLocation;

    // UI functionality
    //
    // make sure they have selected a country
    if (!self.isValidCountrySelected()) {
      self.selectors.countrySelection.addClass('error');
      return;
    }

    // remove the error class from the validation, if any
    self.selectors.countrySelection.removeClass('error');

    // set the location information in the UI
    var country = self.selectors.countrySelection.val();

    self.selectors.userLocation.find('span')
      .data('country', country)
      .text(Drupal.t('Viewing availability for ') + self.selectors.countrySelection.first().find('option:selected').text());
    jQuery('#add-to-cart-user-location').val(country);
    self.selectors.checkAvailabilityButton.text(Drupal.t('Checking availability'));

    // send AJAX to store the user's location.
    var product = jQuery(event.target).closest('form').find('input[name="product_id"],select[name="product_id"]').val();
    jQuery.ajax({
      url: '/ajax/store/location',
      data: {
        location: country,
        product_id: product
      },
      type: 'GET',
    })
    .always(function(data) {
      userLocation.selectors.checkAvailabilityButton.text(Drupal.t('Check availability'));

      // product is available, show and enable the add to cart button
      var disabled = 'disabled';
      var buttonText = 'Unavailable';

      if (data.is_available) {
        disabled = false;
        buttonText = 'Add to Cart';
      }

      // update form elements
      jQuery('form.commerce-add-to-cart').removeClass('disabled').removeClass('in-stock').addClass('unavailable');
      jQuery('form.commerce-add-to-cart input[type="submit"]')
        .removeClass('form-button-disabled')
        .attr('disabled', disabled)
        .val(Drupal.t(buttonText))
        .show();
      self.setStateHaveLocation();

      // update additional availability if present
      if (Drupal.settings.hasOwnProperty('filamentSkuColorMap') && data.hasOwnProperty('related_availability')) {
        // figure out which skus are available
        var available = [];
        for (var sku in data.related_availability) {
          if (data.related_availability.hasOwnProperty(sku)) {
            if (data.related_availability[sku] && data.related_availability[sku].hasOwnProperty(country) && data.related_availability[sku][country] > 0) {
              available.push(sku);
            }
          }
        }

        // figure out which colors relate to those skus
        var availableColors = [];
        for (var color in Drupal.settings.filamentSkuColorMap) {
          if (Drupal.settings.filamentSkuColorMap.hasOwnProperty(color)) {
            for (var i = 0; i < Drupal.settings.filamentSkuColorMap[color].length; i++) {
              if (available.indexOf(Drupal.settings.filamentSkuColorMap[color][i]) != -1) {
                availableColors.push(parseInt(color, 10));
              }
            }
          }
        }

        // update color links
        jQuery('.link--filament-color').each(function() {
          var $this = jQuery(this);
          var $parent = $this.closest('li');
          if (availableColors.indexOf(parseInt($this.data('color'), 10)) != -1) {
            $parent.removeClass('unavailable');
          }
          else {
            $parent.addClass('unavailable');
          }
        });
      }
    });

    Drupal.settings.lulzbot_store.location = country;
    self.setLocation = true;
  },

  /**
   * Hide the add to cart button.
   *
   * Handles hiding the disabled add to cart button and also cases where the
   * UI needs to hide the button no matter what.
   */
  hideAddToCartButton: function() {
    var selector = 'form.commerce-add-to-cart input[type=submit]';

    // show the button, it may get hidden again below.
    jQuery(selector).show();

    if (arguments.length === 0 || (!arguments[0])) {
      selector = 'form.commerce-add-to-cart.disabled input[type=submit]';
    }

    jQuery(selector).hide();
  },

  /**
   * Initialize the user location functionality.
   */
  init: function() {
    var self = userLocation;
    self.initSelectors();

    // check if there is a user location setting
    self.setStateHaveLocation();
    var storePage = Drupal.settings.hasOwnProperty('lulzbot_store');
    var haveLocation = storePage && Drupal.settings.lulzbot_store.hasOwnProperty('location') && Drupal.settings.lulzbot_store.location;
    if (storePage && !haveLocation) {
      self.setStateNeedLocation();
      userLocation.selectors.checkAvailabilityButton.attr('disabled', true);
    }

    // hide the submit button if it is disabled
    self.hideAddToCartButton();

    // self.updateAllSelects();

    jQuery('body')
      .on('change', '.form-item-countries select', self.updateAllSelects)
      .off('click', '#lulzbot-store-check-availability')
      .on('click', '#lulzbot-store-check-availability', self.checkAvailability)
      .off('click', 'a.link--change-location')
      .on('click', 'a.link--change-location', self.changeLocation)
      .off('click', '.notify-btn')
      .on('click', '.notify-btn', self.showModal)
      .off('click', '#lulzbot-store-notify-me')
      .on('click', '#lulzbot-store-notify-me', self.notify);
    self.initialized = true;
  },

  /**
   * Initialize selectors.
   *
   * Called on dom ready and when the product options have been changed.
   */
  initSelectors: function() {
    userLocation.selectors = {
      userLocation: jQuery('.location'),
      checkAvailabilityButton: jQuery('.button--check-availability'),
      changeLocationLink: jQuery('a.link--change-location'),
      countrySelect: jQuery('.country-selection'),
      countrySelection: jQuery('.form-item-countries select'),
      notify: jQuery('.form-item-notify-me :input'),
      notifyButton: jQuery('#lulzbot-store-notify-me'),
      notifyDescription: jQuery('.notify-me .form-item-description'),
    };
  },

  /**
   * Show modal
   */
  showModal: function() {
    swal.setDefaults({ confirmButtonColor: '#c1d640' });
    var options = {
      title: 'E-mail Notification',
      text: Drupal.t('Enter your email address to receive an email when this product becomes available.'),
      allowOutsideClick: true,
      type: 'input',
      inputType: 'email',
      inputPlaceholder: 'email@example.com',
      confirmButtonText: 'Notify Me',
      showCancelButton: true,
      closeOnConfirm: false,
      showLoaderOnConfirm: true,
      animation: 'slide-from-top',
    };

    if (userLocation.selectors.notify.val()) {
      options.inputValue = userLocation.selectors.notify.val();
    }

    swal(options, function(inputValue) {
      if (inputValue === false) return false;
      if (inputValue === '') {
        sweetAlert.showInputError('Please enter your email.');
        return false;
      }

      userLocation.selectors.notify.val(inputValue);
      userLocation.notify(inputValue, function(msg) {
        sweetAlert(Drupal.t('Thank You'), msg);
      });
    });
  },

  /**
   * Add the user's notification request.
   */
  notify: function(input, cb) {
    if (userLocation.selectors.notify.val()) {
      var email = input;
      var $form = userLocation.selectors.notify.closest('form');
      var formId = $form.find('input[name="notify_token"]').val();
      var request = {
        notify_me: email,
        form_token: formId,
        product_id: parseInt($form.find('input[name="product_id"],select[name="product_id"]').val(), 10)
      };
      jQuery.ajax({
        type: 'POST',
        url: '/ajax/store/notify',
        data: request
      })
      .done(function(e) {
        userLocation.log('done');
        jQuery('<div class="message">' + Drupal.t('You will be notified when this product becomes available.') + '</div>')
          .insertAfter('fieldset.notify-me');
          cb(Drupal.t('You will be notified when this product becomes available.'));
        jQuery('fieldset.notify-me').hide();
        jQuery('.notify-btn').hide();
      })
      .fail(function() {
        userLocation.log('fail');
        jQuery('fieldset.notify-me').prepend('<div class="message error">Could not add notification right now. Please try again later.</div>');
        cb(Drupal.t('Could not add notification right now. Please try again later.'));
      });
    }
  },

  /**
   * Configure the UI so the location picked is hidden.
   */
  setStateHaveLocation: function() {
    var self = userLocation;
    self.log('setStateHaveLocation');

    self.selectors.countrySelect.hide();
    self.selectors.checkAvailabilityButton.hide();

    self.selectors.userLocation.show();

    // hides the disabled add to cart button, if any
    self.hideAddToCartButton();

    self.selectors.checkAvailabilityButton.attr('disabled', 'disabled');
    self.state = 'have_location';
  },

  /**
   * Configure the UI so that the location picker is visible.
   */
  setStateNeedLocation: function() {
    var self = userLocation;
    self.log('setStateNeedLocation');

    // hide the user location text & link
    self.selectors.userLocation.hide();

    // hide the add to cart button
    self.hideAddToCartButton(true);

    // turn on the country selection
    self.selectors.countrySelect.show();
    self.selectors.checkAvailabilityButton.show();
    self.selectors.checkAvailabilityButton.attr('disabled', false);
    self.state = 'need_location';
  }

};

// fire when products change (ajax)
Drupal.behaviors.userLocation = {
  attach: function() {
    userLocation.init();
  }
};
