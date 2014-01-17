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
require_relative "lib/sanity.rb"

def check_parameters argv
  case argv[0]
  when 'upload' || 'download' || 'install' || 'reset'
    @command = argv[0].to_sym
  else
    raise RuntimeError, "bad command: #{argv}."
  end
end

def create_client
  token=`git config --global --get github.token`
  raise RuntimeError, 'Token missing.' if token == nil
  github = Github.new :oauth_token => token.chomp
end

check_parameters ARGV
@gh_client = create_client
