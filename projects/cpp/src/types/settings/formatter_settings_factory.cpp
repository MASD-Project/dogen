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
#include "dogen/dynamic/types/content_extensions.hpp"
#include "dogen/cpp/types/traits.hpp"
#include "dogen/cpp/types/settings/formatter_settings_factory.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("cpp.settings.formatter_settings_factory"));

const std::string dot(".");

/**
 * @brief Given a formatter and a trait, returns the fully qualified
 * version of the trait.
 */
inline std::string
qualify(const std::string& formatter_id, const std::string& trait) {
    return formatter_id + dot + trait;
}

}

namespace dogen {
namespace cpp {
namespace settings {

formatter_settings formatter_settings_factory::
read_settings(const std::string& formatter_id, const dynamic::object& o) const {
    using namespace dynamic;

    formatter_settings r;
    const auto enabled_trait(qualify(formatter_id,
            traits::formatter::enabled()));
    if (has_field(o, enabled_trait))
        r.enabled(get_boolean_content(o, enabled_trait));

    const std::string postfix_trait(
        qualify(formatter_id, traits::formatter::additional_postfix()));
    if (has_field(o, postfix_trait))
        r.postfix(get_text_content(o, postfix_trait));

    return r;
}

std::unordered_map<std::string, formatter_settings>
formatter_settings_factory::build(const dynamic::object& /*o*/) const {

    std::unordered_map<std::string, formatter_settings> r;
    // for (const auto& pair : default_formatter_settings_by_formatter_id) {
    //     const auto& formatter_id(pair.first);
    //     const auto& default_settings(pair.second);
    //     const auto s(read_settings(default_settings, formatter_id, o));
    //     r.insert(std::make_pair(formatter_id, s));
    // }
    return r;
}

} } }
