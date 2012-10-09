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
#ifndef DOGEN_TRIVIAL_INHERITANCE_DOMAIN_CHILD_HPP
#define DOGEN_TRIVIAL_INHERITANCE_DOMAIN_CHILD_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <iosfwd>
#include "dogen/trivial_inheritance/domain/versioned_key.hpp"

namespace dogen {
namespace trivial_inheritance {

class child_serializer;

class child {
public:
    child() = default;
    child(const child&) = default;
    ~child() = default;
    child(child&&) = default;

public:
    explicit child(dogen::trivial_inheritance::versioned_key versioned_key);

public:
    friend class dogen::trivial_inheritance::child_serializer;

public:
    void to_stream(std::ostream& stream) const;

public:
    dogen::trivial_inheritance::versioned_key versioned_key() const {
        return versioned_key_;
    }

    void versioned_key(dogen::trivial_inheritance::versioned_key value) {
        versioned_key_ = value;
    }

public:
    bool operator==(const child& rhs) const {
        return versioned_key_ == rhs.versioned_key_;
    }

    bool operator!=(const child rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(child& other);
    child& operator=(child other);

private:
    dogen::trivial_inheritance::versioned_key versioned_key_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::trivial_inheritance::child& lhs,
    dogen::trivial_inheritance::child& rhs) {
    lhs.swap(rhs);
}

}

#endif
