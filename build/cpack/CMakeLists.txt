# -*- mode: cmake; tab-width: 4; indent-tabs-mode: nil -*-
#
# Copyright (C) 2011 Kitanda
#
# This file is distributed under the Kitanda Proprietary Software
# Licence. See doc/LICENCE.TXT for details.
#
include(InstallRequiredSystemLibraries)

set(CPACK_PACKAGE_NAME "${CMAKE_PROJECT_NAME}")
set(CPACK_PACKAGE_VERSION_MAJOR "${DOGEN_MAJOR_VERSION}")
set(CPACK_PACKAGE_VERSION_MINOR "${DOGEN_MINOR_VERSION}")
set(CPACK_PACKAGE_VERSION_PATCH "${DOGEN_PATCH_VERSION}")
set(CPACK_PACKAGE_VERSION "${DOGEN_MAJOR_VERSION}.${DOGEN_MINOR_VERSION}.${DOGEN_PATCH_VERSION}-0")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Dogen - domain generator")
set(CPACK_PACKAGE_CONTACT "http://kitanda.co.uk/html/index.html")
set(CPACK_PACKAGE_VENDOR "Kitanda")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/ReadMe.txt")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/Copyright.txt")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "${PROJECT_NAME}-${DOGEN_MAJOR_VERSION}.${DOGEN_MINOR_VERSION}")

if(NOT DEFINED CPACK_SYSTEM_NAME)
    set(CPACK_SYSTEM_NAME "${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}")
endif()

if(WIN32)
    set(CPACK_GENERATOR "NSIS")
    set(CPACK_SOURCE_GENERATOR "ZIP")
    set(CPACK_PACKAGE_EXECUTABLES "dogen_driver" "Dogen - domain generator")

    # There is a bug in NSI that does not handle full unix paths properly. Make
    # sure there is at least one set of four (4) backslashes.
    set(CPACK_PACKAGE_ICON "${CMAKE_SOURCE_DIR}\\\\images\\\\application_dogen.png")
    set(CPACK_NSIS_INSTALLED_ICON_NAME "bin\\\\dogen_driver.exe")
    set(CPACK_NSIS_DISPLAY_NAME "Dogen")
    set(CPACK_NSIS_HELP_LINK "http:\\\\\\\\http://kitanda.co.uk/html/index.html")
    set(CPACK_NSIS_URL_INFO_ABOUT "http:\\\\\\\\http://kitanda.co.uk/html/index.html")
    set(CPACK_NSIS_CONTACT "info@kitanda.co.uk")
    set(CPACK_NSIS_MODIFY_PATH ON)

elseif(APPLE)
    set(CPACK_SOURCE_GENERATOR "TGZ")

    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Info.plist.in ${stage_dir}/tmp_pkg/macosx/Info.plist)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/start.in ${stage_dir}/tmp_pkg/macosx/start)
    set(CPACK_GENERATOR "Bundle")
    set(CPACK_BUNDLE_PLIST ${stage_dir}/tmp_pkg/macosx/Info.plist)
    set(CPACK_BUNDLE_ICON ${CMAKE_CURRENT_SOURCE_DIR}/application_dogen.icns)
    set(CPACK_BUNDLE_NAME "dogen")
    set(CPACK_BUNDLE_STARTUP_COMMAND ${stage_dir}/tmp_pkg}/macosx/start)
    set(CPACK_PACKAGE_EXECUTABLES "dogen_driver" "Dogen - domain generator")

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
    endif()

    # For Debian-based distros we want to create DEB packages.
    if("${LSB_DISTRIB}" MATCHES "Ubuntu|Debian")
        make_directory(${stage_dir}/tmp_pkg/debian)
        set(GTK_UPDATE_ICON_CACHE "gtk-update-icon-cache -f -t ${THEME_DIRECTORY}")

        set(CPACK_GENERATOR "DEB")
        set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Kitanda Development Group")
        set(CPACK_SOURCE_GENERATOR "TGZ")

        set(CPACK_DEBIAN_PACKAGE_PRIORITY "extra")
        set(CPACK_DEBIAN_PACKAGE_SECTION "devel")
        set(CPACK_DEBIAN_PACKAGE_RECOMMENDS "")

        # We need to alter the architecture names as per distro rules
        if("${CPACK_PACKAGE_ARCHITECTURE}" MATCHES "i[3-6]86")
            set(CPACK_PACKAGE_ARCHITECTURE i386)
        endif("${CPACK_PACKAGE_ARCHITECTURE}" MATCHES "i[3-6]86")
        if("${CPACK_PACKAGE_ARCHITECTURE}" MATCHES "x86_64")
            set(CPACK_PACKAGE_ARCHITECTURE amd64)
        endif("${CPACK_PACKAGE_ARCHITECTURE}" MATCHES "x86_64")
        set(CPACK_DEBIAN_PACKAGE_DEPENDS "libxml2")
        string(TOLOWER
            "${CPACK_PACKAGE_NAME}_${CPACK_PACKAGE_VERSION}_${CPACK_PACKAGE_ARCHITECTURE}" CPACK_PACKAGE_FILE_NAME)
    endif()

    set(CPACK_SET_DESTDIR true)
    set(CPACK_INSTALL_PREFIX "/opt/kitanda")
else()
    message(FATAL_ERROR "unknown operating system")
endif()

set(CPACK_OUTPUT_FILE_PREFIX "${stage_pkg_dir}")
include(CPack)
