<?php

/**
 * @file
 * Default theme implementation to display a node.
 */

?>
<?php print $dev_deets; ?>
<article id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?>"<?php print $attributes; ?>>

  <div class="content"<?php print $content_attributes; ?>>

    <?php if (isset($content['field_merchandise_images'])): ?>
      <div class="filament-image content-primary">
        <?php print render($content['field_merchandise_images'][0]); ?>
      </div>
    <?php endif; ?>

    <div class="content-secondary">
      <?php print render($title_prefix); ?>
      <?php if (!$page): ?>
        <div <?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></div>
      <?php endif; ?>
      <?php print render($title_suffix); ?>

      <?php if (isset($content['product:commerce_price'])): ?>
        <?php if (isset($content['product:original_price'])) : ?>
          <div class="original-price">
            <?php print render($content['product:original_price']); ?>
          </div>
        <?php endif; ?>
        <div class="price--gray">
          <?php print render($content['product:commerce_price']); ?>
          <?php if (isset($content['product:tax_desc'])) : ?>
            <?php print render($content['product:tax_desc']); ?>
          <?php endif; ?>
        </div>
      <?php endif; ?>
    </div>

    <?php
      // We hide the comments and links now so that we can render them later.
      hide($content['comments']);
      hide($content['links']);
      hide($content['product:field_product_tshirt_image']);
      print render($content);
    ?>
  </div>

  <?php print render($content['links']); ?>

  <?php print render($content['comments']); ?>

</article>
