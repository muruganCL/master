<div id="footer">
  <div class="l--constrained clearfix footer">
    <div class="ruled-top"></div>
    <div class="logo-footer"></div>
    <div class="footer-content">
      <?php print render($page['footer']); ?>
      <div class="clearfix"></div>
      <?php if(isset($copyright)): ?>
        <?php print render($copyright); ?>
      <?php endif; ?>
    </div>
  </div>
</div>

<div class="footer-triangle-large"></div>
<div class="footer-triangle-small"></div>

<?php if ($page['admin_footer']): ?>
  <div id="admin-footer" class="l--constrained">
    <?php print render($page['admin_footer']); ?>
  </div>
<?php endif; // end admin_footer ?>
