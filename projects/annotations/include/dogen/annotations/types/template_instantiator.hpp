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
#ifndef DOGEN_ANNOTATIONS_TYPES_TEMPLATE_INSTANTIATOR_HPP
#define DOGEN_ANNOTATIONS_TYPES_TEMPLATE_INSTANTIATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <forward_list>
#include <unordered_set>
#include <unordered_map>
#include "dogen/annotations/types/type.hpp"
#include "dogen/annotations/types/type_template.hpp"
#include "dogen/annotations/types/ownership_hierarchy.hpp"

namespace dogen {
namespace annotations {

class template_instantiator {
public:
    template_instantiator(const std::forward_list<ownership_hierarchy>& oh);

private:
    /**
     * @brief Given the ownership hierarchy, returns all the facets by
     * the model the facet belongs to.
     */
    std::unordered_map<std::string, std::unordered_set<std::string> >
    obtain_facet_names_by_model_name(
        const std::forward_list<ownership_hierarchy>& ohs) const;

private:
    /**
     * @brief Ensures the field definition is in a valid state for
     * instantiation.
     */
    void validate(const type_template& tt) const;

public:
    type to_type(const type_template& tt) const;

private:
    /**
     * @brief Instantiates the field definition as a global template.
     */
    std::list<type> instantiate_global_template(const type_template& tt) const;

    /**
     * @brief Instantiates the field definition as a facet template.
     */
    std::list<type> instantiate_facet_template(const type_template& tt) const;

    /**
     * @brief Instantiates the field definition as a formatter template.
     */
    std::list<type>
    instantiate_formatter_template(const type_template& tt) const;

public:
    /**
     * @brief Returns true if the supplied field definition can be
     * instantiated.
     */
    bool is_instantiable(const type_template& tt) const;

    /**
     * @brief Instantiates the supplied field definition template into
     * a number of field definition instances.
     *
     * @pre is_instantiable(t) must be true.
     */
    std::list<type> instantiate(const type_template& tt) const;

private:
    const std::forward_list<ownership_hierarchy>& ownership_hierarchies_;
    const std::unordered_map<std::string, std::unordered_set<std::string> >
    facet_names_by_model_name_;
};

} }

#endif
