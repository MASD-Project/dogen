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
#include "dogen/sml/types/meta_data/reader.hpp"
#include "dogen/cpp/types/meta_data/traits.hpp"
#include "dogen/cpp/types/meta_data/facet_settings_factory.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("cpp.meta_data.facet_settings_factory"));

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
namespace meta_data {

facet_settings facet_settings_factory::read_settings(
    const facet_settings& default_settings,
    const std::string& facet_id,
    const boost::property_tree::ptree& meta_data) const {

    facet_settings r(default_settings);
    sml::meta_data::reader reader(meta_data);
    const auto enabled_trait(qualify(facet_id, traits::facet::enabled()));
    if (reader.has_key(enabled_trait)) {
        const auto value(reader.get(enabled_trait));
        r.enabled(value == traits::bool_true());
    }

    const auto directory_trait(qualify(facet_id, traits::facet::directory()));
    if (reader.has_key(directory_trait)) {
        const auto value(reader.get(directory_trait));
        r.directory(value);
    }

    const auto postfix_trait(qualify(facet_id, traits::facet::postfix()));
    if (reader.has_key(postfix_trait)) {
        const auto value(reader.get(postfix_trait));
        r.postfix(value);
    }
    return r;
}

std::unordered_map<std::string, facet_settings> facet_settings_factory::build(
    const std::unordered_map<std::string, facet_settings>&
    default_facet_settings_by_facet_id,
    const boost::property_tree::ptree& meta_data) const {

    std::unordered_map<std::string, facet_settings> r;
    for (const auto& pair : default_facet_settings_by_facet_id) {
        const auto& facet_id(pair.first);
        const auto& default_settings(pair.second);
        const auto s(read_settings(default_settings, facet_id, meta_data));
        r.insert(std::make_pair(facet_id, s));
    }
    return r;
}

} } }
