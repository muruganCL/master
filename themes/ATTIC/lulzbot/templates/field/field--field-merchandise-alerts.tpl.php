<?php if (isset($rows)): ?>
  <ul class="list--ruled">
  <?php foreach($rows as $row): ?>
    <li>
      <?php if (isset($row['field_alert_name'])) : ?>
        <div class="alert-title heading--bold"><?php print render($row['field_alert_name']); ?></div>
      <?php endif; ?>

      <?php if (isset($row['field_alert_name'])) : ?>
        <div class="alert-content">
          <?php print render($row['field_alert_message']); ?>
        </div>
      <?php endif; ?>
    </li>
  <?php endforeach; ?>
  </ul>
<?php endif; ?>
