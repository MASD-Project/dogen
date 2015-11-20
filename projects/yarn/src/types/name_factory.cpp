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

const std::string empty_internal_module_path(
    "Internal module path cannot be empty.");

}

namespace dogen {
namespace yarn {

name name_factory::build_model_name(const std::string& model_name,
    const std::string& external_module_path) const {
    name_builder b;
    b.simple_name_contributes_to_qualifed_name(false);
    b.infer_simple_name_from_model_name(true);
    b.model_name(model_name);

    if (!external_module_path.empty())
        b.external_module_path(external_module_path);

    return b.build();
}

name name_factory::build_element_name(const std::string& simple_name) const {
    name_builder b;
    b.compute_qualifed_name(false); // FIXME
    b.simple_name(simple_name);
    return b.build();
}

name name_factory::build_element_name(const std::string& model_name,
    const std::string& simple_name) const {

    name_builder b;
    b.compute_qualifed_name(false); // FIXME
    b.simple_name(simple_name);
    b.model_name(model_name);
    return b.build();
}

name name_factory::build_element_in_model(const name& model_name,
    const std::string& simple_name) const {

    yarn::name n;
    n.simple(simple_name);

    const auto& l(model_name.location());
    n.location().original_model_name(l.original_model_name());
    // n.location().model_module_path(l.model_module_path());
    n.location().external_module_path(l.external_module_path());

    // FIXME: generate qualified name commented out for now
    // name_builder b(n);
    // return b.build();
    return n;
}

name name_factory::build_element_in_model(const name& model_name,
    const std::string& simple_name,
    const std::list<std::string>& internal_module_path) const {

    yarn::name n;
    n.simple(simple_name);

    const auto& l(model_name.location());
    n.location().original_model_name(l.original_model_name());
    // n.location().model_module_path(l.model_module_path());
    n.location().external_module_path(l.external_module_path());
    n.location().internal_module_path(internal_module_path);

    // FIXME: generate qualified name commented out for now
    // name_builder b(n);
    // return b.build();
    return n;
}

name name_factory::build_element_in_module(const name& module_name,
    const std::string& simple_name) const {
    yarn::name n;
    n.simple(simple_name);

    const auto& l(module_name.location());
    n.location().original_model_name(l.original_model_name());
    // n.location().model_module_path(l.model_module_path());
    n.location().external_module_path(l.external_module_path());

    auto pp(l.internal_module_path());
    pp.push_back(module_name.simple());
    n.location().internal_module_path(pp);

    // FIXME:
    // name_builder b(n);
    // return b.build();
    return n;
}

name name_factory::build_module_name(const name& model_name,
    const std::list<std::string>& internal_module_path) const {

    if (internal_module_path.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_internal_module_path;
        BOOST_THROW_EXCEPTION(building_error(empty_internal_module_path));
    }

    yarn::name n;
    n.simple(internal_module_path.back());

    const auto& l(model_name.location());
    n.location().original_model_name(l.original_model_name());
    // n.location().model_module_path(l.model_module_path());
    n.location().external_module_path(l.external_module_path());

    auto ipp(internal_module_path);
    ipp.pop_back();
    n.location().internal_module_path(ipp);

    return n;
}

name name_factory::build_module_name(const name& model_name,
    const std::string& module_name,
    const std::list<std::string>& internal_module_path) const {

    yarn::name n;
    n.simple(module_name);

    const auto& l(model_name.location());
    n.location().original_model_name(l.original_model_name());
    // n.location().model_module_path(l.model_module_path());
    n.location().external_module_path(l.external_module_path());
    n.location().internal_module_path(internal_module_path);

    return n;
}

name name_factory::build_combined_element_name(const name& model_name,
    const name& partial_element_name,
    const bool populate_model_name_if_blank) const {
    name r(partial_element_name);

    const auto& l(model_name.location());
    if (populate_model_name_if_blank &&
        r.location().original_model_name().empty()) {
        r.location().original_model_name(l.original_model_name());
        // r.location().model_module_path(l.model_module_path());
    }
    r.location().external_module_path(l.external_module_path());

    return r;
}

name name_factory::build_promoted_module_name(const name& model_name,
    const name& element_name) const {
    name r;
    r.simple(element_name.simple());

    const auto& l(element_name.location());
    if (!l.internal_module_path().empty()) {
        r.location().original_model_name(l.internal_module_path().front());
        // r.location().model_module_path().push_back(
        // l.internal_module_path().front());
    }
    r.location().external_module_path(
        model_name.location().external_module_path());
    return r;
}

} }
