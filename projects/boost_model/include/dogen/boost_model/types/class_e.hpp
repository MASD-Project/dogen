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
#ifndef DOGEN_BOOST_MODEL_TYPES_CLASS_E_HPP
#define DOGEN_BOOST_MODEL_TYPES_CLASS_E_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/variant.hpp>
#include <vector>
#include "dogen/boost_model/serialization/class_e_fwd_ser.hpp"
#include "dogen/boost_model/types/class_derived.hpp"

namespace dogen {
namespace boost_model {

class class_e final {
public:
    class_e() = default;
    class_e(const class_e&) = default;
    ~class_e() = default;

public:
    class_e(class_e&& rhs);

public:
    class_e(
        const boost::variant<int, double>& prop_0,
        const boost::variant<int, dogen::boost_model::class_derived, double>& prop_1,
        const std::vector<boost::variant<int, dogen::boost_model::class_derived, double> >& prop_2);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const class_e& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, class_e& v, unsigned int version);

public:
    const boost::variant<int, double>& prop_0() const {
        return prop_0_;
    }

    boost::variant<int, double>& prop_0() {
        return prop_0_;
    }

    void prop_0(const boost::variant<int, double>& v) {
        prop_0_ = v;
    }

    void prop_0(const boost::variant<int, double>&& v) {
        prop_0_ = std::move(v);
    }

    const boost::variant<int, dogen::boost_model::class_derived, double>& prop_1() const {
        return prop_1_;
    }

    boost::variant<int, dogen::boost_model::class_derived, double>& prop_1() {
        return prop_1_;
    }

    void prop_1(const boost::variant<int, dogen::boost_model::class_derived, double>& v) {
        prop_1_ = v;
    }

    void prop_1(const boost::variant<int, dogen::boost_model::class_derived, double>&& v) {
        prop_1_ = std::move(v);
    }

    const std::vector<boost::variant<int, dogen::boost_model::class_derived, double> >& prop_2() const {
        return prop_2_;
    }

    std::vector<boost::variant<int, dogen::boost_model::class_derived, double> >& prop_2() {
        return prop_2_;
    }

    void prop_2(const std::vector<boost::variant<int, dogen::boost_model::class_derived, double> >& v) {
        prop_2_ = v;
    }

    void prop_2(const std::vector<boost::variant<int, dogen::boost_model::class_derived, double> >&& v) {
        prop_2_ = std::move(v);
    }

public:
    bool operator==(const class_e& rhs) const;
    bool operator!=(const class_e& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(class_e& other) noexcept;
    class_e& operator=(class_e other);

private:
    boost::variant<int, double> prop_0_;
    boost::variant<int, dogen::boost_model::class_derived, double> prop_1_;
    std::vector<boost::variant<int, dogen::boost_model::class_derived, double> > prop_2_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::boost_model::class_e& lhs,
    dogen::boost_model::class_e& rhs) {
    lhs.swap(rhs);
}

}

#endif
