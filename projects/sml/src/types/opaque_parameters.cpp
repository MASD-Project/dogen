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
#include "dogen/sml/types/opaque_parameters.hpp"

namespace dogen {
namespace om {

const std::string opaque_parameters::odb_pragma("ODB_PRAGMA");
const std::string opaque_parameters::comment("COMMENT");
const std::string opaque_parameters::bool_true("true");
const std::string opaque_parameters::bool_false("false");
const std::string opaque_parameters::cpp::type::family("cpp.type.family");
const std::string opaque_parameters::cpp::domain::status("cpp.domain.status");
const std::string opaque_parameters::cpp::domain::
requires_manual_default_constructor(
    "cpp.domain.requires_manual_default_constructor");
const std::string opaque_parameters::cpp::domain::
requires_manual_move_constructor("cpp.domain.requires_manual_move_constructor");
const std::string opaque_parameters::cpp::domain::header::file_name(
    "cpp.domain.header.file_name");
const std::string opaque_parameters::cpp::domain::header::is_system(
    "cpp.domain.header.is_system");
const std::string opaque_parameters::cpp::hash::standard::status(
    "cpp.hash.standard.status");
const std::string opaque_parameters::cpp::hash::standard::header::file_name(
    "cpp.hash.standard.header.file_name");
const std::string opaque_parameters::cpp::hash::standard::header::is_system(
    "cpp.hash.standard.header.is_system");
const std::string opaque_parameters::cpp::serialization::boost::status(
    "cpp.serialization.boost.status");
const std::string opaque_parameters::cpp::serialization::boost::header::
file_name("cpp.serialization.boost.header.file_name");
const std::string opaque_parameters::cpp::serialization::boost::header::
is_system("cpp.serialization.boost.header.is_system");
const std::string opaque_parameters::cpp::io::status("cpp.io.status");
const std::string opaque_parameters::cpp::io::header::file_name(
    "cpp.io.header.file_name");
const std::string opaque_parameters::cpp::io::header::is_system(
    "cpp.io.header.is_system");

} }
