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
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/list_io.hpp"
#include "dogen/annotations/io/scope_types_io.hpp"
#include "dogen/annotations/io/field_definition_io.hpp"
#include "dogen/annotations/types/value_factory.hpp"
#include "dogen/annotations/types/building_error.hpp"
#include "dogen/annotations/types/annotation_groups_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("annotations.annotation_groups_factory"));

const std::string expected_scope(" Expected scope: ");
const std::string actual_scope(" Actual scope: ");
const std::string duplicate_field_definition(
    "Field definition already inserted: ");
const std::string field_definition_not_found(
    "Field definition not found: ");
const std::string field_used_in_invalid_scope(
    "Field used in invalid scope: ");

}

namespace dogen {
namespace annotations {

annotation_groups_factory::annotation_groups_factory(const repository& rp,
    const bool throw_on_missing_field_definition)
    : repository_(rp),
      throw_on_missing_field_definition_(throw_on_missing_field_definition) { }

boost::optional<field_definition> annotation_groups_factory::
obtain_field_definition(const std::string& n) const {
    const auto i(repository_.field_definitions_by_name().find(n));
    if (i == repository_.field_definitions_by_name().end()) {
        if (throw_on_missing_field_definition_) {
            BOOST_LOG_SEV(lg, error) << field_definition_not_found << n;

            BOOST_THROW_EXCEPTION(
                building_error(field_definition_not_found + n));
        }

        BOOST_LOG_SEV(lg, warn) << field_definition_not_found << n;
        return boost::optional<field_definition>();
    }
    return i->second;
}

void annotation_groups_factory::validate_scope(const field_definition& fd,
    const scope_types current_scope) const {
    if (fd.scope() != scope_types::any &&
        fd.scope() != scope_types::not_applicable &&
        fd.scope() != current_scope) {

        std::stringstream s;
        s << field_used_in_invalid_scope << fd.name().qualified()
          << expected_scope << fd.scope()
          << actual_scope << current_scope;
        BOOST_LOG_SEV(lg, error) << s.str();
        BOOST_THROW_EXCEPTION(building_error(s.str()));
    }
}

annotation annotation_groups_factory::create_annotation(
    const scope_types current_scope,
    const std::unordered_map<std::string, std::list<std::string>>&
    aggregated_scribble_entries) const {

    value_factory f;
    std::unordered_map<std::string, boost::shared_ptr<value>> entries;
    for (auto kvp : aggregated_scribble_entries) {
        const auto& k(kvp.first);
        const auto fd(obtain_field_definition(k));
        if (!fd)
            continue;

        validate_scope(*fd, current_scope);
        const auto& v(kvp.second);
        entries[k] = f.make(*fd, v);
    }
    return annotation(entries);
}

std::unordered_map<std::string, std::list<std::string >>
annotation_groups_factory::
aggregate_scribble_entries(const scribble& scribble) const {
    std::unordered_map<std::string, std::list<std::string> > r;

    for (const auto& entry : scribble.entries())
        r[entry.first].push_front(entry.second);

    return r;
}

scope_types annotation_groups_factory::
compute_scope_for_id(const std::string& root_annotation_id,
    const std::string& current_id) const {
    const auto is_root(current_id == root_annotation_id);
    return is_root ? scope_types::root_module : scope_types::entity;
}

annotation annotation_groups_factory::
build(const scope_types scope, const scribble& scribble) const {
    auto aggregated_entries(aggregate_scribble_entries(scribble));
    auto r(create_annotation(scope, aggregated_entries));
    return r;
}

std::unordered_map<std::string, annotation_group>
annotation_groups_factory::build(const std::string& root_annotation_id,
    const std::unordered_map<std::string, scribble_group>& scribble_groups
    ) const {

    std::unordered_map<std::string, annotation_group> r;
    for (const auto& pair : scribble_groups) {
        const auto id(pair.first);
        const auto& scribble(pair.second);
        annotation_group ag;
        const auto scope(compute_scope_for_id(root_annotation_id, id));
        ag.parent(build(scope, scribble.parent()));

        for (const auto& pair : scribble.children()) {
            const auto child_id(pair.first);
            const auto& child(pair.second);
            const auto scope(scope_types::property);
            ag.children()[child_id] = build(scope, child);
        }
        r[id] = ag;
    }
    return r;
}

} }
