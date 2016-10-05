/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
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
#ifndef DOGEN_QUILT_CPP_TYPES_FORMATTABLES_FACET_PROFILE_HPP
#define DOGEN_QUILT_CPP_TYPES_FORMATTABLES_FACET_PROFILE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/quilt.cpp/serialization/formattables/facet_profile_fwd_ser.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formattables {

class facet_profile final {
public:
    facet_profile(const facet_profile&) = default;
    facet_profile(facet_profile&&) = default;
    ~facet_profile() = default;

public:
    facet_profile();

public:
    facet_profile(
        const bool enabled,
        const bool overwrite);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::quilt::cpp::formattables::facet_profile& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::quilt::cpp::formattables::facet_profile& v, unsigned int version);

public:
    bool enabled() const;
    void enabled(const bool v);

    bool overwrite() const;
    void overwrite(const bool v);

public:
    bool operator==(const facet_profile& rhs) const;
    bool operator!=(const facet_profile& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(facet_profile& other) noexcept;
    facet_profile& operator=(facet_profile other);

private:
    bool enabled_;
    bool overwrite_;
};

} } } }

namespace std {

template<>
inline void swap(
    dogen::quilt::cpp::formattables::facet_profile& lhs,
    dogen::quilt::cpp::formattables::facet_profile& rhs) {
    lhs.swap(rhs);
}

}

#endif
