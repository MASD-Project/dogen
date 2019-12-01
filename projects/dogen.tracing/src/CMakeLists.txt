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
set(name "dogen.tracing")
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

set(use_msvc_libs OFF)
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    if ("${CMAKE_CXX_SIMULATE_ID}" STREQUAL "MSVC")
        set(use_msvc_libs ON)
    endif ()
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(use_msvc_libs ON)
endif ()

if (WITH_RELATIONAL_SUPPORT)
    list(APPEND relational_lib
        -Wl,--whole-archive dogen.relational.lib  -Wl,--no-whole-archive)
    list(APPEND relational_lib odb::libodb)
    list(APPEND relational_lib odb::libodb-boost)
    list(APPEND relational_lib odb::libodb-pgsql)
    list(APPEND relational_lib odb::libodb-sqlite)
    list(APPEND relational_lib OpenSSL::SSL)
    list(APPEND relational_lib OpenSSL::Crypto)
endif()

target_link_libraries(${lib_target_name}
    dogen.lib
    dogen.utility.lib
    $<$<BOOL:${use_msvc_libs}>:bcrypt>
    ${relational_lib}
    ${Boost_LIBRARIES})

install(TARGETS ${lib_target_name}
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    COMPONENT libraries)
