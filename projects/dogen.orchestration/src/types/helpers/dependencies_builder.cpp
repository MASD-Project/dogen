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

#include <ostream>
#include <boost/throw_exception.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen.identification/types/entities/physical_meta_id.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/io/list_io.hpp"
#include "dogen.identification/io/entities/logical_name_io.hpp"
#include "dogen.identification/hash/entities/logical_meta_physical_id_hash.hpp"
#include "dogen.physical/io/entities/inclusion_directives_io.hpp"
#include "dogen.text.cpp/io/formattables/directive_group_io.hpp"
#include "dogen.orchestration/types/helpers/building_error.hpp"
#include "dogen.orchestration/types/helpers/dependencies_builder.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("text.cpp.formattables.dependencies_builder"));

const auto empty_list = std::list<std::string> {};
const std::string pair_type("pair");
const std::string string_type("string");
const std::string variant_type("variant");
const std::string ptree_type("ptree");
const std::string path_type("path");
const std::string date_type("date");
const std::string ptime_type("ptime");

const std::string open_system("<");
const std::string close_system(">");
const std::string open_user("\"");
const std::string close_user("\"");

const std::string empty_directive("Cannot add empty include directive.");
const std::string name_not_found("Cannot find name: ");
const std::string archetype_not_found("Cannot find archetype name: ");

}

namespace dogen::orchestration::helpers {

using identification::entities::logical_name;

dependencies_builder::dependencies_builder(const std::unordered_map<
    identification::entities::logical_meta_physical_id,
    physical::entities::inclusion_directives>& ids,
    const std::unordered_set<
    identification::entities::logical_meta_physical_id>&
    enabled_archetype_for_element) :
    inclusion_directives_(ids),
    enabled_archetype_for_element_(enabled_archetype_for_element) {}

boost::optional<physical::entities::inclusion_directives> dependencies_builder::
get_directive_group(const logical_name& n, const std::string& archetype) const {
    identification::entities::logical_meta_physical_id id;
    id.logical_id(n.id());
    id.physical_meta_id(identification::entities::physical_meta_id(archetype));

    const auto i(inclusion_directives_.find(id));
    if (i == inclusion_directives_.end())
        return boost::optional<physical::entities::inclusion_directives>();

    return i->second;
}

bool dependencies_builder::
is_enabled(const logical_name& n, const std::string& archetype) const {
    using namespace identification::entities;
    logical_id lid(n.qualified().dot());
    physical_meta_id pmid(archetype);
    logical_meta_physical_id ea(lid, pmid);
    const auto i(enabled_archetype_for_element_.find(ea));
    const bool is_disabled(i == enabled_archetype_for_element_.end());
    return !is_disabled;
}

void dependencies_builder::add(const std::string& inclusion_directive) {
    BOOST_LOG_SEV(lg, debug) << "Adding directive: " << inclusion_directive;

    if (inclusion_directive.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_directive;
        BOOST_THROW_EXCEPTION(building_error(empty_directive));
    }
    dependencies_.push_back(inclusion_directive);
}

void dependencies_builder::add_as_system(const std::string& directive) {
    std::ostringstream os;
    os << open_system << directive << close_system;
    add(os.str());
}

void dependencies_builder::add_as_user(const std::string& directive) {
    std::ostringstream os;
    os << open_user << directive << close_user;
    add(os.str());
}

void dependencies_builder::
add(const std::list<std::string>& inclusion_directives) {
    for (const auto& id : inclusion_directives)
        add(id);
}

void
dependencies_builder::add(const logical_name& n, const std::string& archetype) {
    BOOST_LOG_SEV(lg, debug) << "Adding name: " << n.qualified().dot();

    if (!is_enabled(n, archetype)) {
        BOOST_LOG_SEV(lg, trace) << "Archetype not enabled: " << archetype;
        return;
    }

    const auto dg(get_directive_group(n, archetype));
    if (dg) {
        add(dg->primary());
        add(dg->secondary());
        BOOST_LOG_SEV(lg, trace) << "Adding inclusion directive group: " << *dg;
    } else
        BOOST_LOG_SEV(lg, trace) << "Could not find an inclusion directive.";
}

void dependencies_builder::
add(const boost::optional<logical_name>& n, const std::string& archetype) {
    if (!n)
        return;

    add(*n, archetype);
}

void dependencies_builder::add(const std::list<logical_name>& names,
    const std::string& archetype) {
    for (const auto& n : names)
        add(n, archetype);
}


void dependencies_builder::add(const logical_name& n,
    const identification::entities::physical_meta_id& archetype) {
    return add(n, archetype.value());
}

void dependencies_builder::
add(const boost::optional<logical_name>& n,
    const identification::entities::physical_meta_id& archetype) {
    return add(n, archetype.value());
}

void dependencies_builder::
add(const std::list<logical_name>& names,
    const identification::entities::physical_meta_id& archetype) {
    return add(names, archetype.value());
}

std::list<std::string> dependencies_builder::build() {
    BOOST_LOG_SEV(lg, debug) << "Built inclusion dependencies for archetype.";
    BOOST_LOG_SEV(lg, debug) << "Result: " << dependencies_;

    return dependencies_;
}

}
