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
#include "dogen/dynamic/schema/types/selection_error.hpp"
#include "dogen/dynamic/schema/types/repository_selector.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("dynamic.schema.repository_selector"));

const std::string field_not_found("Could not find expected field: ");
const std::string no_fields_for_formatter(
    "Could not find any fields for formatter: ");
const std::string no_fields_for_facet("Could not find any fields for facet: ");
const std::string no_fields_for_model("Could not find any fields for model: ");

}

namespace dogen {
namespace dynamic {
namespace schema {

repository_selector::repository_selector(const repository& rp)
    : repository_(rp) {}

const field_definition& repository_selector::
select_field_by_name(const std::string& n) const {
    const auto& c(repository_.field_definitions_by_name());
    const auto i(c.find(n));
    if (i == c.end()) {
        BOOST_LOG_SEV(lg, error) << field_not_found << n;
        BOOST_THROW_EXCEPTION(selection_error(field_not_found + n));
    }
    return i->second;
}

const std::list<field_definition>& repository_selector::
select_fields_by_formatter_name(const std::string& n) const {
    const auto& c(repository_.field_definitions_by_formatter_name());
    const auto i(c.find(n));
    if (i == c.end()) {
        BOOST_LOG_SEV(lg, error) << no_fields_for_formatter << n;
        BOOST_THROW_EXCEPTION(selection_error(no_fields_for_formatter + n));
    }
    return i->second;
}

const std::list<field_definition>& repository_selector::
select_fields_by_facet_name(const std::string& n) const {
    const auto& c(repository_.field_definitions_by_facet_name());
    const auto i(c.find(n));
    if (i == c.end()) {
        BOOST_LOG_SEV(lg, error) << no_fields_for_facet << n;
        BOOST_THROW_EXCEPTION(selection_error(no_fields_for_facet + n));
    }
    return i->second;
}

const std::list<field_definition>& repository_selector::
select_fields_by_model_name(const std::string& n) const {
    const auto& c(repository_.field_definitions_by_model_name());
    const auto i(c.find(n));
    if (i == c.end()) {
        BOOST_LOG_SEV(lg, error) << no_fields_for_model << n;
        BOOST_THROW_EXCEPTION(selection_error(no_fields_for_model + n));
    }
    return i->second;
}

} } }
