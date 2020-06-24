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
cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

# Log CMake version. Useful for debugging CMake problems.
message(STATUS "CMake Version: ${CMAKE_VERSION}")

# ctest support
enable_testing()

#
# Check environment
#
if (DEFINED ENV{DOGEN_PROJECTS_DIRECTORY})
    message(STATUS
        "DOGEN_PROJECTS_DIRECTORY=$ENV{DOGEN_PROJECTS_DIRECTORY}")
else()
    #
    # If the user did not set the projects directory for dogen, we
    # default it to the well-known projects directory. In truth, the
    # handling of the projects directory is a bit messy: it must be
    # set externally for cases such as running tests for coverage
    # because we do not go via CMake. At the same time, we do not want
    # users to have to deal with setting the variable if all they want
    # to do is build dogen from git - they may not even want to run
    # the system tests, so it seems a bit excessive to ask them to
    # figure out how to set it. Due to, this we have this defaulting
    # here.
    #
    set(ENV{DOGEN_PROJECTS_DIRECTORY} "${CMAKE_SOURCE_DIR}/projects")
    message(STATUS
        "DOGEN_PROJECTS_DIRECTORY=$ENV{DOGEN_PROJECTS_DIRECTORY} (default)")
endif()

#
# C++ Reference Model for system tests.
#
if (DEFINED ENV{CPP_REF_IMPL_PROJECTS_DIRECTORY})
    message(STATUS
        "CPP_REF_IMPL_PROJECTS_DIRECTORY=$ENV{CPP_REF_IMPL_PROJECTS_DIRECTORY}")
    add_compile_definitions(ENABLE_CPP_REF_IMPL_TESTS)
else()
    message(STATUS
        "CPP_REF_IMPL_PROJECTS_DIRECTORY env variable not defined, disabling reference implementation tests.")
endif()

#
# C# Reference Model for system tests.
#
if (DEFINED ENV{CSHARP_REF_IMPL_PROJECTS_DIRECTORY})
    message(STATUS
        "CSHARP_REF_IMPL_PROJECTS_DIRECTORY=$ENV{CSHARP_REF_IMPL_PROJECTS_DIRECTORY}")
    add_compile_definitions(ENABLE_CSHARP_REF_IMPL_TESTS)
else()
    message(STATUS
        "CSHARP_REF_IMPL_PROJECTS_DIRECTORY env variable not defined, disabling reference implementation tests.")
endif()

#
# Setup CCache
#
find_program(CCACHE_PROGRAM ccache)
if (CCACHE_PROGRAM)
    message(STATUS "Found CCache (${CCACHE_PROGRAM})...")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")

    execute_process(COMMAND ${CCACHE_PROGRAM} --max-size=10G
        ${CCACHE_PROGRAM} --show-stats
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
else()
    message(STATUS "CCache NOT found.")
endif()

project(DOGEN LANGUAGES CXX VERSION 1.0.26)

#
# add our own modules
#
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/build/cmake)

#
# options
#
option(WITH_DOXYGEN "Build the project documentation." off)
option(WITH_LATEX "Build LaTeX documents. Requires pdflatex and beamer." off)
option(WITH_MINIMAL_PACKAGING "Package just the main application" off)
option(WITH_JSON_VALIDATION "Adds JSON validation targets. Requires jq." on)
option(WITH_BENCHMARKS "Adds targets for running benchmarks." on)
option(WITH_BOOST_TEST_REPORTING "Create boost test reports." off)
option(WITH_RELATIONAL_SUPPORT "Add support for relational data." off)
option(WITH_FULL_GENERATION "Generate all facets for all models.." off)
option(WITH_PROFILING "Generate profiling information for code coverage.." off)

#
# check for dependencies
#

# threads
find_package(Threads REQUIRED)

# boost. Force static linking for all libraries
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME ON)
set(BOOST_ALL_DYN_LINK OFF)

# Note: it is possible to build with older versions of boost, but
# these require patches.
find_package(Boost 1.61 REQUIRED COMPONENTS
    system
    serialization
    date_time
    log
    thread
    filesystem
    program_options
    unit_test_framework
    regex
    chrono
    atomic
    )

if (Boost_FOUND)
    include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
endif()

# iconv - required by libxml
find_package(Iconv REQUIRED)
if (ICONV_FOUND)
    include_directories(SYSTEM ${ICONV_INCLUDE_DIR})
    set(LIBS ${LIBS} ${ICONV_LIBRARIES})
