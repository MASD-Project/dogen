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
set(name "dogen.cli")
set(lib_binary_name ${name})
set(lib_target_name ${name}.lib)

set(files "")
file(GLOB_RECURSE files RELATIVE
    "${CMAKE_CURRENT_SOURCE_DIR}/"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

set(lib_files ${files})
list(FILTER lib_files EXCLUDE REGEX "main.cpp")

add_library(${lib_target_name} ${lib_files})
set_target_properties(${lib_target_name} PROPERTIES
    OUTPUT_NAME ${lib_binary_name})
set_target_properties(${lib_target_name}
    PROPERTIES VERSION ${DOGEN_VERSION} SOVERSION ${DOGEN_VERSION_MAJOR})

target_include_directories(${lib_target_name}
    PUBLIC ${CMAKE_SOURCE_DIR}/projects/${name}/include
    PRIVATE ${stage_inc_dir}/ # generated header files
    PUBLIC ${CMAKE_SOURCE_DIR}/projects/dogen/include
    PUBLIC ${CMAKE_SOURCE_DIR}/projects/dogen.orchestration/include
    PRIVATE ${CMAKE_SOURCE_DIR}/projects/dogen.utility/include
)

target_link_libraries(${lib_target_name} PRIVATE
    dogen.lib
    dogen.orchestration.lib
    dogen.utility.lib
    Boost::boost
    Boost::date_time
    Boost::program_options
    $<$<BOOL:${USE_MSVC_LIBS}>:bcrypt>)

install(TARGETS ${lib_target_name}
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    COMPONENT libraries)

set(exe_binary_name ${name})
set(exe_target_name ${name}.exe)

set(exe_files ${files})
list(FILTER exe_files INCLUDE REGEX "main.cpp")

add_executable(${exe_target_name} ${exe_files})
set_target_properties(${exe_target_name} PROPERTIES
    OUTPUT_NAME ${exe_binary_name})

target_include_directories(${exe_target_name}
    PRIVATE ${CMAKE_SOURCE_DIR}/projects/${name}/include
    PRIVATE ${stage_inc_dir}/ # generated header files
    PRIVATE ${CMAKE_SOURCE_DIR}/projects/dogen/include
    PRIVATE ${CMAKE_SOURCE_DIR}/projects/dogen.orchestration/include
    PRIVATE ${CMAKE_SOURCE_DIR}/projects/dogen.utility/include)

target_link_libraries(${exe_target_name} PRIVATE
    ${lib_target_name}
    dogen.lib
    dogen.orchestration.lib
    dogen.utility.lib
    Boost::boost
    Boost::date_time
    Boost::program_options
    ${CMAKE_THREAD_LIBS_INIT})

install(TARGETS ${exe_target_name} RUNTIME DESTINATION bin
    COMPONENT applications)
