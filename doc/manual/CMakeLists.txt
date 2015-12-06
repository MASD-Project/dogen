# -*- mode: cmake; tab-width: 4; indent-tabs-mode: nil -*-
#
# Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
if (WITH_LATEX)
    if(NOT IS_DIRECTORY ${stage_doc_dir})
        file(MAKE_DIRECTORY ${stage_doc_dir})
    endif()

    set(manual_dir ${stage_doc_dir}/manual)
    if(NOT IS_DIRECTORY ${manual_dir})
        file(MAKE_DIRECTORY ${manual_dir})
    endif()
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/images DESTINATION ${manual_dir}/)

    set(all_files "")
    file(GLOB all_files RELATIVE
        "${CMAKE_CURRENT_SOURCE_DIR}/" "${CMAKE_CURRENT_SOURCE_DIR}/*.sty")
    foreach(file ${all_files})
        file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/${file} DESTINATION ${manual_dir})
    endforeach()

    file(GLOB all_files RELATIVE
        "${CMAKE_CURRENT_SOURCE_DIR}/" "${CMAKE_CURRENT_SOURCE_DIR}/*.tex")
    foreach(file ${all_files})
        get_filename_component(file_name ${file} NAME_WE)
        if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${file_name}.bib)
          file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/${file_name}.bib
            DESTINATION ${manual_dir})
        endif()
        configure_file(${CMAKE_CURRENT_SOURCE_DIR}/${file} ${manual_dir}/${file})

        message(STATUS "${manual_dir}/${file_name}.pdf")
        add_custom_target(manual ALL
          COMMENT "Generating manual ${file}"
          DEPENDS ${manual_dir}/${file}
          COMMAND ${PDFLATEX_COMMAND} ${file}
          COMMAND bibtex ${file_name}
          COMMAND ${PDFLATEX_COMMAND} ${file}
          OUTPUT ${manual_dir}/${file_name}.pdf
          WORKING_DIRECTORY ${manual_dir})

        add_dependencies(latex_docs manual)
    endforeach()
endif()
