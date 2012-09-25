# -*- mode: cmake; tab-width: 4; indent-tabs-mode: nil -*-
#
# Copyright (C) 2012 Kitanda
#
# This file is distributed under the Kitanda Proprietary Software
# Licence. See doc/LICENCE.TXT for details.

set(curdir ${CMAKE_CURRENT_SOURCE_DIR})
file(GLOB sub-dir RELATIVE ${curdir} *)
set(list_of_dirs "")
add_custom_target(rebase_dataset)
add_custom_target(diff_dataset)

# handle the special case of empty TDS
file(MAKE_DIRECTORY ${stage_test_data_dir}/empty_tds/actual)
file(MAKE_DIRECTORY ${stage_test_data_dir}/empty_tds/expected)

foreach(dir ${sub-dir})
    if(IS_DIRECTORY ${curdir}/${dir})
        file(REMOVE_RECURSE ${stage_test_data_dir}/${dir}/expected)
        file(COPY ${curdir}/${dir} DESTINATION ${stage_dir}/test_data)
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
