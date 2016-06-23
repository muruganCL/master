<?php

/**
 * @file
 * Default theme implementation to display a node.
 */

?>
<?php print $dev_deets; ?>
<article id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?>"<?php print $attributes; ?>>

  <div class="content"<?php print $content_attributes; ?>>

    <?php if (isset($content['field_printer_images'])): ?>
      <div class="compare--printer-image">
        <?php print render($content['field_printer_images']); ?>
      </div>
    <?php endif; ?>

    <div class="compare--printer-info">

      <?php if (isset($content['field_printer_ease_of_use'])): ?>
        <div class="ease-of-use">
          <?php print render($content['field_printer_ease_of_use']); ?>
        </div>
      <?php endif; ?>


      <?php print render($title_prefix); ?>
      <?php if (!$page): ?>
        <h3<?php print $title_attributes; ?>><?php print $title; ?></h3>
      <?php endif; ?>
      <?php print render($title_suffix); ?>

      <?php if (isset($content['product:commerce_price'])) : ?>
        <?php if (isset($content['product:original_price'])) : ?>
          <div class="original-price">
            <?php print render($content['product:original_price']); ?>
          </div>
        <?php endif; ?>
        <div class="price">
          <?php print render($content['product:commerce_price']); ?>
          <?php if (isset($content['product:tax_desc'])) : ?>
            <?php print render($content['product:tax_desc']); ?>
          <?php endif; ?>
        </div>
      <?php endif; ?>

      <?php
        // We hide the comments and links now so that we can render them later.
        hide($content['comments']);
        hide($content['links']);
        print render($content);
      ?>

      <a class="link--button-white" href="<?php print $node_url; ?>"><?php print t('View More'); ?></a>
    </div>
  </div>

  <?php print render($content['links']); ?>

  <?php print render($content['comments']); ?>

</article>
