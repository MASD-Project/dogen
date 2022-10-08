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
if (DOGEN_CLI_EXECUTABLE)
    set(models_dir "${CMAKE_CURRENT_SOURCE_DIR}")
    set(frontend "org")
    set(target "dogen")
    set(target_ext ${target}.${frontend})
    set(target_path ${models_dir}/${target_ext})
    add_custom_target(generate_${target_ext}
        COMMENT "Generating ${target_ext} model" VERBATIM
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMAND ${DOGEN_CLI_EXECUTABLE} generate
        --target ${target_path} ${DOGEN_COMMON_OPTIONS}
        ${DOGEN_GENERATION_OPTIONS} ${DOGEN_REFERENCE_OPTIONS})
    add_dependencies(generate_all_${frontend} generate_${target_ext})

    set(output_dir "${CMAKE_CURRENT_SOURCE_DIR}")
    set(source ${output_dir}/${target}.org)
    set(destination ${output_dir}/${target}.org)
    add_custom_target(convert_${target_ext}_org
        COMMENT "Converting ${target}.org to Org."
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMAND ${DOGEN_CLI_EXECUTABLE} convert
        --source ${source} --destination ${destination}
        ${DOGEN_COMMON_OPTIONS})
    add_dependencies(convert_all_org convert_${target_ext}_org)

    set(output_dir "${CMAKE_CURRENT_SOURCE_DIR}")
    set(source ${output_dir}/${target}.org)
    set(destination ${output_dir}/${target}.plantuml)
    add_custom_target(convert_${target_ext}_plantuml
        COMMENT "Converting ${target}.org to PlantUML."
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMAND ${DOGEN_CLI_EXECUTABLE} convert
        --source ${source} --destination ${destination}
        ${DOGEN_COMMON_OPTIONS})
    add_dependencies(convert_all_plantuml convert_${target_ext}_plantuml)

    if (WITH_PLANTUML)
        set(frontend "plantuml")
        set(target_ext ${target}.${frontend})
        set(target_path ${models_dir}/${target_ext})
        add_custom_target(generate_${target_ext}
            COMMENT "Generating UML for ${target_ext} model" VERBATIM
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMAND ${PLANTUML_ENVIRONMENT} ${PLANTUML_PROGRAM}
            ${PLANTUML_OPTIONS} ${target_path})
        add_dependencies(generate_all_${frontend} generate_${target_ext})
    endif()

endif()
