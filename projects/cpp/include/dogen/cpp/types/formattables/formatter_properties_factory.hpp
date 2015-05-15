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
#ifndef DOGEN_CPP_TYPES_FORMATTABLES_FORMATTER_PROPERTIES_FACTORY_HPP
#define DOGEN_CPP_TYPES_FORMATTABLES_FORMATTER_PROPERTIES_FACTORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include "dogen/dynamic/schema/types/object.hpp"
#include "dogen/dynamic/schema/types/repository.hpp"
#include "dogen/cpp/types/formatters/container.hpp"
#include "dogen/cpp/types/formattables/path_derivatives.hpp"
#include "dogen/cpp/types/formattables/formatter_properties.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

/**
 * @brief Creates the formatter properties.
 */

class formatter_properties_factory {
public:
    formatter_properties_factory(const dynamic::schema::repository& rp,
        const dynamic::schema::object& root_object,
        const formatters::container& fc);

private:
    /**
     * @brief Obtain integrated facets.
     */
    std::unordered_map<std::string, std::unordered_set<std::string> >
    obtain_integrated_facets(const dynamic::schema::repository& rp,
        const dynamic::schema::object& root_object,
        const formatters::container& fc) const;

public:
    /**
     * @brief Create the formatter properties.
     */
    std::unordered_map<std::string, formatter_properties>
    make(const std::unordered_map<std::string, path_derivatives>&
        path_derivatives,
        const std::unordered_map<std::string, std::list<std::string> >&
        inclusion_dependencies) const;

public:
    const std::unordered_map<std::string, std::unordered_set<std::string> >
    integrated_facets_;
};

} } }

#endif
