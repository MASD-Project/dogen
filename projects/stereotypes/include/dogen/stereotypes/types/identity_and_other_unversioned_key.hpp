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
#ifndef DOGEN_STEREOTYPES_TYPES_IDENTITY_AND_OTHER_UNVERSIONED_KEY_HPP
#define DOGEN_STEREOTYPES_TYPES_IDENTITY_AND_OTHER_UNVERSIONED_KEY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/stereotypes/serialization/identity_and_other_unversioned_key_fwd_ser.hpp"

namespace dogen {
namespace stereotypes {

/**
 * @brief Unversioned key for identity_and_other
 */
class identity_and_other_unversioned_key final {
public:
    identity_and_other_unversioned_key(const identity_and_other_unversioned_key&) = default;
    identity_and_other_unversioned_key(identity_and_other_unversioned_key&&) = default;
    ~identity_and_other_unversioned_key() = default;

public:
    identity_and_other_unversioned_key();

public:
    explicit identity_and_other_unversioned_key(const int prop_0);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const identity_and_other_unversioned_key& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, identity_and_other_unversioned_key& v, unsigned int version);

public:
    /**
     * @brief Identity property.
     *
     */
    /**@{*/
    int prop_0() const;
    void prop_0(const int v);
    /**@}*/

public:
    bool operator==(const identity_and_other_unversioned_key& rhs) const;
    bool operator!=(const identity_and_other_unversioned_key& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(identity_and_other_unversioned_key& other) noexcept;
    identity_and_other_unversioned_key& operator=(identity_and_other_unversioned_key other);

private:
    int prop_0_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::stereotypes::identity_and_other_unversioned_key& lhs,
    dogen::stereotypes::identity_and_other_unversioned_key& rhs) {
    lhs.swap(rhs);
}

}

#endif
