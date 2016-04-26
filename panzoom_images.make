; This drush make file downloads the required Panzoom jQuery library into the
; sites/all/libraries/panzoom folder.

core = 7.x
api = 2

libraries[panzoom][download][type] = get
libraries[panzoom][download][url] = https://github.com/timmywil/jquery.panzoom/archive/2.0.6.tar.gz

libraries[jquery.mousewheel][type] = get
libraries[jquery.mousewheel][url] = https://github.com/jquery/jquery-mousewheel/archive/3.1.13.zip
