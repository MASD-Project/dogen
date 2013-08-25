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
#ifndef DOGEN_OM_TYPES_CPP_BASE_HPP
#define DOGEN_OM_TYPES_CPP_BASE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/om/serialization/cpp_base_fwd_ser.hpp"
#include "dogen/om/types/cpp_access_specifier_types.hpp"
#include "dogen/om/types/cpp_typeref.hpp"

namespace dogen {
namespace om {

class cpp_base final {
public:
    cpp_base(const cpp_base&) = default;
    cpp_base(cpp_base&&) = default;
    ~cpp_base() = default;

public:
    cpp_base();

public:
    cpp_base(
        const bool is_virtual,
        const dogen::om::cpp_access_specifier_types& access,
        const dogen::om::cpp_typeref& type);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const cpp_base& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, cpp_base& v, unsigned int version);

public:
    /**
     * @brief If true, inheritance is virtual.
     */
    /**@{*/
    bool is_virtual() const;
    void is_virtual(const bool v);
    /**@}*/

    dogen::om::cpp_access_specifier_types access() const;
    void access(const dogen::om::cpp_access_specifier_types& v);

    const dogen::om::cpp_typeref& type() const;
    dogen::om::cpp_typeref& type();
    void type(const dogen::om::cpp_typeref& v);
    void type(const dogen::om::cpp_typeref&& v);

public:
    bool operator==(const cpp_base& rhs) const;
    bool operator!=(const cpp_base& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(cpp_base& other) noexcept;
    cpp_base& operator=(cpp_base other);

private:
    bool is_virtual_;
    dogen::om::cpp_access_specifier_types access_;
    dogen::om::cpp_typeref type_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::om::cpp_base& lhs,
    dogen::om::cpp_base& rhs) {
    lhs.swap(rhs);
}

}

#endif
