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
#ifndef DOGEN_ANNOTATIONS_TYPES_SCRIBBLE_HPP
#define DOGEN_ANNOTATIONS_TYPES_SCRIBBLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <string>
#include <utility>
#include <algorithm>
#include "dogen/annotations/serialization/scribble_fwd_ser.hpp"

namespace dogen {
namespace annotations {

class scribble final {
public:
    scribble() = default;
    scribble(const scribble&) = default;
    scribble(scribble&&) = default;
    ~scribble() = default;

public:
    explicit scribble(const std::list<std::pair<std::string, std::string> >& entries);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::annotations::scribble& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::annotations::scribble& v, unsigned int version);

public:
    const std::list<std::pair<std::string, std::string> >& entries() const;
    std::list<std::pair<std::string, std::string> >& entries();
    void entries(const std::list<std::pair<std::string, std::string> >& v);
    void entries(const std::list<std::pair<std::string, std::string> >&& v);

public:
    bool operator==(const scribble& rhs) const;
    bool operator!=(const scribble& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(scribble& other) noexcept;
    scribble& operator=(scribble other);

private:
    std::list<std::pair<std::string, std::string> > entries_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::annotations::scribble& lhs,
    dogen::annotations::scribble& rhs) {
    lhs.swap(rhs);
}

}

#endif
