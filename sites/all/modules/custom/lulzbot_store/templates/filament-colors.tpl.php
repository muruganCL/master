<?php
if (isset($variables['element']['#nid'])):
  $nid = $variables['element']['#nid'];
elseif (arg(0) === 'node' && is_numeric(arg(1))):
  $nid = arg(1);
endif;
?>

<input type="hidden" id="<?php echo $variables['element']['#id']; ?>" name="<?php echo $variables['element']['#name']; ?>" value="<?php echo $variables['element']['#value']; ?>">

<ul class="filament-colors">
  <?php foreach ($variables['element']['#options'] as $value => $option): ?>
    <?php $classes = array(); ?>
    <?php
    if ($variables['element']['#value'] == $value):
      $classes[] = 'active';
    endif;
    if (!in_array($value, array_keys($variables['element']['#available_colors']))):
      $classes[] = 'unavailable';
    endif;
    $classes = implode(' ', $classes);
    if ($classes):
      $classes = ' ' . $classes;
    endif;
    ?>
    <li class="filament-color<?php echo $classes; ?>">
      <img src="/filament-color-image/<?php echo $nid; ?>/<?php echo $value; ?>" alt="<?php echo $option; ?>" />
      <span><?php echo $option; ?></span>
      <a href="?product_filament_colors=<?php echo $value; ?>" class="link--filament-color" data-color="<?php echo $value; ?>"></a>
    </li>
  <?php endforeach; ?>
</ul>
