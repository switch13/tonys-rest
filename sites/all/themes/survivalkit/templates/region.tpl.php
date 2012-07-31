<?php
// $Id: region.tpl.php,v 1.1.2.2 2011/01/22 22:41:16 timplunkett Exp $

/**
 * @file
 * Default theme implementation to display a region.
 */
?>
<?php if ($content): ?>
  <section id="<?php print $region; ?>" class="<?php print $classes; ?>">
    <?php print $content; ?>
  </section>
<?php endif; ?>
