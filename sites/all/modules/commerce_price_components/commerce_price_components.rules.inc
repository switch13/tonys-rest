<?php

/**
 * @file
 * Rules integration for the price by components module.
 *
 * @addtogroup rules
 * @{
 */

/**
 * Implements hook_rules_data_info_alter().
 */
function commerce_price_components_rules_data_info_alter(&$data_info) {
  $data_info['commerce_price']['property info'] = commerce_price_components_field_data_property_info();
}
