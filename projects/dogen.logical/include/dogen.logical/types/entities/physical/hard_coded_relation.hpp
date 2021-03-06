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
#ifndef DOGEN_LOGICAL_TYPES_ENTITIES_PHYSICAL_HARD_CODED_RELATION_HPP
#define DOGEN_LOGICAL_TYPES_ENTITIES_PHYSICAL_HARD_CODED_RELATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>

namespace dogen::logical::entities::physical {

class hard_coded_relation final {
public:
    hard_coded_relation() = default;
    hard_coded_relation(const hard_coded_relation&) = default;
    hard_coded_relation(hard_coded_relation&&) = default;
    ~hard_coded_relation() = default;

public:
    explicit hard_coded_relation(const std::string& value);

public:
    const std::string& value() const;
    std::string& value();
    void value(const std::string& v);
    void value(const std::string&& v);

public:
    bool operator==(const hard_coded_relation& rhs) const;
    bool operator!=(const hard_coded_relation& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(hard_coded_relation& other) noexcept;
    hard_coded_relation& operator=(hard_coded_relation other);

private:
    std::string value_;
};

}

namespace std {

template<>
inline void swap(
    dogen::logical::entities::physical::hard_coded_relation& lhs,
    dogen::logical::entities::physical::hard_coded_relation& rhs) {
    lhs.swap(rhs);
}

}

#endif
