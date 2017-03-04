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
#ifndef DOGEN_TEST_MODELS_CPP_MODEL_TYPES_PACKAGE_1_CLASS_5_HPP
#define DOGEN_TEST_MODELS_CPP_MODEL_TYPES_PACKAGE_1_CLASS_5_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/test_models/cpp_model/serialization/package_1/class_5_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace cpp_model {
namespace package_1 {

class class_5 final {
public:
    class_5(const class_5&) = default;
    class_5(class_5&&) = default;
    ~class_5() = default;

public:
    class_5();

public:
    explicit class_5(const int prop_0);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::test_models::cpp_model::package_1::class_5& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::test_models::cpp_model::package_1::class_5& v, unsigned int version);

public:
    int prop_0() const;
    void prop_0(const int v);

public:
    bool operator==(const class_5& rhs) const;
    bool operator!=(const class_5& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(class_5& other) noexcept;
    class_5& operator=(class_5 other);

private:
    int prop_0_;
};

} } } }

namespace std {

template<>
inline void swap(
    dogen::test_models::cpp_model::package_1::class_5& lhs,
    dogen::test_models::cpp_model::package_1::class_5& rhs) {
    lhs.swap(rhs);
}

}

#endif
