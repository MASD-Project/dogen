# -*- mode: cmake; tab-width: 4; indent-tabs-mode: nil -*-
#
# Copyright (C) 2012 Kitanda
#
# This file is distributed under the Kitanda Proprietary Software
# Licence. See doc/LICENCE.TXT for details.
#
set(all_files "")
file(GLOB_RECURSE all_files RELATIVE
    "${CMAKE_CURRENT_SOURCE_DIR}/"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_library(classes_in_a_package STATIC ${all_files})
set_target_properties(classes_in_a_package PROPERTIES
    OUTPUT_NAME dogen_classes_in_a_package)
