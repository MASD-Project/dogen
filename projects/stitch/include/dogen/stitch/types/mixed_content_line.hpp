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
#ifndef DOGEN_STITCH_TYPES_MIXED_CONTENT_LINE_HPP
#define DOGEN_STITCH_TYPES_MIXED_CONTENT_LINE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <algorithm>
#include "dogen/stitch/types/segment.hpp"
#include "dogen/stitch/serialization/mixed_content_line_fwd_ser.hpp"

namespace dogen {
namespace stitch {

class mixed_content_line final {
public:
    mixed_content_line() = default;
    mixed_content_line(const mixed_content_line&) = default;
    mixed_content_line(mixed_content_line&&) = default;
    ~mixed_content_line() = default;

public:
    explicit mixed_content_line(const std::list<dogen::stitch::segment>& segments);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const mixed_content_line& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, mixed_content_line& v, unsigned int version);

public:
    const std::list<dogen::stitch::segment>& segments() const;
    std::list<dogen::stitch::segment>& segments();
    void segments(const std::list<dogen::stitch::segment>& v);
    void segments(const std::list<dogen::stitch::segment>&& v);

public:
    bool operator==(const mixed_content_line& rhs) const;
    bool operator!=(const mixed_content_line& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(mixed_content_line& other) noexcept;
    mixed_content_line& operator=(mixed_content_line other);

private:
    std::list<dogen::stitch::segment> segments_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::stitch::mixed_content_line& lhs,
    dogen::stitch::mixed_content_line& rhs) {
    lhs.swap(rhs);
}

}

#endif
