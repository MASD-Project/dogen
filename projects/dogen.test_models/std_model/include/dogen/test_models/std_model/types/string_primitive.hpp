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
#ifndef DOGEN_TEST_MODELS_STD_MODEL_TYPES_STRING_PRIMITIVE_HPP
#define DOGEN_TEST_MODELS_STD_MODEL_TYPES_STRING_PRIMITIVE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen/test_models/std_model/serialization/string_primitive_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace std_model {
/**
 * @brief Test a primitive with an underlying string.
 */
class string_primitive final {
public:
    string_primitive() = default;
    string_primitive(const string_primitive&) = default;
    string_primitive(string_primitive&&) = default;
    ~string_primitive() = default;
public:
    explicit string_primitive(const std::string& value);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::test_models::std_model::string_primitive& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::test_models::std_model::string_primitive& v, unsigned int version);

public:
    /**
     * @brief Obtain the underlying value.
     */
    /**@{*/
    const std::string& value() const;
    std::string& value();
    void value(const std::string& v);
    void value(const std::string&& v);
    /**@}*/

public:
    explicit operator std::string() const {
        return value_;
    }

public:
    bool operator==(const string_primitive& rhs) const;
    bool operator!=(const string_primitive& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(string_primitive& other) noexcept;
    string_primitive& operator=(string_primitive other);

private:
    std::string value_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::test_models::std_model::string_primitive& lhs,
    dogen::test_models::std_model::string_primitive& rhs) {
    lhs.swap(rhs);
}

}

#endif
