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
#include "dogen/formatters/types/meta_data/traits.hpp"

namespace dogen {
namespace formatters {
namespace meta_data {

const std::string traits::bool_true("true");
const std::string traits::bool_false("false");

const std::string traits::copyright_holder("copyright");
const std::string traits::licence_name("licence");
const std::string traits::modeline_group_name("modeline_group");
const std::string traits::generate_preamble("generate_preamble");

const std::string traits::code_generation_marker::add_date_time(
    "code_generation_marker.add_date_time");
const std::string traits::code_generation_marker::add_warning(
    "code_generation_marker.add_warning");
const std::string traits::code_generation_marker::message(
    "code_generation_marker.message");

} } }
