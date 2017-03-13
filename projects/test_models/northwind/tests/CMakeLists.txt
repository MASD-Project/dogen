# -*- mode: cmake; tab-width: 4; indent-tabs-mode: nil -*-
#
# Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
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
set(tests_files "")
file(GLOB_RECURSE tests_files RELATIVE
    "${CMAKE_CURRENT_SOURCE_DIR}/"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable(northwind_tests ${tests_files})
set(binary_name "dogen_northwind_tests")
set_target_properties(northwind_tests PROPERTIES OUTPUT_NAME ${binary_name})

target_link_libraries(northwind_tests
    northwind
    utility
    ${LIBXML2_LIBRARIES}
    ${Boost_LIBRARIES}
    ${ODB_CORE_LIBRARY}
    ${ODB_PGSQL_LIBRARY}
    ${ODB_BOOST_LIBRARY}
    ${PQXX_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT})

set(command $<TARGET_FILE:${tests_name}> ${boost_test_parameters})

add_custom_target(run_northwind_tests
    COMMAND ${command}
    WORKING_DIRECTORY ${stage_bin_dir}
    DEPENDS northwind_tests)
add_dependencies(run_all_testss run_northwind_tests)

add_boost_tests(northwind ${test^s_files})
install(TARGETS northwind_tests RUNTIME DESTINATION bin COMPONENT tests)
