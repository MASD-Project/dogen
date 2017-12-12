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
#ifndef DOGEN_ANNOTATIONS_TYPES_NAME_HPP
#define DOGEN_ANNOTATIONS_TYPES_NAME_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen.annotations/serialization/name_fwd_ser.hpp"

namespace dogen {
namespace annotations {

/**
 * @brief Name of the field description or field.
 */
class name final {
public:
    name() = default;
    name(const name&) = default;
    name(name&&) = default;
    ~name() = default;

public:
    name(
        const std::string& simple,
        const std::string& qualified);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::annotations::name& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::annotations::name& v, unsigned int version);

public:
    /**
     * @brief Non-qualified name of the field.
     */
    /**@{*/
    const std::string& simple() const;
    std::string& simple();
    void simple(const std::string& v);
    void simple(const std::string&& v);
    /**@}*/

    /**
     * @brief Qualified name of the field, using dots to separate the hierarchy.
     */
    /**@{*/
    const std::string& qualified() const;
    std::string& qualified();
    void qualified(const std::string& v);
    void qualified(const std::string&& v);
    /**@}*/

public:
    bool operator==(const name& rhs) const;
    bool operator!=(const name& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(name& other) noexcept;
    name& operator=(name other);

private:
    std::string simple_;
    std::string qualified_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::annotations::name& lhs,
    dogen::annotations::name& rhs) {
    lhs.swap(rhs);
}

}

#endif
