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
#
set(curdir ${CMAKE_CURRENT_SOURCE_DIR})
file(GLOB subdir RELATIVE ${curdir} *)

set(data_directory "share/dogen/data")
foreach(dir ${subdir})
    if(IS_DIRECTORY ${curdir}/${dir})
        file(COPY ${curdir}/${dir} DESTINATION ${stage_dir}/data)
        install(
            DIRECTORY ${dir}/
            DESTINATION ${data_directory}/${dir}
            COMPONENT applications
            FILES_MATCHING PATTERN "*")
    endif()
endforeach()
message(STATUS "Copied all data files.")

if (WITH_JSON_VALIDATION)
    set(files "")

    #
    # Fields
    #
    file(GLOB_RECURSE files RELATIVE
        "${CMAKE_CURRENT_SOURCE_DIR}/fields"
        "${CMAKE_CURRENT_SOURCE_DIR}/fields/*.json")

    add_custom_target(validate_json_fields)
    add_dependencies(validate_all_json validate_json_fields)
    foreach(file ${files})
        add_custom_target(validate_json_fields_${file}
             COMMENT "Validating JSON for fields/${file}."
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMAND ${JQ_COMMAND} . fields/${file} > /dev/null)
        add_dependencies(validate_json_fields validate_json_fields_${file})
    endforeach()

    #
    # library
    #
    file(GLOB_RECURSE files RELATIVE
        "${CMAKE_CURRENT_SOURCE_DIR}/library"
        "${CMAKE_CURRENT_SOURCE_DIR}/library/*.json")

    add_custom_target(validate_json_library)
    add_dependencies(validate_all_json validate_json_library)
    foreach(file ${files})
        add_custom_target(validate_json_library_${file}
             COMMENT "Validating JSON for library/${file}."
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMAND ${JQ_COMMAND} . library/${file} > /dev/null)
        add_dependencies(validate_json_library validate_json_library_${file})
    endforeach()

    #
    # modeline_groups
    #
    file(GLOB_RECURSE files RELATIVE
        "${CMAKE_CURRENT_SOURCE_DIR}/modeline_groups"
        "${CMAKE_CURRENT_SOURCE_DIR}/modeline_groups/*.json")

    add_custom_target(validate_json_modeline_groups)
    add_dependencies(validate_all_json validate_json_modeline_groups)
    foreach(file ${files})
        add_custom_target(validate_json_modeline_groups_${file}
             COMMENT "Validating JSON for modeline_groups/${file}."
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMAND ${JQ_COMMAND} . modeline_groups/${file} > /dev/null)
        add_dependencies(validate_json_modeline_groups
            validate_json_modeline_groups_${file})
    endforeach()

endif()
