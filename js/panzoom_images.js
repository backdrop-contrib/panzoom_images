/**
 * @file
 * A javascript file for the Panzoom Images module.
 */

(function ($, Drupal) {

  'use strict';

  Drupal.behaviors.panzoomImages = {

    attach: function (context, settings) {

      var $panzoomSel = $('.panzoom');

      // There could possibly be multiple 'teaser' images that are clickable and
      // open up the panzoom image so loop through each panzoom container.
      $panzoomSel.each(function (index) {
        var $panzoomContainer = $(this);
        var $initialImageContainer = $panzoomContainer.children('.panzoom__image_initial');
        var $panzoomControls = $panzoomContainer.children('.panzoom__controls');
        var $panzoomImageContainer = $panzoomContainer.children('.panzoom__image_panzoom');

        // Add a handler to close the panzoom image when clicked.
        $panzoomControls.children('.panzoom__close').on('click', function (e) {
          console.log('closing');
          e.preventDefault();
          $panzoomContainer.removeClass('panzoom--viewing');
        });

        // On the teaser image add a click handler that will ajax load the
        // panzoom image and apply the panzoom library to the new image.
        $initialImageContainer.children('img').on('click', function (e) {
          $panzoomContainer.addClass('panzoom--viewing');
          $panzoomImageContainer.once('loadPanzoomImage', function () {
            var fid = $initialImageContainer.data('fid');
            var style = $initialImageContainer.data('panzoom-image-style');
            var ajaxUrl = '/panzoom/' + fid;

            // The ajax callback requires the file ID (fid) but it does not
            // require the image style. Conditionally append the style to the
            // url if it is present.
            if (style != null) {
              ajaxUrl = ajaxUrl + '/' + style;
            }

            $panzoomImageContainer.load(ajaxUrl, function () {
              var configSetId = $panzoomContainer.data('panzoom-config-set');
              var $configSet = Drupal.settings.panzoomConfigSets[configSetId];

              $.extend($configSet, {
                $zoomIn: $panzoomControls.children($configSet.zoom_in_selector),
                $zoomOut: $panzoomControls.children($configSet.zoom_out_selector),
                $zoomRange: $panzoomControls.children($configSet.zoom_range_selector),
                $reset: $panzoomControls.children($configSet.reset_selector)
              });

              $panzoomImageContainer.children('img').panzoom($configSet);
            });
          });

        });
      });
    }

  };

})(jQuery, Drupal);
