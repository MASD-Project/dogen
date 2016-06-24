/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
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
#ifndef DOGEN_TEST_MODELS_BOOST_MODEL_TYPES_CLASS_E_HPP
#define DOGEN_TEST_MODELS_BOOST_MODEL_TYPES_CLASS_E_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <vector>
#include <algorithm>
#include <boost/variant.hpp>
#include "dogen/test_models/boost_model/types/class_derived.hpp"
#include "dogen/test_models/boost_model/serialization/class_e_fwd_ser.hpp"

namespace dogen {
namespace test_models {
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
        const boost::variant<int, dogen::test_models::boost_model::class_derived, double>& prop_1,
        const std::vector<boost::variant<int, dogen::test_models::boost_model::class_derived, double> >& prop_2,
        const boost::variant<int, std::string, char>& prop_3);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::test_models::boost_model::class_e& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::test_models::boost_model::class_e& v, unsigned int version);

public:
    const boost::variant<int, double>& prop_0() const;
    boost::variant<int, double>& prop_0();
    void prop_0(const boost::variant<int, double>& v);
    void prop_0(const boost::variant<int, double>&& v);

    const boost::variant<int, dogen::test_models::boost_model::class_derived, double>& prop_1() const;
    boost::variant<int, dogen::test_models::boost_model::class_derived, double>& prop_1();
    void prop_1(const boost::variant<int, dogen::test_models::boost_model::class_derived, double>& v);
    void prop_1(const boost::variant<int, dogen::test_models::boost_model::class_derived, double>&& v);

    const std::vector<boost::variant<int, dogen::test_models::boost_model::class_derived, double> >& prop_2() const;
    std::vector<boost::variant<int, dogen::test_models::boost_model::class_derived, double> >& prop_2();
    void prop_2(const std::vector<boost::variant<int, dogen::test_models::boost_model::class_derived, double> >& v);
    void prop_2(const std::vector<boost::variant<int, dogen::test_models::boost_model::class_derived, double> >&& v);

    const boost::variant<int, std::string, char>& prop_3() const;
    boost::variant<int, std::string, char>& prop_3();
    void prop_3(const boost::variant<int, std::string, char>& v);
    void prop_3(const boost::variant<int, std::string, char>&& v);

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
    boost::variant<int, dogen::test_models::boost_model::class_derived, double> prop_1_;
    std::vector<boost::variant<int, dogen::test_models::boost_model::class_derived, double> > prop_2_;
    boost::variant<int, std::string, char> prop_3_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::test_models::boost_model::class_e& lhs,
    dogen::test_models::boost_model::class_e& rhs) {
    lhs.swap(rhs);
}

}

#endif
