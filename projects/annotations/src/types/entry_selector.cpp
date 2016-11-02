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
#include <boost/algorithm/string/erase.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/annotations/types/text.hpp"
#include "dogen/annotations/types/number.hpp"
#include "dogen/annotations/types/boolean.hpp"
#include "dogen/annotations/types/key_value_pair.hpp"
#include "dogen/annotations/types/text_collection.hpp"
#include "dogen/annotations/types/selection_error.hpp"
#include "dogen/annotations/types/entry_selector.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("annotations.entry_selector"));

const std::string entry_not_found("Entry not found: ");
const std::string unexpected_value_type("Unexpected value type.");
const std::string entry("Entry: ");
const std::string not_number_entry("Entry does not have numeric content: ");
const std::string not_boolean_entry("Entry does not have boolean content: ");
const std::string not_text_entry("Entry does not have text content: ");
const std::string not_text_collection_entry(
    "Entry does not have text collection content: ");
const std::string not_kvp_entry("Entry does not have kvp content: ");
const std::string unexpected_entry_type("Entry has an unexpected type: ");
typedef boost::error_info<struct tag_errmsg, std::string> extension_error_info;
const std::string no_default_value(
    "Entry does not have a default value: ");
const std::string duplicate_key("Duplicate key in kvp: ");

}

