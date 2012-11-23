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
#ifndef DOGEN_BOOST_MODEL_TYPES_CLASS_D_HPP
#define DOGEN_BOOST_MODEL_TYPES_CLASS_D_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/optional.hpp>
#include "dogen/boost_model/serialization/class_d_fwd_ser.hpp"

namespace dogen {
namespace boost_model {

class class_d final {
public:
    class_d() = default;
    class_d(const class_d&) = default;
    ~class_d() = default;

public:
    class_d(class_d&& rhs);

public:
    explicit class_d(const boost::optional<int>& prop_0);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const class_d& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, class_d& v, unsigned int version);

public:
    boost::optional<int> prop_0() const {
        return prop_0_;
    }

    void prop_0(const boost::optional<int>& v) {
        prop_0_ = v;
    }

public:
    bool operator==(const class_d& rhs) const;
    bool operator!=(const class_d& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(class_d& other) noexcept;
    class_d& operator=(class_d other);

private:
    boost::optional<int> prop_0_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::boost_model::class_d& lhs,
    dogen::boost_model::class_d& rhs) {
    lhs.swap(rhs);
}

}

#endif
