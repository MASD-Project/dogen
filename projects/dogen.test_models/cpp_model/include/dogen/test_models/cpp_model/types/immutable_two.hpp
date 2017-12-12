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
#ifndef DOGEN_TEST_MODELS_CPP_MODEL_TYPES_IMMUTABLE_TWO_HPP
#define DOGEN_TEST_MODELS_CPP_MODEL_TYPES_IMMUTABLE_TWO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen/test_models/cpp_model/serialization/immutable_two_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace cpp_model {

class immutable_two final {
public:
    immutable_two(const immutable_two&) = default;
    immutable_two(immutable_two&&) = default;
    ~immutable_two() = default;
    immutable_two& operator=(const immutable_two&) = delete;

public:
    immutable_two();

public:
    immutable_two(
        const bool prop_0,
        const std::string& prop_1);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::test_models::cpp_model::immutable_two& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::test_models::cpp_model::immutable_two& v, unsigned int version);

public:
    bool prop_0() const;

    const std::string& prop_1() const;

public:
    bool operator==(const immutable_two& rhs) const;
    bool operator!=(const immutable_two& rhs) const {
        return !this->operator==(rhs);
    }

private:
    bool prop_0_;
    std::string prop_1_;
};

} } }

#endif
