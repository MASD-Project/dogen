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
#ifndef DOGEN_CPP_TYPES_FORMATTERS_FACET_FACTORY_HPP
#define DOGEN_CPP_TYPES_FORMATTERS_FACET_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <forward_list>
#include <unordered_map>
#include "dogen/cpp/types/settings/global_settings.hpp"
#include "dogen/cpp/types/formatters/facet.hpp"
#include "dogen/cpp/types/formatters/container.hpp"

namespace dogen {
namespace cpp {
namespace formatters {

/**
 * @brief Builds a list of facets.
 */
class facet_factory {
public:
    /**
     * @brief Generates the list of facets from the given inputs.
     */
    std::forward_list<facet> build(
        const std::unordered_map<std::string, container>& formatters_by_facet,
        const std::unordered_map<std::string, settings::global_settings>&
        global_settings_for_facet) const;
};

} } }

#endif
