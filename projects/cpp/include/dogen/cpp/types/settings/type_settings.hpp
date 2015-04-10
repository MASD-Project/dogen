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
#ifndef DOGEN_CPP_TYPES_SETTINGS_TYPE_SETTINGS_HPP
#define DOGEN_CPP_TYPES_SETTINGS_TYPE_SETTINGS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/cpp/types/formattables/family_types.hpp"
#include "dogen/cpp/serialization/settings/type_settings_fwd_ser.hpp"

namespace dogen {
namespace cpp {
namespace settings {

class type_settings final {
public:
    type_settings(const type_settings&) = default;
    type_settings(type_settings&&) = default;
    ~type_settings() = default;

public:
    type_settings();

public:
    type_settings(
        const dogen::cpp::formattables::family_types& family_type,
        const bool requires_manual_default_constructor,
        const bool requires_manual_move_constructor);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const type_settings& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, type_settings& v, unsigned int version);

public:
    dogen::cpp::formattables::family_types family_type() const;
    void family_type(const dogen::cpp::formattables::family_types& v);

    bool requires_manual_default_constructor() const;
    void requires_manual_default_constructor(const bool v);

    bool requires_manual_move_constructor() const;
    void requires_manual_move_constructor(const bool v);

public:
    bool operator==(const type_settings& rhs) const;
    bool operator!=(const type_settings& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(type_settings& other) noexcept;
    type_settings& operator=(type_settings other);

private:
    dogen::cpp::formattables::family_types family_type_;
    bool requires_manual_default_constructor_;
    bool requires_manual_move_constructor_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::cpp::settings::type_settings& lhs,
    dogen::cpp::settings::type_settings& rhs) {
    lhs.swap(rhs);
}

}

#endif
