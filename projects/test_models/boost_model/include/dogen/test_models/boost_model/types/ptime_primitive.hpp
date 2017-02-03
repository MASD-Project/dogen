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
#ifndef DOGEN_TEST_MODELS_BOOST_MODEL_TYPES_PTIME_PRIMITIVE_HPP
#define DOGEN_TEST_MODELS_BOOST_MODEL_TYPES_PTIME_PRIMITIVE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include "dogen/test_models/boost_model/serialization/ptime_primitive_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace boost_model {
/**
 * @brief Test a primitive with an underlying ptime.
 */
class ptime_primitive final {
public:
    ptime_primitive() = default;
    ptime_primitive(const ptime_primitive&) = default;
    ptime_primitive(ptime_primitive&&) = default;
    ~ptime_primitive() = default;
public:
    explicit ptime_primitive(const boost::posix_time::ptime& value);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::test_models::boost_model::ptime_primitive& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::test_models::boost_model::ptime_primitive& v, unsigned int version);

public:
    /**
     * @brief Obtain the underlying value.
     */
    /**@{*/
    const boost::posix_time::ptime& value() const;
    boost::posix_time::ptime& value();
    void value(const boost::posix_time::ptime& v);
    void value(const boost::posix_time::ptime&& v);
    /**@}*/

public:
    explicit operator boost::posix_time::ptime() const {
        return value_;
    }

public:
    bool operator==(const ptime_primitive& rhs) const;
    bool operator!=(const ptime_primitive& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(ptime_primitive& other) noexcept;
    ptime_primitive& operator=(ptime_primitive other);

private:
    boost::posix_time::ptime value_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::test_models::boost_model::ptime_primitive& lhs,
    dogen::test_models::boost_model::ptime_primitive& rhs) {
    lhs.swap(rhs);
}

}

#endif
