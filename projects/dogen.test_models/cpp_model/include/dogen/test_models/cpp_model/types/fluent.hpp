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
#ifndef DOGEN_TEST_MODELS_CPP_MODEL_TYPES_FLUENT_HPP
#define DOGEN_TEST_MODELS_CPP_MODEL_TYPES_FLUENT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen/test_models/cpp_model/types/value.hpp"
#include "dogen/test_models/cpp_model/serialization/fluent_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace cpp_model {

/**
 * @brief Tests the fluent scenario across the different types of properties.
 */
class fluent final {
public:
    fluent(const fluent&) = default;
    fluent(fluent&&) = default;
    ~fluent() = default;

public:
    fluent();

public:
    fluent(
        const unsigned int prop_0,
        const std::string& prop_1,
        const dogen::test_models::cpp_model::value& prop_2);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::test_models::cpp_model::fluent& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::test_models::cpp_model::fluent& v, unsigned int version);

public:
    unsigned int prop_0() const;
    fluent& prop_0(const unsigned int v);

    const std::string& prop_1() const;
    std::string& prop_1();
    fluent& prop_1(const std::string& v);
    fluent& prop_1(const std::string&& v);

    const dogen::test_models::cpp_model::value& prop_2() const;
    dogen::test_models::cpp_model::value& prop_2();
    fluent& prop_2(const dogen::test_models::cpp_model::value& v);
    fluent& prop_2(const dogen::test_models::cpp_model::value&& v);

public:
    bool operator==(const fluent& rhs) const;
    bool operator!=(const fluent& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(fluent& other) noexcept;
    fluent& operator=(fluent other);

private:
    unsigned int prop_0_;
    std::string prop_1_;
    dogen::test_models::cpp_model::value prop_2_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::test_models::cpp_model::fluent& lhs,
    dogen::test_models::cpp_model::fluent& rhs) {
    lhs.swap(rhs);
}

}

#endif
