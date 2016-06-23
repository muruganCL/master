<?php
/**
 * @file
 * Printer specs template (field_printer_display_specs)
 */
?>
<table class="printer-specs">
  <?php /* Added here so that the table has meaning, probably should be hidden on the FE */ ?>
  <thead>
    <tr>
      <th>
        LulzBot Mini Specifications
      </th>
      <th>
        Specification
      </th>
      <th>
        LulzBot TAZ Specifications
      </th>
    </tr>
  </thead>
  <tbody>
    <?php foreach ($rows as $row): ?>
      <tr>
        <td data-title="<?php print render($row[0]); ?>">
          <?php print render($row[1]); ?>
        </td>
        <th>
          <?php print render($row[0]); ?>
        </th>
        <td data-title="<?php print render($row[0]); ?>">
          <?php print render($row[2]); ?>
        </td>
      </tr>
    <?php endforeach; ?>
  </tbody>
</table>

<div class="printer-specs-mobile">
  <div class="mini-printer-specs">
    <?php foreach ($rows as $row): ?>
    <div class="comparison--row">
      <div class="comparison--label">
        <?php print render($row[0]); ?>
      </div>
      <div class="comparison--specs">
        <?php print render($row[1]); ?>
      </div>
    </div>
    <?php endforeach; ?>
  </div>

  <div class="taz-printer-specs">
    <?php foreach ($rows as $row): ?>
    <div class="comparison--row">
      <div class="comparison--label">
        <?php print render($row[0]); ?>
      </div>
      <div class="comparison--specs">
        <?php print render($row[2]); ?>
      </div>
    </div>
    <?php endforeach; ?>
  </div>
</div>
