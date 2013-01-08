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
#ifndef DOGEN_ALL_PRIMITIVES_TYPES_A_CLASS_VERSIONED_KEY_HPP
#define DOGEN_ALL_PRIMITIVES_TYPES_A_CLASS_VERSIONED_KEY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/all_primitives/serialization/a_class_versioned_key_fwd_ser.hpp"

namespace dogen {
namespace all_primitives {

class a_class_versioned_key final {
public:
    a_class_versioned_key(const a_class_versioned_key&) = default;
    a_class_versioned_key(a_class_versioned_key&&) = default;
    ~a_class_versioned_key() = default;

public:
    a_class_versioned_key();

public:
    a_class_versioned_key(
        const unsigned int id,
        const unsigned int version);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const a_class_versioned_key& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, a_class_versioned_key& v, unsigned int version);

public:
    unsigned int id() const;
    void id(const unsigned int v);

    unsigned int version() const;
    void version(const unsigned int v);

public:
    bool operator==(const a_class_versioned_key& rhs) const;
    bool operator!=(const a_class_versioned_key& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(a_class_versioned_key& other) noexcept;
    a_class_versioned_key& operator=(a_class_versioned_key other);

private:
    unsigned int id_;
    unsigned int version_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::all_primitives::a_class_versioned_key& lhs,
    dogen::all_primitives::a_class_versioned_key& rhs) {
    lhs.swap(rhs);
}

}

#endif
