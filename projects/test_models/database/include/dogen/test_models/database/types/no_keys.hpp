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
#ifndef DOGEN_TEST_MODELS_DATABASE_TYPES_NO_KEYS_HPP
#define DOGEN_TEST_MODELS_DATABASE_TYPES_NO_KEYS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include "dogen/test_models/database/serialization/no_keys_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace database {

/**
 * @brief Simple value class with no primary keys, etc.
 */
class no_keys final {
public:
    no_keys(const no_keys&) = default;
    no_keys(no_keys&&) = default;
    ~no_keys() = default;

public:
    no_keys();

public:
    no_keys(
        const int prop_0,
        const unsigned int prop_1,
        const std::string& prop_2,
        const boost::posix_time::ptime& prop_3);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const no_keys& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, no_keys& v, unsigned int version);

public:
    int prop_0() const;
    void prop_0(const int v);

    unsigned int prop_1() const;
    void prop_1(const unsigned int v);

    const std::string& prop_2() const;
    std::string& prop_2();
    void prop_2(const std::string& v);
    void prop_2(const std::string&& v);

    const boost::posix_time::ptime& prop_3() const;
    boost::posix_time::ptime& prop_3();
    void prop_3(const boost::posix_time::ptime& v);
    void prop_3(const boost::posix_time::ptime&& v);

public:
    bool operator==(const no_keys& rhs) const;
    bool operator!=(const no_keys& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(no_keys& other) noexcept;
    no_keys& operator=(no_keys other);

private:
    int prop_0_;
    unsigned int prop_1_;
    std::string prop_2_;
    boost::posix_time::ptime prop_3_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::test_models::database::no_keys& lhs,
    dogen::test_models::database::no_keys& rhs) {
    lhs.swap(rhs);
}

}

#endif
