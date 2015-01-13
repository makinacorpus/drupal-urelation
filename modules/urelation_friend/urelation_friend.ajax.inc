<?php

use Urelation\Relation;

/**
 * Action form.
 */
function urelation_friend_relation_action_form($form, &$form_state, Relation $relation, $action) {

  $form['#id']     = 'relation-action-' . $action;
  $form['#rel']    = $relation;
  $form['#action'] = $action;

  switch ($action) {

    case URELATION_ACTION_ACCEPT:
      $description = t("Do you wish to accept this relationship?");
      break;

    case URELATION_ACTION_DELETE:
      $description = t("Do you wish to delete this relationship?");
      break;

    case URELATION_ACTION_REFUSE:
      $description = t("Do you wish to refuse this relationship?");
      break;
  }

  $form = confirm_form($form, t("User confirmation"), '<front>', $description);

  $form['actions']['#attributes']['class'][]      = 'clearfix';
  $form['actions']['submit']['#ajax']['callback'] = 'urelation_friend_relation_action_form_submit_js';
  $form['actions']['submit']['#ajax']['wrapper']  = $form['#id'];

  return $form;
}

/**
 * Action form submit.
 */
function urelation_friend_relation_action_form_submit($form, &$form_state) {
  switch ($form['#action']) {

    case URELATION_ACTION_ACCEPT:
      $form['#rel']->approved = 1;
      urelation_save($form['#rel']->source, $form['#rel']->target, URELATION_FRIEND_BUNDLE, true);
      break;

    case URELATION_ACTION_DELETE:
    case URELATION_ACTION_REFUSE:
      urelation_delete($form['#rel']->source, $form['#rel']->target, URELATION_FRIEND_BUNDLE, true);
      break;
  }

  $form_state['done'] = true;
}

/**
 * Action form submit AJAX callback.
 */
function urelation_friend_relation_action_form_submit_js($form, &$form_state) {
  if (isset($form_state['done']) && $form_state['done']) {
    return array(
      '#type' => 'ajax',
      '#commands' => array(
        minidialog_ajax_command_close(true),
      ),
    );
  } else {
    return $form;
  }
}

/**
 * Cancel callback.
 */
function urelation_friend_relation_action_page(Relation $relation, $action, $mode = 'nojs') {

  switch ($action) {

    case URELATION_ACTION_ACCEPT:
      $title = t("Accept relationship");
      break;

    case URELATION_ACTION_DELETE:
      $title = t("Delete relationship");
      break;

    case URELATION_ACTION_REFUSE:
      $title = t("Refuse relationship");
      break;
  }

  if (isset($title)) {
    drupal_set_title($title);
  } else {
    return MENU_NOT_FOUND;
  }

  $form = drupal_get_form('urelation_friend_relation_action_form', $relation, $action);

  if ('ajax' === $mode) {
    ajax_deliver(array(
      '#type'     => 'ajax',
      '#commands' => array(
        minidialog_ajax_command_content($form),
        minidialog_ajax_command_open(),
      ),
    ));
  } else {
    return $form;
  }
}
