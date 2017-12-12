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
#ifndef DOGEN_TEST_MODELS_CPP_MODEL_TYPES_IMMUTABLE_ONE_BUILTIN_HPP
#define DOGEN_TEST_MODELS_CPP_MODEL_TYPES_IMMUTABLE_ONE_BUILTIN_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/test_models/cpp_model/serialization/immutable_one_builtin_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace cpp_model {

/**
 * @brief Immutable class with a built-in property.
 */
class immutable_one_builtin final {
public:
    immutable_one_builtin(const immutable_one_builtin&) = default;
    immutable_one_builtin(immutable_one_builtin&&) = default;
    ~immutable_one_builtin() = default;
    immutable_one_builtin& operator=(const immutable_one_builtin&) = delete;

public:
    immutable_one_builtin();

public:
    explicit immutable_one_builtin(const bool prop_0);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::test_models::cpp_model::immutable_one_builtin& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::test_models::cpp_model::immutable_one_builtin& v, unsigned int version);

public:
    bool prop_0() const;

public:
    bool operator==(const immutable_one_builtin& rhs) const;
    bool operator!=(const immutable_one_builtin& rhs) const {
        return !this->operator==(rhs);
    }

private:
    bool prop_0_;
};

} } }

#endif
