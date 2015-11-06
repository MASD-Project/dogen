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
#include "dogen/yarn/types/all_model_items_traversal.hpp"
#include "dogen/yarn/types/modules_expander.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("yarn.modules_expander"));

const std::string missing_module("Could not find module: ");

}

namespace dogen {
namespace yarn {

namespace {

class updater {
public:
    updater(intermediate_model& m) : model_(m) { }

private:
    boost::optional<name> containing_module(const name& n);
    void update(element& e);

public:
    void operator()(dogen::yarn::object& o) { update(o); }
    void operator()(dogen::yarn::enumeration& e) { update(e); }
    void operator()(dogen::yarn::primitive& p) { update(p); }
    void operator()(dogen::yarn::module& m) { update(m); }
    void operator()(dogen::yarn::concept& c) { update(c); }

public:
    intermediate_model& model_;
};

boost::optional<name> updater::containing_module(const name& n) {
    if (n.location().original_model_name().empty() ||
        n.simple() == model_.name().location().original_model_name()) {
        BOOST_LOG_SEV(lg, debug) << "Type has no containing module: "
                                 << n.qualified();
        return boost::optional<name>();
    }

    // FIXME: use builder.
    name module_n;
    module_n.location().original_model_name(n.location().original_model_name());
    module_n.location().external_module_path(
        n.location().external_module_path());

    if (n.location().internal_module_path().empty()) {
        module_n.simple(n.location().original_model_name());
    } else {
        module_n.simple(n.location().internal_module_path().back());
        module_n.location().internal_module_path(
            n.location().internal_module_path());
        module_n.location().internal_module_path().pop_back();
    }

    const auto i(model_.modules().find(module_n));
    if (i != model_.modules().end()) {
        i->second.members().push_back(n);
        return module_n;
    }

    BOOST_LOG_SEV(lg, debug) << "Could not find containing module: "
                             << module_n.qualified();
    return boost::optional<name>();;
}

void updater::update(element& e) {
    e.containing_module(containing_module(e.name()));

    if (!e.containing_module())
        return;

    auto i(model_.modules().find(*e.containing_module()));
    if (i == model_.modules().end()) {
        const auto sn(e.containing_module()->simple());
        BOOST_LOG_SEV(lg, error) << missing_module << sn;
        BOOST_THROW_EXCEPTION(expansion_error(missing_module + sn));
    }

    BOOST_LOG_SEV(lg, debug) << "Adding type to module. Type: '"
                             << e.name().qualified()
                             << "' Module: '" << i->first.qualified();
    i->second.members().push_back(e.name());
}

}

void modules_expander::expand(intermediate_model& m) const {
    updater g(m);
    yarn::all_model_items_traversal(m, g);
}

} }
