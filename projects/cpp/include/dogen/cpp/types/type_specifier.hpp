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
#ifndef DOGEN_CPP_TYPES_TYPE_SPECIFIER_HPP
#define DOGEN_CPP_TYPES_TYPE_SPECIFIER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include "dogen/cpp/serialization/type_specifier_fwd_ser.hpp"
#include "dogen/cpp/types/class_key_types.hpp"
#include "dogen/cpp/types/cv_qualifier_types.hpp"
#include "dogen/cpp/types/pointer_types.hpp"
#include "dogen/cpp/types/qualified_id.hpp"
#include "dogen/cpp/types/template_id.hpp"

namespace dogen {
namespace cpp {

class type_specifier final {
public:
    type_specifier(const type_specifier&) = default;
    type_specifier(type_specifier&&) = default;
    ~type_specifier() = default;

public:
    type_specifier();

public:
    type_specifier(
        const dogen::cpp::cv_qualifier_types& cv_qualifier,
        const dogen::cpp::pointer_types& pointer_type,
        const dogen::cpp::qualified_id& qualified_id,
        const dogen::cpp::class_key_types& class_key,
        const dogen::cpp::template_id& template_id);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const type_specifier& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, type_specifier& v, unsigned int version);

public:
    /**
     * @brief Const volatile qualifiers for identifier.
     */
    /**@{*/
    dogen::cpp::cv_qualifier_types cv_qualifier() const;
    void cv_qualifier(const dogen::cpp::cv_qualifier_types& v);
    /**@}*/

    dogen::cpp::pointer_types pointer_type() const;
    void pointer_type(const dogen::cpp::pointer_types& v);

    const dogen::cpp::qualified_id& qualified_id() const;
    dogen::cpp::qualified_id& qualified_id();
    void qualified_id(const dogen::cpp::qualified_id& v);
    void qualified_id(const dogen::cpp::qualified_id&& v);

    dogen::cpp::class_key_types class_key() const;
    void class_key(const dogen::cpp::class_key_types& v);

    const dogen::cpp::template_id& template_id() const;
    dogen::cpp::template_id& template_id();
    void template_id(const dogen::cpp::template_id& v);
    void template_id(const dogen::cpp::template_id&& v);

public:
    bool operator==(const type_specifier& rhs) const;
    bool operator!=(const type_specifier& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(type_specifier& other) noexcept;
    type_specifier& operator=(type_specifier other);

private:
    dogen::cpp::cv_qualifier_types cv_qualifier_;
    dogen::cpp::pointer_types pointer_type_;
    dogen::cpp::qualified_id qualified_id_;
    dogen::cpp::class_key_types class_key_;
    dogen::cpp::template_id template_id_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::cpp::type_specifier& lhs,
    dogen::cpp::type_specifier& rhs) {
    lhs.swap(rhs);
}

}

#endif
