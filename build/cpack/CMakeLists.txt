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
include(InstallRequiredSystemLibraries)

set(CPACK_PACKAGE_NAME "${CMAKE_PROJECT_NAME}")
set(CPACK_PACKAGE_VERSION_MAJOR "${DOGEN_MAJOR_VERSION}")
set(CPACK_PACKAGE_VERSION_MINOR "${DOGEN_MINOR_VERSION}")
set(CPACK_PACKAGE_VERSION_PATCH "${DOGEN_PATCH_VERSION}")
set(CPACK_PACKAGE_VERSION "${DOGEN_VERSION_MAJOR}.${DOGEN_VERSION_MINOR}.${DOGEN_VERSION_PATCH}")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Dogen - domain generator")
set(CPACK_PACKAGE_CONTACT "https://github.com/MASD-Project/dogen")
set(CPACK_PACKAGE_VENDOR "MASD Project")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/ReadMe.txt")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/Copyright.txt")

if(NOT DEFINED CPACK_SYSTEM_NAME)
    set(CPACK_SYSTEM_NAME "${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}")
endif()

#
# Component configuration
#
if(WITH_MINIMAL_PACKAGING)
    set(components applications)
    set(CPACK_COMPONENTS_ALL ${components})

    set(CPACK_COMPONENT_APPLICATIONS_DISPLAY_NAME "Dogen")
    set(CPACK_COMPONENT_APPLICATIONS_DESCRIPTION
        "The Domain Generator - Generates source code for domain driven development.")
    set(CPACK_COMPONENT_APPLICATIONS_GROUP "Runtime")

else()
    set(components applications libraries headers tests)
    if(DOXYGEN_FOUND)
        set(components ${components} documentation)
    endif()
    set(CPACK_COMPONENTS_ALL ${components})

    set(CPACK_COMPONENT_APPLICATIONS_DISPLAY_NAME "Dogen")
    set(CPACK_COMPONENT_APPLICATIONS_DESCRIPTION
        "The Domain Generator - Generates source code for domain driven development.")

    set(CPACK_COMPONENT_LIBRARIES_DISPLAY_NAME "Dogen Libraries")
    set(CPACK_COMPONENT_LIBRARIES_DESCRIPTION
        "Static libraries used to build programs using Dogen")

    set(CPACK_COMPONENT_HEADERS_DISPLAY_NAME "Dogen C++ Headers")
    set(CPACK_COMPONENT_HEADERS_DESCRIPTION
        "C/C++ header files for use with Dogen libraries")

    set(CPACK_COMPONENT_TESTS_DISPLAY_NAME "Dogen unit tests")
    set(CPACK_COMPONENT_TESTS_DESCRIPTION
        "Unit tests used to test Dogen")

    if(DOXYGEN_FOUND)
        set(CPACK_COMPONENT_DOCUMENTATION_DISPLAY_NAME "Dogen documentation")
        set(CPACK_COMPONENT_DOCUMENTATION_DESCRIPTION
            "Dogen documentation")
    endif()

    set(CPACK_COMPONENT_HEADERS_DEPENDS libraries)
    set(CPACK_COMPONENT_TESTS_DEPENDS applications)

    set(CPACK_COMPONENT_APPLICATIONS_GROUP "Runtime")
    set(CPACK_COMPONENT_LIBRARIES_GROUP "Development")
    set(CPACK_COMPONENT_HEADERS_GROUP "Development")
    set(CPACK_COMPONENT_TESTS_GROUP "Development")

    if(DOXYGEN_FOUND)
        set(CPACK_COMPONENT_DOCUMENTATION_GROUP "Development")
    endif()

    set(CPACK_COMPONENT_GROUP_DEVELOPMENT_DESCRIPTION
        "Tools needed to develop applications using Dogen")
endif()

set(CPACK_COMPONENTS_IGNORE_GROUPS TRUE)
set(CPACK_ARCHIVE_COMPONENT_INSTALL TRUE)

if(NOT EXISTS "${stage_lib_dir}")
    file(MAKE_DIRECTORY "${stage_lib_dir}")
