# -*- mode: cmake; tab-width: 4; indent-tabs-mode: nil -*-
#
# Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
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
set(all_files "")
file(GLOB_RECURSE all_files RELATIVE
    "${CMAKE_CURRENT_SOURCE_DIR}/"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_library(quilt_cpp STATIC ${all_files})
target_link_libraries(quilt_cpp
    formatters
    quilt
    ${Boost_LIBRARIES})

set_target_properties(quilt_cpp PROPERTIES
    OUTPUT_NAME dogen_quild_cpp)

install(TARGETS quilt_cpp ARCHIVE DESTINATION lib COMPONENT libraries)

add_custom_target(stitch_quilt_cpp
    COMMENT "Stitching Quilt C++ model" VERBATIM
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMAND ${stitcher_binary}
    --target ${CMAKE_CURRENT_SOURCE_DIR}/
    --verbose)
add_dependencies(stitch_all stitch_quilt_cpp)
