/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
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
#include "dogen/quilt.cpp/types/formattables/name_builder.hpp"

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
namespace quilt {
namespace cpp {
namespace formattables {

std::list<std::string> name_builder::
namespace_list(const yarn::name& n) const {
    const auto& l(n.location());
    std::list<std::string> r(l.external_modules());

    for (const auto& m : l.model_modules())
        r.push_back(m);

    // All modules in the module path contribute to namespaces.
    for (const auto& m : l.internal_modules())
        r.push_back(m);

    /* if the name belongs to the model's module, we need to remove the
     * module's simple name from the module path (it is in both the
     * module path and it is also the module's simple name).
     */
    const bool no_internal_modules(l.internal_modules().empty());
    const bool has_model_modules(!l.model_modules().empty());
    const bool is_model_name(no_internal_modules && has_model_modules &&
        n.simple() == l.model_modules().back());

    if (is_model_name)
        r.pop_back();

    return r;
}

std::string name_builder::
qualified_name(const yarn::name& n) const {
    std::list<std::string> l(namespace_list(n));
    l.push_back(n.simple());
    return boost::algorithm::join(l, scope_operator);
}

void name_builder::
complete_name(const yarn::nested_name& nn, std::string& complete_name) const {
    const auto qualified_name(this->qualified_name(nn.parent()));
    const auto& children(nn.children());
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

        this->complete_name(c, complete_name);
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

} } } }
