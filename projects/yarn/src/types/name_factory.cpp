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
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/string/splitter.hpp"
#include "dogen/yarn/types/building_error.hpp"
#include "dogen/yarn/types/name_builder.hpp"
#include "dogen/yarn/types/name_factory.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("yarn.name_factory"));

const std::string empty_internal_modules("Internal modules cannot be empty.");

}

namespace dogen {
namespace yarn {

name name_factory::build_model_name(const std::string& model_name,
    const std::string& external_modules) const {
    name_builder b(true/*model_name_mode*/);
    b.model_name(model_name);
    b.external_modules(external_modules);
    return b.build();
}

name name_factory::build_element_name(const std::string& simple_name) const {
    name_builder b;
    b.simple_name(simple_name);
    return b.build();
}

name name_factory::build_element_name(const std::string& model_name,
    const std::string& simple_name) const {

    name_builder b;
    b.simple_name(simple_name);
    b.model_name(model_name);
    return b.build();
}

name name_factory::build_element_name(const std::string& simple_name,
    const std::list<std::string>& internal_modules) const {

    yarn::name n;
    n.simple(simple_name);
    n.location().internal_modules(internal_modules);

    name_builder b(n);
    return b.build();
}

name name_factory::build_element_in_model(const name& model_name,
    const std::string& simple_name) const {

    yarn::name n;
    n.simple(simple_name);

    const auto& l(model_name.location());
    n.location().model_modules(l.model_modules());
    n.location().external_modules(l.external_modules());

    name_builder b(n);
    return b.build();
}

name name_factory::build_element_in_model(const name& model_name,
    const std::string& simple_name,
    const std::list<std::string>& internal_modules) const {

    yarn::name n;
    n.simple(simple_name);

    const auto& l(model_name.location());
    n.location().model_modules(l.model_modules());
    n.location().external_modules(l.external_modules());
    n.location().internal_modules(internal_modules);

    name_builder b(n);
    return b.build();
}

name name_factory::build_element_in_module(const name& module_name,
    const std::string& simple_name) const {
    yarn::name n;
    n.simple(simple_name);

    const auto& l(module_name.location());
    n.location().model_modules(l.model_modules());
    n.location().external_modules(l.external_modules());

    auto pp(l.internal_modules());
    pp.push_back(module_name.simple());
    n.location().internal_modules(pp);

    name_builder b(n);
    return b.build();
}

name name_factory::build_module_name(const name& model_name,
    const std::list<std::string>& internal_modules) const {

    if (internal_modules.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_internal_modules;
        BOOST_THROW_EXCEPTION(building_error(empty_internal_modules));
    }

    yarn::name n;
    n.simple(internal_modules.back());

    const auto& l(model_name.location());
    n.location().model_modules(l.model_modules());
    n.location().external_modules(l.external_modules());

    auto ipp(internal_modules);
    ipp.pop_back();
    n.location().internal_modules(ipp);

    name_builder b(n);
    return b.build();
}

name name_factory::build_module_name(const name& model_name,
    const std::string& module_name,
    const std::list<std::string>& internal_modules) const {

    yarn::name n;
    n.simple(module_name);

    const auto& l(model_name.location());
    n.location().model_modules(l.model_modules());
    n.location().external_modules(l.external_modules());
    n.location().internal_modules(internal_modules);

    name_builder b(n);
    return b.build();
}

name name_factory::build_combined_element_name(const name& model_name,
    const name& partial_element_name,
    const bool populate_model_modules_if_blank,
    const bool populate_internal_modules_if_blank) const {
    name n(partial_element_name);

    const auto& l(model_name.location());
    if (populate_model_modules_if_blank &&
        n.location().model_modules().empty()) {
        n.location().model_modules(l.model_modules());
    }

    if (populate_internal_modules_if_blank &&
        n.location().internal_modules().empty()) {
        n.location().internal_modules(l.internal_modules());
    }

    n.location().external_modules(l.external_modules());

    name_builder b(n);
    return b.build();
}

name name_factory::build_promoted_module_name(const name& element_name) const {
    name n;
    n.simple(element_name.simple());

    const auto& l(element_name.location());

    /*
     * We can only promote the internal module to model name if the
     * name does not have any internal modules already.
     */
    if (!l.internal_modules().empty()) {
        auto im(l.internal_modules());
        n.location().model_modules().push_back(im.front());
        im.pop_front();
        n.location().internal_modules(im);
    }

    name_builder b(n);
    return b.build();
}

name name_factory::build_promoted_module_name(const name& model_name,
    const name& element_name) const {
    name n;
    n.simple(element_name.simple());

    const auto& l(element_name.location());
    if (!l.internal_modules().empty()) {
        auto im(l.internal_modules());
        n.location().model_modules().push_back(im.front());
        im.pop_front();
        n.location().internal_modules(im);
    }

    n.location().external_modules(model_name.location().external_modules());

    name_builder b(n);
    return b.build();
}

name name_factory::build_attribute_name(const name& owner_name,
    const std::string& simple_name) const {

    location l(owner_name.location());
    l.element(owner_name.simple());

    name n;
    n.location(l);
    n.simple(simple_name);
    name_builder b(n);
    return b.build();
}

} }
