xdg-desktop-portal-liri
=======================

[![License](https://img.shields.io/badge/license-GPLv3.0-blue.svg)](https://www.gnu.org/licenses/gpl-3.0.html)
[![GitHub release](https://img.shields.io/github/release/lirios/xdg-desktop-portal-liri.svg)](https://github.com/lirios/xdg-desktop-portal-liri)
[![Build Status](https://travis-ci.org/lirios/xdg-desktop-portal-liri.svg?branch=develop)](https://travis-ci.org/lirios/xdg-desktop-portal-liri)
[![GitHub issues](https://img.shields.io/github/issues/lirios/xdg-desktop-portal-liri.svg)](https://github.com/lirios/xdg-desktop-portal-liri/issues)
[![Maintained](https://img.shields.io/maintenance/yes/2018.svg)](https://github.com/lirios/xdg-desktop-portal-liri/commits/develop)

A backend implementation of [xdg-desktop-portal](https://github.com/flatpak/xdg-desktop-portal)
that is using Qt and Liri.

## Dependencies

Make sure you have Qt >= 5.10.0 with the following modules:

 * [qtbase](http://code.qt.io/cgit/qt/qtbase.git)
 * [qtdeclarative](http://code.qt.io/cgit/qt/qtdeclarative.git)
 * [qtquickcontrols2](http://code.qt.io/cgit/qt/qtquickcontrols2.git)

And the following modules:

 * [cmake](https://gitlab.kitware.com/cmake/cmake) >= 3.10.0
 * [cmake-shared](https://github.com/lirios/cmake-shared.git) >= 1.0.0
 * [libliri](https://github.com/lirios/libliri.git)

Runtime dependencies:

 * [flatpak](https://github.com/flatpak/flatpak)
 * [xdg-desktop-portal](https://github.com/flatpak/xdg-desktop-portal)

## Installation

```sh
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=/path/to/prefix ..
make
make install # use sudo if necessary
```

Replace `/path/to/prefix` to your installation prefix.
Default is `/usr/local`.

## Licensing

Licensed under the terms of the GNU General Public License version 3.0 or,
at your option, any later version.
