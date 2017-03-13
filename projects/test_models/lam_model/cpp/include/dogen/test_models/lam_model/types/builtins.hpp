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
#ifndef DOGEN_TEST_MODELS_LAM_MODEL_TYPES_BUILTINS_HPP
#define DOGEN_TEST_MODELS_LAM_MODEL_TYPES_BUILTINS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <cstdint>
#include <algorithm>
#include "dogen/test_models/lam_model/serialization/builtins_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace lam_model {

class builtins final {
public:
    builtins(const builtins&) = default;
    builtins(builtins&&) = default;
    ~builtins() = default;

public:
    builtins();

public:
    builtins(
        const char prop_0,
        const unsigned char prop_1,
        const std::int8_t prop_2,
        const std::int16_t prop_3,
        const std::int32_t prop_4,
        const std::int64_t prop_5,
        const int prop_6,
        const float prop_7,
        const double prop_8,
        const bool prop_9);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::test_models::lam_model::builtins& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::test_models::lam_model::builtins& v, unsigned int version);

public:
    char prop_0() const;
    void prop_0(const char v);

    unsigned char prop_1() const;
    void prop_1(const unsigned char v);

    std::int8_t prop_2() const;
    void prop_2(const std::int8_t v);

    std::int16_t prop_3() const;
    void prop_3(const std::int16_t v);

    std::int32_t prop_4() const;
    void prop_4(const std::int32_t v);

    std::int64_t prop_5() const;
    void prop_5(const std::int64_t v);

    int prop_6() const;
    void prop_6(const int v);

    float prop_7() const;
    void prop_7(const float v);

    double prop_8() const;
    void prop_8(const double v);

    bool prop_9() const;
    void prop_9(const bool v);

public:
    bool operator==(const builtins& rhs) const;
    bool operator!=(const builtins& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(builtins& other) noexcept;
    builtins& operator=(builtins other);

private:
    char prop_0_;
    unsigned char prop_1_;
    std::int8_t prop_2_;
    std::int16_t prop_3_;
    std::int32_t prop_4_;
    std::int64_t prop_5_;
    int prop_6_;
    float prop_7_;
    double prop_8_;
    bool prop_9_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::test_models::lam_model::builtins& lhs,
    dogen::test_models::lam_model::builtins& rhs) {
    lhs.swap(rhs);
}

}

#endif
