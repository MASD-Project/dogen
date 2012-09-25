# -*- mode: cmake; tab-width: 4; indent-tabs-mode: nil -*-
#
# Copyright (C) 2011 Kitanda
#
# This file is distributed under the Kitanda Proprietary Software
# Licence. See doc/LICENCE.TXT for details.
#
include(InstallRequiredSystemLibraries)

set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Dogen - Domain Generator")
set(CPACK_PACKAGE_VENDOR "Dogen")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/ReadMe.txt")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/Copyright.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${DOGEN_MAJOR_VERSION}")
set(CPACK_PACKAGE_VERSION_MINOR "${DOGEN_MINOR_VERSION}")
set(CPACK_PACKAGE_VERSION_PATCH "${DOGEN_PATCH_VERSION}")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "CMake ${CMake_VERSION_MAJOR}.${CMake_VERSION_MINOR}")

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
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Kitanda team")
    set(CPACK_SOURCE_GENERATOR "TGZ")
else()
    message(FATAL_ERROR "unknown operating system")
endif()

if(WIN32 AND NOT UNIX)
    # There is a bug in NSI that does not handle full unix paths properly. Make
    # sure there is at least one set of four (4) backlasshes.
    set(CPACK_PACKAGE_ICON "${CMake_SOURCE_DIR}\\\\doc/website/doc/images/kitanda_logo/kitanda_logo.svg")
    set(CPACK_NSIS_INSTALLED_ICON_NAME "bin\\\\MyExecutable.exe")
    set(CPACK_NSIS_DISPLAY_NAME "${CPACK_PACKAGE_INSTALL_DIRECTORY} My Famous Project")
    set(CPACK_NSIS_HELP_LINK "http:\\\\\\\\www.my-project-home-page.org")
    set(CPACK_NSIS_URL_INFO_ABOUT "http:\\\\\\\\www.my-personal-home-page.com")
    set(CPACK_NSIS_CONTACT "me@my-personal-home-page.com")
    set(CPACK_NSIS_MODIFY_PATH ON)
else(WIN32 AND NOT UNIX)
    set(CPACK_STRIP_FILES "bin/dogen")
    set(CPACK_SOURCE_STRIP_FILES "")
endif(WIN32 AND NOT UNIX)

set(CPACK_PACKAGE_EXECUTABLES "dogen" "dogen")
include(CPack)