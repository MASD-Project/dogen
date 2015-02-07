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
#include "dogen/cpp/types/settings/selection_error.hpp"
#include "dogen/cpp/types/settings/selector.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("cpp.settings.selector"));

const std::string facet_name_not_found(
    "Could not find facet settings for facet name: ");
const std::string formatter_name_not_found(
    "Could not find formatter settings for formatter name:");
}

namespace dogen {
namespace cpp {
namespace settings {

selector::selector(const cpp::settings::settings& s) : settings_(s) { }

const dogen::formatters::general_settings& selector::select_general_settings(
    const std::string& identity) const {

    const auto& ls(settings_.local_settings());
    const auto i(ls.find(identity));
    if (i != ls.end())
        return i->second.general_settings();

    return settings_.global_settings().general_settings();
}

const dogen::formatters::annotation& selector::select_annotation(
    const std::string& identity) const {
    const auto& gs(select_general_settings(identity));
    return gs.annotation();
}

const cpp_settings& selector::select_cpp_settings() const {
    return settings_.global_settings().cpp_settings();
}

const facet_settings& selector::
select_facet_settings(const std::string& facet_name) const {
    const auto& fs(settings_.global_settings().facet_settings());
    const auto i(fs.find(facet_name));
    if (i == fs.end()) {
        BOOST_LOG_SEV(lg, error) << facet_name_not_found << facet_name;
        BOOST_THROW_EXCEPTION(
            selection_error(facet_name_not_found + facet_name));
    }
    return i->second;
}

const formatter_settings& selector::
select_formatter_settings(const std::string& identity,
    const std::string& formatter_name) const {
    const auto& ls(settings_.local_settings());
    const auto i(ls.find(identity));
    if (i != ls.end()) {
        const auto& lfs(i->second.formatter_settings());
        const auto i(lfs.find(formatter_name));
        if (i != lfs.end())
            return i->second;
    }

    const auto& gfs(settings_.global_settings().formatter_settings());
    const auto j(gfs.find(formatter_name));
    if (j == gfs.end()) {
        BOOST_LOG_SEV(lg, error) << formatter_name_not_found << formatter_name;
        BOOST_THROW_EXCEPTION(
            selection_error(formatter_name_not_found + formatter_name));
    }
    return j->second;
}

const cpp::settings::settings& selector::settings() const {
    return settings_;
}

} } }
