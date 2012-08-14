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
	
	// Add a radios element to let the customer select whether they would like pickup or delivery.
    $pane_form['pickup_or_delivery'] = array(
      '#type' => 'radios',
      '#options' => $pickup,
      '#default_value' => variable_get('pickup_or_delivery', 'pickup'),
      '#ajax' => array(
        'callback' => 'pickup_or_delivery_commerce_checkout_pane_info_alter'
      ),
    );
	
	return $pane_form;
}


/**
 * Implements hook_commerce_checkout_pane_info_alter().
 
function pickup_or_delivery_commerce_checkout_pane_info_alter(&$checkout_panes) {
	$pickup_or_delivery = $form_state['values']['pickup_or_delivery'];
	
	if($pickup_or_delivery == "pickup"){
		$checkout_panes['customer_profile_shipping']['enabled'] = 0;
		$checkout_panes['commerce_shipping']['enabled'] = 0;
	}else{
		$checkout_panes['customer_profile_shipping']['enabled'] = 1;
		$checkout_panes['commerce_shipping']['enabled'] = 1;
	}
	
*/

	/******return $form['commerce_shipping']['service_details'];**/
/*}*/

function pickup_or_delivery_commerce_checkout_pane_info_alter(&$checkout_panes) {
    global $user;
    // $checkout_pane actually holds ALL the panes...
    foreach($checkout_pane as $pane_name => &$pane_data) {
        // ...we only need to override one of them
        if($pane_name == 'customer_profile_shipping' && $pane_data['enabled']) {
			$pickup_or_delivery_value = $form_state['values']['pickup_or_delivery'];
					echo "
     
					   <script type='text/javascript'>
					 
						   alert('This is a test. $pickup_or_delivery_value');
					 
					   </script>
					 
					";

			if($pickup_or_delivery_value == "pickup"){
				    echo "
     
					   <script type='text/javascript'>
					 
						   alert('This is a test.');
					 
					   </script>
					 
					";
				$checkout_panes['customer_profile_shipping']['enabled'] = 0;
				$checkout_panes['commerce_shipping']['enabled'] = 0;
			}else{
				$checkout_panes['customer_profile_shipping']['enabled'] = 1;
				$checkout_panes['commerce_shipping']['enabled'] = 1;
			}
        }
    }
}

/**
 * Checkout pane callback: submit the pickup_or_delivery pane.
 */
function pickup_or_delivery_pane_checkout_form_submit($form, &$form_state, $checkout_pane, $order) {
	$pickup_or_delivery = $form_state['values']['pickup_or_delivery'];
	
	if($pickup_or_delivery == "pickup"){
		$checkout_panes['customer_profile_shipping']['enabled'] = 0;
		$checkout_panes['commerce_shipping']['enabled'] = 0;
	}else{
		$checkout_panes['customer_profile_shipping']['enabled'] = 1;
		$checkout_panes['commerce_shipping']['enabled'] = 1;
	}
}