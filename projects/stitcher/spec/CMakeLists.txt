# -*- mode: cmake; tab-width: 4; indent-tabs-mode: nil -*-
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
set(stitcher_spec_files "")
file(GLOB_RECURSE stitcher_spec_files RELATIVE
    "${CMAKE_CURRENT_SOURCE_DIR}/"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

set(all_files "")
file(GLOB_RECURSE all_files RELATIVE
    "${CMAKE_CURRENT_SOURCE_DIR}/../src"
    "${CMAKE_CURRENT_SOURCE_DIR}/../src/*.cpp")

set(stitcher_files "")
set(ignore_file false)
foreach(cpp_file ${all_files})
    if("${cpp_file}" MATCHES "stitcher.cpp")
        set(ignore_file true)
    endif()

    if(NOT ignore_file)
        set(stitcher_files ${stitcher_files}
            "${CMAKE_CURRENT_SOURCE_DIR}/../src/${cpp_file}")
    endif()
    set(ignore_file false)
endforeach()

add_executable(stitcher_spec ${stitcher_spec_files} ${stitcher_files})
set(binary_name "dogen_stitcher_spec")
set_target_properties(stitcher_spec PROPERTIES OUTPUT_NAME ${binary_name})

target_link_libraries(stitcher_spec
    stitch
    utility
    config
    ${Boost_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT})

set(stitcher_spec_cmd ${stage_bin_dir}/${binary_name} ${boost_test_parameters})

add_custom_target(run_stitcher_spec
    COMMAND ${stitcher_spec_cmd}
    WORKING_DIRECTORY ${stage_bin_dir}
    DEPENDS stitcher_spec)
add_dependencies(run_all_specs run_stitcher_spec)

add_boost_tests(stitcher ${stitcher_spec_files})
install(TARGETS stitcher_spec RUNTIME DESTINATION bin COMPONENT tests)
