(function ($) {
  // Store our function as a property of Drupal.behaviors.
  Drupal.behaviors.mySpecialFeature = {
    attach: function (context, settings) {
      // Your jQuery code here	
	  
	  	//overwriting the add to cart button when the store is closed
		if($("div.messages:contains('No orders can be placed at this time.')").length > 0){
			$(".commerce-add-to-cart div input.form-submit").replaceWith("<p>No orders can be placed at this time.</p>");
		}
		
		//adding the special instructions expandable functionality
		$(".field-name-field-instructions .form-textarea-wrapper").hide();
		$(".field-name-field-instructions label").addClass("special-instructions-jquery");
		$(".special-instructions-jquery").click(function() {
		  $(this).next(".field-name-field-instructions .form-textarea-wrapper").toggle("slow");
		});

	}
  };
}(jQuery));
