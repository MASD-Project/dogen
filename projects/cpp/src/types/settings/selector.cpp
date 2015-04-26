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
#include "dogen/utility/log/logger.hpp"
#include "dogen/cpp/types/settings/selection_error.hpp"
#include "dogen/cpp/types/settings/selector.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("cpp.settings.selector"));

const std::string formatter_settings_not_found(
    "Could not find settings for formatter: ");

}

namespace dogen {
namespace cpp {
namespace settings {

selector::selector(const bundle& b) : bundle_(b) {}

settings::formatter_settings selector::
formatter_settings_for_formatter(const std::string& formatter_name) const {
    const auto& fs(bundle_.formatter_settings());
    const auto i(fs.find(formatter_name));
    if (i == fs.end()) {
        BOOST_LOG_SEV(lg, error) << formatter_settings_not_found
                                 << formatter_name;

        BOOST_THROW_EXCEPTION(
            selection_error(formatter_settings_not_found + formatter_name));
    }
    return i->second;
}

} } }
