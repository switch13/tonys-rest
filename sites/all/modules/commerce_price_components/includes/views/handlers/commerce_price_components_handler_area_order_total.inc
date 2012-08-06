<?php

/**
 * Defines an order total area handler that shows the order total field with its
 *   components listed in the footer of a View.
 */
class commerce_price_components_handler_area_order_total extends views_handler_area {

  function option_definition() {
    $options = parent::option_definition();

    $components = commerce_price_component_titles();

    foreach ($components as $key => $component) {
      $options['commerce_price_components']['default'][$key] = $key == 'base_price' ? TRUE : '';
    };

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form += commerce_price_components_settings_form($this->options);
    $form['commerce_price_components']['#states'] = array(
      'invisible' => array(
        'input[name="options[info][total]"]' => array('checked' => FALSE),
      )
    );
  }

  function render($empty = FALSE) {
    if (!$empty) {
      // First look for an order_id argument.
      foreach ($this->view->argument as $name => $argument) {
        if ($argument instanceof commerce_order_handler_argument_order_order_id) {
          // If it is single value...
          if (count($argument->value) == 1) {
            // Load the order.
            $order = commerce_order_load(reset($argument->value));

            // Get the components to filter those not selected.
            $components = $order->commerce_order_total[LANGUAGE_NONE][0]['data']['components'];

            // Only count enabled components
            foreach ($components as $key => $component) {
              if (!$this->options['commerce_price_components'][$component['name']]) {
                unset($components[$key]);
              }
            }

            // Calculate the correct order total for the current components.
            $order->commerce_order_total[LANGUAGE_NONE][0]['data']['components'] = $components;
            $price = commerce_price_component_total($order->commerce_order_total[LANGUAGE_NONE][0]);
            $price['data']['components'] = $components;
            $order->commerce_order_total[LANGUAGE_NONE][0] = $price;            

            // Prepare a display settings array.
            $display = array(
              'label' => 'hidden',
              'type' => 'commerce_price_formatted_components',
              'settings' => array(
                'calculation' => FALSE,
              ),
            );

            // Render the order's order total field with the current display.
            $field = field_view_field('commerce_order', $order, 'commerce_order_total', $display);

            return '<div class="commerce-order-handler-area-order-total">' . drupal_render($field) . '</div>';
          }
        }
      }
    }

    return '';
  }

}
