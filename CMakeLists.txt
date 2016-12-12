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
option(WITH_DOXYGEN "Build the project documentation" off)
option(WITH_LATEX "Build LaTeX documents. Requires pdflatex and beamer." off)
option(WITH_PROFILING "Build the project with profiling support" off)
option(WITH_COVERALLS "Generate coveralls coverage." off)
option(WITH_MINIMAL_PACKAGING "Package just the main application" off)
option(WITH_JSON_VALIDATION "Adds JSON validation targets. Requires jq." on)

#
# check for dependencies
#

# threads
find_package(Threads REQUIRED)

# boost
# force static linking for all libraries
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME ON)
set(BOOST_ALL_DYN_LINK OFF)
find_package(Boost 1.59 REQUIRED COMPONENTS
    system
    chrono
    serialization
    date_time
    thread
    log
    filesystem
    program_options
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
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        message(STATUS "Profiling enabled...")
    else()
        message(STATUS "Ignoring attempt to enable profiling without debug.")
        set(WITH_PROFILING off)
    endif()
else()
    message(STATUS "Profiling NOT enabled...")
endif()

# coveralls
if(WITH_COVERALLS)
    if(WITH_PROFILING)
        message(STATUS "Coveralls enabled...")
        include(Coveralls)
        coveralls_turn_on_coverage()
    else()
        message(STATUS "Ignoring attempt to enable Coveralls without profiling.")
        set(WITH_COVERALLS off)
    endif()
endif()

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
if(GIT_COMMAND)
    message(STATUS "Found git (${GIT_COMMAND})...")
else()
    message(FATAL_ERROR "git not found.")
endif()

#
# setup pdflatex
#
find_program(PDFLATEX_COMMAND NAMES pdflatex)
if(PDFLATEX_COMMAND)
    message(STATUS "Found pdflatex (${PDFLATEX_COMMAND})...")
else()
    message(STATUS "pdflatex not found, disabling latex documents.")
    set(WITH_LATEX "off")
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
if(JQ_COMMAND)
    message(STATUS "Found jq (${JQ_COMMAND})...")
    add_custom_target(validate_all_json)
    add_custom_target(indent_all_json)
else()
    message(STATUS "jq not found, disabling JSON validation.")
    set(WITH_JSON_VALIDATION "off")
endif()

# hash of the top commit
execute_process(COMMAND ${GIT_COMMAND} rev-list -n 1 HEAD
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    ERROR_VARIABLE git_error
    OUTPUT_VARIABLE CURRENT_GIT_COMMIT
    RESULT_VARIABLE ret_var
    OUTPUT_STRIP_TRAILING_WHITESPACE)

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

# ensure cmake dumps binaries in the right places
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${stage_bin_dir})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${stage_bin_dir})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${stage_bin_dir})

# version info
set(DOGEN_MAJOR_VERSION 0)
set(DOGEN_MINOR_VERSION 94)
set(DOGEN_PATCH_VERSION 0)
set(DOGEN_VERSION "${DOGEN_MAJOR_VERSION}")
set(DOGEN_VERSION "${DOGEN_VERSION}.${DOGEN_MINOR_VERSION}")
set(DOGEN_VERSION "${DOGEN_VERSION}.${DOGEN_PATCH_VERSION}")

# debug
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
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
# knitter setup.
#
list(APPEND CMAKE_PROGRAM_PATH ${stage_bin_dir})
find_program(DOGEN_KNITTER_COMMAND NAMES dogen.knitter)
if (DOGEN_KNITTER_COMMAND)
    execute_process(
        COMMAND ${DOGEN_KNITTER_COMMAND} --version
        COMMAND grep ^Dogen
        COMMAND cut -b15-
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        ERROR_VARIABLE git_error
        OUTPUT_VARIABLE DOGEN_KNITTER_VERSION
        RESULT_VARIABLE ret_var
        OUTPUT_STRIP_TRAILING_WHITESPACE)

      set(knitter "${DOGEN_KNITTER_VERSION} (${DOGEN_KNITTER_COMMAND})")
      message(STATUS "Found dogen knitter: ${knitter}...")
      add_custom_target(knit_all)
else()
    message(STATUS "Dogen Knitter not found, not adding knit targets.")
endif()

#
# Stitcher setup.
#
set(stitcher_binary "${stage_bin_dir}/dogen.stitcher")
find_program(DOGEN_STITCHER_COMMAND NAMES dogen.stitcher)
if (DOGEN_STITCHER_COMMAND)
    execute_process(
        COMMAND ${DOGEN_STITCHER_COMMAND} --version
        COMMAND grep ^Dogen
        COMMAND cut -b15-
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        ERROR_VARIABLE git_error
        OUTPUT_VARIABLE DOGEN_STITCHER_VERSION
        RESULT_VARIABLE ret_var
        OUTPUT_STRIP_TRAILING_WHITESPACE)

      set(stitcher "${DOGEN_STITCHER_VERSION} (${DOGEN_STITCHER_COMMAND})")
      message(STATUS "Found Dogen Stitcher: ${stitcher}...")
      add_custom_target(stitch_all)
else()
    message(STATUS "Dogen Stitcher not found, not adding stitch targets.")
endif()

#
# Tailor setup.
#
set(tailor_binary "${stage_bin_dir}/dogen.tailor")
find_program(DOGEN_TAILOR_COMMAND NAMES dogen.tailor)
if (DOGEN_TAILOR_COMMAND)
    execute_process(
        COMMAND ${DOGEN_TAILOR_COMMAND} --version
        COMMAND grep ^Dogen
        COMMAND cut -b15-
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        ERROR_VARIABLE git_error
        OUTPUT_VARIABLE DOGEN_TAILOR_VERSION
        RESULT_VARIABLE ret_var
        OUTPUT_STRIP_TRAILING_WHITESPACE)

      set(tailor "${DOGEN_TAILOR_VERSION} (${DOGEN_TAILOR_COMMAND})")
      message(STATUS "Found Dogen Tailor: ${tailor}...")
      add_custom_target(tailor_all)
else()
    message(STATUS "Dogen Tailor not found, not adding tailor targets.")
endif()

#
# aggregate targets
#
add_custom_target(run_all_tests)
add_custom_target(run_windows_green_tests)
add_custom_target(rebase)
add_custom_target(diff)
if (DOGEN_KNITTER_COMMAND AND DOGEN_STITCHER_COMMAND)
    add_custom_target(knit_and_stitch)
    add_dependencies(knit_and_stitch knit_all)
    add_dependencies(knit_and_stitch stitch_all)
endif()

#
# target aliases
#
add_custom_target(rat)
add_dependencies(rat run_all_tests)

if (DOGEN_KNITTER_COMMAND AND DOGEN_STITCHER_COMMAND)
    add_custom_target(kas)
    add_custom_target(ka)
    add_custom_target(sa)

    add_dependencies(kas knit_and_stitch)
    add_dependencies(ka knit_all)
    add_dependencies(sa stitch_all)
endif()



#
# include all sub directories
#
add_subdirectory(${CMAKE_SOURCE_DIR}/build)
add_subdirectory(${CMAKE_SOURCE_DIR}/data)
add_subdirectory(${CMAKE_SOURCE_DIR}/doc)
add_subdirectory(${CMAKE_SOURCE_DIR}/test_data)
add_subdirectory(${CMAKE_SOURCE_DIR}/projects)

#
# dependencies for aggregate targets
#
add_dependencies(rebase rebase_test_models rebase_dataset)
add_dependencies(diff diff_test_models diff_dataset)
