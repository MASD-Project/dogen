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
#ifndef DOGEN_ENTITY_SERVICE_VALUE_TYPES_ENTITY_HPP
#define DOGEN_ENTITY_SERVICE_VALUE_TYPES_ENTITY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/entity_service_value/serialization/entity_fwd_ser.hpp"
#include "dogen/entity_service_value/types/entity_versioned_key.hpp"

namespace dogen {
namespace entity_service_value {

class entity final {
public:
    entity(const entity&) = default;
    entity(entity&&) = default;
    ~entity() = default;

public:
    entity();

public:
    entity(
        const int prop_0,
        const dogen::entity_service_value::entity_versioned_key& versioned_key);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const entity& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, entity& v, unsigned int version);

public:
    int prop_0() const;
    void prop_0(const int v);

    const dogen::entity_service_value::entity_versioned_key& versioned_key() const;
    dogen::entity_service_value::entity_versioned_key& versioned_key();
    void versioned_key(const dogen::entity_service_value::entity_versioned_key& v);
    void versioned_key(const dogen::entity_service_value::entity_versioned_key&& v);

public:
    bool operator==(const entity& rhs) const;
    bool operator!=(const entity& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(entity& other) noexcept;
    entity& operator=(entity other);

private:
    int prop_0_;
    dogen::entity_service_value::entity_versioned_key versioned_key_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::entity_service_value::entity& lhs,
    dogen::entity_service_value::entity& rhs) {
    lhs.swap(rhs);
}

}

#endif
