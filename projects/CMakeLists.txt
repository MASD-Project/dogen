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

#
# macro to create CTest tests for each boost unit tests
#
macro(add_boost_tests test_module)
    foreach(cpp_file ${ARGN})
        file(READ "${cpp_file}" contents)
        string(REGEX MATCHALL "BOOST_AUTO_TEST_CASE\\(([A-Za-z_0-9]+)\\)"
            found_tests ${contents})

        foreach(hit ${found_tests})
            string(REGEX REPLACE "BOOST_AUTO_TEST_CASE(\\([A-Za-z_0-9]+\\))"
                "\\1" test_name ${hit})
            string(REPLACE "(" "" test_name ${test_name})
            string(REPLACE ")" "" test_name ${test_name})

            string(REPLACE "_spec.cpp" "" test_suite ${cpp_file})
            string(REPLACE "spec/" "" test_suite ${test_suite})

            set(spec_cmd
                ${stage_bin_dir}/dogen_${test_module}_spec-${DOGEN_VERSION})
            add_test(${test_module}/${test_suite}/${test_name}
                ${CMAKE_COMMAND} -E chdir ${stage_bin_dir}
                ${spec_cmd} --run_test=${test_suite}/${test_name})
        endforeach()
    endforeach()
endmacro()

#
# compiler and linker flags
#

# enable as many warnings as possible
set(warning_flags "-Wall -Wextra")

# issue all the warnings demanded by strict iso c and iso c++
set(warning_flags "${warning_flags} -pedantic")

# treat warnings as errors
set(warning_flags "${warning_flags} -Werror")

# definition shadows another
# FIXME: causes too many problems.
# set(warning_flags "${warning_flags} -Wshadow")

# do not issue warnings for system headers
set(warning_flags "${warning_flags} -Wno-system-headers")

# overloaded virtual function has a different signature
set(warning_flags "${warning_flags} -Woverloaded-virtual")

# make string constants const char*
set(warning_flags "${warning_flags} -Wwrite-strings")

# debug flags
if(WITH_DEBUG)
    set(optimisation_flags "-g -O0")
else()
    set(optimisation_flags "-O3")
endif()

if(WITH_PROFILING)
    # enable code profiling options
    set(profiling_flags "-fprofile-arcs -ftest-coverage")
endif()

# enable RTTI
# -fvisibility=hidden
set(other_flags "-frtti -fvisibility-inlines-hidden -fvisibility=default")

# set the flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${optimisation_flags}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${warning_flags}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${profiling_flags}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${other_flags}")

# ignore fuzzy link errors
if (WIN32)
    set(CMAKE_EXE_LINKER_FLAGS
        "${CMAKE_EXE_LINKER_FLAGS} -Wl,-enable-stdcall-fixup")
    set(CMAKE_SHARED_LINKER_FLAGS
        "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-enable-stdcall-fixup")
endif()

# parameters for boost tests
set(boost_test_parameters "")

file(GLOB_RECURSE all_hpp_files RELATIVE
    "${CMAKE_SOURCE_DIR}/"
    "${CMAKE_SOURCE_DIR}/projects/*.hpp")

set(header_validation_template "build/templates/cpp/header_validation.cpp.in")
set(header_validation_files "")

set(ignore_file false)
set(file_counter "0")
foreach(hpp_file ${all_hpp_files})
    # if (hpp_file MATCHES "REGEX_TO_IGNORE")
    #     set(ignore_file true)
    # endif()

    if(NOT ignore_file)
        set(input_filename ${CMAKE_SOURCE_DIR}/${header_validation_template})
        set(output_filename "${CMAKE_BINARY_DIR}/${hpp_file}_hv.cpp")
        set(header_validation_target ${CMAKE_SOURCE_DIR}/${hpp_file})
        configure_file(${input_filename} ${output_filename})
        set(header_validation_files
            ${header_validation_files} ${output_filename})
    endif()
    set(ignore_file false)
    math(EXPR file_counter "${file_counter} + 1")
endforeach()

add_library(header_validation STATIC ${header_validation_files})
set_target_properties(header_validation
    PROPERTIES OUTPUT_NAME dogen_header_validation-${DOGEN_VERSION})
