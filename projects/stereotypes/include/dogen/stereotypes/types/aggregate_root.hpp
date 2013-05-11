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
#ifndef DOGEN_STEREOTYPES_TYPES_AGGREGATE_ROOT_HPP
#define DOGEN_STEREOTYPES_TYPES_AGGREGATE_ROOT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/stereotypes/serialization/aggregate_root_fwd_ser.hpp"

namespace dogen {
namespace stereotypes {

/**
 * @brief Type is an aggregate root.
 */
class aggregate_root final {
public:
    aggregate_root(const aggregate_root&) = default;
    aggregate_root(aggregate_root&&) = default;
    ~aggregate_root() = default;

public:
    aggregate_root();

public:
    explicit aggregate_root(const int prop_0);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const aggregate_root& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, aggregate_root& v, unsigned int version);

public:
    int prop_0() const;
    void prop_0(const int v);

public:
    bool operator==(const aggregate_root& rhs) const;
    bool operator!=(const aggregate_root& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(aggregate_root& other) noexcept;
    aggregate_root& operator=(aggregate_root other);

private:
    int prop_0_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::stereotypes::aggregate_root& lhs,
    dogen::stereotypes::aggregate_root& rhs) {
    lhs.swap(rhs);
}

}

#endif
