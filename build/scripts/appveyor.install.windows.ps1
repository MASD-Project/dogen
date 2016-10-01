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
$dropbox="https://dl.dropboxusercontent.com/u/541873/packages"
$package="dogen_deps_vc14_windows_amd64.7z"
$input_location="${dropbox}/${package}"
$output_location="$env:temp/${package}"
$extract_dir="$env:temp/dogen_deps"

write-host ${input_location}
write-host ${output_location}
wget ${input_location} -OutFile ${output_location}

ls $env:temp
mkdir ${extract_dir}
cd ${extract_dir}
7z x ../${package} > $null;
