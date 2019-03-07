# - Find DTL library
# Find the DTL includes
# This module defines
#  DTL_INCLUDE_DIR, where to find dtl.h, etc.
#  DTL_FOUND, If false, do not try to use DTL.

FIND_PATH(DTL_INCLUDE_DIR dtl/dtl.hpp)

# handle the QUIETLY and REQUIRED arguments and set ODB_FOUND to TRUE if
# all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(DTL DEFAULT_MSG DTL_INCLUDE_DIR)

IF(DTL_FOUND)
    MESSAGE(STATUS "Found DTL Include folder (DTL_INCLUDE_DIR = ${DTL_INCLUDE_DIR})")
ENDIF()

MARK_AS_ADVANCED(DTL_INCLUDE_DIR)
