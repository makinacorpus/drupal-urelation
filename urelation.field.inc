<?php

/**
 * Relation field type.
 */
const URELATION_FIELD = 'urelation';

/**
 * Field caching limit variable name.
 */
const URELATION_VAR_FIELD_THRESHOLD = 'urelation_field_threshold';

/**
 * Field caching limit default value.
 */
const URELATION_FIELD_THRESHOLD = 100;

/**
 * Implements hook_field_info().
 */
function urelation_field_info() {
  return array(
    URELATION_FIELD => array(
      'label'             => t("Relations"),
      'description'       => t("User relations."),
      'settings'          => array(),
      'instance_settings' => array(),
      'default_widget'    => URELATION_FIELD,
      'default_formatter' => URELATION_FIELD,
      'no_ui'             => true,
    ),
  );
}

/**
 * Implements hook_field_formatter_info().
 */
function urelation_field_formatter_info() {
  return array(
    URELATION_FIELD => array(
      'label'       => t("Hidden"),
      'description' => t("Relation field has no formatter."),
      'field types' => array(URELATION_FIELD),
    ),
  );
}

/**
 * Implements hook_field_formatter_info().
 */
function urelation_field_widget_info() {
  return array(
    URELATION_FIELD => array(
      'label'       => t("Hidden"),
      'description' => t("Relation field has no widget."),
      'field types' => array(URELATION_FIELD),
    ),
  );
}

/**
 * Implements hook_field_widget_form().
 */
function urelation_field_widget_form(&$form, &$form_state, $field, $instance, $langcode, $items, $delta, $element) {
  return array();
}

/**
 * Implements hook_field_formatter_view().
 */
function urelation_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  return array();
}

/**
 * Implements hook_field_load().
 */
function urelation_field_load($entity_type, $entities, $field, $instances, $langcode, &$items, $age) {
  switch ($field['type']) {

    case URELATION_FIELD:
      if ('user' === $entity_type) {
        $relations = db_select('urelation', 'r')
          ->fields('r', array('id', 'type', 'source', 'target', 'is_bidirectional'))
          ->condition('r.source', array_keys($entities))
          ->orderBy('r.source')
          ->orderBy('r.type')
          ->orderBy('r.date_created')
          ->execute()
          ->fetchAll();
        foreach ($relations as $relation) {
          $items[$relation->source][] = (array)$relation;
        }
      }
      break;
  }
}

/**
 * Implements hook_field_is_empty().
 */
function urelation_field_is_empty($item, $field) {
  return false;
}
