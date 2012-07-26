<?php

/**
 * @file
 * Callback functions for the Pickup or delivery's checkout pane.
 */


/**
 * Checkout pane callback: builds Pickup or delivery's radio button form.
 */
function pickup_or_delivery_pane_checkout_form($form, &$form_state, $checkout_pane, $order) {
	$pane_form = array();

	$pickup = array('pickup' => t('Pickup'), 'delivery' => t('Delivery'));
	
	// Add a radios element to let the customer select a shipping service.
    $pane_form['pickup_or_delivery'] = array(
      '#type' => 'radios',
      '#options' => $pickup,
      '#default_value' => variable_get('pickup_or_delivery', 'pickup'),
      '#ajax' => array(
        'callback' => 'pickup_or_delivery_commerce_checkout_pane_info_alter'
      ),
    );
	
	return $pane_form;
};

function pickup_or_delivery_commerce_checkout_pane_info_alter(&$checkout_panes) {
	$pickup_or_delivery = $form_state['values']['pickup_or_delivery'];
	
	if($pickup_or_delivery == "pickup"){
		$checkout_panes['customer_profile_shipping']['enabled'] = 0;
		$checkout_panes['commerce_shipping']['enabled'] = 0;
	}else{
		$checkout_panes['customer_profile_shipping']['enabled'] = 1;
		$checkout_panes['commerce_shipping']['enabled'] = 1;
	}
}

