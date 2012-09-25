# -*- mode: cmake; tab-width: 4; indent-tabs-mode: nil -*-
#
# Copyright (C) 2011 Kitanda
#
# This file is distributed under the Kitanda Proprietary Software
# Licence. See doc/LICENCE.TXT for details.
#
set(generator_spec_files "")
file(GLOB_RECURSE generator_spec_files RELATIVE
    "${CMAKE_CURRENT_SOURCE_DIR}/"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable(generator_spec ${generator_spec_files})
set(binary_name "dogen_generator_spec")
set_target_properties(generator_spec PROPERTIES OUTPUT_NAME ${binary_name})

target_link_libraries(generator_spec
    generator
    utility
    dia
    sml
    ${LIBXML2_LIBRARIES}
    ${Boost_LIBRARIES}
    ${PQXX_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT})

set(generator_spec_cmd ${stage_bin_dir}/${binary_name} ${boost_test_parameters})

add_custom_target(run_generator_spec
    COMMAND ${generator_spec_cmd}
    WORKING_DIRECTORY ${stage_bin_dir}
    DEPENDS generator_spec)

add_boost_tests(generator ${generator_spec_files})
