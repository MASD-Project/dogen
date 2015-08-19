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
#include "dogen/tack/types/properties_expander.hpp"

namespace dogen {
namespace tack {

std::unordered_set<std::string>
properties_expander::obtain_top_level_module_names(const model& m) const {
    std::unordered_set<std::string> r;

    for (const auto& pair : m.modules()) {
        const auto& module(pair.second);
        if (!module.containing_module())
            r.insert(module.name().simple());
    }
    return r;
}

identifier_parser
properties_expander::make_identifier_parser(const model& m) const {
    const auto tlmn(obtain_top_level_module_names(m));
    const auto& l(m.name().location());
    identifier_parser r(tlmn, l);
    return r;
}

void properties_expander::
expand_property(const identifier_parser& /*ip*/, property& /*p*/) const {
    /*tack::nested_name nn(ip.parse_name(p.unparsed_name()));
      p.type(nn);*/
}

void properties_expander::expand(model& m) const {
    const auto ip(make_identifier_parser(m));
    for (auto& pair : m.objects()) {
        auto& o(pair.second);
        for (auto& p : o.local_properties())
            expand_property(ip, p);
    }
}

} }
