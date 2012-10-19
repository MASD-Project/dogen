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
#ifndef DOGEN_ENABLE_FACET_IO_DOMAIN_VERSIONED_KEY_HPP
#define DOGEN_ENABLE_FACET_IO_DOMAIN_VERSIONED_KEY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/enable_facet_io/domain/unversioned_key.hpp"

namespace dogen {
namespace enable_facet_io {

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
        unsigned int id,
        unsigned int version);

public:
    friend class dogen::enable_facet_io::versioned_key_serializer;

public:
    unversioned_key to_unversioned() const;

public:
    unsigned int id() const {
        return id_;
    }

    void id(unsigned int value) {
        id_ = value;
    }

    unsigned int version() const {
        return version_;
    }

    void version(unsigned int value) {
        version_ = value;
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
    dogen::enable_facet_io::versioned_key& lhs,
    dogen::enable_facet_io::versioned_key& rhs) {
    lhs.swap(rhs);
}

}

#endif
