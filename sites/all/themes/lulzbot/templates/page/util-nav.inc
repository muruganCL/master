<nav class="utility-nav">
  <ul class="nav">
    <?php if ($user->uid): ?>
      <li><a href="/user/<?php print $user->uid; ?>/orders" title="My Account">My Account</a></li>
      <li><a href="/user/logout" title="Log out">Log out</a></li>
    <?php else: ?>
      <li><a href="/user/login" title="Log in">Log in</a></li>
      <li><a href="/user/register" title="Register">Register</a></li>
    <?php endif; ?>
  </ul>
</nav>
