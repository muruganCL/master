<figure class="gallery-item">

  <a class="gallery-original-image" href="<?php print render($variables['original']); ?>" data-size="<?php print render($variables['original_width']); ?>x<?php print render($variables['original_height']); ?>">
    <?php if (isset($variables['thumb'])) : ?>
      <img src="<?php print render($variables['thumb']); ?>" />
    <?php endif; ?>
  </a>
</figure>
