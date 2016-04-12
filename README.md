Introduction
============

Panzoom Images provides a new image field formatter to render the image using
the Panzoom jQuery library (http://timmywil.github.io/jquery.panzoom/).

For each field instance, an 'teaser' image style is chosen and a Panzoom image
style is chosen. The image initially gets rendered on the page using the
'teaser' image style. When the user clicks on that image, another image is
ajax loaded to the page using the Panzoom image style. The user may then pan
and zoom the image to explore in detail.

Main Features
-------------

* Provides a Panzoom image field formatter.
* Create and choose from multiple Panzoom configuration sets.

Installation
============

Requirements
------------

* Libraries module (https://www.drupal.org/project/libraries)
* Panzoom jQuery Library (http://timmywil.github.io/jquery.panzoom/)

# Install the libraries module.
# Add the Panzoom jQuery library to the sites/all/libraries folder.
  Note: A .make file is included to download the jQuery library to the
  right folder.
# Install the Panzoom Images module.

Configuration
-------------

# Go to the 'Manage Display' for the entity (e.g. node).
# Choose 'Panzoom' as the Format for an image field.
# Select the image styles to use for rendering the image.
# (Optionally) Add new Panzoom configuration sets that can be selected on the
  field formatter settings.

Maintainers
===========

* Craig Aschbrenner <https://www.drupal.org/user/246322>

Sponsors
========

@todo
