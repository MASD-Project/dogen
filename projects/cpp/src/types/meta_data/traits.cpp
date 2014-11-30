/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#include "dogen/cpp/types/meta_data/traits.hpp"

namespace dogen {
namespace cpp {
namespace meta_data {

const std::string traits::bool_true("true");
const std::string traits::bool_false("false");

const std::string traits::enabled("cpp.enabled");
const std::string traits::split_project("cpp.split_project");
const std::string traits::source_directory("cpp.source_directory");
const std::string traits::include_directory("cpp.include_directory");
const std::string traits::header_file_extension("cpp.header_file_extension");
const std::string traits::implementation_file_extension(
    "cpp.implementation_file_extension");
const std::string traits::enable_facet_folders("cpp.enable_facet_folders");
const std::string traits::enable_unique_file_names(
    "cpp.enable_unique_file_names");

const std::string traits::facet::enabled("enabled");
const std::string traits::facet::directory("directory");
const std::string traits::facet::postfix("postfix");

} } }
