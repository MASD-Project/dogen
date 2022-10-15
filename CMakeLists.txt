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
cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

#
# vcpkg
#
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
set(X_VCPKG_APPLOCAL_DEPS_INSTALL ON)
set(CMAKE_TOOLCHAIN_FILE
    ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake
    CACHE STRING "Vcpkg toolchain file")

# Log CMake version. Useful for debugging CMake problems.
message(STATUS "CMake Version: ${CMAKE_VERSION}")

# ctest support
enable_testing()

# Suppress warning: "The practice of declaring the Bind placeholders
add_definitions(-DBOOST_BIND_GLOBAL_PLACEHOLDERS)

#
# Check environment
#
if (DEFINED ENV{DOGEN_PROJECTS_DIRECTORY})
    message(STATUS
        "DOGEN_PROJECTS_DIRECTORY=$ENV{DOGEN_PROJECTS_DIRECTORY}")
else()
    #
    # If the user did not set the projects directory for dogen, we default it to
    # the well-known projects directory. In truth, the handling of the projects
    # directory is a bit messy: it must be set externally for cases such as
    # running tests for coverage because we do not go via CMake. At the same
    # time, we do not want users to have to deal with setting the variable if
    # all they want to do is build dogen from git - they may not even want to
    # run the system tests, so it seems a bit excessive to ask them to figure
    # out how to set it. Due to, this we have this defaulting here.
    #
    set(ENV{DOGEN_PROJECTS_DIRECTORY} "${CMAKE_SOURCE_DIR}/projects")
    message(STATUS
        "DOGEN_PROJECTS_DIRECTORY=$ENV{DOGEN_PROJECTS_DIRECTORY} (default)")
endif()

if(NOT EXISTS $ENV{DOGEN_PROJECTS_DIRECTORY})
    message(FATAL_ERROR "DOGEN_PROJECTS_DIRECTORY not found.")
endif()

#
# Frozen projects directory.
#
# Frozen contains a stale copy of Dogen, snapshotted before we removed the JSON
# and Dia models.
#
if (DEFINED ENV{FROZEN_PROJECTS_DIRECTORY})
    message(STATUS
        "FROZEN_PROJECTS_DIRECTORY=$ENV{FROZEN_PROJECTS_DIRECTORY}")
    if(NOT EXISTS $ENV{FROZEN_PROJECTS_DIRECTORY})
        message(FATAL_ERROR "FROZEN_PROJECTS_DIRECTORY not found.")
    endif()
    add_compile_definitions(ENABLE_FROZEN_TESTS)
else()
    message(STATUS
        "FROZEN_PROJECTS_DIRECTORY env variable not defined, disabling Frozen tests.")
endif()

#
# C++ Reference Model for system tests.
#
if (DEFINED ENV{CPP_REF_IMPL_PROJECTS_DIRECTORY})
    message(STATUS
        "CPP_REF_IMPL_PROJECTS_DIRECTORY=$ENV{CPP_REF_IMPL_PROJECTS_DIRECTORY}")
    if(NOT EXISTS $ENV{CPP_REF_IMPL_PROJECTS_DIRECTORY})
        message(FATAL_ERROR "CPP_REF_IMPL_PROJECTS_DIRECTORY not found.")
    endif()
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
    if(NOT EXISTS $ENV{CSHARP_REF_IMPL_PROJECTS_DIRECTORY})
        message(FATAL_ERROR "CSHARP_REF_IMPL_PROJECTS_DIRECTORY not found.")
    endif()
    add_compile_definitions(ENABLE_CSHARP_REF_IMPL_TESTS)
else()
    message(STATUS
        "CSHARP_REF_IMPL_PROJECTS_DIRECTORY env variable not defined, disabling reference implementation tests.")
endif()

#
# Setup CCache
#
find_program(CCACHE_PROGRAM sccache)
if (CCACHE_PROGRAM)
    message(STATUS "Found SCCache (${CCACHE_PROGRAM})...")
    set(CMAKE_C_COMPILER_LAUNCHER "${CCACHE_PROGRAM}" CACHE STRING "")
    set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}" CACHE STRING "")
else()
    message(STATUS "SCCache NOT found.")
endif()

project(DOGEN VERSION 1.0.32 LANGUAGES CXX
    DESCRIPTION "Code generator for Model Assisted Software Development.")

#
# add our own modules
#
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/build/cmake)

#
# options
#
option(WITH_PLANTUML "Build UML representation." ON)
option(WITH_DOXYGEN "Build the project documentation." OFF)
option(WITH_LATEX "Build LaTeX documents. Requires pdflatex and beamer." OFF)
option(WITH_MINIMAL_PACKAGING "Package just the main application" ON)
option(WITH_FULL_GENERATION "Generate all facets for all models." OFF)
option(WITH_PROFILING "Generate profiling information for code coverage." OFF)

