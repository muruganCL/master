<?php
/**
 * @file
 * Default theme implementation for beans.
 *
 * Available variables:
 * - $content: An array of comment items. Use render($content) to print them all, or
 *   print a subset such as render($content['field_example']). Use
 *   hide($content['field_example']) to temporarily suppress the printing of a
 *   given element.
 * - $title: The (sanitized) entity label.
 * - $url: Direct url of the current entity if specified.
 * - $page: Flag for the full page state.
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. By default the following classes are available, where
 *   the parts enclosed by {} are replaced by the appropriate values:
 *   - entity-{ENTITY_TYPE}
 *   - {ENTITY_TYPE}-{BUNDLE}
 *
 * Other variables:
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 *
 * @see template_preprocess()
 * @see template_preprocess_entity()
 * @see template_process()
 */
?>
<div class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>

  <div class="content"<?php print $content_attributes; ?>>

    <?php if (isset($content['field_store_category_promo_text'])) : ?>
      <div class="store--category-description">
        <?php print render($content['field_store_category_promo_text']); ?>
      </div>
    <?php endif; ?>

    <?php if (isset($content['field_store_category_link'])) : ?>
      <div class="link--go--container">
        <?php print render($content['field_store_category_link']); ?>
      </div>
    <?php endif; ?>

    <?php if (isset($content['field_store_category_products'])) : ?>
      <div class="">
        <?php print render($content['field_store_category_products']); ?>
      </div>
    <?php endif; ?>

    <?php
      print render($content);
    ?>
  </div>
</div>
