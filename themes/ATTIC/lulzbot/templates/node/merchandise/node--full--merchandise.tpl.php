<?php

/**
 * @file
 * Merchandise full theme implementation to display a node.
 */

?>
<?php print $dev_deets; ?>
<article id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?>"<?php print $attributes; ?>>

  <div class="content"<?php print $content_attributes; ?>>

    <section id="product" class="product-section">
      <div class="l--constrained">
        <?php if (isset($content['field_merchandise_images'])) : ?>
        <div class="section-primary">
          <div class="field--item field--field_merchandise_images">
            <div class="product--gallery">
              <?php print render($content['field_merchandise_images']); ?>
            </div>
          </div>
        </div>
        <?php endif; ?>


        <?php if (isset($content['body'])) : ?>
        <div class="section-secondary">

          <?php if (isset($content['field_printer_ease_of_use'])) : ?>
            <div class="field--item field--field_printer_ease_of_use">
              <?php print render($content['field_printer_ease_of_use']); ?>
            </div>
          <?php endif; ?>

          <?php print render($title_prefix); ?>
            <h1<?php print $title_attributes; ?>><?php print $title; ?></h1>
          <?php print render($title_suffix); ?>

          <div class="product-info clearfix">
            <div class="product-info--primary clearfix">
              <?php if (isset($content['field_merchandise_alerts'])) : ?>
                <a href="#" class="toggle alert-toggle" aria-controls="alert">Product Alert <span class="alert-count"> (<?php print render($content['alert_count']); ?>)</span></a>
                <div id="alert" aria-expanded="false">
                  <div>
                    <?php print render($content['field_merchandise_alerts']); ?>
                  </div>
                </div>
              <?php endif; ?>

              <?php print render($content['body']); ?>

              <?php if (isset($content['field_merchandise_reviews'])) : ?>
                <a href="#reviews" class="review-promo-link link--go link--text"><?php print t('Read our Reviews'); ?></a>
              <?php endif; ?>

              <?php if (isset($content['field_merchandise_note_body'])) : ?>
                <?php if (isset($content['field_merchandise_note_title'])) : ?><span class="review-promo-link"><?php print render($content['field_merchandise_note_title']); ?></span><?php endif; ?>
                <span class="tooltip-anchor" data-tooltip-positions="top;bottom;right" data-tooltip='<div><?php if (isset($content['field_merchandise_note_title'])) : ?><div class="note-title"><?php print render($content['field_merchandise_note_title']); ?></div><?php endif; ?><?php if (isset($content['field_merchandise_note_body'])) : ?><div class="note-message"><?php print render($content['field_merchandise_note_body']); ?></div><?php endif; ?></div>'>?</span>
              <?php endif; ?>
            </div>

            <div class="product-info--secondary">
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
              <div class="share--wrapper">
                <a class="share--product toggle" href="#" aria-controls="social-media-links">
                  <?php print t('Share'); ?>
                </a>
                <ul id="social-media-links">
                  <li>
                    <a href="http://www.facebook.com/sharer/sharer.php?u=<?php print urlencode(url('node/' . $node->nid, array('absolute' => TRUE))); ?>" class="share--facebook facebook" target="_blank"><span></span></a>
                  </li>
                  <li>
                    <a href="http://www.twitter.com/share?url=<?php print urlencode(url('node/' . $node->nid, array('absolute' => TRUE))); ?>" class="share--twitter twitter" target="_blank"><span></span></a>
                  </li>
                </ul>
              </div>
            </div>
            <?php if (isset($content['field_product_reference'])) : ?>
              <div class="clearfix"></div>
              <div class="field--item field--field_product_reference">
                <?php print render($content['field_product_reference']); ?>
              </div>
            <?php endif; ?>
          </div>
        </div>
        <?php endif; ?>
      </div>

      <?php if ($field_merchandise_bg_triangle['und'][0]['value']): ?>
        <div class="top-triangle-left"></div>
      <?php endif; ?>
    </section>

    <section id="related">
      <div class="l--constrained clearfix">
        <?php if (isset($content['field_merchandise_learning_links'])) : ?>
          <div class="section--primary">
            <div class="callout learn-with-community">
              <h3 class="callout-title"><?php print t('Learn with the Community'); ?></h3>
                <div class="link--list">
                  <?php print render($content['field_merchandise_learning_links']); ?>
                </div>
            </div>
          </div>
        <?php endif; ?>
        <div class="section--secondary">
          <?php if (isset($content['field_merchandise_related_prods'])) : ?>

            <h4><?php print t('Related Products'); ?></h4>
            <div class="field--field_merchandise_related_prods related-products product-reference-2">
              <?php print render($content['field_merchandise_related_prods']); ?>
            </div>
          <?php endif; ?>
        </div>
      </div>
    </section>

    <?php if (
      isset($content['field_merchandise_video_title']) ||
      isset($content['field_merch_video_description']) ||
      isset($content['field_merchandise_video'])
    ): ?>
      <section id="video" class="feature product-section <?php if (isset($video_classes)) { print $video_classes; } ?>">
        <?php if (isset($video_background)) : ?>
          <div class="feature-parallax" <?php print ' style="background-image: url(' . $video_background . ')"'; ?>></div>
        <?php endif; ?>
        <div class="l--constrained">
          <div class="section-primary">
            <?php if (isset($content['field_merchandise_video_title'])) : ?>
              <div class="field--item field--field_merchandise_video_title heading--large">
                <?php print render($content['field_merchandise_video_title']); ?>
              </div>
            <?php endif; ?>

            <?php if (isset($content['field_merch_video_description'])) : ?>
              <div class="field--item field--field_merch_video_description">
                <?php print render($content['field_merch_video_description']); ?>
              </div>
            <?php endif; ?>
          </div>
          <?php if (isset($content['field_merchandise_video'])) : ?>
            <div class="section-secondary">
              <div class="field--item field--field_merchandise_video">
                <?php print render($content['field_merchandise_video']); ?>
              </div>
            </div>
          <?php endif; ?>
        </div>
      </section>
    <?php endif; ?>

    <?php if (
      !isset($content['field_merchandise_video_title']) &&
      !isset($content['field_merch_video_description']) &&
      !isset($content['field_merchandise_video'])
    ): ?>
    <div class="l--constrained">
      <div class="separator-rule"></div>
    </div>
    <?php endif; ?>

    <?php if (isset($content['field_merchandise_reviews'])) : ?>
    <section id="reviews" class="product-section l--constrained">

      <?php if (isset($content['field_product_reference']) || isset($content['field_printer_images'])) : ?>
      <div class="section--primary">
        <?php if (isset($content['first_product_image'])) : ?>
          <div class="field--item first-product-image">
            <?php print render($content['first_product_image']); ?>
          </div>
        <?php endif; ?>

        <?php print render($title_prefix); ?>
          <h3 class="heading--ruled"><?php print $title; ?></h3>
        <?php print render($title_suffix); ?>

        <?php if (isset($content['product:commerce_price'])) : ?>
        <div class="price">
          <?php print render($content['product:commerce_price']); ?>
        </div>
        <?php endif; ?>

        <?php if (isset($content['field_product_reference'])) : ?>
          <div class="field--field_product_reference product-reference-2">
            <?php print render($content['field_product_reference']); ?>
          </div>
        <?php endif; ?>
      </div>
      <?php endif; ?>

      <?php if (isset($content['field_merchandise_reviews'])) : ?>
        <div class="section--secondary">
          <h3 class="heading--large"><?php print t('Product Reviews'); ?></h3>
          <div class="field--item field--field_merchandise_reviews">
            <?php print render($content['field_merchandise_reviews']); ?>
          </div>
        </div>
      <?php endif; ?>
    </section>
    <?php endif; ?>


    <?php
      // We hide the comments and links now so that we can render them later.
      hide($content['comments']);
      hide($content['links']);
      hide($content['first_product_image']);
      hide($content['alert_count']);
      print render($content);
    ?>
  </div>

  <?php print render($content['links']); ?>

  <?php print render($content['comments']); ?>

</article>
