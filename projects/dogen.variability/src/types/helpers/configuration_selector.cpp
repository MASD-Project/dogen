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
#include <boost/algorithm/string/predicate.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.variability/types/meta_model/text.hpp"
#include "dogen.variability/types/meta_model/number.hpp"
#include "dogen.variability/types/meta_model/boolean.hpp"
#include "dogen.variability/types/meta_model/key_value_pair.hpp"
#include "dogen.variability/types/meta_model/text_collection.hpp"
#include "dogen.variability/types/helpers/selection_exception.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("variability.helpers.configuration_selector"));

const std::string configuration_point_not_found(
    "Configuration point not found: ");
const std::string unexpected_value_type("Unexpected value type.");
const std::string configuration_point_name("Configuration point: ");
const std::string not_number(
    "Configuration point does not have numeric content: ");
const std::string not_boolean(
    "Configuration point does not have boolean content: ");
const std::string not_text("Configuration point does not have text content: ");
const std::string not_text_collection(
    "Configuration point does not have text collection content: ");
const std::string not_kvp("Configuration point does not have kvp content: ");
const std::string unexpected_type(
    "Configuration point has an unexpected type: ");
typedef boost::error_info<struct tag_errmsg, std::string> extension_error_info;
const std::string no_default_value(
    "Feature does not have a default value: ");
const std::string duplicate_key("Duplicate key in kvp: ");

}

