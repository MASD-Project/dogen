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
#include <string>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/dynamic/schema/types/text.hpp"
#include "dogen/dynamic/schema/types/boolean.hpp"
#include "dogen/dynamic/schema/types/text_collection.hpp"
#include "dogen/dynamic/schema/types/selection_error.hpp"
#include "dogen/dynamic/schema/types/field_selector.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("dynamic.schema.content_extensions"));

const std::string field_not_found("Field not found: ");
const std::string unexpected_value_type("Unexpected value type.");
const std::string field("Field: ");
const std::string not_boolean_field("Field does not have boolean content: ");
const std::string not_text_field("Field does not have text content: ");
const std::string unexpected_field_type("Field has an unexpected type: ");
typedef boost::error_info<struct tag_errmsg, std::string> extension_error_info;

}

namespace dogen {
namespace dynamic {
namespace schema {

field_selector::field_selector(const object& o) : object_(o) { }

bool field_selector::has_field(const std::string& qualified_field_name) const {
    const auto i(object_.fields().find(qualified_field_name));
    return (i != object_.fields().end());
}

bool field_selector::has_field(const field_definition& fd) const {
    return has_field(fd.name().qualified());
}

const field_instance& field_selector::
get_field(const std::string& qualified_field_name) const {
    const auto i(object_.fields().find(qualified_field_name));

    if (i == object_.fields().end()) {
        BOOST_LOG_SEV(lg, error) << field_not_found << qualified_field_name;
        BOOST_THROW_EXCEPTION(selection_error(field_not_found
                + qualified_field_name));
    }

    return i->second;
}

const field_instance& field_selector::
get_field(const field_definition& fd) const {
    return get_field(fd.name().qualified());
}

std::string field_selector::get_text_content(const value& v) {
    try {
        const auto& b(dynamic_cast<const text&>(v));
        return b.content();
    } catch(const std::bad_cast& e) {
        BOOST_LOG_SEV(lg, error) << unexpected_value_type;
        BOOST_THROW_EXCEPTION(selection_error(unexpected_value_type));
    }
}

std::string field_selector::
get_text_content(const std::string& qualified_field_name) const {
    const auto& f(get_field(qualified_field_name));
    const auto& v(*f.value());

    try {
        return get_text_content(v);
    } catch(boost::exception& e) {
        BOOST_LOG_SEV(lg, error) << not_text_field << qualified_field_name;
        e << extension_error_info(field + qualified_field_name);
        throw;
    }
}

std::string field_selector::get_text_content(const field_definition& fd) const {
    return get_text_content(fd.name().qualified());
}

std::list<std::string> field_selector::
get_text_collection_content(const std::string& qualified_field_name) const {
    const auto& f(get_field(qualified_field_name));
    const auto& v(*f.value());

    try {
        const auto& tc(dynamic_cast<const text_collection&>(v));
        return tc.content();
    } catch(const std::bad_cast& e) {
        BOOST_LOG_SEV(lg, error) << unexpected_field_type
                                 << qualified_field_name;
        BOOST_THROW_EXCEPTION(selection_error(unexpected_field_type +
                qualified_field_name));
    }
}

std::list<std::string> field_selector::
get_text_collection_content(const field_definition& fd) const {
    return get_text_collection_content(fd.name().qualified());
}

bool field_selector::get_boolean_content(const value& v) {
    try {
        const auto& b(dynamic_cast<const boolean&>(v));
        return b.content();
    } catch(const std::bad_cast& e) {
        BOOST_LOG_SEV(lg, error) << unexpected_value_type;
        BOOST_THROW_EXCEPTION(selection_error(unexpected_value_type));
    }
}

bool field_selector::
get_boolean_content(const std::string& qualified_field_name) const {
    const auto& f(get_field(qualified_field_name));
    const auto& v(*f.value());
    try {
        return get_boolean_content(v);
    } catch(boost::exception& e) {
        BOOST_LOG_SEV(lg, error) << not_boolean_field << qualified_field_name;
        e << extension_error_info(field + qualified_field_name);
        throw;
    }
}

bool field_selector::get_boolean_content(const field_definition& fd) const {
    return get_boolean_content(fd.name().qualified());
}

} } }
