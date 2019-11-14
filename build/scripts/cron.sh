#!/bin/bash

#
# Very trivial script to use CTest to run two nightly builds (clang
# and gcc). Ensure you have exported CMAKE_TOOLCHAIN_FILE before running
# this script.
export PATH=/home/marco/local/cmake-3.15.3-Linux-x86_64/bin:$PATH
export MASD_DIR=/work/DomainDrivenConsulting/masd
export CMAKE_TOOLCHAIN_FILE=${MASD_DIR}/vcpkg/masd/scripts/buildsystems/vcpkg.cmake

workspace="${HOME}/nightly"
configuration=Debug
generator=Ninja
number_of_jobs=4
build_group=Nightly
logs_dir=../logs

#
# C# Ref Impl
#
product="csharp_ref_impl"
git_url="https://github.com/MASD-Project/${product}.git"
git_dir="${workspace}/${product}"
export CSHARP_REF_IMPL_PROJECTS_DIRECTORY=${git_dir}/Src/
if [ ! -d "${git_dir}" ]; then
    git clone ${git_url} ${git_dir}
fi
cd ${git_dir}

# update manually as ctest won't do it for us.
git pull origin master

#
# C++ Ref Impl
#
product="cpp_ref_impl"
git_url="https://github.com/MASD-Project/${product}.git"
git_dir="${workspace}/${product}"
export CPP_REF_IMPL_PROJECTS_DIRECTORY=${git_dir}/projects
if [ ! -d "${git_dir}" ]; then
    git clone ${git_url} ${git_dir}
fi
cd ${git_dir}

compiler=clang8
ctest --extra-verbose --script ".ctest.cmake,configuration_type=${configuration},generator=${generator},compiler=${compiler},number_of_jobs=${JOBS},build_group=${build_group}"  > ${logs_dir}/ctest_${product}_${compiler}.log 2>&1

compiler=gcc8
ctest --extra-verbose --script ".ctest.cmake,configuration_type=${configuration},generator=${generator},compiler=${compiler},number_of_jobs=${JOBS},build_group=${build_group}"  > ${logs_dir}/ctest_${product}_${compiler}.log 2>&1

#
# Dogen
#
product="dogen"
git_url="https://github.com/MASD-Project/${product}.git"
git_dir="${workspace}/${product}"
export DOGEN_PROJECTS_DIRECTORY="${git_dir}/projects"
if [ ! -d "${git_dir}" ]; then
    git clone ${git_url} ${git_dir}
fi
cd ${git_dir}

compiler=clang8
ctest --extra-verbose --script ".ctest.cmake,configuration_type=${configuration},generator=${generator},compiler=${compiler},number_of_jobs=${number_of_jobs},build_group=${build_group},minimal_packaging=1" > ${logs_dir}/ctest_${product}_${compiler}.log 2>&1

compiler=gcc8
ctest --extra-verbose --script ".ctest.cmake,configuration_type=${configuration},generator=${generator},compiler=${compiler},number_of_jobs=${number_of_jobs},build_group=${build_group},minimal_packaging=1" > ${logs_dir}/ctest_${product}_${compiler}.log 2>&1
