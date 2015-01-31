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
#ifndef DOGEN_CPP_TYPES_SETTINGS_GLOBAL_SETTINGS_FACTORY_HPP
#define DOGEN_CPP_TYPES_SETTINGS_GLOBAL_SETTINGS_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <unordered_map>
#include "dogen/sml/types/module.hpp"
#include "dogen/formatters/types/general_settings.hpp"
#include "dogen/cpp/types/settings/cpp_settings.hpp"
#include "dogen/cpp/types/settings/global_settings.hpp"
#include "dogen/cpp/types/settings/facet_settings.hpp"
#include "dogen/cpp/types/settings/formatter_settings.hpp"

namespace dogen {
namespace cpp {
namespace settings {

/**
 * @brief Creates all the global settings for all facets.
 */
class global_settings_factory {
private:
    /**
     * @brief Create the facet settings
     */
    std::unordered_map<std::string, facet_settings>
    create_facet_settings(
        const std::unordered_map<std::string, facet_settings>&
        default_facet_settings_by_facet_id,
        const sml::module& model_module) const;

    /**
     * @brief Create the formatter settings
     */
    std::unordered_map<std::string, formatter_settings>
    create_formatter_settings(
        const std::unordered_map<std::string, formatter_settings>&
        default_formatter_settings_by_formatter_id,
        const sml::module& model_module) const;

    /**
     * @brief Create the c++ settings
     */
    cpp_settings create_cpp_settings(const sml::module& m) const;

public:
    /**
     * @brief Builds the global settings for all facets.
     */
    std::unordered_map<std::string, global_settings>
    build(const std::unordered_map<std::string, facet_settings>&
        default_facet_settings_by_facet_id,
        /*const std::unordered_map<std::string, formatter_settings>&
          default_formatter_settings_by_formatter_id, FIXME*/
        const dogen::formatters::general_settings& gs,
        const sml::module& model_module) const;
};

} } }

#endif
