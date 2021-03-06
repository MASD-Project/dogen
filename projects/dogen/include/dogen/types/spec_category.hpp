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
#ifndef DOGEN_TYPES_SPEC_CATEGORY_HPP
#define DOGEN_TYPES_SPEC_CATEGORY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <algorithm>
#include "dogen/types/spec_entry.hpp"

namespace dogen {

/**
 * @brief Describes a category of dogen specifications.
 */
class spec_category final {
public:
    spec_category() = default;
    spec_category(const spec_category&) = default;
    spec_category(spec_category&&) = default;
    ~spec_category() = default;

public:
    spec_category(
        const std::string& name,
        const std::list<dogen::spec_entry>& entries,
        const std::string& description);

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

    /**
     * @brief Purpose of the group.
     */
    /**@{*/
    const std::string& description() const;
    std::string& description();
    void description(const std::string& v);
    void description(const std::string&& v);
    /**@}*/

public:
    bool operator==(const spec_category& rhs) const;
    bool operator!=(const spec_category& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(spec_category& other) noexcept;
    spec_category& operator=(spec_category other);

private:
    std::string name_;
    std::list<dogen::spec_entry> entries_;
    std::string description_;
};

}

namespace std {

template<>
inline void swap(
    dogen::spec_category& lhs,
    dogen::spec_category& rhs) {
    lhs.swap(rhs);
}

}

#endif
