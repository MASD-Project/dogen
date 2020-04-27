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
number_of_jobs=6
build_group=Nightly
logs_dir=../logs
clang_compiler=clang9
gcc_compiler=gcc9
verbosity=--progress

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
git pull origin master

compiler=${clang_compiler}
ctest ${verbosity} --script ".ctest.cmake,configuration_type=${configuration},generator=${generator},compiler=${compiler},number_of_jobs=${JOBS},build_group=${build_group}" > ${logs_dir}/ctest_${product}_${compiler}.log 2>&1

compiler=${gcc_compiler}
ctest ${verbosity} --script ".ctest.cmake,configuration_type=${configuration},generator=${generator},compiler=${compiler},number_of_jobs=${JOBS},build_group=${build_group},code_coverage=1" > ${logs_dir}/ctest_${product}_${compiler}.log 2>&1

#
# Dogen
#
product="dogen"
git_url="https://github.com/MASD-Project/${product}.git"
git_dir="${workspace}/${product}"
if [ -d "${git_dir}" ]; then
    rm -rf ${git_dir}
fi

pristine_dir="${workspace}/${product}_pristine"
if [ -d "${pristine_dir}" ]; then
    rm -rf ${pristine_dir}
fi

git clone --depth=3 ${git_url} ${git_dir}
cp -r ${git_dir} ${pristine_dir}
export DOGEN_PROJECTS_DIRECTORY="${pristine_dir}/projects"

cd ${git_dir}
build/scripts/build.linux.sh Release ${number_of_jobs} ${clang_compiler} dogen.cli > ${logs_dir}/dogen.cli.log
export DOGEN_FULL_GENERATION="1"
build/scripts/build.linux.sh Release ${number_of_jobs} ${clang_compiler} gad > ${logs_dir}/gad.log
git add -A > ${logs_dir}/git_add.log
git commit -m "Generated code." > ${logs_dir}/git_add.log

compiler=${clang_compiler}
ctest ${verbosity} --script ".ctest.cmake,configuration_type=${configuration},generator=${generator},compiler=${compiler},number_of_jobs=${number_of_jobs},build_group=${build_group},minimal_packaging=1,relational_support=1" > ${logs_dir}/ctest_${product}_${compiler}.log 2>&1

STAGE_DIR=build/output/${compiler}/${configuration}/stage

compiler=${gcc_compiler}
ctest ${verbosity} --script ".ctest.cmake,configuration_type=${configuration},generator=${generator},compiler=${compiler},number_of_jobs=${number_of_jobs},build_group=${build_group},minimal_packaging=1,relational_support=1,code_coverage=1" > ${logs_dir}/ctest_${product}_${compiler}.log 2>&1
