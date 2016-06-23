# CINC Display

Manage display settings with CINC using an entity-specific interface.

## Usage

Create or update a module and add `dependencies[] = cinc_display` to your module's info file.

Next, add `hook_cinc_display_apply`:

```
function example_module_cinc_display_apply() {
  // update default/full settings for the page content type
  CINCDisplay::init('page')
    ->field('field_author_image', 'image.image_image')
    ->setImageStyle('field_author_image', 'medium')
    ->field('field_author')
    ->field('body')
    ->update();

  CINCDisplay::init('page', 'teaser')
    ->field('field_author')
    ->field('body', 'text_summary_or_trimmed')
    ->field('field_topic', array(
        'type' => 'taxonomy_link',
        'module' => 'taxonomy',
      ))
    ->update();
}
```

By default, fields not listed will be hidden but you can also explicitly hide
fields:

```
CINCDisplay::init('page', 'teaser')
  ->field('field_author')
  ->field('body', 'text_summary_or_trimmed')
  ->hide('field_author_image')
  ->update();
```

CINC Display will apply a field's default formatter and settings if you don't specify options. Currently, CINCDisplay ties into cinc_yaml functionality so after the CINC YAML config is applied, CINCDisplay will invoke `hook_cinc_display_apply`.

**Experimental:** you can copy another display:

```
$default = CINCDisplay::init('page')
  ...;

$teaser = CINCDisplay::cloneDisplay($default, 'page', 'teaser')
  ...;
```
