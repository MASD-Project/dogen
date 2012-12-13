# -*- mode: ruby; tab-width: 4; indent-tabs-mode: nil -*-
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
path_to_executable = '../../bin/dogen'
if (!File.exist?(path_to_executable))
    puts "error: executable not found: #{path_to_executable}"
    exit 1
end

options = '--help'
output = `#{path_to_executable} #{options}` ; result = $?
if result != 0
    puts "error: command returned non-zero status: #{result}"
    exit 1
end

expected = 'Output directory for C++ include files.'
if output.index(expected)
    puts "test executed successfully."
    exit 0
end

puts "error: expected string not found: #{expected}"
exit 1
