# -*- mode: cmake; cmake-tab-width: 4; indent-tabs-mode: nil -*-
#
# Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
# MA 02110-1301, USA.
#

# parameters for boost tests
set(boost_test_parameters "--log_level=error")

# tests to ignore
set(boost_tests_ignore "")

if (WIN32)
    # This test fails on windows. This is because we are generating paths
    # that are too large for windows. We tried moving it to TEMP but even
    # then the test still fails. The test is set to ignore from the
    # CMakeLists that adds boost tests.
    set(boost_tests_ignore
        enabling_detailed_tracing_with_org_mode_results_in_expected_trace_files)
endif()

#
# macro to create CTest tests for each boost unit tests
#
macro(add_boost_tests test_module)
    foreach(cpp_file ${ARGN})
        file(READ "${cpp_file}" contents)

        string(REGEX MATCHALL "BOOST_AUTO_TEST_SUITE(\\([A-Za-z_0-9]+\\))"
            found_suites ${contents})

        list(LENGTH found_suites total_suites)
         if (total_suites GREATER 1)
             message(FATAL_ERROR "Only one test suite per file is supported. File: ${cpp_file}")
         elseif (total_suites EQUAL 1)
             list (GET found_suites 0 test_suite)
             string(REGEX REPLACE "BOOST_AUTO_TEST_SUITE(\\([A-Za-z_0-9]+\\))"
                 "\\1" test_suite ${test_suite})
             string(REPLACE "(" "" test_suite ${test_suite})
             string(REPLACE ")" "" test_suite ${test_suite})

             string(REGEX MATCHALL "BOOST_AUTO_TEST_CASE\\(([A-Za-z_0-9]+)\\)"
                 found_tests ${contents})
             foreach(hit ${found_tests})
                 string(REGEX REPLACE "BOOST_AUTO_TEST_CASE(\\([A-Za-z_0-9]+\\))"
                     "\\1" test_name ${hit})
                 string(REPLACE "(" "" test_name ${test_name})
                 string(REPLACE ")" "" test_name ${test_name})

                 if (${test_name} IN_LIST boost_tests_ignore)
                     message(STATUS "Ignoring test: ${test_name}")
                 else()
                     set(tests_cmd ${stage_bin_dir}/${test_module})
                     add_test(${test_module}/${test_suite}/${test_name}
                         ${CMAKE_COMMAND} -E chdir ${stage_bin_dir}
                         ${tests_cmd} --run_test=${test_suite}/${test_name}
                         ${boost_test_parameters})
                 endif()
             endforeach()
         endif()
    endforeach()
endmacro()

#
# compiler and linker flags
#
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_COMPILER_IS_CLANGXX "TRUE")
endif()

#
# Use C++ 17 on all compilers.
#
set(CMAKE_CXX_STANDARD 17 CACHE STRING "The C++ standard to use")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANGXX
        AND NOT "x${CMAKE_CXX_SIMULATE_ID}" STREQUAL "xMSVC")
    # enable as many warnings as possible
    set(warning_flags "-Wall -Wextra -Wconversion")

    if (CMAKE_COMPILER_IS_GNUCXX)
        set(warning_flags "${warning_flags} -Wno-maybe-uninitialized")
    endif()

    if (CMAKE_COMPILER_IS_CLANGXX)
        # disable mismatched tags as there are STL inconsistencies that
        # make it a bit useless.
        set(warning_flags "${warning_flags} -Wno-mismatched-tags")

        # force DWARF version to 4 in order to keep Valgrind happy.
        set(warning_flags "${warning_flags} -gdwarf-4")
        if(CCACHE_PROGRAM)
            # CCache and Clang don't seem to play nice when it comes
            # to unused arguments.
            set(warning_flags "${warning_flags} -Qunused-arguments")
        endif()
    endif()

    # issue all the warnings demanded by strict iso c and iso c++
    set(warning_flags "${warning_flags} -pedantic")

    # treat warnings as errors
    set(warning_flags "${warning_flags} -Werror")

    # do not issue warnings for system headers
    set(warning_flags "${warning_flags} -Wno-system-headers")

    # overloaded virtual function has a different signature
    set(warning_flags "${warning_flags} -Woverloaded-virtual")

    # make string constants const char*
    set(warning_flags "${warning_flags} -Wwrite-strings")

    # enable RTTI
    set(other_flags "${other_flags} -frtti")

    # handle visibility settings
    if(APPLE)
        set(other_flags "${other_flags} -fvisibility=default")
    else()
        set(other_flags "${other_flags} -fvisibility-inlines-hidden")
        set(other_flags "${other_flags} -fvisibility=hidden")
    endif()

    set(profiling_flags "")
    if(WITH_PROFILING)
        if (CMAKE_COMPILER_IS_GNUCXX)
            # set absolute path to avoid problems with relative path. This
            # only works with GCC.
            set(profiling_flags "-fprofile-abs-path")
        endif()

        # do not use --coverage to support both gcc and clang.
        set(profiling_flags "${profiling_flags} -fprofile-arcs")
        set(profiling_flags "${profiling_flags} -ftest-coverage")
    endif()

    # set the flags
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${warning_flags}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${other_flags}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${profiling_flags}")

    if(UNIX AND NOT APPLE)
        # use the Gold linker.
        set(CMAKE_EXE_LINKER_FLAGS
            "${CMAKE_EXE_LINKER_FLAGS} -Wl,-fuse-ld=gold")
        set(CMAKE_SHARED_LINKER_FLAGS
            "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-fuse-ld=gold")
    endif()
