<div id="page" class="<?php print $classes; ?>">

  <?php include('page-header.inc'); ?>

  <div id="main">
    <?php if (isset($callout_image)) : ?>
      <div class="callout-image" <?php print ' style="background-image: url(' . $callout_image . ')"'; ?>></div>
    <?php endif; ?>

      <?php if ($messages): ?>
        <div id="messages" class="clearfix l--constrained">
            <?php print $messages; ?>
        </div>
      <?php endif; // end messages ?>

      <?php if ($page['above_content']): ?>
        <div id="above-content">
          <div class="l--constrained">
            <?php print render($page['above_content']); ?>
          </div>
        </div>
      <?php endif; // end Above Content ?>

      <div id="main-content" class="clearfix l--constrained-small">
        <div class="callout-header">
          <div class="meta">
            <?php if (isset($created)) : ?>
              <div class="date date-border">
                <?php print render($created); ?>
              </div>
            <?php endif; ?>
            <div class="share--wrapper">
              <a class="share--product toggle" href="#" aria-controls="social-media-links">
                <?php print t('Share'); ?>
              </a>
              <ul id="social-media-links" class="toggle-right">
                <li>
                  <a href="http://www.facebook.com/sharer/sharer.php?u=<?php print urlencode(url('node/' . $node->nid, array('absolute' => TRUE))); ?>" class="share--facebook facebook" target="_blank"><span></span></a>
                </li>
                <li>
                  <a href="http://www.twitter.com/share?url=<?php print urlencode(url('node/' . $node->nid, array('absolute' => TRUE))); ?>" class="share--twitter twitter" target="_blank"><span></span></a>
                </li>
              </ul>
            </div>
          </div>
          <?php if ($show_title && !$is_front && strlen($title) > 0): ?>
            <h1 <?php if (!empty($title_attributes)) print $title_attributes ?>>
              <?php print $title; ?>
            </h1>
          <?php endif; ?>
        </div>

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

        <?php if ($page['sidebar_first']): ?>
          <div id="sidebar-first" class="aside">
            <?php print render($page['sidebar_first']); ?>
          </div>
        <?php endif; // end sidebar_first ?>

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
