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
set(input_dir "json")
set(folder "${CMAKE_CURRENT_SOURCE_DIR}/json")
if (WITH_JSON_VALIDATION)
    set(files "")

    file(GLOB_RECURSE files RELATIVE
        "${CMAKE_CURRENT_SOURCE_DIR}/${input_dir}"
        "${CMAKE_CURRENT_SOURCE_DIR}/${input_dir}/*.json")

    set(target "models.json")
    add_custom_target(validate_${target})
    add_dependencies(validate_all_json validate_${target})

    add_custom_target(indent_${target})
    add_dependencies(indent_all_json indent_${target})

    foreach(file ${files})
        add_custom_target(validate_${file}
            COMMENT "Validating JSON for ${target}/${file}."
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMAND ${JQ_COMMAND} . ${folder}/${file} > /dev/null)
        add_dependencies(validate_${target} validate_${file})

        add_custom_target(indent_${file}
            COMMENT "Indenting JSON for ${target}/${file}."
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMAND ${JQ_COMMAND} . ${folder}/${file} > ${folder}/${file}_tmp
            COMMAND mv ${folder}/${file}_tmp ${folder}/${file})
        add_dependencies(indent_${target} indent_${file})

    endforeach()
endif()

if (DOGEN_CLI_EXECUTABLE)
    #
    # Model conversion
    #
    file(GLOB models "dia/*.dia")
    foreach(model ${models})
        set(model_name "")
        get_filename_component(model_name ${model} NAME)

        set(output_dir "${CMAKE_CURRENT_SOURCE_DIR}/json")
        set(destination_name ${output_dir}/${model_name})
        string(REGEX REPLACE ".dia$" ".json" destination_name
            ${destination_name})

        add_custom_target(convert_${model_name}_json
            COMMENT "Converting ${model_name} to JSON."
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMAND ${DOGEN_CLI_EXECUTABLE} convert
            --source ${model} --destination ${destination_name}
            ${DOGEN_COMMON_OPTIONS})
        add_dependencies(convert_all_json convert_${model_name}_json)

        set(output_dir "${CMAKE_CURRENT_SOURCE_DIR}/org")
        set(destination_name ${output_dir}/${model_name})
        string(REGEX REPLACE ".dia$" ".org" destination_name
            ${destination_name})

        add_custom_target(convert_${model_name}_org
            COMMENT "Converting ${model_name} to org-mode."
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMAND ${DOGEN_CLI_EXECUTABLE} convert
            --source ${model} --destination ${destination_name}
            ${DOGEN_COMMON_OPTIONS})
        add_dependencies(convert_all_org convert_${model_name}_org)
    endforeach()

    #
    # Input models for generation
    #
    set(prefix "dogen")
    set(models ${prefix})
    set(models ${models} ${prefix}.physical)
    set(models ${models} ${prefix}.cli)
    set(models ${models} ${prefix}.dia)
    set(models ${models} ${prefix}.org)
    set(models ${models} ${prefix}.tracing)
    set(models ${models} ${prefix}.codec)
    set(models ${models} ${prefix}.codec.dia)
    set(models ${models} ${prefix}.text)
    set(models ${models} ${prefix}.logical)
    set(models ${models} ${prefix}.templating)
    set(models ${models} ${prefix}.orchestration)
    set(models ${models} ${prefix}.utility)
    set(models ${models} ${prefix}.variability)
    set(models ${models} ${prefix}.relational)
    set(models ${models} ${prefix}.identification)
endif()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dia)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/json)
