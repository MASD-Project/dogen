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
set(output_dir "${CMAKE_CURRENT_SOURCE_DIR}/json")
set(folder "${CMAKE_CURRENT_SOURCE_DIR}/json")
if (WITH_JSON_VALIDATION)
    set(files "")

    file(GLOB_RECURSE files RELATIVE
        "${CMAKE_CURRENT_SOURCE_DIR}/${input_dir}"
        "${CMAKE_CURRENT_SOURCE_DIR}/${input_dir}/*.json")

    set(target "input_models.json")
    add_custom_target(validate_json_${target})
    add_dependencies(validate_all_json validate_json_${target})

    add_custom_target(indent_json_${target})
    add_dependencies(indent_all_json indent_json_${target})

    foreach(file ${files})
        add_custom_target(validate_json_${target}_${file}
            COMMENT "Validating JSON for ${target}/${file}."
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMAND ${JQ_COMMAND} . ${folder}/${file} > /dev/null)
        add_dependencies(validate_json_${target}
            validate_json_${target}_${file})

        add_custom_target(indent_json_${target}_${file}
            COMMENT "Indenting JSON for ${target}/${file}."
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMAND ${JQ_COMMAND} . ${folder}/${file} > ${folder}/${file}_tmp
            COMMAND mv ${folder}/${file}_tmp ${folder}/${file})
        add_dependencies(indent_json_${target}
            indent_json_${target}_${file})

    endforeach()
endif()

#
# Tailor targets
#
file(GLOB models "dia/*.dia")

if (DOGEN_TAILOR_EXECUTABLE)
    foreach(model ${models})
        set(model_name "")
        get_filename_component(model_name ${model} NAME)

        add_custom_target(tailor_${model_name}
          COMMENT "Tailoring ${model_name}."
          WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
          COMMAND ${DOGEN_TAILOR_EXECUTABLE} --log-level=${DOGEN_LOG_LEVEL} --target ${model} --output ${output_dir}/${model_name}.json)
        add_dependencies(tailor_all tailor_${model_name})
    endforeach()
endif()

if (DOGEN_KNITTER_EXECUTABLE)
    set(ig_flg "--ignore-files-matching-regex")
    set(ignore_regexes ${ig_flg} .*/CMakeLists.txt)
    set(ignore_regexes ${ignore_regexes} ${ig_flg} .*/test/.*)
    set(ignore_regexes ${ignore_regexes} ${ig_flg} .*/tests/.*)
    set(ignore_regexes ${ignore_regexes} ${ig_flg} .*/poly-stitch.el)
    set(ignore_regexes ${ignore_regexes} ${ig_flg} .*/colour.py)


    set(other_options --log-level ${DOGEN_LOG_LEVEL})
    set(other_options ${other_options} --delete-extra-files)

    # uncomment the next line if you require compatibility support
    # set(other_options ${other_options} --compatibility-mode)

    set(projects_dir "${CMAKE_SOURCE_DIR}/projects")
    set(common_arguments --output-directory ${projects_dir}/)
    set(common_arguments ${common_arguments} ${other_options})
    set(common_arguments ${common_arguments} ${ignore_regexes})

    # uncomment to enable probing.
    # set(common_arguments ${common_arguments} "--probe-all")
    # set(common_arguments ${common_arguments} "--probe-stats-org-mode")

    # main input models
    set(models dogen.annotations)
    set(models ${models} dogen.dia)
    set(models ${models} dogen.formatting)
    set(models ${models} dogen.options)
    set(models ${models} dogen.probing)
    set(models ${models} dogen.external)
    set(models ${models} dogen.external.dia)
    set(models ${models} dogen.external.json)
    set(models ${models} dogen.quilt.cpp)
    set(models ${models} dogen.quilt.csharp)
    set(models ${models} dogen.stitch)
    set(models ${models} dogen.wale)
    set(models ${models} dogen.modeling)
    # models that are not yet ready
    # set(models ${models} pleat)
    # set(models ${models} dart)
endif()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dia)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/json)
