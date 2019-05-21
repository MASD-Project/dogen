# -*- mode: cmake; cmake-tab-width: 4; indent-tabs-mode: nil -*-
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
set(curdir ${CMAKE_CURRENT_SOURCE_DIR})
file(GLOB subdir RELATIVE ${curdir} *)

set(share_directory "share/dogen")
foreach(dir ${subdir})
    if(IS_DIRECTORY ${curdir}/${dir})
        file(COPY ${curdir}/${dir} DESTINATION ${stage_dir}/share)
        install(
            DIRECTORY ${dir}/
            DESTINATION ${share_directory}/${dir}
            COMPONENT applications
            FILES_MATCHING PATTERN "*")
    endif()
endforeach()
message(STATUS "Copied all data files.")

if (WITH_JSON_VALIDATION)
    set(files "")

    set(folder "library")
    file(GLOB_RECURSE files RELATIVE
        "${CMAKE_CURRENT_SOURCE_DIR}/${folder}"
        "${CMAKE_CURRENT_SOURCE_DIR}/${folder}/*.json")

    add_custom_target(validate_json_${folder})
    add_dependencies(validate_all_json validate_json_${folder})

    add_custom_target(indent_json_${folder})
    add_dependencies(indent_all_json indent_json_${folder})
    foreach(file ${files})
        add_custom_target(validate_json_${folder}_${file}
            COMMENT "Validating JSON for ${folder}/${file}."
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMAND ${JQ_COMMAND} . ${folder}/${file} > /dev/null)
        add_dependencies(validate_json_${folder}
            validate_json_${folder}_${file})

        add_custom_target(indent_json_${folder}_${file}
             COMMENT "Indenting JSON for ${folder}/${file}."
             WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
             COMMAND ${JQ_COMMAND} . ${folder}/${file} > ${folder}/${file}_tmp
             COMMAND mv ${folder}/${file}_tmp ${folder}/${file})
        add_dependencies(indent_json_${folder} indent_json_${folder}_${file})
    endforeach()
endif()
