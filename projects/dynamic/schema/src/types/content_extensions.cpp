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
#include "dogen/dynamic/schema/types/field_access_error.hpp"
#include "dogen/dynamic/schema/types/content_extensions.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("dynamic.schema.content_extensions.cpp"));

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

bool has_field(const object& o, const std::string& k) {
    const auto i(o.fields().find(k));
    return (i != o.fields().end());
}

bool has_field(const object& o, const field_definition& fd) {
    return has_field(o, fd.name().qualified());
}

const field_instance& get_field(const object& o, const std::string& k) {
    const auto i(o.fields().find(k));

    if (i == o.fields().end()) {
        BOOST_LOG_SEV(lg, error) << field_not_found << k;
        BOOST_THROW_EXCEPTION(field_access_error(field_not_found + k));
    }

    return i->second;
}

const field_instance& get_field(const object& o, const field_definition& fd) {
    return get_field(o, fd.name().qualified());
}

std::string get_text_content(const value& v) {
    try {
        const auto& b(dynamic_cast<const text&>(v));
        return b.content();
    } catch(const std::bad_cast& e) {
        BOOST_LOG_SEV(lg, error) << unexpected_value_type;
        BOOST_THROW_EXCEPTION(field_access_error(unexpected_value_type));
    }
}

std::string
get_text_content(const object& o, const std::string& k) {
    const auto& f(get_field(o, k));
    const auto& v(*f.value());

    try {
        return get_text_content(v);
    } catch(boost::exception& e) {
        BOOST_LOG_SEV(lg, error) << not_text_field << k;
        e << extension_error_info(field + k);
        throw;
    }
}

std::string
get_text_content(const object& o, const field_definition& fd) {
    return get_text_content(o, fd.name().qualified());
}

std::list<std::string>
get_text_collection_content(const object& o, const std::string& k) {
    const auto& f(get_field(o, k));
    const auto& v(*f.value());

    try {
        const auto& tc(dynamic_cast<const text_collection&>(v));
        return tc.content();
    } catch(const std::bad_cast& e) {
        BOOST_LOG_SEV(lg, error) << unexpected_field_type << k;
        BOOST_THROW_EXCEPTION(field_access_error(unexpected_field_type + k));
    }
}

std::list<std::string>
get_text_collection_content(const object& o, const field_definition& fd) {
    return get_text_collection_content(o, fd.name().qualified());
}

bool get_boolean_content(const value& v) {
    try {
        const auto& b(dynamic_cast<const boolean&>(v));
        return b.content();
    } catch(const std::bad_cast& e) {
        BOOST_LOG_SEV(lg, error) << unexpected_value_type;
        BOOST_THROW_EXCEPTION(field_access_error(unexpected_value_type));
    }
}

bool get_boolean_content(const object& o, const std::string& k) {
    const auto& f(get_field(o, k));
    const auto& v(*f.value());
    try {
        return get_boolean_content(v);
    } catch(boost::exception& e) {
        BOOST_LOG_SEV(lg, error) << not_boolean_field << k;
        e << extension_error_info(field + k);
        throw;
    }
}


bool get_boolean_content(const object& o, const field_definition& fd) {
    return get_boolean_content(o, fd.name().qualified());
}

} } }
