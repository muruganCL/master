<?php

/**
 * @file
 * Default theme implementation to display a node.
 */

?>
<?php print $dev_deets; ?>
<article id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?>"<?php print $attributes; ?>>

  <span class="promo-image"<?php if (isset($promo_background)) { print ' style="background-image: url(' . $promo_background . ')"';} ?>></span>


  <?php if (isset($content['promo_type'])) : ?>
    <div class="promo-type">
      <?php print render($content['promo_type']); ?>
    </div>
  <?php endif; ?>

  <?php print render($title_prefix); ?>
  <?php if (!$page): ?>
    <h4<?php print $title_attributes; ?>><?php print $title; ?></h4>
  <?php endif; ?>
  <?php print render($title_suffix); ?>

  <div class="promo-slideout">

    <?php if (isset($content['promo_type_slideout'])) : ?>
      <div class="promo-type-slideout">
        <?php print render($content['promo_type_slideout']); ?>
      </div>
    <?php endif; ?>

    <?php if (isset($content['title_slideout'])) : ?>
      <h4 class="promo-title-slideout heading--link-text">
        <a href="<?php print $node_url; ?>"><?php print render($content['title_slideout']); ?></a>
      </h4>
    <?php endif; ?>

    <?php if (isset($content['body'])) : ?>
      <div class="promo-content">
        <?php print render($content['body']); ?>
      </div>
    <?php endif; ?>

    <a class="promo-link" href="<?php print $node_url; ?>"><?php print t('Learn More'); ?></a>
  </div>

  <a class="promo-image-link" href="<?php print $node_url; ?>"></a>

    <?php
      // We hide the comments and links now so that we can render them later.
      hide($content['comments']);
      hide($content['links']);
      hide($content['field_in_the_news_image']);
      hide($content['field_forum_post_image']);
      hide($content['field_event_image']);
      hide($content['field_announcement_image']);
      hide($content['field_case_study_image']);
      hide($content['field_tutorial_image']);
      print render($content);
    ?>

</article>
