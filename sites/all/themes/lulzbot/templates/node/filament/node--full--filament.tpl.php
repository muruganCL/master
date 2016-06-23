<?php

/**
 * @file
 * tool head full theme implementation to display a node.
 */

?>
<?php print $dev_deets; ?>
<article id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?>"<?php print $attributes; ?>>

  <div class="content"<?php print $content_attributes; ?>>


    <section id="product" class="product-section">
      <div class="l--constrained">
        <?php if (isset($content['field_filament_images'])) : ?>
        <div class="section-primary">
          <div class="field--item field--field_filament_images">
            <div class="product--gallery">
              <?php print render($content['field_filament_images']); ?>
            </div>
          </div>
        </div>
        <?php endif; ?>


        <?php if (isset($content['body'])) : ?>
        <div class="section-secondary">

          <?php if (isset($content['field_filament_ease_of_use'])) : ?>
            <div class="field--item ease-of-use field--field_filament_ease_of_use">
              <?php print render($content['field_filament_ease_of_use']); ?>
            </div>
          <?php endif; ?>

          <?php print render($title_prefix); ?>
            <h1<?php print $title_attributes; ?>><?php print $title; ?> <?php if (isset($content['field_filament_supplier'])) : ?><span class="supplier">by <?php print render($content['field_filament_supplier']); ?></span><?php endif; ?></h1>
          <?php print render($title_suffix); ?>

          <?php if (isset($content['field_filament_width']) || isset($content['field_filament_weight'])) : ?>
            <div class="filament-width-weight">
              <?php if (isset($content['field_filament_width'])) : ?>
                <?php print render($content['field_filament_width']); ?>
              <?php endif; ?>

              <?php if (isset($content['field_filament_weight'])) : ?>
                , <?php print render($content['field_filament_weight']); ?>
              <?php endif; ?>
            </div>
            <div class="title-rule"></div>
          <?php endif; ?>

          <div class="product-info clearfix">
            <div class="product-info--primary clearfix">
              <?php if (isset($content['field_filament_alerts'])) : ?>
                <a href="#" class="toggle alert-toggle" aria-controls="alert">Product Alert <span class="alert-count"> (<?php print render($content['alert_count']); ?>)</span></a>
                <div id="alert" aria-expanded="false">
                  <div>
                    <?php print render($content['field_filament_alerts']); ?>
                  </div>
                </div>
              <?php endif; ?>

              <?php print render($content['body']); ?>

              <?php if (isset($content['field_filament_compatiblity'])) : ?>
                <div class="compatibility">
                  <em><?php print t('Works with'); ?>:</em> <?php print render($content['field_filament_compatiblity']); ?>
                </div>
              <?php endif; ?>

              <?php if (isset($content['field_filament_reviews'])) : ?>
                <a href="#reviews" class="review-promo-link link--go link--text"><?php print t('Read our Reviews'); ?></a>
              <?php endif; ?>

              <?php if (isset($support_links)) : ?>
                <?php print render($support_links); ?>
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
            <div class="clearfix"></div>
            <?php if (isset($content['field_product_reference'])) : ?>

              <div class="field--item field--field_product_reference">
                <?php print render($content['field_product_reference']); ?>
              </div>
            <?php endif; ?>
            <ul class="accordion">
              <?php if (isset($content['field_filament_features'])) : ?>
                <li>
                  <a href="#" class="heading--thin accordion-toggle toggle" aria-controls="features-panel"><span class="toggle-icon"></span><?php print t('Features'); ?></a>
                  <div class="accordion-panel">
                    <?php print render($content['field_filament_features']); ?>
                  </div>
                </li>
              <?php endif; ?>
              <?php if (isset($content['field_filament_specifications'])) : ?>
                <li>
                  <a href="#" class="heading--thin accordion-toggle toggle" aria-controls="specs-panel"><span class="toggle-icon"></span><?php print t('Parts &amp; Specifications'); ?></a>
                  <div class="accordion-panel">
                    <?php print render($content['field_filament_specifications']); ?>
                  </div>
                </li>
              <?php endif; ?>
              <?php if (isset($content['field_filament_documentation'])) : ?>
                <li>
                  <a href="#" class="heading--thin accordion-toggle toggle" aria-controls="resources-panel"><span class="toggle-icon"></span><?php print t('Resources &amp; Documentation'); ?></a>
                  <div class="accordion-panel">
                    <?php print render($content['field_filament_documentation']); ?>
                  </div>
                </li>
              <?php endif; ?>
            </ul>
          </div>
        </div>
        <?php endif; ?>
      </div>
      <?php if ($field_filament_bg_triangle['und'][0]['value']): ?>
        <div class="top-triangle-left"></div>
      <?php endif; ?>
    </section>

    <section id="related">
      <div class="l--constrained clearfix">
        <?php if (isset($content['field_filament_learning_links'])) : ?>
          <div class="section--primary">
            <div class="callout learn-with-community">
              <h3 class="callout-title"><?php print t('Learn with the Community'); ?></h3>
                <div class="link--list">
                  <?php print render($content['field_filament_learning_links']); ?>
                </div>
            </div>
          </div>
        <?php endif; ?>
        <div class="section--secondary">
          <?php if (isset($content['field_filament_related_filaments'])) : ?>

            <h4><?php print t('Alternative Filaments'); ?></h4>
            <div class="field--field_filament_related_filaments related-products product-reference-2">
              <?php print render($content['field_filament_related_filaments']); ?>
            </div>
          <?php endif; ?>
        </div>
      </div>
    </section>

    <?php if (
      isset($content['field_filament_video_title']) ||
      isset($content['field_filament_video_description']) ||
      isset($content['field_filament_video'])
    ): ?>
      <section id="video" class="feature product-section <?php if (isset($video_classes)) { print $video_classes; } ?>">
        <?php if (isset($video_background)) : ?>
          <div class="feature-parallax" <?php print ' style="background-image: url(' . $video_background . ')"'; ?>></div>
        <?php endif; ?>
        <div class="l--constrained">
          <div class="section-primary">
            <?php if (isset($content['field_filament_video_title'])) : ?>
              <div class="field--item field--field_filament_video_title heading--large">
                <?php print render($content['field_filament_video_title']); ?>
              </div>
            <?php endif; ?>

            <?php if (isset($content['field_filament_video_description'])) : ?>
              <div class="field--item field--field_filament_video_description">
                <?php print render($content['field_filament_video_description']); ?>
              </div>
            <?php endif; ?>
          </div>
          <?php if (isset($content['field_filament_video'])) : ?>
            <div class="section-secondary">
              <div class="field--item field--field_filament_video">
                <?php print render($content['field_filament_video']); ?>
              </div>
            </div>
          <?php endif; ?>
        </div>
      </section>
    <?php endif; ?>

    <?php if (isset($content['field_filament_reviews'])) : ?>

    <?php if (
      !isset($content['field_filament_video_title']) &&
      !isset($content['field_filament_video_description']) &&
      !isset($content['field_filament_video'])
    ): ?>
    <div class="l--constrained">
      <div class="separator-rule"></div>
    </div>
    <?php endif; ?>

    <section id="reviews" class="product-section l--constrained">

      <?php if (isset($content['field_product_reference']) || isset($content['field_filament_images'])) : ?>
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

      <?php if (isset($content['field_filament_reviews'])) : ?>
        <div class="section--secondary">
          <h3 class="heading--large"><?php print t('Product Reviews'); ?></h3>
          <div class="field--item field--field_filament_reviews">
            <?php print render($content['field_filament_reviews']); ?>
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
