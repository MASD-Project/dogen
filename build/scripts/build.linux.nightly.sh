#!/bin/bash

#
# Very trivial script to use CTest to run two nightly builds (clang
# and gcc). Ensure you have exported CMAKE_TOOLCHAIN_FILE before running
# this script.

#
git_url="https://github.com/MASD-Project/dogen.git"
workspace="${HOME}/nightly"

if [ ! -d "${workspace}" ]; then
    mkdir ${workspace}
fi

git_dir="${workspace}/dogen"
if [ ! -d "${git_dir}" ]; then
    git clone ${git_url} ${git_dir}
fi

cd ${git_dir}

configuration=Debug
generator=Ninja
compiler=clang7
number_of_jobs=3
build_group=Nightly

ctest --extra-verbose --script ".ctest.cmake,configuration_type=${configuration},generator=${generator},compiler=${compiler},number_of_jobs=${number_of_jobs},build_group=${build_group},minimal_packaging=1" > /tmp/ctest_${compiler}.log 2>&1

compiler=gcc8
ctest --extra-verbose --script ".ctest.cmake,configuration_type=${configuration},generator=${generator},compiler=${compiler},number_of_jobs=${number_of_jobs},build_group=${build_group},minimal_packaging=1" > /tmp/ctest_${compiler}.log 2>&1
