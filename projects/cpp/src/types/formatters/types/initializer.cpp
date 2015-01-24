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
    rg.register_default_facet_settings(traits::facet_id(), default_settings);
}

void initialise_class_header_formatter(registrar& rg) {
    formatter_settings default_settings;
    default_settings.enabled(true);

    const auto id(traits::types_formatter_id());
    rg.register_default_formatter_settings(id, default_settings);
    rg.register_formatter(std::make_shared<class_header_formatter>());
}

void register_field_definitions() {
    auto& reg(dynamic::workflow::registrar());

    using fd = field_definitions;
    reg.register_field_definition(fd::enabled());
    reg.register_field_definition(fd::directory());
    reg.register_field_definition(fd::postfix());

    using chf = fd::class_header_formatter;
    reg.register_field_definition(chf::enabled());
    reg.register_field_definition(chf::postfix());
    reg.register_field_definition(chf::file_name());

    using cif = fd::class_implementation_formatter;
    reg.register_field_definition(cif::postfix());
    reg.register_field_definition(cif::enabled());

    using ehf = fd::enumeration_header_formatter;
    reg.register_field_definition(ehf::postfix());
    reg.register_field_definition(ehf::enabled());

    using exhf = fd::exception_header_formatter;
    reg.register_field_definition(exhf::postfix());
    reg.register_field_definition(exhf::enabled());

    using nhf = fd::namespace_header_formatter;
    reg.register_field_definition(nhf::postfix());
    reg.register_field_definition(nhf::enabled());

    using vhf = fd::visitor_header_formatter;
    reg.register_field_definition(vhf::postfix());
    reg.register_field_definition(vhf::enabled());
}

void initializer::initialize(registrar& rg) {
    initialise_facet(rg);
    initialise_class_header_formatter(rg);
    register_field_definitions();
}

} } } }
