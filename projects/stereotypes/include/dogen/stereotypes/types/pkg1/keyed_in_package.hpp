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
#ifndef DOGEN_STEREOTYPES_TYPES_PKG1_KEYED_IN_PACKAGE_HPP
#define DOGEN_STEREOTYPES_TYPES_PKG1_KEYED_IN_PACKAGE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/stereotypes/serialization/pkg1/keyed_in_package_fwd_ser.hpp"

namespace dogen {
namespace stereotypes {
namespace pkg1 {

/**
 * @brief Tests generation of keys inside a package.
 */
class keyed_in_package final {
public:
    keyed_in_package(const keyed_in_package&) = default;
    keyed_in_package(keyed_in_package&&) = default;
    ~keyed_in_package() = default;

public:
    keyed_in_package();

public:
    explicit keyed_in_package(const int prop_0);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const keyed_in_package& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, keyed_in_package& v, unsigned int version);

public:
    /**
     * @brief Identity property
     *
     */
    /**@{*/
    int prop_0() const;
    void prop_0(const int v);
    /**@}*/

public:
    bool operator==(const keyed_in_package& rhs) const;
    bool operator!=(const keyed_in_package& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(keyed_in_package& other) noexcept;
    keyed_in_package& operator=(keyed_in_package other);

private:
    int prop_0_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::stereotypes::pkg1::keyed_in_package& lhs,
    dogen::stereotypes::pkg1::keyed_in_package& rhs) {
    lhs.swap(rhs);
}

}

#endif
