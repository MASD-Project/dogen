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
#ifndef DOGEN_CPP_TYPES_MEMBER_SPECIFICATION_HPP
#define DOGEN_CPP_TYPES_MEMBER_SPECIFICATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <list>
#include "dogen/cpp/serialization/member_specification_fwd_ser.hpp"
#include "dogen/cpp/types/access_specifier_types.hpp"
#include "dogen/cpp/types/member_declaration.hpp"

namespace dogen {
namespace cpp {

class member_specification final {
public:
    member_specification(const member_specification&) = default;
    member_specification(member_specification&&) = default;
    ~member_specification() = default;

public:
    member_specification();

public:
    member_specification(
        const dogen::cpp::access_specifier_types& access,
        const std::list<dogen::cpp::member_declaration>& member_declaration_list);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const member_specification& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, member_specification& v, unsigned int version);

public:
    dogen::cpp::access_specifier_types access() const;
    void access(const dogen::cpp::access_specifier_types& v);

    const std::list<dogen::cpp::member_declaration>& member_declaration_list() const;
    std::list<dogen::cpp::member_declaration>& member_declaration_list();
    void member_declaration_list(const std::list<dogen::cpp::member_declaration>& v);
    void member_declaration_list(const std::list<dogen::cpp::member_declaration>&& v);

public:
    bool operator==(const member_specification& rhs) const;
    bool operator!=(const member_specification& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(member_specification& other) noexcept;
    member_specification& operator=(member_specification other);

private:
    dogen::cpp::access_specifier_types access_;
    std::list<dogen::cpp::member_declaration> member_declaration_list_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::cpp::member_specification& lhs,
    dogen::cpp::member_specification& rhs) {
    lhs.swap(rhs);
}

}

#endif
