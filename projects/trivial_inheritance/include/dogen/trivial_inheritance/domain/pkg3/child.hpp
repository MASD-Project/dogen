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
#ifndef DOGEN_TRIVIAL_INHERITANCE_DOMAIN_PKG3_CHILD_HPP
#define DOGEN_TRIVIAL_INHERITANCE_DOMAIN_PKG3_CHILD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <iosfwd>
#include "dogen/trivial_inheritance/domain/pkg2/parent.hpp"
#include "dogen/trivial_inheritance/serialization/pkg3/child_fwd_ser.hpp"

namespace dogen {
namespace trivial_inheritance {
namespace pkg3 {

class child final : public dogen::trivial_inheritance::pkg2::parent {
public:
    child(const child&) = default;
    child(child&&) = default;

public:
    child();

public:
    child(
        const int prop_0,
        const dogen::trivial_inheritance::versioned_key& versioned_key,
        const int prop_1);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const child& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, child& v, unsigned int version);

public:
    void to_stream(std::ostream& s) const override;

public:
    int prop_1() const {
        return prop_1_;
    }

    void prop_1(const int v) {
        prop_1_ = v;
    }

public:
    bool operator==(const child& rhs) const;
    bool operator!=(const child& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(child& other) noexcept;
    child& operator=(child other);

private:
    int prop_1_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::trivial_inheritance::pkg3::child& lhs,
    dogen::trivial_inheritance::pkg3::child& rhs) {
    lhs.swap(rhs);
}

}

#endif
