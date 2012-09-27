# -*- mode: cmake; tab-width: 4; indent-tabs-mode: nil -*-
#
# Copyright (C) 2011 Kitanda
#
# This file is distributed under the Kitanda Proprietary Software
# Licence. See doc/LICENCE.TXT for details.
#
include(InstallRequiredSystemLibraries)

set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Dogen - domain generator")
set(CPACK_PACKAGE_VENDOR "Kitanda")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/ReadMe.txt")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/Copyright.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${DOGEN_MAJOR_VERSION}")
set(CPACK_PACKAGE_VERSION_MINOR "${DOGEN_MINOR_VERSION}")
set(CPACK_PACKAGE_VERSION_PATCH "${DOGEN_PATCH_VERSION}")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "CMake ${CMAKE_VERSION_MAJOR}.${CMAKE_VERSION_MINOR}")

if(NOT DEFINED CPACK_SYSTEM_NAME)
    set(CPACK_SYSTEM_NAME "${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}")
endif()

if(WIN32)
    set(CPACK_GENERATOR "NSIS")
    set(CPACK_SOURCE_GENERATOR "ZIP")
elseif(APPLE)
    set(CPACK_GENERATOR "PackageMaker")
    set(CPACK_SOURCE_GENERATOR "TGZ")
elseif(UNIX)
    set(CPACK_GENERATOR "DEB")
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Kitanda Development Group")
    set(CPACK_SOURCE_GENERATOR "TGZ")

    set(CPACK_SET_DESTDIR true)
    set(CPACK_INSTALL_PREFIX "/opt/kitanda")
    set(CPACK_DEBIAN_PACKAGE_DEPENDS "libxml2")
else()
    message(FATAL_ERROR "unknown operating system")
endif()

if(WIN32 AND NOT UNIX)
    # There is a bug in NSI that does not handle full unix paths properly. Make
    # sure there is at least one set of four (4) backslashes.
    set(CPACK_PACKAGE_ICON "${CMAKE_SOURCE_DIR}\\\\images\\\\application_dogen.png")
    set(CPACK_NSIS_INSTALLED_ICON_NAME "bin\\\\dogen_driver.exe")
    set(CPACK_NSIS_DISPLAY_NAME "Dogen")
    set(CPACK_NSIS_HELP_LINK "http:\\\\\\\\http://kitanda.co.uk/html/index.html")
    set(CPACK_NSIS_URL_INFO_ABOUT "http:\\\\\\\\http://kitanda.co.uk/html/index.html")
    set(CPACK_NSIS_CONTACT "info@kitanda.co.uk")
    set(CPACK_NSIS_MODIFY_PATH ON)

else(WIN32 AND NOT UNIX)
    set(CPACK_STRIP_FILES "")
    set(CPACK_SOURCE_STRIP_FILES "")
endif(WIN32 AND NOT UNIX)

# set(CPACK_PACKAGE_EXECUTABLES "stage/bin/dogen_driver" "Dogen - domain generator")
set(CPACK_OUTPUT_FILE_PREFIX "${stage_pkg_dir}")
include(CPack)
