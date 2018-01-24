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

param (
    [string]$build_type = "Release",
    [string]$compiler = "msvc",
    [string]$third_party = "",
    [string[]]$target = @()
)

function Get-ScriptDirectory {
    $Invocation = (Get-Variable MyInvocation -Scope 1).Value;
    Split-Path $Invocation.MyCommand.Path;
}

#
# Root directory for the product.
#
$dir=Get-ScriptDirectory;
$product_dir="${dir}\..\..";
write-host "* Product directory: ${product_dir}";

#
# Compiler
#
if ($compiler -eq "msvc") {
    $generator="Visual Studio 14 2015 Win64";
    write-host "* compiler: ${compiler}";
} else {
    write-host "* Unrecognised compiler: ${compiler}";
    exit 1
}

#
# Additional directory for includes and libs.
#
if ([string]::IsNullOrEmpty($third_party)) {
    write-host "* Third party: NOT PROVIDED";
} else {
    write-host "* Third party: ${third_party}";
    $env:CMAKE_INCLUDE_PATH="${third_party}\include";
    $env:CMAKE_LIBRARY_PATH="${third_party}\lib";
}

#
# Target
#
write-host "* Target: '${target}'";

#
# Setup directories
#
$output_dir="${product_dir}/build/output";
if (!(Test-Path -Path $output_dir)) {
    New-Item -ItemType directory -Path $output_dir | Out-Null
}

$compiler_dir="${output_dir}/${compiler}";
if (!(Test-Path -Path $compiler_dir)) {
    New-Item -ItemType directory -Path $compiler_dir | Out-Null
}

$build_type_dir="${compiler_dir}/${build_type}";
if (!(Test-Path -Path $build_type_dir)) {
    New-Item -ItemType directory -Path $build_type_dir | Out-Null
}

cd ${build_type_dir}
if ($build_type -eq "Release") {
    conan install ${product_dir} -s compiler="Visual Studio" -s compiler.version=14 -s arch=x86_64
} elseif ($build_type -eq "Debug") {
    conan install ${product_dir} -s compiler="Visual Studio" -s compiler.version=14 -s arch=x86_64 -s build_type=Debug -s compiler.runtime=MDd
}

#
# CMake setup
#
$cmake_defines="-DCMAKE_BUILD_TYPE=${build_type}"
$cmake_defines="${cmake_defines} -DWITH_LATEX=OFF"
$cmake_defines="${cmake_defines} -DWITH_MINIMAL_PACKAGING=ON"

#
# Build
#
write-host "* Starting build.";
$command = "cmake ${product_dir} ${cmake_defines} -G '${generator}'";
Invoke-Expression -Command $command
if ($LastExitCode -ne 0) {
    write-host "Error whilst configuring."
    exit 1
}

$targets = $target -split " ";
foreach ($element in $targets) {
    $command = "cmake --build . --config $build_type --target ${element}";
    Invoke-Expression -Command $command
    if ($LastExitCode -ne 0) {
        write-host "Error whilst running target ${target}."
        exit 1
    }
}
