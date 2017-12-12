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

# user includes
include_directories(
    ${CMAKE_SOURCE_DIR}/projects/dogen.test_models/all_path_and_directory_settings/cpp_backend/some_include_dir
    ${CMAKE_SOURCE_DIR}/projects/dogen.test_models/cpp_model/include
    ${CMAKE_SOURCE_DIR}/projects/dogen.test_models/compressed/include
    ${CMAKE_SOURCE_DIR}/projects/dogen.test_models/disable_facet_folders/include
    ${CMAKE_SOURCE_DIR}/projects/dogen.test_models/disable_cmakelists/include
    ${CMAKE_SOURCE_DIR}/projects/dogen.test_models/enable_facet_types/include
    ${CMAKE_SOURCE_DIR}/projects/dogen.test_models/enable_facet_hash/include
    ${CMAKE_SOURCE_DIR}/projects/dogen.test_models/enable_facet_io/include
    ${CMAKE_SOURCE_DIR}/projects/dogen.test_models/enable_facet_serialization/include
    ${CMAKE_SOURCE_DIR}/projects/dogen.test_models/two_layers_with_objects/include
    ${CMAKE_SOURCE_DIR}/projects/dogen.test_models/std_model/include
    ${CMAKE_SOURCE_DIR}/projects/dogen.test_models/boost_model/include
    ${CMAKE_SOURCE_DIR}/projects/dogen.test_models/test_model_sanitizer/include
    ${CMAKE_SOURCE_DIR}/projects/dogen.test_models/seam/include
    ${CMAKE_SOURCE_DIR}/projects/dogen.test_models/split_project/dir/inc/another
    ${CMAKE_SOURCE_DIR}/projects/dogen.test_models/cpp_98/include
    ${CMAKE_SOURCE_DIR}/projects/dogen.test_models/lam_model/cpp/include
    )

#
# feature specific projects
#
if(ODB_FOUND)
    message(STATUS "Adding ODB feature test project")
    include_directories(${CMAKE_SOURCE_DIR}/projects/dogen.test_models/northwind/include)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/northwind)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/northwind/tests)
endif()

# global targets
add_custom_target(rebase_test_models)
add_custom_target(diff_test_models)
add_custom_target(clean_test_models)

# Note: no "build_" prefix to make it similar to all other build
# targets.
add_custom_target(test_models)

#
# add projects
#
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/all_path_and_directory_settings/cpp_backend)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/cpp_model)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/compressed)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/disable_facet_folders)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/enable_facet_types)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/enable_facet_hash)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/enable_facet_io)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/enable_facet_serialization)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/two_layers_with_objects)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/std_model)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/boost_model)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test_model_sanitizer/tests)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/seam)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/split_project/some_dir/split_project)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/cpp_98)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lam_model/cpp)

# copy all generated files into the expected directory of test data
foreach(dia_model ${all_dia_test_models})
    set(model_name "")
    get_filename_component(model_name "${dia_model}" NAME_WE)

    set(top_dir "${stage_test_data_dir}/${model_name}")
    set(actual_dir "${top_dir}/actual.dia")
    if(NOT IS_DIRECTORY "${actual_dir}")
        file(MAKE_DIRECTORY "${actual_dir}")
    endif()

    set(actual_dir "${top_dir}/actual.json")
    if(NOT IS_DIRECTORY "${actual_dir}")
        file(MAKE_DIRECTORY "${actual_dir}")
    endif()

    # Note: it would make more sense to always remove actual directory
    # before every run. However the downside of that approach is that
    # we can no longer diff results after a run, or else we will
    # delete the results before diffing. Thus we decided to not delete
    # actual directory.
    #
    # if(IS_DIRECTORY "${actual_dir}")
    #     file(REMOVE_RECURSE "${actual_dir}")
    # endif()
    # file(MAKE_DIRECTORY "${actual_dir}")

    set(expected_dir "${top_dir}/expected")
    if(IS_DIRECTORY "${expected_dir}")
        file(REMOVE_RECURSE "${expected_dir}")
    endif()

    set(model_folder_name "${model_name}")
    set(git_dir "${CMAKE_CURRENT_SOURCE_DIR}/${model_folder_name}")
    if(IS_DIRECTORY "${git_dir}")
        file(COPY "${git_dir}" DESTINATION "${expected_dir}")

        # ensure we remove the IDE directories before copying for the C#
        # projects, or else we will have spurious diffs.
        if ("${model_name}" STREQUAL "CSharpModel")
            file(REMOVE_RECURSE "${expected_dir}/CSharpModel/bin")
            file(REMOVE_RECURSE "${expected_dir}/CSharpModel/obj")
        elseif("${model_name}" STREQUAL "all_path_and_directory_settings")
            file(REMOVE_RECURSE "${expected_dir}/all_path_and_directory_settings/csharp_backend/bin")
            file(REMOVE_RECURSE "${expected_dir}/all_path_and_directory_settings/csharp_backend/obj")
        elseif("${model_name}" STREQUAL "lam_model")
            file(REMOVE_RECURSE "${expected_dir}/lam_model/cs/bin")
            file(REMOVE_RECURSE "${expected_dir}/lam_model/cs/obj")
        endif()
    else()
        if(NOT EXISTS "${expected_dir}")
            file(MAKE_DIRECTORY "${expected_dir}")
        endif()
    endif()

    message(STATUS "Created data set for model: ${model_name}")
