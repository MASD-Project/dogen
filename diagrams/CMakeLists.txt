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
add_custom_target(codegen)

set(dogen_dir "${CMAKE_BINARY_DIR}/stage/bin/")
set(dogen_binary "${dogen_dir}/dogen_driver")
set(dogen_version "")
set(use_latest_driver FALSE)
execute_process(
    COMMAND ${dogen_binary} --version
    COMMAND head -n1
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    OUTPUT_VARIABLE dogen_version
    RESULT_VARIABLE ret_var
    OUTPUT_STRIP_TRAILING_WHITESPACE)

message(STATUS "Using: ${dogen_version}")

set(target sml)
add_custom_target(codegen_${target}
    COMMENT "Generating SML model" VERBATIM
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMAND ${dogen_binary}
    --target ${CMAKE_SOURCE_DIR}/diagrams/${target}.dia
    --cpp-project-dir ${CMAKE_SOURCE_DIR}/projects/
    --cpp-enable-facet domain
    --cpp-enable-facet io
    --cpp-enable-facet hash
    --cpp-enable-facet serialization
    --cpp-enable-facet test_data
    --ignore-files-matching-regex .*/test/.*
    --ignore-files-matching-regex .*/spec/.*
    -v -d -p dogen)
if(use_latest_driver)
    add_dependencies(codegen_${target} driver)
endif()
add_dependencies(codegen codegen_${target})

set(target dia)
add_custom_target(codegen_${target}
    COMMENT "Generating Dia model" VERBATIM
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMAND ${dogen_binary}
    --target ${CMAKE_SOURCE_DIR}/diagrams/${target}.dia
    --cpp-project-dir ${CMAKE_SOURCE_DIR}/projects/
    --cpp-enable-facet domain
    --cpp-enable-facet io
    --cpp-enable-facet hash
    --cpp-enable-facet serialization
    --cpp-enable-facet test_data
    --ignore-files-matching-regex .*/test/.*
    --ignore-files-matching-regex .*/spec/.*
    -v -d -p dogen)
if(use_latest_driver)
    add_dependencies(codegen_${target} driver)
endif()
add_dependencies(codegen codegen_${target})

set(target config)
add_custom_target(codegen_${target}
    COMMENT "Generating Config model" VERBATIM
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMAND ${dogen_binary}
    --target ${CMAKE_SOURCE_DIR}/diagrams/${target}.dia
    --cpp-project-dir ${CMAKE_SOURCE_DIR}/projects/
    --cpp-enable-facet domain
    --cpp-enable-facet io
    --cpp-enable-facet hash
    --cpp-enable-facet serialization
    --cpp-enable-facet test_data
    --ignore-files-matching-regex .*/test/.*
    --ignore-files-matching-regex .*/spec/.*
    -v -d -p dogen)
if(use_latest_driver)
    add_dependencies(codegen_${target} driver)
endif()
add_dependencies(codegen codegen_${target})

set(target cpp)
add_custom_target(codegen_${target}
    COMMENT "Generating C++ model" VERBATIM
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMAND ${dogen_binary}
    --target ${CMAKE_SOURCE_DIR}/diagrams/${target}.dia
    --reference ${CMAKE_SOURCE_DIR}/diagrams/config.dia,dogen
    --reference ${CMAKE_SOURCE_DIR}/diagrams/sml.dia,dogen
    --cpp-project-dir ${CMAKE_SOURCE_DIR}/projects/
    --cpp-enable-facet domain
    --cpp-enable-facet io
    --cpp-enable-facet hash
    --cpp-enable-facet serialization
    --cpp-enable-facet test_data
    --ignore-files-matching-regex .*/spec/.*
    -v -d -p dogen)
if(use_latest_driver)
    add_dependencies(codegen_${target} driver)
endif()
add_dependencies(codegen codegen_${target})

set(target database)
add_custom_target(codegen_${target}
    COMMENT "Generating database model" VERBATIM
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMAND ${dogen_binary}
    --target ${CMAKE_SOURCE_DIR}/diagrams/${target}.dia
    --cpp-project-dir ${CMAKE_SOURCE_DIR}/projects/
    --cpp-enable-facet domain
    --cpp-enable-facet io
    --cpp-enable-facet hash
    --cpp-enable-facet serialization
    --cpp-enable-facet test_data
    --cpp-enable-facet odb
    --ignore-files-matching-regex .*/test/.*
    --ignore-files-matching-regex .*/spec/.*
    --ignore-files-matching-regex .*sql
    --ignore-files-matching-regex .*-odb.*
    -v -d -p dogen)
if(use_latest_driver)
    add_dependencies(codegen_${target} driver)
endif()
add_dependencies(codegen codegen_${target})

set(target engine)
add_custom_target(codegen_${target}
    COMMENT "Generating engine model" VERBATIM
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMAND ${dogen_binary}
    --target ${CMAKE_SOURCE_DIR}/diagrams/${target}.dia
    --reference ${CMAKE_SOURCE_DIR}/diagrams/config.dia,dogen
    --reference ${CMAKE_SOURCE_DIR}/diagrams/sml.dia,dogen
    --reference ${CMAKE_SOURCE_DIR}/diagrams/cpp.dia,dogen
    --cpp-project-dir ${CMAKE_SOURCE_DIR}/projects/
    --cpp-enable-facet domain
    --cpp-enable-facet io
    --cpp-enable-facet hash
    --cpp-enable-facet serialization
    --cpp-enable-facet test_data
    --cpp-disable-cmakelists
    --ignore-files-matching-regex .*/CMakeLists.txt
    --ignore-files-matching-regex .*/spec/.*
    -v -d -p dogen)
if(use_latest_driver)
    add_dependencies(codegen_${target} driver)
endif()
add_dependencies(codegen codegen_${target})

set(target dia_to_sml)
add_custom_target(codegen_${target}
    COMMENT "Generating engine model" VERBATIM
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMAND ${dogen_binary}
    --target ${CMAKE_SOURCE_DIR}/diagrams/${target}.dia
    --reference ${CMAKE_SOURCE_DIR}/diagrams/dia.dia,dogen
    --reference ${CMAKE_SOURCE_DIR}/diagrams/sml.dia,dogen
    --cpp-project-dir ${CMAKE_SOURCE_DIR}/projects/
    --cpp-enable-facet domain
    --cpp-enable-facet io
    --cpp-enable-facet hash
    --cpp-enable-facet serialization
    --cpp-enable-facet test_data
    --cpp-disable-cmakelists
    --ignore-files-matching-regex .*/CMakeLists.txt
    --ignore-files-matching-regex .*/spec/.*
    --ignore-files-matching-regex .*/test/.*
    -v -d -p dogen)
if(use_latest_driver)
    add_dependencies(codegen_${target} driver)
endif()
add_dependencies(codegen codegen_${target})
