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
New-Item -ItemType directory -Path $top_level_dir | Out-Null

$installs_dir="$top_level_dir\installs"
New-Item -ItemType directory -Path $installs_dir | Out-Null

$ref_models_dir="$top_level_dir\ref_models"
New-Item -ItemType directory -Path $ref_models_dir | Out-Null

$downloads_dir="$top_level_dir\downloads"
New-Item -ItemType directory -Path $downloads_dir | Out-Null

#
# vcpkg dependencies. Important: when updating the package remember to
# generate the dropbox link or else we will still point to the old
# package. Update the link below as well as the folder name.
#
$vcpkg_dropbox_link="s/r68lb32g5040vif"
$vcpkg_folder="vcpkg-export-20190701-083321"
$vcpkg_package="${vcpkg_folder}.zip"
$vcpkg_input_location="https://www.dropbox.com/${vcpkg_dropbox_link}/${vcpkg_package}?dl=0"
$vcpkg_downloads_location="${downloads_dir}\${vcpkg_package}"
$vcpkg_installs_dir="$installs_dir"
$vcpkg_final_folder="vcpkg-export"

# Note: we don't seem to be able to download from dropbox using DownloadFile
# so we use wget instead.
# appveyor DownloadFile $vcpkg_input_location -FileName $vcpkg_downloads_location
build\scripts\wget.exe --quiet --no-check-certificate $vcpkg_input_location -O $vcpkg_downloads_location

Write-Host "URL: $vcpkg_input_location"
Write-Host "Download location: $vcpkg_downloads_location"
Set-Location -Path $vcpkg_installs_dir | Out-Null
7z x $vcpkg_downloads_location > $null;
Rename-Item -Path $vcpkg_installs_dir/$vcpkg_folder -newName $vcpkg_installs_dir/$vcpkg_final_folder | Out-Null

#
# Ninja
#
$ninja_package="ninja-win.zip"
$ninja_input_location="https://github.com/ninja-build/ninja/releases/download/v1.8.2/${ninja_package}"
$ninja_installs_dir="$installs_dir\Ninja"
$ninja_downloads_location="${downloads_dir}/${ninja_package}"

appveyor DownloadFile $ninja_input_location -FileName $ninja_downloads_location
Write-Host "URL: $ninja_input_location"
Write-Host "Download location: $ninja_downloads_location"
New-Item -ItemType directory -Path $ninja_installs_dir | Out-Null
Set-Location -Path $ninja_installs_dir | Out-Null
7z x $ninja_downloads_location > $null

#
# Reference models
#
$cpp_ref_impl_input_location="https://github.com/MASD-Project/cpp_ref_impl/archive/master.zip"
$cpp_ref_impl_downloads_location="${downloads_dir}\cpp_ref_impl.zip"
$cpp_ref_impl_installs_dir="$ref_models_dir"

appveyor DownloadFile $cpp_ref_impl_input_location -FileName $cpp_ref_impl_downloads_location
Write-Host "URL: $cpp_ref_impl_input_location"
Write-Host "Download location: $cpp_ref_impl_downloads_location"
Set-Location -Path $cpp_ref_impl_installs_dir | Out-Null
7z x $cpp_ref_impl_downloads_location > $null

$frozen_input_location="https://github.com/MASD-Project/frozen/archive/master.zip"
$frozen_downloads_location="${downloads_dir}\frozen.zip"
$frozen_installs_dir="$ref_models_dir"

appveyor DownloadFile $frozen_input_location -FileName $frozen_downloads_location
Write-Host "URL: $frozen_input_location"
Write-Host "Download location: $frozen_downloads_location"
Set-Location -Path $frozen_installs_dir | Out-Null
7z x $frozen_downloads_location > $null

$csharp_ref_impl_input_location="https://github.com/MASD-Project/csharp_ref_impl/archive/master.zip"
$csharp_ref_impl_downloads_location="${downloads_dir}\csharp_ref_impl.zip"
$csharp_ref_impl_installs_dir="$ref_models_dir"

appveyor DownloadFile $csharp_ref_impl_input_location -FileName $csharp_ref_impl_downloads_location
Write-Host "URL: $csharp_ref_impl_input_location"
Write-Host "Download location: $csharp_ref_impl_downloads_location"
Set-Location -Path $csharp_ref_impl_installs_dir | Out-Null
7z x $csharp_ref_impl_downloads_location > $null
