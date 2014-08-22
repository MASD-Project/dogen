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
#ifndef DOGEN_TEST_MODELS_STEREOTYPES_TYPES_COMPOSITE_IDENTITY_VER_UNVERSIONED_KEY_HPP
#define DOGEN_TEST_MODELS_STEREOTYPES_TYPES_COMPOSITE_IDENTITY_VER_UNVERSIONED_KEY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/test_models/stereotypes/serialization/composite_identity_ver_unversioned_key_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace stereotypes {

/**
 * @brief Unversioned key for composite_identity_ver
 */
class composite_identity_ver_unversioned_key final {
public:
    composite_identity_ver_unversioned_key(const composite_identity_ver_unversioned_key&) = default;
    composite_identity_ver_unversioned_key(composite_identity_ver_unversioned_key&&) = default;
    ~composite_identity_ver_unversioned_key() = default;

public:
    composite_identity_ver_unversioned_key();

public:
    composite_identity_ver_unversioned_key(
        const int prop_0,
        const int prop_1);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const composite_identity_ver_unversioned_key& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, composite_identity_ver_unversioned_key& v, unsigned int version);

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

public:
    bool operator==(const composite_identity_ver_unversioned_key& rhs) const;
    bool operator!=(const composite_identity_ver_unversioned_key& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(composite_identity_ver_unversioned_key& other) noexcept;
    composite_identity_ver_unversioned_key& operator=(composite_identity_ver_unversioned_key other);

private:
    int prop_0_;
    int prop_1_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::test_models::stereotypes::composite_identity_ver_unversioned_key& lhs,
    dogen::test_models::stereotypes::composite_identity_ver_unversioned_key& rhs) {
    lhs.swap(rhs);
}

}

#endif
