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
#ifndef DOGEN_TEST_MODELS_CPP_MODEL_TYPES_BUILTINS_HPP
#define DOGEN_TEST_MODELS_CPP_MODEL_TYPES_BUILTINS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/test_models/cpp_model/serialization/builtins_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace cpp_model {

class builtins final {
public:
    builtins(const builtins&) = default;
    builtins(builtins&&) = default;
    ~builtins() = default;

public:
    builtins();

public:
    builtins(
        const bool bool_property,
        const char char_property,
        const unsigned char uchar_property,
        const int int_property,
        const unsigned int uint_property,
        const long long_property,
        const unsigned long ulong_property,
        const long long long_long_property,
        const unsigned long long ulong_long_property,
        const short short_property,
        const unsigned short ushort_property,
        const double double_property,
        const float float_property);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::test_models::cpp_model::builtins& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::test_models::cpp_model::builtins& v, unsigned int version);

public:
    bool bool_property() const;
    void bool_property(const bool v);

    char char_property() const;
    void char_property(const char v);

    unsigned char uchar_property() const;
    void uchar_property(const unsigned char v);

    int int_property() const;
    void int_property(const int v);

    unsigned int uint_property() const;
    void uint_property(const unsigned int v);

    long long_property() const;
    void long_property(const long v);

    unsigned long ulong_property() const;
    void ulong_property(const unsigned long v);

    long long long_long_property() const;
    void long_long_property(const long long v);

    unsigned long long ulong_long_property() const;
    void ulong_long_property(const unsigned long long v);

    short short_property() const;
    void short_property(const short v);

    unsigned short ushort_property() const;
    void ushort_property(const unsigned short v);

    double double_property() const;
    void double_property(const double v);

    float float_property() const;
    void float_property(const float v);

public:
    bool operator==(const builtins& rhs) const;
    bool operator!=(const builtins& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(builtins& other) noexcept;
    builtins& operator=(builtins other);

private:
    bool bool_property_;
    char char_property_;
    unsigned char uchar_property_;
    int int_property_;
    unsigned int uint_property_;
    long long_property_;
    unsigned long ulong_property_;
    long long long_long_property_;
    unsigned long long ulong_long_property_;
    short short_property_;
    unsigned short ushort_property_;
    double double_property_;
    float float_property_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::test_models::cpp_model::builtins& lhs,
    dogen::test_models::cpp_model::builtins& rhs) {
    lhs.swap(rhs);
}

}

#endif
