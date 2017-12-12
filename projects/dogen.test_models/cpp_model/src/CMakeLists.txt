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
set(files "")
file(GLOB_RECURSE files RELATIVE
    "${CMAKE_CURRENT_SOURCE_DIR}/"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

set(odb_files "")
file(GLOB_RECURSE odb_files RELATIVE
   "${CMAKE_CURRENT_SOURCE_DIR}/"
   "${CMAKE_CURRENT_SOURCE_DIR}/*.cxx")
set(files ${files} ${odb_files})

add_library(cpp_model STATIC ${files})
set_target_properties(cpp_model PROPERTIES
    OUTPUT_NAME dogen.cpp_model)

install(TARGETS cpp_model ARCHIVE DESTINATION lib COMPONENT libraries)
