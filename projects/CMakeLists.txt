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
if (WITH_BOOST_TEST_REPORTING)
    set(boost_test_parameters ${boost_test_parameters} "--log_format=XML"
        "--report_format=XML")
endif()

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
                     set(sink_setup "")
                     if (WITH_BOOST_TEST_REPORTING)
                         set(sink_setup
                             "--log_sink=log_${test_suite}_${test_name}.xml"
                             "--report_sink=report_${test_suite}_${test_name}.xml")
                     endif()

                     set(tests_cmd ${stage_bin_dir}/${test_module})
                     add_test(${test_module}/${test_suite}/${test_name}
                         ${CMAKE_COMMAND} -E chdir ${stage_bin_dir}
                         ${tests_cmd} --run_test=${test_suite}/${test_name}
                         ${boost_test_parameters} ${sink_setup})
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

if (UNIX)
    check_library_exists(rt clock_gettime "" HAVE_CLOCK_GETTIME)
    if (HAVE_CLOCK_GETTIME)
        message(STATUS "Requires clock_gettime.")
        set(CMAKE_REQUIRED_LIBRARIES ${CMAKE_REQUIRED_LIBRARIES} rt)
    else()
        message(STATUS "Does NOT require clock_gettime.")
    endif()
endif()

#
# Use C++ 17 on all compilers.
#
set(CMAKE_CXX_STANDARD 17)

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
    add_definitions(-D_GLIBCXX_USE_CXX11_ABI=1)
    if(APPLE)
        set(other_flags "${other_flags} -fvisibility=default")
    else()
        set(other_flags "${other_flags} -frtti -fvisibility-inlines-hidden")
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

    if (WIN32)
        # ignore fuzzy link errors
        set(CMAKE_EXE_LINKER_FLAGS
            "${CMAKE_EXE_LINKER_FLAGS} -Wl,-enable-stdcall-fixup")
        set(CMAKE_SHARED_LINKER_FLAGS
            "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-enable-stdcall-fixup")
    elseif(UNIX AND NOT APPLE)
        # use the Gold linker.
        set(CMAKE_EXE_LINKER_FLAGS
            "${CMAKE_EXE_LINKER_FLAGS} -Wl,-fuse-ld=gold")
        set(CMAKE_SHARED_LINKER_FLAGS
            "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-fuse-ld=gold")
    endif()

elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC" OR
        CMAKE_CXX_SIMULATE_ID MATCHES "MSVC")

    if(${MSVC_VERSION} GREATER 1399) # 1400+ => VC2005+
        # cannot use incremental rebuild
        string(REPLACE "/Gm" "" CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG}")
        string(REPLACE "/Gm" "" CMAKE_C_FLAGS_RELEASE
            "${CMAKE_C_FLAGS_RELEASE}")
        string(REPLACE "/Gm" "" CMAKE_CXX_FLAGS_DEBUG
            "${CMAKE_CXX_FLAGS_DEBUG}")
        string(REPLACE "/Gm" "" CMAKE_CXX_FLAGS_RELEASE
            "${CMAKE_CXX_FLAGS_RELEASE}")

        # workaround for C1128: number of sections exceeded object
        # file format limit.
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")
    endif()

    # It seems Wall and /W4 are not practical for now as it includes
    # all of the third party headers.
    # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    set(CMAKE_CXX_FLAGS
        "${CMAKE_CXX_FLAGS} /D _SILENCE_CXX17_OLD_ALLOCATOR_MEMBERS_DEPRECATION_WARNING")
    set(CMAKE_CXX_FLAGS
        "${CMAKE_CXX_FLAGS} /D _SILENCE_CXX17_ALLOCATOR_VOID_DEPRECATION_WARNING")
    set(CMAKE_CXX_FLAGS
        "${CMAKE_CXX_FLAGS} /D CRT_SECURE_NO_WARNINGS")

    foreach(flag_var CMAKE_C_FLAGS_DEBUG CMAKE_CXX_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE CMAKE_CXX_FLAGS_RELEASE CMAKE_C_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELWITHDEBINFO CMAKE_CXX_FLAGS_RELWITHDEBINFO)
        string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
        string(REGEX REPLACE "/MDd" "/MTd" ${flag_var} "${${flag_var}}")
    endforeach(flag_var)

    # Options specific to clang-cl. We suppress a number of warnings
    # because at present the code is littered with these coming out of
    # third party libraries like boost.
    if (CMAKE_COMPILER_IS_CLANGXX)
        # Ingore the annoying "locally defined symbol imported"
        # warning we get from boost thread on clang-cl.
        set(CMAKE_EXE_LINKER_FLAGS
            "${CMAKE_EXE_LINKER_FLAGS} /IGNORE:4217")

        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Xclang -Wno-unknown-pragmas")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Xclang -Wno-assume")
        set(CMAKE_CXX_FLAGS
            "${CMAKE_CXX_FLAGS} -Xclang -Wno-deprecated-declarations")
        set(CMAKE_CXX_FLAGS
            "${CMAKE_CXX_FLAGS} -Xclang -Wno-delete-non-virtual-dtor")
        set(CMAKE_CXX_FLAGS
            "${CMAKE_CXX_FLAGS} -Xclang -Wno-potentially-evaluated-expression")
    endif()

    if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
        # flag not supported by clang-cl
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")

        # For some reason CMake seems to be including the debug
        # version of this library on release builds as well so we
        # need to ignore it. Not adding this to clang-cl as it
        # does not seem to recognise it.
        set(CMAKE_SHARED_LINKER_FLAGS_RELEASE
            "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /NODEFAULTLIB:libcmtd")
        set(CMAKE_EXE_LINKER_FLAGS_RELEASE
            "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /NODEFAULTLIB:libcmtd")
    endif()

    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG}" CACHE STRING "MSVC C Debug MT flags " FORCE)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}" CACHE STRING "MSVC CXX Debug MT flags " FORCE)
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}" CACHE STRING "MSVC C Release MT flags " FORCE)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}" CACHE STRING "MSVC CXX Release MT flags " FORCE)
    set(CMAKE_C_FLAGS_MINSIZEREL "${CMAKE_C_FLAGS_MINSIZEREL}" CACHE STRING "MSVC C Debug MT flags " FORCE)
    set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL}" CACHE STRING "MSVC C Release MT flags " FORCE)
    set(CMAKE_C_FLAGS_RELWITHDEBINFO "${CMAKE_C_FLAGS_RELWITHDEBINFO}" CACHE STRING "MSVC CXX Debug MT flags " FORCE)
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO}" CACHE STRING "MSVC CXX Release MT flags " FORCE)

