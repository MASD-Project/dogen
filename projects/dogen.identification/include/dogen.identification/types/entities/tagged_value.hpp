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
#ifndef DOGEN_IDENTIFICATION_TYPES_ENTITIES_TAGGED_VALUE_HPP
#define DOGEN_IDENTIFICATION_TYPES_ENTITIES_TAGGED_VALUE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>

namespace dogen::identification::entities {

/**
 * @brief Represents a tagged value in a similar spirit to UMLs.
 */
class tagged_value final {
public:
    tagged_value() = default;
    tagged_value(const tagged_value&) = default;
    tagged_value(tagged_value&&) = default;
    ~tagged_value() = default;

public:
    tagged_value(
        const std::string& tag,
        const std::string& value);

public:
    /**
     * @brief Tag name.
     */
    /**@{*/
    const std::string& tag() const;
    std::string& tag();
    void tag(const std::string& v);
    void tag(const std::string&& v);
    /**@}*/

    /**
     * @brief Value associated with this tag.
     */
    /**@{*/
    const std::string& value() const;
    std::string& value();
    void value(const std::string& v);
    void value(const std::string&& v);
    /**@}*/

public:
    bool operator==(const tagged_value& rhs) const;
    bool operator!=(const tagged_value& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(tagged_value& other) noexcept;
    tagged_value& operator=(tagged_value other);

private:
    std::string tag_;
    std::string value_;
};

}

namespace std {

template<>
inline void swap(
    dogen::identification::entities::tagged_value& lhs,
    dogen::identification::entities::tagged_value& rhs) {
    lhs.swap(rhs);
}

}

#endif
