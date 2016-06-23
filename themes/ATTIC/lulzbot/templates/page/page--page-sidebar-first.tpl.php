<div id="page" class="<?php print $classes; ?>">

  <?php include('page-header.inc'); ?>

  <div id="main">
    <?php if (isset($callout_image)) : ?>
      <div class="basic-page--image" <?php print ' style="background-image: url(' . $callout_image . ')"'; ?>>
        <div class="basic-page--header">
          <div class="l--constrained-small">
            <?php if ($show_title && !$is_front && strlen($title) > 0): ?>
              <h1 <?php if (!empty($title_attributes)) print $title_attributes ?>>
                <?php print $title; ?>
              </h1>
            <?php endif; ?>

            <?php if (isset($intro)) : ?>
            <div class="basic-page--intro">
              <?php print render($intro); ?>
            </div>
            <?php endif; ?>

            <?php if ($page['above_content']): ?>
              <div id="above-content" class="basic-page--intro">
                <?php print render($page['above_content']); ?>
              </div>
            <?php endif; // end Above Content ?>

          </div>
        </div>
      </div>
    <?php endif; ?>

    <?php if (!isset($callout_image)): ?>
      <div class="l--constrained page-header">
        <?php if ($show_title && !$is_front && strlen($title) > 0): ?>
          <h1 <?php if (!empty($title_attributes)) print $title_attributes ?>>
            <?php print $title; ?>
          </h1>
        <?php endif; ?>

        <?php if (isset($intro)) : ?>
          <?php print render($intro); ?>
        <?php endif; ?>

        <?php if ($page['above_content']): ?>
          <div id="above-content">
            <?php print render($page['above_content']); ?>
          </div>
        <?php endif; // end Above Content ?>

      </div>
    <?php endif; ?>

      <?php if ($messages): ?>
        <div id="messages" class="clearfix l--constrained">
            <?php print $messages; ?>
        </div>
      <?php endif; // end messages ?>

      <div id="main-content" class="clearfix l--constrained-small">

        <?php if ($page['sidebar_first']): ?>
          <div id="sidebar-first" class="aside">
            <?php print render($page['sidebar_first']); ?>
          </div>
        <?php endif; // end sidebar_first ?>

        <div id="content">

          <?php if (render($tabs)): ?>
            <div id="tabs">
              <?php print render($tabs); ?>
            </div>
          <?php endif; // end tabs ?>

          <?php if ($page['highlighted']): ?>
            <div id="highlighted">
              <div class="l--constrained">
                <?php print render($page['highlighted']); ?>
              </div>
            </div>
          <?php endif; // end highlighted ?>

          <?php if ($page['help']): ?>
            <div id="help">
              <?php print render($page['help']); ?>
            </div>
          <?php endif; // end help ?>

          <?php print render($page['content']); ?>
        </div>

        <?php if ($page['sidebar_second']): ?>
          <div id="sidebar-second" class="aside">
            <?php print render($page['sidebar_second']); ?>
          </div>
        <?php endif; // end sidebar_second ?>
      </div>

      <?php if ($page['below_content']): ?>
        <div id="below-content">
          <div class="l--constrained">
            <?php print render($page['below_content']); ?>
          </div>
        </div>
      <?php endif; // end Below Content ?>
    </div>

  <?php include('page-footer.inc'); ?>
</div>
