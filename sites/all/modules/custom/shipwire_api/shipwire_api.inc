<?php

/**
 * Shipwire API Request class.
 */
class ShipwireAPI {
  public $endpoint;
  public $server;

  protected $method = 'GET';
  protected $cache = FALSE;
  protected $ignoreCache = FALSE;
  protected $cacheExpiration;
  protected $debugRequest;
  protected $nextUrl = NULL;
  protected $previousUrl = NULL;
  protected $urls = array();

  public $debugInfo = NULL;

  /**
   * Constructor.
   */
  public function __construct() {
    $this->server = variable_get('shipwire_response', 'Test');
    $endpoint = variable_get('shipwire_server', 'Test');
    $this->endpoint = ($endpoint == 'Test') ? 'https://api.beta.shipwire.com/api/v3/' : 'https://api.shipwire.com/api/v3/';
  }

  /**
   * Call specific API functions.
   */
  public function __call($method, $arguments) {
    // handle nested endpoints
    if (!empty($arguments) && !is_array($arguments[0])) {
      while ($arguments && !is_array($arguments[0])) {
        $piece = array_shift($arguments);
        $method .= '/' . $piece;
      }
    }
    elseif (!empty($arguments) && is_array($arguments[0])) {
      $arguments = $arguments[0];
    }

    return $this->sendRequest($method, $arguments);
  }

  /**
   * Figure out the API URL to call.
   */
  public function apiURL($api) {
    $url = $this->endpoint;
    if (substr($url, -1) !== '/') {
      $url .= '/';
    }
    return $url . $api;
  }

  /**
   * Borrow the authentication settings from the shipwire module.
   */
  public function authorization() {
    $account = variable_get('shipwire_account', FALSE);
    if (!$account) {
      throw new Exception('Shipwire account information not available.');
    }

    // this number if from the shipwire module.
    $app_id = 3048610241825397;
    $key = trim(preg_replace('/[^0-9]/', '', $app_id), 293570648);
    $len = preg_replace('/[^0-9]/', '', substr($account, 0, 8)) - $key;
    $value_decrypt = base64_decode(substr($account, 8));

    $user = substr($value_decrypt, 0, $len);
    $pass = substr($value_decrypt, $len);
    return 'Basic ' . base64_encode($user . ':' . $pass);
  }

  /**
   * Turn on request caching for this instance.
   */
  public function cacheable($expiration = '+1 hour') {
    $this->cache = TRUE;
    $this->cacheExpiration = $expiration;
    return $this;
  }

  /**
   * Clear the cache for this request.
   *
   * If the request is cacheable, this will ignore any cached value and request
   * fresh data.
   */
  public function clearCache() {
    $this->ignoreCache = TRUE;
    return $this;
  }

  /**
   * Turn on/off debugging.
   */
  public function debug($debug = TRUE) {
    $this->debugRequest = boolval($debug);
    return $this;
  }

  /**
   * Delete method.
   */
  public function delete() {
    $this->method = 'DELETE';
    return $this;
  }

  /**
   * Dump/save the debug information if we are debugging.
   */
  public function dumpDebug($debug) {
    if ($this->debugRequest) {
      $this->debugInfo = $debug;
      if (function_exists('dd') && variable_get('shipwire_api_debug')) {
        dd($debug);
      }
    }
  }

  /**
   * Get the warehouses.
   */
  public function getWarehouses() {
    $warehouses = array();
    $response = $this->sendRequest('stock');
    if ($response && count($response->resource->items) > 0) {
      do {
        foreach ($response->resource->items as $item) {
          if (!in_array($item->resource->warehouseRegion, $warehouses)) {
            $warehouses[] = $item->resource->warehouseRegion;
          }
        }
      } while ($response = $this->next());
    }
    sort($warehouses);
    return $warehouses;
  }

  /**
   * Set the next request method to GET.
   *
   * Note that unlike post(), setting this to GET is "sticky" meaning it will
   * persist in this mode for more than one request.
   */
  public function get() {
    $this->method = 'GET';
    return $this;
  }

  /**
   * The next request should use POST
   */
  public function post() {
    $this->method = 'POST';
    return $this;
  }

