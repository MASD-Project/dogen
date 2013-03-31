/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2013 Kitanda <info@kitanda.co.uk>
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
#include "dogen/cpp/types/dependency_extractor.hpp"

namespace {

const std::string empty;
const std::string primitive_model("primitive_model");
const std::string bool_type("bool");
const std::string double_type("double");
const std::string float_type("float");

}

namespace dogen {
namespace cpp {

void dependency_extractor::
recurse_nested_qnames(const sml::nested_qname& nqn,
    dependency_details& dd, bool& is_pointer) const {

    const auto qn(nqn.type());
    if (is_pointer)
        dd.forward_decls().insert(qn);
    else
        dd.names().insert(qn);

    is_pointer = false;
    if (qn.meta_type() == sml::meta_types::pod) {
        const auto i(pods_.find(qn));
        if (i != pods_.end()) {
            const auto pt(i->second.pod_type());
            const auto is_ac(pt == sml::pod_types::associative_container);
            if (is_ac && nqn.children().size() >= 1)
                dd.keys().insert(nqn.children().front().type());
            is_pointer = pt == sml::pod_types::smart_pointer;
        }
    }

    if (qn.type_name() == bool_type || qn.type_name() == double_type ||
        qn.type_name() == float_type)
        dd.requires_stream_manipulators(true);
    else if (qn.type_name() == std_.type(std_types::string))
        dd.has_std_string(true);
    else if (qn.type_name() == boost_.type(boost_types::variant))
        dd.has_variant(true);
    else if (qn.type_name() == std_.type(std_types::pair))
        dd.has_std_pair(true);

    for (const auto c : nqn.children())
        recurse_nested_qnames(c, dd, is_pointer);
}

dependency_details dependency_extractor::extract(const sml::pod& p) const {
    dependency_details r;

    if (p.parent_name())
        r.names().insert(*p.parent_name());

    r.is_parent(p.is_parent());
    r.is_child(p.parent_name());
    r.leaves().insert(p.leaves().begin(), p.leaves().end());

    for (const auto prop : p.properties()) {
        const auto nqn(prop.type_name());
        bool is_pointer(nqn.is_pointer());
        recurse_nested_qnames(nqn, r, is_pointer);
    }

    for (const auto& n : r.names()) {
        if (r.forward_decls().find(n) != r.forward_decls().end())
            r.forward_decls().erase(n);
    }

    return r;
}

} }