endif()

# user includes
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

if (WITH_RELATIONAL_SUPPORT)
    include_directories(
        ${CMAKE_SOURCE_DIR}/projects/dogen.relational/include
        )
endif()

# Model reference directories
set(DOGEN_REFERENCE_OPTIONS "")
list(APPEND DOGEN_REFERENCE_OPTIONS
    --reference-directory ${CMAKE_CURRENT_SOURCE_DIR}/dogen/modeling)
list(APPEND DOGEN_REFERENCE_OPTIONS
    --reference-directory ${CMAKE_CURRENT_SOURCE_DIR}/dogen.cli/modeling)
list(APPEND DOGEN_REFERENCE_OPTIONS
    --reference-directory ${CMAKE_CURRENT_SOURCE_DIR}/dogen.physical/modeling)
list(APPEND DOGEN_REFERENCE_OPTIONS
    --reference-directory ${CMAKE_CURRENT_SOURCE_DIR}/dogen.dia/modeling)
list(APPEND DOGEN_REFERENCE_OPTIONS
    --reference-directory ${CMAKE_CURRENT_SOURCE_DIR}/dogen.org/modeling)
list(APPEND DOGEN_REFERENCE_OPTIONS
    --reference-directory ${CMAKE_CURRENT_SOURCE_DIR}/dogen.tracing/modeling)
list(APPEND DOGEN_REFERENCE_OPTIONS
    --reference-directory ${CMAKE_CURRENT_SOURCE_DIR}/dogen.codec/modeling)
list(APPEND DOGEN_REFERENCE_OPTIONS
    --reference-directory ${CMAKE_CURRENT_SOURCE_DIR}/dogen.text/modeling)
list(APPEND DOGEN_REFERENCE_OPTIONS
    --reference-directory ${CMAKE_CURRENT_SOURCE_DIR}/dogen.logical/modeling)
list(APPEND DOGEN_REFERENCE_OPTIONS
    --reference-directory ${CMAKE_CURRENT_SOURCE_DIR}/dogen.templating/modeling)
list(APPEND DOGEN_REFERENCE_OPTIONS
    --reference-directory ${CMAKE_CURRENT_SOURCE_DIR}/dogen.orchestration/modeling)
list(APPEND DOGEN_REFERENCE_OPTIONS
    --reference-directory ${CMAKE_CURRENT_SOURCE_DIR}/dogen.utility/modeling)
list(APPEND DOGEN_REFERENCE_OPTIONS
    --reference-directory ${CMAKE_CURRENT_SOURCE_DIR}/dogen.variability/modeling)
list(APPEND DOGEN_REFERENCE_OPTIONS
    --reference-directory ${CMAKE_CURRENT_SOURCE_DIR}/dogen.relational/modeling)
list(APPEND DOGEN_REFERENCE_OPTIONS
    --reference-directory ${CMAKE_CURRENT_SOURCE_DIR}/dogen.identification/modeling)
list(APPEND DOGEN_REFERENCE_OPTIONS
    --reference-directory ${CMAKE_CURRENT_SOURCE_DIR}/dogen.modeling/org)

get_directory_property(dirs INCLUDE_DIRECTORIES)
set(global_includes "")
foreach(dir IN LISTS dirs)
    set(ODB_EXECUTABLE_GLOBAL_ARGS ${ODB_EXECUTABLE_GLOBAL_ARGS} -I ${dir})
endforeach()

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

if (WITH_RELATIONAL_SUPPORT)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dogen.relational)
endif()
