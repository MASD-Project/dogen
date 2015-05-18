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
#include <sstream>
#include <boost/filesystem/path.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen/cpp/types/formattables/name_builder.hpp"

namespace {

const std::string empty;
const std::string comma(",");
const std::string space(" ");
const std::string less_than("<");
const std::string more_than(">");
const std::string separator("_");
const std::string scope_operator("::");

}

namespace dogen {
namespace cpp {
namespace formattables {

std::list<std::string> name_builder::
namespace_list(const sml::model& m, const sml::qname& qn) const {
    std::list<std::string> r(qn.external_module_path());

    // if there is no model name, it won't contribute to the namespaces.
    if (!qn.model_name().empty())
        r.push_back(qn.model_name());

    // all modules in the module path contribute to namespaces.
    const auto mp(qn.module_path());
    r.insert(r.end(), mp.begin(), mp.end());

    // if the qname belongs to a module, the simple name will
    // contribute to the namespaces (since it is a module).
    const auto i(m.modules().find(qn));
    if (i != m.modules().end())
        r.pop_back();
        // r.push_back(qn.simple_name());

    return r;
}

std::string name_builder::
qualified_name(const sml::model& m, const sml::qname& qn) const {
    std::list<std::string> l(namespace_list(m, qn));
    l.push_back(qn.simple_name());
    return boost::algorithm::join(l, scope_operator);
}

void name_builder::
complete_name(const sml::model& m, const sml::nested_qname& nqn,
    std::string& complete_name) const {
    const auto qualified_name(this->qualified_name(m, nqn.type()));
    const auto& children(nqn.children());
    complete_name += qualified_name;

    auto lambda([&](char c) {
            if (!children.empty()) {
                if (complete_name[complete_name.length() - 1] == c)
                    complete_name += " ";
                complete_name += c;
            }
        });

    lambda('<');
    bool is_first(true);
    for (const auto c : children) {
        if (!is_first)
            complete_name += ", ";

        this->complete_name(m, c, complete_name);
        is_first = false;
    }
    lambda('>');
}

std::string name_builder::identifiable_name(const std::string& n) const {
    std::string r(n);

    boost::replace_all(r, scope_operator, separator);
    boost::replace_all(r, space, separator);
    boost::replace_all(r, comma, empty);
    boost::replace_all(r, less_than, separator);
    boost::replace_all(r, more_than, empty);

    return r;
}

} } }
