<?php
// $Id: region--footer.tpl.php,v 1.1.2.2 2011/01/22 23:25:40 timplunkett Exp $

/**
 * @file
 * Default theme implementation to display a region.
 */
?>
<?php if ($content): ?>
  <footer id="<?php print $region; ?>" class="<?php print $classes; ?> clearfix">
    <?php print $content; ?>
  </footer>
<?php endif; ?>
