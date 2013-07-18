<?php
/**
 * @file
 * timelinejs_content_types.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function timelinejs_content_types_taxonomy_default_vocabularies() {
  return array(
    'timeline_category' => array(
      'name' => 'Timeline Category',
      'machine_name' => 'timeline_category',
      'description' => 'Category for timeline events',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
      'rdf_mapping' => array(
        'rdftype' => array(
          0 => 'skos:ConceptScheme',
        ),
        'name' => array(
          'predicates' => array(
            0 => 'dc:title',
          ),
        ),
        'description' => array(
          'predicates' => array(
            0 => 'rdfs:comment',
          ),
        ),
      ),
    ),
  );
}
