<?php

/**
 * @file
 * support full theme implementation to display a node.
 */

?>
<?php print $dev_deets; ?>
<article id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?>"<?php print $attributes; ?>>

  <div class="content"<?php print $content_attributes; ?>>


    <section id="product" class="product-section">
      <div class="l--constrained">
        <?php if (isset($product_ref['field_images'])) : ?>
        <div class="section-primary">
          <div class="field--item field--field_images">
            <div class="product--gallery">
              <?php print render($product_ref['field_images']); ?>
            </div>
          </div>
        </div>
        <?php endif; ?>

        <div class="section-secondary">

          <?php if (isset($product_ref['field_ease_of_use'])) : ?>
            <div class="field--item field--ease_of_use">
              <?php print render($product_ref['field_ease_of_use']); ?>
            </div>
          <?php endif; ?>

          <?php print render($title_prefix); ?>
            <h1<?php print $title_attributes; ?>><?php print $title; ?></h1>
          <?php print render($title_suffix); ?>

          <div class="product-info clearfix">
            <div class="clearfix">
              <?php if (isset($content['field_part_alerts'])) : ?>
                <a href="#" class="toggle alert-toggle" aria-controls="alert">Product Alert <span class="alert-count"> (<?php print render($content['alert_count']); ?>)</span></a>
                <div id="alert" aria-expanded="false">
                  <div>
                    <?php print render($content['field_part_alerts']); ?>
                  </div>
                </div>
              <?php endif; ?>

              <?php if (isset($product_ref['body'])) : ?>
                <?php print render($product_ref['body']); ?>
              <?php endif; ?>

              <?php if (isset($product_ref['field_compatiblity'])) : ?>
                <div class="filament-compatibility">
                  <em><strong><?php print t('Works with'); ?>:</strong></em> <?php print render($product_ref['field_compatiblity']); ?>
                </div>
              <?php endif; ?>

              <div class="support--links">
                <a class="link--go" href="/<?php print drupal_get_path_alias('node/' . $product_ref['#node']->nid); ?>"><?php print t('@product Product Page', array('@product' => $product_ref['#node']->title)); ?></a>

                <a class="link--go" href="https://forum.lulzbot.com"><?php print t('Visit the Forums'); ?></a>
              </div>

              <?php if (isset($content['field_part_reviews'])) : ?>
                <a href="#reviews" class="review-promo-link link--go link--text"><?php print t('Read our Reviews'); ?></a>
              <?php endif; ?>

            </div>
            <div class="clearfix"></div>
            <?php if (isset($content['field_product_reference'])) : ?>

              <div class="field--item field--field_product_reference">
                <?php print render($content['field_product_reference']); ?>
              </div>
            <?php endif; ?>
            <ul class="accordion">
              <?php if (isset($product_ref['field_features'])) : ?>
                <li>
                  <a href="#" class="heading--thin accordion-toggle toggle" aria-controls="features-panel"><span class="toggle-icon"></span><?php print t('Features'); ?></a>
                  <div class="accordion-panel">
                    <?php print render($product_ref['field_features']); ?>
                  </div>
                </li>
              <?php endif; ?>
              <?php if (isset($product_ref['field_specifications'])) : ?>
                <li>
                  <a href="#" class="heading--thin accordion-toggle toggle" aria-controls="specs-panel"><span class="toggle-icon"></span><?php print t('Parts &amp; Specifications'); ?></a>
                  <div class="accordion-panel">
                    <?php print render($product_ref['field_specifications']); ?>
                  </div>
                </li>
              <?php endif; ?>
              <?php if (isset($content['field_support_downloads'])) : ?>
                <li>
                  <a href="#" class="heading--thin accordion-toggle toggle" aria-controls="resources-panel"><span class="toggle-icon"></span><?php print t('Downloads'); ?></a>
                  <div class="accordion-panel">
                    <?php print render($content['field_support_downloads']); ?>
                  </div>
                </li>
              <?php endif; ?>
            </ul>
          </div>
        </div>
      </div>
      <div class="top-triangle-left"></div>
    </section>

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

  <?php //print views_embed_view('related_documentation','block', $product_ref['#node']->nid); ?>

</article>
