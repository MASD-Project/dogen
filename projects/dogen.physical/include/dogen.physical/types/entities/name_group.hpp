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
#ifndef DOGEN_PHYSICAL_TYPES_ENTITIES_NAME_GROUP_HPP
#define DOGEN_PHYSICAL_TYPES_ENTITIES_NAME_GROUP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include <unordered_map>
#include "dogen.physical/types/entities/location.hpp"

namespace dogen::physical::entities {

class name_group final {
public:
    name_group() = default;
    name_group(const name_group&) = default;
    name_group(name_group&&) = default;
    ~name_group() = default;

public:
    name_group(
        const std::list<dogen::physical::entities::location>& locations,
        const std::unordered_map<std::string, std::string>& canonical_locations);

public:
    /**
     * @brief All archetype locations that belong to this group.
     */
    /**@{*/
    const std::list<dogen::physical::entities::location>& locations() const;
    std::list<dogen::physical::entities::location>& locations();
    void locations(const std::list<dogen::physical::entities::location>& v);
    void locations(const std::list<dogen::physical::entities::location>&& v);
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

public:
    bool operator==(const name_group& rhs) const;
    bool operator!=(const name_group& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(name_group& other) noexcept;
    name_group& operator=(name_group other);

private:
    std::list<dogen::physical::entities::location> locations_;
    std::unordered_map<std::string, std::string> canonical_locations_;
};

}

namespace std {

template<>
inline void swap(
    dogen::physical::entities::name_group& lhs,
    dogen::physical::entities::name_group& rhs) {
    lhs.swap(rhs);
}

}

#endif
