#!/bin/bash
#
# Copyright (C) 2012-2022 Marco Craveiro <marco.craveiro@gmail.com>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be  useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
# MA 02110-1301, USA.
#
cpp_ref_impl_input_location="https://github.com/MASD-Project/cpp_ref_impl/archive/master.zip"
cpp_ref_impl_output_location="${RUNNER_TEMP}/cpp_ref_impl.zip"
cpp_ref_impl_extract_dir="${GITHUB_WORKSPACE}/../.."
curl -L -o ${cpp_ref_impl_output_location} ${cpp_ref_impl_input_location}
unzip -q ${cpp_ref_impl_output_location} -d ${cpp_ref_impl_extract_dir}

frozen_input_location="https://github.com/MASD-Project/frozen/archive/master.zip"
frozen_output_location="${RUNNER_TEMP}/frozen.zip"
frozen_extract_dir="${GITHUB_WORKSPACE}/../.."
curl -L -o ${frozen_output_location} ${frozen_input_location}
unzip -q ${frozen_output_location} -d ${frozen_extract_dir}

csharp_ref_impl_input_location="https://github.com/MASD-Project/csharp_ref_impl/archive/master.zip"
csharp_ref_impl_output_location="${RUNNER_TEMP}/csharp_ref_impl.zip"
csharp_ref_impl_extract_dir="${GITHUB_WORKSPACE}/../.."
curl -L -o ${csharp_ref_impl_output_location} ${csharp_ref_impl_input_location}
unzip -q ${csharp_ref_impl_output_location} -d ${csharp_ref_impl_extract_dir}
