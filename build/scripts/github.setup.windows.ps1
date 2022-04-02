#
# Copyright (C) 2012-2022 Marco Craveiro <marco.craveiro@gmail.com>
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
$ref_models_dir="${GITHUB_WORKSPACE}\..\.."
$downloads_dir="${RUNNER_TEMP}\"

$cpp_ref_impl_input_location="https://github.com/MASD-Project/cpp_ref_impl/archive/master.zip"
$cpp_ref_impl_downloads_location="${downloads_dir}\cpp_ref_impl.zip"
$cpp_ref_impl_installs_dir="$ref_models_dir"

Invoke-WebRequest -OutFile $cpp_ref_impl_downloads_location $cpp_ref_impl_input_location
Write-Host "URL: $cpp_ref_impl_input_location"
Write-Host "Download location: $cpp_ref_impl_downloads_location"
Set-Location -Path $cpp_ref_impl_installs_dir | Out-Null
7z x $cpp_ref_impl_downloads_location > $null

$frozen_input_location="https://github.com/MASD-Project/frozen/archive/master.zip"
$frozen_downloads_location="${downloads_dir}\frozen.zip"
$frozen_installs_dir="$ref_models_dir"

Invoke-WebRequest -OutFile $frozen_downloads_location $frozen_input_location
Write-Host "URL: $frozen_input_location"
Write-Host "Download location: $frozen_downloads_location"
Set-Location -Path $frozen_installs_dir | Out-Null
7z x $frozen_downloads_location > $null

$csharp_ref_impl_input_location="https://github.com/MASD-Project/csharp_ref_impl/archive/master.zip"
$csharp_ref_impl_downloads_location="${downloads_dir}\csharp_ref_impl.zip"
$csharp_ref_impl_installs_dir="$ref_models_dir"

Invoke-WebRequest -OutFile $csharp_ref_impl_downloads_location $csharp_ref_impl_input_location
Write-Host "URL: $csharp_ref_impl_input_location"
Write-Host "Download location: $csharp_ref_impl_downloads_location"
Set-Location -Path $csharp_ref_impl_installs_dir | Out-Null
7z x $csharp_ref_impl_downloads_location > $null
