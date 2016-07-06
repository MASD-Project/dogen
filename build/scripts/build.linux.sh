#!/bin/bash

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
product_dir=$(realpath ${dir}/../..)
echo "* Product directory: ${product_dir}"

#
# Compiler
#
compiler="$1"
shift
if [[ "x${compiler}" = "x" ]]; then
    compiler="gcc";
    echo "* Compiler: ${compiler} (default)"
else
    echo "* Compiler: ${compiler}"
fi

if [ "${compiler}" = "gcc" ]; then
    export CC=gcc-5
    export CXX=g++-5
elif [ "${compiler}" = "clang" ]; then
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

compiler_dir="${output_dir}/${CC}";
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
echo "* Starting build."
cd ${build_type_dir}
cmake ${product_dir} -G Ninja ${cmake_defines}
ninja -j5 ${target}
