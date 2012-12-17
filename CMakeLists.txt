# -*- mode: cmake; tab-width: 4; indent-tabs-mode: nil -*-
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
#
# avoid nonsense warning on cygwin
set(CMAKE_LEGACY_CYGWIN_WIN32 0) # Remove when CMake >= 2.8.4 is required

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

# enable ctest support
enable_testing()

# prohibit in-source builds: i.e. users are not allowed to perform
# builds either in the source root directory or in any of its
# sub-directories.
string(REGEX MATCH "^${CMAKE_SOURCE_DIR}" source_build ${CMAKE_BINARY_DIR})
if (source_build)
    message(FATAL_ERROR "Attempting to build in the source directory."
        "Please create a separate build directory and invoke cmake from there.")
endif()

project(dogen)

# add our own modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/build/cmake)

# options
option(WITH_DEBUG "Build the project with debug symbols" off)
option(WITH_PROFILING "Build the project with profiling support" off)

#
# check for dependencies
#

# threads
find_package(Threads REQUIRED)

# boost
set(BOOST_ROOT "$ENV{PFH_LOCATION}")
set(Boost_NO_SYSTEM_PATHS "ON")

find_package(Boost 1.49 REQUIRED COMPONENTS
    system
    chrono
    serialization
    date_time
    thread
    log
    filesystem
    program_options
    )

find_package(LibXml2)

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

# WinSock (for PQXX)
if (WIN32)
    find_library(WSOCK_LIB NAMES wsock32 DOC "The winsock library")
    if(WSOCK_LIB)
        list(APPEND CMAKE_REQUIRED_LIBRARIES wsock32)
    else()
        message(FATAL_ERROR "winsock not found.")
    endif()

    find_library(WSOCK2_LIB NAMES ws2_32 DOC "The winsock 2 library")
    if(WSOCK2_LIB)
        list(APPEND CMAKE_REQUIRED_LIBRARIES ws2_32)
    else()
        message(FATAL_ERROR "winsock2 not found.")
    endif()

    find_library(MSWSOCK_LIB NAMES mswsock DOC "The winsock 2 library")
    if(MSWSOCK_LIB)
        list(APPEND CMAKE_REQUIRED_LIBRARIES mswsock)
    else()
        message(FATAL_ERROR "mswsock not found.")
    endif()
endif()

# database
# find_package(PQXX)
# if(PQXX_FOUND)
#     message(STATUS "Found libpqxx...")
# else()
#     message(FATAL_ERROR "libpqxx not found.")
# endif()

#
# Test models
#
set(all_dia_test_models "")
file(GLOB_RECURSE all_dia_test_models ABSOLUTE
    "${CMAKE_SOURCE_DIR}/test_data/dia_sml/input/*.dia")

#
# setup git
#
find_program(CTEST_GIT_COMMAND NAMES git)
if(NOT DEFINED CTEST_GIT_COMMAND)
    message(FATAL_ERROR "git not found.")
endif()
message(STATUS "Found git (${CTEST_GIT_COMMAND})...")

# hash of the top commit
execute_process(COMMAND ${CTEST_GIT_COMMAND} rev-list -n 1 HEAD
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    ERROR_VARIABLE git_error
    OUTPUT_VARIABLE CURRENT_GIT_COMMIT
    RESULT_VARIABLE ret_var
    OUTPUT_STRIP_TRAILING_WHITESPACE)

# commit count
execute_process(
    COMMAND ${CTEST_GIT_COMMAND} rev-list master
    COMMAND wc -l
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    ERROR_VARIABLE git_error
    OUTPUT_VARIABLE GIT_COMMIT_COUNT
    RESULT_VARIABLE ret_var
    OUTPUT_STRIP_TRAILING_WHITESPACE)
string(STRIP ${GIT_COMMIT_COUNT} GIT_COMMIT_COUNT)

# ssh
find_program(ssh_executable ssh)
if(ssh_executable)
    message(STATUS "Found ssh (${ssh_executable})...")
