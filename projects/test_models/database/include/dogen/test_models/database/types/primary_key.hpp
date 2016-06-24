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
#ifndef DOGEN_TEST_MODELS_DATABASE_TYPES_PRIMARY_KEY_HPP
#define DOGEN_TEST_MODELS_DATABASE_TYPES_PRIMARY_KEY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen/test_models/database/serialization/primary_key_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace database {

class primary_key final {
public:
    primary_key(const primary_key&) = default;
    primary_key(primary_key&&) = default;
    ~primary_key() = default;

public:
    primary_key();

public:
    primary_key(
        const unsigned int prop_0,
        const std::string& prop_1);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::test_models::database::primary_key& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::test_models::database::primary_key& v, unsigned int version);

public:
    unsigned int prop_0() const;
    void prop_0(const unsigned int v);

    const std::string& prop_1() const;
    std::string& prop_1();
    void prop_1(const std::string& v);
    void prop_1(const std::string&& v);

public:
    bool operator==(const primary_key& rhs) const;
    bool operator!=(const primary_key& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(primary_key& other) noexcept;
    primary_key& operator=(primary_key other);

private:
    unsigned int prop_0_;
    std::string prop_1_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::test_models::database::primary_key& lhs,
    dogen::test_models::database::primary_key& rhs) {
    lhs.swap(rhs);
}

}

#endif
