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
#ifndef DOGEN_TEXT_TYPES_HELPERS_TEXT_TO_TEXT_TRANSFORM_DATA_HPP
#define DOGEN_TEXT_TYPES_HELPERS_TEXT_TO_TEXT_TRANSFORM_DATA_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include <unordered_set>
#include "dogen.physical/types/entities/archetype.hpp"
#include "dogen.text/types/entities/element_artefacts.hpp"

namespace dogen::text::helpers {

class text_to_text_transform_data final {
public:
    text_to_text_transform_data() = default;
    text_to_text_transform_data(const text_to_text_transform_data&) = default;
    text_to_text_transform_data(text_to_text_transform_data&&) = default;
    ~text_to_text_transform_data() = default;

public:
    text_to_text_transform_data(
        const std::string& name,
        const std::list<dogen::physical::entities::archetype>& archetypes,
        const std::unordered_set<std::string>& logical_meta_model_ids,
        const std::list<dogen::text::entities::element_artefacts>& target_logical_elements);

public:
    /**
     * @brief Name of the T2T transform.
     */
    /**@{*/
    const std::string& name() const;
    std::string& name();
    void name(const std::string& v);
    void name(const std::string&& v);
    /**@}*/

    /**
     * @brief All of the archetypes that requested this T2T transform.
     */
    /**@{*/
    const std::list<dogen::physical::entities::archetype>& archetypes() const;
    std::list<dogen::physical::entities::archetype>& archetypes();
    void archetypes(const std::list<dogen::physical::entities::archetype>& v);
    void archetypes(const std::list<dogen::physical::entities::archetype>&& v);
    /**@}*/

    /**
     * @brief All of the logical model IDs for this T2T transform.
     */
    /**@{*/
    const std::unordered_set<std::string>& logical_meta_model_ids() const;
    std::unordered_set<std::string>& logical_meta_model_ids();
    void logical_meta_model_ids(const std::unordered_set<std::string>& v);
    void logical_meta_model_ids(const std::unordered_set<std::string>&& v);
    /**@}*/

    /**
     * @brief All of the entities that the T2T transform needs to operate against.
     */
    /**@{*/
    const std::list<dogen::text::entities::element_artefacts>& target_logical_elements() const;
    std::list<dogen::text::entities::element_artefacts>& target_logical_elements();
    void target_logical_elements(const std::list<dogen::text::entities::element_artefacts>& v);
    void target_logical_elements(const std::list<dogen::text::entities::element_artefacts>&& v);
    /**@}*/

public:
    bool operator==(const text_to_text_transform_data& rhs) const;
    bool operator!=(const text_to_text_transform_data& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(text_to_text_transform_data& other) noexcept;
    text_to_text_transform_data& operator=(text_to_text_transform_data other);

private:
    std::string name_;
    std::list<dogen::physical::entities::archetype> archetypes_;
    std::unordered_set<std::string> logical_meta_model_ids_;
    std::list<dogen::text::entities::element_artefacts> target_logical_elements_;
};

}

namespace std {

template<>
inline void swap(
    dogen::text::helpers::text_to_text_transform_data& lhs,
    dogen::text::helpers::text_to_text_transform_data& rhs) {
    lhs.swap(rhs);
}

}

#endif
