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
#ifndef DOGEN_PHYSICAL_TYPES_ENTITIES_ARCHETYPE_NAME_SET_HPP
#define DOGEN_PHYSICAL_TYPES_ENTITIES_ARCHETYPE_NAME_SET_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include <unordered_map>
#include "dogen.physical/types/entities/meta_name.hpp"

namespace dogen::physical::entities {

/**
 * @brief Groups archetype names for a given logical meta-name.
 */
class archetype_name_set final {
public:
    archetype_name_set() = default;
    archetype_name_set(const archetype_name_set&) = default;
    archetype_name_set(archetype_name_set&&) = default;
    ~archetype_name_set() = default;

public:
    archetype_name_set(
        const std::string& logical_meta_element_id,
        const std::list<dogen::physical::entities::meta_name>& meta_names,
        const std::unordered_map<std::string, std::string>& canonical_locations,
        const std::unordered_map<std::string, std::string>& archetype_for_label);

public:
    /**
     * @brief Identifier of the meta-element in the logical dimension.
     */
    /**@{*/
    const std::string& logical_meta_element_id() const;
    std::string& logical_meta_element_id();
    void logical_meta_element_id(const std::string& v);
    void logical_meta_element_id(const std::string&& v);
    /**@}*/

    /**
     * @brief All meta-names that belong to this group.
     */
    /**@{*/
    const std::list<dogen::physical::entities::meta_name>& meta_names() const;
    std::list<dogen::physical::entities::meta_name>& meta_names();
    void meta_names(const std::list<dogen::physical::entities::meta_name>& v);
    void meta_names(const std::list<dogen::physical::entities::meta_name>&& v);
    /**@}*/

    /**
     * @brief Maps a concrete archetype location to its canonical form, if the canonical
     * form is supported. Otherwise no such mapping will exist.
     */
    /**@{*/
    const std::unordered_map<std::string, std::string>& canonical_locations() const;
    std::unordered_map<std::string, std::string>& canonical_locations();
    void canonical_locations(const std::unordered_map<std::string, std::string>& v);
    void canonical_locations(const std::unordered_map<std::string, std::string>&& v);
    /**@}*/

    /**
     * @brief Maps a label to archetype ID within the present logical manifold.
     */
    /**@{*/
    const std::unordered_map<std::string, std::string>& archetype_for_label() const;
    std::unordered_map<std::string, std::string>& archetype_for_label();
    void archetype_for_label(const std::unordered_map<std::string, std::string>& v);
    void archetype_for_label(const std::unordered_map<std::string, std::string>&& v);
    /**@}*/

public:
    bool operator==(const archetype_name_set& rhs) const;
    bool operator!=(const archetype_name_set& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(archetype_name_set& other) noexcept;
    archetype_name_set& operator=(archetype_name_set other);

private:
    std::string logical_meta_element_id_;
    std::list<dogen::physical::entities::meta_name> meta_names_;
    std::unordered_map<std::string, std::string> canonical_locations_;
    std::unordered_map<std::string, std::string> archetype_for_label_;
};

}

namespace std {

template<>
inline void swap(
    dogen::physical::entities::archetype_name_set& lhs,
    dogen::physical::entities::archetype_name_set& rhs) {
    lhs.swap(rhs);
}

}

#endif
