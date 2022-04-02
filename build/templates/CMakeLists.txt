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
set(version_template "${CMAKE_CURRENT_SOURCE_DIR}/cpp/config.hpp.in")
configure_file(${version_template} ${stage_inc_dir}/dogen/config.hpp)
message(STATUS "Transformed ${version_template}.")

set(doxy_template "${CMAKE_CURRENT_SOURCE_DIR}/doxygen/dogen.in")
configure_file(${doxy_template} ${stage_doxygen_dir}/dogen.doxy)
message(STATUS "Transformed ${doxy_template}.")

set(doxy_css "${CMAKE_CURRENT_SOURCE_DIR}/doxygen/doxygen-awesome.css")
file(COPY ${doxy_css} DESTINATION ${stage_doxygen_dir}/)
message(STATUS "Transformed ${doxy_css}.")

set(main_page_template "${CMAKE_CURRENT_SOURCE_DIR}/doxygen/mainpage.dox.in")
configure_file(${main_page_template} ${stage_doxygen_dir}/dox/mainpage.dox)
message(STATUS "Transformed ${main_page_template}.")

set(htaccess_template "${CMAKE_CURRENT_SOURCE_DIR}/doxygen/htaccess")
configure_file(${htaccess_template} ${stage_doxygen_dir}/.htaccess)
message(STATUS "Transformed ${htaccess_template}.")