  /**
   * Ask for the next set of data.
   */
  public function next() {
    if (!$this->nextUrl) {
      return NULL;
    }

    $url = parse_url($this->nextUrl);
    $query = array();
    parse_str($url['query'], $query);
    $api = explode('/', $url['path']);
    $api = array_pop($api);

    return $this->sendRequest($api, $query);
  }

  /**
   * Send an API request.
   */
  public function sendRequest($api, $data = array()) {
    $debug = array('messages' => array());
    $url = $this->apiURL($api);
    $headers = array(
      'Authorization: ' . $this->authorization(),
    );

    if ($this->method === 'GET') {
      $url .= '?' . http_build_query($data);
      $debug['encoded_data'] = http_build_query($data);
    }
    elseif ($this->method === 'POST') {
      $headers[] = 'Content-Type: application/json';
    }

    // if this is a GET request, check the cache
    if (!isset($this->urls[$url])) {
      $this->urls[$url] = 0;
    }
    $this->urls[$url]++;

    if ($this->urls[$url] > 10) {
      drupal_set_message(t('Error: recursive API call detected'), 'error');
      return FALSE;
    }

    $url_hash = sha1($url);
    $cache_key = $api . '_' . $url_hash;
    if ($this->cache && $this->method === 'GET') {
      $debug['messages'][] = 'Checking cache for ' . $cache_key;
      $cache = cache_get($cache_key, 'cache_shipwire_api');

      // if we're skipping the cache, reset it here.
      if ($this->ignoreCache) {
        $debug['messages'][] = 'Ignoring cache';
        $cache = NULL;
      }

      if ($cache && stools_use_cache($cache) && $cache->data) {
        $debug['messages'][] = 'Using cached value';
        try {
          $response = new ShipwireAPIResponse($cache->data);
          $response->url = $url;
          $response->cached = TRUE;
          $this->nextUrl = NULL;
          if (isset($response->resource->next) && $response->resource->next) {
            $this->nextUrl = $response->resource->next;
          }
          $this->previousUrl = NULL;
          if (isset($response->resource->previous) && $response->resource->previous) {
            $this->previousUrl = $response->resource->previous;
          }
          $this->dumpDebug($debug);
          return $response;
        }
        catch (Exception $e) {

        }
      }
    }
    // if we are not caching this request, but we were asked to clear the
    // cache we will just make an explicit clear call.
    elseif (!$this->cache && $this->ignoreCache) {
      $debug['messages'][] = 'Clearing cache for ' . $cache_key;
      cache_clear_all($cache_key, 'cache_shipwire_api');
    }

    $debug['url'] = $url;
    $debug['headers'] = $headers;
    $debug['raw_data'] = $data;

    // Setup the cURL request.
    $debug['messages'][] = 'Preparing request';
    $ch = curl_init();
    curl_setopt($ch, CURLOPT_URL, $url);
    curl_setopt($ch, CURLOPT_VERBOSE, 0);
    curl_setopt($ch, CURLOPT_HTTPHEADER, $headers);
    if ($this->method === 'POST') {
      $debug['messages'][] = 'Using POST method for this request';
      curl_setopt($ch, CURLOPT_POST, 1);
      // curl_setopt($ch, CURLOPT_POSTFIELDS, http_build_query($data));
      // var_dump(json_encode($data));
      $encoded_data = json_encode($data);
      $debug['encoded_data'] = $encoded_data;
      curl_setopt($ch, CURLOPT_POSTFIELDS, $encoded_data);
    }
    elseif ($this->method === 'DELETE') {
      $debug['messages'][] = 'Using DELETE method for this request';
      curl_setopt($ch, CURLOPT_CUSTOMREQUEST, 'DELETE');
      // curl_setopt($ch, CURLOPT_POSTFIELDS, $data);
    }
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
    curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, 1);
    curl_setopt($ch, CURLOPT_NOPROGRESS, 1);
    curl_setopt($ch, CURLOPT_FOLLOWLOCATION, 0);
    curl_setopt($ch, CURLOPT_HEADER, 1);

