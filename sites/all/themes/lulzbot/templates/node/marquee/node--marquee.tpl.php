<?php

/**
 * @file
 * Default theme implementation to display a node.
 */

?>
<?php print $dev_deets; ?>
<article id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?>"<?php print $attributes; ?>>

  <?php print render($title_prefix); ?>
  <?php if (!$page): ?>
    <!--<h2<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h2>-->
  <?php endif; ?>
  <?php print render($title_suffix); ?>

  <div class="content"<?php print $content_attributes; ?>>

    <?php if (isset($content['field_marquee_image'])) : ?>
      <div class="marquee-image marquee--primary">
        <?php print render($content['field_marquee_image']); ?>
      </div>
    <?php endif; ?>

    <?php if (isset($content['field_marquee_links']) || isset($content['field_marquee_image'])) : ?>
    <div class="marquee--secondary">
    <?php endif; ?>

      <?php if (isset($content['body'])) : ?>
        <div class="marquee-content">
          <?php print render($content['body']); ?>
        </div>
      <?php endif; ?>

      <?php if (isset($content['field_marquee_links'])) : ?>
        <div class="marquee-links">
          <?php print render($content['field_marquee_links']); ?>
        </div>
      <?php endif; ?>

    <?php if (isset($content['field_marquee_links']) || isset($content['field_marquee_image'])) : ?>
    </div>
    <?php endif; ?>

    <?php
      // We hide the comments and links now so that we can render them later.
      hide($content['comments']);
      hide($content['links']);
      print render($content);
    ?>
  </div>

  <?php print render($content['links']); ?>

  <?php print render($content['comments']); ?>

</article>
