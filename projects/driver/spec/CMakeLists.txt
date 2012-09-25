# -*- mode: cmake; tab-width: 4; indent-tabs-mode: nil -*-
#
# Copyright (C) 2011 Kitanda
#
# This file is distributed under the Kitanda Proprietary Software
# Licence. See doc/LICENCE.TXT for details.
#
set(driver_spec_files "")
file(GLOB_RECURSE driver_spec_files RELATIVE
    "${CMAKE_CURRENT_SOURCE_DIR}/"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

set(all_files "")
file(GLOB_RECURSE all_files RELATIVE
    "${CMAKE_CURRENT_SOURCE_DIR}/../src"
    "${CMAKE_CURRENT_SOURCE_DIR}/../src/*.cpp")

set(driver_files "")
set(ignore_file false)
foreach(cpp_file ${all_files})
    if("${cpp_file}" MATCHES "driver.cpp")
        set(ignore_file true)
    endif()

    if(NOT ignore_file)
        set(driver_files ${driver_files}
            "${CMAKE_CURRENT_SOURCE_DIR}/../src/${cpp_file}")
    endif()
    set(ignore_file false)
endforeach()

add_executable(driver_spec ${driver_spec_files} ${driver_files})
set(binary_name "dogen_driver_spec")
set_target_properties(driver_spec PROPERTIES OUTPUT_NAME ${binary_name})

target_link_libraries(driver_spec
    generator
    utility
    dia
    sml
    ${LIBXML2_LIBRARIES}
    ${Boost_LIBRARIES}
    ${PQXX_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT})

set(driver_spec_cmd ${stage_bin_dir}/${binary_name} ${boost_test_parameters})

add_custom_target(run_driver_spec
    COMMAND ${driver_spec_cmd}
    WORKING_DIRECTORY ${stage_bin_dir}
    DEPENDS driver_spec)

add_boost_tests(driver ${driver_spec_files})
