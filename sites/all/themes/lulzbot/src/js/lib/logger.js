var logger = {};
module.exports = logger;

logger.canLog = null;
logger.canApply = null;

// define contexts and whether they can console.log or not
logger.debugSettings = {
  master: true,
  multimedia: true
};

/**
 * Check if we are in a console capable system
 */
logger.init = function() {
  logger.canLog = typeof console !== 'undefined' && typeof console.log !== 'undefined';
  logger.canApply = typeof console.log.apply !== 'undefined';
};

/**
 * Log a message, taking context and loggability into account.
 */
logger.log = function() {
  var context = 'master',
    thisArguments = Array.prototype.slice.call(arguments);

  if (logger.canLog === null) {
    logger.init();
  }

  if (arguments.length > 1) {
    if (typeof arguments[0] === 'string' && typeof logger.debugSettings[arguments[0]] !== 'undefined') {
      console.log(arguments);
      console.log(thisArguments);
      context = arguments[0];
      thisArguments.shift();
    }
  }

  if (typeof logger.debugSettings[context] !== 'undefined' && logger.debugSettings[context]) {
    if (logger.canLog) {
      if (logger.canApply) {
        return console.log.apply(console, thisArguments);
      }

      // non-apply version for some browsers (*cough* ie)
      console.log(thisArguments);
    }
  }
};
