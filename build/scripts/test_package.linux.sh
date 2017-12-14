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
# Remove packages we won't test to save space.
#
rm ${build_type_dir}/stage/pkg/dogen_*_amd64-headers.deb
rm ${build_type_dir}/stage/pkg/dogen_*_amd64-libraries.deb
rm ${build_type_dir}/stage/pkg/dogen_*_amd64-tests.deb
echo "Removed packages not required for testing."

#
# Test the package
#
sudo dpkg -i ${build_type_dir}/stage/pkg/dogen_*_amd64-applications.deb
cp ${product_dir}/projects/dogen.input_models/dia/hello_world.dia /tmp
cd /tmp
/usr/bin/dogen.knitter --version
/usr/bin/dogen.knitter -t hello_world.dia
