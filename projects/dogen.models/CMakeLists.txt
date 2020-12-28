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
if (DOGEN_CLI_EXECUTABLE)
    #
    # Input models for generation
    #
    set(prefix "dogen")
    set(models ${prefix})
    set(models ${models} ${prefix}.physical)
    set(models ${models} ${prefix}.cli)
    set(models ${models} ${prefix}.dia)
    set(models ${models} ${prefix}.org)
    set(models ${models} ${prefix}.tracing)
    set(models ${models} ${prefix}.codec)
    set(models ${models} ${prefix}.codec.dia)
    set(models ${models} ${prefix}.text)
    set(models ${models} ${prefix}.logical)
    set(models ${models} ${prefix}.templating)
    set(models ${models} ${prefix}.orchestration)
    set(models ${models} ${prefix}.utility)
    set(models ${models} ${prefix}.variability)
    set(models ${models} ${prefix}.relational)
    set(models ${models} ${prefix}.identification)
endif()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/org)
