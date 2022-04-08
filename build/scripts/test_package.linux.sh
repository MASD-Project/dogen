#!/bin/bash
#
# Copyright (C) 2012-2016 Marco Craveiro <marco.craveiro@gmail.com>
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
if [[ $# -lt 1 ]]; then
    echo "USAGE: CMAKE_PRESET"
    exit 1
fi
preset="$1"

#
# Root directory for the product.
#
dir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
product_dir=$(readlink -f ${dir}/../..)
echo "* Product directory: ${product_dir}"

#
# Test the package
#
output_dir="${product_dir}/build/output/${preset}";
sudo dpkg -i ${output_dir}/stage/pkg/dogen_*_amd64-applications.deb
cp ${product_dir}/projects/dogen.modeling/org/hello_world.org /tmp
cd /tmp
/usr/bin/dogen.cli --version
/usr/bin/dogen.cli generate -t hello_world.org
