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
set(name "dogen.m2t.csharp")
set(lib_binary_name ${name})
set(lib_target_name ${name}.lib)

set(files "")
file(GLOB_RECURSE files RELATIVE
    "${CMAKE_CURRENT_SOURCE_DIR}/"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

set(lib_files ${files})
add_library(${lib_target_name} ${lib_files})
set_target_properties(${lib_target_name} PROPERTIES
    OUTPUT_NAME ${lib_binary_name})
set_target_properties(${lib_target_name}
    PROPERTIES VERSION ${DOGEN_VERSION} SOVERSION ${DOGEN_VERSION_MAJOR})

target_link_libraries(${lib_target_name}
    dogen.variability.lib
    dogen.physical.lib
    dogen.logical.lib
    ${Boost_LIBRARIES})

install(TARGETS ${lib_target_name}
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    COMPONENT libraries)
