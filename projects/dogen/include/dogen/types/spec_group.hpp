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
#ifndef DOGEN_TYPES_SPEC_GROUP_HPP
#define DOGEN_TYPES_SPEC_GROUP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include "dogen/types/spec_entry.hpp"

namespace dogen {

class spec_group final {
public:
    spec_group() = default;
    spec_group(const spec_group&) = default;
    spec_group(spec_group&&) = default;
    ~spec_group() = default;

public:
    spec_group(
        const std::string& name,
        const std::list<dogen::spec_entry>& entries);

public:
    /**
     * @brief Name of this group of specs.
     */
    /**@{*/
    const std::string& name() const;
    std::string& name();
    void name(const std::string& v);
    void name(const std::string&& v);
    /**@}*/

    /**
     * @brief Entries describing various aspects of this group.
     */
    /**@{*/
    const std::list<dogen::spec_entry>& entries() const;
    std::list<dogen::spec_entry>& entries();
    void entries(const std::list<dogen::spec_entry>& v);
    void entries(const std::list<dogen::spec_entry>&& v);
    /**@}*/

public:
    bool operator==(const spec_group& rhs) const;
    bool operator!=(const spec_group& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(spec_group& other) noexcept;
    spec_group& operator=(spec_group other);

private:
    std::string name_;
    std::list<dogen::spec_entry> entries_;
};

}

namespace std {

template<>
inline void swap(
    dogen::spec_group& lhs,
    dogen::spec_group& rhs) {
    lhs.swap(rhs);
}

}

#endif
