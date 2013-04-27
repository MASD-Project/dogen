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
#ifndef DOGEN_STEREOTYPES_TYPES_IMMUTABLE_ONE_PRIMITIVE_HPP
#define DOGEN_STEREOTYPES_TYPES_IMMUTABLE_ONE_PRIMITIVE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/stereotypes/serialization/immutable_one_primitive_fwd_ser.hpp"

namespace dogen {
namespace stereotypes {

/**
 * @brief Immutable class with a primitive property.
 */
class immutable_one_primitive final {
public:
    immutable_one_primitive(const immutable_one_primitive&) = default;
    immutable_one_primitive(immutable_one_primitive&&) = default;
    ~immutable_one_primitive() = default;
    immutable_one_primitive& operator=(const immutable_one_primitive&) = delete;

public:
    immutable_one_primitive();

public:
    explicit immutable_one_primitive(const bool prop_0);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const immutable_one_primitive& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, immutable_one_primitive& v, unsigned int version);

public:
    bool prop_0() const;

public:
    bool operator==(const immutable_one_primitive& rhs) const;
    bool operator!=(const immutable_one_primitive& rhs) const {
        return !this->operator==(rhs);
    }

private:
    bool prop_0_;
};

} }



#endif