namespace dogen {
namespace annotations {

entry_selector::entry_selector(const annotation& a) : annotation_(a) { }

void entry_selector::ensure_default_value(const type& t) const {
    if (!t.default_value()) {
        const auto& n(t.name().qualified());
        BOOST_LOG_SEV(lg, error) << no_default_value << "'" << n << "'";
        BOOST_THROW_EXCEPTION(selection_error(no_default_value + n));
    }
}

bool entry_selector::has_entry(const std::string& qualified_name) const {
    const auto i(annotation_.entries().find(qualified_name));
    return (i != annotation_.entries().end());
}

bool entry_selector::has_entry(const type& t) const {
    return has_entry(t.name().qualified());
}

const value& entry_selector::
get_entry_value(const std::string& qualified_name) const {
    const auto i(annotation_.entries().find(qualified_name));

    if (i == annotation_.entries().end()) {
        BOOST_LOG_SEV(lg, error) << entry_not_found << qualified_name;
        BOOST_THROW_EXCEPTION(selection_error(entry_not_found
                + qualified_name));
    }

    return *i->second;
}

const value& entry_selector::get_entry_value(const type& t) const {
    return get_entry_value(t.name().qualified());
}

std::string entry_selector::get_text_content(const value& v) {
    try {
        const auto& b(dynamic_cast<const text&>(v));
        return b.content();
    } catch(const std::bad_cast& e) {
        BOOST_LOG_SEV(lg, error) << unexpected_value_type;
        BOOST_THROW_EXCEPTION(selection_error(unexpected_value_type));
    }
}

std::string entry_selector::
get_text_content(const std::string& qualified_name) const {
    const auto& v(get_entry_value(qualified_name));

    try {
        return get_text_content(v);
    } catch(boost::exception& e) {
        BOOST_LOG_SEV(lg, error) << not_text_entry << qualified_name;
        e << extension_error_info(entry + qualified_name);
        throw;
    }
}

std::string entry_selector::
get_text_content_or_default(const type& t) const {
    if (has_entry(t))
        return get_text_content(t);

    ensure_default_value(t);

    try {
        return get_text_content(*t.default_value());
    } catch(boost::exception& e) {
        const auto n(t.name().qualified());
        BOOST_LOG_SEV(lg, error) << not_text_entry << n
                                 << " (Entry's default value)";
        e << extension_error_info(entry + n);
        throw;
    }
}

std::list<std::string>
entry_selector::get_text_collection_content(const value& v) {
    try {
        const auto& b(dynamic_cast<const text_collection&>(v));
        return b.content();
    } catch(const std::bad_cast& e) {
        BOOST_LOG_SEV(lg, error) << unexpected_value_type;
        BOOST_THROW_EXCEPTION(selection_error(unexpected_value_type));
    }
}

std::string entry_selector::get_text_content(const type& t) const {
    return get_text_content(t.name().qualified());
}

std::list<std::string> entry_selector::
get_text_collection_content(const std::string& qualified_name) const {
    const auto& v(get_entry_value(qualified_name));

    try {
        const auto& tc(dynamic_cast<const text_collection&>(v));
        return tc.content();
    } catch(const std::bad_cast& e) {
        BOOST_LOG_SEV(lg, error) << unexpected_entry_type
                                 << qualified_name;
        BOOST_THROW_EXCEPTION(selection_error(unexpected_entry_type +
                qualified_name));
    }
}

std::list<std::string> entry_selector::
get_text_collection_content(const type& t) const {
    return get_text_collection_content(t.name().qualified());
}

std::list<std::string> entry_selector::
get_text_collection_content_or_default(const type& t) const {
    if (has_entry(t))
        return get_text_collection_content(t);

    ensure_default_value(t);

    try {
        return get_text_collection_content(*t.default_value());
    } catch(boost::exception& e) {
        const auto n(t.name().qualified());
        BOOST_LOG_SEV(lg, error) << not_text_collection_entry << n
                                 << " (entry's default value)";
        e << extension_error_info(entry + n);
        throw;
    }
}

bool entry_selector::get_boolean_content(const value& v) {
    try {
        const auto& b(dynamic_cast<const boolean&>(v));
        return b.content();
    } catch(const std::bad_cast& e) {
        BOOST_LOG_SEV(lg, error) << unexpected_value_type;
        BOOST_THROW_EXCEPTION(selection_error(unexpected_value_type));
    }
}

bool entry_selector::
get_boolean_content(const std::string& qualified_name) const {
    const auto& v(get_entry_value(qualified_name));

    try {
        return get_boolean_content(v);
    } catch(boost::exception& e) {
        BOOST_LOG_SEV(lg, error) << not_boolean_entry << qualified_name;
        e << extension_error_info(entry + qualified_name);
        throw;
    }
}

bool entry_selector::get_boolean_content(const type& t) const {
    return get_boolean_content(t.name().qualified());
}

bool entry_selector::
get_boolean_content_or_default(const type& t) const {
    if (has_entry(t))
        return get_boolean_content(t);

    ensure_default_value(t);

    try {
        return get_boolean_content(*t.default_value());
    } catch(boost::exception& e) {
        const auto n(t.name().qualified());
        BOOST_LOG_SEV(lg, error) << not_boolean_entry << n
                                 << " (entry's default value)";
        e << extension_error_info(entry + n);
        throw;
    }
}

int entry_selector::get_number_content(const value& v) {
    try {
        const auto& b(dynamic_cast<const number&>(v));
        return b.content();
    } catch(const std::bad_cast& e) {
        BOOST_LOG_SEV(lg, error) << unexpected_value_type;
        BOOST_THROW_EXCEPTION(selection_error(unexpected_value_type));
    }
}

int entry_selector::
get_number_content(const std::string& qualified_name) const {
    const auto& v(get_entry_value(qualified_name));

    try {
        return get_number_content(v);
    } catch(boost::exception& e) {
        BOOST_LOG_SEV(lg, error) << not_number_entry << qualified_name;
        e << extension_error_info(entry + qualified_name);
        throw;
    }
}

int entry_selector::get_number_content(const type& t) const {
    return get_number_content(t.name().qualified());
}

int entry_selector::
get_number_content_or_default(const type& t) const {
    if (has_entry(t))
        return get_number_content(t);

    ensure_default_value(t);

    try {
        return get_number_content(*t.default_value());
    } catch(boost::exception& e) {
        const auto n(t.name().qualified());
        BOOST_LOG_SEV(lg, error) << not_number_entry << n
                                 << " (entry's default value)";
        e << extension_error_info(entry + n);
        throw;
    }
}

std::unordered_map<std::string, std::string>
entry_selector::get_kvp_content(const value& v) {
    try {
        const auto& b(dynamic_cast<const key_value_pair&>(v));
        return b.content();
    } catch(const std::bad_cast& e) {
        BOOST_LOG_SEV(lg, error) << unexpected_value_type;
        BOOST_THROW_EXCEPTION(selection_error(unexpected_value_type));
    }
}

std::unordered_map<std::string, std::string>
entry_selector::get_kvp_content(const std::string& qualified_name) const {
    const auto& v(get_entry_value(qualified_name));

    try {
        return get_kvp_content(v);
    } catch(boost::exception& e) {
        BOOST_LOG_SEV(lg, error) << not_kvp_entry << qualified_name;
        e << extension_error_info(entry + qualified_name);
        throw;
    }
}

std::unordered_map<std::string, std::string> entry_selector::
get_kvp_content(const type& t) const {
    return get_kvp_content(t.name().qualified());
}

} }
