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
#ifndef DOGEN_OM_TYPES_PREAMBLE_FIELD_HPP
#define DOGEN_OM_TYPES_PREAMBLE_FIELD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <string>
#include "dogen/om/serialization/preamble_field_fwd_ser.hpp"

namespace dogen {
namespace om {

class preamble_field final {
public:
    preamble_field() = default;
    preamble_field(const preamble_field&) = default;
    preamble_field(preamble_field&&) = default;
    ~preamble_field() = default;

public:
    preamble_field(
        const std::string& name,
        const std::string& value);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const preamble_field& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, preamble_field& v, unsigned int version);

public:
    const std::string& name() const;
    std::string& name();
    void name(const std::string& v);
    void name(const std::string&& v);

    const std::string& value() const;
    std::string& value();
    void value(const std::string& v);
    void value(const std::string&& v);

public:
    bool operator==(const preamble_field& rhs) const;
    bool operator!=(const preamble_field& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(preamble_field& other) noexcept;
    preamble_field& operator=(preamble_field other);

private:
    std::string name_;
    std::string value_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::om::preamble_field& lhs,
    dogen::om::preamble_field& rhs) {
    lhs.swap(rhs);
}

}

#endif
