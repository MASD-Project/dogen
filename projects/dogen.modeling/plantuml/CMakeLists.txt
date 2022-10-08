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
set(frontend "plantuml")
set(models_dir "${CMAKE_CURRENT_SOURCE_DIR}")

if (WITH_PLANTUML)
    foreach(model ${models})
        set(model_name "")
        get_filename_component(model_name ${model} NAME)
        string(REGEX REPLACE ".org$" "" model_name
            ${model_name})

        set(target ${model_name})
        set(target_ext ${target}.${frontend})
        set(target_path ${models_dir}/${target_ext})
        add_custom_target(generate_${target_ext}_${frontend}
            COMMENT "Generating UML for ${target_ext} model" VERBATIM
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMAND ${PLANTUML_ENVIRONMENT} ${PLANTUML_PROGRAM}
            ${PLANTUML_OPTIONS} ${target_path})
        add_dependencies(generate_all_${frontend} generate_${target_ext}_${frontend})
    endforeach()
endif()
