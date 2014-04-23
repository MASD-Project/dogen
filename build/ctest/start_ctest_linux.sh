#!/bin/bash
#
# Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
function usage() {
    echo "USAGE: start_ctest_linux.sh COMPILER MODEL BUILD_TYPE" >&2
    echo "" >&2
    echo "WHERE:" >&2
    echo "    COMPILER: gcc | clang" >&2
    echo "    MODEL: Continuous | Experimental | Nightly" >&2
    echo "    BUILD_TYPE: code | doxygen" >&2
    echo "" >&2
    echo "EXAMPLE: ./start_ctest_linux.sh gcc Continuous code" >&2
}

if [ "$#" -ne "3" ]; then
    usage
    exit 1
fi

compiler="$1"
model="$2"
build_type="$3"
product="dogen"

if [ "${compiler}" == "gcc" ]; then
    export CC="gcc"
    export CXX="g++"
elif [ "${compiler}" == "clang" ]; then
    export CC="clang"
    export CXX="clang++"
else
    echo "Invalid compiler: '${compiler}'." >&2
    usage
    exit 1
fi

pid_to_kill=`ps -efww | grep ctest | grep model=${model} | \
    grep product=${product} | \
    grep build_type=${build_type} | awk '{print $2; }'`

if [ "x${pid_to_kill}" != "x" ]; then
    kill -9 ${pid_to_kill}
    pid_to_kill=`ps -efww | grep ctest | grep model=${model} | \
        grep product=${product} | \
        grep build_type=${build_type} | awk '{print $2; }'`

    if [ "x${pid_to_kill}" == "x" ]; then
        echo "Killed ctest for ${model} ${product} ${build_type}"
    else
        echo "Failed to kill ctest for ${model} ${product} ${build_type}" >&2
        exit 1
    fi
fi

build_dir="/home/${USER}/build"
ctest_script="./CTest.cmake"

if [ ! -d "${build_dir}" ]; then
    echo "build directory not found: ${build_dir}" >&2
    exit 1
fi

args="${ctest_script},model=${model},product=${product}"
log="${model}-${product}"

os_name="debian"
os_version="testing"
os_architecture="`uname -m`"
os_available_cores="`grep -c ^processor /proc/cpuinfo`"
compiler="gcc";
compiler_version="4.8"

args="${args},build_type=${build_type}"
if [ "$build_type" == "doxygen" ]; then
    log="${log}-${build_type}.log";
elif [ "$build_type" = "code" ]; then

    log="${log}-${os_name}-${os_version}";
    log="${log}-${os_architecture}";
    log="${log}-${compiler}-${compiler_version}.log";

    args="${args},operative_system=${os_name}"
    args="${args},operative_system_version=${os_version}"
    args="${args},compiler=${compiler}"
    args="${args},compiler_version=${compiler_version}"
    args="${args},architecture=${os_architecture}"
    args="${args},number_of_cpus=${os_available_cores}"
else
    echo "Build type not supported: ${build_type}" >&2
    exit 1
fi

old_log=`echo ${build_dir}/${log} | sed -e 's/\.log/\.previous/g'`
if [ -f ${build_dir}/${log} ]; then
    mv ${build_dir}/${log} ${old_log}
fi

grep_result=0;
ctest_result=0;
while [ "${grep_result}" == "0" ];
do
    ctest --extra-verbose --script "${args}" 2&>1 >> ${build_dir}/${log}
    ctest_result=$?
    tail -n1 ${build_dir}/${log} | grep "Failed to update files from git"
    grep_result=$?
done
exit $ctest_result
