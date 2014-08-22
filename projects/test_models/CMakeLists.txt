# -*- mode: cmake; tab-width: 4; indent-tabs-mode: nil -*-
#
# Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
    ${CMAKE_SOURCE_DIR}/projects/test_models/all_primitives/include
    ${CMAKE_SOURCE_DIR}/projects/test_models/classes_in_a_package/include
    ${CMAKE_SOURCE_DIR}/projects/test_models/classes_inout_package/include
    ${CMAKE_SOURCE_DIR}/projects/test_models/classes_without_package/include
    ${CMAKE_SOURCE_DIR}/projects/test_models/class_in_a_package/include
    ${CMAKE_SOURCE_DIR}/projects/test_models/class_without_attributes/include
    ${CMAKE_SOURCE_DIR}/projects/test_models/class_without_package/include
    ${CMAKE_SOURCE_DIR}/projects/test_models/stand_alone_class/include
    ${CMAKE_SOURCE_DIR}/projects/test_models/compressed/include
    ${CMAKE_SOURCE_DIR}/projects/test_models/disable_full_ctor/include
    ${CMAKE_SOURCE_DIR}/projects/test_models/disable_facet_folders/include
    ${CMAKE_SOURCE_DIR}/projects/test_models/disable_cmakelists/include
    ${CMAKE_SOURCE_DIR}/projects/test_models/enable_facet_domain/include
    ${CMAKE_SOURCE_DIR}/projects/test_models/enable_facet_hash/include
    ${CMAKE_SOURCE_DIR}/projects/test_models/enable_facet_io/include
    ${CMAKE_SOURCE_DIR}/projects/test_models/enable_facet_serialization/include
    ${CMAKE_SOURCE_DIR}/projects/test_models/two_layers_with_objects/include
    ${CMAKE_SOURCE_DIR}/projects/test_models/dmp/include
    ${CMAKE_SOURCE_DIR}/projects/test_models/split_project/dir/inc
    ${CMAKE_SOURCE_DIR}/projects/test_models/trivial_inheritance/include
    ${CMAKE_SOURCE_DIR}/projects/test_models/trivial_association/include
    ${CMAKE_SOURCE_DIR}/projects/test_models/std_model/include
    ${CMAKE_SOURCE_DIR}/projects/test_models/boost_model/include
    ${CMAKE_SOURCE_DIR}/projects/test_models/comments/include
    ${CMAKE_SOURCE_DIR}/projects/test_models/enumeration/include
    ${CMAKE_SOURCE_DIR}/projects/test_models/exception/include
    ${CMAKE_SOURCE_DIR}/projects/test_models/stereotypes/include
    ${CMAKE_SOURCE_DIR}/projects/test_models/test_model_sanitizer/include
    )

#
# feature specific projects
#
if(ODB_FOUND)
    message(STATUS "Adding ODB feature test project")
    include_directories(${CMAKE_SOURCE_DIR}/projects/test_models/database/include)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/database)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/database/spec)
endif()

if(EOS_FOUND)
    message(STATUS "Adding EOS feature test project")
    include_directories(${CMAKE_SOURCE_DIR}/projects/test_models/eos_serialization/include)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/eos_serialization)
endif()

#
# add projects
#
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/all_primitives)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/classes_in_a_package)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/classes_inout_package)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/classes_without_package)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/class_in_a_package)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/class_without_attributes)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/class_without_package)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/stand_alone_class)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/compressed)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/disable_full_ctor)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/disable_facet_folders)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/enable_facet_domain)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/enable_facet_hash)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/enable_facet_io)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/enable_facet_serialization)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/two_layers_with_objects)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dmp)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/split_project/source/split_project)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/trivial_inheritance)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/trivial_association)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/std_model)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/boost_model)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/comments)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/enumeration)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/exception)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/stereotypes)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test_model_sanitizer/spec)

# global targets
add_custom_target(rebase_test_models)
add_custom_target(diff_test_models)
add_custom_target(clean_test_models)
add_custom_target(build_test_models)

