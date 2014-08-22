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
#ifndef DOGEN_TEST_MODELS_STEREOTYPES_TYPES_COMPOSITE_IDENTITY_HPP
#define DOGEN_TEST_MODELS_STEREOTYPES_TYPES_COMPOSITE_IDENTITY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/test_models/stereotypes/serialization/composite_identity_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace stereotypes {

/**
 * @brief Type has multiple identity properties.
 */
class composite_identity final {
public:
    composite_identity(const composite_identity&) = default;
    composite_identity(composite_identity&&) = default;
    ~composite_identity() = default;

public:
    composite_identity();

public:
    composite_identity(
        const int prop_0,
        const int prop_1,
        const int prop_2);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const composite_identity& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, composite_identity& v, unsigned int version);

public:
    /**
     * @brief First identity property.
     *
     */
    /**@{*/
    int prop_0() const;
    void prop_0(const int v);
    /**@}*/

    /**
     * @brief Second identity property.
     *
     */
    /**@{*/
    int prop_1() const;
    void prop_1(const int v);
    /**@}*/

    /**
     * @brief A non-identity property.
     */
    /**@{*/
    int prop_2() const;
    void prop_2(const int v);
    /**@}*/

public:
    bool operator==(const composite_identity& rhs) const;
    bool operator!=(const composite_identity& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(composite_identity& other) noexcept;
    composite_identity& operator=(composite_identity other);

private:
    int prop_0_;
    int prop_1_;
    int prop_2_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::test_models::stereotypes::composite_identity& lhs,
    dogen::test_models::stereotypes::composite_identity& rhs) {
    lhs.swap(rhs);
}

}

#endif
