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
# Build Type: Debug or Release.
#
build_type="$1"
shift
if [[ "x${build_type}" = "x" ]]; then
    build_type="Release";
    echo "* Build type: ${build_type} (default)"
else
    echo "* Build type: ${build_type}"
fi

#
# Root directory for the product.
#
dir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
product_dir=$(readlink -f ${dir}/../..)
echo "* Product directory: ${product_dir}"

#
# Compiler
#
compiler="$1"
shift
if [[ "x${compiler}" = "x" ]]; then
    compiler="gcc";
    echo "* Compiler: ${compiler} (default)"
    export CC=gcc-6
    export CXX=g++-6
elif [ "${compiler}" = "gcc" ]; then
    echo "* Compiler: ${compiler}"
    export CC=gcc-6
    export CXX=g++-6
elif [ "${compiler}" = "clang" ]; then
    echo "* Compiler: ${compiler}"
    export CC=clang-3.7
    export CXX=clang++-3.7
else
    echo "* Unrecognised compiler: ${compiler}"
    exit
fi

#
# Additional directory for includes and libs.
#
third_party="$1"
shift
if [[ "x$third_party" = "x" ]]; then
    third_party="";
    echo "* Third party: NOT PROVIDED"
else
    echo "* Third party: ${third_party}"
    export CMAKE_INCLUDE_PATH=${third_party}/include
    export CMAKE_LIBRARY_PATH=${third_party}/lib
fi

#
# Target
#
target="$*"
echo "* Target: '${target}'"

#
# Setup directories
#
output_dir="${product_dir}/build/output";
if [[ ! -e $output_dir ]]; then
    mkdir $output_dir
fi

compiler_dir="${output_dir}/${compiler}";
if [[ ! -e $compiler_dir ]]; then
    mkdir $compiler_dir
fi

build_type_dir="${compiler_dir}/${build_type}";
if [[ ! -e $build_type_dir ]]; then
    mkdir $build_type_dir
fi

#
# CMake setup
#
cmake_defines="-DCMAKE_BUILD_TYPE=${build_type}"
cmake_defines="${cmake_defines} -DCMAKE_EXPORT_COMPILE_COMMANDS=TRUE"
cmake_defines="${cmake_defines} -DWITH_LATEX=OFF"
if [ "${COVERALLS}" = "1" ]; then
    cmake_defines="${cmake_defines} -DWITH_PROFILING=ON"
    cmake_defines="${cmake_defines} -DWITH_COVERALLS=ON"
fi

#
# Build
#
if [ "${WITH_CSHARP}" == "1" ]; then
    echo "* Starting C# build."
    csharp_dir="${product_dir}/projects/test_models";
    cd ${csharp_dir}
    nuget restore Dogen.TestModels.sln
    xbuild Dogen.TestModels.sln
    mono packages/NUnit.ConsoleRunner.3.5.0/tools/nunit3-console.exe CSharpModel.Tests/bin/Debug/CSharpModel.Tests.dll
fi

echo "* Starting C++ build."
cd ${build_type_dir}
cmake ${product_dir} -G Ninja ${cmake_defines} && ninja -j5 ${target}
