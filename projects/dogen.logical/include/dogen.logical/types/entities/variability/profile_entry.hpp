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
#ifndef DOGEN_LOGICAL_TYPES_ENTITIES_VARIABILITY_PROFILE_ENTRY_HPP
#define DOGEN_LOGICAL_TYPES_ENTITIES_VARIABILITY_PROFILE_ENTRY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <algorithm>
#include "dogen.logical/types/entities/variability/abstract_profile_entry.hpp"

namespace dogen::logical::entities::variability {

class profile_entry final : public dogen::logical::entities::variability::abstract_profile_entry {
public:
    profile_entry() = default;
    profile_entry(const profile_entry&) = default;
    profile_entry(profile_entry&&) = default;

    virtual ~profile_entry() noexcept { }

public:
    profile_entry(
        const std::string& documentation,
        const boost::shared_ptr<dogen::variability::entities::configuration>& configuration,
        const dogen::identification::entities::logical_name& name,
        const std::string& original_key,
        const std::string& key,
        const std::list<std::string>& value);

public:
    void to_stream(std::ostream& s) const override;

public:
    bool operator==(const profile_entry& rhs) const;
    bool operator!=(const profile_entry& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::logical::entities::variability::abstract_profile_entry& other) const override;

public:
    void swap(profile_entry& other) noexcept;
    profile_entry& operator=(profile_entry other);

};

}

namespace std {

template<>
inline void swap(
    dogen::logical::entities::variability::profile_entry& lhs,
    dogen::logical::entities::variability::profile_entry& rhs) {
    lhs.swap(rhs);
}

}

#endif
