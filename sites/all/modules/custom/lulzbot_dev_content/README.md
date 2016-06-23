# Dev Content

This module provides a simple way to add development content to a site. This
content is added from YAML files which help handle dependencies between
different pieces of content as well as some assumptions for how the content
is structure/provided.

When this module is re-enabled, it will run the migration, updating content as
needed.

Some things todo:

- handle images, files via URL/paths
- entity references by dev content machine names
- other various field type handling
- rollback functionality
- general refactoring

## Taxonomy terms

Taxonomy terms are very simple to add:

```yaml
---
  vocabulary: vocabulary_machine_name
  items:
    - name: Term
      id: 1
    - name: Term 2
      id: 2
```

Each term needs a unique ID which should not be reused.

## Nodes

Nodes can also be added:

```yaml
---
  entity_type: node
  bundle: article
  items:
    - id: 1
      title: Sample Article
      body: Lorem ipsum dolor sit amet, consectetur adipisicing elit
```

## Dependencies

Files can depend on other content files:

```yaml
---
  dependencies:
    - topics.yml
```

This file will only process after the other files have processed.
