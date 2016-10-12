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
#include <string>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/annotations/types/text.hpp"
#include "dogen/annotations/types/number.hpp"
#include "dogen/annotations/types/boolean.hpp"
#include "dogen/annotations/types/text_collection.hpp"
#include "dogen/annotations/types/selection_error.hpp"
#include "dogen/annotations/types/field_selector.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("annotations.field_selector"));

const std::string field_not_found("Field not found: ");
const std::string unexpected_value_type("Unexpected value type.");
const std::string field("Field: ");
const std::string not_number_field("Field does not have numeric content: ");
const std::string not_boolean_field("Field does not have boolean content: ");
const std::string not_text_field("Field does not have text content: ");
const std::string not_text_collection_field(
    "Field does not have text collection content: ");
const std::string unexpected_field_type("Field has an unexpected type: ");
typedef boost::error_info<struct tag_errmsg, std::string> extension_error_info;
const std::string no_default_value(
    "Field does not have a default value: ");

}

namespace dogen {
namespace annotations {

type_selector::type_selector(const annotation& a) : annotation_(a) { }

void type_selector::ensure_default_value(const type& t) const {
    if (!t.default_value()) {
        const auto& n(t.name().qualified());
        BOOST_LOG_SEV(lg, error) << no_default_value << "'" << n << "'";
        BOOST_THROW_EXCEPTION(selection_error(no_default_value + n));
    }
}

bool type_selector::has_field(const std::string& qualified_field_name) const {
    const auto i(annotation_.entries().find(qualified_field_name));
    return (i != annotation_.entries().end());
}

bool type_selector::has_field(const type& t) const {
    return has_field(t.name().qualified());
}

const value& type_selector::
get_field(const std::string& qualified_field_name) const {
    const auto i(annotation_.entries().find(qualified_field_name));

    if (i == annotation_.entries().end()) {
        BOOST_LOG_SEV(lg, error) << field_not_found << qualified_field_name;
        BOOST_THROW_EXCEPTION(selection_error(field_not_found
                + qualified_field_name));
    }

    return *i->second;
}

const value& type_selector::get_field(const type& t) const {
    return get_field(t.name().qualified());
}

std::string type_selector::get_text_content(const value& v) {
    try {
        const auto& b(dynamic_cast<const text&>(v));
        return b.content();
    } catch(const std::bad_cast& e) {
        BOOST_LOG_SEV(lg, error) << unexpected_value_type;
        BOOST_THROW_EXCEPTION(selection_error(unexpected_value_type));
    }
}

std::string type_selector::
get_text_content(const std::string& qualified_field_name) const {
    const auto& v(get_field(qualified_field_name));

    try {
        return get_text_content(v);
    } catch(boost::exception& e) {
        BOOST_LOG_SEV(lg, error) << not_text_field << qualified_field_name;
        e << extension_error_info(field + qualified_field_name);
        throw;
    }
}

std::string type_selector::
get_text_content_or_default(const type& t) const {
    if (has_field(t))
        return get_text_content(t);

    ensure_default_value(t);

    try {
        return get_text_content(*t.default_value());
    } catch(boost::exception& e) {
        const auto n(t.name().qualified());
        BOOST_LOG_SEV(lg, error) << not_text_field << n
                                 << " (field's default value)";
        e << extension_error_info(field + n);
        throw;
    }
}

std::list<std::string>
type_selector::get_text_collection_content(const value& v) {
    try {
        const auto& b(dynamic_cast<const text_collection&>(v));
        return b.content();
    } catch(const std::bad_cast& e) {
        BOOST_LOG_SEV(lg, error) << unexpected_value_type;
        BOOST_THROW_EXCEPTION(selection_error(unexpected_value_type));
    }
}

std::string type_selector::get_text_content(const type& t) const {
    return get_text_content(t.name().qualified());
}

std::list<std::string> type_selector::
get_text_collection_content(const std::string& qualified_field_name) const {
    const auto& v(get_field(qualified_field_name));

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

std::list<std::string> type_selector::
get_text_collection_content(const type& t) const {
    return get_text_collection_content(t.name().qualified());
}

std::list<std::string> type_selector::
get_text_collection_content_or_default(const type& t) const {
    if (has_field(t))
        return get_text_collection_content(t);

    ensure_default_value(t);

    try {
        return get_text_collection_content(*t.default_value());
    } catch(boost::exception& e) {
        const auto n(t.name().qualified());
        BOOST_LOG_SEV(lg, error) << not_text_collection_field << n
                                 << " (field's default value)";
        e << extension_error_info(field + n);
        throw;
    }
}

bool type_selector::get_boolean_content(const value& v) {
    try {
        const auto& b(dynamic_cast<const boolean&>(v));
        return b.content();
    } catch(const std::bad_cast& e) {
        BOOST_LOG_SEV(lg, error) << unexpected_value_type;
        BOOST_THROW_EXCEPTION(selection_error(unexpected_value_type));
    }
}

bool type_selector::
get_boolean_content(const std::string& qualified_field_name) const {
    const auto& v(get_field(qualified_field_name));

    try {
        return get_boolean_content(v);
    } catch(boost::exception& e) {
        BOOST_LOG_SEV(lg, error) << not_boolean_field << qualified_field_name;
        e << extension_error_info(field + qualified_field_name);
        throw;
    }
}

bool type_selector::get_boolean_content(const type& t) const {
    return get_boolean_content(t.name().qualified());
}

bool type_selector::
get_boolean_content_or_default(const type& t) const {
    if (has_field(t))
        return get_boolean_content(t);

    ensure_default_value(t);

    try {
        return get_boolean_content(*t.default_value());
    } catch(boost::exception& e) {
        const auto n(t.name().qualified());
        BOOST_LOG_SEV(lg, error) << not_boolean_field << n
                                 << " (field's default value)";
        e << extension_error_info(field + n);
        throw;
    }
}

int type_selector::get_number_content(const value& v) {
    try {
        const auto& b(dynamic_cast<const number&>(v));
        return b.content();
    } catch(const std::bad_cast& e) {
        BOOST_LOG_SEV(lg, error) << unexpected_value_type;
        BOOST_THROW_EXCEPTION(selection_error(unexpected_value_type));
    }
}

int type_selector::
get_number_content(const std::string& qualified_field_name) const {
    const auto& v(get_field(qualified_field_name));

    try {
        return get_number_content(v);
    } catch(boost::exception& e) {
        BOOST_LOG_SEV(lg, error) << not_number_field << qualified_field_name;
        e << extension_error_info(field + qualified_field_name);
        throw;
    }
}

int type_selector::get_number_content(const type& t) const {
    return get_number_content(t.name().qualified());
}

int type_selector::
get_number_content_or_default(const type& t) const {
    if (has_field(t))
        return get_number_content(t);

    ensure_default_value(t);

    try {
        return get_number_content(*t.default_value());
    } catch(boost::exception& e) {
        const auto n(t.name().qualified());
        BOOST_LOG_SEV(lg, error) << not_number_field << n
                                 << " (field's default value)";
        e << extension_error_info(field + n);
        throw;
    }
}

} }
