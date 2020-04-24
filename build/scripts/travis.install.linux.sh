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
# vcpkg dependencies. Important: when updating the package remember to
# generate the dropbox link or else we will still point to the old
# package. Update the link below as well as the folder name.
#
vcpkg_dropbox_link="s/dxvdvygmj5s69mu"
vcpkg_folder="vcpkg-export-20190910-105654"
vcpkg_package="${vcpkg_folder}.zip"
vcpkg_input_location="https://www.dropbox.com/${vcpkg_dropbox_link}/${vcpkg_package}?dl=0"
vcpkg_output_location="/tmp/${vcpkg_package}"
vcpkg_extract_dir="/tmp"
vcpkg_final_folder="vcpkg-export"
wget --no-check-certificate ${vcpkg_input_location} -O ${vcpkg_output_location}
unzip -q ${vcpkg_output_location} -d ${vcpkg_extract_dir}
mv ${vcpkg_extract_dir}/${vcpkg_folder} ${vcpkg_extract_dir}/${vcpkg_final_folder}
echo "vcpkg version: ${vcpkg_folder}"

#
# common repos
#
sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test
sudo apt-get update -qq

#
# kcov deps
#
sudo apt-get install -qq libcurl4-openssl-dev zlib1g-dev libdw-dev libiberty-dev

#
# clang
#
if [ "$CXX" == "clang++" ]; then
    version="9"
    release="xenial"
    server="http://apt.llvm.org/${release}/"
    sources="/etc/apt/sources.list"
    toolchain="llvm-toolchain-xenial"
    sudo sh -c "echo 'deb ${server} ${toolchain}-${version} main' >> ${sources}"
    sudo sh -c "echo 'deb ${server} ${toolchain}-${version} main' >> ${sources}"
    wget -O - http://llvm.org/apt/llvm-snapshot.gpg.key | sudo apt-key add -
    sudo apt-get update -qq

    sudo apt-get install --allow-unauthenticated -qq clang-${version}
    which clang-${version} llvm-toolchain-${version}
    export CXX="clang++-${version}" CC="clang-${version}"

    # Need to update GCC in order to get headers for clang.
    version="9"
    sudo apt-get install -qq g++-${version}
fi

#
# Boost
#
sudo apt-get remove libboost-all-dev libboost-test-dev

#
# g++
#
if [ "$CXX" = "g++" ]; then
    version="9"
    sudo apt-get install -qq g++-${version}
    export CXX="g++-${version}" CC="gcc-${version}" GCOV="gcov-${version}"
fi

#
# ninja
#
sudo apt-get install ninja-build

#
# cmake
#
sudo rm -rf /usr/local/cmake-3.12.4

cmake_name="cmake-3.15.3-Linux-x86_64"
cmake_tar="${cmake_name}.tar.gz"
cmake_input="https://cmake.org/files/v3.15/${cmake_tar}"
cmake_output="/tmp/${cmake_tar}"
wget --no-check-certificate ${cmake_input} -O ${cmake_output}
tar xf ${cmake_output} -C /tmp
sudo cp -r /tmp/${cmake_name}/* /usr
which cmake
cmake --version
rm -rf ${cmake_output} /tmp/${cmake_name}

#
# kcov
#
kcov_input_location="https://www.dropbox.com/s/fjaz9x6nnxuvne9/kcov?dl=0"
kcov_output_location="/tmp/kcov"
wget --no-check-certificate ${kcov_input_location} -O ${kcov_output_location}
chmod +x ${kcov_output_location}
${kcov_output_location} --version

#
# Clean cache
#
sudo apt-get clean
echo "Cleaned cache."

#
# Reference models
#
cpp_ref_impl_input_location="https://github.com/MASD-Project/cpp_ref_impl/archive/master.zip"
cpp_ref_impl_output_location="/tmp/cpp_ref_impl.zip"
cpp_ref_impl_extract_dir="/tmp"
wget --no-check-certificate ${cpp_ref_impl_input_location} -O ${cpp_ref_impl_output_location}
unzip -q ${cpp_ref_impl_output_location} -d ${cpp_ref_impl_extract_dir}

csharp_ref_impl_input_location="https://github.com/MASD-Project/csharp_ref_impl/archive/master.zip"
csharp_ref_impl_output_location="/tmp/csharp_ref_impl.zip"
csharp_ref_impl_extract_dir="/tmp"
wget --no-check-certificate ${csharp_ref_impl_input_location} -O ${csharp_ref_impl_output_location}
unzip -q ${csharp_ref_impl_output_location} -d ${csharp_ref_impl_extract_dir}
