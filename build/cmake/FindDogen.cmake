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
find_program(DOGEN_CLI_EXECUTABLE NAMES dogen.cli
    HINTS ${CMAKE_BINARY_DIR}/stage/bin)

if (DOGEN_CLI_EXECUTABLE)
    execute_process(
        COMMAND ${DOGEN_CLI_EXECUTABLE} --version
        COMMAND grep ^MASD
        COMMAND cut -b12-
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        ERROR_VARIABLE DOGEN_ERROR
        OUTPUT_VARIABLE DOGEN_KNITTER_VERSION
        RESULT_VARIABLE DOGEN_RESULT
        OUTPUT_STRIP_TRAILING_WHITESPACE)

    message(STATUS
        "Found Dogen CLI ${DOGEN_KNITTER_VERSION} (${DOGEN_CLI_EXECUTABLE})")
else()
    message(STATUS "Dogen CLI not found.")
endif()