else()
    message(FATAL_ERROR "Could not find a valid ssh installation.")
endif()

find_program(scp_executable scp)
if(scp_executable)
    message(STATUS "Found scp (${scp_executable})...")
else()
    message(FATAL_ERROR "Could not find a valid ssh installation.")
endif()

#
# useful vars
#

# site (for ctest)
site_name(DOGEN_SITE)

# staging directory
set(stage_dir ${CMAKE_BINARY_DIR}/stage)
set(stage_bin_dir ${stage_dir}/bin)
set(stage_pkg_dir ${stage_dir}/pkg)
set(stage_lib_dir ${stage_dir}/lib)
set(stage_inc_dir ${stage_dir}/include)
set(stage_test_data_dir ${stage_dir}/test_data)
set(stage_doxygen_dir ${stage_dir}/doxygen)

# ensure cmake dumps binaries in the right places
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${stage_bin_dir})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${stage_bin_dir})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${stage_bin_dir})

# version info
set(DOGEN_MAJOR_VERSION 0)
set(DOGEN_MINOR_VERSION 0)
set(DOGEN_PATCH_VERSION ${GIT_COMMIT_COUNT})
set(DOGEN_VERSION "${DOGEN_MAJOR_VERSION}")
set(DOGEN_VERSION "${DOGEN_VERSION}.${DOGEN_MINOR_VERSION}")
set(DOGEN_VERSION "${DOGEN_VERSION}.${DOGEN_PATCH_VERSION}")
message(STATUS "Product version: ${DOGEN_VERSION}")

if(WITH_DEBUG)
    set(DOGEN_VERSION "${DOGEN_VERSION}d")
endif()

# system includes
include_directories(SYSTEM
    ${LIBXML2_INCLUDE_DIR}
    # for sigc++config.h multiarch
    /usr/lib/i386-linux-gnu/sigc++-2.0/include
    /usr/lib/x86_64-linux-gnu/sigc++-2.0/include
    )

#
# doxygen
#
find_package(Doxygen)
if(DOXYGEN_FOUND)
    # input directories (used in doxygen template)
    set(DOGEN_CPP_CODE_DIR ${CMAKE_SOURCE_DIR}/projects)
    set(DOGEN_DOX_DIR ${stage_doxygen_dir}/dox)

    # output directory (used in doxygen template)
    set(DOGEN_DOXYGEN_DIR ${stage_doxygen_dir})

    # input file
    set(doxy_file ${stage_doxygen_dir}/dogen.doxy)
    add_custom_target(doxy ALL
        COMMAND rm -rf ${stage_doxygen_dir}/html
        COMMAND ${DOXYGEN_EXECUTABLE} ${doxy_file}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen" VERBATIM)

    set(target_dir "/usr/share/cdash/doxygen/dogen")
    add_custom_target(deploy_doxy
        COMMAND rm -rf ${target_dir}.new
        COMMAND mkdir ${target_dir}.new
        COMMAND cp -r ${stage_dir}/doxygen/html ${target_dir}.new/
        COMMAND rm -rf ${target_dir}
        COMMAND mv ${target_dir}.new ${target_dir}
        )
    add_dependencies(deploy_doxy doxy)

    install(
        DIRECTORY ${stage_doxygen_dir}/html/
        DESTINATION share/doc/${DOGEN_VERSION}/
        COMPONENT documentation
        )
endif()

#
# aggregate targets
#
add_custom_target(run_all_specs)

add_custom_target(rebase)
add_dependencies(rebase rebase_codegen rebase_dataset)

add_custom_target(diff)
add_dependencies(diff diff_codegen diff_dataset)

#
# include all sub directories
#
add_subdirectory(${CMAKE_SOURCE_DIR}/build)
add_subdirectory(${CMAKE_SOURCE_DIR}/deployment)
add_subdirectory(${CMAKE_SOURCE_DIR}/test_data)
add_subdirectory(${CMAKE_SOURCE_DIR}/projects)
add_subdirectory(${CMAKE_SOURCE_DIR}/diagrams)
