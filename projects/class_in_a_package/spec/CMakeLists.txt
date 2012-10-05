# -*- mode: cmake; tab-width: 4; indent-tabs-mode: nil -*-
#
# Copyright (C) 2012 Kitanda
#
# This file is distributed under the Kitanda Proprietary Software
# Licence. See doc/LICENCE.TXT for details.
#
set(main_name "class_in_a_package")
set(spec_name "${main_name}_spec")
set(spec_files "")
file(GLOB_RECURSE spec_files RELATIVE
    "${CMAKE_CURRENT_SOURCE_DIR}/"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable(${spec_name} ${spec_files})
set(binary_name "dogen_${spec_name}")
set_target_properties(${spec_name} PROPERTIES OUTPUT_NAME ${binary_name})

target_link_libraries(${spec_name}
    ${main_name}
    utility
    ${LIBXML2_LIBRARIES}
    ${Boost_LIBRARIES})

set(${spec_name}_cmd ${stage_bin_dir}/${binary_name} ${boost_test_parameters})

add_custom_target(run_${spec_name}
    COMMAND ${${spec_name}_cmd}
    WORKING_DIRECTORY ${stage_bin_dir}
    DEPENDS ${spec_name})

add_boost_tests(${main_name} ${files})
