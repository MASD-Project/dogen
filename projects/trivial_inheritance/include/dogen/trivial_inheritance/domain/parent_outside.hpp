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
#ifndef DOGEN_TRIVIAL_INHERITANCE_DOMAIN_PARENT_OUTSIDE_HPP
#define DOGEN_TRIVIAL_INHERITANCE_DOMAIN_PARENT_OUTSIDE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <iosfwd>
#include "dogen/trivial_inheritance/domain/versioned_key.hpp"
#include "dogen/trivial_inheritance/serialization/parent_outside_fwd_ser.hpp"

namespace dogen {
namespace trivial_inheritance {

class parent_outside {
public:
    parent_outside() = default;
    parent_outside(const parent_outside&) = default;
    parent_outside(parent_outside&&) = default;

    virtual ~parent_outside() noexcept = 0;

public:
    explicit parent_outside(const dogen::trivial_inheritance::versioned_key& versioned_key);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const parent_outside& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, parent_outside& v, unsigned int version);

public:
    virtual void to_stream(std::ostream& s) const;

public:
    dogen::trivial_inheritance::versioned_key versioned_key() const {
        return versioned_key_;
    }

    void versioned_key(const dogen::trivial_inheritance::versioned_key& v) {
        versioned_key_ = v;
    }

protected:
    bool compare(const parent_outside& rhs) const;
public:
    virtual bool equals(const parent_outside& other) const = 0;

protected:
    void swap(parent_outside& other) noexcept;

private:
    dogen::trivial_inheritance::versioned_key versioned_key_;
};

inline parent_outside::~parent_outside() noexcept { }

inline bool operator==(const parent_outside& lhs, const parent_outside& rhs) {
    return lhs.equals(rhs);
}

} }



#endif
