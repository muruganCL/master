<?php if (isset($rows)): ?>
  <ul class="reviews ">
  <?php foreach($rows as $row): ?>
    <li>
    <figure class="review">
      <div class="item-content">
        <blockquote>
            <div>"<?php print render($row['field_review_quote']); ?>"</div>
        </blockquote>
        <figcaption><span class="dash"></span> <?php print render($row['field_review_name']); ?>, <span class="review-title"><?php print render($row['field_review_title']); ?></span></figcaption>
      </div>
      <?php if ($row['field_review_image']): ?>
        <div class="review-img"><?php print render($row['field_review_image']); ?></div>
      <?php endif; ?>
    </figure>
    </li>
  <?php endforeach; ?>
  </ul>
<?php endif; ?>
