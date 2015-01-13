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
#include <sstream>
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/forward_list_io.hpp"
#include "dogen/dynamic/io/field_definition_io.hpp"
#include "dogen/dynamic/io/scope_types_io.hpp"
#include "dogen/dynamic/types/field_factory.hpp"
#include "dogen/dynamic/types/workflow_error.hpp"
#include "dogen/dynamic/types/workflow.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("dynamic.workflow"));

const std::string scope(" scope: ");
const std::string duplicate_field_definition(
    "Field definition already inserted: ");
const std::string field_definition_not_found(
    "Field definition not found: ");
const std::string field_used_in_invalid_scope(
    "Field used in invalid scope: ");

}

namespace dogen {
namespace dynamic {

std::shared_ptr<registrar> workflow::registrar_;

dynamic::registrar& workflow::registrar() {
    if (!registrar_)
        registrar_ = std::make_shared<dynamic::registrar>();

    return *registrar_;
}

workflow::workflow() : field_definitions_by_complete_name_(
    create_field_definitions_by_complete_name()) { }

std::unordered_map<std::string, field_definition> workflow::
create_field_definitions_by_complete_name() const {
    std::unordered_map<std::string, field_definition> r;

    registrar().validate();
    BOOST_LOG_SEV(lg, debug) << "Field definitions: "
                             << registrar().field_definitions();

    for (const auto& fd : registrar().field_definitions()) {
        const auto cn(fd.name().complete_name());
        const auto result(r.insert(std::make_pair(cn, fd)));
        if (!result.second) {
            BOOST_LOG_SEV(lg, error) << duplicate_field_definition << cn;
            BOOST_THROW_EXCEPTION(workflow_error(
                    duplicate_field_definition + cn));
        }
    }
    return r;
}

boost::optional<field_definition> workflow::
obtain_field_definition(const std::string& complete_name,
    const scope_types current_scope) const {

    const auto i(field_definitions_by_complete_name_.find(complete_name));
    if (i == field_definitions_by_complete_name_.end()) {
        BOOST_LOG_SEV(lg, error) << field_definition_not_found << complete_name;

        // FIXME: commented for now
        // BOOST_THROW_EXCEPTION(workflow_error(
        //         field_definition_not_found + complete_name));
        return boost::optional<field_definition>();
    }

    const auto& fd(i->second);
    if (fd.scope() != scope_types::any &&
        fd.scope() != scope_types::not_applicable &&
        fd.scope() != current_scope) {

        std::stringstream s;
        s << field_used_in_invalid_scope << complete_name
          << scope << current_scope;
        BOOST_LOG_SEV(lg, error) << s.str();
        BOOST_THROW_EXCEPTION(workflow_error(s.str()));
    }

    return boost::optional<field_definition>(fd);
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

std::unordered_map<std::string, field> workflow::build_fields_activity(
    const std::unordered_map<std::string, std::list<std::string> >&
    aggregated_data, const scope_types current_scope) const {
    std::unordered_map<std::string, field> r;
    field_factory f;
    for (auto pair : aggregated_data) {
        const auto& complete_name(pair.first);
        const auto fd(obtain_field_definition(complete_name, current_scope));
        if (!fd)
            continue;

        const auto& values(pair.second);
        r[complete_name] = f.build(*fd, values);
    }
    return r;
}

object workflow::execute(const scope_types current_scope,
    const std::list<std::pair<std::string, std::string>>&
    raw_data) const {
    auto aggregated_raw_data(aggregate_raw_data_activity(raw_data));
    auto fields(build_fields_activity(aggregated_raw_data, current_scope));
    return object(fields);
}

} }
