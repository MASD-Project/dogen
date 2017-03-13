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

set(include_odb_dir "${CMAKE_CURRENT_SOURCE_DIR}/include/dogen/test_models/lam_model/odb")
set(all_odb_files "")
file(GLOB_RECURSE all_odb_files RELATIVE
    "${include_odb_dir}/"
    "${include_odb_dir}/*_pragmas.hpp")

set(src_odb_dir "${CMAKE_CURRENT_SOURCE_DIR}/src/odb/")
if(NOT EXISTS "${src_odb_dir}")
    file(MAKE_DIRECTORY "${src_odb_dir}")
endif()

add_custom_target(odb_lam_model
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMAND mv ${include_odb_dir}/*.cpp ${src_odb_dir})

set(ignore_file false)
set(include_types_dir "${CMAKE_CURRENT_SOURCE_DIR}/include/dogen/test_models/lam_model/types")
foreach(odb_file ${all_odb_files})
    if (odb_file MATCHES "all_pragmas.hpp")
        set(ignore_file true)
    endif()

    if(NOT ignore_file)
        set(type_name "")
        string(REPLACE "_pragmas.hpp" "" type_name ${odb_file})
        string(REPLACE "\\" "_" type_name ${type_name})
        string(REPLACE "/" "_" type_name ${type_name})

        set(target_name "odb_lam_model_${type_name}")
        add_custom_target(${target_name}
            COMMENT "ODB ${type_name}"
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMAND ${ODB_EXECUTABLE}
            --options-file ${CMAKE_CURRENT_SOURCE_DIR}/src/options.odb
            --output-dir ${include_odb_dir}/
            --odb-epilogue '\#include \"dogen/test_models/lam_model/odb/${odb_file}\"'
            -I ${ODB_INCLUDE_DIRS} -I ${CMAKE_CURRENT_SOURCE_DIR}/include
            ${include_types_dir}/${type_name}.hpp)

        add_dependencies(odb_lam_model ${target_name})
    endif()
    set(ignore_file false)
endforeach()
