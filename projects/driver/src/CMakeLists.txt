# -*- mode: cmake; tab-width: 4; indent-tabs-mode: nil -*-
#
# Copyright (C) 2011 Kitanda
#
# This file is distributed under the Kitanda Proprietary Software
# Licence. See doc/LICENCE.TXT for details.
#
set(driver_files "")
file(GLOB_RECURSE driver_files RELATIVE
    "${CMAKE_CURRENT_SOURCE_DIR}/"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable(driver ${driver_files})
set(binary_name "dogen_driver")
set_target_properties(driver PROPERTIES OUTPUT_NAME ${binary_name})

target_link_libraries(driver
    generator
    dia
    sml
    utility
    ${LIBXML2_LIBRARIES}
    ${Boost_LIBRARIES})