endforeach()

# targets for each test model. First the manual ones.
add_dependencies(test_models all_path_and_directory_settings)
add_dependencies(test_models split_project)
foreach(dia_model ${all_dia_test_models})
    set(ignore_dependencies false)
    if (dia_model MATCHES "disable_cmakelists")
        set(ignore_dependencies true)
    endif()

    set(model_name "")
    get_filename_component(model_name ${dia_model} NAME_WE)

    set(top_dir "${stage_test_data_dir}/${model_name}")

    set(model_folder_name "${model_name}")
    set(actual_dir "${top_dir}/actual.dia/")
    set(expected_dir "${top_dir}/expected/")
    set(git_dir "${CMAKE_CURRENT_SOURCE_DIR}/${model_folder_name}")

    if (EXISTS "${actual_dir}")
        set(main_target_name "${model_name}")
        if (NOT ignore_dependencies)
            # Checking the presence of the cmake file to ensure this
            # is a valid project to build - e.g. ignore C#.
            if (EXISTS "${expected_dir}/${model_folder_name}/CMakeLists.txt")
                add_dependencies(test_models ${main_target_name})
            endif()
        endif()

        file(GLOB result ${actual_dir}/*)
        list(LENGTH result result_length)
        if(NOT result_length EQUAL 0)
            set(target_name "diff_${model_name}_dia")
            add_custom_target(${target_name}
                COMMENT "Diffing ${model_name}"
                COMMAND diff -r -u ${expected_dir} ${actual_dir}
                WORKING_DIRECTORY ${stage_bin_dir})
            add_dependencies(diff_test_models ${target_name})

            set(target_name "rebase_${model_name}_dia")
            add_custom_target(${target_name}
                COMMENT "Rebasing ${model_name}"
                COMMAND rm -rf ${git_dir}
                COMMAND cp -r ${actual_dir}/${model_name} ${git_dir}
                WORKING_DIRECTORY ${stage_bin_dir})
            add_dependencies(rebase_test_models ${target_name})

            set(target_name "clean_${model_name}_dia")
            add_custom_target(${target_name}
                COMMENT "Cleaning ${model_name}"
                COMMAND rm -rf ${actual_dir}
                COMMAND mkdir ${actual_dir}
                WORKING_DIRECTORY ${stage_bin_dir})
            add_dependencies(clean_test_models ${target_name})
            message(STATUS "Processed model: ${model_name} (dia)")
        endif()
    endif()

    set(actual_dir "${top_dir}/actual.json/")
    if (EXISTS "${actual_dir}")
        set(main_target_name "${model_name}")

        file(GLOB result ${actual_dir}/*)
        list(LENGTH result result_length)
        if(NOT result_length EQUAL 0)
            set(target_name "diff_${model_name}_json")
            add_custom_target(${target_name}
                COMMENT "Diffing ${model_name}"
                COMMAND diff -r -u ${expected_dir} ${actual_dir}
                WORKING_DIRECTORY ${stage_bin_dir})
            add_dependencies(diff_test_models ${target_name})

            set(target_name "clean_${model_name}_json")
            add_custom_target(${target_name}
                COMMENT "Cleaning ${model_name}"
                COMMAND rm -rf ${actual_dir}
                COMMAND mkdir ${actual_dir}
                WORKING_DIRECTORY ${stage_bin_dir})
            add_dependencies(clean_test_models ${target_name})
            message(STATUS "Processed model: ${model_name} (json)")
        endif()
    endif()
endforeach()
