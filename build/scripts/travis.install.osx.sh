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
# generate the dropbox link or else we will still point to the old
# package.
#
vcpkg_dropbox_link="s/kr3wr1pqeu3x6bq"
vcpkg_folder="vcpkg-export-20181016-095434"
vcpkg_package="${vcpkg_folder}.zip"
vcpkg_input_location="https://www.dropbox.com/${vcpkg_dropbox_link}/${vcpkg_package}?dl=0"
vcpkg_output_location="/tmp/${vcpkg_package}"
vcpkg_extract_dir="/tmp"
vcpkg_final_folder="vcpkg-export"
curl -L -o ${vcpkg_output_location} ${vcpkg_input_location}
unzip -q ${vcpkg_output_location} -d ${vcpkg_extract_dir}
mv ${vcpkg_extract_dir}/${vcpkg_folder} ${vcpkg_extract_dir}/${vcpkg_final_folder}
echo "vcpkg version: ${vcpkg_folder}"
