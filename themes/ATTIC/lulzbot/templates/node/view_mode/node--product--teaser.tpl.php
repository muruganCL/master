<?php

/**
 * @file
 * Default theme implementation to display a node.
 */

?>
<?php print $dev_deets; ?>
<article id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?>"<?php print $attributes; ?>>

  <?php if (isset($content['field_part_images'])): ?>
    <figure class="product--teaser-image">
      <?php print render($content['field_part_images'][0]); ?>
    </figure>
  <?php endif; ?>

  <?php if (isset($content['field_merchandise_images'])): ?>
    <figure class="product--teaser-image">
      <?php print render($content['field_merchandise_images'][0]); ?>
    </figure>
  <?php endif; ?>

  <?php if (isset($content['field_tool_head_images'])): ?>
    <figure class="product--teaser-image">
      <?php print render($content['field_tool_head_images'][0]); ?>
    </figure>
  <?php endif; ?>

  <?php if (isset($content['field_filament_images'])): ?>
    <figure class="product--teaser-image">
      <?php print render($content['field_filament_images'][0]); ?>
    </figure>
  <?php endif; ?>

  <?php print render($title_prefix); ?>
  <?php if (!$page): ?>
    <h4<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h4>
    <?php if (isset($content['field_filament_supplier'])): ?>
      <?php print render($content['field_filament_supplier']); ?>
    <?php endif; ?>
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

  <div class="content"<?php print $content_attributes; ?>>
    <?php
      // We hide the comments and links now so that we can render them later.
      hide($content['comments']);
      hide($content['links']);
      hide($content['field_part_images']);
      hide($content['field_merchandise_images']);
      hide($content['field_tool_head_images']);
      hide($content['field_filament_images']);
      print render($content);
    ?>
    <a class="link--button" href="<?php print $node_url; ?>"><?php print t('Buy Now'); ?></a>
  </div>

</article>
