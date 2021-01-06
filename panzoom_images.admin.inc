<?php
/**
 * @file
 * Admin callbacks for the Panzoom module.
 */

/**
 * Page callback: Panzoom Config Sets List.
 */
function panzoom_images_config_sets_list() {
  $config_set_options = panzoom_images_get_configuration_set_options();

  if (empty($config_set_options)) {
    return t('There are no Panzoom Configuration Sets at this time.');
  }

  $header = array(
    t('Name'),
    array('data' => t('Operations'), 'colspan' => 2),
  );
  $rows = array();

  foreach ($config_set_options as $file_name => $label) {
    $machine_name = str_replace('panzoom_images.set.', '', $file_name);
    $rows[$machine_name] = array(
      $label,
      l(t('Edit'), "admin/config/media/panzoom/{$machine_name}"),
      l(t('Delete'), "admin/config/media/panzoom/{$machine_name}/delete"),
    );
  }

  return theme('table', array('header' => $header, 'rows' => $rows));
}

/**
 * Page callback: Panzoom Config Set Add / Edit Form.
 */
function panzoom_images_config_set_form($form, &$form_state, $config_set = '') {
  $defaults = panzoom_images_get_config_set($config_set);

  $form['label'] = array(
    '#type' => 'textfield',
    '#title' => t('Configuration Set Name'),
    '#default_value' => !empty($defaults['label']) ? $defaults['label'] : '',
    '#required' => TRUE,
    '#size' => 40,
    '#maxlength' => 40,
  );
  $form['name'] = array(
    '#type' => 'machine_name',
    '#default_value' => !empty($defaults['name']) ? $defaults['name'] : '',
    '#max_length' => $form['label']['#maxlength'],
    '#machine_name' => array(
      'exists' => 'panzoom_images_machine_name_exists',
      'source' => array('label'),
    ),
    '#disabled' => !empty($defaults['name']),
  );
  $form['transition'] = array(
    '#type' => 'checkbox',
    '#title' => t('Transition'),
    '#description' => t('Whether or not to transition the scale'),
    '#default_value' => $defaults['transition'],
  );
  $form['cursor'] = array(
    '#type' => 'textfield',
    '#title' => t('Cursor'),
    '#description' => t('Default cursor style for the element'),
    '#default_value' => $defaults['cursor'],
    '#size' => 10,
    '#required' => TRUE,
  );
  $form['disablePan'] = array(
    '#type' => 'checkbox',
    '#title' => t('Disable Panning'),
    '#default_value' => $defaults['disablePan'],
  );
  $form['disableZoom'] = array(
    '#type' => 'checkbox',
    '#title' => t('Disable Zoom'),
    '#default_value' => $defaults['disableZoom'],
  );
  $form['increment'] = array(
    '#type' => 'textfield',
    '#title' => t('Increment'),
    '#description' => t('The increment at which to zoom. Adds / substracts to the scale each time the user zooms in / out.'),
    '#default_value' => $defaults['increment'],
    '#element_validate' => array('element_validate_number'),
    '#size' => 5,
    '#required' => TRUE,
  );
  $form['minScale'] = array(
    '#type' => 'textfield',
    '#title' => t('Minimum Scale'),
    '#default_value' => $defaults['minScale'],
    '#element_validate' => array('element_validate_number'),
    '#size' => 5,
    '#required' => TRUE,
  );
  $form['maxScale'] = array(
    '#type' => 'textfield',
    '#title' => t('Maximum Scale'),
    '#default_value' => $defaults['maxScale'],
    '#element_validate' => array('element_validate_number'),
    '#size' => 5,
    '#required' => TRUE,
  );
  $form['rangeStep'] = array(
    '#type' => 'textfield',
    '#title' => t('Range Step'),
    '#description' => t('The default step for the range input. Precendence: default < HTML attribute < option setting'),
    '#default_value' => $defaults['rangeStep'],
    '#element_validate' => array('element_validate_number'),
    '#size' => 5,
    '#required' => TRUE,
  );
  $form['duration'] = array(
    '#type' => 'textfield',
    '#title' => t('Duration'),
    '#description' => t('Animation duration (ms)'),
    '#default_value' => $defaults['duration'],
    '#element_validate' => array('element_validate_number'),
    '#size' => 5,
    '#required' => TRUE,
  );
  $form['easing'] = array(
    '#type' => 'textfield',
    '#title' => t('Easing'),
    '#description' => t('CSS easing used for scale transition'),
    '#default_value' => $defaults['easing'],
    '#size' => 15,
    '#required' => TRUE,
  );
  $form['contain'] = array(
    '#type' => 'checkbox',
    '#title' => t('Contain in Parent'),
    '#description' => t('The element should be contained within it\'s parent when panning.'),
    '#default_value' => $defaults['contain'],
  );

  // Custom configuration not provided directly by Panzoom.
  $form['custom'] = array('#type' => 'container');
  $form['custom']['mouse_scroll'] = array(
    '#type' => 'select',
    '#title' => t('Mouse Scroll Effect'),
    '#options' => array(
      'none' => t('None'),
      'pan_vertical' => t('Pan Vertically'),
      'zoom' => t('Zoom'),
    ),
    '#default_value' => $defaults['mouse_scroll'],
    '#description' => t('Provide mouse scroll effects if the jQuery Mousewheel library is installed.'),
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  $form['actions']['cancel'] = array(
    '#markup' => l(t('Cancel'), 'admin/config/media/panzoom'),
  );

  return $form;
}

/**
 * Submit Handler: Panzoom Config Set Add / Edit Form.
 */
function panzoom_images_config_set_form_submit($form, &$form_state) {
  $defaults = panzoom_images_get_config_set();
  $settings = $defaults;

  foreach (array_keys($defaults) as $key) {
    if (isset($form_state['values'][$key])) {
      $settings[$key] = $form_state['values'][$key];
    }
  }

  $settings['label'] = $form_state['values']['label'];
  $settings['name'] = $form_state['values']['name'];

  $config = config('panzoom_images.set.' . $settings['name']);
  $config->setData($settings);
  $config->save();

  $form_state['redirect'] = 'admin/config/media/panzoom';
}

/**
 * Machine Name element validate handler.
 */
function panzoom_images_machine_name_exists($value) {
  $config_set = config_get('panzoom_images.set.' . $value);
  return !empty($config_set);
}

/**
 * Page callback: Delete Panzoom Config Set.
 *
 * @param $machine_name
 *   The machine name of the config set to delete.
 */
function panzoom_images_config_set_delete($form, &$form_state, $machine_name) {
  $form['name'] = array(
    '#type' => 'value',
    '#value' => $machine_name,
  );

  return confirm_form(
    $form,
    t('Are you sure you want to delete this Panzoom Configuration Set?'),
    'admin/config/media/panzoom',
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

/**
 * Submit handler: Delete Panzoom Config Set.
 */
function panzoom_images_config_set_delete_submit($form, &$form_state) {
  $machine_name = $form_state['values']['name'];

  $config = config('panzoom_images.set.' . $machine_name);
  $config->delete();

  $form_state['redirect'] = 'admin/config/media/panzoom';
}
