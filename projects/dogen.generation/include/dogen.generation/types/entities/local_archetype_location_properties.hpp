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
#ifndef DOGEN_GENERATION_TYPES_ENTITIES_LOCAL_ARCHETYPE_LOCATION_PROPERTIES_HPP
#define DOGEN_GENERATION_TYPES_ENTITIES_LOCAL_ARCHETYPE_LOCATION_PROPERTIES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/optional.hpp>

namespace dogen::generation::entities {

class local_archetype_location_properties final {
public:
    local_archetype_location_properties() = default;
    local_archetype_location_properties(const local_archetype_location_properties&) = default;
    ~local_archetype_location_properties() = default;

public:
    local_archetype_location_properties(local_archetype_location_properties&& rhs);

public:
    local_archetype_location_properties(
        const boost::optional<bool>& facet_enabled,
        const boost::optional<bool>& archetype_enabled,
        const boost::optional<bool>& facet_overwrite,
        const boost::optional<bool>& archetype_overwrite);

public:
    const boost::optional<bool>& facet_enabled() const;
    boost::optional<bool>& facet_enabled();
    void facet_enabled(const boost::optional<bool>& v);
    void facet_enabled(const boost::optional<bool>&& v);

    const boost::optional<bool>& archetype_enabled() const;
    boost::optional<bool>& archetype_enabled();
    void archetype_enabled(const boost::optional<bool>& v);
    void archetype_enabled(const boost::optional<bool>&& v);

    const boost::optional<bool>& facet_overwrite() const;
    boost::optional<bool>& facet_overwrite();
    void facet_overwrite(const boost::optional<bool>& v);
    void facet_overwrite(const boost::optional<bool>&& v);

    const boost::optional<bool>& archetype_overwrite() const;
    boost::optional<bool>& archetype_overwrite();
    void archetype_overwrite(const boost::optional<bool>& v);
    void archetype_overwrite(const boost::optional<bool>&& v);

public:
    bool operator==(const local_archetype_location_properties& rhs) const;
    bool operator!=(const local_archetype_location_properties& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(local_archetype_location_properties& other) noexcept;
    local_archetype_location_properties& operator=(local_archetype_location_properties other);

private:
    boost::optional<bool> facet_enabled_;
    boost::optional<bool> archetype_enabled_;
    boost::optional<bool> facet_overwrite_;
    boost::optional<bool> archetype_overwrite_;
};

}

namespace std {

template<>
inline void swap(
    dogen::generation::entities::local_archetype_location_properties& lhs,
    dogen::generation::entities::local_archetype_location_properties& rhs) {
    lhs.swap(rhs);
}

}

#endif
