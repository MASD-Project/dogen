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
set(main_name "test_model_sanitizer")
set(spec_name "${main_name}_spec")
set(spec_files "")
file(GLOB_RECURSE spec_files RELATIVE
    "${CMAKE_CURRENT_SOURCE_DIR}/"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# we need to add these manually as the point of this test model
# is not to generate a make file.
file(GLOB_RECURSE disable_cmakelists_files ABSOLUTE
    "${CMAKE_SOURCE_DIR}/projects/disable_cmakelists/src/*.cpp")

add_executable(${spec_name} ${spec_files} ${disable_cmakelists_files})
set(binary_name "dogen_${spec_name}")
set_target_properties(${spec_name} PROPERTIES OUTPUT_NAME ${binary_name})

target_link_libraries(${spec_name}
    all_primitives
    classes_in_a_package
    classes_inout_package
    classes_without_package
    class_in_a_package
    class_without_package
    compressed
    disable_full_ctor
    disable_facet_folders
    unnamed_model # disable model package
    enable_facet_domain
    enable_facet_hash
    enable_facet_io
    enable_facet_serialization
    split_project
    stand_alone_class
    two_layers_with_objects
    trivial_inheritance
    trivial_association
    enumeration
    std_model
    boost_model
    stereotypes
    utility
    ${LIBXML2_LIBRARIES}
    ${Boost_LIBRARIES}
    )

set(${spec_name}_cmd ${stage_bin_dir}/${binary_name} ${boost_test_parameters})

add_custom_target(run_${spec_name}
    COMMAND ${${spec_name}_cmd}
    WORKING_DIRECTORY ${stage_bin_dir}
    DEPENDS ${spec_name})
add_dependencies(run_all_specs run_${spec_name})

add_boost_tests(${main_name} ${spec_files})
install(TARGETS ${spec_name} RUNTIME DESTINATION bin COMPONENT tests)
