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
set(spec_files "")
file(GLOB_RECURSE spec_files RELATIVE
    "${CMAKE_CURRENT_SOURCE_DIR}/"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

set(stitch_files "")
file(GLOB_RECURSE stitch_files RELATIVE
    "${CMAKE_CURRENT_SOURCE_DIR}/"
    "${CMAKE_CURRENT_SOURCE_DIR}/../src/*.cpp")

add_executable(seam_spec ${spec_files} ${stitch_files})
set(binary_name "dogen_seam_spec")
set_target_properties(seam_spec PROPERTIES OUTPUT_NAME ${binary_name})

target_link_libraries(seam_spec
    utility
    ${Boost_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT})

set(seam_spec_cmd ${stage_bin_dir}/${binary_name} ${boost_test_parameters})

add_custom_target(run_seam_spec
    COMMAND ${seam_spec_cmd}
    WORKING_DIRECTORY ${stage_bin_dir}
    DEPENDS seam_spec)
add_dependencies(run_all_specs run_seam_spec)

add_boost_tests(seam ${spec_files})
install(TARGETS seam_spec RUNTIME DESTINATION bin COMPONENT tests)
