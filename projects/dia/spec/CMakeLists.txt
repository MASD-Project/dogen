# -*- mode: cmake; tab-width: 4; indent-tabs-mode: nil -*-
#
# Copyright (C) 2011 Kitanda
#
# This file is distributed under the Kitanda Proprietary Software
# Licence. See doc/LICENCE.TXT for details.
#
set(dia_spec_files "")
file(GLOB_RECURSE dia_spec_files RELATIVE
    "${CMAKE_CURRENT_SOURCE_DIR}/"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable(dia_spec ${dia_spec_files})
set(binary_name "dogen_dia_spec")
set_target_properties(dia_spec PROPERTIES OUTPUT_NAME ${binary_name})

target_link_libraries(dia_spec
    dia
    utility
    ${LIBXML2_LIBRARIES}
    ${Boost_LIBRARIES})

set(dia_spec_cmd ${stage_bin_dir}/${binary_name} ${boost_test_parameters})

add_custom_target(run_dia_spec
    COMMAND ${dia_spec_cmd}
    WORKING_DIRECTORY ${stage_bin_dir}
    DEPENDS dia_spec)

add_boost_tests(dia ${dia_spec_files})
