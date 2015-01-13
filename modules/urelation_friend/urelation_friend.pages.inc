<?php

/**
 * User relation overview.
 *
 * @param object $account
 */
function urelation_friend_account_page($account) {
  $build = array();

  $q = db_select('urelation', 'r');
  $q->addField('r', 'id');
  $q->condition('r.source', $account->uid);
  $q->condition('r.is_bidirectional', 1);
  $q->orderBy('r.date_created');

  if ($list = $q->execute()->fetchCol()) {
    $relations = entity_load(URELATION_ENTITY_TYPE, $list);
    $build['list'] = urelation_view_multiple($relations);
  } else {
    $build['empty'] = array(
      '#markup' => t("You have no relations yet"), 
      '#prefix' => '<p>',
      '#suffix' => '</p>',
    );
  }

  return $build;
}

/**
 * User relation overview.
 *
 * @param object $account
 */
function urelation_friend_account_pending_page($account) {
  $build = array();

  $q = db_select('urelation', 'r');
  $q->addField('r', 'id');
  $q->condition('r.source', $account->uid);
  $q->condition('r.is_bidirectional', 0);
  $q->orderBy('r.date_created');

  if ($list = $q->execute()->fetchCol()) {
    $relations = entity_load(URELATION_ENTITY_TYPE, $list);
    $build['list'] = urelation_view_multiple($relations);
  } else {
    $build['empty'] = array(
      '#markup' => t("You have no pending relationships"), 
      '#prefix' => '<p>',
      '#suffix' => '</p>',
    );
  }

  return $build;
}

/**
 * User relation overview.
 *
 * @param object $account
 */
function urelation_friend_account_requests_page($account) {
  $build = array();

  $q = db_select('urelation', 'r');
  $q->addField('r', 'id');
  $q->condition('r.target', $account->uid);
  $q->condition('r.is_bidirectional', 0);
  $q->orderBy('r.date_created');

  if ($list = $q->execute()->fetchCol()) {
    $relations = entity_load(URELATION_ENTITY_TYPE, $list);
    $build['list'] = urelation_view_multiple($relations);
  } else {
    $build['empty'] = array(
      '#markup' => t("You have no pending relationship requests"), 
      '#prefix' => '<p>',
      '#suffix' => '</p>',
    );
  }

  return $build;
}