endif()

#
# add c++ runtime DLLs
#
if(NOT EXISTS "${stage_lib_dir}")
    file(MAKE_DIRECTORY "${stage_lib_dir}")
endif()

include (InstallRequiredSystemLibraries)

#
# platform specific
#
if(WIN32)
    set(CPACK_PACKAGE_INSTALL_DIRECTORY "${PROJECT_NAME}")

    if (MSVC)
        # don't forget to set the WIX path, e.g.:
        # WIX="C:/Program Files (x86)/WiX Toolset v3.10/bin" cpack -G WIX -C Release
        set(CPACK_GENERATOR "WIX")
        set(CPACK_PACKAGE_EXECUTABLES "masd.dogen.cli" "Dogen - CLI")
        set(CPACK_WIX_PRODUCT_GUID "6CEB9CA0-B274-41A0-8B46-D35FF3FE46B6")
        set(CPACK_WIX_UPGRADE_GUID "B634B583-2F49-41D3-AC4C-8A67E88E88E3")
        set(CPACK_WIX_PRODUCT_ICON "${CMAKE_SOURCE_DIR}/doc/images/application_dogen.png")
    else()
        set(CPACK_GENERATOR "NSIS")
        set(CPACK_SOURCE_GENERATOR "ZIP")
        set(CPACK_PACKAGE_EXECUTABLES "masd.dogen.cli" "Dogen - CLI")
        set(CPACK_PACKAGE_ICON "${CMAKE_SOURCE_DIR}\\\\doc\\\\images\\\\application_dogen.png")

        if(CMAKE_CL_64)
            set(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES64")
        else()
            set(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES")
        endif()

        # There is a bug in NSI that does not handle full unix paths properly. Make
        # sure there is at least one set of four (4) backslashes.
        set(CPACK_PACKAGE_ICON "${CMAKE_SOURCE_DIR}\\\\images\\\\application_dogen.png")
        set(CPACK_NSIS_INSTALLED_ICON_NAME "bin\\\\masd.dogen.cli.exe")
        set(CPACK_NSIS_DISPLAY_NAME "Dogen")
        set(CPACK_NSIS_PACKAGE_NAME "Dogen ${DOGEN_VERSION}")
        set(CPACK_NSIS_HELP_LINK "http:\\\\\\\\https://github.com/DomainDrivenConsulting/dogen/blob/master/doc/manual/manual.org")
        set(CPACK_NSIS_URL_INFO_ABOUT "http:\\\\\\\\https://github.com/DomainDrivenConsulting/dogen/blob/master/doc/manual/manual.org")
        set(CPACK_NSIS_CONTACT "")
        set(CPACK_NSIS_MODIFY_PATH ON)
    endif()
elseif(APPLE)
    set(CPACK_SOURCE_GENERATOR "TGZ")
    set(CPACK_PACKAGE_INSTALL_DIRECTORY "${PROJECT_NAME}")
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Info.plist.in ${stage_dir}/tmp_pkg/macosx/Info.plist)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/start.in ${stage_dir}/tmp_pkg/macosx/start)

    set(CPACK_GENERATOR "Bundle")
    set(CPACK_BUNDLE_PLIST ${stage_dir}/tmp_pkg/macosx/Info.plist)
    set(CPACK_BUNDLE_ICON ${CMAKE_CURRENT_SOURCE_DIR}/application_dogen.icns)
    set(CPACK_BUNDLE_NAME "dogen")
    set(CPACK_BUNDLE_STARTUP_COMMAND ${stage_dir}/tmp_pkg/macosx/start)
    set(CPACK_PACKAGE_EXECUTABLES "masd.dogen.cli" "Dogen - CLI")

    set(CPACK_ALL_INSTALL_TYPES Full Developer)
    set(CPACK_COMPONENT_LIBRARIES_INSTALL_TYPES Developer Full)
    set(CPACK_COMPONENT_HEADERS_INSTALL_TYPES Developer Full)
    set(CPACK_COMPONENT_APPLICATIONS_INSTALL_TYPES Full)