endif()

# libxml
find_package(LibXml2 REQUIRED)
if (LIBXML2_FOUND)
    include_directories(SYSTEM ${LIBXML2_INCLUDE_DIR})
    set(LIBS ${LIBS} ${LIBXML2_LIBRARY_DIR})
endif()

find_package(ZLIB REQUIRED)
if (ZLIB_FOUND)
    message(STATUS "Found ZLib...")
    include_directories(SYSTEM ${ZLIB_INCLUDE_DIR})
    set(LIBS ${LIBS} ${ZLIB_LIBRARY_DIR})
endif()

find_package(DTL REQUIRED)
if (DTL_FOUND)
    message(STATUS "Found DTL...")
endif()

# rapidjson
find_package(RapidJSON)
if (RAPIDJSON_FOUND)
    message(STATUS "Found RapidJSON...")
    include_directories(SYSTEM ${RAPIDJSON_INCLUDEDIR})
else()
    message(STATUS "RapidJson not found.")
endif()

# packaging type
if (WITH_MINIMAL_PACKAGING)
    message(STATUS "Packaging just the main application")
else()
    message(STATUS "Packaging everything main application")
endif()

# profiling
if(WITH_PROFILING)
    if(CMAKE_BUILD_TYPE MATCHES Debug)
        message(STATUS "Profiling enabled...")
    else()
        message(STATUS "Ignoring attempt to enable profiling without debug...")
        set(WITH_PROFILING off)
    endif()
else()
    message(STATUS "Profiling NOT enabled...")
endif()

#
# Test models
#
set(all_dia_test_models "")
file(GLOB_RECURSE all_dia_test_models ABSOLUTE
    "${CMAKE_SOURCE_DIR}/test_data/external.dia/input/*.dia")

#
# setup pdflatex
#
find_program(PDFLATEX_COMMAND NAMES pdflatex)
if (PDFLATEX_COMMAND)
    message(STATUS "Found pdflatex (${PDFLATEX_COMMAND})...")
else()
    message(STATUS "pdflatex not found, disabling latex documents.")
    set(WITH_LATEX "off")
endif()

if (WITH_LATEX)
    message(STATUS "Building latex documents...")
else()
    message(STATUS "NOT building latex documents...")
endif()

#
# setup jq, for JSON validation.
#
find_program(JQ_COMMAND NAMES jq)
if (JQ_COMMAND)
    message(STATUS "Found jq (${JQ_COMMAND})...")
    add_custom_target(validate_all_json)
    add_custom_target(indent_all_json)
else()
    message(STATUS "jq not found, disabling JSON validation.")
    set(WITH_JSON_VALIDATION "off")
endif()

#
# useful vars
#

# site (for ctest)
site_name(DOGEN_SITE)

# setup staging directory
set(stage_dir ${PROJECT_BINARY_DIR}/stage)
if(NOT EXISTS "${stage_dir}")
    make_directory("${stage_dir}")
endif()

set(stage_bin_dir ${stage_dir}/bin)
if(NOT EXISTS "${stage_bin_dir}")
    make_directory("${stage_bin_dir}")
endif()

set(stage_pkg_dir ${stage_dir}/pkg)
if(NOT EXISTS "${stage_pkg_dir}")
    make_directory("${stage_pkg_dir}")
endif()
set(DOGEN_PACKAGE_DIR "${stage_pkg_dir}")

set(stage_lib_dir ${stage_dir}/lib)
if(NOT EXISTS "${stage_lib_dir}")
    make_directory("${stage_lib_dir}")
endif()

set(stage_inc_dir ${stage_dir}/include)
if(NOT EXISTS "${stage_inc_dir}")
    make_directory("${stage_inc_dir}")
endif()

set(stage_test_data_dir ${stage_dir}/test_data)
if(NOT EXISTS "${stage_test_data_dir}")
    make_directory("${stage_test_data_dir}")
endif()

set(stage_doc_dir ${stage_dir}/doc)
if(NOT EXISTS "${stage_doc_dir}")
    make_directory("${stage_doc_dir}")
endif()

set(stage_doxygen_dir ${stage_dir}/doxygen)
if(NOT EXISTS "${stage_doxygen_dir}")
    make_directory("${stage_doxygen_dir}")
endif()

#
# ensure cmake dumps binaries in the right places
#
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${stage_bin_dir})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${stage_bin_dir})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${stage_bin_dir})

