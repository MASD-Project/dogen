# -*- mode: cmake; cmake-tab-width: 4; indent-tabs-mode: nil -*-
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
set(input_dir "org")
set(folder "${CMAKE_CURRENT_SOURCE_DIR}/org")
if (DOGEN_CLI_EXECUTABLE)
    #
    # Model conversion
    #
    file(GLOB models "org/*.org")
    foreach(model ${models})
        set(model_name "")
        get_filename_component(model_name ${model} NAME)

        set(output_dir "${CMAKE_CURRENT_SOURCE_DIR}/plantuml")
        set(destination_name ${output_dir}/${model_name})
        string(REGEX REPLACE ".org$" ".plantuml" destination_name
            ${destination_name})

        add_custom_target(convert_${model_name}_plantuml
            COMMENT "Converting ${model_name} to PlantUML."
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMAND ${DOGEN_CLI_EXECUTABLE} convert
            --source ${model} --destination ${destination_name}
            ${DOGEN_COMMON_OPTIONS})
        add_dependencies(convert_all_plantuml convert_${model_name}_plantuml)
    endforeach()

    #
    # Input models for generation
    #
    set(prefix "dogen")
    set(models "")
    set(models ${models} ${prefix}.profiles)
    set(models ${models} ${prefix}.variability)
    set(models ${models} ${prefix}.relational)
    set(models ${models} ${prefix}.identification)
endif()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/org)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/plantuml)
