# -*- mode: cmake; tab-width: 4; indent-tabs-mode: nil -*-
#
# Copyright (C) 2011 Kitanda
#
# This file is distributed under the Kitanda Proprietary Software
# Licence. See doc/LICENCE.TXT for details.
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

            set(spec_cmd ${stage_bin_dir}/dogen_${test_module}_spec)
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
    if("${hpp_file}" MATCHES "database" AND NOT WITH_DATABASE_SUPPORT)
        set(ignore_file true)
    endif()

    if(NOT ignore_file)
        set(input_filename ${CMAKE_SOURCE_DIR}/${header_validation_template})
        set(output_filename "${CMAKE_BINARY_DIR}/${hpp_file}_hv.cpp")
        set(DUMMY_FUNCTION "")
        string(REGEX REPLACE "\\." "_" DUMMY_FUNCTION "dummy_${file_counter}")
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
    PROPERTIES OUTPUT_NAME dogen_header_validation)
set_target_properties(header_validation
    PROPERTIES VERSION ${DOGEN_VERSION} SOVERSION ${DOGEN_MAJOR_VERSION})

#
# add all projects
#
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dia/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/dia/spec)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/sml/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/sml/spec)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/utility/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/utility/spec)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/generator/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/generator/spec)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/driver/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/driver/spec)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/all_primitives/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/all_primitives/spec)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/classes_in_a_package/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/classes_inside_and_outside_package/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/classes_without_package/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/class_in_a_package/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/class_in_a_package/spec)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/class_without_attributes/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/class_without_package/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/class_without_package_and_attributes/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/compressed/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/disable_complete_constructor/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/enable_facet_domain/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/enable_facet_hash/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/enable_facet_io/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/enable_facet_serialization/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/two_layers_with_objects/src)

# global targets for codegen
add_custom_target(rebase_codegen)
add_custom_target(diff_codegen)
add_custom_target(clean_codegen)

# targets for each test model
foreach(dia_model ${all_dia_test_models})
    set(model_name "")
    get_filename_component(model_name ${dia_model} NAME_WE)

    set(top_dir "${stage_test_data_dir}/${model_name}")
    set(actual_dir "${top_dir}/actual/${model_name}")
    set(expect_dir "${top_dir}/expected/${model_name}")
    set(git_dir "${CMAKE_CURRENT_SOURCE_DIR}/${model_name}")

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
    message(STATUS "Created data set for model: ${model_name}")

    set(git_dir "${CMAKE_CURRENT_SOURCE_DIR}/${model_name}")
    if(IS_DIRECTORY "${git_dir}")
        set(top_dir "${stage_test_data_dir}/${model_name}")
        set(actual_dir "${top_dir}/actual")
        if(NOT IS_DIRECTORY "${actual_dir}")
            file(MAKE_DIRECTORY "${actual_dir}")
        endif()

        set(expected_dir "${top_dir}/expected")
        if(IS_DIRECTORY "${expected_dir}")
            file(REMOVE_RECURSE "${expected_dir}")
        endif()
        file(COPY "${git_dir}" DESTINATION "${expected_dir}")
    endif()
endforeach()
