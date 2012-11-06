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
#ifndef DOGEN_TRIVIAL_INHERITANCE_DOMAIN_PARENT_WITHOUT_MEMBERS_VERSIONED_KEY_HPP
#define DOGEN_TRIVIAL_INHERITANCE_DOMAIN_PARENT_WITHOUT_MEMBERS_VERSIONED_KEY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/trivial_inheritance/serialization/parent_without_members_versioned_key_fwd_ser.hpp"

namespace dogen {
namespace trivial_inheritance {

class parent_without_members_versioned_key final {
public:
    parent_without_members_versioned_key(const parent_without_members_versioned_key&) = default;
    parent_without_members_versioned_key(parent_without_members_versioned_key&&) = default;
    ~parent_without_members_versioned_key() = default;

public:
    parent_without_members_versioned_key();

public:
    parent_without_members_versioned_key(
        const unsigned int id,
        const unsigned int version);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const parent_without_members_versioned_key& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, parent_without_members_versioned_key& v, unsigned int version);

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
    bool operator==(const parent_without_members_versioned_key& rhs) const;
    bool operator!=(const parent_without_members_versioned_key& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(parent_without_members_versioned_key& other) noexcept;
    parent_without_members_versioned_key& operator=(parent_without_members_versioned_key other);

private:
    unsigned int id_;
    unsigned int version_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::trivial_inheritance::parent_without_members_versioned_key& lhs,
    dogen::trivial_inheritance::parent_without_members_versioned_key& rhs) {
    lhs.swap(rhs);
}

}

#endif