if(MSVC)
    foreach(CONFIGURATION_TYPE ${CMAKE_CONFIGURATION_TYPES})
        string(TOUPPER ${CONFIGURATION_TYPE} CONFIGURATION_TYPE)
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${CONFIGURATION_TYPE} ${stage_bin_dir})
        set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${CONFIGURATION_TYPE} ${stage_bin_dir})
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CONFIGURATION_TYPE} ${stage_bin_dir})
    endforeach()
endif()

#
# Handle build information
#
set(WITH_BUILD_INFO ON)
set(DOGEN_BUILD_INFO "")

if (NOT DEFINED ENV{BUILD_PROVIDER})
    set(WITH_BUILD_INFO OFF)
endif()

if (NOT DEFINED ENV{BUILD_COMMIT})
    set(WITH_BUILD_INFO OFF)
endif()

if (NOT DEFINED ENV{BUILD_NUMBER})
    set(WITH_BUILD_INFO OFF)
endif()

if (NOT DEFINED ENV{BUILD_TIMESTAMP})
    set(WITH_BUILD_INFO OFF)
endif()

if (WITH_BUILD_INFO)
    set(DOGEN_BUILD_INFO "Build: Provider = '$ENV{BUILD_PROVIDER}'")
    set(DOGEN_BUILD_INFO "${DOGEN_BUILD_INFO} Number = '$ENV{BUILD_NUMBER}'")
    set(DOGEN_BUILD_INFO "${DOGEN_BUILD_INFO} Commit = '$ENV{BUILD_COMMIT}'")
    set(DOGEN_BUILD_INFO "${DOGEN_BUILD_INFO} Timestamp = '$ENV{BUILD_TIMESTAMP}'")
    message(STATUS "${DOGEN_BUILD_INFO}")
else()
    message(STATUS "Not adding build info.")
endif()

#
# Build type
#
if(CMAKE_BUILD_TYPE MATCHES Debug)
    message(STATUS "Configuring in DEBUG mode")
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    if (UNIX)
        set(CMAKE_INSTALL_DO_STRIP TRUE)
    endif()
    message(STATUS "Configuring in RELEASE mode")
elseif(CMAKE_BUILD_TYPE MATCHES RelWithDebInfo)
    message(STATUS "Configuring in RELEASE mode WITH symbols")
elseif(CMAKE_BUILD_TYPE MATCHES MinRelSize)
    if (UNIX)
        set(CMAKE_INSTALL_DO_STRIP TRUE)
    endif()
    message(STATUS "Configuring in RELEASE mode with minimised size")
else()
    message(STATUS "Unrecognized build type - will use cmake defaults")
endif()
message(STATUS "Product version: ${DOGEN_VERSION}")

