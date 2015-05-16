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
set(dynamic_spec_files "")
file(GLOB_RECURSE dynamic_spec_files RELATIVE
    "${CMAKE_CURRENT_SOURCE_DIR}/"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable(dynamic_spec ${dynamic_spec_files})
set(binary_name "dogen_dynamic_spec")
set_target_properties(dynamic_spec PROPERTIES OUTPUT_NAME ${binary_name})

target_link_libraries(dynamic_spec
    config
    utility
    dynamic
    ${Boost_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT})

set(dynamic_spec_cmd ${stage_bin_dir}/${binary_name} ${boost_test_parameters})

add_custom_target(run_dynamic_spec
    COMMAND ${dynamic_spec_cmd}
    WORKING_DIRECTORY ${stage_bin_dir}
    DEPENDS dynamic_spec)
add_dependencies(run_all_specs run_dynamic_spec)

add_boost_tests(dynamic ${dynamic_spec_files})
install(TARGETS dynamic_spec RUNTIME DESTINATION bin COMPONENT tests)
