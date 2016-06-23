<?php

/**
 * @file
 * Default theme implementation to display a node.
 */

?>
<?php print $dev_deets; ?>
<article id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?>"<?php print $attributes; ?>>

  <?php if (isset($created)) : ?>
    <div class="date">
      <?php print render($created); ?>
    </div>
  <?php endif; ?>

  <?php print render($title_prefix); ?>
  <?php if (!$page): ?>
    <div<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></div>
  <?php endif; ?>
  <?php print render($title_suffix); ?>

</article>
