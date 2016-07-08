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
set(name "seam")
set(binary_name "dogen.${name}.tests")
set(files "")
file(GLOB_RECURSE files RELATIVE
    "${CMAKE_CURRENT_SOURCE_DIR}/"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

set(stitch_files "")
file(GLOB_RECURSE stitch_files RELATIVE
    "${CMAKE_CURRENT_SOURCE_DIR}/"
    "${CMAKE_CURRENT_SOURCE_DIR}/../src/*.cpp")

add_executable(${name}_tests ${files} ${stitch_files})
set_target_properties(${name}_tests PROPERTIES OUTPUT_NAME ${binary_name})

target_link_libraries(${name}_tests
    utility
    ${Boost_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT})

set(command ${stage_bin_dir}/${binary_name} ${boost_test_parameters})

add_custom_target(run_${name}_tests
    COMMAND ${command}
    WORKING_DIRECTORY ${stage_bin_dir}
    DEPENDS ${name}_tests)
add_dependencies(run_all_tests run_${name}_tests)

add_boost_tests(${name} ${files})
install(TARGETS ${name}_tests RUNTIME DESTINATION bin COMPONENT tests)
