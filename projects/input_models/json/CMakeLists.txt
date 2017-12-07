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
set(models_dir "${projects_dir}/input_models/${frontend}")

if (DOGEN_KNITTER_EXECUTABLE)
    foreach(model ${models})
        set(target ${model})
        set(target_path ${models_dir}/${target}.${frontend})
        add_custom_target(knit_${target}_${frontend}
            COMMENT "Knitting ${target} model" VERBATIM
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMAND ${DOGEN_KNITTER_EXECUTABLE}
            --target ${target_path} ${common_arguments})
        add_dependencies(knit_all knit_${target})

        if (WITH_BENCHMARKS)
            add_custom_target(benchmark_knit_${target}_${frontend}
                COMMENT "Benchmarking knitting ${target} model" VERBATIM
                WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                COMMAND ${benchmark_command} ${benchmark_repeats}
                ${benchmark_directory}/${benchmark_prefix}${target}.csv
                ${DOGEN_KNITTER_EXECUTABLE} --target ${target_path}
                ${common_arguments})
            add_dependencies(benchmark_all benchmark_knit_${target})
        endif()
    endforeach()

    set(target northwind)
    add_custom_target(knit_${target}_${frontend}
        COMMENT "Knitting Northwind model" VERBATIM
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMAND ${DOGEN_KNITTER_EXECUTABLE}
        --target ${models_dir}/${target}.${frontend}
        --output-dir ${projects_dir}/test_models
        ${other_options}
        ${ignore_regexes}
        --ignore-files-matching-regex .*sql
        --ignore-files-matching-regex .*-odb.*)
    add_dependencies(knit_all knit_${target})

    if (WITH_BENCHMARKS)
        set(target northwind)
        add_custom_target(benchmark_knit_${target}_${frontend}
            COMMENT "Benchmarking knitting Northwind model" VERBATIM
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMAND ${benchmark_command} ${benchmark_repeats}
            ${benchmark_directory}/${benchmark_prefix}${target}.csv
            ${DOGEN_KNITTER_EXECUTABLE} --target ${models_dir}/${target}.${frontend}
            --output-dir ${projects_dir}/test_models
            ${other_options}
            ${ignore_regexes}
            --ignore-files-matching-regex .*sql
            --ignore-files-matching-regex .*-odb.*)
        add_dependencies(benchmark_all benchmark_knit_${target})
    endif()
endif()
