<?php

/**
 * Provides a views area handler that can display line item summary with total
 * using specified components
 */
class commerce_price_components_handler_area_line_item_summary extends commerce_line_item_handler_area_line_item_summary {

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form += commerce_price_components_settings_form($this->options);
    $form['commerce_price_components']['#states'] = array(
      'invisible' => array(
        'input[name="options[info][total]"]' => array('checked' => FALSE),
      )
    );
  }

  function option_definition() {
    $options = parent::option_definition();
    $components = commerce_price_component_titles();

    foreach ($components as $key => $component) {
      $options['commerce_price_components']['default'][$key] = $key == 'base_price' ? TRUE : '';
    };

    return $options;
  }

function render($empty = FALSE) {
  // Most of this is forked from
  // commerce_line_item_handler_area_line_item_summary.
    if (!$empty) {
      // Build an array of line item IDs from the View results that we will load
      // and use for calculating totals.
      $line_item_ids = array();

      foreach ($this->view->result as $result) {
        $line_item_id = $this->get_value($result);
        if ($line_item_id) {
          $line_item_ids[] = $line_item_id;
        }
      }

      $line_items = commerce_line_item_load_multiple($line_item_ids);

      // Add total information and the line item summary links.
      $quantity = commerce_line_items_quantity($line_items);
      $total = commerce_line_items_total($line_items);
      $currency = commerce_currency_load($total['currency_code']);

      $links = array();

      foreach (commerce_line_item_summary_links() as $name => $link) {
        if ($this->options['links'][$name] === $name && $link['access']) {
          $links[str_replace('_', '-', 'line-item-summary-' . $name)] = $link;
        }
      }

      // Build the variables array to send to the template.
      $variables = array(
        'view' => $this->view,
        'links' => theme('links', array('links' => $links, 'attributes' => array('class' => array('links', 'inline')))),
      );
      if ($this->options['info']['quantity']) {
        $variables = array(
          'quantity_raw' => $quantity,
          'quantity_label' => format_plural($quantity, 'item', 'items', array(), array('context' => 'product count on a Commerce order')),
          'quantity' => format_plural($quantity, '1 item', '@count items', array(), array('context' => 'product count on a Commerce order')),
        ) + $variables;
      }
      if ($this->options['info']['total']) {
        $component_total_amount = 0;
        // Calculate component price.
        foreach ($line_items as $line_item) {
          $lang = field_language('commerce_line_item', $line_item, 'commerce_unit_price');
          $components = $line_item->commerce_unit_price[$lang][0]['data']['components'];

          // Only count enabled components
          foreach ($components as $key => $component) {
            if (!$this->options['commerce_price_components'][$component['name']]) {
              unset($components[$key]);
            }
          }

          $total['data']['components'] = $components;
          $component_total = commerce_price_component_total($total);

          // Tally line item component price amounts.
          $component_total_amount += $component_total['amount'] * (isset($line_item->quantity) ? $line_item->quantity : 1);
        }

        $variables = array(
          'total_raw' => number_format(commerce_currency_round($total['amount'], $currency), $currency['decimals']),
          'total_label' => t('Total:'),
          'total' => commerce_currency_format($component_total_amount, $total['currency_code'], $this->view),
        ) + $variables;
      }

      return theme('commerce_line_item_summary', $variables);
    }

    return '';
  }
}
