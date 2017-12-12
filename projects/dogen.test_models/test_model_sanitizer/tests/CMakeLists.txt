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
set(name "test_model_sanitizer")
set(tests_name "${name}.tests")
set(binary_name "dogen.${name}.tests")
set(candidate_files "")
set(files "")
file(GLOB_RECURSE candidate_files RELATIVE
    "${CMAKE_CURRENT_SOURCE_DIR}/"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

set(ignore_file false)
foreach(candidate_file ${candidate_files})
    if(NOT ODB_FOUND)
        if (candidate_file MATCHES "database")
            set(ignore_file true)
        endif()
    endif()

    if(NOT ignore_file)
        set(files ${files} ${candidate_file})
    endif()
    set(ignore_file false)
endforeach()

# we need to add these manually as the point of this test model
# is not to generate a make file.
file(GLOB_RECURSE disable_cmakelists_files ABSOLUTE
    "${CMAKE_SOURCE_DIR}/projects/dogen.test_models/disable_cmakelists/src/*.cpp")

add_executable(${tests_name} ${files} ${disable_cmakelists_files})
set_target_properties(${tests_name} PROPERTIES OUTPUT_NAME ${binary_name})

target_link_libraries(${tests_name}
    cpp_model
    cpp_98
    compressed
    disable_facet_folders
    enable_facet_types
    enable_facet_hash
    enable_facet_io
    enable_facet_serialization
    two_layers_with_objects
    std_model
    boost_model
    utility
    ${LIBXML2_LIBRARIES}
    ${CMAKE_REQUIRED_LIBRARIES}
    ${Boost_LIBRARIES})

# FIXME: link against database if feature is on?

set(command $<TARGET_FILE:${tests_name}> ${boost_test_parameters})

add_custom_target(run_${tests_name}
    COMMENT "Running ${tests_name}" VERBATIM
    COMMAND ${command}
    WORKING_DIRECTORY ${stage_bin_dir}
    DEPENDS ${tests_name})

add_dependencies(run_all_tests run_${tests_name})

if(WITH_BENCHMARKS)
    add_custom_target(benchmark_${tests_name}
        COMMENT "Benchmarking testing ${tests_name}" VERBATIM
        COMMAND ${benchmark_command} ${benchmark_repeats}
        ${benchmark_directory}/${benchmark_prefix}${tests_name}.csv ${command}
        WORKING_DIRECTORY ${stage_bin_dir}
        DEPENDS ${tests_name})

    add_dependencies(benchmark_all benchmark_${tests_name})
endif()

add_boost_tests(${name} ${files})
install(TARGETS ${tests_name} RUNTIME DESTINATION bin COMPONENT tests)
