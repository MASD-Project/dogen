/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
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
#ifndef DOGEN_QUILT_CPP_TYPES_FORMATTABLES_FORMATTER_PROPERTIES_FACTORY_HPP
#define DOGEN_QUILT_CPP_TYPES_FORMATTABLES_FORMATTER_PROPERTIES_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include "dogen/quilt.cpp/types/formattables/path_derivatives.hpp"
#include "dogen/quilt.cpp/types/formattables/formatter_properties.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

/**
 * @brief Creates the formatter properties.
 */
class formatter_properties_factory {
public:
    /**
     * @brief Create the formatter properties.
     */
    std::unordered_map<std::string, formatter_properties>
    make(const std::unordered_map<std::string, path_derivatives>&
        path_derivatives,
        const std::unordered_map<std::string, std::list<std::string> >&
        inclusion_dependencies,
        const std::unordered_map<std::string, bool>& enablement,
        std::unordered_set<std::string> enabled_formatters,
        std::unordered_map<std::string, std::string>
        facet_directory_for_facet) const;
};

} } } }

#endif
