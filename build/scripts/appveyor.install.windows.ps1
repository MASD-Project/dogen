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
7z x ${output_location} > $null;

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
$cmake_zip="cmake-3.12.0-win64-x64.zip"
$cmake_url="https://cmake.org/files/v3.12/${cmake_zip}"
$cmake_extract_dir="$env:temp"
$cmake_output_location="$env:temp/${cmake_zip}"

appveyor DownloadFile ${cmake_url} -FileName ${cmake_output_location}

write-host "URL: ${cmake_url}"
write-host "CMake dir: ${cmake_extract_dir}"
cd ${cmake_extract_dir}
7z x ${cmake_output_location} > $null;
Rename-Item -Path $cmake_extract_dir/cmake-3.12.0-win64-x64 -newName $cmake_extract_dir/cmake
${cmake_extract_dir}\cmake\bin\cmake --version

#
# Clang
#
$clang_version="7.0.0"
$clang_file="LLVM-${clang_version}-win64.exe"
$clang_url="http://releases.llvm.org/${clang_version}/"
$clang_extract_dir="$env:temp"
$clang_output_location="$env:temp/${clang_file}"

appveyor DownloadFile ${clang_url} -FileName ${clang_output_location}
write-host "URL: $clang_url"
write-host "Clang dir: $clang_extract_dir"
cd ${clang_extract_dir}
${clang_extract_dir}\llvm-installer.exe /S /D=C:\"Program Files\LLVM"

#
# Ninja
#
$ninja_file="ninja-win.zip"
$ninja_url="https://github.com/ninja-build/ninja/releases/download/v1.6.0/$ninja_file"
$ninja_extract_dir="$env:temp/Ninja"
$ninja_output_location="$env:temp/$ninja_file"

appveyor DownloadFile $ninja_file -FileName $ninja_file
write-host "URL: $ninja_url"
write-host "Ninja dir: $ninja_extract_dir"
New-Item -ItemType directory -Path $ninja_extract_dir
7z x $ninja_file -o $ninja_extract_dir > nul
${ninja_extract_dir}\ninja.exe -v
