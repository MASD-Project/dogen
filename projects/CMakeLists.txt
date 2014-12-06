# -*- mode: cmake; tab-width: 4; indent-tabs-mode: nil -*-
#
# Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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

#
# macro to create CTest tests for each boost unit tests
#
macro(add_boost_tests test_module)
    foreach(cpp_file ${ARGN})
        file(READ "${cpp_file}" contents)
        string(REGEX MATCHALL "BOOST_AUTO_TEST_CASE\\(([A-Za-z_0-9]+)\\)"
            found_tests ${contents})

        foreach(hit ${found_tests})
            string(REGEX REPLACE "BOOST_AUTO_TEST_CASE(\\([A-Za-z_0-9]+\\))"
                "\\1" test_name ${hit})
            string(REPLACE "(" "" test_name ${test_name})
            string(REPLACE ")" "" test_name ${test_name})

            string(REPLACE "_spec.cpp" "" test_suite ${cpp_file})
            string(REPLACE "spec/" "" test_suite ${test_suite})

            set(spec_cmd
                ${stage_bin_dir}/dogen_${test_module}_spec)
            add_test(${test_module}/${test_suite}/${test_name}
                ${CMAKE_COMMAND} -E chdir ${stage_bin_dir}
                ${spec_cmd} --run_test=${test_suite}/${test_name})
        endforeach()
    endforeach()
endmacro()

#
# compiler and linker flags


# enable as many warnings as possible
set(warning_flags "-Wall -Wextra")

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    # disable mismatched tags as there are STL inconsistencies that
    # make it a bit useless.
    set(warning_flags "${warning_flags} -Wno-mismatched-tags")
endif()

# issue all the warnings demanded by strict iso c and iso c++
set(warning_flags "${warning_flags} -pedantic")

# treat warnings as errors
set(warning_flags "${warning_flags} -Werror")

# definition shadows another
# FIXME: causes too many problems.
# set(warning_flags "${warning_flags} -Wshadow")

# do not issue warnings for system headers
set(warning_flags "${warning_flags} -Wno-system-headers")

# overloaded virtual function has a different signature
set(warning_flags "${warning_flags} -Woverloaded-virtual")

# make string constants const char*
set(warning_flags "${warning_flags} -Wwrite-strings")

# debug flags
if(WITH_DEBUG)
    set(optimisation_flags "-g -O0")
else()
    set(optimisation_flags "-O3")
endif()

if(WITH_PROFILING)
    # enable code profiling options
    set(profiling_flags "-fprofile-arcs -ftest-coverage")

    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        # FIXME: profiling flags appear not to be used during
        # compilation so disable the warning. bit of a hack, for now.
        set(profiling_flags "${profiling_flags} -Qunused-arguments")

        set(profiling_flags "${profiling_flags} --coverage")
        set(profiling_flags "${profiling_flags} -Xclang -coverage-cfg-checksum")
        set(profiling_flags
            "${profiling_flags} -Xclang -coverage-no-function-names-in-data")

        # 407 for gcc 4.7 compatibility of the gcov format.
        set(profiling_flags
            "${profiling_flags} -Xclang -coverage-version='407*'")

    endif()
else()
    if(WITH_COVERAGE)
        set(profiling_flags "--coverage")
    endif()
endif()

# enable RTTI
# -fvisibility=hidden
if (WIN32)
    set(other_flags "-std=gnu++11")
else()
    set(other_flags "-std=c++11")
endif()
set(other_flags "${other_flags} -frtti -fvisibility-inlines-hidden")
set(other_flags "${other_flags} -fvisibility=default")

# set the flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${optimisation_flags}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${warning_flags}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${profiling_flags}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${other_flags}")

# ignore fuzzy link errors
if (WIN32)
    set(CMAKE_EXE_LINKER_FLAGS
        "${CMAKE_EXE_LINKER_FLAGS} -Wl,-enable-stdcall-fixup")
    set(CMAKE_SHARED_LINKER_FLAGS
        "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-enable-stdcall-fixup")
endif()

# parameters for boost tests
set(boost_test_parameters "")

# user includes
include_directories(
    # generated header files
    ${stage_inc_dir}/

    # real code
    ${CMAKE_SOURCE_DIR}/projects/dia/include
    ${CMAKE_SOURCE_DIR}/projects/dia_to_sml/include
    ${CMAKE_SOURCE_DIR}/projects/frontend/include
    ${CMAKE_SOURCE_DIR}/projects/backend/include
    ${CMAKE_SOURCE_DIR}/projects/sml/include
    ${CMAKE_SOURCE_DIR}/projects/config/include
    ${CMAKE_SOURCE_DIR}/projects/cpp/include
    ${CMAKE_SOURCE_DIR}/projects/cpp_formatters/include
    ${CMAKE_SOURCE_DIR}/projects/sml_to_cpp/include
    ${CMAKE_SOURCE_DIR}/projects/formatters/include
    ${CMAKE_SOURCE_DIR}/projects/utility/include
    ${CMAKE_SOURCE_DIR}/projects/knit/include
    ${CMAKE_SOURCE_DIR}/projects/knitter/include
    )

#
# add all other projects
#
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dia)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dia/spec)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dia_to_sml/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dia_to_sml/spec)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/frontend/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/frontend/spec)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/backend/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/backend/spec)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/sml)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/sml/spec)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/config)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/config/spec)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/cpp)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/cpp/spec)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/cpp_formatters)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/cpp_formatters/spec)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/sml_to_cpp)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/sml_to_cpp/spec)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/formatters)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/formatters/spec)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/utility)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/knit)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/knitter)

# test models
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test_models)
