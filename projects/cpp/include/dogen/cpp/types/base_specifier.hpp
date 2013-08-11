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
#ifndef DOGEN_CPP_TYPES_BASE_SPECIFIER_HPP
#define DOGEN_CPP_TYPES_BASE_SPECIFIER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/cpp/serialization/base_specifier_fwd_ser.hpp"
#include "dogen/cpp/types/access_specifier_types.hpp"
#include "dogen/cpp/types/qualified_id.hpp"

namespace dogen {
namespace cpp {

class base_specifier final {
public:
    base_specifier(const base_specifier&) = default;
    base_specifier(base_specifier&&) = default;
    ~base_specifier() = default;

public:
    base_specifier();

public:
    base_specifier(
        const bool is_virtual,
        const dogen::cpp::access_specifier_types& access,
        const dogen::cpp::qualified_id& name);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const base_specifier& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, base_specifier& v, unsigned int version);

public:
    /**
     * @brief If true, inheritance is virtual.
     */
    /**@{*/
    bool is_virtual() const;
    void is_virtual(const bool v);
    /**@}*/

    dogen::cpp::access_specifier_types access() const;
    void access(const dogen::cpp::access_specifier_types& v);

    const dogen::cpp::qualified_id& name() const;
    dogen::cpp::qualified_id& name();
    void name(const dogen::cpp::qualified_id& v);
    void name(const dogen::cpp::qualified_id&& v);

public:
    bool operator==(const base_specifier& rhs) const;
    bool operator!=(const base_specifier& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(base_specifier& other) noexcept;
    base_specifier& operator=(base_specifier other);

private:
    bool is_virtual_;
    dogen::cpp::access_specifier_types access_;
    dogen::cpp::qualified_id name_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::cpp::base_specifier& lhs,
    dogen::cpp::base_specifier& rhs) {
    lhs.swap(rhs);
}

}

#endif
