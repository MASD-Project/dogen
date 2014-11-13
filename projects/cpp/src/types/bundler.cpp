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
#include "dogen/cpp/types/cpp_settings.hpp"
#include "dogen/cpp/types/facet_settings.hpp"
#include "dogen/cpp/types/meta_data/cpp_settings_factory.hpp"
#include "dogen/cpp/types/meta_data/facet_settings_factory.hpp"
#include "dogen/cpp/types/bundler.hpp"

namespace dogen {
namespace cpp {

std::unordered_map<std::string, facet_settings>
bundler::create_facet_settings(
    const std::unordered_map<std::string, facet_settings>&
    default_facet_settings_by_facet_id, const sml::module& m) const {
    meta_data::facet_settings_factory f;
    return f.build(default_facet_settings_by_facet_id, m.meta_data());
}

cpp_settings bundler::create_cpp_settings(const sml::module& m) const {
    meta_data::cpp_settings_factory f;
    return f.build(m.meta_data());
}

std::unordered_map<std::string, settings_bundle> bundler::
bundle(const std::unordered_map<std::string, facet_settings>&
    default_facet_settings_by_facet_id,
    const dogen::formatters::general_settings gs, const sml::module& m) const {

    const auto cs(create_cpp_settings(m));
    const auto fs(create_facet_settings(default_facet_settings_by_facet_id, m));

    std::unordered_map<std::string, settings_bundle> r;
    for (auto pair : fs) {
        settings_bundle b;
        b.general_settings(gs);
        b.cpp_settings(cs);
        b.facet_settings(pair.second);
        r[pair.first] = b;
    }
    return r;
}

} }
