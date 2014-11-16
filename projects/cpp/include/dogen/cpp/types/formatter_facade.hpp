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
#ifndef DOGEN_CPP_TYPES_FORMATTER_FACADE_HPP
#define DOGEN_CPP_TYPES_FORMATTER_FACADE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <forward_list>
#include <unordered_map>
#include "dogen/cpp/types/registrar.hpp"
#include "dogen/formatters/types/file.hpp"
#include "dogen/cpp/types/settings_bundle.hpp"
#include "dogen/cpp/types/formatters/class_formatter_interface.hpp"

namespace dogen {
namespace cpp {

/**
 * @brief Responsible for dispatching the entity to the appropriate
 * formatters.
 */
class formatter_facade {
public:
    /**
     * @brief Utility container to hold together all of the facet
     * related bits.
     */
    struct facet {
        std::string id;
        settings_bundle bundle;
        std::forward_list<
            std::shared_ptr<formatters::class_formatter_interface>
            > class_formatters;
    };

public:
    /**
     * @brief Reads all the information in the facet settings and
     * registrar to build the list of facets.
     */
    std::forward_list<facet> build_facets(const registrar& rg,
        const std::unordered_map<std::string, settings_bundle>&
        settings_bundle_for_facet) const;

public:
    formatter_facade(const registrar& reg,
        const std::unordered_map<std::string, settings_bundle>&
        settings_bundle_for_facet);

public:
    /**
     * @brief Converts the supplied entity into all supported
     * representations.
     */
    std::forward_list<dogen::formatters::file> format(const entity& e) const;

private:
    const std::forward_list<facet> facets_;
};

} }

#endif
