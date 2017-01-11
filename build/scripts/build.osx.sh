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
# Concurrent jobs.
#
number_of_jobs="$1"
shift
if [[ "x${number_of_jobs}" = "x" ]]; then
    number_of_jobs="5";
    echo "* Jobs: ${number_of_jobs} (default)"
else
    echo "* Jobs: ${number_of_jobs}"
fi

realpath() {
    [[ $1 = /* ]] && echo "$1" || echo "$PWD/${1#./}"
}

#
# Root directory for the product.
#
dir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
product_dir=$(realpath ${dir}/../..)
echo "* Product directory: ${product_dir}"

#
# Compiler
#
compiler="$1"
shift
if [ "${compiler}" = "clang" ]; then
    echo "* Compiler: ${compiler}"
    export CC=clang
    export CXX=clang++
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
    export DYLD_FALLBACK_LIBRARY_PATH=${third_party}/lib
    echo "DYLD_FALLBACK_LIBRARY_PATH: $DYLD_FALLBACK_LIBRARY_PATH"
    export PATH=${third_party}/bin:${PATH};
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
cmake_defines="${cmake_defines} -DWITH_MINIMAL_PACKAGING=ON"
cmake_defines="${cmake_defines} -DWITH_LATEX=OFF"
if [ "${COVERALLS}" = "1" ]; then
    cmake_defines="${cmake_defines} -DWITH_PROFILING=ON"
    cmake_defines="${cmake_defines} -DWITH_COVERALLS=ON"
fi

#
# Build
#
echo "* Starting build."
cd ${build_type_dir}
cmake ${product_dir} ${cmake_defines} && make -j ${number_of_jobs} ${target}
