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
#ifndef DOGEN_BOOST_MODEL_DOMAIN_CLASS_DERIVED_HPP
#define DOGEN_BOOST_MODEL_DOMAIN_CLASS_DERIVED_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <iosfwd>
#include "dogen/boost_model/domain/class_base.hpp"
#include "dogen/boost_model/serialization/class_derived_fwd_ser.hpp"

namespace dogen {
namespace boost_model {

class class_derived final : public dogen::boost_model::class_base {
public:
    class_derived(const class_derived&) = default;
    class_derived(class_derived&&) = default;

public:
    class_derived();

public:
    class_derived(
        const int prop_0,
        const dogen::boost_model::versioned_key& versioned_key,
        const int prop_1);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const class_derived& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, class_derived& v, unsigned int version);

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
    bool operator==(const class_derived& rhs) const;
    bool operator!=(const class_derived& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(class_derived& other) noexcept;
    class_derived& operator=(class_derived other);

private:
    int prop_1_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::boost_model::class_derived& lhs,
    dogen::boost_model::class_derived& rhs) {
    lhs.swap(rhs);
}

}

#endif
