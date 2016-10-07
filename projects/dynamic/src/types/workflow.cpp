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
#include "dogen/dynamic/io/field_definition_io.hpp"
#include "dogen/dynamic/io/scope_types_io.hpp"
#include "dogen/dynamic/types/field_instance_factory.hpp"
#include "dogen/dynamic/types/workflow_error.hpp"
#include "dogen/dynamic/types/workflow.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("dynamic.workflow"));

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
namespace dynamic {

workflow::workflow(const repository& rp,
    const bool throw_on_missing_field_definition)
    : repository_(rp),
      throw_on_missing_field_definition_(throw_on_missing_field_definition) { }

boost::optional<field_definition> workflow::
obtain_field_definition(const std::string& n) const {
    const auto i(repository_.field_definitions_by_name().find(n));
    if (i == repository_.field_definitions_by_name().end()) {
        if (throw_on_missing_field_definition_) {
            BOOST_LOG_SEV(lg, error) << field_definition_not_found << n;

            BOOST_THROW_EXCEPTION(
                workflow_error(field_definition_not_found + n));
        }

        BOOST_LOG_SEV(lg, warn) << field_definition_not_found << n;
        return boost::optional<field_definition>();
    }
    return i->second;
}

void workflow::validate_scope(const field_definition& fd,
    const scope_types current_scope) const {
    if (fd.scope() != scope_types::any &&
        fd.scope() != scope_types::not_applicable &&
        fd.scope() != current_scope) {

        std::stringstream s;
        s << field_used_in_invalid_scope << fd.name().qualified()
          << expected_scope << fd.scope()
          << actual_scope << current_scope;
        BOOST_LOG_SEV(lg, error) << s.str();
        BOOST_THROW_EXCEPTION(workflow_error(s.str()));
    }
}

std::unordered_map<std::string, std::list<std::string> >
workflow::aggregate_raw_data_activity(
    const std::list<std::pair<std::string, std::string> >&
    raw_data) const {
    std::unordered_map<std::string, std::list<std::string> > r;

    for (const auto& rd : raw_data)
        r[rd.first].push_front(rd.second);

    return r;
}

std::unordered_map<std::string, field_instance>
workflow::create_fields_activity(
    const std::unordered_map<std::string, std::list<std::string> >&
    aggregated_data, const scope_types current_scope) const {
    std::unordered_map<std::string, field_instance> r;
    field_instance_factory f;
    for (auto pair : aggregated_data) {
        const auto& n(pair.first);
        const auto fd(obtain_field_definition(n));
        if (!fd)
            continue;

        validate_scope(*fd, current_scope);
        const auto& values(pair.second);
        r[n] = f.make(*fd, values);
    }
    return r;
}

object workflow::execute(const scope_types current_scope,
    const std::list<std::pair<std::string, std::string>>&
    raw_data) const {
    auto aggregated_raw_data(aggregate_raw_data_activity(raw_data));
    auto fields(create_fields_activity(aggregated_raw_data, current_scope));
    return object(fields);
}

std::unordered_map<std::string, object_aggregate> workflow::
execute(const std::string& root_object_id, const std::unordered_map<
    std::string, raw_aggregate>& raw_aggregates) const {

    std::unordered_map<std::string, object_aggregate> r;
    for (const auto& pair : raw_aggregates) {
        const auto id(pair.first);
        const auto is_root_module(id == root_object_id);
        const auto scope(is_root_module ?
            dynamic::scope_types::root_module :
            dynamic::scope_types::entity);

        const auto& ra(pair.second);
        object_aggregate oa;
        oa.element(execute(scope, ra.element()));
        for (const auto& pair : ra.attributes()) {
            const auto attr_id(pair.first);
            const auto& attr(pair.second);
            const auto scope(dynamic::scope_types::property);
            oa.attributes()[attr_id] = execute(scope, attr);
        }
        r[id] = oa;
    }
    return r;
}

} }
