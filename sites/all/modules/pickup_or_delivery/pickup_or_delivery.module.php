<?php

/**
* @file
* Pickup or Delivery Module creates a checkout pane on the initial Checkout page that gives the user the option to either pickup their order for have it delivered. This is a simple radio button that will default to Pickup. When Pickup is selected, the Shipping address pane will be disabled and hidden. When delivery is chosen, normal commerce shipping rules will apply.
*/

/**
* Implements hook_help.
*
* Displays help and module information.
*
* @param path
*   Which path of the site we're using to display help
* @param arg
*   Array that holds the current path as returned from arg() function
*/
function pickup_or_delivery_help($path, $arg) {
  switch ($path) {
    case "admin/help#pickup_or_delivery":
      return '<p>'.  t("Creates a checkout pane on the initial Checkout page that gives the user the option to either pickup their order for have it delivered.") .'</p>';
      break;
  }
}

/**
* Implements hook_block_info().

function pickup_or_delivery_block_info() {
  $blocks['pickup_or_delivery'] = array(
    'info' => t('Pickup or Delivery'), //The name that will appear in the block list.
    'cache' => DRUPAL_CACHE_PER_ROLE, //Default
  );
  return $blocks;
}*/

/**
*
* if the radio button for Pickup or Delivery pane is set to Pickup (default) then disable the shipping page and pane
*/

/**
 * Implements hook_commerce_checkout_pane_info().
 
function pickup_or_delivery_commerce_checkout_pane_info() {
  $checkout_panes = array();

  $checkout_panes['pickup_or_delivery'] = array(
    'title' => t('Pickup or Delivery'),
    'base' => 'pickup_or_delivery_pane',
    'file' => 'includes/pickup_or_delivery.checkout_pane.inc',
    'page' => 'checkout',
    'weight' => 1,
    'review' => TRUE,
  );

  return $checkout_panes;
}*/

/*
* Hook hook_commerce_checkout_pane_info_alter($checkout_pane)
*/
function mymodule_commerce_checkout_pane_info_alter(&$checkout_pane) {
    global $user;
    // $checkout_pane actually holds ALL the panes...
    foreach($checkout_pane as $pane_name => &$pane_data) {
        // ...we only need to override one of them
        if($pane_name == 'customer_profile_shipping' && $pane_data['enabled']) {
            // load current order
            $order = commerce_cart_order_load($user->uid);
            // array $order->data was detected with dsm()
            // it doesn't contain anything except 'shipping_method' string element
            // rules_pick_up is the ID of a cloned flat_rate shipping method
            if($order->commerce_order_total['und']['0']['data']['components']['2']['name'] == 'pick_up') {
                // the pane is enabled by default, so we need to disable it
                $pane_data['enabled'] = 0;
            }
        }
    }
}























