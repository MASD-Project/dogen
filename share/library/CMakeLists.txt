# -*- mode: cmake; cmake-tab-width: 4; indent-tabs-mode: nil -*-
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
if (DOGEN_CLI_EXECUTABLE)
  file(GLOB models "*.org")
  foreach(model ${models})
    set(model_name "")
    get_filename_component(model_name ${model} NAME)
    set(destination_name ${model_name})

    add_custom_target(convert_${model_name}_org
      COMMENT "Converting ${model_name} to org-mode."
      WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
      COMMAND ${DOGEN_CLI_EXECUTABLE} convert
      --source ${model} --destination ${model}
      ${DOGEN_COMMON_OPTIONS})
    add_dependencies(convert_all_org convert_${model_name}_org)
  endforeach()
endif()
