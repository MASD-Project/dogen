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
#ifndef DOGEN_CLASS_WITHOUT_PACKAGE_DOMAIN_CLASS_1_HPP
#define DOGEN_CLASS_WITHOUT_PACKAGE_DOMAIN_CLASS_1_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/class_without_package/domain/versioned_key.hpp"
#include "dogen/class_without_package/serialization/class_1_fwd_ser.hpp"

namespace dogen {
namespace class_without_package {

class class_1 final {
public:
    class_1(const class_1&) = default;
    class_1(class_1&&) = default;
    ~class_1() = default;

public:
    class_1();

public:
    class_1(
        const int an_attribute,
        const dogen::class_without_package::versioned_key& versioned_key);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const class_1& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, class_1& v, unsigned int version);

public:
    int an_attribute() const {
        return an_attribute_;
    }

    void an_attribute(const int v) {
        an_attribute_ = v;
    }

    dogen::class_without_package::versioned_key versioned_key() const {
        return versioned_key_;
    }

    void versioned_key(const dogen::class_without_package::versioned_key& v) {
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
    int an_attribute_;
    dogen::class_without_package::versioned_key versioned_key_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::class_without_package::class_1& lhs,
    dogen::class_without_package::class_1& rhs) {
    lhs.swap(rhs);
}

}

#endif
