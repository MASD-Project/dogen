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
set(target tack)
add_custom_target(knit_${target}
    COMMENT "Knitting Tack model" VERBATIM
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMAND ${knitter_binary}
    --target ${CMAKE_SOURCE_DIR}/diagrams/${target}.dia
    --reference ${CMAKE_SOURCE_DIR}/diagrams/config.dia,dogen
    --reference ${CMAKE_SOURCE_DIR}/diagrams/dynamic.dia,dogen
    --cpp-project-dir ${CMAKE_SOURCE_DIR}/projects/
    --cpp-disable-cmakelists
    --ignore-files-matching-regex .*/CMakeLists.txt
    --ignore-files-matching-regex .*/test/.*
    --ignore-files-matching-regex .*/spec/.*
    --verbose
    --delete-extra-files
    --external-module-path dogen)
if(use_latest_knitter)
    add_dependencies(knit_${target} knitter)
endif()
add_dependencies(knit_all knit_${target})

set(target dia)
add_custom_target(knit_${target}
    COMMENT "Knitting Dia model" VERBATIM
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMAND ${knitter_binary}
    --target ${CMAKE_SOURCE_DIR}/diagrams/${target}.dia
    --cpp-project-dir ${CMAKE_SOURCE_DIR}/projects/
    --ignore-files-matching-regex .*/test/.*
    --ignore-files-matching-regex .*/spec/.*
    --verbose
    --delete-extra-files
    --external-module-path dogen)
if(use_latest_knitter)
    add_dependencies(knit_${target} knitter)
endif()
add_dependencies(knit_all knit_${target})

set(target config)
add_custom_target(knit_${target}
    COMMENT "Knitting Config model" VERBATIM
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMAND ${knitter_binary}
    --target ${CMAKE_SOURCE_DIR}/diagrams/${target}.dia
    --cpp-project-dir ${CMAKE_SOURCE_DIR}/projects/
    --ignore-files-matching-regex .*/test/.*
    --ignore-files-matching-regex .*/spec/.*
    --verbose
    --delete-extra-files
    --external-module-path dogen)
if(use_latest_knitter)
    add_dependencies(knit_${target} knitter)
endif()
add_dependencies(knit_all knit_${target})

set(target cpp)
add_custom_target(knit_${target}
    COMMENT "Knitting C++ model" VERBATIM
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMAND ${knitter_binary}
    --target ${CMAKE_SOURCE_DIR}/diagrams/${target}.dia
    --reference ${CMAKE_SOURCE_DIR}/diagrams/config.dia,dogen
    --reference ${CMAKE_SOURCE_DIR}/diagrams/tack.dia,dogen
    --reference ${CMAKE_SOURCE_DIR}/diagrams/formatters.dia,dogen
    --reference ${CMAKE_SOURCE_DIR}/diagrams/dynamic.dia,dogen
    --cpp-project-dir ${CMAKE_SOURCE_DIR}/projects/
    --cpp-disable-cmakelists
    --ignore-files-matching-regex .*/CMakeLists.txt
    --ignore-files-matching-regex .*/spec/.*
    --ignore-files-matching-regex .*stitch
    --ignore-files-matching-regex .*_stitch.hpp
    --ignore-files-matching-regex .*_stitch.cpp
    --verbose
    --delete-extra-files
    --external-module-path dogen)
if(use_latest_knitter)
    add_dependencies(knit_${target} knitter)
endif()
add_dependencies(knit_all knit_${target})

set(target database)
add_custom_target(knit_${target}
    COMMENT "Knitting database model" VERBATIM
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMAND ${knitter_binary}
    --target ${CMAKE_SOURCE_DIR}/diagrams/${target}.dia
    --cpp-project-dir ${CMAKE_SOURCE_DIR}/projects/test_models
    --cpp-disable-cmakelists
    --ignore-files-matching-regex .*CMakeLists.txt
    --ignore-files-matching-regex .*/test/.*
    --ignore-files-matching-regex .*/spec/.*
    --ignore-files-matching-regex .*sql
    --ignore-files-matching-regex .*-odb.*
    --verbose
    --delete-extra-files
    --external-module-path dogen::test_models)
if(use_latest_knitter)
    add_dependencies(knit_${target} knitter)
endif()
add_dependencies(knit_all knit_${target})

set(target knit)
add_custom_target(knit_${target}
    COMMENT "Knitting knit model" VERBATIM
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMAND ${knitter_binary}
    --target ${CMAKE_SOURCE_DIR}/diagrams/${target}.dia
    --reference ${CMAKE_SOURCE_DIR}/diagrams/config.dia,dogen
    --reference ${CMAKE_SOURCE_DIR}/diagrams/tack.dia,dogen
    --reference ${CMAKE_SOURCE_DIR}/diagrams/cpp.dia,dogen
    --cpp-project-dir ${CMAKE_SOURCE_DIR}/projects/
    --cpp-disable-cmakelists
    --ignore-files-matching-regex .*/CMakeLists.txt
    --ignore-files-matching-regex .*/spec/.*
    --verbose
    --delete-extra-files
    --external-module-path dogen)
if(use_latest_knitter)
    add_dependencies(knit_${target} knitter)
endif()
add_dependencies(knit_all knit_${target})

