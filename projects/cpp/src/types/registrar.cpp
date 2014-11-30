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
#include "dogen/cpp/types/registrar_error.hpp"
#include "dogen/cpp/types/registrar.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("cpp.registrar"));

const std::string duplicate_facet_id(
    "Attempt to register settings for the same facet more than once");
const std::string duplicate_formatter_id(
    "Attempt to register settings for the same formatter more than once");
const std::string no_formatters("No formatters provided.");
const std::string null_formatter("Formatter supplied is null");

}

namespace dogen {
namespace cpp {

void registrar::validate() const {
    if (formatter_container_.class_formatters().empty()) {
        BOOST_LOG_SEV(lg, error) << no_formatters;
        BOOST_THROW_EXCEPTION(registrar_error(no_formatters));
    }
    BOOST_LOG_SEV(lg, debug) << "Registrar is in a valid state.";
}

void registrar::register_default_facet_settings(const std::string& facet_id,
    const facet_settings& s) {
    const auto pair(std::make_pair(facet_id, s));
    const auto result(default_facet_settings_by_facet_id_.insert(pair));
    if (!result.second) {
        BOOST_LOG_SEV(lg, error) << duplicate_facet_id;
        BOOST_THROW_EXCEPTION(registrar_error(duplicate_facet_id));
    }
}

void registrar::register_default_formatter_settings(
    const std::string& formatter_id, const formatter_settings& s) {
    const auto pair(std::make_pair(formatter_id, s));
    const auto result(default_formatter_settings_by_formatter_id_.insert(pair));
    if (!result.second) {
        BOOST_LOG_SEV(lg, error) << duplicate_formatter_id;
        BOOST_THROW_EXCEPTION(registrar_error(duplicate_formatter_id));
    }
}

void registrar::register_formatter(
    std::shared_ptr<formatters::class_formatter_interface> f) {
    // note: not logging by design
    if (!f)
        BOOST_THROW_EXCEPTION(registrar_error(null_formatter));

    formatter_container_.class_formatters().push_front(f);
}

const formatters::container& registrar::formatter_container() const {
    return formatter_container_;
}

const std::unordered_map<std::string, facet_settings>&
registrar::default_facet_settings_by_facet_id() const {
    return default_facet_settings_by_facet_id_;
}

} }
