# -*- mode: cmake; tab-width: 4; indent-tabs-mode: nil -*-
#
# Copyright (C) 2011 Kitanda
#
# This file is distributed under the Kitanda Proprietary Software
# Licence. See doc/LICENCE.TXT for details.
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
option(WITH_DEBUG "Build the project with debug symbols" on)
option(WITH_DATABASE_SUPPORT "Build with postgres support" on)
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
        message(STATUS "winsock not found, building WITHOUT postgres support.")
        set(WITH_DATABASE_SUPPORT off)
    endif()

    find_library(WSOCK2_LIB NAMES ws2_32 DOC "The winsock 2 library")
    if(WSOCK2_LIB)
        list(APPEND CMAKE_REQUIRED_LIBRARIES ws2_32)
    else()
        message(STATUS "winsock2 not found, building WITHOUT postgres support.")
        set(WITH_DATABASE_SUPPORT off)
    endif()

    find_library(MSWSOCK_LIB NAMES mswsock DOC "The winsock 2 library")
    if(MSWSOCK_LIB)
        list(APPEND CMAKE_REQUIRED_LIBRARIES mswsock)
    else()
        message(STATUS "mswsock not found, building WITHOUT postgres support.")
        set(WITH_DATABASE_SUPPORT off)
    endif()
endif()

# database
set(DOGEN_DATABASE_SUPPORT 0)
if(WITH_DATABASE_SUPPORT)
   find_package(PQXX)
   if(PQXX_FOUND)
       message(STATUS "Found libpqxx...")
       set(DOGEN_DATABASE_SUPPORT 1)
   else()
       message(STATUS "libpqxx not found, building WITHOUT postgres support.")
       set(WITH_DATABASE_SUPPORT off)
   endif()
else()
   message(STATUS "Building WITHOUT postgres support...")
endif()

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

#
# useful vars
#

# site (for ctest)
site_name(DOGEN_SITE)

# staging directory
set(stage_dir ${CMAKE_BINARY_DIR}/stage)
set(stage_bin_dir ${CMAKE_BINARY_DIR}/stage/bin)
set(stage_test_data_dir ${stage_dir}/test_data)
set(stage_doxygen_dir ${stage_dir}/doxygen)

# ensure cmake dumps binaries in the right places
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${stage_bin_dir})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${stage_bin_dir})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${stage_bin_dir})

# version info
set(DOGEN_MAJOR_VERSION 0)
set(DOGEN_MINOR_VERSION 0)
set(DOGEN_PATCH_VERSION 17)
set(DOGEN_VERSION "${DOGEN_MAJOR_VERSION}")
set(DOGEN_VERSION "${DOGEN_VERSION}.${DOGEN_MINOR_VERSION}")
set(DOGEN_VERSION "${DOGEN_VERSION}.${DOGEN_PATCH_VERSION}")

if(WITH_DEBUG)
    set(DOGEN_VERSION "${DOGEN_VERSION}-debug")
endif()

# additional include
include_directories(
    ${CMAKE_SOURCE_DIR}/projects/config/include
    ${CMAKE_SOURCE_DIR}/projects/dia/include
    ${CMAKE_SOURCE_DIR}/projects/sml/include
    ${CMAKE_SOURCE_DIR}/projects/utility/include
    ${CMAKE_SOURCE_DIR}/projects/generator/include
    ${CMAKE_SOURCE_DIR}/projects/driver/include

    ${CMAKE_SOURCE_DIR}/projects/all_primitives/include
    ${CMAKE_SOURCE_DIR}/projects/classes_in_a_package/include
    ${CMAKE_SOURCE_DIR}/projects/classes_inside_and_outside_package/include
    ${CMAKE_SOURCE_DIR}/projects/classes_without_package/include
    ${CMAKE_SOURCE_DIR}/projects/class_in_a_package/include
    ${CMAKE_SOURCE_DIR}/projects/class_without_attributes/include
    ${CMAKE_SOURCE_DIR}/projects/class_without_package/include
    ${CMAKE_SOURCE_DIR}/projects/class_without_package_and_attributes/include
    ${CMAKE_SOURCE_DIR}/projects/compressed/include
    ${CMAKE_SOURCE_DIR}/projects/disable_complete_constructor/include
    ${CMAKE_SOURCE_DIR}/projects/disable_facet_folders/include
    ${CMAKE_SOURCE_DIR}/projects/disable_cmakelists/include
    ${CMAKE_SOURCE_DIR}/projects/enable_facet_domain/include
    ${CMAKE_SOURCE_DIR}/projects/enable_facet_hash/include
    ${CMAKE_SOURCE_DIR}/projects/enable_facet_io/include
    ${CMAKE_SOURCE_DIR}/projects/enable_facet_serialization/include
    ${CMAKE_SOURCE_DIR}/projects/two_layers_with_objects/include
    )

include_directories(SYSTEM
    ${LIBXML2_INCLUDE_DIR}
    # for sigc++config.h multiarch
    /usr/lib/i386-linux-gnu/sigc++-2.0/include
    /usr/lib/x86_64-linux-gnu/sigc++-2.0/include
    )

#
# doxygen
#

# input directories (used in doxygen template)
set(DOGEN_CPP_CODE_DIR ${CMAKE_SOURCE_DIR}/projects)
set(DOGEN_DOX_DIR ${stage_doxygen_dir}/dox)

# output directory (used in doxygen template)
set(DOGEN_DOXYGEN_DIR ${stage_doxygen_dir})

# input file
set(doxy_file ${stage_doxygen_dir}/dogen.doxy)
add_custom_target(doxy doxygen ${doxy_file})

#
# include all sub directories
#
add_subdirectory(${CMAKE_SOURCE_DIR}/build/templates)
add_subdirectory(${CMAKE_SOURCE_DIR}/build/cpack)
add_subdirectory(${CMAKE_SOURCE_DIR}/test_data)
add_subdirectory(${CMAKE_SOURCE_DIR}/projects)

#
# aggregate targets
#
add_custom_target(build_all)
add_dependencies(build_all
    sml
    sml_spec
    dogen
    dogen_spec
    utility
    utility_spec
    dia
    dia_spec
    header_validation
    generator
    generator_spec
    driver
    driver_spec

    all_primitives
    all_primitives_spec
    classes_in_a_package
    classes_inside_and_outside_package
    classes_without_package
    class_in_a_package
    class_in_a_package_spec
    class_without_attributes
    class_without_package
    class_without_package_and_attributes
    compressed
    disable_complete_constructor
    enable_facet_domain
    enable_facet_hash
    enable_facet_io
    enable_facet_serialization
    two_layers_with_objects
    )

add_custom_target(run_all_specs)
add_dependencies(run_all_specs
    clean_codegen
    build_all
    run_sml_spec
    run_dia_spec
    run_generator_spec
    run_driver_spec
    run_utility_spec
    run_all_primitives_spec
    run_class_in_a_package_spec
    )

add_custom_target(rebase)
add_dependencies(rebase rebase_codegen rebase_dataset)

add_custom_target(diff)
add_dependencies(diff diff_codegen diff_dataset)
