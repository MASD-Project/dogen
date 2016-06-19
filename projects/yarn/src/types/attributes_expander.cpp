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
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/unordered_set_io.hpp"
#include "dogen/yarn/types/attributes_expander.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("yarn.attributes_expander"));

}

namespace dogen {
namespace yarn {

bool attributes_expander::
is_circular_dependency(const name& owner, const name_tree& nn) const {

    if (owner == nn.parent())
        return true;

    for (const auto& c : nn.children()) {
        if (is_circular_dependency(owner, c))
            return true;
    }
    return false;
}

std::unordered_set<std::string> attributes_expander::
obtain_top_level_module_names(const intermediate_model& m) const {
    std::unordered_set<std::string> r;
    BOOST_LOG_SEV(lg, debug) << "Obtaining top-level modules for: "
                             << m.name().id();

    for (const auto& pair : m.modules()) {
        const auto& module(pair.second);

        if (!module.contained_by()) {
            BOOST_LOG_SEV(lg, debug) << "Module is not a top-level module: "
                                     << pair.first;
            continue;
        }

        const auto& cm(*module.contained_by());
        if (cm != m.name()) {
            BOOST_LOG_SEV(lg, debug) << "Module is not a top-level module: "
                                     << pair.first
                                     << " containing module: "
                                     << cm.id()
                                     << " model name: " << m.name().id();
        }
        r.insert(module.name().simple());
    }

    BOOST_LOG_SEV(lg, debug) << "Top-level model names for "
                             << m.name().id() << " : "
                             << r;
    return r;
}

void attributes_expander::expand(intermediate_model& m) const {
    const auto tlmn(obtain_top_level_module_names(m));
    const name_tree_parser ntp(tlmn, m.name().location());

    for (auto& pair : m.objects())
        update_attributes(ntp, pair.second);

    for (auto& pair : m.concepts())
        update_attributes(ntp, pair.second);
}

} }
