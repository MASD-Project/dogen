#!/bin/bash

#
# Very trivial script to use CTest to run two nightly builds (clang and gcc).
#
workspace="${HOME}/nightly"
configuration=Debug
number_of_jobs=6
build_group=Nightly
logs_dir=${workspace}/logs
clang_compiler=clang
gcc_compiler=gcc
verbosity=-VV

#
# Logs
#
if [ ! -d "${logs_dir}" ]; then
    echo "Creating the logs directory."
    mkdir ${logs_dir}
else
    echo "Deleting old logs."
    rm -f ${logs_dir}/*.log
fi

#
# C# Ref Impl
#
echo "C# Ref Impl"
product="csharp_ref_impl"
git_url="https://github.com/MASD-Project/${product}.git"
git_dir="${workspace}/${product}/master"
if [ ! -d "${git_dir}" ]; then
    git clone --depth=1 ${git_url} ${git_dir}
fi
cd ${git_dir}
git pull origin master

#
# Frozen
#
echo "Frozen"
product="frozen"
git_url="https://github.com/MASD-Project/${product}.git"
git_dir="${workspace}/${product}/master"
if [ ! -d "${git_dir}" ]; then
    git clone --depth=1 ${git_url} ${git_dir}
fi
cd ${git_dir}
git pull origin master

#
# C++ Ref Impl
#
echo "C++ Ref Impl"
product="cpp_ref_impl"
git_url="https://github.com/MASD-Project/${product}.git"
git_dir="${workspace}/${product}/master"
if [ ! -d "${git_dir}" ]; then
    git clone --depth=1 ${git_url} ${git_dir}
fi
cd ${git_dir}

# update manually as ctest won't do it for us.
git pull origin master

# compiler=${clang_compiler}
# ctest ${verbosity} --script ".ctest.cmake,configuration_type=${configuration},generator=${generator},compiler=${compiler},number_of_jobs=${JOBS},build_group=${build_group}" > ${logs_dir}/ctest_${product}_${compiler}.log 2>&1

# compiler=${gcc_compiler}
# ctest ${verbosity} --script ".ctest.cmake,configuration_type=${configuration},generator=${generator},compiler=${compiler},number_of_jobs=${JOBS},build_group=${build_group},code_coverage=1" > ${logs_dir}/ctest_${product}_${compiler}.log 2>&1

#
# Dogen
#
product="dogen"
git_url="https://github.com/MASD-Project/${product}.git"

cd ${workspace}
git_dir="${workspace}/${product}/master"
# if [ -d "${workspace}/${product}" ]; then
#     rm -rf ${workspace}/${product}
# fi
mkdir ${workspace}/${product}
cd ${workspace}/${product}
git clone --depth=1 --recurse-submodules ${git_url} master

# Build just the code generator first, do a full generation and commit that
# locally. This commit is only for the purposes of the nightly.
echo "Dogen (for generation)"
cd ${git_dir}
preset="linux-gcc-release"
cmake -DWITH_FULL_GENERATION=ON --preset ${preset} > ${logs_dir}/dogen.cli.log
cmake --build --preset ${preset} --target dogen.cli >> ${logs_dir}/dogen.cli.log

cmake -DWITH_FULL_GENERATION=ON --preset ${preset} > ${logs_dir}/dogen.cli.log
cmake --build --preset ${preset} --target gao >> ${logs_dir}/gao.log
git add -A > ${logs_dir}/git_add.log
git commit -m "Generated code." >> ${logs_dir}/git_add.log
export WITH_FULL_GENERATION=ON

echo "Dogen GCC"
preset="linux-gcc-debug"
compiler=${gcc_compiler}
ctest ${verbosity} --script "CTest.cmake,build_group=${build_group},build_name=${preset},code_coverage=1" > ${logs_dir}/ctest_${product}_${compiler}.log 2>&1

echo "Dogen clang"
preset="linux-clang-debug"
compiler=${clang_compiler}
ctest ${verbosity} --script "CTest.cmake,build_group=${build_group},build_name=${preset},code_coverage=1" > ${logs_dir}/ctest_${product}_${compiler}.log 2>&1
