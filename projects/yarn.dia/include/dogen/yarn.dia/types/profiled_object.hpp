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
#ifndef DOGEN_YARN_DIA_TYPES_PROFILED_OBJECT_HPP
#define DOGEN_YARN_DIA_TYPES_PROFILED_OBJECT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/yarn.dia/types/profile.hpp"
#include "dogen/yarn.dia/types/processed_object.hpp"
#include "dogen/yarn.dia/serialization/profiled_object_fwd_ser.hpp"

namespace dogen {
namespace yarn {
namespace dia {

class profiled_object final {
public:
    profiled_object() = default;
    profiled_object(const profiled_object&) = default;
    profiled_object(profiled_object&&) = default;
    ~profiled_object() = default;

public:
    profiled_object(
        const dogen::yarn::dia::processed_object& object,
        const dogen::yarn::dia::profile& profile);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::yarn::dia::profiled_object& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::yarn::dia::profiled_object& v, unsigned int version);

public:
    const dogen::yarn::dia::processed_object& object() const;
    dogen::yarn::dia::processed_object& object();
    void object(const dogen::yarn::dia::processed_object& v);
    void object(const dogen::yarn::dia::processed_object&& v);

    const dogen::yarn::dia::profile& profile() const;
    dogen::yarn::dia::profile& profile();
    void profile(const dogen::yarn::dia::profile& v);
    void profile(const dogen::yarn::dia::profile&& v);

public:
    bool operator==(const profiled_object& rhs) const;
    bool operator!=(const profiled_object& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(profiled_object& other) noexcept;
    profiled_object& operator=(profiled_object other);

private:
    dogen::yarn::dia::processed_object object_;
    dogen::yarn::dia::profile profile_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::yarn::dia::profiled_object& lhs,
    dogen::yarn::dia::profiled_object& rhs) {
    lhs.swap(rhs);
}

}

#endif