namespace dogen::variability::helpers {

configuration_selector::
configuration_selector(const meta_model::configuration& c)
    : configuration_(c) { }

void configuration_selector::
ensure_default_value(const meta_model::feature& f) const {
    if (!f.default_value()) {
        const auto& n(f.name().qualified());
        BOOST_LOG_SEV(lg, error) << no_default_value << "'" << n << "'";
        BOOST_THROW_EXCEPTION(selection_exception(no_default_value + n));
    }
}

bool configuration_selector::
has_configuration_point(const std::string& qn) const {
    const auto& cps(configuration_.configuration_points());
    const auto i(cps.find(qn));
    return (i != cps.end());
}

bool configuration_selector::
has_configuration_point(const meta_model::feature& f) const {
    return has_configuration_point(f.name().qualified());
}

bool configuration_selector::
has_configuration_point_ending_with(const std::string& s) const {
    for (const auto& cp : configuration_.configuration_points()) {
        const auto& key(cp.first);
        BOOST_LOG_SEV(lg, trace) << "Key: " << key;

        if (boost::ends_with(key, s)) {
            BOOST_LOG_SEV(lg, trace) << "Key ends with " << s;
            return true;
        } else
            BOOST_LOG_SEV(lg, trace) << "Key does not end with " << s;
    }
    return false;
}

const meta_model::value& configuration_selector::
get_configuration_point_value(const std::string& qn) const {
    const auto& cps(configuration_.configuration_points());
    const auto i(cps.find(qn));
    if (i != cps.end())
        return *i->second.value();

    BOOST_LOG_SEV(lg, error) << configuration_point_not_found << qn;
    BOOST_THROW_EXCEPTION(selection_exception(configuration_point_not_found + qn));
}

const meta_model::value& configuration_selector::
get_configuration_point_value(const meta_model::feature& f) const {
    return get_configuration_point_value(f.name().qualified());
}

std::string
configuration_selector::get_text_content(const meta_model::value& v) {
    try {
        const auto& b(dynamic_cast<const meta_model::text&>(v));
        return b.content();
    } catch(const std::bad_cast& /*e*/) {
        BOOST_LOG_SEV(lg, error) << unexpected_value_type;
        BOOST_THROW_EXCEPTION(selection_exception(unexpected_value_type));
    }
}

std::string configuration_selector::
get_text_content(const std::string& qn) const {
    const auto& v(get_configuration_point_value(qn));

    try {
        return get_text_content(v);
    } catch(boost::exception& e) {
        BOOST_LOG_SEV(lg, error) << not_text << qn;
        e << extension_error_info(configuration_point_name + qn);
        throw;
    }
}

std::string configuration_selector::
get_text_content_or_default(const meta_model::feature& f) const {
    if (has_configuration_point(f))
        return get_text_content(f);

    ensure_default_value(f);

    try {
        return get_text_content(*f.default_value());
    } catch(boost::exception& e) {
        const auto n(f.name().qualified());
        BOOST_LOG_SEV(lg, error) << not_text << n
                                 << " (Entry's default value)";
        e << extension_error_info(configuration_point_name + n);
        throw;
    }
}

std::list<std::string> configuration_selector::
get_text_collection_content(const meta_model::value& v) {
    try {
        const auto& b(dynamic_cast<const meta_model::text_collection&>(v));
        return b.content();
    } catch(const std::bad_cast& /*e*/) {
        BOOST_LOG_SEV(lg, error) << unexpected_value_type;
        BOOST_THROW_EXCEPTION(selection_exception(unexpected_value_type));
    }
}

std::string configuration_selector::
get_text_content(const meta_model::feature& f) const {
    return get_text_content(f.name().qualified());
}

std::list<std::string> configuration_selector::
get_text_collection_content(const std::string& qn) const {
    const auto& v(get_configuration_point_value(qn));

    try {
        const auto& tc(dynamic_cast<const meta_model::text_collection&>(v));
        return tc.content();
    } catch(const std::bad_cast& /*e*/) {
        BOOST_LOG_SEV(lg, error) << unexpected_type
                                 << qn;
        BOOST_THROW_EXCEPTION(selection_exception(unexpected_type + qn));
    }
}

std::list<std::string> configuration_selector::
get_text_collection_content(const meta_model::feature& f) const {
    return get_text_collection_content(f.name().qualified());
}

std::list<std::string> configuration_selector::
get_text_collection_content_or_default(const meta_model::feature& f) const {
    if (has_configuration_point(f))
        return get_text_collection_content(f);

    ensure_default_value(f);

    try {
        return get_text_collection_content(*f.default_value());
    } catch(boost::exception& e) {
        const auto n(f.name().qualified());
        BOOST_LOG_SEV(lg, error) << not_text_collection << n
                                 << " (entry's default value)";
        e << extension_error_info(configuration_point_name + n);
        throw;
    }
}

bool configuration_selector::get_boolean_content(const meta_model::value& v) {
    try {
        const auto& b(dynamic_cast<const meta_model::boolean&>(v));
        return b.content();
    } catch(const std::bad_cast& /*e*/) {
        BOOST_LOG_SEV(lg, error) << unexpected_value_type;
        BOOST_THROW_EXCEPTION(selection_exception(unexpected_value_type));
    }
}

bool configuration_selector::
get_boolean_content(const std::string& qn) const {
    const auto& v(get_configuration_point_value(qn));

    try {
        return get_boolean_content(v);
    } catch(boost::exception& e) {
        BOOST_LOG_SEV(lg, error) << not_boolean << qn;
        e << extension_error_info(configuration_point_name + qn);
        throw;
    }
}

bool configuration_selector::
get_boolean_content(const meta_model::feature& f) const {
    return get_boolean_content(f.name().qualified());
}

bool configuration_selector::
get_boolean_content_or_default(const meta_model::feature& f) const {
    if (has_configuration_point(f))
        return get_boolean_content(f);

    ensure_default_value(f);

    try {
        return get_boolean_content(*f.default_value());
    } catch(boost::exception& e) {
        const auto n(f.name().qualified());
        BOOST_LOG_SEV(lg, error) << not_boolean << n
                                 << " (entry's default value)";
        e << extension_error_info(configuration_point_name + n);
        throw;
    }
}

int configuration_selector::get_number_content(const meta_model::value& v) {
    try {
        const auto& b(dynamic_cast<const meta_model::number&>(v));
        return b.content();
    } catch(const std::bad_cast& /*e*/) {
        BOOST_LOG_SEV(lg, error) << unexpected_value_type;
        BOOST_THROW_EXCEPTION(selection_exception(unexpected_value_type));
    }
}

int configuration_selector::
get_number_content(const std::string& qn) const {
    const auto& v(get_configuration_point_value(qn));

    try {
        return get_number_content(v);
    } catch(boost::exception& e) {
        BOOST_LOG_SEV(lg, error) << not_number << qn;
        e << extension_error_info(configuration_point_name + qn);
        throw;
    }
}

int configuration_selector::
get_number_content(const meta_model::feature& f) const {
    return get_number_content(f.name().qualified());
}

int configuration_selector::
get_number_content_or_default(const meta_model::feature& f) const {
    if (has_configuration_point(f))
        return get_number_content(f);

    ensure_default_value(f);

    try {
        return get_number_content(*f.default_value());
    } catch(boost::exception& e) {
        const auto n(f.name().qualified());
        BOOST_LOG_SEV(lg, error) << not_number << n
                                 << " (entry's default value)";
        e << extension_error_info(configuration_point_name + n);
        throw;
    }
}

const std::list<std::pair<std::string, std::string>>&
configuration_selector::get_key_value_pair_content(const meta_model::value& v) {
    try {
        const auto& b(dynamic_cast<const meta_model::key_value_pair&>(v));
        return b.content();
    } catch(const std::bad_cast& /*e*/) {
        BOOST_LOG_SEV(lg, error) << unexpected_value_type;
        BOOST_THROW_EXCEPTION(selection_exception(unexpected_value_type));
    }
}

const std::list<std::pair<std::string, std::string>>&
configuration_selector::get_key_value_pair_content(const std::string& qn) const {
    const auto& v(get_configuration_point_value(qn));

    try {
        return get_key_value_pair_content(v);
    } catch(boost::exception& e) {
        BOOST_LOG_SEV(lg, error) << not_kvp << qn;
        e << extension_error_info(configuration_point_name + qn);
        throw;
    }
}

const std::list<std::pair<std::string, std::string>>& configuration_selector::
get_key_value_pair_content(const meta_model::feature& f) const {
    return get_key_value_pair_content(f.name().qualified());
}

}
