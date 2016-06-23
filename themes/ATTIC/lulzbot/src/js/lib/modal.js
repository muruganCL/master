'use strict';

var logger = require('./logger'),
    log = logger.log,
    $ = require('jquery'),
    sweetAlert = require('sweetalert');

class Modal {
  elements() {
    return {
      $body: $('body'),
      $notifyBtn: $('.notify-btn'),
      $notifyMe: $('.notify-me .form-item-description'),
    }
  }
  bindUi() {
    var _modal = this;
    this.elements().$body.on('click.notify', '.notify-btn', function() {
      _modal.showModal(_modal.elements().$notifyMe.text());
    });
  }
  showModal(content) {

    sweetAlert.setDefaults({ confirmButtonColor: '#c1d640' });

    sweetAlert({
      title: 'E-mail Notification',
      text: content,
      allowOutsideClick: true,
      type: 'input',
      inputPlaceholder: 'admin@example.com',
      confirmButtonText: 'Notify Me',
      showCancelButton: true,
      closeOnConfirm: false,
    }, function(inputValue){
      log(inputValue);
      if (inputValue === false) return false;
      if (inputValue === "") {
        sweetAlert.showInputError("You need to write something!");
        return false
      }



      sweetAlert("Nice!", "You wrote: " + inputValue, "success");
    });
  }
}

module.exports = new Modal;
