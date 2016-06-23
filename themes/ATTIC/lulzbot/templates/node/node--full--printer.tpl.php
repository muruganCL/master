<?php

/**
 * @file
 * printer full theme implementation to display a node.
 */

?>
<?php print $dev_deets; ?>
<article id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?>"<?php print $attributes; ?>>

  <div class="content"<?php print $content_attributes; ?>>


    <section id="product" class="product-section">
      <div class="l--constrained">

        <?php if (isset($content['field_printer_images'])) : ?>
        <div class="section-primary">
          <div class="field--item field--field_printer_images product-gallery--printer" itemscope itemtype="http://schema.org/ImageGallery">
            <?php print render($content['field_printer_images']); ?>
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
            <div class="field--item field--body product-info--primary">
              <?php if (isset($content['field_printer_alerts'])) : ?>
                <a href="#" class="toggle alert-toggle" aria-controls="alert">Product Alert <span class="alert-count"> (<?php print render($content['alert_count']); ?>)</span></a>
                <div id="alert" aria-expanded="false">
                  <div>
                    <?php print render($content['field_printer_alerts']); ?>
                  </div>
                </div>
              <?php endif; ?>

              <?php print render($content['body']); ?>
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
          </div>

          <?php if (isset($content['field_product_reference'])) : ?>
            <div class="field--item field--field_product_reference">
              <?php print render($content['field_product_reference']); ?>
            </div>
          <?php endif; ?>

          <div class="review--promo">
            <?php if (isset($review_images_tiny)): ?>
            <ul class="review-promo-images">
              <li><?php print render($review_images_tiny[0]); ?></li>
              <li><?php print render($review_images_tiny[1]); ?></li>
              <li><?php print render($review_images_tiny[2]); ?></li>
            </ul>
            <?php endif; ?>
            <?php if (isset($content['field_printer_reviews'])) : ?>
              <a href="#reviews" class="review-promo-link link--go link--text"><?php print t('Read our Reviews'); ?></a>
            <?php endif; ?>

          </div>

        </div>
        <?php endif; ?>

        <div class="clearfix"></div>

        <?php if (isset($content['field_printer_images_thumbnails'])) : ?>
        <div class="product-thumbnails">
          <?php print render($content['field_printer_images_thumbnails']); ?>
        </div>
        <?php endif; ?>

      </div>
      <?php if (isset($field_printer_bg_triangle['und'][0]['value'])): ?>
        <div class="top-triangle-left"></div>
      <?php endif; ?>
    </section>

    <div class="text--center">
      <a href="#" class="heading--thin product-toggle toggle" aria-controls="details"><span class="toggle-icon"></span><?php print t('Parts &amp; Specifications'); ?></a>
    </div>
    <section id="details" class="product-section l--constrained" aria-expanded="false">
      <?php if (isset($content['field_printer_parts_specs1'])) : ?>
        <div class="field--item field--field_printer_parts_specs1">
          <?php print render($content['field_printer_parts_specs1']); ?>
        </div>
      <?php endif; ?>

      <?php if (isset($content['field_printer_parts_specs2'])) : ?>
        <div class="field--item field--field_printer_parts_specs2">
          <?php print render($content['field_printer_parts_specs2']); ?>
        </div>
      <?php endif; ?>

      <?php if (isset($content['field_printer_parts_specs3'])) : ?>
        <div class="field--item field--field_printer_parts_specs3">
          <?php print render($content['field_printer_parts_specs3']); ?>
        </div>
      <?php endif; ?>
    </section>

    <section id="feature1" class="feature product-section <?php if (isset($feature1_classes)) { print $feature1_classes; } ?>">
      <?php if (isset($feature1_background)) : ?>
        <div class="feature-parallax" <?php print ' style="background-image: url(' . $feature1_background . ')"'; ?>></div>
      <?php endif; ?>
      <div class="l--constrained">
        <div class="section-primary">
          <?php if (isset($content['field_printer_fc1_text'])) : ?>
            <div class="field--item field--field_printer_fc1_text heading--large">
              <?php print render($content['field_printer_fc1_text']); ?>
            </div>
          <?php endif; ?>

          <?php if (isset($content['field_printer_fc1_description'])) : ?>
            <div class="field--item field--field_printer_fc1_description">
              <?php print render($content['field_printer_fc1_description']); ?>
            </div>
          <?php endif; ?>

          <?php if (isset($content['field_printer_fc1_link'])) : ?>
            <div class="field--item field--field_printer_fc1_link field--button--teritary">
              <?php print render($content['field_printer_fc1_link']); ?>
            </div>
          <?php endif; ?>
        </div>
      </div>
    </section>

    <section id="feature2" class="feature product-section <?php if (isset($feature2_classes)) { print $feature2_classes; } ?>">
      <?php if (isset($feature2_background)) : ?>
        <div class="feature-parallax" <?php print ' style="background-image: url(' . $feature2_background . ')"'; ?>></div>
      <?php endif; ?>

      <div class="l--constrained clearfix">
        <div class="section-primary">
          <?php if (isset($content['field_printer_fc2_image'])) : ?>
            <div class="field--item field--field_printer_fc2_image feature--image-left">
              <?php print render($content['field_printer_fc2_image']); ?>
            </div>
          <?php endif; ?>
        </div>

        <div class="column-secondary">
          <div class="section-secondary">
            <?php if (isset($content['field_printer_fc2_text'])) : ?>
              <div class="field--item field--field_printer_fc2_text heading--large">
                <?php print render($content['field_printer_fc2_text']); ?>
              </div>
            <?php endif; ?>

            <?php if (isset($content['field_printer_fc2_description'])) : ?>
              <div class="field--item field--field_printer_fc2_description">
                <?php print render($content['field_printer_fc2_description']); ?>
              </div>
            <?php endif; ?>

            <?php if (isset($content['field_printer_fc2_link'])) : ?>
              <div class="field--item field--field_printer_fc2_link link--go--container">
                <?php print render($content['field_printer_fc2_link']); ?>
              </div>
            <?php endif; ?>
          </div>

          <div class="section-tertiary">
            <?php if (isset($content['field_printer_fc2_rel_title'])) : ?>
              <h4 class="field--item field--field_printer_fc2_rel_title">
                <?php print render($content['field_printer_fc2_rel_title']); ?>
              </h4>
            <?php endif; ?>

            <?php if (isset($content['field_printer_fc2_products'])) : ?>
              <div class="field--item field--field_printer_fc2_products">
                <?php print render($content['field_printer_fc2_products']); ?>
              </div>
            <?php endif; ?>
          </div>
        </div>
      </div>
    </section>

    <section id="feature3" class="feature product-section <?php if (isset($feature3_classes)) { print $feature3_classes; } ?>">
      <?php if (isset($feature3_background)) : ?>
        <div class="feature-parallax" <?php print ' style="background-image: url(' . $feature3_background . ')"'; ?>></div>
      <?php endif; ?>
      <div class="l--constrained">
        <div class="section-primary">
          <?php if (isset($content['field_printer_fc3_text'])) : ?>
            <div class="field--item field--field_printer_fc3_text heading--large">
              <?php print render($content['field_printer_fc3_text']); ?>
            </div>
          <?php endif; ?>

          <?php if (isset($content['field_printer_fc3_description'])) : ?>
            <div class="field--item field--field_printer_fc3_description">
              <?php print render($content['field_printer_fc3_description']); ?>
            </div>
          <?php endif; ?>

          <?php if (isset($content['field_printer_fc3_image'])) : ?>
            <div class="field--item field--field_printer_fc3_image">
              <?php print render($content['field_printer_fc3_image']); ?>
            </div>
          <?php endif; ?>

          <?php if (
            isset($content['field_printer_fc3_link']) ||
            isset($support_links)
           ) : ?>
            <div class="field--item field--field_printer_fc3_link link--list">

              <?php if (isset($content['field_printer_fc3_link'])) : ?>
                <?php print render($content['field_printer_fc3_link']); ?>
              <?php endif; ?>

              <?php if (isset($support_links)) : ?>
                <?php print render($support_links); ?>
              <?php endif; ?>

            </div>
          <?php endif; ?>

        </div>
        <?php if (isset($content['field_printer_fc3_video'])) : ?>
          <div class="section-secondary">
            <div class="field--item field--field_printer_fc3_video">
              <?php print render($content['field_printer_fc3_video']); ?>
            </div>
          </div>
        <?php endif; ?>
      </div>
    </section>

  <?php if (isset($content['field_printer_reviews'])) : ?>
    <section id="reviews" class="product-section l--constrained">

      <?php if (isset($content['field_product_reference']) || isset($content['field_printer_images'])) : ?>
        <div class="section--primary">
          <?php if (isset($content['field_printer_images'])) : ?>
            <div class="field--item field--field_printer_images product-gallery--printer" itemscope itemtype="http://schema.org/ImageGallery">
              <?php print render($content['field_printer_images']); ?>
            </div>
          <?php endif; ?>

          <?php print render($title_prefix); ?>
            <h3 class="heading--ruled"><?php print $title; ?></h3>
          <?php print render($title_suffix); ?>

          <?php if (isset($content['product:original_price'])) : ?>
          <div class="original-price">
            <?php print render($content['product:original_price']); ?>
          </div>
          <?php endif; ?>

          <?php if (isset($content['product:commerce_price'])) : ?>
          <div class="price">
            <?php print render($content['product:commerce_price']); ?>
            <?php if (isset($content['product:tax_desc'])) : ?>
              <?php print render($content['product:tax_desc']); ?>
            <?php endif; ?>
          </div>
          <?php endif; ?>

          <?php if (isset($content['field_product_reference'])) : ?>
            <div class="field--field_product_reference product-reference-2">
              <?php print render($content['field_product_reference']); ?>
            </div>
          <?php endif; ?>
        </div>
      <?php endif; ?>

      <?php if (isset($content['field_printer_reviews'])) : ?>
        <div class="section--secondary">
          <h3 class="heading--large"><?php print t('Product Reviews'); ?></h3>
          <div class="field--item field--field_printer_reviews">
            <?php print render($content['field_printer_reviews']); ?>
          </div>
        </div>
      <?php endif; ?>
    </section>
  <?php endif; ?>


    <?php
      // We hide the comments and links now so that we can render them later.
      hide($content['comments']);
      hide($content['links']);
      hide($content['field_printer_fc1_image']);
      hide($content['field_printer_fc3_bg_image']);
      hide($content['field_printer_reviews']);
      hide($content['alert_count']);
      print render($content);
    ?>
  </div>

  <?php print render($content['links']); ?>

  <?php print render($content['comments']); ?>

</article>