endif()

# Model reference directories
set(DOGEN_REFERENCE_OPTIONS "")
set(reference_prefix --reference-directory ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND DOGEN_REFERENCE_OPTIONS ${reference_prefix}/dogen/modeling)
list(APPEND DOGEN_REFERENCE_OPTIONS ${reference_prefix}/dogen.cli/modeling)
list(APPEND DOGEN_REFERENCE_OPTIONS ${reference_prefix}/dogen.physical/modeling)
list(APPEND DOGEN_REFERENCE_OPTIONS ${reference_prefix}/dogen.dia/modeling)
list(APPEND DOGEN_REFERENCE_OPTIONS ${reference_prefix}/dogen.org/modeling)
list(APPEND DOGEN_REFERENCE_OPTIONS ${reference_prefix}/dogen.tracing/modeling)
list(APPEND DOGEN_REFERENCE_OPTIONS ${reference_prefix}/dogen.codec/modeling)
list(APPEND DOGEN_REFERENCE_OPTIONS ${reference_prefix}/dogen.text/modeling)
list(APPEND DOGEN_REFERENCE_OPTIONS ${reference_prefix}/dogen.logical/modeling)
list(APPEND DOGEN_REFERENCE_OPTIONS ${reference_prefix}/dogen.templating/modeling)
list(APPEND DOGEN_REFERENCE_OPTIONS ${reference_prefix}/dogen.orchestration/modeling)
list(APPEND DOGEN_REFERENCE_OPTIONS ${reference_prefix}/dogen.utility/modeling)
list(APPEND DOGEN_REFERENCE_OPTIONS ${reference_prefix}/dogen.variability/modeling)
list(APPEND DOGEN_REFERENCE_OPTIONS ${reference_prefix}/dogen.relational/modeling)
list(APPEND DOGEN_REFERENCE_OPTIONS ${reference_prefix}/dogen.identification/modeling)
list(APPEND DOGEN_REFERENCE_OPTIONS ${reference_prefix}/dogen.modeling/org)

#
# user includes.
# FIXME: temporary hack until we add local include support to generated
# FIXME: CMakeFiles. This is required to get the Nightly build to work.
#
include_directories(
    # generated header files
    ${stage_inc_dir}/

    # real code
    ${CMAKE_SOURCE_DIR}/projects/dogen/include
    ${CMAKE_SOURCE_DIR}/projects/dogen.identification/include
    ${CMAKE_SOURCE_DIR}/projects/dogen.physical/include
    ${CMAKE_SOURCE_DIR}/projects/dogen.cli/include
    ${CMAKE_SOURCE_DIR}/projects/dogen.utility/include
    ${CMAKE_SOURCE_DIR}/projects/dogen.variability/include
    ${CMAKE_SOURCE_DIR}/projects/dogen.org/include
    ${CMAKE_SOURCE_DIR}/projects/dogen.dia/include
    ${CMAKE_SOURCE_DIR}/projects/dogen.codec/include
    ${CMAKE_SOURCE_DIR}/projects/dogen.tracing/include
    ${CMAKE_SOURCE_DIR}/projects/dogen.logical/include
    ${CMAKE_SOURCE_DIR}/projects/dogen.orchestration/include
    ${CMAKE_SOURCE_DIR}/projects/dogen.templating/include
    ${CMAKE_SOURCE_DIR}/projects/dogen.text/include
)

#
# add all other projects
#
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dogen)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dogen.identification)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dogen.physical)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dogen.cli)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dogen.utility)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dogen.variability)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dogen.org)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dogen.dia)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dogen.codec)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dogen.tracing)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dogen.logical)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dogen.orchestration)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dogen.modeling)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dogen.templating)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dogen.text)
