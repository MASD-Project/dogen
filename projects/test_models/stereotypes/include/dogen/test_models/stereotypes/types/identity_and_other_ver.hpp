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
#ifndef DOGEN_TEST_MODELS_STEREOTYPES_TYPES_IDENTITY_AND_OTHER_VER_HPP
#define DOGEN_TEST_MODELS_STEREOTYPES_TYPES_IDENTITY_AND_OTHER_VER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/test_models/stereotypes/serialization/identity_and_other_ver_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace stereotypes {

/**
 * @brief Type has an identity property and another, non-identity property. Versioned scenario.
 */
class identity_and_other_ver final {
public:
    identity_and_other_ver(const identity_and_other_ver&) = default;
    identity_and_other_ver(identity_and_other_ver&&) = default;
    ~identity_and_other_ver() = default;

public:
    identity_and_other_ver();

public:
    identity_and_other_ver(
        const int prop_0,
        const int prop_1,
        const unsigned int version);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const identity_and_other_ver& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, identity_and_other_ver& v, unsigned int version);

public:
    /**
     * @brief Identity property.
     *
     */
    /**@{*/
    int prop_0() const;
    void prop_0(const int v);
    /**@}*/

    /**
     * @brief Non-identity property.
     */
    /**@{*/
    int prop_1() const;
    void prop_1(const int v);
    /**@}*/

    /**
     * @brief Object instance's version.
     */
    /**@{*/
    unsigned int version() const;
    void version(const unsigned int v);
    /**@}*/

public:
    bool operator==(const identity_and_other_ver& rhs) const;
    bool operator!=(const identity_and_other_ver& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(identity_and_other_ver& other) noexcept;
    identity_and_other_ver& operator=(identity_and_other_ver other);

private:
    int prop_0_;
    int prop_1_;
    unsigned int version_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::test_models::stereotypes::identity_and_other_ver& lhs,
    dogen::test_models::stereotypes::identity_and_other_ver& rhs) {
    lhs.swap(rhs);
}

}

#endif