#
# doxygen
#
if (WITH_DOXYGEN)
    find_package(Doxygen)

    if(DOXYGEN_FOUND)
        message(STATUS "Doxygen enabled - generating API documentation")
        # input directories (used in doxygen template)
        set(DOGEN_CPP_CODE_DIR ${CMAKE_SOURCE_DIR}/projects)
        set(DOGEN_DOX_DIR ${stage_doxygen_dir}/dox)

        # output directory (used in doxygen template)
        set(DOGEN_DOXYGEN_DIR ${stage_doxygen_dir})

        # input file
        set(doxy_file ${stage_doxygen_dir}/dogen.doxy)
        add_custom_target(doxy ALL
            COMMENT "Generating doxygen documentation."
            COMMAND rm -rf ${stage_doxygen_dir}/html
            COMMAND ${DOXYGEN_EXECUTABLE} ${doxy_file}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen" VERBATIM)

        install(
            DIRECTORY ${stage_doxygen_dir}/html/
            DESTINATION share/doc/
            COMPONENT documentation
            )
    else()
        message(STATUS "Could not find Doxygen.")
    endif()
else()
    message(STATUS "Doxygen not enabled (set WITH_DOXYGEN=on).")
endif()

#
# Analysis and formatting tools
#
find_package(ClangTools)
if (CLANG_FORMAT_FOUND)
    message(STATUS "Found clang-format (${CLANG_FORMAT_BIN}).")
else()
    message(STATUS "Could not find clang-format.")
endif()

if (CLANG_TIDY_FOUND)
    message(STATUS "Found clang-tidy (${CLANG_FORMAT_BIN}).")
else()
    message(STATUS "Could not find clang-tidy.")
endif()

find_package(cppcheck)
if (CPPCHECK_FOUND)
    message(STATUS "Found cppcheck (${CPPCHECK_EXECUTABLE}).")
else()
    message(STATUS "Could not find cppcheck.")
endif()

#
# ODB
#
if (WITH_RELATIONAL_SUPPORT)
    set(DOGEN_HAVE_RELATIONAL_MODEL "1")
    find_package(odb COMPONENTS libodb boost pgsql sqlite REQUIRED)
    if (odb_FOUND)
        message(STATUS "Found ODB Libraries...")
        set(ODB_LIBODB_FOUND ${odb_FOUND})
    else()
        message(FATAL_ERROR "ODB Libraries NOT Found.")
    endif()

    find_program(ODB_EXECUTABLE NAMES odb)

    # sqlite
    find_package(sqlite3 REQUIRED)
    if (sqlite3_FOUND)
        include_directories(SYSTEM ${sqlite3_INCLUDE_DIR})
        set(LIBS ${LIBS} ${sqlite3_LIBRARY_DIR})
    endif()

    #
    # OpenSSL
    #
    find_package(OpenSSL REQUIRED)

    if (ODB_EXECUTABLE)
        message(STATUS "Found ODB Compiler... (${ODB_EXECUTABLE})")
        add_custom_target(odb_all)
        add_custom_target(oa)
        add_dependencies(oa odb_all)
    else()
        message(STATUS "ODB Compiler NOT Found.")
    endif()
endif()

#
# Determine if MSVC-specific libraries are required.
#
set(USE_MSVC_LIBS OFF)
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    if ("${CMAKE_CXX_SIMULATE_ID}" STREQUAL "MSVC")
        set(USE_MSVC_LIBS ON)
    endif ()
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(USE_MSVC_LIBS ON)
endif ()
message(STATUS "MSVC-specific libraries: ${USE_MSVC_LIBS}")

#
# Dogen
#

# FIXME: this looks strange!
find_package(Dogen REQUIRED)

#
# aggregate targets and their aliases
#
add_custom_target(run_all_tests)
add_custom_target(rat)
add_dependencies(rat run_all_tests)

add_custom_target(rebase)
add_custom_target(diff)

if (DOGEN_CLI_EXECUTABLE)
    add_custom_target(generate_all_dia)
    add_custom_target(generate_all_json)
    add_custom_target(gad)
    add_dependencies(gad generate_all_dia)
    add_custom_target(gaj)
    add_dependencies(gaj generate_all_json)

    add_custom_target(convert_all)
    add_custom_target(ca)
    add_dependencies(ca convert_all)

    add_custom_target(convert_all_json)
    add_custom_target(caj)
    add_dependencies(caj convert_all_json)
    add_dependencies(ca caj)

    add_custom_target(convert_all_org)
    add_custom_target(cao)
    add_dependencies(cao convert_all_org)
    add_dependencies(ca cao)

    #
    # Options to use for all Dogen invocations
    #

    # model processing options
    set(DOGEN_PROCESSING_OPTIONS "")
    # uncomment the next line if you need dry runs.
    # set(DOGEN_PROCESSING_OPTIONS ${DOGEN_PROCESSING_OPTIONS}
    #    --dry-run-mode-enabled)
    # set(DOGEN_PROCESSING_OPTIONS ${DOGEN_PROCESSING_OPTIONS}
    #     --activity-timestamp "2020-01-18T12:45:33")

    message(STATUS "Full generation: ${WITH_FULL_GENERATION}")
    if (WITH_FULL_GENERATION)
        set(profile "dogen.profiles.base.test_all_facets")
        set(DOGEN_PROCESSING_OPTIONS ${DOGEN_PROCESSING_OPTIONS}
            --variability-override masd.variability.profile,${profile})
    endif()

    # uncomment to enable logging.
    set(DOGEN_LOGGING_OPTIONS "")
    # set(DOGEN_LOG_LEVEL "trace")
    # set(DOGEN_LOGGING_OPTIONS --log-enabled --log-level ${DOGEN_LOG_LEVEL})

    set(DOGEN_TRACING_OPTIONS "")
    # uncomment to enable tracing.
    # set(DOGEN_TRACING_OPTIONS ${DOGEN_TRACING_OPTIONS} --tracing-enabled)
    # set(DOGEN_TRACING_OPTIONS ${DOGEN_TRACING_OPTIONS} --tracing-level detail)
    # set(DOGEN_TRACING_OPTIONS ${DOGEN_TRACING_OPTIONS} --tracing-format org-mode)
    # set(DOGEN_TRACING_OPTIONS ${DOGEN_TRACING_OPTIONS} --tracing-guids-enabled)
    # change to file or relational as required.
    # set(DOGEN_TRACING_OPTIONS ${DOGEN_TRACING_OPTIONS} --tracing-backend file)
    # set(DOGEN_TRACING_OPTIONS ${DOGEN_TRACING_OPTIONS}
    #    --tracing-filter-regex .*text.transforms.model_to_text_chain.*)

    set(DOGEN_DATABASE_OPTIONS "")
    # uncomment to enable database tracing.
    # set(DOGEN_DATABASE_OPTIONS ${DOGEN_DATABASE_OPTIONS} --database-host localhost)
    # set(DOGEN_DATABASE_OPTIONS ${DOGEN_DATABASE_OPTIONS} --database-port 5433)
    # set(DOGEN_DATABASE_OPTIONS ${DOGEN_DATABASE_OPTIONS} --database-name musseque)
    # set(DOGEN_DATABASE_OPTIONS ${DOGEN_DATABASE_OPTIONS} --database-user build)
    # set(DOGEN_DATABASE_OPTIONS ${DOGEN_DATABASE_OPTIONS} --database-password build)
    # uncomment out if schema regeneration is required.
    # WARNING: all data will be deleted.
    # set(DOGEN_DATABASE_OPTIONS ${DOGEN_DATABASE_OPTIONS} --database-generate-schema)

    set(DOGEN_DIFFING_OPTIONS "")
    # uncomment to enable diffing
    # set(DOGEN_DIFFING_OPTIONS ${DOGEN_DIFFING_OPTIONS} --diffing-enabled)
    # set(DOGEN_DIFFING_OPTIONS ${DOGEN_DIFFING_OPTIONS}
    #    --diffing-destination console)

    set(DOGEN_REPORTING_OPTIONS "")
    # uncomment to enable reporting
    #set(DOGEN_REPORTING_OPTIONS ${DOGEN_REPORTING_OPTIONS} --reporting-enabled)
    # set(DOGEN_REPORTING_OPTIONS ${DOGEN_REPORTING_OPTIONS}
    #    --reporting-style org-mode )

    set(DOGEN_COMMON_OPTIONS ${DOGEN_PROCESSING_OPTIONS}
        ${DOGEN_LOGGING_OPTIONS} ${DOGEN_TRACING_OPTIONS}
        ${DOGEN_DATABASE_OPTIONS} ${DOGEN_DIFFING_OPTIONS}
        ${DOGEN_REPORTING_OPTIONS})

    # uncomment the next line if you require compatibility support
    # set(DOGEN_COMMON_OPTIONS ${DOGEN_COMMON_OPTIONS} --compatibility-mode)

    #
    # Options for code generation only
    #
    set(projects_dir "${CMAKE_SOURCE_DIR}/projects")
    set(DOGEN_GENERATION_OPTIONS --output-directory ${projects_dir}/)
endif()

if (WITH_JSON_VALIDATION)
    add_custom_target(iaj)
    add_custom_target(vaj)

    add_dependencies(iaj indent_all_json)
    add_dependencies(vaj indent_all_json)
endif()

#
# Benchmarks
#
if(NOT UNIX)
    set(WITH_BENCHMARKS "off")
endif()

if(WITH_BENCHMARKS)
    set(benchmark_repeats "20")
    set(benchmark_command
        "${CMAKE_SOURCE_DIR}/build/scripts/benchmark.linux.sh")
    set(benchmark_directory "${stage_test_data_dir}/benchmarks/actual")
    set(benchmark_prefix "")
    if(NOT EXISTS "${benchmark_directory}")
        make_directory("${benchmark_directory}")
    endif()

    add_custom_target(benchmark_stats)
    add_custom_target(benchmark_all)
    add_custom_target(ba)
    add_dependencies(ba benchmark_all)

    add_custom_target(benchmark_dia)
    add_custom_target(benchmark_json)
    add_dependencies(benchmark_all benchmark_dia)
endif()

#
# include all sub directories
#
add_subdirectory(${CMAKE_SOURCE_DIR}/build)
add_subdirectory(${CMAKE_SOURCE_DIR}/share)
add_subdirectory(${CMAKE_SOURCE_DIR}/doc)
add_subdirectory(${CMAKE_SOURCE_DIR}/test_data)
add_subdirectory(${CMAKE_SOURCE_DIR}/projects)
