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
#include "dogen/cpp/types/facet_settings_factory.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("cpp.facet_settings_factory"));

const std::string dot(".");

/**
 * @brief Given a facet and a trait, returns the fully qualified
 * version of the trait.
 */
inline std::string
qualify(const std::string& facet_id, const std::string& trait) {
    return facet_id + dot + trait;
}

}

namespace dogen {
namespace cpp {

facet_settings facet_settings_factory::read_settings(
    const facet_settings& default_settings, const std::string& facet_id,
    const dynamic::object& o) const {

    facet_settings r(default_settings);
    using namespace dynamic;

    const auto enabled_trait(qualify(facet_id, traits::facet::enabled()));
    if (has_field(o, enabled_trait))
        r.enabled(get_boolean_content(o, enabled_trait));

    const auto directory_trait(qualify(facet_id, traits::facet::directory()));
    if (has_field(o, directory_trait))
        r.directory(get_text_content(o, directory_trait));

    const auto postfix_trait(qualify(facet_id, traits::facet::postfix()));
    if (has_field(o, postfix_trait))
        r.postfix(get_text_content(o, postfix_trait));

    return r;
}

std::unordered_map<std::string, facet_settings> facet_settings_factory::build(
    const std::unordered_map<std::string, facet_settings>&
    default_facet_settings_by_facet_id,
    const dynamic::object& o) const {

    std::unordered_map<std::string, facet_settings> r;
    for (const auto& pair : default_facet_settings_by_facet_id) {
        const auto& facet_id(pair.first);
        const auto& default_settings(pair.second);
        const auto s(read_settings(default_settings, facet_id, o));
        r.insert(std::make_pair(facet_id, s));
    }
    return r;
}

} }
