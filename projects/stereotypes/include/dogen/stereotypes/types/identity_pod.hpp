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
#ifndef DOGEN_STEREOTYPES_TYPES_IDENTITY_POD_HPP
#define DOGEN_STEREOTYPES_TYPES_IDENTITY_POD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/stereotypes/serialization/identity_pod_fwd_ser.hpp"
#include "dogen/stereotypes/types/value.hpp"

namespace dogen {
namespace stereotypes {

/**
 * @brief Test scenario where identity property is a pod defined in model.
 */
class identity_pod final {
public:
    identity_pod(const identity_pod&) = default;
    identity_pod(identity_pod&&) = default;
    ~identity_pod() = default;

public:
    identity_pod();

public:
    identity_pod(
        const dogen::stereotypes::value& prop_0,
        const unsigned int version);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const identity_pod& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, identity_pod& v, unsigned int version);

public:
    /**
     * @brief Identity property.
     *
     */
    /**@{*/
    const dogen::stereotypes::value& prop_0() const;
    dogen::stereotypes::value& prop_0();
    void prop_0(const dogen::stereotypes::value& v);
    void prop_0(const dogen::stereotypes::value&& v);
    /**@}*/

    /**
     * @brief Object instance's version.
     */
    /**@{*/
    unsigned int version() const;
    void version(const unsigned int v);
    /**@}*/

public:
    bool operator==(const identity_pod& rhs) const;
    bool operator!=(const identity_pod& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(identity_pod& other) noexcept;
    identity_pod& operator=(identity_pod other);

private:
    dogen::stereotypes::value prop_0_;
    unsigned int version_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::stereotypes::identity_pod& lhs,
    dogen::stereotypes::identity_pod& rhs) {
    lhs.swap(rhs);
}

}

#endif
