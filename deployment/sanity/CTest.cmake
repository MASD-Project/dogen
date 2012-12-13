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

#
# to run this script do:
# ctest -S /opt/kitanda/dogen-0.0.762/deployment/sanity/CTest.cmake,package_dir=/opt/kitanda/dogen-0.0.762 -VV
#

# handle input parameters to script.
if(DEFINED CTEST_SCRIPT_ARG)
    # transform ctest script arguments of the form
    # script.ctest,var1=value1,var2=value2
    # to variables with the respective names set to the respective values
    string(REPLACE "," ";" script_args "${CTEST_SCRIPT_ARG}")
    foreach(current_var ${script_args})
        if ("${current_var}" MATCHES "^([^=]+)=(.+)$")
            set("${CMAKE_MATCH_1}" "${CMAKE_MATCH_2}")
        endif()
    endforeach()
endif()

#
# model
#
if(NOT DEFINED model)
    set(model Experimental)
else()
    if(${model} MATCHES Experimental)
        message("Building Experimental model.")
    elseif(${model} MATCHES Nightly)
        message("Building Nightly model.")
    elseif(${model} MATCHES Continuous)
        message("Building Continuous model.")
    else()
        message(FATAL_ERROR "Invalid model: ${model}")
    endif()
endif()

#
# path to package directory
#
if(NOT DEFINED package_dir)
    message(FATAL_ERROR "Path to package directory not supplied")
endif()
message(STATUS "Performing sanity checks for: ${package_dir}")

# set the site to the hostname. this shows up in the dashboard.
site_name(CURRENT_SITE)
set(SITE "${CURRENT_SITE}")
set(CTEST_SITE "${CURRENT_SITE}")

# create the build name
set(CTEST_BUILD_NAME "deployment_sanity_test")

set(CTEST_SOURCE_DIRECTORY "${package_dir}/deployment/sanity")
if(WIN32)
  set(tmpdir "$ENV{TEMP}")
else()
  set(tmpdir "$ENV{TMPDIR}")
endif()

if(NOT EXISTS "${tmpdir}")
    set(tmpdir "$ENV{TMP}")
    if(NOT EXISTS "${tmpdir}")

        if(UNIX)
            set(tmpdir "/tmp")
        elseif (WIN32)
            set(tmpdir "c:/temp")
        endif()

        if(NOT EXISTS "${tmpdir}")
            message(FATAL_ERROR "Cannot determine temporary directory")
        endif()
    endif()
endif()

set(CTEST_BINARY_DIRECTORY "${tmpdir}/dogen_sanity_tests")

set(CTEST_CONFIGURE_COMMAND "${CMAKE_COMMAND} ${CTEST_SOURCE_DIRECTORY}")
set(CTEST_NIGHTLY_START_TIME "00:30:00 UTC")
ctest_start(Continuous)
ctest_configure(BUILD ${CTEST_BINARY_DIRECTORY})
ctest_test(BUILD "${CTEST_BINARY_DIRECTORY}")
ctest_submit()
