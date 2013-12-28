# - Find ODB library
# Find the native ODB includes and library
# This module defines
#  ODB_INCLUDE_DIR, where to find Url.h, etc.
#  ODB_LIBRARIES, libraries to link against to use ODB client C++.
#  ODB_FOUND, If false, do not try to use ODB client C++.
# also defined, but not for general use are
#  ODB_CORE_LIBRARY, where to find the core ODB library.
#  ODB_MYSQL_LIBRARY, where to find the mysql ODB library.
#  ODB_PGSQL_LIBRARY, where to find the pgsql ODB library.
#  ODB_BOOST_LIBRARY, where to find the boost profile for the ODB library.

# function(ODB_WRAP SRCS HDRS DATABASE PROFILE) # ARGS
# MESSAGE(STATUS "ODB database: " ${DATABASE})
# MESSAGE(STATUS "ODB profile: " ${PROFILE})
# set(${SRCS})
# set(${HDRS})
# foreach(_odb_h ${ARGN})
#     get_filename_component(_abs_odb_h ${_odb_h} ABSOLUTE)
#     get_filename_component(_we_odb_h ${_odb_h} NAME_WE)

#     list(APPEND ${SRCS} "${CMAKE_CURRENT_BINARY_DIR}/${_we_odb_h}-odb.cpp")
#     list(APPEND ${HDRS} "${CMAKE_CURRENT_BINARY_DIR}/${_we_odb_h}-odb.h")
#     list(APPEND ${HDRS} "${CMAKE_CURRENT_BINARY_DIR}/${_we_odb_h}-odb.i")

#     add_custom_command(
#     OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${_we_odb_h}-odb.cpp"
#            "${CMAKE_CURRENT_BINARY_DIR}/${_we_odb_h}-odb.h"
#            "${CMAKE_CURRENT_BINARY_DIR}/${_we_odb_h}-odb.i"
#     COMMAND ${ODB_COMPILER}
#     ARGS -d ${DATABASE} -p ${PROFILE}
#     -I ${ODB_INCLUDE_DIR} -I ${CMAKE_BINARY_DIR}/proto
#     --hxx-suffix .h
#     --ixx-suffix .i
#     --cxx-suffix .cpp
#     --output-dir ${CMAKE_CURRENT_BINARY_DIR}
#     --generate-query
#     --generate-schema
# #   --schema-format embedded
#     ${_abs_odb_h}
#     DEPENDS ${_abs_odb_h}
#     COMMENT "Running C++ ODB compiler on ${_odb_h}")
# endforeach()
# set_source_files_properties(${${SRCS}} ${${HDRS}} PROPERTIES GENERATED TRUE)
# set(${SRCS} ${${SRCS}} PARENT_SCOPE)
# set(${HDRS} ${${HDRS}} PARENT_SCOPE)
# endfunction()

# function(ODB_WRAP_MYSQL_BOOST SRCS HDRS)
# ODB_WRAP(__srcs __hdrs "mysql" "boost" ${ARGN})
# SET(${SRCS} ${__srcs} PARENT_SCOPE)
# SET(${HDRS} ${__hdrs} PARENT_SCOPE)
# endfunction()

# function(ODB_WRAP_PGSQL_BOOST SRCS HDRS)
# ODB_WRAP(__srcs __hdrs "pgsql" "boost" ${ARGN})
# SET(${SRCS} ${__srcs} PARENT_SCOPE)
# SET(${HDRS} ${__hdrs} PARENT_SCOPE)
# endfunction()


# FIND_PROGRAM(ODB_COMPILER odb
# PATHS
# /bin
# /usr/bin
# /opt/bin
# /opt/odb/bin
# )

FIND_PATH(ODB_INCLUDE_DIR odb/core.hxx)

FIND_LIBRARY(ODB_CORE_LIBRARY odb)

# FIND_LIBRARY(ODB_MYSQL_LIBRARY odb-mysql
# PATHS
# /usr/lib/
# /usr/lib64/
# /usr/local/lib/
# /usr/local/lib64/
# /opt/odb/lib
# /opt/lib
# )

FIND_LIBRARY(ODB_PGSQL_LIBRARY odb-pgsql)

FIND_LIBRARY(ODB_BOOST_LIBRARY odb-boost)

# handle the QUIETLY and REQUIRED arguments and set ODB_FOUND to TRUE if
# all listed variables are TRUE
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(ODB  DEFAULT_MSG
    ODB_CORE_LIBRARY ODB_PGSQL_LIBRARY ODB_BOOST_LIBRARY # ODB_MYSQL_LIBRARY
    ODB_INCLUDE_DIR #ODB_COMPILER
    )
#
IF(ODB_FOUND)
    SET(ODB_LIBRARIES ${ODB_CORE_LIBRARY} ${ODB_BOOST_LIBRARY})
    # MESSAGE(STATUS "Found ODB Compiler (ODB_COMPILER = ${ODB_COMPILER})")
    MESSAGE(STATUS "Found ODB Include folder (ODB_INCLUDE_DIR = ${ODB_INCLUDE_DIR})")
    MESSAGE(STATUS "Found ODB Core Libraries (ODB_LIBRARIES = ${ODB_LIBRARIES})")
    # MESSAGE(STATUS "Found ODB MySQL Library (ODB_MYSQL_LIBRARY = ${ODB_MYSQL_LIBRARY})")
    MESSAGE(STATUS "Found ODB PostgreSQL Library (ODB_PGSQL_LIBRARY = ${ODB_PGSQL_LIBRARY})")
ENDIF()
#
MARK_AS_ADVANCED(ODB_INCLUDE_DIR ODB_LIBRARIES)
