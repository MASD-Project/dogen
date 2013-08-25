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
#ifndef DOGEN_OM_TYPES_CMAKE_FEATURE_HPP
#define DOGEN_OM_TYPES_CMAKE_FEATURE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <iosfwd>
#include "dogen/om/serialization/cmake_feature_fwd_ser.hpp"

namespace dogen {
namespace om {

/**
 * @brief Base class for all CMake features.
 */
class cmake_feature {
public:
    cmake_feature() = default;
    cmake_feature(const cmake_feature&) = default;
    cmake_feature(cmake_feature&&) = default;
    cmake_feature& operator=(const cmake_feature&) = default;

    virtual ~cmake_feature() noexcept = 0;

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const cmake_feature& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, cmake_feature& v, unsigned int version);

public:
    virtual void to_stream(std::ostream& s) const;

protected:
    bool compare(const cmake_feature& rhs) const;
public:
    virtual bool equals(const cmake_feature& other) const = 0;

protected:
    void swap(cmake_feature& other) noexcept;

};

inline cmake_feature::~cmake_feature() noexcept { }

inline bool operator==(const cmake_feature& lhs, const cmake_feature& rhs) {
    return lhs.equals(rhs);
}

} }

#endif
