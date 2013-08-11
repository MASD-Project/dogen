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
#ifndef DOGEN_CPP_TYPES_MEMBER_DECLARATION_HPP
#define DOGEN_CPP_TYPES_MEMBER_DECLARATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <list>
#include <string>
#include "dogen/cpp/serialization/member_declaration_fwd_ser.hpp"
#include "dogen/cpp/types/decl_specifier.hpp"
#include "dogen/cpp/types/declarator.hpp"
#include "dogen/cpp/types/function_types.hpp"

namespace dogen {
namespace cpp {

class member_declaration final {
public:
    member_declaration(const member_declaration&) = default;
    member_declaration(member_declaration&&) = default;
    ~member_declaration() = default;

public:
    member_declaration();

public:
    member_declaration(
        const std::list<dogen::cpp::decl_specifier>& decl_specifier_seq,
        const dogen::cpp::declarator& declarator,
        const std::string& constant_initialiser,
        const dogen::cpp::function_types& function_type,
        const bool is_pure,
        const bool is_override,
        const bool is_default);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const member_declaration& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, member_declaration& v, unsigned int version);

public:
    const std::list<dogen::cpp::decl_specifier>& decl_specifier_seq() const;
    std::list<dogen::cpp::decl_specifier>& decl_specifier_seq();
    void decl_specifier_seq(const std::list<dogen::cpp::decl_specifier>& v);
    void decl_specifier_seq(const std::list<dogen::cpp::decl_specifier>&& v);

    const dogen::cpp::declarator& declarator() const;
    dogen::cpp::declarator& declarator();
    void declarator(const dogen::cpp::declarator& v);
    void declarator(const dogen::cpp::declarator&& v);

    const std::string& constant_initialiser() const;
    std::string& constant_initialiser();
    void constant_initialiser(const std::string& v);
    void constant_initialiser(const std::string&& v);

    dogen::cpp::function_types function_type() const;
    void function_type(const dogen::cpp::function_types& v);

    bool is_pure() const;
    void is_pure(const bool v);

    bool is_override() const;
    void is_override(const bool v);

    bool is_default() const;
    void is_default(const bool v);

public:
    bool operator==(const member_declaration& rhs) const;
    bool operator!=(const member_declaration& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(member_declaration& other) noexcept;
    member_declaration& operator=(member_declaration other);

private:
    std::list<dogen::cpp::decl_specifier> decl_specifier_seq_;
    dogen::cpp::declarator declarator_;
    std::string constant_initialiser_;
    dogen::cpp::function_types function_type_;
    bool is_pure_;
    bool is_override_;
    bool is_default_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::cpp::member_declaration& lhs,
    dogen::cpp::member_declaration& rhs) {
    lhs.swap(rhs);
}

}

#endif
