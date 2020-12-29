#!/bin/bash
#
# Copyright (C) 2012-2016 Marco Craveiro <marco.craveiro@gmail.com>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be  useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
# MA 02110-1301, USA.
#

#
# vcpkg dependencies. Important: when updating the package remember to
# create the dropbox link or else we will still point to the old
# package. Update the link below as well as the folder name.
#
vcpkg_dropbox_link="s/gb02t28ln1jytdj"
vcpkg_folder="vcpkg-export-20190305-140814"
vcpkg_package="${vcpkg_folder}.zip"
vcpkg_input_location="https://www.dropbox.com/${vcpkg_dropbox_link}/${vcpkg_package}?dl=0"
vcpkg_output_location="/tmp/${vcpkg_package}"
vcpkg_extract_dir="/tmp"
vcpkg_final_folder="vcpkg-export"
curl -L -o ${vcpkg_output_location} ${vcpkg_input_location}
unzip -q ${vcpkg_output_location} -d ${vcpkg_extract_dir}
mv ${vcpkg_extract_dir}/${vcpkg_folder} ${vcpkg_extract_dir}/${vcpkg_final_folder}
echo "vcpkg version: ${vcpkg_folder}"

#
# Reference models
#
cpp_ref_impl_input_location="https://github.com/MASD-Project/cpp_ref_impl/archive/master.zip"
cpp_ref_impl_output_location="/tmp/cpp_ref_impl.zip"
cpp_ref_impl_extract_dir="/tmp"
curl -L -o ${cpp_ref_impl_output_location} ${cpp_ref_impl_input_location}
unzip -q ${cpp_ref_impl_output_location} -d ${cpp_ref_impl_extract_dir}

frozen_input_location="https://github.com/MASD-Project/frozen/archive/master.zip"
frozen_output_location="/tmp/frozen.zip"
frozen_extract_dir="/tmp"
curl -L -o ${frozen_output_location} ${frozen_input_location}
unzip -q ${frozen_output_location} -d ${frozen_extract_dir}

csharp_ref_impl_input_location="https://github.com/MASD-Project/csharp_ref_impl/archive/master.zip"
csharp_ref_impl_output_location="/tmp/csharp_ref_impl.zip"
csharp_ref_impl_extract_dir="/tmp"
curl -L -o ${csharp_ref_impl_output_location} ${csharp_ref_impl_input_location}
unzip -q ${csharp_ref_impl_output_location} -d ${csharp_ref_impl_extract_dir}

#
# Upgrade CMake. Note that brew gives an error if the package is
# already up-to-date, which is not very nice. See:
# https://github.com/Homebrew/legacy-homebrew/issues/27897
#
brew upgrade cmake || true

#
# Remove the brew packages for boost
#
brew uninstall --force --ignore-dependencies boost || true
