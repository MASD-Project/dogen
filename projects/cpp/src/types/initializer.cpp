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
#include "dogen/backend/types/workflow.hpp"
#include "dogen/cpp/types/workflow.hpp"
#include "dogen/cpp/types/field_definitions.hpp"
#include "dogen/cpp/types/formatters/initializer.hpp"
#include "dogen/cpp/types/initializer.hpp"

namespace {

void register_field_definitions() {
    auto& rg(dogen::dynamic::workflow::registrar());
    using fd = dogen::cpp::field_definitions;
    rg.register_field_definitions(fd::all_field_definitions());
}

}

namespace dogen {
namespace cpp {

void initializer::initialize() {
    register_field_definitions();
    formatters::initializer::initialize(workflow::registrar());
    backend::workflow::register_backend(std::make_shared<workflow>());
}

} }
