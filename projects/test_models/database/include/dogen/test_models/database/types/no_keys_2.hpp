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
#ifndef DOGEN_TEST_MODELS_DATABASE_TYPES_NO_KEYS_2_HPP
#define DOGEN_TEST_MODELS_DATABASE_TYPES_NO_KEYS_2_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/test_models/database/serialization/no_keys_2_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace database {

class no_keys_2 final {
public:
    no_keys_2(const no_keys_2&) = default;
    no_keys_2(no_keys_2&&) = default;
    ~no_keys_2() = default;

public:
    no_keys_2();

public:
    explicit no_keys_2(const int prop_0);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const no_keys_2& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, no_keys_2& v, unsigned int version);

public:
    int prop_0() const;
    void prop_0(const int v);

public:
    bool operator==(const no_keys_2& rhs) const;
    bool operator!=(const no_keys_2& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(no_keys_2& other) noexcept;
    no_keys_2& operator=(no_keys_2 other);

private:
    int prop_0_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::test_models::database::no_keys_2& lhs,
    dogen::test_models::database::no_keys_2& rhs) {
    lhs.swap(rhs);
}

}

#endif
