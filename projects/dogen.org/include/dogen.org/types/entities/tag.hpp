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
#ifndef DOGEN_ORG_TYPES_ENTITIES_TAG_HPP
#define DOGEN_ORG_TYPES_ENTITIES_TAG_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>

namespace dogen::org::entities {
class tag final {
public:
    tag() = default;
    tag(const tag&) = default;
    tag(tag&&) = default;
    ~tag() = default;
public:
    explicit tag(const std::string& value);

public:
    /**
     * @brief Obtain the underlying value.
     */
    /**@{*/
    const std::string& value() const;
    std::string& value();
    void value(const std::string& v);
    void value(const std::string&& v);
    /**@}*/

public:
    explicit operator std::string() const {
        return value_;
    }

public:
    bool operator==(const tag& rhs) const;
    bool operator!=(const tag& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(tag& other) noexcept;
    tag& operator=(tag other);

private:
    std::string value_;
};

}

namespace std {

template<>
inline void swap(
    dogen::org::entities::tag& lhs,
    dogen::org::entities::tag& rhs) {
    lhs.swap(rhs);
}

}

#endif
