# -*- mode: cmake; cmake-tab-width: 4; indent-tabs-mode: nil -*-
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
set(name "quilt.cpp")
set(binary_name "dogen.${name}")
set(files "")
file(GLOB_RECURSE files RELATIVE
    "${CMAKE_CURRENT_SOURCE_DIR}/"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_library(${name} STATIC ${files})
target_link_libraries(${name}
    annotations
    formatting
    yarn
    wale
    stitch
    ${Boost_LIBRARIES})

set_target_properties(${name} PROPERTIES OUTPUT_NAME ${binary_name})
set_target_properties(${name}
    PROPERTIES VERSION ${DOGEN_VERSION} SOVERSION ${DOGEN_MAJOR_VERSION})

if (DOGEN_STITCHER_EXECUTABLE)
    add_custom_target(stitch_${name}
        COMMENT "Stitching Quilt C++ model" VERBATIM
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMAND ${DOGEN_STITCHER_EXECUTABLE}
        --target ${CMAKE_CURRENT_SOURCE_DIR}/
        --log-level ${DOGEN_LOG_LEVEL})
    add_dependencies(stitch_all stitch_${name})
endif()

install(TARGETS ${name} ARCHIVE DESTINATION lib COMPONENT libraries)
