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
#include <memory>
#include "dogen/dynamic/types/workflow.hpp"
#include "dogen/cpp/types/facet_settings.hpp"
#include "dogen/cpp/types/formatters/types/traits.hpp"
#include "dogen/cpp/types/formatters/types/class_header_formatter.hpp"
#include "dogen/cpp/types/formatters/types/field_definitions.hpp"
#include "dogen/cpp/types/formatters/types/initializer.hpp"

namespace {

const std::string default_facet_directory("types");
const std::string default_facet_postfix;

}

namespace dogen {
namespace cpp {
namespace formatters {
namespace types {

void initialise_facet(registrar& rg) {
    facet_settings default_settings;
    default_settings.enabled(true);
    default_settings.directory(default_facet_directory);
    default_settings.postfix(default_facet_postfix);
    rg.register_default_facet_settings(traits::facet_name(), default_settings);
}

void initialise_class_header_formatter(registrar& rg) {
    formatter_settings default_settings;
    default_settings.enabled(true);

    const auto id(traits::class_header_formatter_name());
    rg.register_default_formatter_settings(id, default_settings);
    rg.register_formatter(std::make_shared<class_header_formatter>());
}

void register_field_definitions() {
    auto& rg(dynamic::workflow::registrar());
    rg.register_field_definitions(field_definitions::all_field_definitions());
}

void initializer::initialize(registrar& rg) {
    initialise_facet(rg);
    initialise_class_header_formatter(rg);
    register_field_definitions();
}

} } } }
