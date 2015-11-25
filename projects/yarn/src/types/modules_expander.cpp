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
#include <boost/algorithm/string.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/name_factory.hpp"
#include "dogen/yarn/types/name_builder.hpp"
#include "dogen/yarn/types/expansion_error.hpp"
#include "dogen/yarn/types/elements_traversal.hpp"
#include "dogen/yarn/types/modules_expander.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("yarn.modules_expander"));

const std::string separator(".");
const std::string missing_module("Could not find module: ");

}

namespace dogen {
namespace yarn {

namespace {

class internal_module_path_builder {
private:
    void process(const name& n);

public:
    void operator()(dogen::yarn::object& o) { process(o.name()); }
    void operator()(dogen::yarn::enumeration& e) { process(e.name()); }
    void operator()(dogen::yarn::primitive& p) { process(p.name()); }
    void operator()(dogen::yarn::module& m) { process(m.name()); }
    void operator()(dogen::yarn::concept& c) { process(c.name()); }

public:
    const std::unordered_map<std::string, std::list<std::string>>&
    result();

public:
    std::unordered_map<std::string, std::list<std::string>>
        distinct_internal_module_paths_;
};

void internal_module_path_builder::process(const name& n) {
    auto ipp(n.location().internal_module_path());
    while (!ipp.empty()) {
        const std::string key(boost::join(ipp, separator));
        distinct_internal_module_paths_.insert(std::make_pair(key, ipp));
        ipp.pop_back();
    }
}

const std::unordered_map<std::string, std::list<std::string>>&
    internal_module_path_builder::result() {
    return distinct_internal_module_paths_;
}

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
    BOOST_LOG_SEV(lg, debug) << "Finding containing module for: "
                             << n.qualified();

    const bool in_global_namespace(n.location().model_module_path().empty());
    if (in_global_namespace) {
        BOOST_LOG_SEV(lg, debug) << "Type is in global module so, it has"
                                 << " no containing module yet. Type: "
                                 << n.qualified();
        return boost::optional<name>();
    }

    const bool at_model_level(n.location().internal_module_path().empty());
    const auto mn(n.location().model_module_path().back());
    if (at_model_level && n.simple() == mn) {
        BOOST_LOG_SEV(lg, debug) << "Type is a model module, so containing "
                                 << "module will be handled later. Type: "
                                 << n.qualified();
        return boost::optional<name>();
    }

    name_builder b;
    if (!n.location().external_module_path().empty())
        b.external_module_path(n.location().external_module_path());

    auto imp(n.location().internal_module_path());
    if (imp.empty())
        b.simple_name(mn);
    else {
        b.model_module_path(n.location().model_module_path());
        b.simple_name(imp.back());
        imp.pop_back();
        if (!imp.empty())
            b.internal_module_path(imp);
    }

    const auto module_n(b.build());
    const auto i(model_.modules().find(module_n.qualified()));
    if (i != model_.modules().end()) {
        i->second.members().push_back(n);
        BOOST_LOG_SEV(lg, debug) << "Containing module: "
                                 << module_n.qualified();
        return module_n;
    }

    BOOST_LOG_SEV(lg, debug) << "Could not find containing module: "
                             << module_n.qualified();
    return boost::optional<name>();
}

void updater::update(element& e) {
    e.containing_module(containing_module(e.name()));

    if (!e.containing_module())
        return;

    auto i(model_.modules().find(e.containing_module()->qualified()));
    if (i == model_.modules().end()) {
        const auto sn(e.containing_module()->simple());
        BOOST_LOG_SEV(lg, error) << missing_module << sn;
        BOOST_THROW_EXCEPTION(expansion_error(missing_module + sn));
    }

    BOOST_LOG_SEV(lg, debug) << "Adding type to module. Type: '"
                             << e.name().qualified()
                             << "' Module: '" << i->first;
    i->second.members().push_back(e.name());
}

}

void modules_expander::create_missing_modules(intermediate_model& m) const {
    internal_module_path_builder b;
    yarn::elements_traversal(m, b);

    for (const auto& pair : b.result()) {
        yarn::name_factory f;
        const auto& ipp(pair.second);
        const auto n(f.build_module_name(m.name(), ipp));
        const auto i(m.modules().find(n.qualified()));
        if (i == m.modules().end()) {
            yarn::module mod;
            mod.name(n);
            mod.origin_type(m.origin_type());
            mod.generation_type(m.generation_type());
            m.modules().insert(std::make_pair(n.qualified(), mod));
        }
    }
}

void modules_expander::expand_containing_module(intermediate_model& m) const {
    updater g(m);
    yarn::elements_traversal(m, g);
}

void modules_expander::expand(intermediate_model& m) const {
    create_missing_modules(m);
    expand_containing_module(m);
}

} }
