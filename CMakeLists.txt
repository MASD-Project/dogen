# -*- mode: cmake; tab-width: 4; indent-tabs-mode: nil -*-
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
cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

# ctest support
enable_testing()

project(dogen)

# conan support
if(EXISTS "${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
    message(STATUS "Setting up Conan support.")
    include("${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
    CONAN_BASIC_SETUP()
else()
    message(STATUS "Conan build file not found, skipping include")
endif()

# add our own modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/build/cmake)

# options
option(WITH_DEBUG "Build the project with debug symbols" off)
option(WITH_DOXYGEN "Build the project documentation" off)
option(WITH_LATEX "Build all LaTeX documents. Requires pdflatex and beamer." off)
option(WITH_PROFILING "Build the project with profiling support" off)
option(WITH_MINIMAL_PACKAGING "Package just the main application" off)
option(WITH_JSON_VALIDATION "Adds JSON validation targets. Requires jq." on)

#
# check for dependencies
#

# threads
find_package(Threads REQUIRED)

# boost
if (DEFINED ENV{PFH_LOCATION})
    set(BOOST_ROOT "$ENV{PFH_LOCATION}")
    set(Boost_NO_SYSTEM_PATHS "ON")
    include_directories(SYSTEM $ENV{PFH_LOCATION}/include)
endif()

add_definitions(-DBOOST_ALL_DYN_LINK)
find_package(Boost 1.59 REQUIRED COMPONENTS
    system
    chrono
    serialization
    date_time
    thread
    log
    filesystem
    program_options
    iostreams
    )

if(Boost_FOUND)
    include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
endif()

# iconv - required by libxml
find_package(Iconv REQUIRED)
if(ICONV_FOUND)
    include_directories(SYSTEM ${ICONV_INCLUDE_DIR})
    set(LIBS ${LIBS} ${ICONV_LIBRARIES})
endif()

# libxml
find_package(LibXml2 REQUIRED)
if(LIBXML2_FOUND)
    include_directories(SYSTEM ${LIBXML2_INCLUDE_DIR})
    set(LIBS ${LIBS} ${LIBXML2_LIBRARY_DIR})
endif()

# odb
# find_package(ODB)
# if(ODB_FOUND)
#    message(STATUS "Found odb...")
#    include_directories(SYSTEM ${ODB_INCLUDE_DIR})
#    set(LIBS ${LIBS} ${LIBXML2_LIBRARY_DIR})
# else()
    message(STATUS "odb not found.")
# endif()

# packaging type
if(WITH_MINIMAL_PACKAGING)
    message(STATUS "Packaging just the main application")
else()
    message(STATUS "Packaging everything main application")
endif()

# profiling
if(WITH_PROFILING)
    if(WITH_DEBUG)
        message(STATUS "Profiling enabled...")
    else()
        message(STATUS "Ignoring attempt to enable profiling without debug...")
        set(WITH_PROFILING off)
    endif()
else()
    message(STATUS "Profiling NOT enabled...")
endif()

# WinSock (for database)
# if (WIN32)
#     find_library(WSOCK_LIB NAMES wsock32 DOC "The winsock library")
#     if(WSOCK_LIB)
#         list(APPEND CMAKE_REQUIRED_LIBRARIES wsock32)
#     else()
#         message(FATAL_ERROR "winsock not found.")
#     endif()

#     find_library(WSOCK2_LIB NAMES ws2_32 DOC "The winsock 2 library")
#     if(WSOCK2_LIB)
#         list(APPEND CMAKE_REQUIRED_LIBRARIES ws2_32)
#     else()
#         message(FATAL_ERROR "winsock2 not found.")
#     endif()

#     find_library(MSWSOCK_LIB NAMES mswsock DOC "The winsock 2 library")
#     if(MSWSOCK_LIB)
#         list(APPEND CMAKE_REQUIRED_LIBRARIES mswsock)
#     else()
#         message(FATAL_ERROR "mswsock not found.")
#     endif()
# endif()

#
# Test models
#
set(all_dia_test_models "")
file(GLOB_RECURSE all_dia_test_models ABSOLUTE
    "${CMAKE_SOURCE_DIR}/test_data/yarn.dia/input/*.dia")

#
# setup git
#
find_program(GIT_COMMAND NAMES git)
if(NOT DEFINED GIT_COMMAND)
    message(FATAL_ERROR "git not found.")
endif()
message(STATUS "Found git (${GIT_COMMAND})...")

#
# setup pdflatex
#
find_program(PDFLATEX_COMMAND NAMES pdflatex)
if(NOT DEFINED PDFLATEX_COMMAND)
    message(STATUS "pdflatex not found, disabling latex documents.")
    set(WITH_LATEX "off")
else()
    message(STATUS "Found pdflatex (${PDFLATEX_COMMAND})...")
endif()

if(WITH_LATEX)
    message(STATUS "Building latex documents...")
else()
    message(STATUS "NOT building latex documents...")
endif()

#
# setup jq, for JSON validation.
#
find_program(JQ_COMMAND NAMES jq)
if(NOT DEFINED JQ_COMMAND)
    message(STATUS "jq not found, disabling JSON validation.")
    set(WITH_JSON_VALIDATION "off")
else()
    message(STATUS "Found jq (${JQ_COMMAND})...")
    add_custom_target(validate_all_json)
endif()

# hash of the top commit
execute_process(COMMAND ${GIT_COMMAND} rev-list -n 1 HEAD
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    ERROR_VARIABLE git_error
    OUTPUT_VARIABLE CURRENT_GIT_COMMIT
    RESULT_VARIABLE ret_var
    OUTPUT_STRIP_TRAILING_WHITESPACE)

# commit count
execute_process(
    COMMAND ${GIT_COMMAND} rev-list master
    COMMAND wc -l
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    ERROR_VARIABLE git_error
    OUTPUT_VARIABLE GIT_COMMIT_COUNT
    RESULT_VARIABLE ret_var
    OUTPUT_STRIP_TRAILING_WHITESPACE)
string(STRIP ${GIT_COMMIT_COUNT} GIT_COMMIT_COUNT)

#
# useful vars
#

# site (for ctest)
site_name(DOGEN_SITE)

# staging directory
set(stage_dir ${PROJECT_BINARY_DIR}/stage)
set(stage_bin_dir ${stage_dir}/bin)
set(stage_pkg_dir ${stage_dir}/pkg)
set(stage_lib_dir ${stage_dir}/lib)
set(stage_inc_dir ${stage_dir}/include)
set(stage_test_data_dir ${stage_dir}/test_data)
set(stage_doc_dir ${stage_dir}/doc)
set(stage_doxygen_dir ${stage_dir}/doxygen)

# ensure cmake dumps binaries in the right places
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${stage_bin_dir})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${stage_bin_dir})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${stage_bin_dir})

