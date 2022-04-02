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
$ref_models_dir="$Env:GITHUB_WORKSPACE\..\.."
Write-Host "Reference models: $ref_models_dir"

$downloads_dir="$Env:RUNNER_TEMP\"
Write-Host "Downloads dir: $downloads_dir"

$cpp_ref_impl_input_location="https://github.com/MASD-Project/cpp_ref_impl/archive/master.zip"
$cpp_ref_impl_output_location="${downloads_dir}\cpp_ref_impl.zip"
$cpp_ref_impl_extract_dir="$ref_models_dir"

Write-Host "URL: $cpp_ref_impl_input_location"
Write-Host "Download location: $cpp_ref_impl_output_location"
Invoke-WebRequest -OutFile $cpp_ref_impl_output_location $cpp_ref_impl_input_location
Set-Location -Path $cpp_ref_impl_extract_dir | Out-Null
7z x $cpp_ref_impl_output_location > $null
New-Item -Path "$cpp_ref_impl_extract_dir" -Name "cpp_ref_impl" -ItemType "directory"
Move-Item -Path  $cpp_ref_impl_extract_dir/cpp_ref_impl-master -Destination $cpp_ref_impl_extract_dir/cpp_ref_impl/master

$frozen_input_location="https://github.com/MASD-Project/frozen/archive/master.zip"
$frozen_output_location="${downloads_dir}\frozen.zip"
$frozen_extract_dir="$ref_models_dir"

Write-Host "URL: $frozen_input_location"
Write-Host "Download location: $frozen_output_location"
Invoke-WebRequest -OutFile $frozen_output_location $frozen_input_location
Set-Location -Path $frozen_extract_dir | Out-Null
7z x $frozen_output_location > $null
New-Item -Path "$frozen_extract_dir" -Name "frozen" -ItemType "directory"
Move-Item -Path  $frozen_extract_dir/frozen-master -Destination $frozen_extract_dir/frozen/master

$csharp_ref_impl_input_location="https://github.com/MASD-Project/csharp_ref_impl/archive/master.zip"
$csharp_ref_impl_output_location="${downloads_dir}\csharp_ref_impl.zip"
$csharp_ref_impl_extract_dir="$ref_models_dir"

Write-Host "URL: $csharp_ref_impl_input_location"
Write-Host "Download location: $csharp_ref_impl_output_location"
Invoke-WebRequest -OutFile $csharp_ref_impl_output_location $csharp_ref_impl_input_location
Set-Location -Path $csharp_ref_impl_extract_dir | Out-Null
7z x $csharp_ref_impl_output_location > $null
New-Item -Path "$csharp_ref_impl_extract_dir" -Name "csharp_ref_impl" -ItemType "directory"
Move-Item -Path  $csharp_ref_impl_extract_dir/csharp_ref_impl-master -Destination $csharp_ref_impl_extract_dir/csharp_ref_impl/master
