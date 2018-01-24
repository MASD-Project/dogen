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

$dropbox="https://www.dropbox.com/s/ntz6moq7kg9a8m7"
$version=4
$package="dogen_deps_vc14_windows_amd64_v${version}.7z"
$input_location="${dropbox}/${package}"
$output_location="$env:temp/${package}"
$extract_dir="$env:temp/dogen_deps"

build\scripts\wget.exe --quiet --no-check-certificate ${input_location} -O ${output_location}

write-host "URL: ${input_location}"
write-host "Dogen deps: ${output_location}"
mkdir ${extract_dir} | Out-Null
cd ${extract_dir}
7z x ../${package} > $null;

#
# conan
#
write-host "Installing conan..."
$env:PYTHON = "C:/Python27"
$env:PATH += ";$env:PYTHON/Scripts"
pip.exe install conan
$env:PATH += ";C:\Program Files (x86)\Conan\conan"
conan --version
conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan

#
# cmake
#
cinst cmake --version 3.4.3
cmake --version
