Panzoom Images
===============

Panzoom Images provides a new image field formatter to render the image using
the Panzoom jQuery library (http://timmywil.github.io/jquery.panzoom/).

For each field instance, an 'teaser' image style is chosen and a Panzoom image
style is chosen. The image initially gets rendered on the page using the
'teaser' image style. When the user clicks on that image, another image is
ajax loaded to the page using the Panzoom image style. The user may then pan
and zoom the image to explore in detail.

Main Features

* Provides a Panzoom image field formatter.
* Create and choose from multiple Panzoom configuration sets.


Requirements
------------

 * None (The PanZoom jQuery library is included in this module)

Installation
------------

- Install this module using the official Backdrop CMS instructions at
  https://backdropcms.org/guide/modules.

- Add an Image field to any entity (Node, User, or Term).

- Go to the 'Manage Display' page for that entity.

- Choose 'Panzoom' as the Format for the image field.

- Select the image styles to use for rendering the image.

- (Optionally) Add new Panzoom configuration sets that can be selected on the
  field formatter settings.


Documentation
-------------

Additional documentation is located in the Wiki:
https://github.com/backdrop-contrib/panzoom_images/wiki/Documentation.

Issues
------

Bugs and Feature requests should be reported in the Issue Queue:
https://github.com/backdrop-contrib/panzoom_images/issues.

Current Maintainers
-------------------

- [Jen Lampton](https://github.com/jenlampton).
- Seeking additional maintainers.

Credits
-------

- Ported to Backdrop CMS by [Jen Lampton](https://github.com/jenlampton).
- Originally written for Drupal by [Craig Aschbrenner](https://www.drupal.org/user/246322)
- Based on the [Panzoom jQuery library](http://timmywil.github.io/jquery.panzoom).
- Drupal module sponsored by [University Business Magazine](http://www.universitybusiness.com/
- Drupal module sponsored by [Redfin Solutions, LLC](https://www.drupal.org/redfin-solutions-llc).

Licenses
--------

* This project is GPL v2 software.
  See the LICENSE.txt file in this directory for complete text.

* The jQuery PanZoom library is MIT-licenced.
  See the MTC-License.txt file in the panzoom directory for complete text.



