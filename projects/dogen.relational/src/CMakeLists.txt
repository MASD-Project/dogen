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
set(files "")
file(GLOB_RECURSE files RELATIVE
    "${CMAKE_CURRENT_SOURCE_DIR}/"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

if(NOT ODB_LIBODB_FOUND)
    message(FATAL_ERROR "ODB include directories not defined.")
endif()

set(odb_files "")
file(GLOB_RECURSE odb_files RELATIVE
   "${CMAKE_CURRENT_SOURCE_DIR}/"
   "${CMAKE_CURRENT_SOURCE_DIR}/*.cxx")
set(files ${files} ${odb_files})

add_library(dogen_relational ${files})
set_target_properties(dogen_relational PROPERTIES
    OUTPUT_NAME dogen_relational)

install(TARGETS dogen_relational
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


    add_custom_target(odb_dogen_relational_attribute
        COMMENT "ODB attribute"
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMAND ${ODB_EXECUTABLE}
            --options-file ${CMAKE_CURRENT_SOURCE_DIR}/odb/common_options.odb
            --options-file ${CMAKE_CURRENT_SOURCE_DIR}/odb/tracing/attribute_options.odb
            --output-dir ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/odb/tracing
            ${ODB_EXECUTABLE_GLOBAL_ARGS}
            ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/types/tracing/attribute.hpp
        COMMAND mv ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/odb/tracing/attribute-odb.cxx ${CMAKE_CURRENT_SOURCE_DIR}/odb/tracing/
        VERBATIM
    )
    add_dependencies(odb_dogen_relational odb_dogen_relational_attribute)

    add_custom_target(odb_dogen_relational_attribute_id
        COMMENT "ODB attribute_id"
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMAND ${ODB_EXECUTABLE}
            --options-file ${CMAKE_CURRENT_SOURCE_DIR}/odb/common_options.odb
            --options-file ${CMAKE_CURRENT_SOURCE_DIR}/odb/tracing/attribute_id_options.odb
            --output-dir ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/odb/tracing
            ${ODB_EXECUTABLE_GLOBAL_ARGS}
            ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/types/tracing/attribute_id.hpp
        COMMAND mv ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/odb/tracing/attribute_id-odb.cxx ${CMAKE_CURRENT_SOURCE_DIR}/odb/tracing/
        VERBATIM
    )
    add_dependencies(odb_dogen_relational odb_dogen_relational_attribute_id)

    add_custom_target(odb_dogen_relational_element
        COMMENT "ODB element"
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMAND ${ODB_EXECUTABLE}
            --options-file ${CMAKE_CURRENT_SOURCE_DIR}/odb/common_options.odb
            --options-file ${CMAKE_CURRENT_SOURCE_DIR}/odb/tracing/element_options.odb
            --output-dir ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/odb/tracing
            ${ODB_EXECUTABLE_GLOBAL_ARGS}
            ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/types/tracing/element.hpp
        COMMAND mv ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/odb/tracing/element-odb.cxx ${CMAKE_CURRENT_SOURCE_DIR}/odb/tracing/
        VERBATIM
    )
    add_dependencies(odb_dogen_relational odb_dogen_relational_element)

    add_custom_target(odb_dogen_relational_element_id
        COMMENT "ODB element_id"
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMAND ${ODB_EXECUTABLE}
            --options-file ${CMAKE_CURRENT_SOURCE_DIR}/odb/common_options.odb
            --options-file ${CMAKE_CURRENT_SOURCE_DIR}/odb/tracing/element_id_options.odb
            --output-dir ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/odb/tracing
            ${ODB_EXECUTABLE_GLOBAL_ARGS}
            ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/types/tracing/element_id.hpp
        COMMAND mv ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/odb/tracing/element_id-odb.cxx ${CMAKE_CURRENT_SOURCE_DIR}/odb/tracing/
        VERBATIM
    )
    add_dependencies(odb_dogen_relational odb_dogen_relational_element_id)

    add_custom_target(odb_dogen_relational_json
        COMMENT "ODB json"
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMAND ${ODB_EXECUTABLE}
            --options-file ${CMAKE_CURRENT_SOURCE_DIR}/odb/common_options.odb
            --options-file ${CMAKE_CURRENT_SOURCE_DIR}/odb/tracing/json_options.odb
            --output-dir ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/odb/tracing
            ${ODB_EXECUTABLE_GLOBAL_ARGS}
            ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/types/tracing/json.hpp
        COMMAND mv ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/odb/tracing/json-odb.cxx ${CMAKE_CURRENT_SOURCE_DIR}/odb/tracing/
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
        COMMAND mv ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/odb/tracing/log-odb.cxx ${CMAKE_CURRENT_SOURCE_DIR}/odb/tracing/
        VERBATIM
    )
    add_dependencies(odb_dogen_relational odb_dogen_relational_log)

    add_custom_target(odb_dogen_relational_model
        COMMENT "ODB model"
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMAND ${ODB_EXECUTABLE}
            --options-file ${CMAKE_CURRENT_SOURCE_DIR}/odb/common_options.odb
            --options-file ${CMAKE_CURRENT_SOURCE_DIR}/odb/tracing/model_options.odb
            --output-dir ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/odb/tracing
            ${ODB_EXECUTABLE_GLOBAL_ARGS}
            ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/types/tracing/model.hpp
        COMMAND mv ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/odb/tracing/model-odb.cxx ${CMAKE_CURRENT_SOURCE_DIR}/odb/tracing/
        VERBATIM
    )
    add_dependencies(odb_dogen_relational odb_dogen_relational_model)

    add_custom_target(odb_dogen_relational_model_id
        COMMENT "ODB model_id"
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMAND ${ODB_EXECUTABLE}
            --options-file ${CMAKE_CURRENT_SOURCE_DIR}/odb/common_options.odb
            --options-file ${CMAKE_CURRENT_SOURCE_DIR}/odb/tracing/model_id_options.odb
            --output-dir ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/odb/tracing
            ${ODB_EXECUTABLE_GLOBAL_ARGS}
            ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/types/tracing/model_id.hpp
        COMMAND mv ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/odb/tracing/model_id-odb.cxx ${CMAKE_CURRENT_SOURCE_DIR}/odb/tracing/
        VERBATIM
    )
    add_dependencies(odb_dogen_relational odb_dogen_relational_model_id)

    add_custom_target(odb_dogen_relational_model_set
        COMMENT "ODB model_set"
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMAND ${ODB_EXECUTABLE}
            --options-file ${CMAKE_CURRENT_SOURCE_DIR}/odb/common_options.odb
            --options-file ${CMAKE_CURRENT_SOURCE_DIR}/odb/tracing/model_set_options.odb
            --output-dir ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/odb/tracing
            ${ODB_EXECUTABLE_GLOBAL_ARGS}
            ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/types/tracing/model_set.hpp
        COMMAND mv ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/odb/tracing/model_set-odb.cxx ${CMAKE_CURRENT_SOURCE_DIR}/odb/tracing/
        VERBATIM
    )
    add_dependencies(odb_dogen_relational odb_dogen_relational_model_set)

    add_custom_target(odb_dogen_relational_model_set_id
        COMMENT "ODB model_set_id"
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMAND ${ODB_EXECUTABLE}
            --options-file ${CMAKE_CURRENT_SOURCE_DIR}/odb/common_options.odb
            --options-file ${CMAKE_CURRENT_SOURCE_DIR}/odb/tracing/model_set_id_options.odb
            --output-dir ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/odb/tracing
            ${ODB_EXECUTABLE_GLOBAL_ARGS}
            ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/types/tracing/model_set_id.hpp
        COMMAND mv ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/odb/tracing/model_set_id-odb.cxx ${CMAKE_CURRENT_SOURCE_DIR}/odb/tracing/
        VERBATIM
    )
    add_dependencies(odb_dogen_relational odb_dogen_relational_model_set_id)

    add_custom_target(odb_dogen_relational_run
        COMMENT "ODB run"
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMAND ${ODB_EXECUTABLE}
            --options-file ${CMAKE_CURRENT_SOURCE_DIR}/odb/common_options.odb
            --options-file ${CMAKE_CURRENT_SOURCE_DIR}/odb/tracing/run_options.odb
            --output-dir ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/odb/tracing
            ${ODB_EXECUTABLE_GLOBAL_ARGS}
            ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/types/tracing/run.hpp
        COMMAND mv ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/odb/tracing/run-odb.cxx ${CMAKE_CURRENT_SOURCE_DIR}/odb/tracing/
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
        COMMAND mv ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/odb/tracing/run_id-odb.cxx ${CMAKE_CURRENT_SOURCE_DIR}/odb/tracing/
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
        COMMAND mv ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/odb/tracing/transform-odb.cxx ${CMAKE_CURRENT_SOURCE_DIR}/odb/tracing/
        VERBATIM
    )
    add_dependencies(odb_dogen_relational odb_dogen_relational_transform)

    add_custom_target(odb_dogen_relational_transform_components
        COMMENT "ODB transform_components"
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMAND ${ODB_EXECUTABLE}
            --options-file ${CMAKE_CURRENT_SOURCE_DIR}/odb/common_options.odb
            --options-file ${CMAKE_CURRENT_SOURCE_DIR}/odb/tracing/transform_components_options.odb
            --output-dir ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/odb/tracing
            ${ODB_EXECUTABLE_GLOBAL_ARGS}
            ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/types/tracing/transform_components.hpp
        COMMAND mv ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/odb/tracing/transform_components-odb.cxx ${CMAKE_CURRENT_SOURCE_DIR}/odb/tracing/
        VERBATIM
    )
    add_dependencies(odb_dogen_relational odb_dogen_relational_transform_components)

    add_custom_target(odb_dogen_relational_transform_components_key
        COMMENT "ODB transform_components_key"
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMAND ${ODB_EXECUTABLE}
            --options-file ${CMAKE_CURRENT_SOURCE_DIR}/odb/common_options.odb
            --options-file ${CMAKE_CURRENT_SOURCE_DIR}/odb/tracing/transform_components_key_options.odb
            --output-dir ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/odb/tracing
            ${ODB_EXECUTABLE_GLOBAL_ARGS}
            ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/types/tracing/transform_components_key.hpp
        COMMAND mv ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/odb/tracing/transform_components_key-odb.cxx ${CMAKE_CURRENT_SOURCE_DIR}/odb/tracing/
        VERBATIM
    )
    add_dependencies(odb_dogen_relational odb_dogen_relational_transform_components_key)

    add_custom_target(odb_dogen_relational_transform_id
        COMMENT "ODB transform_id"
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMAND ${ODB_EXECUTABLE}
            --options-file ${CMAKE_CURRENT_SOURCE_DIR}/odb/common_options.odb
            --options-file ${CMAKE_CURRENT_SOURCE_DIR}/odb/tracing/transform_id_options.odb
            --output-dir ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/odb/tracing
            ${ODB_EXECUTABLE_GLOBAL_ARGS}
            ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/types/tracing/transform_id.hpp
        COMMAND mv ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/odb/tracing/transform_id-odb.cxx ${CMAKE_CURRENT_SOURCE_DIR}/odb/tracing/
        VERBATIM
    )
    add_dependencies(odb_dogen_relational odb_dogen_relational_transform_id)

    add_custom_target(odb_dogen_relational_transform_model
        COMMENT "ODB transform_model"
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMAND ${ODB_EXECUTABLE}
            --options-file ${CMAKE_CURRENT_SOURCE_DIR}/odb/common_options.odb
            --options-file ${CMAKE_CURRENT_SOURCE_DIR}/odb/tracing/transform_model_options.odb
            --output-dir ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/odb/tracing
            ${ODB_EXECUTABLE_GLOBAL_ARGS}
            ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/types/tracing/transform_model.hpp
        COMMAND mv ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/odb/tracing/transform_model-odb.cxx ${CMAKE_CURRENT_SOURCE_DIR}/odb/tracing/
        VERBATIM
    )
    add_dependencies(odb_dogen_relational odb_dogen_relational_transform_model)

    add_custom_target(odb_dogen_relational_transform_model_set
        COMMENT "ODB transform_model_set"
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMAND ${ODB_EXECUTABLE}
            --options-file ${CMAKE_CURRENT_SOURCE_DIR}/odb/common_options.odb
            --options-file ${CMAKE_CURRENT_SOURCE_DIR}/odb/tracing/transform_model_set_options.odb
            --output-dir ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/odb/tracing
            ${ODB_EXECUTABLE_GLOBAL_ARGS}
            ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/types/tracing/transform_model_set.hpp
        COMMAND mv ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/odb/tracing/transform_model_set-odb.cxx ${CMAKE_CURRENT_SOURCE_DIR}/odb/tracing/
        VERBATIM
    )
    add_dependencies(odb_dogen_relational odb_dogen_relational_transform_model_set)

    add_custom_target(odb_dogen_relational_xml
        COMMENT "ODB xml"
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMAND ${ODB_EXECUTABLE}
            --options-file ${CMAKE_CURRENT_SOURCE_DIR}/odb/common_options.odb
            --options-file ${CMAKE_CURRENT_SOURCE_DIR}/odb/tracing/xml_options.odb
            --output-dir ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/odb/tracing
            ${ODB_EXECUTABLE_GLOBAL_ARGS}
            ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/types/tracing/xml.hpp
        COMMAND mv ${CMAKE_CURRENT_SOURCE_DIR}/../include/dogen.relational/odb/tracing/xml-odb.cxx ${CMAKE_CURRENT_SOURCE_DIR}/odb/tracing/
        VERBATIM
    )
    add_dependencies(odb_dogen_relational odb_dogen_relational_xml)
endif()
