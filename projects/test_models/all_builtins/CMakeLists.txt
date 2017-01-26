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
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)

install(
    DIRECTORY include/
    DESTINATION include/
    COMPONENT headers
    FILES_MATCHING PATTERN "*.hpp")

set(include_dir "${CMAKE_CURRENT_SOURCE_DIR}/include/dogen/all_builtins")
set(all_odb_files "")
file(GLOB_RECURSE all_odb_files RELATIVE
    "${include_dir}/odb/"
    "${include_dir}/odb/*_pragmas.hpp")

set(src_odb_dir "${CMAKE_CURRENT_SOURCE_DIR}/src/odb/")
if(NOT EXISTS "${src_odb_dir}")
    file(MAKE_DIRECTORY "${src_odb_dir}")
endif()

add_custom_target(codegen_all_builtins_odb
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMAND mv ${CMAKE_CURRENT_SOURCE_DIR}/include/dogen/all_builtins/odb/*.cpp
    ${src_odb_dir})

set(ignore_file false)
foreach(odb_file ${all_odb_files})
    if (odb_file MATCHES "all_pragmas.hpp")
        set(ignore_file true)
    endif()

    if(NOT ignore_file)
        set(type_name "")
        string(REPLACE "_pragmas.hpp" "" type_name ${odb_file})
        string(REPLACE "\\" "_" type_name ${type_name})
        string(REPLACE "/" "_" type_name ${type_name})

        set(pfh_dir "$ENV{PFH_LOCATION}")
        set(target_name "codegen_all_builtins_odb_${type_name}")
        add_custom_target(${target_name}
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMAND odb
            --options-file ${CMAKE_CURRENT_SOURCE_DIR}/src/options.odb
            --std c++11
            --output-dir ${CMAKE_CURRENT_SOURCE_DIR}/include/dogen/all_builtins/odb/
            --odb-epilogue '\#include \"dogen/all_builtins/odb/${odb_file}\"'
            -I ${pfh_dir}/include -I ${CMAKE_CURRENT_SOURCE_DIR}/include
            ${include_dir}/types/${type_name}.hpp)

        add_dependencies(codegen_all_builtins_odb ${target_name})
    endif()
    add_dependencies(codegen_all_builtins_odb codegen_all_builtins)
    set(ignore_file false)
endforeach()
