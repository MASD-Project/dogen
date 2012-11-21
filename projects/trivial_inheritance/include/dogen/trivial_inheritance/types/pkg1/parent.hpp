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
#ifndef DOGEN_TRIVIAL_INHERITANCE_TYPES_PKG1_PARENT_HPP
#define DOGEN_TRIVIAL_INHERITANCE_TYPES_PKG1_PARENT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <iosfwd>
#include "dogen/trivial_inheritance/serialization/pkg1/parent_fwd_ser.hpp"

namespace dogen {
namespace trivial_inheritance {
namespace pkg1 {

class parent {
public:
    parent(const parent&) = default;
    parent(parent&&) = default;

public:
    parent();

    virtual ~parent() noexcept = 0;

public:
    explicit parent(const unsigned int prop_0);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const parent& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, parent& v, unsigned int version);

public:
    virtual void to_stream(std::ostream& s) const;

public:
    unsigned int prop_0() const {
        return prop_0_;
    }

    void prop_0(const unsigned int v) {
        prop_0_ = v;
    }

protected:
    bool compare(const parent& rhs) const;
public:
    virtual bool equals(const parent& other) const = 0;

protected:
    void swap(parent& other) noexcept;

private:
    unsigned int prop_0_;
};

inline parent::~parent() noexcept { }

inline bool operator==(const parent& lhs, const parent& rhs) {
    return lhs.equals(rhs);
}

} } }



#endif
