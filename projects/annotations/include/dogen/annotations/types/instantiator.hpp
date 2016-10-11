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
#ifndef DOGEN_ANNOTATIONS_TYPES_INSTANTIATOR_HPP
#define DOGEN_ANNOTATIONS_TYPES_INSTANTIATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <forward_list>
#include <unordered_set>
#include <unordered_map>
#include "dogen/annotations/types/field_definition.hpp"
#include "dogen/annotations/types/ownership_hierarchy.hpp"

namespace dogen {
namespace annotations {

class instantiator {
public:
    instantiator(const std::forward_list<ownership_hierarchy>& oh);

private:
    /**
     * @brief Given the ownership hierarchy, returns all the facets by
     * the model the facet belongs to.
     */
    std::unordered_map<std::string, std::unordered_set<std::string> >
    obtain_facet_names_by_model_name(
        const std::forward_list<ownership_hierarchy>& oh) const;

private:
    /**
     * @brief Ensures the field definition is in a valid state for
     * instantiation.
     */
    void validate(const type& fd) const;

private:
    /**
     * @brief Instantiates the field definition as a global template.
     */
    std::list<type>
    instantiate_global_template(const type& fd) const;

    /**
     * @brief Instantiates the field definition as a facet template.
     */
    std::list<type>
    instantiate_facet_template(const type& fd) const;

    /**
     * @brief Instantiates the field definition as a formatter template.
     */
    std::list<type>
    instantiate_formatter_template(const type& fd) const;

public:
    /**
     * @brief Returns true if the supplied field definition can be
     * instantiated.
     */
    bool is_instantiable(const type& fd) const;

    /**
     * @brief Instantiates the supplied field definition template into
     * a number of field definition instances.
     *
     * @pre is_instantiable(fd)fd must be true.
     */
    std::list<type>
    instantiate(const type& fd) const;

private:
    const std::forward_list<ownership_hierarchy>& ownership_hierarchy_;
    const std::unordered_map<std::string, std::unordered_set<std::string> >
    facet_names_by_model_name_;
};

} }

#endif
