#!/bin/sh

# conan
wget http://downloads.conan.io/latest_macos -O conan.pkg
pkgutil --expand conan.pkg ~/conan
ls ~/conan
