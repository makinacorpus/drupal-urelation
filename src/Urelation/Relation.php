<?php

namespace Urelation;

class Relation
{
    /**
     * Relationship identifier
     *
     * @var int
     */
    public $id;

    /**
     * Relationship type identifier
     *
     * @var int
     */
    public $type = 0;

    /**
     * Relationship type string identifier for entity API
     *
     * @var string
     */
    public $bundle = URELATION_BUNDLE_DEFAULT;

    /**
     * Account that owns the relationship identifier
     *
     * @var int
     */
    public $source;

    /**
     * Account targetted by the relationship identifier
     *
     * @var int
     */
    public $target;

    /**
     * Is the relationship bidirectional
     *
     * @var int
     */
    public $is_bidirectional = 0;

    /**
     * @var \DateTime
     */
    public $date_created;

    /**
     * @var \DateTime
     */
    public $date_accepted;
}