set(target dia_to_tack)
add_custom_target(knit_${target}
    COMMENT "Knitting Dia to Tack model" VERBATIM
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMAND ${knitter_binary}
    --target ${CMAKE_SOURCE_DIR}/diagrams/${target}.dia
    --reference ${CMAKE_SOURCE_DIR}/diagrams/dia.dia,dogen
    --reference ${CMAKE_SOURCE_DIR}/diagrams/tack.dia,dogen
    --cpp-project-dir ${CMAKE_SOURCE_DIR}/projects/
    --cpp-disable-cmakelists
    --ignore-files-matching-regex .*/CMakeLists.txt
    --ignore-files-matching-regex .*/spec/.*
    --ignore-files-matching-regex .*/test/.*
    --verbose
    --delete-extra-files
    --external-module-path dogen)
if(use_latest_knitter)
    add_dependencies(knit_${target} knitter)
endif()
add_dependencies(knit_all knit_${target})

set(target formatters)
add_custom_target(knit_${target}
    COMMENT "Knitting the Formatters Model" VERBATIM
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMAND ${knitter_binary}
    --target ${CMAKE_SOURCE_DIR}/diagrams/${target}.dia
    --cpp-project-dir ${CMAKE_SOURCE_DIR}/projects/
    --cpp-disable-cmakelists
    --ignore-files-matching-regex .*/CMakeLists.txt
    --ignore-files-matching-regex .*/spec/.*
    --ignore-files-matching-regex .*/test/.*
    --ignore-files-matching-regex .*/file_formatter_interface_io.hpp
    --ignore-files-matching-regex .*/repository_io.hpp
    --ignore-files-matching-regex .*/transformer_interface_io.hpp
    --ignore-files-matching-regex .*/file_formatter_interface_io.cpp
    --ignore-files-matching-regex .*/repository_io.cpp
    --ignore-files-matching-regex .*/transformer_interface_io.cpp
    --verbose
    --delete-extra-files
    --external-module-path dogen)

if(use_latest_knitter)
    add_dependencies(knit_${target} knitter)
endif()
add_dependencies(knit_all knit_${target})

set(target frontend)
add_custom_target(knit_${target}
    COMMENT "Knitting Frontend model" VERBATIM
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMAND ${knitter_binary}
    --target ${CMAKE_SOURCE_DIR}/diagrams/${target}.dia
    --reference ${CMAKE_SOURCE_DIR}/diagrams/config.dia,dogen
    --reference ${CMAKE_SOURCE_DIR}/diagrams/dia.dia,dogen
    --reference ${CMAKE_SOURCE_DIR}/diagrams/dia_to_tack.dia,dogen
    --reference ${CMAKE_SOURCE_DIR}/diagrams/tack.dia,dogen
    --cpp-project-dir ${CMAKE_SOURCE_DIR}/projects/
    --cpp-disable-cmakelists
    --ignore-files-matching-regex .*/CMakeLists.txt
    --ignore-files-matching-regex .*/spec/.*
    --ignore-files-matching-regex .*/test/.*
    --verbose
    --delete-extra-files
    --external-module-path dogen)
if(use_latest_knitter)
    add_dependencies(knit_${target} knitter)
endif()
add_dependencies(knit_all knit_${target})

set(target backend)
add_custom_target(knit_${target}
    COMMENT "Knitting Backend model" VERBATIM
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMAND ${knitter_binary}
    --target ${CMAKE_SOURCE_DIR}/diagrams/${target}.dia
    --reference ${CMAKE_SOURCE_DIR}/diagrams/config.dia,dogen
    --reference ${CMAKE_SOURCE_DIR}/diagrams/dynamic.dia,dogen
    --reference ${CMAKE_SOURCE_DIR}/diagrams/tack.dia,dogen
    --reference ${CMAKE_SOURCE_DIR}/diagrams/formatters.dia,dogen
    --cpp-project-dir ${CMAKE_SOURCE_DIR}/projects/
    --cpp-disable-cmakelists
    --ignore-files-matching-regex .*/CMakeLists.txt
    --ignore-files-matching-regex .*/spec/.*
    --ignore-files-matching-regex .*/test/.*
    --verbose
    --delete-extra-files
    --external-module-path dogen)
if(use_latest_knitter)
    add_dependencies(knit_${target} knitter)
endif()
add_dependencies(knit_all knit_${target})

set(target dynamic)
add_custom_target(knit_${target}
    COMMENT "Knitting Dynamic model" VERBATIM
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMAND ${knitter_binary}
    --target ${CMAKE_SOURCE_DIR}/diagrams/${target}.dia
    --cpp-project-dir ${CMAKE_SOURCE_DIR}/projects/
    --cpp-disable-cmakelists
    --ignore-files-matching-regex .*/CMakeLists.txt
    --ignore-files-matching-regex .*/spec/.*
    --ignore-files-matching-regex .*/test/.*
    --verbose
    --delete-extra-files
    --external-module-path dogen)
if(use_latest_knitter)
    add_dependencies(knit_${target} knitter)
endif()
add_dependencies(knit_all knit_${target})

set(target stitch)
add_custom_target(knit_${target}
    COMMENT "Knitting Stitch model" VERBATIM
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMAND ${knitter_binary}
    --target ${CMAKE_SOURCE_DIR}/diagrams/${target}.dia
    --reference ${CMAKE_SOURCE_DIR}/diagrams/dynamic.dia,dogen
    --reference ${CMAKE_SOURCE_DIR}/diagrams/formatters.dia,dogen
    --cpp-project-dir ${CMAKE_SOURCE_DIR}/projects/
    --cpp-disable-cmakelists
    --ignore-files-matching-regex .*/CMakeLists.txt
    --ignore-files-matching-regex .*/spec/.*
    --ignore-files-matching-regex .*/test/.*
    --verbose
    --delete-extra-files
    --external-module-path dogen)
if(use_latest_knitter)
    add_dependencies(knit_${target} knitter)
endif()
add_dependencies(knit_all knit_${target})
