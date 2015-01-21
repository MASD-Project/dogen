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
#include "dogen/dynamic/types/workflow.hpp"
#include "dogen/formatters/types/field_definitions.hpp"
#include "dogen/formatters/types/initializer.hpp"

namespace dogen {
namespace formatters {

void initializer::initialize() {
    auto& rg(dynamic::workflow::registrar());

    rg.register_field_definition(field_definitions::copyright_notices());
    rg.register_field_definition(field_definitions::licence_name());
    rg.register_field_definition(field_definitions::modeline_group_name());
    rg.register_field_definition(field_definitions::generate_preamble());

    using cgm = field_definitions::code_generation_marker;
    rg.register_field_definition(cgm::add_date_time());
    rg.register_field_definition(cgm::add_warning());
    rg.register_field_definition(cgm::message());
}

} }
