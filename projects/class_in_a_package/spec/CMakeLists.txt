# -*- mode: cmake; tab-width: 4; indent-tabs-mode: nil -*-
#
# Copyright (C) 2011 Kitanda
#
# This file is distributed under the Kitanda Proprietary Software
# Licence. See doc/LICENCE.TXT for details.
#
set(class_in_a_package_spec_files "")
file(GLOB_RECURSE class_in_a_package_spec_files RELATIVE
    "${CMAKE_CURRENT_SOURCE_DIR}/"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable(class_in_a_package_spec ${class_in_a_package_spec_files})
set(binary_name "dogen_class_in_a_package_spec")
set_target_properties(class_in_a_package_spec
    PROPERTIES OUTPUT_NAME ${binary_name})

target_link_libraries(class_in_a_package_spec
    class_in_a_package
    utility
    ${LIBXML2_LIBRARIES}
    ${Boost_LIBRARIES})

set(class_in_a_package_spec_cmd
    ${stage_bin_dir}/${binary_name} ${boost_test_parameters})

add_custom_target(run_class_in_a_package_spec
    COMMAND ${class_in_a_package_spec_cmd}
    WORKING_DIRECTORY ${stage_bin_dir}
    DEPENDS class_in_a_package_spec)

add_boost_tests(class_in_a_package ${class_in_a_package_spec_files})
