<header id="header">
  <div class="l--constrained clearfix">
    <div id="branding">
      <h1><a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" id="logo">
        <img class="logo--regular" src="<?php echo $logo_svg; ?>" alt="<?php echo $site_name; ?>" onerror="this.onerror=null; this.src='<?php echo $logo_png; ?>'">
        <img class="logo--small" src="<?php echo $logo_small_svg; ?>" alt="<?php echo $site_name; ?>" onerror="this.onerror=null; this.src='<?php echo $logo_small_png; ?>'">
      </a></h1>

      <button class="header-toggle toggle" aria-expanded="false" aria-controls="header-drawer">
        <span class="menu-toggle-icon">
          <span></span>
        <?php //echo t('Menu') ?>
        </span>
      </button>

    </div>

    <?php if ($page['navigation']): ?>
      <div id="navigation">
          <?php print render($page['navigation']); ?>
      </div>
    <?php endif; // end navigation?>


    <?php if ($page['utility'] || $page['header']) : ?>
      <div id="utility">
    <?php endif; ?>
        <?php if ($page['utility']): ?>
          <div>
            <?php print render($page['utility']); ?>
          </div>
        <?php endif; // end utility ?>

        <?php if ($page['header']): ?>
            <?php print render($page['header']); ?>
        <?php endif; // end header ?>

        <?php include('util-nav.inc'); ?>

        <a href="/cart"><span class="cart" data-grunticon-embed>
          <?php if (isset($cart_items_num) && $cart_items_num > 0) : ?>
            <span class="cart-item-count"><?php print render($cart_items_num); ?></span>
          <?php endif; ?>
        </span>
        </a>
    <?php if ($page['utility'] || $page['header']) : ?>
      </div>
    <?php endif; ?>
  </div>
</header>

<div id="header-drawer" class="header-drawer" aria-expanded="false">
  <div class="header-utilities clearfix">

    <div class="drawer-utlitly-nav clearfix">
      <?php include('util-nav.inc'); ?>
    </div>

    <?php if (isset($page['header']['search_form'])): ?>
      <?php echo render($page['header']['search_form']); ?>
    <?php endif; // search ?>
  </div>
  <nav class="drawer-menu">
    <?php if (isset($page['navigation']['system_main-menu'])): ?>
      <?php print render($page['navigation']['system_main-menu']); ?>
    <?php endif; ?>

  </nav>

  <?php if (isset($page['footer']['bean_footer_social'])): ?>
    <?php print render($page['footer']['bean_footer_social_drawer']); ?>
  <?php endif; ?>
</div>
<div id="header-overlay"></div>
