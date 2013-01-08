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
#ifndef DOGEN_STD_MODEL_TYPES_CLASS_A_UNVERSIONED_KEY_HPP
#define DOGEN_STD_MODEL_TYPES_CLASS_A_UNVERSIONED_KEY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/std_model/serialization/class_a_unversioned_key_fwd_ser.hpp"

namespace dogen {
namespace std_model {

class class_a_unversioned_key final {
public:
    class_a_unversioned_key(const class_a_unversioned_key&) = default;
    class_a_unversioned_key(class_a_unversioned_key&&) = default;
    ~class_a_unversioned_key() = default;

public:
    class_a_unversioned_key();

public:
    explicit class_a_unversioned_key(const unsigned int id);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const class_a_unversioned_key& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, class_a_unversioned_key& v, unsigned int version);

public:
    unsigned int id() const;
    void id(const unsigned int v);

public:
    bool operator==(const class_a_unversioned_key& rhs) const;
    bool operator!=(const class_a_unversioned_key& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(class_a_unversioned_key& other) noexcept;
    class_a_unversioned_key& operator=(class_a_unversioned_key other);

private:
    unsigned int id_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::std_model::class_a_unversioned_key& lhs,
    dogen::std_model::class_a_unversioned_key& rhs) {
    lhs.swap(rhs);
}

}

#endif
