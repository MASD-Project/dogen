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
set(frontend "json")
set(models_dir "${CMAKE_CURRENT_SOURCE_DIR}")

if (DOGEN_CLI_EXECUTABLE)
    foreach(model ${models})
        set(target ${model})
        set(target_ext ${target}.${frontend})
        set(target_path ${models_dir}/${target_ext})
        add_custom_target(generate_${target_ext}
            COMMENT "Generating ${target_ext} model" VERBATIM
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMAND ${DOGEN_CLI_EXECUTABLE} generate
            --target ${target_path} ${DOGEN_COMMON_OPTIONS}
            ${DOGEN_GENERATION_OPTIONS})
        add_dependencies(generate_all_${frontend} generate_${target_ext})

        if (WITH_BENCHMARKS)
            add_custom_target(benchmark_generate_${target_ext}
                COMMENT "Benchmarking generating ${target_ext} model" VERBATIM
                WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                COMMAND ${benchmark_command} ${benchmark_repeats}
                ${benchmark_directory}/${benchmark_prefix}${target}.csv
                ${DOGEN_CLI_EXECUTABLE} --target ${target_path}
                ${DOGEN_COMMON_OPTIONS} ${DOGEN_GENERATION_OPTIONS})
            add_dependencies(benchmark_${frontend}
                benchmark_generate_${target_ext})
        endif()
    endforeach()
endif()
