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
#ifndef DOGEN_CLASS_WITHOUT_ATTRIBUTES_DOMAIN_VERSIONED_KEY_HPP
#define DOGEN_CLASS_WITHOUT_ATTRIBUTES_DOMAIN_VERSIONED_KEY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/class_without_attributes/domain/unversioned_key.hpp"

namespace dogen {
namespace class_without_attributes {

class versioned_key_serializer;

class versioned_key final {
public:
    versioned_key(const versioned_key&) = default;
    versioned_key(versioned_key&&) = default;
    ~versioned_key() = default;

public:
    versioned_key();


public:
    versioned_key(
        const unsigned int id,
        const unsigned int version);

public:
    friend class dogen::class_without_attributes::versioned_key_serializer;

public:
    unversioned_key to_unversioned() const;

public:
    unsigned int id() const {
        return id_;
    }

    void id(const unsigned int v) {
        id_ = v;
    }

    unsigned int version() const {
        return version_;
    }

    void version(const unsigned int v) {
        version_ = v;
    }

public:
    bool operator==(const versioned_key& rhs) const;

    bool operator!=(const versioned_key& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(versioned_key& other) noexcept;

public:
    versioned_key& operator=(versioned_key other);
private:
    unsigned int id_;
    unsigned int version_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::class_without_attributes::versioned_key& lhs,
    dogen::class_without_attributes::versioned_key& rhs) {
    lhs.swap(rhs);
}

}

#endif
