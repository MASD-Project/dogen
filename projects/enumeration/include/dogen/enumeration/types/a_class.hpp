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
#ifndef DOGEN_ENUMERATION_TYPES_A_CLASS_HPP
#define DOGEN_ENUMERATION_TYPES_A_CLASS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/enumeration/serialization/a_class_fwd_ser.hpp"
#include "dogen/enumeration/types/book_types.hpp"
#include "dogen/enumeration/types/colour_types.hpp"
#include "dogen/enumeration/types/pkg1/shape_types.hpp"

namespace dogen {
namespace enumeration {

class a_class final {
public:
    a_class() = default;
    a_class(const a_class&) = default;
    a_class(a_class&&) = default;
    ~a_class() = default;

public:
    a_class(
        const dogen::enumeration::colour_types& colour_type,
        const dogen::enumeration::book_types& book_type,
        const dogen::enumeration::pkg1::shape_types& shape_type);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const a_class& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, a_class& v, unsigned int version);

public:
    dogen::enumeration::colour_types colour_type() const {
        return colour_type_;
    }

    void colour_type(const dogen::enumeration::colour_types& v) {
        colour_type_ = v;
    }

    dogen::enumeration::book_types book_type() const {
        return book_type_;
    }

    void book_type(const dogen::enumeration::book_types& v) {
        book_type_ = v;
    }

    dogen::enumeration::pkg1::shape_types shape_type() const {
        return shape_type_;
    }

    void shape_type(const dogen::enumeration::pkg1::shape_types& v) {
        shape_type_ = v;
    }

public:
    bool operator==(const a_class& rhs) const;
    bool operator!=(const a_class& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(a_class& other) noexcept;
    a_class& operator=(a_class other);

private:
    dogen::enumeration::colour_types colour_type_;
    dogen::enumeration::book_types book_type_;
    dogen::enumeration::pkg1::shape_types shape_type_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::enumeration::a_class& lhs,
    dogen::enumeration::a_class& rhs) {
    lhs.swap(rhs);
}

}

#endif
