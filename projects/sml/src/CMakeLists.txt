# -*- mode: cmake; tab-width: 4; indent-tabs-mode: nil -*-
#
# Copyright (C) 2011 Kitanda
#
# This file is distributed under the Kitanda Proprietary Software
# Licence. See doc/LICENCE.TXT for details.
#
set(sml_files "")
file(GLOB_RECURSE sml_files RELATIVE
    "${CMAKE_CURRENT_SOURCE_DIR}/"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_library(sml STATIC ${sml_files})
set_target_properties(sml PROPERTIES OUTPUT_NAME dogen_sml)
set_target_properties(sml
    PROPERTIES VERSION ${KITANDA_VERSION} SOVERSION ${KITANDA_MAJOR_VERSION})