elseif(UNIX)
    set(CPACK_STRIP_FILES "")
    set(CPACK_SOURCE_STRIP_FILES "")

    # Try to find architecture
    execute_process(COMMAND uname -m OUTPUT_VARIABLE CPACK_PACKAGE_ARCHITECTURE)
    string(STRIP "${CPACK_PACKAGE_ARCHITECTURE}" CPACK_PACKAGE_ARCHITECTURE)

    # Try to find distro name and distro-specific arch
    execute_process(COMMAND lsb_release -is OUTPUT_VARIABLE LSB_ID)
    execute_process(COMMAND lsb_release -rs OUTPUT_VARIABLE LSB_RELEASE)
    string(STRIP "${LSB_ID}" LSB_ID)
    string(STRIP "${LSB_RELEASE}" LSB_RELEASE)
    set(LSB_DISTRIB "${LSB_ID}${LSB_RELEASE}")
    if(NOT LSB_DISTRIB)
        set(LSB_DISTRIB "unix")
    endif()

    if("${LSB_DISTRIB}" MATCHES "Fedora|Mandriva")
        make_directory(${stage_dir}/tmp_pkg/rpm)
        set(CPACK_GENERATOR "RPM")
        set(CPACK_RPM_PACKAGE_ARCHITECTURE ${CPACK_PACKAGE_ARCHITECTURE})
        set(CPACK_RPM_PACKAGE_RELEASE "1")
        set(CPACK_RPM_COMPONENT_INSTALL ON)
    endif()

    # For Debian-based distros we want to create DEB packages.
    if("${LSB_DISTRIB}" MATCHES "Ubuntu|Debian")
        make_directory(${stage_dir}/tmp_pkg/debian)
        set(GTK_UPDATE_ICON_CACHE "gtk-update-icon-cache -f -t ${THEME_DIRECTORY}")
        set(CPACK_DEB_PACKAGE_DEBUG "1")
        set(CPACK_GENERATOR "DEB")
        set(CPACK_DEB_COMPONENT_INSTALL ON)
        set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Domain Driven Consulting")
        set(CPACK_SOURCE_GENERATOR "TGZ")
        set(CPACK_DEBIAN_PACKAGE_PRIORITY "extra")
        set(CPACK_DEBIAN_PACKAGE_SECTION "devel")
        set(CPACK_DEBIAN_PACKAGE_RECOMMENDS "")

        # set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS TRUE)

        # We need to alter the architecture names as per distro rules
        if("${CPACK_PACKAGE_ARCHITECTURE}" MATCHES "i[3-6]86")
            set(CPACK_PACKAGE_ARCHITECTURE i386)
        endif("${CPACK_PACKAGE_ARCHITECTURE}" MATCHES "i[3-6]86")
        if("${CPACK_PACKAGE_ARCHITECTURE}" MATCHES "x86_64")
            set(CPACK_PACKAGE_ARCHITECTURE amd64)
        endif("${CPACK_PACKAGE_ARCHITECTURE}" MATCHES "x86_64")

        set(deps "libxml2")
        set(deps "${deps}, libc6 (>= 2.1.3)")
        set(deps "${deps}, libgcc1 (>= 1:4.7.1)")
        set(deps "${deps}, libstdc++6 (>= 4.7.1)")
        if (CMAKE_COMPILER_IS_CLANGXX)
            set(deps "${deps}, llvm-3.1-dev (>= 3.1.0)")
        endif()

        set(CPACK_DEBIAN_PACKAGE_DEPENDS ${deps})
        string(TOLOWER
            "${CPACK_PACKAGE_NAME}_${CPACK_PACKAGE_VERSION}_${CPACK_PACKAGE_ARCHITECTURE}" CPACK_PACKAGE_FILE_NAME)
    endif()

    set(CPACK_SET_DESTDIR true)
    set(CPACK_INSTALL_PREFIX "/usr")
else()
    message(FATAL_ERROR "unknown operating system")
endif()

set(CPACK_OUTPUT_FILE_PREFIX "${stage_pkg_dir}")
include(CPack)
