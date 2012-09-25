# -*- mode: cmake; tab-width: 4; indent-tabs-mode: nil -*-
#
# Copyright (C) 2011 Kitanda
#
# This file is distributed under the Kitanda Proprietary Software
# Licence. See doc/LICENCE.TXT for details.
#
set(utility_spec_files "")
file(GLOB_RECURSE utility_spec_files RELATIVE
    "${CMAKE_CURRENT_SOURCE_DIR}/"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable(utility_spec ${utility_spec_files})
set(binary_name "dogen_utility_spec")
set_target_properties(utility_spec PROPERTIES OUTPUT_NAME ${binary_name})

target_link_libraries(utility_spec
    utility
    ${LIBXML2_LIBRARIES}
    ${Boost_LIBRARIES})

set(utility_spec_cmd ${stage_bin_dir}/${binary_name} ${boost_test_parameters})

add_custom_target(run_utility_spec
    COMMAND ${utility_spec_cmd}
    WORKING_DIRECTORY ${stage_bin_dir}
    DEPENDS utility_spec)

add_boost_tests(utility ${utility_spec_files})
