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
#ifndef DOGEN_CLASSES_WITHOUT_PACKAGE_TYPES_CLASS_3_HPP
#define DOGEN_CLASSES_WITHOUT_PACKAGE_TYPES_CLASS_3_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/classes_without_package/serialization/class_3_fwd_ser.hpp"

namespace dogen {
namespace classes_without_package {

class class_3 final {
public:
    class_3(const class_3&) = default;
    class_3(class_3&&) = default;
    ~class_3() = default;

public:
    class_3();

public:
    explicit class_3(const int prop_0);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const class_3& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, class_3& v, unsigned int version);

public:
    int prop_0() const {
        return prop_0_;
    }

    void prop_0(const int v) {
        prop_0_ = v;
    }

public:
    bool operator==(const class_3& rhs) const;
    bool operator!=(const class_3& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(class_3& other) noexcept;
    class_3& operator=(class_3 other);

private:
    int prop_0_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::classes_without_package::class_3& lhs,
    dogen::classes_without_package::class_3& rhs) {
    lhs.swap(rhs);
}

}

#endif
