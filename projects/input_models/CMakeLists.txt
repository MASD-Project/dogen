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
set(projects_dir "${CMAKE_SOURCE_DIR}/projects")
set(models_dir "${projects_dir}/input_models")

if (DOGEN_KNITTER_COMMAND)
    set(ignore_regexes --ignore-files-matching-regex .*/CMakeLists.txt)
    set(ignore_regexes ${ignore_regexes} --ignore-files-matching-regex .*/test/.*)
    set(ignore_regexes ${ignore_regexes} --ignore-files-matching-regex .*/tests/.*)

    set(other_options --log_level debug)
    set(other_options ${other_options} --delete-extra-files)

    set(common_arguments --output-dir ${projects_dir}/)
    set(common_arguments ${common_arguments} ${other_options})
    set(common_arguments ${common_arguments} ${ignore_regexes})

    set(target yarn)
    add_custom_target(knit_${target}
        COMMENT "Knitting Yarn model" VERBATIM
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMAND ${DOGEN_KNITTER_COMMAND}
        --target ${models_dir}/${target}.dia
        ${common_arguments})
    add_dependencies(knit_all knit_${target})

    set(target yarn.json)
    add_custom_target(knit_${target}
        COMMENT "Knitting Yarn JSON model" VERBATIM
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMAND ${DOGEN_KNITTER_COMMAND}
        --target ${models_dir}/${target}.dia
        ${common_arguments})
    add_dependencies(knit_all knit_${target})

    set(target dia)
    add_custom_target(knit_${target}
        COMMENT "Knitting Dia model" VERBATIM
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMAND ${DOGEN_KNITTER_COMMAND}
        --target ${models_dir}/${target}.dia
        ${common_arguments})
    add_dependencies(knit_all knit_${target})

    set(target options)
    add_custom_target(knit_${target}
        COMMENT "Knitting Options model" VERBATIM
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMAND ${DOGEN_KNITTER_COMMAND}
        --target ${models_dir}/${target}.dia
        ${common_arguments})
    add_dependencies(knit_all knit_${target})

    set(target quilt)
    add_custom_target(knit_${target}x
        COMMENT "Knitting Quilt model" VERBATIM
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMAND ${DOGEN_KNITTER_COMMAND}
        --target ${models_dir}/${target}.dia
        ${common_arguments})
    add_dependencies(knit_all knit_${target}x)

    set(target quilt.cpp)
    add_custom_target(knit_${target}
        COMMENT "Knitting Quilt C++ model" VERBATIM
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMAND ${DOGEN_KNITTER_COMMAND}
        --target ${models_dir}/${target}.dia
        ${common_arguments})
    add_dependencies(knit_all knit_${target})

    set(target quilt.csharp)
    add_custom_target(knit_${target}
        COMMENT "Knitting Quilt C# model" VERBATIM
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMAND ${DOGEN_KNITTER_COMMAND}
        --target ${models_dir}/${target}.dia
        ${common_arguments})
    add_dependencies(knit_all knit_${target})

    set(target database)
    add_custom_target(knit_${target}
        COMMENT "Knitting database model" VERBATIM
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMAND ${DOGEN_KNITTER_COMMAND}
        --target ${models_dir}/${target}.dia
        --output-dir ${projects_dir}/test_models
        ${other_options}
        ${ignore_regexes}
        --ignore-files-matching-regex .*sql
        --ignore-files-matching-regex .*-odb.*)
    add_dependencies(knit_all knit_${target})

    set(target knit)
    add_custom_target(knit_${target}
        COMMENT "Knitting knit model" VERBATIM
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMAND ${DOGEN_KNITTER_COMMAND}
        --target ${models_dir}/${target}.dia
        ${common_arguments})
    add_dependencies(knit_all knit_${target})

    set(target yarn.dia)
    add_custom_target(knit_${target}
        COMMENT "Knitting Yarn Dia model" VERBATIM
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMAND ${DOGEN_KNITTER_COMMAND}
        --target ${models_dir}/${target}.dia
        ${common_arguments})
    add_dependencies(knit_all knit_${target})

    set(target formatters)
    add_custom_target(knit_${target}
        COMMENT "Knitting the Formatters Model" VERBATIM
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMAND ${DOGEN_KNITTER_COMMAND}
        --target ${models_dir}/${target}.dia
        ${common_arguments})
    add_dependencies(knit_all knit_${target})

    set(target annotations)
    add_custom_target(knit_${target}
        COMMENT "Knitting Annotations model" VERBATIM
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMAND ${DOGEN_KNITTER_COMMAND}
        --target ${models_dir}/${target}.dia
        ${common_arguments})
    add_dependencies(knit_all knit_${target})

    set(target stitch)
    add_custom_target(knit_${target}
        COMMENT "Knitting Stitch model" VERBATIM
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMAND ${DOGEN_KNITTER_COMMAND}
        --target ${models_dir}/${target}.dia
        ${common_arguments})
    add_dependencies(knit_all knit_${target})

    set(target wale)
    add_custom_target(knit_${target}
        COMMENT "Knitting Wale model" VERBATIM
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMAND ${DOGEN_KNITTER_COMMAND}
        --target ${models_dir}/${target}.dia
        ${common_arguments})
    add_dependencies(knit_all knit_${target})

    set(target upsilon)
    add_custom_target(knit_${target}
        COMMENT "Knitting Upsilon model" VERBATIM
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMAND ${DOGEN_KNITTER_COMMAND}
        --target ${models_dir}/${target}.dia
        ${common_arguments})
    add_dependencies(knit_all knit_${target})

    set(target yarn.upsilon)
    add_custom_target(knit_${target}
        COMMENT "Knitting Yarn Upsilon model" VERBATIM
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMAND ${DOGEN_KNITTER_COMMAND}
        --target ${models_dir}/${target}.dia
        ${common_arguments})
    add_dependencies(knit_all knit_${target})

    if(WITH_BENCHMARKS)
        set(target yarn)
        add_custom_target(benchmark_knit_${target}
            COMMENT "Benchmarking knitting Yarn model" VERBATIM
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMAND ${benchmark_command} ${benchmark_repeats}
            ${benchmark_directory}/${benchmark_prefix}${target}.csv
            ${DOGEN_KNITTER_COMMAND} --target ${models_dir}/${target}.dia
            ${common_arguments})
        add_dependencies(benchmark_all benchmark_knit_${target})

        set(target yarn.json)
        add_custom_target(benchmark_knit_${target}
            COMMENT "Benchmarking knitting Yarn JSON model" VERBATIM
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMAND ${benchmark_command} ${benchmark_repeats}
            ${benchmark_directory}/${benchmark_prefix}${target}.csv
            ${DOGEN_KNITTER_COMMAND} --target ${models_dir}/${target}.dia
            ${common_arguments})
        add_dependencies(benchmark_all benchmark_knit_${target})

        set(target dia)
        add_custom_target(benchmark_knit_${target}
            COMMENT "Benchmarking knitting Dia model" VERBATIM
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMAND ${benchmark_command} ${benchmark_repeats}
            ${benchmark_directory}/${benchmark_prefix}${target}.csv
            ${DOGEN_KNITTER_COMMAND} --target ${models_dir}/${target}.dia
            ${common_arguments})
        add_dependencies(benchmark_all benchmark_knit_${target})

        set(target options)
        add_custom_target(benchmark_knit_${target}
            COMMENT "Benchmarking knitting Options model" VERBATIM
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMAND ${benchmark_command} ${benchmark_repeats}
            ${benchmark_directory}/${benchmark_prefix}${target}.csv
            ${DOGEN_KNITTER_COMMAND} --target ${models_dir}/${target}.dia
            ${common_arguments})
        add_dependencies(benchmark_all benchmark_knit_${target})

        set(target quilt)
        add_custom_target(benchmark_knit_${target}x
            COMMENT "Benchmarking knitting Quilt model" VERBATIM
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMAND ${benchmark_command} ${benchmark_repeats}
            ${benchmark_directory}/${benchmark_prefix}${target}.csv
            ${DOGEN_KNITTER_COMMAND} --target ${models_dir}/${target}.dia
            ${common_arguments})
        add_dependencies(benchmark_all benchmark_knit_${target}x)

        set(target quilt.cpp)
        add_custom_target(benchmark_knit_${target}
            COMMENT "Benchmarking knitting Quilt C++ model" VERBATIM
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMAND ${benchmark_command} ${benchmark_repeats}
            ${benchmark_directory}/${benchmark_prefix}${target}.csv
            ${DOGEN_KNITTER_COMMAND} --target ${models_dir}/${target}.dia
            ${common_arguments})
        add_dependencies(benchmark_all benchmark_knit_${target})

        set(target quilt.csharp)
        add_custom_target(benchmark_knit_${target}
            COMMENT "Benchmarking knitting Quilt C# model" VERBATIM
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMAND ${benchmark_command} ${benchmark_repeats}
            ${benchmark_directory}/${benchmark_prefix}${target}.csv
            ${DOGEN_KNITTER_COMMAND} --target ${models_dir}/${target}.dia
            ${common_arguments})
        add_dependencies(benchmark_all benchmark_knit_${target})

        set(target database)
        add_custom_target(benchmark_knit_${target}
            COMMENT "Benchmarking knitting database model" VERBATIM
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMAND ${benchmark_command} ${benchmark_repeats}
            ${benchmark_directory}/${benchmark_prefix}${target}.csv
            ${DOGEN_KNITTER_COMMAND} --target ${models_dir}/${target}.dia
            --output-dir ${projects_dir}/test_models
            ${other_options}
            ${ignore_regexes}
            --ignore-files-matching-regex .*sql
            --ignore-files-matching-regex .*-odb.*)
        add_dependencies(benchmark_all benchmark_knit_${target})

        set(target knit)
        add_custom_target(benchmark_knit_${target}
            COMMENT "Benchmarking knitting knit model" VERBATIM
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMAND ${benchmark_command} ${benchmark_repeats}
            ${benchmark_directory}/${benchmark_prefix}${target}.csv
            ${DOGEN_KNITTER_COMMAND} --target ${models_dir}/${target}.dia
            ${common_arguments})
        add_dependencies(benchmark_all benchmark_knit_${target})

        set(target yarn.dia)
        add_custom_target(benchmark_knit_${target}
            COMMENT "Benchmarking knitting Yarn Dia model" VERBATIM
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMAND ${benchmark_command} ${benchmark_repeats}
            ${benchmark_directory}/${benchmark_prefix}${target}.csv
            ${DOGEN_KNITTER_COMMAND} --target ${models_dir}/${target}.dia
            ${common_arguments})
        add_dependencies(benchmark_all benchmark_knit_${target})

        set(target formatters)
        add_custom_target(benchmark_knit_${target}
            COMMENT "Benchmarking knitting Formatters Model" VERBATIM
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMAND ${benchmark_command} ${benchmark_repeats}
            ${benchmark_directory}/${benchmark_prefix}${target}.csv
            ${DOGEN_KNITTER_COMMAND} --target ${models_dir}/${target}.dia
            ${common_arguments})
        add_dependencies(benchmark_all benchmark_knit_${target})

        set(target annotations)
        add_custom_target(benchmark_knit_${target}
            COMMENT "Benchmarking knitting Annotations model" VERBATIM
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMAND ${benchmark_command} ${benchmark_repeats}
            ${benchmark_directory}/${benchmark_prefix}${target}.csv
            ${DOGEN_KNITTER_COMMAND} --target ${models_dir}/${target}.dia
            ${common_arguments})
        add_dependencies(benchmark_all benchmark_knit_${target})

        set(target stitch)
        add_custom_target(benchmark_knit_${target}
            COMMENT "Benchmarking knitting Stitch model" VERBATIM
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMAND ${benchmark_command} ${benchmark_repeats}
            ${benchmark_directory}/${benchmark_prefix}${target}.csv
            ${DOGEN_KNITTER_COMMAND} --target ${models_dir}/${target}.dia
            ${common_arguments})
        add_dependencies(benchmark_all benchmark_knit_${target})

        set(target wale)
        add_custom_target(benchmark_knit_${target}
            COMMENT "Benchmarking knitting Wale model" VERBATIM
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMAND ${benchmark_command} ${benchmark_repeats}
            ${benchmark_directory}/${benchmark_prefix}${target}.csv
            ${DOGEN_KNITTER_COMMAND} --target ${models_dir}/${target}.dia
            ${common_arguments})
        add_dependencies(benchmark_all benchmark_knit_${target})

        set(target upsilon)
        add_custom_target(benchmark_knit_${target}
            COMMENT "Benchmarking knitting Upsilon model" VERBATIM
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMAND ${benchmark_command} ${benchmark_repeats}
            ${benchmark_directory}/${benchmark_prefix}${target}.csv
            ${DOGEN_KNITTER_COMMAND} --target ${models_dir}/${target}.dia
            ${common_arguments})
        add_dependencies(benchmark_all benchmark_knit_${target})

        set(target yarn.upsilon)
        add_custom_target(benchmark_knit_${target}
            COMMENT "Benchmarking knitting Yarn Upsilon model" VERBATIM
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMAND ${benchmark_command} ${benchmark_repeats}
            ${benchmark_directory}/${benchmark_prefix}${target}.csv
            ${DOGEN_KNITTER_COMMAND} --target ${models_dir}/${target}.dia
            ${common_arguments})
        add_dependencies(benchmark_all benchmark_knit_${target})
    endif()
endif()
