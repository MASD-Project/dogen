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
#ifndef DOGEN_PHYSICAL_TYPES_ENTITIES_DENORMALISED_ARCHETYPE_PROPERTIES_HPP
#define DOGEN_PHYSICAL_TYPES_ENTITIES_DENORMALISED_ARCHETYPE_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/optional.hpp>

namespace dogen::physical::entities {

class denormalised_archetype_properties final {
public:
    denormalised_archetype_properties(const denormalised_archetype_properties&) = default;
    ~denormalised_archetype_properties() = default;

public:
    denormalised_archetype_properties();

public:
    denormalised_archetype_properties(denormalised_archetype_properties&& rhs);

public:
    denormalised_archetype_properties(
        const bool backend_enabled,
        const bool facet_enabled,
        const bool facet_overwrite,
        const bool archetype_enabled,
        const boost::optional<bool>& archetype_overwrite);

public:
    bool backend_enabled() const;
    void backend_enabled(const bool v);

    bool facet_enabled() const;
    void facet_enabled(const bool v);

    bool facet_overwrite() const;
    void facet_overwrite(const bool v);

    bool archetype_enabled() const;
    void archetype_enabled(const bool v);

    const boost::optional<bool>& archetype_overwrite() const;
    boost::optional<bool>& archetype_overwrite();
    void archetype_overwrite(const boost::optional<bool>& v);
    void archetype_overwrite(const boost::optional<bool>&& v);

public:
    bool operator==(const denormalised_archetype_properties& rhs) const;
    bool operator!=(const denormalised_archetype_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(denormalised_archetype_properties& other) noexcept;
    denormalised_archetype_properties& operator=(denormalised_archetype_properties other);

private:
    bool backend_enabled_;
    bool facet_enabled_;
    bool facet_overwrite_;
    bool archetype_enabled_;
    boost::optional<bool> archetype_overwrite_;
};

}

namespace std {

template<>
inline void swap(
    dogen::physical::entities::denormalised_archetype_properties& lhs,
    dogen::physical::entities::denormalised_archetype_properties& rhs) {
    lhs.swap(rhs);
}

}

#endif
