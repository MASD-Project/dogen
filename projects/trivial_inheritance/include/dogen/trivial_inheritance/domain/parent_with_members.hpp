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
#ifndef DOGEN_TRIVIAL_INHERITANCE_DOMAIN_PARENT_WITH_MEMBERS_HPP
#define DOGEN_TRIVIAL_INHERITANCE_DOMAIN_PARENT_WITH_MEMBERS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <iosfwd>
#include "dogen/trivial_inheritance/serialization/parent_with_members_fwd_ser.hpp"

namespace dogen {
namespace trivial_inheritance {

class parent_with_members {
public:
    parent_with_members(const parent_with_members&) = default;
    parent_with_members(parent_with_members&&) = default;

public:
    parent_with_members();

    virtual ~parent_with_members() noexcept = 0;

public:
    explicit parent_with_members(const int prop_0);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const parent_with_members& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, parent_with_members& v, unsigned int version);

public:
    virtual void to_stream(std::ostream& s) const;

public:
    int prop_0() const {
        return prop_0_;
    }

    void prop_0(const int v) {
        prop_0_ = v;
    }

protected:
    bool compare(const parent_with_members& rhs) const;
public:
    virtual bool equals(const parent_with_members& other) const = 0;

protected:
    void swap(parent_with_members& other) noexcept;

private:
    int prop_0_;
};

inline parent_with_members::~parent_with_members() noexcept { }

inline bool operator==(const parent_with_members& lhs, const parent_with_members& rhs) {
    return lhs.equals(rhs);
}

} }



#endif
