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
#ifndef DOGEN_VARIABILITY_TYPES_ENTITIES_PROFILE_TEMPLATE_REPOSITORY_HPP
#define DOGEN_VARIABILITY_TYPES_ENTITIES_PROFILE_TEMPLATE_REPOSITORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <algorithm>
#include "dogen.variability/types/entities/profile_template.hpp"

namespace dogen::variability::entities {

class profile_template_repository final {
public:
    profile_template_repository() = default;
    profile_template_repository(const profile_template_repository&) = default;
    profile_template_repository(profile_template_repository&&) = default;
    ~profile_template_repository() = default;

public:
    explicit profile_template_repository(const std::list<dogen::variability::entities::profile_template>& templates);

public:
    const std::list<dogen::variability::entities::profile_template>& templates() const;
    std::list<dogen::variability::entities::profile_template>& templates();
    void templates(const std::list<dogen::variability::entities::profile_template>& v);
    void templates(const std::list<dogen::variability::entities::profile_template>&& v);

public:
    bool operator==(const profile_template_repository& rhs) const;
    bool operator!=(const profile_template_repository& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(profile_template_repository& other) noexcept;
    profile_template_repository& operator=(profile_template_repository other);

private:
    std::list<dogen::variability::entities::profile_template> templates_;
};

}

namespace std {

template<>
inline void swap(
    dogen::variability::entities::profile_template_repository& lhs,
    dogen::variability::entities::profile_template_repository& rhs) {
    lhs.swap(rhs);
}

}

#endif
