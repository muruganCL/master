<?php

/**
 * @file
 * Default theme implementation to display a node.
 */

?>
<?php print $dev_deets; ?>
<article id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?>"<?php print $attributes; ?>>

  <div class="content"<?php print $content_attributes; ?>>

    <div class="support--primary">
      <?php if (isset($image)) : ?>
        <a href="<?php print $node_url; ?>">
          <?php print render($image); ?>
        </a>
      <?php endif; ?>
    </div>

    <div class="support--secondary">
      <?php print render($title_prefix); ?>
      <?php if (!$page): ?>
        <h2<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h2>
      <?php endif; ?>
      <?php print render($title_suffix); ?>

      <?php if (isset($product_type)) : ?>
        <div class="support--type">
          <?php print render($product_type); ?>
        </div>
      <?php endif; ?>

      <?php if (isset($description)) : ?>
        <div class="support--description">
          <?php print render($description); ?>
        </div>
      <?php endif; ?>
    </div>

    <?php
      // We hide the comments and links now so that we can render them later.
      hide($content['comments']);
      hide($content['links']);
      print render($content);
    ?>
  </div>

</article>
