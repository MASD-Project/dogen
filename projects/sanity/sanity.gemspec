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
# coding: utf-8
lib = File.expand_path('../lib', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 'sanity/version'

Gem::Specification.new do |spec|
    spec.name = "sanity"
    spec.version = Sanity::VERSION
    spec.authors = ["Marco Craveiro"]
    spec.email = ["marco.craveiro@gmail.com"]
    spec.summary = %Q{Dogen sanity spec scripts}
    spec.description = %Q{Sanity performs basic checks on a Dogen binary.}

    spec.homepage = "https://github.com/kitanda/dogen"
    spec.license = "GPLv3"
    spec.files = `git ls-files`.split($/)
    spec.executables = spec.files.grep(%r{^bin/}) { |f| File.basename(f) }
    spec.test_files = spec.files.grep(%r{^(test|spec|features)/})
    spec.require_paths = ["lib"]

    spec.add_development_dependency "bundler", "~> 1.5"
    spec.add_development_dependency "rake"
end
