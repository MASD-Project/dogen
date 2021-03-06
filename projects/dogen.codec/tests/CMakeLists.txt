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
set(name "dogen.codec")
set(lib_target_name ${name}.lib)
set(tests_binary_name ${name}.tests)
set(tests_target_name ${name}.tests)

set(files "")
file(GLOB_RECURSE files RELATIVE
    "${CMAKE_CURRENT_SOURCE_DIR}/"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable(${tests_target_name} ${files})

set_target_properties(${tests_target_name}
    PROPERTIES OUTPUT_NAME ${tests_binary_name})

target_link_libraries(${tests_target_name}
    ${lib_target_name}
    ${CMAKE_THREAD_LIBS_INIT})

set(command $<TARGET_FILE:${tests_target_name}> ${boost_test_parameters})

add_custom_target(run_${tests_target_name}
    COMMENT "Running ${tests_target_name}" VERBATIM
    COMMAND ${command}
    WORKING_DIRECTORY ${stage_bin_dir}
    DEPENDS ${tests_target_name})

add_dependencies(run_all_tests run_${tests_target_name})

if(WITH_BENCHMARKS)
    set(benchmark_file
        ${benchmark_directory}/${benchmark_prefix}${tests_target_name}.csv)
    add_custom_target(benchmark_${tests_target_name}
        COMMENT "Benchmarking testing ${tests_target_name}" VERBATIM
        COMMAND ${benchmark_command} ${benchmark_repeats} ${benchmark_file}
        ${command}
        WORKING_DIRECTORY ${stage_bin_dir}
        DEPENDS ${tests_target_name})

    add_dependencies(benchmark_all benchmark_${tests_target_name})
endif()

add_boost_tests(${tests_binary_name} ${files})

install(TARGETS ${tests_target_name} RUNTIME DESTINATION bin COMPONENT tests)
