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
#ifndef DOGEN_ANNOTATIONS_TYPES_ARCHETYPE_LOCATIONS_GROUP_HPP
#define DOGEN_ANNOTATIONS_TYPES_ARCHETYPE_LOCATIONS_GROUP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include <unordered_map>
#include "dogen.annotations/types/archetype_location.hpp"

namespace dogen {
namespace annotations {

class archetype_locations_group final {
public:
    archetype_locations_group() = default;
    archetype_locations_group(const archetype_locations_group&) = default;
    archetype_locations_group(archetype_locations_group&&) = default;
    ~archetype_locations_group() = default;

public:
    archetype_locations_group(
        const std::list<dogen::annotations::archetype_location>& archetype_locations,
        const std::unordered_map<std::string, std::string>& canonical_archetype_locations);

public:
    /**
     * @brief All archetype locations that belong to this group.
     */
    /**@{*/
    const std::list<dogen::annotations::archetype_location>& archetype_locations() const;
    std::list<dogen::annotations::archetype_location>& archetype_locations();
    void archetype_locations(const std::list<dogen::annotations::archetype_location>& v);
    void archetype_locations(const std::list<dogen::annotations::archetype_location>&& v);
    /**@}*/

    /**
     * @brief Maps a concrete archetype location to its canonical form, if the canonical
     * form is supported. Otherwise no such mapping will exist.
     */
    /**@{*/
    const std::unordered_map<std::string, std::string>& canonical_archetype_locations() const;
    std::unordered_map<std::string, std::string>& canonical_archetype_locations();
    void canonical_archetype_locations(const std::unordered_map<std::string, std::string>& v);
    void canonical_archetype_locations(const std::unordered_map<std::string, std::string>&& v);
    /**@}*/

public:
    bool operator==(const archetype_locations_group& rhs) const;
    bool operator!=(const archetype_locations_group& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(archetype_locations_group& other) noexcept;
    archetype_locations_group& operator=(archetype_locations_group other);

private:
    std::list<dogen::annotations::archetype_location> archetype_locations_;
    std::unordered_map<std::string, std::string> canonical_archetype_locations_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::annotations::archetype_locations_group& lhs,
    dogen::annotations::archetype_locations_group& rhs) {
    lhs.swap(rhs);
}

}

#endif
