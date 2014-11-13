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
#ifndef DOGEN_CPP_TYPES_BUNDLER_HPP
#define DOGEN_CPP_TYPES_BUNDLER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <unordered_map>
#include "dogen/sml/types/module.hpp"
#include "dogen/formatters/types/general_settings.hpp"
#include "dogen/cpp/types/settings_bundle.hpp"

namespace dogen {
namespace cpp {

/**
 * @brief Creates all the settings bundles for all facets.
 */
class bundler {
private:
    /**
     * @brief Create the facet settings
     */
    std::unordered_map<std::string, facet_settings>
    create_facet_settings(
        const std::unordered_map<std::string, facet_settings>&
        default_facet_settings_by_facet_id,
        const sml::module& m) const;

    /**
     * @brief Create the c++ settings
     */
    cpp_settings create_cpp_settings(const sml::module& m) const;

public:
    /**
     * @brief Builds the bundle of settings for all facets.
     */
    std::unordered_map<std::string, settings_bundle>
    bundle(const std::unordered_map<std::string, facet_settings>&
        default_facet_settings_by_facet_id,
        const dogen::formatters::general_settings gs,
        const sml::module& m) const;
};

} }

#endif