set_target_properties(header_validation
    PROPERTIES VERSION ${DOGEN_VERSION} SOVERSION ${DOGEN_MAJOR_VERSION})

# user includes
include_directories(
    # generated header files
    ${stage_inc_dir}/

    # real code
    ${CMAKE_SOURCE_DIR}/projects/dia/include
    ${CMAKE_SOURCE_DIR}/projects/sml/include
    ${CMAKE_SOURCE_DIR}/projects/utility/include
    ${CMAKE_SOURCE_DIR}/projects/generator/include
    ${CMAKE_SOURCE_DIR}/projects/driver/include
    ${CMAKE_SOURCE_DIR}/projects/test_model_sanitizer/include

    # test models
    ${CMAKE_SOURCE_DIR}/projects/all_primitives/include
    ${CMAKE_SOURCE_DIR}/projects/classes_in_a_package/include
    ${CMAKE_SOURCE_DIR}/projects/classes_inout_package/include
    ${CMAKE_SOURCE_DIR}/projects/classes_without_package/include
    ${CMAKE_SOURCE_DIR}/projects/class_in_a_package/include
    ${CMAKE_SOURCE_DIR}/projects/class_without_attributes/include
    ${CMAKE_SOURCE_DIR}/projects/class_without_package/include
    ${CMAKE_SOURCE_DIR}/projects/stand_alone_class/include
    ${CMAKE_SOURCE_DIR}/projects/compressed/include
    ${CMAKE_SOURCE_DIR}/projects/disable_full_ctor/include
    ${CMAKE_SOURCE_DIR}/projects/disable_facet_folders/include
    ${CMAKE_SOURCE_DIR}/projects/disable_cmakelists/include
    ${CMAKE_SOURCE_DIR}/projects/enable_facet_domain/include
    ${CMAKE_SOURCE_DIR}/projects/enable_facet_hash/include
    ${CMAKE_SOURCE_DIR}/projects/enable_facet_io/include
    ${CMAKE_SOURCE_DIR}/projects/enable_facet_serialization/include
    ${CMAKE_SOURCE_DIR}/projects/two_layers_with_objects/include
    ${CMAKE_SOURCE_DIR}/projects/dmp/include
    ${CMAKE_SOURCE_DIR}/projects/split_project/dir/inc
    ${CMAKE_SOURCE_DIR}/projects/prototype/include
    ${CMAKE_SOURCE_DIR}/projects/trivial_inheritance/include
    ${CMAKE_SOURCE_DIR}/projects/trivial_association/include
    ${CMAKE_SOURCE_DIR}/projects/std_model/include
    ${CMAKE_SOURCE_DIR}/projects/boost_model/include
    ${CMAKE_SOURCE_DIR}/projects/comments/include
    ${CMAKE_SOURCE_DIR}/projects/enumeration/include
    ${CMAKE_SOURCE_DIR}/projects/exception/include
    ${CMAKE_SOURCE_DIR}/projects/entity_service_value/include
    )

#
# add all projects
#
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dia)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/sml)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/sml/spec)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/utility)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/generator)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/driver)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test_model_sanitizer/spec)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/prototype/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/prototype/spec)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/prototype/sql)

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
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/entity_service_value)

# global targets for codegen
add_custom_target(rebase_codegen)
add_custom_target(diff_codegen)
add_custom_target(clean_codegen)

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
        set(target_name "diff_${model_name}")
        add_custom_target(${target_name}
            COMMAND diff -r -u ${expect_dir} ${actual_dir}
            WORKING_DIRECTORY ${stage_bin_dir})
        add_dependencies(diff_codegen ${target_name})

        set(target_name "rebase_${model_name}")
        add_custom_target(${target_name}
            COMMAND rm -rf ${git_dir}
            COMMAND cp -r ${actual_dir} ${git_dir}
            WORKING_DIRECTORY ${stage_bin_dir})
        add_dependencies(rebase_codegen ${target_name})

        set(target_name "clean_${model_name}")
        add_custom_target(${target_name}
            COMMAND rm -rf ${actual_dir}
            COMMAND mkdir ${actual_dir}
            WORKING_DIRECTORY ${stage_bin_dir})
        add_dependencies(clean_codegen ${target_name})
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
