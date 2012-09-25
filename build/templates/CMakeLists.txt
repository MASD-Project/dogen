# -*- mode: cmake; tab-width: 4; indent-tabs-mode: nil -*-
#
# Copyright (C) 2011 Kitanda
#
# This file is distributed under the Kitanda Proprietary Software
# Licence. See doc/LICENCE.TXT for details.
#
set(version_template "${CMAKE_CURRENT_SOURCE_DIR}/cpp/version.hpp.in")
configure_file(${version_template}
    ${CMAKE_SOURCE_DIR}/projects/config/include/dogen/config/version.hpp)
message(STATUS "Transformed version.hpp.")

set(doxy_template "${CMAKE_CURRENT_SOURCE_DIR}/doxygen/dogen.in")
configure_file(${doxy_template} ${stage_doxygen_dir}/dogen.doxy)
message(STATUS "Transformed dogen.doxy.")