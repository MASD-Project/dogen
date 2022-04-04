# -*- mode: cmake; cmake-tab-width: 4; indent-tabs-mode: nil -*-
#
# Copyright (C) 2012-2022 Marco Craveiro <marco.craveiro@gmail.com>
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
cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

#
# Handle input parameters to script. Define them as internal CMake
# variables.
#
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

#
# Detect if we are in GitHub or not.
#
if(NOT DEFINED "ENV{GITHUB_ACTIONS}")
    message(STATUS "This script is being run outside of GitHub-Actions.")
else ()
    message(STATUS "This script is being run inside of GitHub-Actions")
endif()

#
# Ensure all mandatory parameters have been set.
#
if(NOT DEFINED model)
    message(FATAL_ERROR "CTest model parameter not defined.")
endif()

if(NOT DEFINED preset)
    message(FATAL_ERROR "CTest preset parameter not defined.")
endif()

if(NOT DEFINED configuration)
    message(FATAL_ERROR "CTest configuration parameter not defined.")
endif()

#
# Setup CTest variables
#
if (DEFINED ENV{DOGEN_BUILD_PROVIDER})
    set(CTEST_SITE $ENV{DOGEN_BUILD_PROVIDER})
else()
    site_name(APP_SITE)
    set(CTEST_SITE "${APP_SITE}")
endif()

set(CTEST_BUILD_NAME "${preset}")
set(CTEST_BUILD_TARGET "package")

string(TOLOWER "${configuration}" configuration_lower)
if(configuration_lower STREQUAL "debug")
    set(CTEST_CONFIGURATION_TYPE "Debug")
else()
    set(CTEST_CONFIGURATION_TYPE "Release")
endif()

# Set the generator. This will override the presets, but we have no option as
# CTest refuses to configure unless there is a generator.
set(CTEST_CMAKE_GENERATOR "Ninja")

# Note that we expect CTest to be executed at the top-level directory.
set(CTEST_SOURCE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "Source directory: ${CTEST_SOURCE_DIRECTORY}")

# Note that we have hard-coded the paths to match the presets. This is not very
# nice but since it should not change often, it suffices.
set(CTEST_BINARY_DIRECTORY "${CTEST_SOURCE_DIRECTORY}/build/output/${preset}")
message(STATUS "Binary directory: ${CTEST_BINARY_DIRECTORY}")

# Determine the number of jobs to run in parallel.
include(ProcessorCount)
ProcessorCount(nproc)
message(STATUS "Available processors: ${nproc}")
if(NOT "$ENV{CTEST_MAX_PARALLELISM}" STREQUAL "")
    if(nproc GREATER "$ENV{CTEST_MAX_PARALLELISM}")
        set(nproc "$ENV{CTEST_MAX_PARALLELISM}")
    endif()
endif()

# We assume Ninja, but this also works for make.
message(STATUS "Number of parallel jobs: ${nproc}")
set(CTEST_BUILD_FLAGS "-l${nproc}")

# Set limits for test output
set(CTEST_CUSTOM_MAXIMUM_PASSED_TEST_OUTPUT_SIZE 0)
set(CTEST_CUSTOM_MAXIMUM_FAILED_TEST_OUTPUT_SIZE 0)
set(CTEST_CUSTOM_MAXIMUM_NUMBER_OF_WARNINGS 50)

# How long to wait between timed-out CTest submissions
set(retry_delay 300)

# How many times to retry timed-out CTest submissions
set(retry_count 10)

set(WITH_COVERAGE false)
if(DEFINED code_coverage)
    if (code_coverage EQUAL 1)
        if (CMAKE_COMPILER_IS_GNUCXX)
            find_program(CTEST_COVERAGE_COMMAND NAMES gcov)
            message(STATUS "Looking for gcov.")
        elseif(CMAKE_COMPILER_IS_CLANGXX)
            message(STATUS "Looking for llvm-cov.")
            find_program(CTEST_COVERAGE_COMMAND NAMES llvm-cov)
        else()
            message(STATUS "Compiler does not support code coverage.")
        endif()

        if(NOT CTEST_COVERAGE_COMMAND)
            message(STATUS "gcov not found, disabling coverage.")
            set(WITH_COVERAGE false)
        else()
            message(STATUS "Found gcov (${CTEST_COVERAGE_COMMAND})...")
            set(cmake_defines ${cmake_defines} "-DWITH_PROFILING=On")
            set(CTEST_COVERAGE_EXTRA_FLAGS "--preserve-paths")
            set(WITH_COVERAGE true)
        endif()
    else()
        message(STATUS "Coverage not enabled.")
    endif()
else()
    message(STATUS "Coverage not enabled.")
endif()

# only run these for Nightly.
set(WITH_MEMCHECK false)

#
# Step: start the build
#
ctest_start(${model})

#
# Step: Version control.
#
find_package(Git)
set(CTEST_UPDATE_COMMAND "${GIT_EXECUTABLE}")

# In CI, we do not actually want to run an update, just retrieve the current
# version.
set(CTEST_UPDATE_VERSION_ONLY ON)
ctest_update(RETURN_VALUE update_result)
if(git_result)
    message(FATAL_ERROR "Failed to update source code from git.")
endif()

# Setup the preset for configuration.
set(cmake_args ${cmake_defines} "--preset ${preset}")
ctest_configure(OPTIONS "${cmake_args}" RETURN_VALUE configure_result)
if(configure_result)
    message(FATAL_ERROR "Failed to configure")
endif()

#
# Step: build.
#
ctest_build()

#
# Step: test.
#
# Note: because we are doing nothing with the return value, the build will be
# green even when tests fail. This is OK because we rely on CDash to see the
# testing status. Travis/AppVeyor just tells us weather the build and packaging
# steps have worked or failed.
#
ctest_test()

#
# Step: code coverage
#
if(WITH_COVERAGE)
    ctest_coverage()
endif()

#
# Step: memcheck.
#
if(WITH_MEMCHECK AND CTEST_MEMORYCHECK_COMMAND)
    ctest_memcheck(PARALLEL_LEVEL ${number_of_jobs})
endif()

#
# Step: submit build results
#
ctest_submit(RETRY_COUNT ${retry_count} RETRY_DELAY ${retry_delay})
