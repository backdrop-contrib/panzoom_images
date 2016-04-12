<?php
/**
 * @file
 * Theming functions for the Panzoom Images module.
 */

/**
 * Theme function: Render the Panzoom controls.
 */
function theme_panzoom_controls($variables) {
  $content = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array('panzoom__controls'),
    ),
  );

  if ($variables['include_zoom_out']) {
    $content['zoom_out'] = array(
      '#markup' => '<button class="panzoom__zoom_out">Zoom Out</button>',
    );
  }
  if ($variables['include_zoom_range']) {
    $content['zoom_range'] = array(
      '#markup' => '<input type="range" class="panzoom__zoom_range">',
    );
  }
  if ($variables['include_zoom_in']) {
    $content['zoom_in'] = array(
      '#markup' => '<button class="panzoom__zoom_in">Zoom In</button>',
    );
  }
  if ($variables['include_reset']) {
    $content['reset'] = array(
      '#markup' => '<button class="panzoom__reset">Reset</button>',
    );
  }
  $content['close'] = array(
    '#markup' => '<button class="panzoom__close">Close</button>',
  );

  return render($content);
}