    // send the request
    $response = curl_exec($ch);
    $header_size = curl_getinfo($ch, CURLINFO_HEADER_SIZE);
    $header = substr($response, 0, $header_size);
    $body = substr($response, $header_size);
    $error = curl_error($ch);
    $code = curl_getinfo($ch, CURLINFO_HTTP_CODE);
    curl_close($ch);

    $debug['messages'][] = 'Request sent';
    $debug['raw_response'] = $body;
    $debug['raw_error'] = $error;
    $debug['response_headers'] = $header;

    // handle low-level API errors (like not being able to connect)
    if (!$response) {
      $debug['messages'][] = 'Invalid raw response: ' . var_export($response, TRUE);
      if ($error) {
        watchdog('shipwire_api', 'There was an error receiving information from shipwire: %error', array('%error' => $error), WATCHDOG_ERROR);
        $debug['messages'][] = 'There was an error: ' . $error;
      }
      $this->dumpDebug($debug);
      return NULL;
    }

    // return data
    $api_response = new ShipwireAPIResponse($body, $error, $code, $debug);
    $api_response->url = $url;
    if (!$api_response->isError() && $this->cache) {
      cache_set($cache_key, $body, 'cache_shipwire_api', strtotime($this->cacheExpiration));
      $debug['messages'][] = 'Updated cache for ' . $cache_key;
    }

    $this->nextUrl = NULL;
    if (isset($api_response->resource->next)) {
      $this->nextUrl = $api_response->resource->next;
    }

    $this->previousUrl = NULL;
    if (isset($api_response->resource->previous)) {
      $this->previousUrl = $api_response->resource->previous;
    }

    // reset the method flag
    if ($this->method !== 'GET') {
      $this->method = 'GET';
    }
    $this->dumpDebug($debug);
    return $api_response;
  }

}

/**
 * Response data.
 */
class ShipwireAPIResponse {
  public $data;
  public $error;
  public $cached = FALSE;
  public $url;
  public $code;
  public $debug;

  /**
   * Parse the data.
   */
  public function __construct($data, $error = NULL, $code = NULL, $debug = NULL) {
    if (is_string($data)) {
      $decoded_data = json_decode($data);
    }

    if (!$data) {
      throw new Exception('Invalid response data');
    }

    $this->data = $decoded_data;
    $this->error = $error;
    $this->code = $code;
    $this->debug = $debug;

    if (isset($this->data->error) && !$this->error) {
      $this->error = $this->data->error;
    }

    if (isset($this->data->errors) && !$this->error) {
      $this->error = $this->data->errors;
    }

    // log the error
    if ($this->isError() && $this->debug) {
      db_insert('shipwire_api_errors')
        ->fields(array(
          'id' => NULL,
          'commerce_order_number' => 0,
          'message' => $data,
          'error_date' => time(),
        ))
        ->execute();
    }
  }

  /**
   * Get something from the data.
   */
  public function __get($key) {
    $this->assertData();
    if (isset($this->data->{$key})) {
      return $this->data->{$key};
    }
  }

  /**
   * Check if data exists.
   */
  public function __isset($name) {
    return isset($this->data->{$name});
  }

  /**
   * Make sure we have data.
   */
  public function assertData() {
    if (!$this->data) {
      // print '<pre>';
      // debug_print_backtrace();
      throw new Exception('Invalid response data');
    }
  }

  /**
   * Return the status code.
   *
   * @return int
   *   The status code for the request.
   */
  public function status() {
    $this->assertData();
    if (!isset($this->data->status)) {
      return FALSE;
    }
    return intval($this->data->status);
  }

  /**
   * Check if there was an error with this request.
   *
   * @return bool
   *   Returns TRUE if there was an error, FALSE if not.
   */
  public function isError() {
    if ($this->error) {
      return TRUE;
    }

    try {
      $status = $this->status();
      $return = ($status >= 400);
      if ($return) {
        $this->error = TRUE;
      }
      return $return;
    }
    catch (Exception $e) {
      return FALSE;
    }
  }

  /**
   * Return pagination details.
   */
  public function paginationDetails() {
    $details = array();
    $details['total'] = $this->resource->total;
    $details['offset'] = $this->resource->offset;
    $details['next'] = $this->resource->next;
    $details['previous'] = $this->resource->previous;
    return $details;
  }

}