#
# check for dependencies
#

# threads
find_package(Threads REQUIRED)

# boost.
set(Boost_USE_MULTITHREADED ON)

# Note: it is possible to build with older versions of boost, but
# these require patches.
find_package(Boost 1.80 REQUIRED COMPONENTS
    date_time
    exception
    filesystem
    log
    program_options
    serialization
    unit_test_framework)

# Other packages
find_package(LibXml2 CONFIG REQUIRED)
find_package(ZLIB REQUIRED)
find_package(DTL REQUIRED)

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

set(stage_doxygen_dir ${stage_doc_dir}/doxygen)
if(NOT EXISTS "${stage_doxygen_dir}")
    make_directory("${stage_doxygen_dir}")
endif()

set(stage_modeling_dir ${stage_doc_dir}/modeling)
if(NOT EXISTS "${stage_modeling_dir}")
    make_directory("${stage_modeling_dir}")
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

if (NOT DEFINED ENV{DOGEN_BUILD_PROVIDER})
    set(WITH_BUILD_INFO OFF)
endif()

if (NOT DEFINED ENV{DOGEN_BUILD_COMMIT})
    set(WITH_BUILD_INFO OFF)
endif()

if (NOT DEFINED ENV{DOGEN_BUILD_NUMBER})
    set(WITH_BUILD_INFO OFF)
endif()

if (NOT DEFINED ENV{DOGEN_BUILD_TIMESTAMP})
    set(WITH_BUILD_INFO OFF)
endif()

if (WITH_BUILD_INFO)
    set(DOGEN_BUILD_INFO "Build: Provider = '$ENV{DOGEN_BUILD_PROVIDER}'")
    set(DOGEN_BUILD_INFO "${DOGEN_BUILD_INFO} Number = '$ENV{DOGEN_BUILD_NUMBER}'")
    set(DOGEN_BUILD_INFO "${DOGEN_BUILD_INFO} Commit = '$ENV{DOGEN_BUILD_COMMIT}'")
    set(DOGEN_BUILD_INFO "${DOGEN_BUILD_INFO} Timestamp = '$ENV{DOGEN_BUILD_TIMESTAMP}'")
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
    find_package(Doxygen REQUIRED dot)

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
            COMPONENT documentation)
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
# PlantUML
#
find_program(PLANTUML_PROGRAM plantuml)
if (PLANTUML_PROGRAM)
    message(STATUS "Found PlantUML: ${PLANTUML_PROGRAM}")
    set(WITH_PLANTUML "on")
    set(PLANTUML_ENVIRONMENT "PLANTUML_LIMIT_SIZE=65536")
    set(PLANTUML_OPTIONS -Playout=elk -tsvg)
else()
    message(STATUS "PlantUML not found.")
endif()

#
# Dogen
#

# We need to use the code generator to generate the code generator.
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
    add_custom_target(generate_all_org)
    add_custom_target(gao)
    add_dependencies(gao generate_all_org)

    add_custom_target(convert_all_plantuml)
    add_custom_target(cap)
    add_dependencies(cap convert_all_plantuml)

    add_custom_target(convert_all_org)
    add_custom_target(cao)
    add_dependencies(cao convert_all_org)

    if (WITH_PLANTUML)
        add_custom_target(generate_all_plantuml)
        add_custom_target(gap)
        add_dependencies(gap generate_all_plantuml)
    endif()

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
        message(STATUS "Using profile: ${profile}")

        # need to fix the activity timestamp to the value used in tests.
        set(DOGEN_PROCESSING_OPTIONS ${DOGEN_PROCESSING_OPTIONS}
            --activity-timestamp "2022-10-20 10:20:30")
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
        ${DOGEN_DIFFING_OPTIONS} ${DOGEN_REPORTING_OPTIONS})

    # uncomment the next line if you require compatibility support
    # set(DOGEN_COMMON_OPTIONS ${DOGEN_COMMON_OPTIONS} --compatibility-mode)

    #
    # Options for code generation only
    #
    set(projects_dir "${CMAKE_SOURCE_DIR}/projects")
    set(DOGEN_GENERATION_OPTIONS --output-directory ${projects_dir}/)
endif()

#
# include all sub directories
#
add_subdirectory(${CMAKE_SOURCE_DIR}/build)
add_subdirectory(${CMAKE_SOURCE_DIR}/share)
add_subdirectory(${CMAKE_SOURCE_DIR}/doc)
add_subdirectory(${CMAKE_SOURCE_DIR}/test_data)
add_subdirectory(${CMAKE_SOURCE_DIR}/projects)

#
# Special targets for nightlies. Commit current set of files.
#
add_custom_target(commit_all_changes
    COMMAND git add -A 1>/dev/null
    COMMAND git commit --author="Temporary Author temporary.author@example.com" -m "Generated code."
)
