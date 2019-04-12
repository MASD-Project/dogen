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
#ifndef MASD_DOGEN_ANNOTATIONS_TYPES_UNBOUND_CONFIGURATIONS_REPOSITORY_HPP
#define MASD_DOGEN_ANNOTATIONS_TYPES_UNBOUND_CONFIGURATIONS_REPOSITORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <unordered_map>
#include "masd.dogen.annotations/types/annotation.hpp"

namespace masd::dogen::annotations {

class unbound_configurations_repository final {
public:
    unbound_configurations_repository() = default;
    unbound_configurations_repository(const unbound_configurations_repository&) = default;
    unbound_configurations_repository(unbound_configurations_repository&&) = default;
    ~unbound_configurations_repository() = default;

public:
    explicit unbound_configurations_repository(const std::unordered_map<std::string, masd::dogen::annotations::annotation>& by_name);

public:
    const std::unordered_map<std::string, masd::dogen::annotations::annotation>& by_name() const;
    std::unordered_map<std::string, masd::dogen::annotations::annotation>& by_name();
    void by_name(const std::unordered_map<std::string, masd::dogen::annotations::annotation>& v);
    void by_name(const std::unordered_map<std::string, masd::dogen::annotations::annotation>&& v);

public:
    bool operator==(const unbound_configurations_repository& rhs) const;
    bool operator!=(const unbound_configurations_repository& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(unbound_configurations_repository& other) noexcept;
    unbound_configurations_repository& operator=(unbound_configurations_repository other);

private:
    std::unordered_map<std::string, masd::dogen::annotations::annotation> by_name_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::annotations::unbound_configurations_repository& lhs,
    masd::dogen::annotations::unbound_configurations_repository& rhs) {
    lhs.swap(rhs);
}

}

#endif
