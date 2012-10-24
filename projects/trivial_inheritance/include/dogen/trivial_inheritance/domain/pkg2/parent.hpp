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
#ifndef DOGEN_TRIVIAL_INHERITANCE_DOMAIN_PKG2_PARENT_HPP
#define DOGEN_TRIVIAL_INHERITANCE_DOMAIN_PKG2_PARENT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <iosfwd>
#include "dogen/trivial_inheritance/domain/versioned_key.hpp"
#include "dogen/trivial_inheritance/serialization/pkg2/parent_fwd_ser.hpp"

namespace dogen {
namespace trivial_inheritance {
namespace pkg2 {

class parent {
public:
    parent(const parent&) = default;
    parent(parent&&) = default;

public:
    parent();

    virtual ~parent() noexcept = 0;

public:
    parent(
        const int prop_0,
        const dogen::trivial_inheritance::versioned_key& versioned_key);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const parent& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, parent& v, unsigned int version);

public:
    virtual void to_stream(std::ostream& s) const;

public:
    int prop_0() const {
        return prop_0_;
    }

    void prop_0(const int v) {
        prop_0_ = v;
    }

    dogen::trivial_inheritance::versioned_key versioned_key() const {
        return versioned_key_;
    }

    void versioned_key(const dogen::trivial_inheritance::versioned_key& v) {
        versioned_key_ = v;
    }

protected:
    bool operator==(const parent& rhs) const;
    bool operator!=(const parent& rhs) const {
        return !this->operator==(rhs);
    }

protected:
    void swap(parent& other) noexcept;

private:
    int prop_0_;
    dogen::trivial_inheritance::versioned_key versioned_key_;
};


inline parent::~parent() noexcept { }

} } }



#endif
