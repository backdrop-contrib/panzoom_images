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

              if ($configSet.mouse_scroll == 'zoom') {
                $panzoomImageContainer.children('img').parent().on('mousewheel.focal', function( e ) {
                  e.preventDefault();
                  var delta = e.delta || e.originalEvent.wheelDelta;
                  var zoomOut = delta ? delta < 0 : e.originalEvent.deltaY > 0;
                  // @todo make zoom options configuration.
                  $panzoomImageContainer.children('img').panzoom('zoom', zoomOut, {
                    increment: 0.1,
                    animate: false,
                    focal: e
                  });
                });
              }
              else if ($configSet.mouse_scroll == 'pan_vertical') {
                $panzoomImageContainer.children('img').parent().on('mousewheel.focal', function( e ) {
                  e.preventDefault();
                  var delta = e.delta || e.originalEvent.wheelDelta;
                  var panDown = delta ? delta < 0 : e.originalEvent.deltaY > 0;
                  var changeY = panDown ? -20 : 20;
                  // @todo make pan options configuration.
                  $panzoomImageContainer.children('img').panzoom('pan', 0, changeY, {
                    relative: true
                  });
                });
              }

            });
          });

        });
      });
    }

  };

})(jQuery, Drupal);
