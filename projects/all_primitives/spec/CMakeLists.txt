# -*- mode: cmake; tab-width: 4; indent-tabs-mode: nil -*-
#
# Copyright (C) 2011 Kitanda
#
# This file is distributed under the Kitanda Proprietary Software
# Licence. See doc/LICENCE.TXT for details.
#
set(all_primitives_spec_files "")
file(GLOB_RECURSE all_primitives_spec_files RELATIVE
    "${CMAKE_CURRENT_SOURCE_DIR}/"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable(all_primitives_spec ${all_primitives_spec_files})
set(binary_name "dogen_all_primitives_spec")
set_target_properties(all_primitives_spec PROPERTIES OUTPUT_NAME ${binary_name})

target_link_libraries(all_primitives_spec
    all_primitives
    utility
    ${LIBXML2_LIBRARIES}
    ${Boost_LIBRARIES})

set(all_primitives_spec_cmd
    ${stage_bin_dir}/${binary_name} ${boost_test_parameters})

add_custom_target(run_all_primitives_spec
    COMMAND ${all_primitives_spec_cmd}
    WORKING_DIRECTORY ${stage_bin_dir}
    DEPENDS all_primitives_spec)

add_boost_tests(all_primitives ${all_primitives_spec_files})
