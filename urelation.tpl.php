<div class="relation<?php echo $is_active ? ' active' : ''; ?>">
  <?php echo render($target_picture); ?>
  <div class="user-info">
    <?php echo render($target_name); ?>
  </div>
  <div class="actions">
    <?php echo render($links); ?>
  </div>
</div>