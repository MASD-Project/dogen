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

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("yarn.name_builder"));


const std::string dot(".");
const std::string start_component("<");
const std::string end_component(">");
const std::string empty_type_name("Type name is empty.");
const std::string empty_model_name("Model name is empty.");
const std::string unexpected_type_name(
    "Type name supplied when building model name: ");
const std::string empty_internal_module_path("Internal module path is empty.");

inline void add_component_markers(std::ostream& s, const std::string& c) {
    if (c.empty())
        return;

    s << start_component << c << end_component;
}

}

namespace dogen {
namespace yarn {

name_builder::name_builder(const bool building_model_name)
    : building_model_name_(building_model_name) { }

void name_builder::create_qualified_name() {
    const auto& l(name_.location());

    std::ostringstream s;
    for (const auto& m : l.external_module_path())
        add_component_markers(s, m);

    for (const auto& m : l.model_module_path())
        add_component_markers(s, m);

    if (!building_model_name_) {
        for (const auto& m : l.internal_module_path())
            add_component_markers(s, m);

        add_component_markers(s, name_.simple());
    }

    name_.qualified(s.str());
    BOOST_LOG_SEV(lg, debug) << "Created qualified name: " << name_.qualified();
}

void name_builder::add_model_name(const std::string& mn) {
    if (mn.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_model_name;
        BOOST_THROW_EXCEPTION(building_error(empty_model_name));
    }

    name_.location().original_model_name(mn);

    using utility::string::splitter;
    name_.location().model_module_path(splitter::split_scoped(mn, dot));

    if (building_model_name_)
        name_.simple(*name_.location().model_module_path().rbegin());

    BOOST_LOG_SEV(lg, debug) << "Added original model name: " << mn;
}

void name_builder::add_type_name(const std::string& tn) {
    if (tn.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_type_name;
        BOOST_THROW_EXCEPTION(building_error(empty_type_name));
    }

    if (building_model_name_) {
        BOOST_LOG_SEV(lg, error) << unexpected_type_name + tn;
        BOOST_THROW_EXCEPTION(building_error(unexpected_type_name + tn));
    }
    name_.simple(tn);

    BOOST_LOG_SEV(lg, debug) << "Added type name: " << tn;
}

void name_builder::add_external_module_path(const std::string& epp) {
    if (epp.empty())
        return;

    using utility::string::splitter;
    name_.location().external_module_path(splitter::split_scoped(epp));
}

void name_builder::add_internal_module_path(const std::string& ipp) {
    if (ipp.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_internal_module_path;
        BOOST_THROW_EXCEPTION(building_error(empty_internal_module_path));
    }

    using utility::string::splitter;
    name_.location().external_module_path(splitter::split_scoped(ipp));
}

name name_builder::build() {
    create_qualified_name();
    return name_;
}

} }
