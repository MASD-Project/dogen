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
#ifndef DOGEN_STEREOTYPES_TYPES_VERSIONED_HPP
#define DOGEN_STEREOTYPES_TYPES_VERSIONED_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/stereotypes/serialization/versioned_fwd_ser.hpp"

namespace dogen {
namespace stereotypes {

/**
 * @brief Types marked as versioned will generate a system property called version.
 */
class versioned final {
public:
    versioned(const versioned&) = default;
    versioned(versioned&&) = default;
    ~versioned() = default;

public:
    versioned();

public:
    explicit versioned(const unsigned int version);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const versioned& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, versioned& v, unsigned int version);

public:
    unsigned int version() const;
    void version(const unsigned int v);

public:
    bool operator==(const versioned& rhs) const;
    bool operator!=(const versioned& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(versioned& other) noexcept;
    versioned& operator=(versioned other);

private:
    unsigned int version_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::stereotypes::versioned& lhs,
    dogen::stereotypes::versioned& rhs) {
    lhs.swap(rhs);
}

}

#endif