# targets for each test model
foreach(dia_model ${all_dia_test_models})
    set(model_name "")
    get_filename_component(model_name ${dia_model} NAME_WE)

    set(top_dir "${stage_test_data_dir}/${model_name}")

    set(model_folder_name "${model_name}")
    if (model_name STREQUAL "disable_model_package")
        set(model_folder_name "dmp")
    endif()

    set(actual_dir "${top_dir}/actual/${model_folder_name}")
    set(expect_dir "${top_dir}/expected/${model_folder_name}")
    set(git_dir "${CMAKE_CURRENT_SOURCE_DIR}/${model_folder_name}")

    if(EXISTS "${actual_dir}")
        add_dependencies(build_test_models ${model_name})

        set(target_name "diff_${model_name}")
        add_custom_target(${target_name}
            COMMAND diff -r -u ${expect_dir} ${actual_dir}
            WORKING_DIRECTORY ${stage_bin_dir})
        add_dependencies(diff_test_models ${target_name})

        set(target_name "rebase_${model_name}")
        add_custom_target(${target_name}
            COMMAND rm -rf ${git_dir}
            COMMAND cp -r ${actual_dir} ${git_dir}
            WORKING_DIRECTORY ${stage_bin_dir})
        add_dependencies(rebase_test_models ${target_name})

        set(target_name "clean_${model_name}")
        add_custom_target(${target_name}
            COMMAND rm -rf ${actual_dir}
            COMMAND mkdir ${actual_dir}
            WORKING_DIRECTORY ${stage_bin_dir})
        add_dependencies(clean_test_models ${target_name})
        message(STATUS "Processed model: ${model_name}")
    endif()
endforeach()

# copy all generated files into the expected directory of test data
foreach(dia_model ${all_dia_test_models})
    set(model_name "")
    get_filename_component(model_name "${dia_model}" NAME_WE)

    set(top_dir "${stage_test_data_dir}/${model_name}")
    set(actual_dir "${top_dir}/actual")
    if(NOT IS_DIRECTORY "${actual_dir}")
        file(MAKE_DIRECTORY "${actual_dir}")
    endif()

    set(expected_dir "${top_dir}/expected")
    if(IS_DIRECTORY "${expected_dir}")
        file(REMOVE_RECURSE "${expected_dir}")
    endif()

    set(model_folder_name "${model_name}")
    if (model_name STREQUAL "disable_model_package")
        set(model_folder_name "dmp")
    endif()

    set(git_dir "${CMAKE_CURRENT_SOURCE_DIR}/${model_folder_name}")
    if(IS_DIRECTORY "${git_dir}")
        file(COPY "${git_dir}" DESTINATION "${expected_dir}")
    else()
        if(NOT EXISTS "${expected_dir}")
            file(MAKE_DIRECTORY "${expected_dir}")
        endif()
    endif()

    message(STATUS "Created data set for model: ${model_name}")
endforeach()

file(GLOB_RECURSE all_hpp_files RELATIVE
    "${CMAKE_SOURCE_DIR}/"
    "${CMAKE_SOURCE_DIR}/projects/test_models/*.hpp")

set(header_validation_template "build/templates/cpp/header_validation.cpp.in")
set(header_validation_files "")

set(ignore_file false)
set(file_counter "0")

foreach(hpp_file ${all_hpp_files})
    if(NOT ODB_FOUND)
        if (hpp_file MATCHES "database")
            set(ignore_file true)
        endif()
    endif()

    if(NOT EOS_FOUND)
        if (hpp_file MATCHES "eos")
            set(ignore_file true)
        endif()
    endif()

    if(NOT ignore_file)
        set(input_filename ${CMAKE_SOURCE_DIR}/${header_validation_template})
        set(output_filename "${CMAKE_BINARY_DIR}/${hpp_file}_hv.cpp")
        set(DUMMY_FUNCTION "")
        string(REGEX REPLACE "\\." "_" DUMMY_FUNCTION "dummy_${file_counter}")

        # note: do not remove the line below, it is used by the template
        set(header_validation_target ${CMAKE_SOURCE_DIR}/${hpp_file})

        configure_file(${input_filename} ${output_filename})
        set(header_validation_files
            ${header_validation_files} ${output_filename})
    endif()
    set(ignore_file false)
    math(EXPR file_counter "${file_counter} + 1")
endforeach()

add_library(test_models_header_validation STATIC ${header_validation_files})
set_target_properties(test_models_header_validation
    PROPERTIES OUTPUT_NAME dogen_test_models_header_validation)
set_target_properties(test_models_header_validation
    PROPERTIES VERSION ${DOGEN_VERSION} SOVERSION ${DOGEN_MAJOR_VERSION})
