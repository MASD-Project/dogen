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
#ifndef DOGEN_TEST_MODELS_CPP_MODEL_TYPES_IMMUTABLE_PRIMITIVE_HPP
#define DOGEN_TEST_MODELS_CPP_MODEL_TYPES_IMMUTABLE_PRIMITIVE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/test_models/cpp_model/serialization/immutable_primitive_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace cpp_model {
/**
 * @brief Test for a primitive which is also immutable.
 */
class immutable_primitive final {
public:
    immutable_primitive() = default;
    immutable_primitive(const immutable_primitive&) = default;
    immutable_primitive(immutable_primitive&&) = default;
    ~immutable_primitive() = default;
    immutable_primitive& operator=(const immutable_primitive&) = delete;
public:
    explicit immutable_primitive(const short value);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::test_models::cpp_model::immutable_primitive& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::test_models::cpp_model::immutable_primitive& v, unsigned int version);

public:
    /**
     * @brief Obtain the underlying value.
     */
    /**@{*/
    short value() const;
    void value(const short v);
    /**@}*/

public:
    explicit operator short() const {
        return value_;
    }

public:
    bool operator==(const immutable_primitive& rhs) const;
    bool operator!=(const immutable_primitive& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(immutable_primitive& other) noexcept;

private:
    short value_;
};

} } }

#endif
