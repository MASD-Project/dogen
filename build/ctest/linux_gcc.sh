#!/bin/bash

if [ "$#" -ne "3" ]; then
    echo "linux_gcc.sh MODEL PRODUCT BUILD_TYPE" >&2
    exit 1
fi

model="$1"
product="$2"
build_type="$3"

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

build_dir="/home/ctest/build"
ctest_script="/home/ctest/scripts/CTest.cmake"
export CTEST_BUILD_DIR="${build_dir}"

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

git_commit="`git rev-list -n 1 HEAD`"

grep_result=0;
ctest_result=0;
while [ "${grep_result}" == "0" ];
do
    echo "`date +"%Y-%m-%d %H:%M:%S"` INFO Starting CTest " \
        >> ${build_dir}/${log} 2 2>&1
    echo "`date +"%Y-%m-%d %H:%M:%S"` INFO Scripts version: ${git_commit}" \
        >> ${build_dir}/${log} 2 2>&1
    ctest --extra-verbose --script "${args}" \
        --output-log "${build_dir}/ctest-${log}" \
        >> ${build_dir}/${log} 2>&1
    ctest_result=$?
    tail -n1 ${build_dir}/${log} | grep "Failed to update files from git"
    grep_result=$?
done
exit $ctest_result
