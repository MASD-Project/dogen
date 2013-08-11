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
#ifndef DOGEN_CPP_TYPES_DECL_SPECIFIER_HPP
#define DOGEN_CPP_TYPES_DECL_SPECIFIER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/cpp/serialization/decl_specifier_fwd_ser.hpp"
#include "dogen/cpp/types/function_specifier_types.hpp"
#include "dogen/cpp/types/storage_class_types.hpp"
#include "dogen/cpp/types/type_specifier.hpp"

namespace dogen {
namespace cpp {

class decl_specifier final {
public:
    decl_specifier(const decl_specifier&) = default;
    decl_specifier(decl_specifier&&) = default;
    ~decl_specifier() = default;

public:
    decl_specifier();

public:
    decl_specifier(
        const dogen::cpp::storage_class_types& storage_class_type,
        const dogen::cpp::type_specifier& type_specifier,
        const dogen::cpp::function_specifier_types& function_specifier,
        const bool is_friend,
        const bool is_typedef);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const decl_specifier& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, decl_specifier& v, unsigned int version);

public:
    dogen::cpp::storage_class_types storage_class_type() const;
    void storage_class_type(const dogen::cpp::storage_class_types& v);

    const dogen::cpp::type_specifier& type_specifier() const;
    dogen::cpp::type_specifier& type_specifier();
    void type_specifier(const dogen::cpp::type_specifier& v);
    void type_specifier(const dogen::cpp::type_specifier&& v);

    dogen::cpp::function_specifier_types function_specifier() const;
    void function_specifier(const dogen::cpp::function_specifier_types& v);

    bool is_friend() const;
    void is_friend(const bool v);

    bool is_typedef() const;
    void is_typedef(const bool v);

public:
    bool operator==(const decl_specifier& rhs) const;
    bool operator!=(const decl_specifier& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(decl_specifier& other) noexcept;
    decl_specifier& operator=(decl_specifier other);

private:
    dogen::cpp::storage_class_types storage_class_type_;
    dogen::cpp::type_specifier type_specifier_;
    dogen::cpp::function_specifier_types function_specifier_;
    bool is_friend_;
    bool is_typedef_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::cpp::decl_specifier& lhs,
    dogen::cpp::decl_specifier& rhs) {
    lhs.swap(rhs);
}

}

#endif
