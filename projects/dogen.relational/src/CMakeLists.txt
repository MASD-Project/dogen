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
set(name "dogen.relational")
set(lib_binary_name ${name})
set(lib_target_name ${name}.lib)

set(files "")
file(GLOB_RECURSE files RELATIVE
    "${CMAKE_CURRENT_SOURCE_DIR}/"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

set(odb_files "")
file(GLOB_RECURSE odb_files RELATIVE
   "${CMAKE_CURRENT_SOURCE_DIR}/"
   "${CMAKE_CURRENT_SOURCE_DIR}/*.cxx")
set(files ${files} ${odb_files})

set(lib_files ${files})
add_library(${lib_target_name} ${lib_files})
set_target_properties(${lib_target_name} PROPERTIES
    OUTPUT_NAME ${lib_binary_name})

install(TARGETS ${lib_target_name}
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    COMPONENT libraries)

#
# ODB Executable Targets
#
if (ODB_EXECUTABLE)
    # Top-level targets
    add_custom_target(odb_dogen_relational)
    add_dependencies(odb_all odb_dogen_relational)

    if (NOT ODB_EXECUTABLE_GLOBAL_ARGS)
        message(WARNING "ODB_EXECUTABLE_GLOBAL_ARGS not defined. Inclusion errors likely when running ODB targets.")
    endif()


    add_custom_target(odb_dogen_relational_json
        COMMENT "ODB json"
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMAND ${ODB_EXECUTABLE}
            --options-file ${CMAKE_CURRENT_SOURCE_DIR}/odb/common_options.odb
            --options-file ${CMAKE_CURRENT_SOURCE_DIR}/odb/tracing/json_options.odb
            --output-dir ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/odb/tracing
            ${ODB_EXECUTABLE_GLOBAL_ARGS}
            ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/types/tracing/json.hpp
        COMMAND mv ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/odb/tracing/json-odb-pgsql.cxx ${CMAKE_CURRENT_SOURCE_DIR}/odb/tracing/
        COMMAND mv ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/odb/tracing/json-odb-sqlite.cxx ${CMAKE_CURRENT_SOURCE_DIR}/odb/tracing/
        VERBATIM
    )
    add_dependencies(odb_dogen_relational odb_dogen_relational_json)

    add_custom_target(odb_dogen_relational_log
        COMMENT "ODB log"
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMAND ${ODB_EXECUTABLE}
            --options-file ${CMAKE_CURRENT_SOURCE_DIR}/odb/common_options.odb
            --options-file ${CMAKE_CURRENT_SOURCE_DIR}/odb/tracing/log_options.odb
            --output-dir ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/odb/tracing
            ${ODB_EXECUTABLE_GLOBAL_ARGS}
            ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/types/tracing/log.hpp
        COMMAND mv ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/odb/tracing/log-odb-pgsql.cxx ${CMAKE_CURRENT_SOURCE_DIR}/odb/tracing/
        COMMAND mv ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/odb/tracing/log-odb-sqlite.cxx ${CMAKE_CURRENT_SOURCE_DIR}/odb/tracing/
        VERBATIM
    )
    add_dependencies(odb_dogen_relational odb_dogen_relational_log)

    add_custom_target(odb_dogen_relational_run
        COMMENT "ODB run"
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMAND ${ODB_EXECUTABLE}
            --options-file ${CMAKE_CURRENT_SOURCE_DIR}/odb/common_options.odb
            --options-file ${CMAKE_CURRENT_SOURCE_DIR}/odb/tracing/run_options.odb
            --output-dir ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/odb/tracing
            ${ODB_EXECUTABLE_GLOBAL_ARGS}
            ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/types/tracing/run.hpp
        COMMAND mv ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/odb/tracing/run-odb-pgsql.cxx ${CMAKE_CURRENT_SOURCE_DIR}/odb/tracing/
        COMMAND mv ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/odb/tracing/run-odb-sqlite.cxx ${CMAKE_CURRENT_SOURCE_DIR}/odb/tracing/
        VERBATIM
    )
    add_dependencies(odb_dogen_relational odb_dogen_relational_run)

    add_custom_target(odb_dogen_relational_run_id
        COMMENT "ODB run_id"
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMAND ${ODB_EXECUTABLE}
            --options-file ${CMAKE_CURRENT_SOURCE_DIR}/odb/common_options.odb
            --options-file ${CMAKE_CURRENT_SOURCE_DIR}/odb/tracing/run_id_options.odb
            --output-dir ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/odb/tracing
            ${ODB_EXECUTABLE_GLOBAL_ARGS}
            ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/types/tracing/run_id.hpp
        COMMAND mv ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/odb/tracing/run_id-odb-pgsql.cxx ${CMAKE_CURRENT_SOURCE_DIR}/odb/tracing/
        COMMAND mv ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/odb/tracing/run_id-odb-sqlite.cxx ${CMAKE_CURRENT_SOURCE_DIR}/odb/tracing/
        VERBATIM
    )
    add_dependencies(odb_dogen_relational odb_dogen_relational_run_id)

    add_custom_target(odb_dogen_relational_transform
        COMMENT "ODB transform"
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMAND ${ODB_EXECUTABLE}
            --options-file ${CMAKE_CURRENT_SOURCE_DIR}/odb/common_options.odb
            --options-file ${CMAKE_CURRENT_SOURCE_DIR}/odb/tracing/transform_options.odb
            --output-dir ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/odb/tracing
            ${ODB_EXECUTABLE_GLOBAL_ARGS}
            ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/types/tracing/transform.hpp
        COMMAND mv ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/odb/tracing/transform-odb-pgsql.cxx ${CMAKE_CURRENT_SOURCE_DIR}/odb/tracing/
        COMMAND mv ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/odb/tracing/transform-odb-sqlite.cxx ${CMAKE_CURRENT_SOURCE_DIR}/odb/tracing/
        VERBATIM
    )
    add_dependencies(odb_dogen_relational odb_dogen_relational_transform)

    add_custom_target(odb_dogen_relational_transform_id
        COMMENT "ODB transform_id"
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMAND ${ODB_EXECUTABLE}
            --options-file ${CMAKE_CURRENT_SOURCE_DIR}/odb/common_options.odb
            --options-file ${CMAKE_CURRENT_SOURCE_DIR}/odb/tracing/transform_id_options.odb
            --output-dir ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/odb/tracing
            ${ODB_EXECUTABLE_GLOBAL_ARGS}
            ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/types/tracing/transform_id.hpp
        COMMAND mv ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/odb/tracing/transform_id-odb-pgsql.cxx ${CMAKE_CURRENT_SOURCE_DIR}/odb/tracing/
        COMMAND mv ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/odb/tracing/transform_id-odb-sqlite.cxx ${CMAKE_CURRENT_SOURCE_DIR}/odb/tracing/
        VERBATIM
    )
    add_dependencies(odb_dogen_relational odb_dogen_relational_transform_id)

    add_custom_target(odb_dogen_relational_transform_instance_id
        COMMENT "ODB transform_instance_id"
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMAND ${ODB_EXECUTABLE}
            --options-file ${CMAKE_CURRENT_SOURCE_DIR}/odb/common_options.odb
            --options-file ${CMAKE_CURRENT_SOURCE_DIR}/odb/tracing/transform_instance_id_options.odb
            --output-dir ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/odb/tracing
            ${ODB_EXECUTABLE_GLOBAL_ARGS}
            ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/types/tracing/transform_instance_id.hpp
        COMMAND mv ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/odb/tracing/transform_instance_id-odb-pgsql.cxx ${CMAKE_CURRENT_SOURCE_DIR}/odb/tracing/
        COMMAND mv ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/odb/tracing/transform_instance_id-odb-sqlite.cxx ${CMAKE_CURRENT_SOURCE_DIR}/odb/tracing/
        VERBATIM
    )
    add_dependencies(odb_dogen_relational odb_dogen_relational_transform_instance_id)
endif()
