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
# Top-level directories used by install
#
$top_level_dir="C:\third_party"
New-Item -ItemType directory -Path $top_level_dir

$installs_dir="$top_level_dir\installs"
New-Item -ItemType directory -Path $installs_dir

$downloads_dir="$top_level_dir\downloads"
New-Item -ItemType directory -Path $downloads_dir

#
# vcpkg
#
$vcpkg_folder="vcpkg-export-20181010-114151"
$vcpkg_package="${vcpkg_folder}.zip"
$vcpkg_input_location="https://www.dropbox.com/s/yui5t4w7mivgdi0/${vcpkg_package}?dl=0"
$vcpkg_downloads_location="${downloads_dir}\${vcpkg_package}"
$vcpkg_installs_dir="$installs_dir"
$vcpkg_final_folder="vcpkg-export"
# appveyor DownloadFile $vcpkg_input_location -FileName $vcpkg_downloads_location
build\scripts\wget.exe --quiet --no-check-certificate $vcpkg_input_location -O $vcpkg_downloads_location

Write-Host "URL: $vcpkg_input_location"
Write-Host "Download location: $vcpkg_downloads_location"
Set-Location -Path $vcpkg_installs_dir
7z x $vcpkg_downloads_location > $null;
Rename-Item -Path $vcpkg_installs_dir/$vcpkg_folder -newName $vcpkg_installs_dir/$vcpkg_final_folder

#
# Ninja
#
$ninja_package="ninja-win.zip"
$ninja_input_location="https://github.com/ninja-build/ninja/releases/download/v1.6.0/${ninja_package}"
$ninja_installs_dir="$installs_dir\Ninja"
$ninja_downloads_location="${downloads_dir}/${ninja_package}"

appveyor DownloadFile $ninja_input_location -FileName $ninja_downloads_location
Write-Host "URL: $ninja_input_location"
Write-Host "Download location: $ninja_downloads_location"
New-Item -ItemType directory -Path $ninja_installs_dir
Set-Location -Path $ninja_installs_dir
7z x $ninja_downloads_location > $null
