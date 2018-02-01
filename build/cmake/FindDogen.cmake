# -*- mode: cmake; cmake-tab-width: 4; indent-tabs-mode: nil -*-
#
# Copyright (C) 2016 Domain Driven Consulting Plc
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
find_program(DOGEN_KNITTER_EXECUTABLE NAMES dogen.knitter
    HINTS ${CMAKE_BINARY_DIR}/stage/bin)
if (DOGEN_KNITTER_EXECUTABLE)
    execute_process(
        COMMAND ${DOGEN_KNITTER_EXECUTABLE} --version
        COMMAND grep ^Dogen
        COMMAND cut -b15-
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        ERROR_VARIABLE DOGEN_ERROR
        OUTPUT_VARIABLE DOGEN_KNITTER_VERSION
        RESULT_VARIABLE DOGEN_RESULT
        OUTPUT_STRIP_TRAILING_WHITESPACE)

      message(STATUS "Found Dogen Knitter ${DOGEN_KNITTER_VERSION} (${DOGEN_KNITTER_EXECUTABLE})")
else()
    message(STATUS "Dogen Knitter not found.")
endif()

find_program(DOGEN_STITCHER_EXECUTABLE NAMES dogen.stitcher
    HINTS ${CMAKE_BINARY_DIR}/stage/bin)
if (DOGEN_STITCHER_EXECUTABLE)
    execute_process(
        COMMAND ${DOGEN_STITCHER_EXECUTABLE} --version
        COMMAND grep ^Dogen
        COMMAND cut -b16-
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        ERROR_VARIABLE DOGEN_ERROR
        OUTPUT_VARIABLE DOGEN_STITCHER_VERSION
        RESULT_VARIABLE DOGEN_RESULT
        OUTPUT_STRIP_TRAILING_WHITESPACE)

      message(STATUS "Found Dogen Stitcher ${DOGEN_STITCHER_VERSION} (${DOGEN_STITCHER_EXECUTABLE})")
else()
    message(STATUS "Dogen Stitcher not found.")
endif()

find_program(DOGEN_TAILOR_EXECUTABLE NAMES dogen.tailor
    HINTS ${CMAKE_BINARY_DIR}/stage/bin)
if (DOGEN_TAILOR_EXECUTABLE)
    execute_process(
        COMMAND ${DOGEN_TAILOR_EXECUTABLE} --version
        COMMAND grep ^Dogen
        COMMAND cut -b14-
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        ERROR_VARIABLE DOGEN_ERROR
        OUTPUT_VARIABLE DOGEN_TAILOR_VERSION
        RESULT_VARIABLE DOGEN_RESULT
        OUTPUT_STRIP_TRAILING_WHITESPACE)

      message(STATUS "Found Dogen Tailor ${DOGEN_TAILOR_VERSION} (${DOGEN_TAILOR_EXECUTABLE})")
else()
    message(STATUS "Dogen Tailor not found.")
endif()
