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
#ifndef DOGEN_TEST_MODELS_CPP_MODEL_TYPES_CHAR_PRIMITIVE_HPP
#define DOGEN_TEST_MODELS_CPP_MODEL_TYPES_CHAR_PRIMITIVE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/test_models/cpp_model/serialization/char_primitive_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace cpp_model {
/**
 * @brief Test a primitive with an underlying char.
 */
class char_primitive final {
public:
    char_primitive() = default;
    char_primitive(const char_primitive&) = default;
    char_primitive(char_primitive&&) = default;
    ~char_primitive() = default;
public:
    explicit char_primitive(const char value);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::test_models::cpp_model::char_primitive& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::test_models::cpp_model::char_primitive& v, unsigned int version);

public:
    /**
     * @brief Obtain the underlying value.
     */
    /**@{*/
    char value() const;
    void value(const char v);
    /**@}*/

public:
    explicit operator char() const {
        return value_;
    }

public:
    bool operator==(const char_primitive& rhs) const;
    bool operator!=(const char_primitive& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(char_primitive& other) noexcept;
    char_primitive& operator=(char_primitive other);

private:
    char value_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::test_models::cpp_model::char_primitive& lhs,
    dogen::test_models::cpp_model::char_primitive& rhs) {
    lhs.swap(rhs);
}

}

#endif
