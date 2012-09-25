# Find PostGreSQL C++ library and header file
# Sets
#   PQXX_FOUND                 to 0 or 1 depending on result
#   PQXX_INCLUDE_DIRECTORIES  to the directory containing mysql.h
#   PQXX_LIBRARIES            to the MySQL client library (and any dependents required)
# If PQXX_REQUIRED is defined, then a fatal error message will be generated if libpqxx is not found

# This script is initially based on:
# http://ruby-vtk.rubyforge.org/svn/trunk/VTK/CMake/FindPQXX.cmake
# As  scripts for finding the PQXX package seem either to not be
# maintained or to serve different sets of assumptions of those on
# Kitanda, we maintain our own version, with sensible modifications
#
# This version of the file removes the requirement of having Postgres
# installed in order to build with PQXX. After confirmation, the lines
# commented on the code should be removed.

if ( NOT PQXX_INCLUDE_DIRECTORIES OR NOT PQXX_LIBRARIES )

# Set 9.1 the first Postgres version to be checked for
  set(PostgreSQL_ADDITIONAL_VERSIONS "9.1")
  FIND_PACKAGE( PostgreSQL REQUIRED )
  
  if ( POSTGRESQL_FOUND )
    file( TO_CMAKE_PATH "$ENV{PQXX_DIR}" _PQXX_DIR )

    find_library( PQXX_LIBRARY
      NAMES libpqxx pqxx
      PATHS
        ${_PQXX_DIR}/lib
        ${_PQXX_DIR}
        ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/bin
        /usr/local/pgsql/lib
        /usr/local/lib
        /usr/lib
      DOC "Location of libpqxx library"
      NO_DEFAULT_PATH
    )

    find_path( PQXX_HEADER_PATH
      NAMES pqxx/pqxx
      PATHS
        ${_PQXX_DIR}/include
        ${_PQXX_DIR}
        ${CMAKE_INSTALL_PREFIX}/include
        /usr/local/pgsql/include
        /usr/local/include
        /usr/include
      DOC "Path to pqxx/pqxx header file. Do not include the 'pqxx' directory in this value."
      NO_DEFAULT_PATH
    )
  endif ( POSTGRESQL_FOUND )

  if ( PQXX_HEADER_PATH AND PQXX_LIBRARY )

    set( PQXX_FOUND 1 CACHE INTERNAL "PQXX found" FORCE )
    set( PQXX_INCLUDE_DIRECTORIES "${PQXX_HEADER_PATH};${PostgreSQL_INCLUDE_DIRS}" CACHE STRING "Include directories for PostGreSQL C++ library"  FORCE )
    set( PQXX_LIBRARIES "${PQXX_LIBRARY};${PostgreSQL_LIBRARY}" CACHE STRING "Link libraries for PostGreSQL C++ interface" FORCE )

    mark_as_advanced( FORCE PQXX_INCLUDE_DIRECTORIES )
    mark_as_advanced( FORCE PQXX_LIBRARIES )

  else ( PQXX_HEADER_PATH AND PQXX_LIBRARY )
    message( "PQXX NOT FOUND" )
  endif ( PQXX_HEADER_PATH AND PQXX_LIBRARY )

endif ( NOT PQXX_INCLUDE_DIRECTORIES OR NOT PQXX_LIBRARIES )

