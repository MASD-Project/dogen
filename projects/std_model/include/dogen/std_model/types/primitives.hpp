/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#ifndef DOGEN_STD_MODEL_TYPES_PRIMITIVES_HPP
#define DOGEN_STD_MODEL_TYPES_PRIMITIVES_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <cstdint>
#include "dogen/std_model/serialization/primitives_fwd_ser.hpp"

namespace dogen {
namespace std_model {

class primitives final {
public:
    primitives(const primitives&) = default;
    primitives(primitives&&) = default;
    ~primitives() = default;

public:
    primitives();

public:
    primitives(
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
    friend void boost::serialization::save(Archive& ar, const primitives& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, primitives& v, unsigned int version);

public:
    std::int8_t prop_0() const {
        return prop_0_;
    }

    void prop_0(const std::int8_t v) {
        prop_0_ = v;
    }

    std::int16_t prop_1() const {
        return prop_1_;
    }

    void prop_1(const std::int16_t v) {
        prop_1_ = v;
    }

    std::int32_t prop_2() const {
        return prop_2_;
    }

    void prop_2(const std::int32_t v) {
        prop_2_ = v;
    }

    std::int64_t prop_3() const {
        return prop_3_;
    }

    void prop_3(const std::int64_t v) {
        prop_3_ = v;
    }

    std::uint8_t prop_4() const {
        return prop_4_;
    }

    void prop_4(const std::uint8_t v) {
        prop_4_ = v;
    }

    std::uint16_t prop_5() const {
        return prop_5_;
    }

    void prop_5(const std::uint16_t v) {
        prop_5_ = v;
    }

    std::uint32_t prop_6() const {
        return prop_6_;
    }

    void prop_6(const std::uint32_t v) {
        prop_6_ = v;
    }

    std::uint64_t prop_7() const {
        return prop_7_;
    }

    void prop_7(const std::uint64_t v) {
        prop_7_ = v;
    }

public:
    bool operator==(const primitives& rhs) const;
    bool operator!=(const primitives& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(primitives& other) noexcept;
    primitives& operator=(primitives other);

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

} }

namespace std {

template<>
inline void swap(
    dogen::std_model::primitives& lhs,
    dogen::std_model::primitives& rhs) {
    lhs.swap(rhs);
}

}

#endif
