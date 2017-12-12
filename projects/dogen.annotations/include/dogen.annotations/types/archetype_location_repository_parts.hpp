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
#ifndef DOGEN_ANNOTATIONS_TYPES_ARCHETYPE_LOCATION_REPOSITORY_PARTS_HPP
#define DOGEN_ANNOTATIONS_TYPES_ARCHETYPE_LOCATION_REPOSITORY_PARTS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include <unordered_map>
#include "dogen.annotations/types/archetype_location.hpp"
#include "dogen.annotations/types/archetype_locations_group.hpp"
#include "dogen.annotations/serialization/archetype_location_repository_parts_fwd_ser.hpp"

namespace dogen {
namespace annotations {

class archetype_location_repository_parts final {
public:
    archetype_location_repository_parts() = default;
    archetype_location_repository_parts(const archetype_location_repository_parts&) = default;
    archetype_location_repository_parts(archetype_location_repository_parts&&) = default;
    ~archetype_location_repository_parts() = default;

public:
    archetype_location_repository_parts(
        const std::list<dogen::annotations::archetype_location>& archetype_locations,
        const std::unordered_map<std::string, dogen::annotations::archetype_locations_group>& archetype_locations_by_meta_name,
        const std::unordered_map<std::string, std::list<dogen::annotations::archetype_location> >& archetype_locations_by_family,
        const std::unordered_map<std::string, std::list<dogen::annotations::archetype_location> >& archetype_locations_by_intra_backend_segment);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::annotations::archetype_location_repository_parts& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::annotations::archetype_location_repository_parts& v, unsigned int version);

public:
    /**
     * @brief All archetype locations for the archetypes owned by this transform,
     * listing all available backends, facets and archetypes.
     */
    /**@{*/
    const std::list<dogen::annotations::archetype_location>& archetype_locations() const;
    std::list<dogen::annotations::archetype_location>& archetype_locations();
    void archetype_locations(const std::list<dogen::annotations::archetype_location>& v);
    void archetype_locations(const std::list<dogen::annotations::archetype_location>&& v);
    /**@}*/

    /**
     * @brief Returns the archetype locations for each meta name.
     */
    /**@{*/
    const std::unordered_map<std::string, dogen::annotations::archetype_locations_group>& archetype_locations_by_meta_name() const;
    std::unordered_map<std::string, dogen::annotations::archetype_locations_group>& archetype_locations_by_meta_name();
    void archetype_locations_by_meta_name(const std::unordered_map<std::string, dogen::annotations::archetype_locations_group>& v);
    void archetype_locations_by_meta_name(const std::unordered_map<std::string, dogen::annotations::archetype_locations_group>&& v);
    /**@}*/

    /**
     * @brief All archetype locations for a given family.
     *
     * Families are backend specific sets of archetype locations, with associated
     * properties such as file extensions.
     */
    /**@{*/
    const std::unordered_map<std::string, std::list<dogen::annotations::archetype_location> >& archetype_locations_by_family() const;
    std::unordered_map<std::string, std::list<dogen::annotations::archetype_location> >& archetype_locations_by_family();
    void archetype_locations_by_family(const std::unordered_map<std::string, std::list<dogen::annotations::archetype_location> >& v);
    void archetype_locations_by_family(const std::unordered_map<std::string, std::list<dogen::annotations::archetype_location> >&& v);
    /**@}*/

    /**
     * @brief All archetype locations for a given intra-backend segment.
     *
     * Intra-backend segments are backend specific sets of archetype locations, with
     * associated properties.
     */
    /**@{*/
    const std::unordered_map<std::string, std::list<dogen::annotations::archetype_location> >& archetype_locations_by_intra_backend_segment() const;
    std::unordered_map<std::string, std::list<dogen::annotations::archetype_location> >& archetype_locations_by_intra_backend_segment();
    void archetype_locations_by_intra_backend_segment(const std::unordered_map<std::string, std::list<dogen::annotations::archetype_location> >& v);
    void archetype_locations_by_intra_backend_segment(const std::unordered_map<std::string, std::list<dogen::annotations::archetype_location> >&& v);
    /**@}*/

public:
    bool operator==(const archetype_location_repository_parts& rhs) const;
    bool operator!=(const archetype_location_repository_parts& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(archetype_location_repository_parts& other) noexcept;
    archetype_location_repository_parts& operator=(archetype_location_repository_parts other);

private:
    std::list<dogen::annotations::archetype_location> archetype_locations_;
    std::unordered_map<std::string, dogen::annotations::archetype_locations_group> archetype_locations_by_meta_name_;
    std::unordered_map<std::string, std::list<dogen::annotations::archetype_location> > archetype_locations_by_family_;
    std::unordered_map<std::string, std::list<dogen::annotations::archetype_location> > archetype_locations_by_intra_backend_segment_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::annotations::archetype_location_repository_parts& lhs,
    dogen::annotations::archetype_location_repository_parts& rhs) {
    lhs.swap(rhs);
}

}

#endif
