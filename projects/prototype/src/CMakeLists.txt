# -*- mode: cmake; tab-width: 4; indent-tabs-mode: nil -*-
#
# Copyright (C) 2011 Kitanda
#
# This file is distributed under the Kitanda Proprietary Software
# Licence. See doc/LICENCE.TXT for details.
#
set(files "")
file(GLOB_RECURSE files RELATIVE
    "${CMAKE_CURRENT_SOURCE_DIR}/"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_library(prototype STATIC ${files})
set_target_properties(prototype PROPERTIES OUTPUT_NAME dogen_prototype)
set_target_properties(prototype
    PROPERTIES VERSION ${DOGEN_VERSION} SOVERSION ${DOGEN_MAJOR_VERSION})
