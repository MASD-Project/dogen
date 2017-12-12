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
#ifndef DOGEN_TEST_MODELS_BOOST_MODEL_TYPES_CLASS_F_HPP
#define DOGEN_TEST_MODELS_BOOST_MODEL_TYPES_CLASS_F_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <algorithm>
#include <boost/date_time/gregorian/gregorian_types.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include "dogen/test_models/boost_model/serialization/class_f_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace boost_model {

class class_f final {
public:
    class_f() = default;
    class_f(const class_f&) = default;
    ~class_f() = default;

public:
    class_f(class_f&& rhs);

public:
    class_f(
        const boost::gregorian::date& prop_0,
        const boost::posix_time::ptime& prop_1,
        const boost::posix_time::time_duration& prop_2,
        const std::list<boost::gregorian::date>& prop_3,
        const std::list<boost::posix_time::ptime>& prop_4,
        const std::list<boost::posix_time::time_duration>& prop_5);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::test_models::boost_model::class_f& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::test_models::boost_model::class_f& v, unsigned int version);

public:
    const boost::gregorian::date& prop_0() const;
    boost::gregorian::date& prop_0();
    void prop_0(const boost::gregorian::date& v);
    void prop_0(const boost::gregorian::date&& v);

    const boost::posix_time::ptime& prop_1() const;
    boost::posix_time::ptime& prop_1();
    void prop_1(const boost::posix_time::ptime& v);
    void prop_1(const boost::posix_time::ptime&& v);

    const boost::posix_time::time_duration& prop_2() const;
    boost::posix_time::time_duration& prop_2();
    void prop_2(const boost::posix_time::time_duration& v);
    void prop_2(const boost::posix_time::time_duration&& v);

    const std::list<boost::gregorian::date>& prop_3() const;
    std::list<boost::gregorian::date>& prop_3();
    void prop_3(const std::list<boost::gregorian::date>& v);
    void prop_3(const std::list<boost::gregorian::date>&& v);

    const std::list<boost::posix_time::ptime>& prop_4() const;
    std::list<boost::posix_time::ptime>& prop_4();
    void prop_4(const std::list<boost::posix_time::ptime>& v);
    void prop_4(const std::list<boost::posix_time::ptime>&& v);

    const std::list<boost::posix_time::time_duration>& prop_5() const;
    std::list<boost::posix_time::time_duration>& prop_5();
    void prop_5(const std::list<boost::posix_time::time_duration>& v);
    void prop_5(const std::list<boost::posix_time::time_duration>&& v);

public:
    bool operator==(const class_f& rhs) const;
    bool operator!=(const class_f& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(class_f& other) noexcept;
    class_f& operator=(class_f other);

private:
    boost::gregorian::date prop_0_;
    boost::posix_time::ptime prop_1_;
    boost::posix_time::time_duration prop_2_;
    std::list<boost::gregorian::date> prop_3_;
    std::list<boost::posix_time::ptime> prop_4_;
    std::list<boost::posix_time::time_duration> prop_5_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::test_models::boost_model::class_f& lhs,
    dogen::test_models::boost_model::class_f& rhs) {
    lhs.swap(rhs);
}

}

#endif
