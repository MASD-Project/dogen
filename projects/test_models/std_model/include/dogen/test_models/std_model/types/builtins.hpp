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
#ifndef DOGEN_TEST_MODELS_STD_MODEL_TYPES_BUILTINS_HPP
#define DOGEN_TEST_MODELS_STD_MODEL_TYPES_BUILTINS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <cstdint>
#include <algorithm>
#include "dogen/test_models/std_model/serialization/builtins_fwd_ser.hpp"

namespace dogen {
namespace test_models {
namespace std_model {

class builtins final {
public:
    builtins(const builtins&) = default;
    builtins(builtins&&) = default;
    ~builtins() = default;

public:
    builtins();

public:
    builtins(
        const std::int8_t prop_0,
        const std::int16_t prop_1,
        const std::int32_t prop_2,
        const std::int64_t prop_3,
        const std::uint8_t prop_4,
        const std::uint16_t prop_5,
        const std::uint32_t prop_6,
        const std::uint64_t prop_7);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::test_models::std_model::builtins& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::test_models::std_model::builtins& v, unsigned int version);

public:
    std::int8_t prop_0() const;
    void prop_0(const std::int8_t v);

    std::int16_t prop_1() const;
    void prop_1(const std::int16_t v);

    std::int32_t prop_2() const;
    void prop_2(const std::int32_t v);

    std::int64_t prop_3() const;
    void prop_3(const std::int64_t v);

    std::uint8_t prop_4() const;
    void prop_4(const std::uint8_t v);

    std::uint16_t prop_5() const;
    void prop_5(const std::uint16_t v);

    std::uint32_t prop_6() const;
    void prop_6(const std::uint32_t v);

    std::uint64_t prop_7() const;
    void prop_7(const std::uint64_t v);

public:
    bool operator==(const builtins& rhs) const;
    bool operator!=(const builtins& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(builtins& other) noexcept;
    builtins& operator=(builtins other);

private:
    std::int8_t prop_0_;
    std::int16_t prop_1_;
    std::int32_t prop_2_;
    std::int64_t prop_3_;
    std::uint8_t prop_4_;
    std::uint16_t prop_5_;
    std::uint32_t prop_6_;
    std::uint64_t prop_7_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::test_models::std_model::builtins& lhs,
    dogen::test_models::std_model::builtins& rhs) {
    lhs.swap(rhs);
}

}

#endif
