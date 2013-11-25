<?php
/**
 * @file
 * timelinejs_content_types.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function timelinejs_content_types_default_rules_configuration() {
  $items = array();
  $items['rules_generate_timeline_era_navigation_dates'] = entity_import('rules_config', '{ "rules_generate_timeline_era_navigation_dates" : {
      "LABEL" : "Generate Timeline Era Navigation Dates",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "TimelineJS" ],
      "REQUIRES" : [ "rules" ],
      "ON" : { "node_insert" : [] },
      "IF" : [
        { "node_is_of_type" : {
            "node" : [ "node" ],
            "type" : { "value" : { "timelinejs_era" : "timelinejs_era" } }
          }
        }
      ],
      "DO" : [
        { "entity_create" : {
            "USING" : {
              "type" : "node",
              "param_type" : "timelinejs_dates",
              "param_title" : "[node:title]",
              "param_author" : [ "node:author" ]
            },
            "PROVIDE" : { "entity_created" : { "new_timelinejs_date" : "New Date" } }
          }
        },
        { "data_set" : {
            "data" : [ "new-timelinejs-date:field-timeline-category" ],
            "value" : [ "node:field-timeline-category" ]
          }
        },
        { "data_set" : {
            "data" : [ "new-timelinejs-date:field-dates" ],
            "value" : [ "node:field-dates" ]
          }
        },
        { "data_set" : {
            "data" : [ "new-timelinejs-date:field-custom-class-name" ],
            "value" : "era-navigation-class"
          }
        },
        { "entity_save" : { "data" : [ "new-timelinejs-date" ] } }
      ]
    }
  }');
  return $items;
}
