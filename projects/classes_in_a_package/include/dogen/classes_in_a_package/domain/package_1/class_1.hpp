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
#ifndef DOGEN_CLASSES_IN_A_PACKAGE_DOMAIN_PACKAGE_1_CLASS_1_HPP
#define DOGEN_CLASSES_IN_A_PACKAGE_DOMAIN_PACKAGE_1_CLASS_1_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/classes_in_a_package/domain/versioned_key.hpp"
#include "dogen/classes_in_a_package/serialization/package_1/class_1_fwd_ser.hpp"

namespace dogen {
namespace classes_in_a_package {
namespace package_1 {

class class_1_serializer;

class class_1 final {
public:
    class_1() = default;
    class_1(const class_1&) = default;
    class_1(class_1&&) = default;
    ~class_1() = default;

public:
    explicit class_1(const dogen::classes_in_a_package::versioned_key& versioned_key);

public:
    friend class dogen::classes_in_a_package::package_1::class_1_serializer;

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const class_1& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, class_1& v, unsigned int version);

public:
    dogen::classes_in_a_package::versioned_key versioned_key() const {
        return versioned_key_;
    }

    void versioned_key(const dogen::classes_in_a_package::versioned_key& v) {
        versioned_key_ = v;
    }

public:
    bool operator==(const class_1& rhs) const;
    bool operator!=(const class_1& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(class_1& other) noexcept;
    class_1& operator=(class_1 other);

private:
    dogen::classes_in_a_package::versioned_key versioned_key_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::classes_in_a_package::package_1::class_1& lhs,
    dogen::classes_in_a_package::package_1::class_1& rhs) {
    lhs.swap(rhs);
}

}

#endif
