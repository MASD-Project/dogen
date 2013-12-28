# - Find EOS library
# Find the native EOS includes
# This module defines
#  EOS_INCLUDE_DIR, where to find Url.h, etc.
#  EOS_FOUND, If false, do not try to use EOS.

FIND_PATH(EOS_INCLUDE_DIR eos/portable_archive.hpp)

# handle the QUIETLY and REQUIRED arguments and set ODB_FOUND to TRUE if
# all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(EOS DEFAULT_MSG EOS_INCLUDE_DIR)

IF(EOS_FOUND)
    MESSAGE(STATUS "Found EOS Include folder (EOS_INCLUDE_DIR = ${EOS_INCLUDE_DIR})")
ENDIF()

MARK_AS_ADVANCED(EOS_INCLUDE_DIR)
