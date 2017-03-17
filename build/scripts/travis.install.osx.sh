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
# deps
#
dropbox="https://www.dropbox.com/s/28uz0mqvih5g3su/"
package="dogen_deps_clang_7_3_0_osx_amd64.tar.bz2"
input_location="${dropbox}/${package}"
output_location="/tmp/${package}"
extract_dir="/tmp/dogen_deps"
curl -L -o ${output_location} ${input_location}
mkdir ${extract_dir}
tar -zxf ${output_location} -C ${extract_dir}
