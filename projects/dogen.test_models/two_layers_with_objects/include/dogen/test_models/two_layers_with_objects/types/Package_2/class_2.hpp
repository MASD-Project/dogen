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
#ifndef DOGEN_TEST_MODELS_TWO_LAYERS_WITH_OBJECTS_TYPES_PACKAGE_2_CLASS_2_HPP
#define DOGEN_TEST_MODELS_TWO_LAYERS_WITH_OBJECTS_TYPES_PACKAGE_2_CLASS_2_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/test_models/two_layers_with_objects/serialization/Package_2/class_2_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace two_layers_with_objects {
namespace Package_2 {

class class_2 final {
public:
    class_2(const class_2&) = default;
    class_2(class_2&&) = default;
    ~class_2() = default;

public:
    class_2();

public:
    explicit class_2(const int prop_0);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::test_models::two_layers_with_objects::Package_2::class_2& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::test_models::two_layers_with_objects::Package_2::class_2& v, unsigned int version);

public:
    int prop_0() const;
    void prop_0(const int v);

public:
    bool operator==(const class_2& rhs) const;
    bool operator!=(const class_2& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(class_2& other) noexcept;
    class_2& operator=(class_2 other);

private:
    int prop_0_;
};

} } } }

namespace std {

template<>
inline void swap(
    dogen::test_models::two_layers_with_objects::Package_2::class_2& lhs,
    dogen::test_models::two_layers_with_objects::Package_2::class_2& rhs) {
    lhs.swap(rhs);
}

}

#endif
