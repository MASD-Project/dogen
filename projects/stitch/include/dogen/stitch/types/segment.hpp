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
#ifndef DOGEN_STITCH_TYPES_SEGMENT_HPP
#define DOGEN_STITCH_TYPES_SEGMENT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <string>
#include <algorithm>
#include "dogen/stitch/types/segment_types.hpp"
#include "dogen/stitch/serialization/segment_fwd_ser.hpp"

namespace dogen {
namespace stitch {

class segment final {
public:
    segment(const segment&) = default;
    segment(segment&&) = default;
    ~segment() = default;

public:
    segment();

public:
    segment(
        const dogen::stitch::segment_types& type,
        const std::string& content);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const segment& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, segment& v, unsigned int version);

public:
    dogen::stitch::segment_types type() const;
    void type(const dogen::stitch::segment_types& v);

    const std::string& content() const;
    std::string& content();
    void content(const std::string& v);
    void content(const std::string&& v);

public:
    bool operator==(const segment& rhs) const;
    bool operator!=(const segment& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(segment& other) noexcept;
    segment& operator=(segment other);

private:
    dogen::stitch::segment_types type_;
    std::string content_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::stitch::segment& lhs,
    dogen::stitch::segment& rhs) {
    lhs.swap(rhs);
}

}

#endif
