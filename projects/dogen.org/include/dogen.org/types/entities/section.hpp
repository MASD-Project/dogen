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
#ifndef DOGEN_ORG_TYPES_ENTITIES_SECTION_HPP
#define DOGEN_ORG_TYPES_ENTITIES_SECTION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <algorithm>
#include "dogen.org/types/entities/block.hpp"

namespace dogen::org::entities {

class section final {
public:
    section() = default;
    section(const section&) = default;
    section(section&&) = default;
    ~section() = default;

public:
    explicit section(const std::list<dogen::org::entities::block>& blocks);

public:
    const std::list<dogen::org::entities::block>& blocks() const;
    std::list<dogen::org::entities::block>& blocks();
    void blocks(const std::list<dogen::org::entities::block>& v);
    void blocks(const std::list<dogen::org::entities::block>&& v);

public:
    bool operator==(const section& rhs) const;
    bool operator!=(const section& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(section& other) noexcept;
    section& operator=(section other);

private:
    std::list<dogen::org::entities::block> blocks_;
};

}

namespace std {

template<>
inline void swap(
    dogen::org::entities::section& lhs,
    dogen::org::entities::section& rhs) {
    lhs.swap(rhs);
}

}

#endif
