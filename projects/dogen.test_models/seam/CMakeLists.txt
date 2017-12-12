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
set(model_name "seam")
set(git_dir "${CMAKE_CURRENT_SOURCE_DIR}/src")

set(top_dir "${stage_test_data_dir}/${model_name}")
if(NOT IS_DIRECTORY "${top_dir}")
    file(MAKE_DIRECTORY "${top_dir}")
endif()

set(actual_dir "${top_dir}/actual")
if(NOT IS_DIRECTORY "${actual_dir}")
    file(MAKE_DIRECTORY "${actual_dir}")
endif()

set(expected_dir "${top_dir}/expected")
if(IS_DIRECTORY "${expected_dir}")
    file(REMOVE_RECURSE "${expected_dir}")
endif()

if(IS_DIRECTORY "${git_dir}")
    file(COPY "${git_dir}" DESTINATION "${expected_dir}")
else()
    if(NOT EXISTS "${expected_dir}")
        file(MAKE_DIRECTORY "${expected_dir}")
    endif()
endif()
message(STATUS "Created data set for model: ${model_name}")

set(target_name "diff_${model_name}")
add_custom_target(${target_name}
    COMMENT "Diffing ${model_name}"
    COMMAND diff -r -u ${expected_dir} ${actual_dir}
    WORKING_DIRECTORY ${stage_bin_dir})
add_dependencies(diff_test_models ${target_name})

set(target_name "rebase_${model_name}")
add_custom_target(${target_name}
    COMMENT "Rebasing ${model_name}"
    COMMAND rm -rf ${git_dir}
    COMMAND cp -r ${actual_dir}/src ${git_dir}
    WORKING_DIRECTORY ${stage_bin_dir})
add_dependencies(rebase_test_models ${target_name})

set(target_name "clean_${model_name}")
add_custom_target(${target_name}
    COMMENT "Cleaning ${model_name}"
    COMMAND rm -rf ${actual_dir}
    COMMAND mkdir ${actual_dir}
    WORKING_DIRECTORY ${stage_bin_dir})
add_dependencies(clean_test_models ${target_name})
message(STATUS "Processed model: ${model_name}")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)
