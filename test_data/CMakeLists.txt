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
set(cur_dir ${CMAKE_CURRENT_SOURCE_DIR})
file(GLOB sub_dir RELATIVE ${cur_dir} *)
add_custom_target(rebase_dataset)
add_custom_target(diff_dataset)

# handle the special case of empty test data set
file(MAKE_DIRECTORY ${stage_test_data_dir}/empty_tds/actual)
file(MAKE_DIRECTORY ${stage_test_data_dir}/empty_tds/expected)

foreach(dir ${sub_dir})
    if(IS_DIRECTORY ${cur_dir}/${dir})
        file(REMOVE_RECURSE ${stage_test_data_dir}/${dir}/expected)
        file(COPY ${cur_dir}/${dir} DESTINATION ${stage_dir}/test_data)
        file(MAKE_DIRECTORY ${stage_test_data_dir}/${dir}/actual)
        file(MAKE_DIRECTORY ${stage_test_data_dir}/${dir}/expected)

        set(model_name "${dir}")
        set(git_expected "${CMAKE_CURRENT_SOURCE_DIR}/${model_name}/expected")
        set(actual "${stage_test_data_dir}/${model_name}/actual")
        set(expected "${stage_test_data_dir}/${model_name}/expected")

        set(target_name "diff_${model_name}")
        add_custom_target(${target_name}
            COMMAND diff -r -u ${expected} ${actual}
            WORKING_DIRECTORY ${stage_bin_dir})
        add_dependencies(diff_dataset ${target_name})

        set(target_name "rebase_${model_name}")
        if(EXISTS "${git_expected}/")
            add_custom_target(${target_name}
                COMMAND rm -rf ${expected}/*
                COMMAND cp ${actual}/* ${expected}
                COMMAND cp ${actual}/* ${git_expected}/
                WORKING_DIRECTORY ${stage_bin_dir})
            add_dependencies(rebase_dataset ${target_name})
            message(STATUS "Processed data set: ${dir}")
        endif()
    endif()
endforeach()

if (WITH_JSON_VALIDATION)
    set(files "")

    set(folder "yarn.json/input")
    file(GLOB_RECURSE files RELATIVE
        "${CMAKE_CURRENT_SOURCE_DIR}/${folder}"
        "${CMAKE_CURRENT_SOURCE_DIR}/${folder}/*.json")

    set(target "yarn.json")
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
# sample files for installation
#
set(input_dir "${CMAKE_CURRENT_SOURCE_DIR}/yarn.dia/input")
set(output_dir "${CMAKE_CURRENT_SOURCE_DIR}/yarn.json/input")

#
# Tailor targets
#
file(GLOB samples "${input_dir}/*.dia")
install(FILES ${samples} DESTINATION share/samples/dia)

foreach(sample ${samples})
    set(model_name "")
    get_filename_component(model_name ${sample} NAME_WE)

    add_custom_target(tailor_${model_name}
        COMMENT "Tailoring ${model_name}."
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMAND ${tailor_binary} -v --target ${sample} --output ${output_dir}/${model_name}.json)

    add_dependencies(tailor_all tailor_${model_name})
endforeach()
