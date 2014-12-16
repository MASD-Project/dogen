/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#ifndef DOGEN_DYNAMIC_TYPES_OBJECT_HPP
#define DOGEN_DYNAMIC_TYPES_OBJECT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <string>
#include <unordered_map>
#include "dogen/dynamic/serialization/object_fwd_ser.hpp"
#include "dogen/dynamic/types/field.hpp"

namespace dogen {
namespace dynamic {

/**
 * @brief Represents an object with dynamic structure.
 */
class object final {
public:
    object() = default;
    object(const object&) = default;
    object(object&&) = default;
    ~object() = default;

public:
    explicit object(const std::unordered_map<std::string, dogen::dynamic::field>& fields);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const object& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, object& v, unsigned int version);

public:
    /**
     * @brief All the fields associated with this object, by complete field name.
     */
    /**@{*/
    const std::unordered_map<std::string, dogen::dynamic::field>& fields() const;
    std::unordered_map<std::string, dogen::dynamic::field>& fields();
    void fields(const std::unordered_map<std::string, dogen::dynamic::field>& v);
    void fields(const std::unordered_map<std::string, dogen::dynamic::field>&& v);
    /**@}*/

public:
    bool operator==(const object& rhs) const;
    bool operator!=(const object& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(object& other) noexcept;
    object& operator=(object other);

private:
    std::unordered_map<std::string, dogen::dynamic::field> fields_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::dynamic::object& lhs,
    dogen::dynamic::object& rhs) {
    lhs.swap(rhs);
}

}

#endif
