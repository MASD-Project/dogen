# -*- mode: cmake; cmake-tab-width: 4; indent-tabs-mode: nil -*-
#
# Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
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
cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

# handle input parameters to script.
if(DEFINED CTEST_SCRIPT_ARG)
    # transform ctest script arguments of the form
    # script.ctest,var1=value1,var2=value2
    # to variables with the respective names set to the respective values
    string(REPLACE "," ";" script_args "${CTEST_SCRIPT_ARG}")
    foreach(current_var ${script_args})
        if ("${current_var}" MATCHES "^([^=]+)=(.+)$")
            set("${CMAKE_MATCH_1}" "${CMAKE_MATCH_2}")
        endif()
    endforeach()
endif()

# no limits for test output
set(CTEST_CUSTOM_MAXIMUM_PASSED_TEST_OUTPUT_SIZE 0)
set(CTEST_CUSTOM_MAXIMUM_FAILED_TEST_OUTPUT_SIZE 0)


if(NOT DEFINED configuration_type)
    message(FATAL_ERROR "Configuration type parameter not defined.")
endif()

if(NOT DEFINED generator)
    message(FATAL_ERROR "Generator parameter not defined.")
endif()

if(NOT DEFINED compiler)
    message(FATAL_ERROR "Compiler parameter not defined.")
endif()

set(environment_vars "")
if(${compiler} STREQUAL "gcc8")
    set(ENV{CC} "gcc-8")
    set(ENV{CXX} "g++-8")
elseif(${compiler} STREQUAL "clang7")
    set(ENV{CC} "clang-7")
    set(ENV{CXX} "clang++-7")
elseif(${compiler} STREQUAL "clang6")
    set(ENV{CC} "clang-6.0")
    set(ENV{CXX} "clang++-6.0")
else()
    message(FATAL_ERROR "Unrecognised compiler: ${compiler}")
endif()

set(CTEST_PROJECT_NAME "dogen")
if (DEFINED ENV{BUILD_AGENT})
    set(CTEST_SITE $ENV{BUILD_AGENT})
else()
    set(CTEST_SITE $ENV{COMPUTERNAME})
endif()
set(CTEST_CMAKE_GENERATOR "${generator}")
set(CTEST_CONFIGURATION_TYPE "${configuration_type}")
set(CTEST_BUILD_NAME "${compiler}-${CMAKE_SYSTEM}-${CMAKE_SYSTEM_PROCESSOR}-${configuration_type}")

if(NOT DEFINED number_of_jobs)
  set(number_of_jobs 1)
endif()

set(CTEST_BUILD_TARGET "package")
set(CTEST_SOURCE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
set(build_folder "${compiler}/${CTEST_CONFIGURATION_TYPE}")
set(CTEST_BINARY_DIRECTORY
  "${CMAKE_CURRENT_SOURCE_DIR}/build/output/${build_folder}")

ctest_start("Continuous")

if(DEFINED ENV{CMAKE_TOOLCHAIN_FILE})
    set(cmake_defines "-DCMAKE_TOOLCHAIN_FILE=$ENV{CMAKE_TOOLCHAIN_FILE}")
endif()

ctest_configure(BUILD ${CTEST_BINARY_DIRECTORY} OPTIONS ${cmake_defines})

if(NOT DEFINED number_of_jobs)
  set(number_of_jobs 1)
endif()
set(CTEST_BUILD_FLAGS -j${number_of_jobs})
ctest_build()

ctest_test(RETURN_VALUE retval)
ctest_submit()
