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
#ifndef DOGEN_LOGICAL_TYPES_ENTITIES_VARIABILITY_DEFAULT_VALUE_OVERRIDE_HPP
#define DOGEN_LOGICAL_TYPES_ENTITIES_VARIABILITY_DEFAULT_VALUE_OVERRIDE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>

namespace dogen::logical::entities::variability {

class default_value_override final {
public:
    default_value_override() = default;
    default_value_override(const default_value_override&) = default;
    default_value_override(default_value_override&&) = default;
    ~default_value_override() = default;

public:
    default_value_override(
        const std::string& key_ends_with,
        const std::string& default_value);

public:
    const std::string& key_ends_with() const;
    std::string& key_ends_with();
    void key_ends_with(const std::string& v);
    void key_ends_with(const std::string&& v);

    const std::string& default_value() const;
    std::string& default_value();
    void default_value(const std::string& v);
    void default_value(const std::string&& v);

public:
    bool operator==(const default_value_override& rhs) const;
    bool operator!=(const default_value_override& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(default_value_override& other) noexcept;
    default_value_override& operator=(default_value_override other);

private:
    std::string key_ends_with_;
    std::string default_value_;
};

}

namespace std {

template<>
inline void swap(
    dogen::logical::entities::variability::default_value_override& lhs,
    dogen::logical::entities::variability::default_value_override& rhs) {
    lhs.swap(rhs);
}

}

#endif
