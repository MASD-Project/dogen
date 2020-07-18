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
#ifndef DOGEN_IDENTIFICATION_TYPES_ENTITIES_LABEL_HPP
#define DOGEN_IDENTIFICATION_TYPES_ENTITIES_LABEL_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>

namespace dogen::identification::entities {

/**
 * @brief A label is a key-value pair that can be used by the processing engine in a flexible way.
 */
class label final {
public:
    label() = default;
    label(const label&) = default;
    label(label&&) = default;
    ~label() = default;

public:
    label(
        const std::string& key,
        const std::string& value);

public:
    /**
     * @brief Key of the label.
     */
    /**@{*/
    const std::string& key() const;
    std::string& key();
    void key(const std::string& v);
    void key(const std::string&& v);
    /**@}*/

    /**
     * @brief Value associated with this label.
     */
    /**@{*/
    const std::string& value() const;
    std::string& value();
    void value(const std::string& v);
    void value(const std::string&& v);
    /**@}*/

public:
    bool operator==(const label& rhs) const;
    bool operator!=(const label& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(label& other) noexcept;
    label& operator=(label other);

private:
    std::string key_;
    std::string value_;
};

}

namespace std {

template<>
inline void swap(
    dogen::identification::entities::label& lhs,
    dogen::identification::entities::label& rhs) {
    lhs.swap(rhs);
}

}

#endif
