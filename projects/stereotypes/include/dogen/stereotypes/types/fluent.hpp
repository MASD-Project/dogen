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
#ifndef DOGEN_STEREOTYPES_TYPES_FLUENT_HPP
#define DOGEN_STEREOTYPES_TYPES_FLUENT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <string>
#include "dogen/stereotypes/serialization/fluent_fwd_ser.hpp"
#include "dogen/stereotypes/types/value.hpp"

namespace dogen {
namespace stereotypes {

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
        const dogen::stereotypes::value& prop_2);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const fluent& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, fluent& v, unsigned int version);

public:
    unsigned int prop_0() const;
    fluent& prop_0(const unsigned int v);

    const std::string& prop_1() const;
    std::string& prop_1();
    fluent& prop_1(const std::string& v);
    fluent& prop_1(const std::string&& v);

    const dogen::stereotypes::value& prop_2() const;
    dogen::stereotypes::value& prop_2();
    fluent& prop_2(const dogen::stereotypes::value& v);
    fluent& prop_2(const dogen::stereotypes::value&& v);

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
    dogen::stereotypes::value prop_2_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::stereotypes::fluent& lhs,
    dogen::stereotypes::fluent& rhs) {
    lhs.swap(rhs);
}

}

#endif
