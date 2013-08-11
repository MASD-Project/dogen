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
#ifndef DOGEN_CPP_TYPES_DECLARATOR_HPP
#define DOGEN_CPP_TYPES_DECLARATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <list>
#include "dogen/cpp/serialization/declarator_fwd_ser.hpp"
#include "dogen/cpp/types/cv_qualifier_types.hpp"
#include "dogen/cpp/types/parameter_declaration.hpp"
#include "dogen/cpp/types/pointer_types.hpp"
#include "dogen/cpp/types/qualified_id.hpp"

namespace dogen {
namespace cpp {

/**
 * @brief Declares a single object, function, or type, within a declaration.
 */
class declarator final {
public:
    declarator(const declarator&) = default;
    declarator(declarator&&) = default;
    ~declarator() = default;

public:
    declarator();

public:
    declarator(
        const dogen::cpp::cv_qualifier_types& cv_qualifier,
        const dogen::cpp::pointer_types& pointer_type,
        const dogen::cpp::cv_qualifier_types& pointer_cv_qualifier,
        const dogen::cpp::qualified_id& declarator_id,
        const std::list<dogen::cpp::qualified_id>& exception_specification,
        const std::list<dogen::cpp::parameter_declaration>& parameter_declaration_list);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const declarator& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, declarator& v, unsigned int version);

public:
    dogen::cpp::cv_qualifier_types cv_qualifier() const;
    void cv_qualifier(const dogen::cpp::cv_qualifier_types& v);

    dogen::cpp::pointer_types pointer_type() const;
    void pointer_type(const dogen::cpp::pointer_types& v);

    dogen::cpp::cv_qualifier_types pointer_cv_qualifier() const;
    void pointer_cv_qualifier(const dogen::cpp::cv_qualifier_types& v);

    const dogen::cpp::qualified_id& declarator_id() const;
    dogen::cpp::qualified_id& declarator_id();
    void declarator_id(const dogen::cpp::qualified_id& v);
    void declarator_id(const dogen::cpp::qualified_id&& v);

    const std::list<dogen::cpp::qualified_id>& exception_specification() const;
    std::list<dogen::cpp::qualified_id>& exception_specification();
    void exception_specification(const std::list<dogen::cpp::qualified_id>& v);
    void exception_specification(const std::list<dogen::cpp::qualified_id>&& v);

    const std::list<dogen::cpp::parameter_declaration>& parameter_declaration_list() const;
    std::list<dogen::cpp::parameter_declaration>& parameter_declaration_list();
    void parameter_declaration_list(const std::list<dogen::cpp::parameter_declaration>& v);
    void parameter_declaration_list(const std::list<dogen::cpp::parameter_declaration>&& v);

public:
    bool operator==(const declarator& rhs) const;
    bool operator!=(const declarator& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(declarator& other) noexcept;
    declarator& operator=(declarator other);

private:
    dogen::cpp::cv_qualifier_types cv_qualifier_;
    dogen::cpp::pointer_types pointer_type_;
    dogen::cpp::cv_qualifier_types pointer_cv_qualifier_;
    dogen::cpp::qualified_id declarator_id_;
    std::list<dogen::cpp::qualified_id> exception_specification_;
    std::list<dogen::cpp::parameter_declaration> parameter_declaration_list_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::cpp::declarator& lhs,
    dogen::cpp::declarator& rhs) {
    lhs.swap(rhs);
}

}

#endif
