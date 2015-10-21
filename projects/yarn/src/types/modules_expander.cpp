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
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/expansion_error.hpp"
#include "dogen/yarn/types/modules_expander.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("yarn.modules_expander"));

const std::string missing_module("Could not find module: ");

}

namespace dogen {
namespace yarn {

boost::optional<name> containing_module(model& m, const name& n) {
    if (n.location().original_model_name().empty() ||
        n.simple() == m.name().location().original_model_name()) {
        BOOST_LOG_SEV(lg, debug) << "Type has no containing module: "
                                 << n.qualified();
        return boost::optional<name>();
    }

    // FIXME: use builder.
    name module_n;
    const auto omn(n.location().original_model_name());
    module_n.location().original_model_name(n.location().original_model_name());

    if (n.location().internal_module_path().empty()) {
        module_n.simple(n.location().original_model_name());
    } else {
        module_n.simple(n.location().internal_module_path().back());
        module_n.location().internal_module_path(
            n.location().internal_module_path());
        module_n.location().internal_module_path().pop_back();
    }

    const auto i(m.modules().find(module_n));
    if (i != m.modules().end())
        return module_n;

    BOOST_LOG_SEV(lg, debug) << "Could not find containing module: "
                             << module_n.qualified();
    return boost::optional<name>();;
}

template<typename AssociativeContainerOfContainable>
inline void update_containing_module(model& m,
    AssociativeContainerOfContainable& c) {
    for (auto& pair : c) {
        auto& s(pair.second);
        s.containing_module(containing_module(m, s.name()));

        if (!s.containing_module())
            continue;

        auto i(m.modules().find(*s.containing_module()));
        if (i == m.modules().end()) {
            const auto sn(s.containing_module()->simple());
            BOOST_LOG_SEV(lg, error) << missing_module << sn;
            BOOST_THROW_EXCEPTION(expansion_error(missing_module + sn));
        }

        BOOST_LOG_SEV(lg, debug) << "Adding type to module. Type: '"
                                 << s.name().qualified()
                                 << "' Module: '" << i->first.qualified();
        i->second.members().push_back(s.name());
    }
}

void modules_expander::expand_containing_module(model& m) const {
    update_containing_module(m, m.objects());
    update_containing_module(m, m.primitives());
    update_containing_module(m, m.enumerations());
    update_containing_module(m, m.concepts());
    update_containing_module(m, m.modules());
}

void modules_expander::expand(model& m) const {
    expand_containing_module(m);
}

} }
