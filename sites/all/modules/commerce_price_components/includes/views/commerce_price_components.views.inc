<?php

function commerce_price_components_views_data() {

  // Define a handler for an area used to summarize a set of line items.
  $data['commerce_line_item']['line_item_summary_component'] = array(
    'title' => t('Line item summary (component)'),
    'help' => t('Summarize the line items in a View with an optional link to checkout. Order total may compute from individual components'),
    'area' => array(
      'handler' => 'commerce_price_components_handler_area_line_item_summary',
    ),
  );

  // Define a handler for an area used to summarize a set of line items.
  $data['commerce_order']['order_total_component'] = array(
    'title' => t('Order total (component)'),
    'help' => t('Displays the order total field formatted with its components list; requires an Order ID argument. You can filter individual components.'),
    'area' => array(
      'handler' => 'commerce_price_components_handler_area_order_total',
    ),
  );

  return $data;
}
