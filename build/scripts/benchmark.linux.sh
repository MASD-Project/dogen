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

# Script inspired by https://gist.github.com/peterjmit/3864743

#
# Number of repeats
#
repeats="$1"
shift
if [[ "x${repeats}" = "x" ]]; then
    echo "Number of repeats not supplied." >&2
    exit 1;
fi

output_file="$1"
shift
if [[ "x${output_file}" = "x" ]]; then
    echo "Output file not supplied." >&2
    exit 1;
fi

#
# Command to benchmark
#
target="$*"
if [[ "x${target}" = "x" ]]; then
    echo "Target not supplied." >&2
    exit 1;
fi

#
# Add header
#
echo "elapsed_real_time, filesystem_inputs, filesystem_outputs, max_rss, avg_rss, avg_total_memory, avg_unshared_memory, avg_shared_memory, total_page_faults, total_soft_page_faults" > ${output_file}

#
# Benchmark loop
#
format="%e, %I, %O, %M, %t, %K, %D, %X, %F, %R"
for (( i = 1; i <= ${repeats} ; i++ ))
do
    /usr/bin/time -f "${format}" -o ${output_file} -a ${target} > /dev/null 2>&1
done;