# version info
set(DOGEN_MAJOR_VERSION 0)
set(DOGEN_MINOR_VERSION 79)
set(DOGEN_PATCH_VERSION 4275)
set(DOGEN_VERSION "${DOGEN_MAJOR_VERSION}")
set(DOGEN_VERSION "${DOGEN_VERSION}.${DOGEN_MINOR_VERSION}")
set(DOGEN_VERSION "${DOGEN_VERSION}.${DOGEN_PATCH_VERSION}")

# debug
if(WITH_DEBUG)
    message(STATUS "Building WITH DEBUG symbols...")
    set(DOGEN_VERSION "${DOGEN_VERSION}d")
else()
    message(STATUS "Building WITHOUT DEBUG symbols...")
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
            DESTINATION share/doc/${DOGEN_VERSION}/
            COMPONENT documentation
            )
    else()
        message(STATUS "Could not find Doxygen.")
    endif()
else()
    message(STATUS "Doxygen not enabled (set WITH_DOXYGEN=on).")
endif()

#
# Top-level knitter target.
#
add_custom_target(knit_all)
set(use_latest_knitter FALSE)
if(use_latest_knitter)
    add_dependencies(knit_all knitter)
endif()

set(knitter_binary "${stage_bin_dir}/dogen.knitter")
set(knitter_version "")
execute_process(
    COMMAND ${knitter_binary} --version
    COMMAND head -n1
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    OUTPUT_VARIABLE knitter_version
    RESULT_VARIABLE ret_var
    OUTPUT_STRIP_TRAILING_WHITESPACE)

message(STATUS "Using: ${knitter_version}")

#
# Top-level stitcher target.
#
add_custom_target(stitch_all)
set(use_latest_stitcher FALSE)
if(use_latest_stitcher)
    add_dependencies(stitch_all stitcher)
endif()

set(stitcher_binary "${stage_bin_dir}/dogen.stitcher")
set(stitcher_version "")
execute_process(
    COMMAND ${stitcher_binary} --version
    COMMAND head -n1
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    OUTPUT_VARIABLE stitcher_version
    RESULT_VARIABLE ret_var
    OUTPUT_STRIP_TRAILING_WHITESPACE)

message(STATUS "Using: ${stitcher_version}")

#
# aggregate targets
#
add_custom_target(run_all_specs)
add_custom_target(rebase)
add_custom_target(diff)
add_custom_target(knit_and_stitch)
add_dependencies(knit_and_stitch knit_all)
add_dependencies(knit_and_stitch stitch_all)

#
# include all sub directories
#
add_subdirectory(${CMAKE_SOURCE_DIR}/build)
add_subdirectory(${CMAKE_SOURCE_DIR}/data)
add_subdirectory(${CMAKE_SOURCE_DIR}/doc)
add_subdirectory(${CMAKE_SOURCE_DIR}/test_data)
add_subdirectory(${CMAKE_SOURCE_DIR}/projects)
add_subdirectory(${CMAKE_SOURCE_DIR}/diagrams)

#
# dependencies for aggregate targets
#
add_dependencies(rebase rebase_test_models rebase_dataset)
add_dependencies(diff diff_test_models diff_dataset)
