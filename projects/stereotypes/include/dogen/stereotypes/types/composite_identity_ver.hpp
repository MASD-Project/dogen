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
#ifndef DOGEN_STEREOTYPES_TYPES_COMPOSITE_IDENTITY_VER_HPP
#define DOGEN_STEREOTYPES_TYPES_COMPOSITE_IDENTITY_VER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/stereotypes/serialization/composite_identity_ver_fwd_ser.hpp"

namespace dogen {
namespace stereotypes {

/**
 * @brief Type has multiple identity properties. Versioned scenario.
 */
class composite_identity_ver final {
public:
    composite_identity_ver(const composite_identity_ver&) = default;
    composite_identity_ver(composite_identity_ver&&) = default;
    ~composite_identity_ver() = default;

public:
    composite_identity_ver();

public:
    composite_identity_ver(
        const int prop_0,
        const int prop_1,
        const int prop_2,
        const unsigned int version);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const composite_identity_ver& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, composite_identity_ver& v, unsigned int version);

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

    unsigned int version() const;
    void version(const unsigned int v);

public:
    bool operator==(const composite_identity_ver& rhs) const;
    bool operator!=(const composite_identity_ver& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(composite_identity_ver& other) noexcept;
    composite_identity_ver& operator=(composite_identity_ver other);

private:
    int prop_0_;
    int prop_1_;
    int prop_2_;
    unsigned int version_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::stereotypes::composite_identity_ver& lhs,
    dogen::stereotypes::composite_identity_ver& rhs) {
    lhs.swap(rhs);
}

}

#endif
