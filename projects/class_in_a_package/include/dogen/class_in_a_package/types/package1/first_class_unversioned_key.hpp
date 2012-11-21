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
#ifndef DOGEN_CLASS_IN_A_PACKAGE_TYPES_PACKAGE1_FIRST_CLASS_UNVERSIONED_KEY_HPP
#define DOGEN_CLASS_IN_A_PACKAGE_TYPES_PACKAGE1_FIRST_CLASS_UNVERSIONED_KEY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/class_in_a_package/serialization/package1/first_class_unversioned_key_fwd_ser.hpp"

namespace dogen {
namespace class_in_a_package {
namespace package1 {

class first_class_unversioned_key final {
public:
    first_class_unversioned_key(const first_class_unversioned_key&) = default;
    first_class_unversioned_key(first_class_unversioned_key&&) = default;
    ~first_class_unversioned_key() = default;

public:
    first_class_unversioned_key();

public:
    explicit first_class_unversioned_key(const unsigned int id);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const first_class_unversioned_key& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, first_class_unversioned_key& v, unsigned int version);

public:
    unsigned int id() const {
        return id_;
    }

    void id(const unsigned int v) {
        id_ = v;
    }

public:
    bool operator==(const first_class_unversioned_key& rhs) const;
    bool operator!=(const first_class_unversioned_key& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(first_class_unversioned_key& other) noexcept;
    first_class_unversioned_key& operator=(first_class_unversioned_key other);

private:
    unsigned int id_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::class_in_a_package::package1::first_class_unversioned_key& lhs,
    dogen::class_in_a_package::package1::first_class_unversioned_key& rhs) {
    lhs.swap(rhs);
}

}

#endif
