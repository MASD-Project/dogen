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

#
# Compiler
#
compiler="$1"
shift
if [[ "x${compiler}" = "x" ]]; then
    compiler="gcc";
    echo "* Compiler: ${compiler} (default)"
    export CC=gcc-8
    export CXX=g++-8
elif [ "${compiler}" = "gcc" ]; then
    echo "* Compiler: ${compiler}"
    export CC=gcc-8
    export CXX=g++-8
elif [ "${compiler}" = "clang" ]; then
    echo "* Compiler: ${compiler}"
    export CC=clang-6.0
    export CXX=clang++-6.0
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
# C#
#
if [[ "x${WITH_CSHARP}" = "x" ]]; then
    echo "* C#: disabled"
else
    echo "* C#: enabled"
fi

#
# C++
#
if [[ "x${WITH_CPP}" = "x" ]]; then
    echo "* C++: disabled"
else
    echo "* C++: enabled"
fi

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

if [ "${WITH_CORE_ONLY}" == "1" ]; then
    cmake_defines="${cmake_defines} -DWITH_CORE=ON"
    cmake_defines="${cmake_defines} -DWITH_TEST_MODELS=OFF"
elif [ "${WITH_TEST_MODELS_ONLY}" == "1" ]; then
    cmake_defines="${cmake_defines} -DWITH_CORE=OFF"
    cmake_defines="${cmake_defines} -DWITH_TEST_MODELS=ON"
fi

#
# Use minimal packaging in debug to preserve disk space.
#
if [ "${build_type}" = "Debug" ]; then
    cmake_defines="${cmake_defines} -DWITH_MINIMAL_PACKAGING=ON"
fi

if [ "${COVERALLS}" = "1" ]; then
    cmake_defines="${cmake_defines} -DWITH_PROFILING=ON"
    cmake_defines="${cmake_defines} -DWITH_COVERALLS=ON"
fi

#
# Build
#
if [ "${WITH_CSHARP}" == "1" ]; then
    echo "* Starting C# build."
    csharp_dir="${product_dir}/projects/dogen.test_models";
    cd ${csharp_dir}
    nuget restore Dogen.TestModels.sln
    if [ $? -ne 0 ]; then
        echo "Error in nuget restore." >&2
        exit 1;
    fi

    xbuild Dogen.TestModels.sln
    if [ $? -ne 0 ]; then
        echo "Error building C# solution." >&2
        exit 1;
    fi

    mono packages/NUnit.ConsoleRunner.3.5.0/tools/nunit3-console.exe CSharpModel.Tests/bin/Debug/Dogen.TestModels.CSharpModel.Tests.dll
    if [ $? -ne 0 ]; then
        echo "Error running C# unit tests." >&2
        exit 1;
    fi
fi

if [ "${WITH_CPP}" == "1" ]; then
    echo "* Starting C++ build."
    cd ${build_type_dir}
    cmake ${product_dir} -G Ninja ${cmake_defines} && ninja -j${number_of_jobs} ${target}
    if [ $? -ne 0 ]; then
        echo "Error running CMake." >&2
        exit 1;
    fi
fi

exit 0;
