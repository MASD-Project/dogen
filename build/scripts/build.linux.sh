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
# Concurrent jobs
#
number_of_jobs="$1"
shift
if [[ "x${number_of_jobs}" = "x" ]]; then
    number_of_jobs="5";
    echo "* Jobs: ${number_of_jobs} (default)"
else
    echo "* Jobs: ${number_of_jobs}"
fi

#
# Root directory for the product.
#
dir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
product_dir=$(readlink -f ${dir}/../..)
echo "* Product directory: ${product_dir}"

projects_dir="${product_dir}/projects/"

#
# Compiler
#
compiler="$1"
shift
if [[ "x${compiler}" = "x" ]]; then
    compiler="gcc9";
    echo "* Compiler: ${compiler} (default)"
    export CC=gcc-9
    export CXX=g++-9
elif [ "${compiler}" = "gcc8" ]; then
    echo "* Compiler: ${compiler}"
    export CC=gcc-8
    export CXX=g++-8
elif [ "${compiler}" = "gcc9" ]; then
    echo "* Compiler: ${compiler}"
    export CC=gcc-9
    export CXX=g++-9
elif [ "${compiler}" = "gcc11" ]; then
    echo "* Compiler: ${compiler}"
    export CC=gcc-11
    export CXX=g++-11
elif [ "${compiler}" = "clang14" ]; then
    echo "* Compiler: ${compiler}"
    export CC=clang-14
    export CXX=clang-14
elif [ "${compiler}" = "clang11" ]; then
    echo "* Compiler: ${compiler}"
    export CC=clang-11
    export CXX=clang++-11
elif [ "${compiler}" = "clang10" ]; then
    echo "* Compiler: ${compiler}"
    export CC=clang-10
    export CXX=clang++-10
elif [ "${compiler}" = "clang9" ]; then
    echo "* Compiler: ${compiler}"
    export CC=clang-9
    export CXX=clang++-9
elif [ "${compiler}" = "clang8" ]; then
    echo "* Compiler: ${compiler}"
    export CC=clang-8
    export CXX=clang++-8
elif [ "${compiler}" = "clang7" ]; then
    echo "* Compiler: ${compiler}"
    export CC=clang-7
    export CXX=clang++-7
else
    echo "* Unrecognised compiler: ${compiler}"
    exit
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
cmake_defines="${cmake_defines} -DWITH_BENCHMARKS=ON"
cmake_defines="${cmake_defines} -DWITH_RELATIONAL_SUPPORT=OFF"
cmake_defines="${cmake_defines} -DBUILD_SHARED_LIBS=OFF"

if [[ ! -z "${CMAKE_TOOLCHAIN_FILE}" ]]; then
    cmake_defines="${cmake_defines} -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}"
fi

if [[ ! -z "${CMAKE_PROGRAM_PATH}" ]]; then
    cmake_defines="${cmake_defines} -DCMAKE_PROGRAM_PATH='${CMAKE_PROGRAM_PATH}'"
fi

if [[ ! -z "${DOGEN_FULL_GENERATION}" ]]; then
    cmake_defines="${cmake_defines} -DWITH_FULL_GENERATION=ON"
fi

if [[ ! -z "${WITH_DOXYGEN}" ]]; then
    cmake_defines="${cmake_defines} -DWITH_DOXYGEN=ON"
fi

#
# Use minimal packaging in debug to preserve disk space.
#
if [ "${build_type}" = "Debug" ]; then
    cmake_defines="${cmake_defines} -DWITH_MINIMAL_PACKAGING=ON"
fi

if [ "${COVERAGE}" = "1" ]; then
    cmake_defines="${cmake_defines} -DWITH_PROFILING=ON"
else
    cmake_defines="${cmake_defines} -DWITH_PROFILING=OFF"
fi

#
# Build
#
echo "* Starting C++ build."
cd ${build_type_dir}
cmake ${product_dir} -G Ninja ${cmake_defines} && ninja -j${number_of_jobs} ${target}
if [ $? -ne 0 ]; then
    echo "Error running CMake." >&2
    exit 1;
fi

exit 0;
