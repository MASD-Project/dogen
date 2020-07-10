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
#ifndef DOGEN_PHYSICAL_TYPES_ENTITIES_GLOBAL_ENABLEMENT_PROPERTIES_HPP
#define DOGEN_PHYSICAL_TYPES_ENTITIES_GLOBAL_ENABLEMENT_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include "dogen.physical/types/entities/facet_properties.hpp"
#include "dogen.physical/types/entities/backend_properties.hpp"
#include "dogen.physical/types/entities/archetype_properties.hpp"
#include "dogen.physical/types/entities/denormalised_archetype_properties.hpp"

namespace dogen::physical::entities {

class global_enablement_properties final {
public:
    global_enablement_properties() = default;
    global_enablement_properties(const global_enablement_properties&) = default;
    global_enablement_properties(global_enablement_properties&&) = default;
    ~global_enablement_properties() = default;

public:
    global_enablement_properties(
        const std::unordered_map<std::string, dogen::physical::entities::backend_properties>& backend_properties,
        const std::unordered_map<std::string, dogen::physical::entities::facet_properties>& facet_properties,
        const std::unordered_map<std::string, dogen::physical::entities::archetype_properties>& archetype_properties,
        const std::unordered_map<std::string, dogen::physical::entities::denormalised_archetype_properties>& denormalised_archetype_properties);

public:
    const std::unordered_map<std::string, dogen::physical::entities::backend_properties>& backend_properties() const;
    std::unordered_map<std::string, dogen::physical::entities::backend_properties>& backend_properties();
    void backend_properties(const std::unordered_map<std::string, dogen::physical::entities::backend_properties>& v);
    void backend_properties(const std::unordered_map<std::string, dogen::physical::entities::backend_properties>&& v);

    const std::unordered_map<std::string, dogen::physical::entities::facet_properties>& facet_properties() const;
    std::unordered_map<std::string, dogen::physical::entities::facet_properties>& facet_properties();
    void facet_properties(const std::unordered_map<std::string, dogen::physical::entities::facet_properties>& v);
    void facet_properties(const std::unordered_map<std::string, dogen::physical::entities::facet_properties>&& v);

    const std::unordered_map<std::string, dogen::physical::entities::archetype_properties>& archetype_properties() const;
    std::unordered_map<std::string, dogen::physical::entities::archetype_properties>& archetype_properties();
    void archetype_properties(const std::unordered_map<std::string, dogen::physical::entities::archetype_properties>& v);
    void archetype_properties(const std::unordered_map<std::string, dogen::physical::entities::archetype_properties>&& v);

    const std::unordered_map<std::string, dogen::physical::entities::denormalised_archetype_properties>& denormalised_archetype_properties() const;
    std::unordered_map<std::string, dogen::physical::entities::denormalised_archetype_properties>& denormalised_archetype_properties();
    void denormalised_archetype_properties(const std::unordered_map<std::string, dogen::physical::entities::denormalised_archetype_properties>& v);
    void denormalised_archetype_properties(const std::unordered_map<std::string, dogen::physical::entities::denormalised_archetype_properties>&& v);

public:
    bool operator==(const global_enablement_properties& rhs) const;
    bool operator!=(const global_enablement_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(global_enablement_properties& other) noexcept;
    global_enablement_properties& operator=(global_enablement_properties other);

private:
    std::unordered_map<std::string, dogen::physical::entities::backend_properties> backend_properties_;
    std::unordered_map<std::string, dogen::physical::entities::facet_properties> facet_properties_;
    std::unordered_map<std::string, dogen::physical::entities::archetype_properties> archetype_properties_;
    std::unordered_map<std::string, dogen::physical::entities::denormalised_archetype_properties> denormalised_archetype_properties_;
};

}

namespace std {

template<>
inline void swap(
    dogen::physical::entities::global_enablement_properties& lhs,
    dogen::physical::entities::global_enablement_properties& rhs) {
    lhs.swap(rhs);
}

}

#endif
