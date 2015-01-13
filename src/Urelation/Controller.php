<?php

namespace Urelation;

class Controller extends \DrupalDefaultEntityController
{
    public function load($ids = array(), $conditions = array())
    {
        $entities = array();

        // Create a new variable which is either a prepared version of the $ids
        // array for later comparison with the entity cache, or FALSE if no $ids
        // were passed. The $ids array is reduced as items are loaded from cache,
        // and we need to know if it's empty for this reason to avoid querying the
        // database when all requested entities are loaded from cache.
        $passed_ids = !empty($ids) ? array_flip($ids) : FALSE;

        if ($ids === FALSE || $ids || ($conditions && !$passed_ids)) {
            $result = $this
                ->buildQuery($ids, $conditions)
                ->execute();
            $result->setFetchMode(\PDO::FETCH_CLASS, '\Urelation\Relation');
            $queried_entities = $result->fetchAllAssoc($this->idKey);
        }

        // Pass all entities loaded from the database through $this->attachLoad(),
        // which attaches fields (if supported by the entity type) and calls the
        // entity type specific load callback, for example hook_node_load().
        if (!empty($queried_entities)) {
            $this->attachLoad($queried_entities);
            $entities += $queried_entities;
        }

        // Ensure that the returned array is ordered the same as the original
        // $ids array if this was passed in and remove any invalid ids.
        if ($passed_ids) {
            // Remove any invalid ids from the array.
            $passed_ids = array_intersect_key($passed_ids, $entities);
            foreach ($entities as $entity) {
                $passed_ids[$entity->{$this->idKey}] = $entity;
            }
            $entities = $passed_ids;
        }

        return $entities;
    }

    public function loadFromData(array $data)
    {
        
    }

    protected function attachLoad(&$queried_entities, $revision_id = false)
    {
        foreach ($queried_entities as $entity) {

            if ($entity->date_created) {
                $entity->date_created = \DateTime::createFromFormat(URELATION_PHP_DATETIME, $entity->date_created);
            }
            if ($entity->date_accepted) {
                $entity->date_accepted = \DateTime::createFromFormat(URELATION_PHP_DATETIME, $entity->date_accepted);
            }
        }

        parent::attachLoad($queried_entities, $revision_id);
    }

    protected function buildQuery($ids, $conditions = array(), $revision_id = false)
    {
        $query = parent::buildQuery($ids, $conditions, $revision_id);

        $query->innerJoin('urelation_type', 'bundle', "bundle.id = base.type");
        $query->condition('bundle.is_active', 1);
        $query->addField('bundle', 'bundle');

        return $query;
    }
}
