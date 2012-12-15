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
require 'tmpdir'
require 'pathname'

path_to_executable = Pathname.new("../../../MacOS/dogen").realpath
if (!File.exist?(path_to_executable))
    puts "error: executable not found: #{path_to_executable}"
    exit 1
end

path_to_diagram = Pathname.new("hello_world.dia").realpath
Dir.chdir("#{Dir.tmpdir}") do
    options = "--target #{path_to_diagram}"
    output = `#{path_to_executable} #{options}` ; result = $?
    if result != 0
        puts "error: command returned non-zero status: #{result}"
        exit 1
    end

    expected_project_dir = "#{Dir.tmpdir}/hello_world"
    if (!File.exist?(expected_project_dir))
        puts "error: expected directory not found #{expected_project_dir}"
        exit 1
    end
    puts "found project directory #{expected_project_dir}"

    if (Dir[expected_project_dir + '/*'].empty?)
        puts "error: directory is empty: #{expected_project_dir}"
        exit 1
    end
    puts "found files in directory #{expected_project_dir}"

    expected_cpp_files = 6
    found_cpp_files = Dir[expected_project_dir + '/**/*.cpp'].length
    if found_cpp_files != expected_cpp_files
        puts "error: expected to find #{expected_cpp_files} but found #{found_cpp_files} cpp files"
        exit 1
    end
    puts "total cpp files found: #{found_cpp_files}"

    Dir[expected_project_dir + '/**/*.cpp'].each do |path|
        if File.zero?(path)
            puts "error: file is empty #{path}"
            exit 1
        else
            puts "file has content: #{path}"
        end
    end

    expected_hpp_files = 13
    found_hpp_files = Dir[expected_project_dir + '/**/*.hpp'].length
    if found_hpp_files != expected_hpp_files
        puts "error: expected to find #{expected_hpp_files} but found #{found_hpp_files} hpp files"
        exit 1
    end
    puts "total hpp files found: #{found_hpp_files}"

    Dir[expected_project_dir + '/**/*.hpp'].each do |path|
        if File.zero?(path)
            puts "error: file is empty #{path}"
            exit 1
        else
            puts "file has content: #{path}"
        end
    end

    expected_cmake_files = 2
    found_cmake_files = Dir[expected_project_dir + '/**/CMakeLists.txt'].length
    if found_cmake_files != expected_cmake_files
        puts "error: expected to find #{expected_cmake_files} but found #{found_cmake_files} CMake files"
        exit 1
    end
    puts "total CMake files found: #{found_cmake_files}"

    Dir[expected_project_dir + '/**/CMakeLists.txt'].each do |path|
        if File.zero?(path)
            puts "error: file is empty #{path}"
            exit 1
        else
            puts "file has content: #{path}"
        end
    end
end

puts "test executed successfully."
exit 0
