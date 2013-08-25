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
#ifndef DOGEN_OM_TYPES_CPP_MEMBER_FUNCTION_HPP
#define DOGEN_OM_TYPES_CPP_MEMBER_FUNCTION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <iosfwd>
#include "dogen/om/serialization/cpp_member_function_fwd_ser.hpp"
#include "dogen/om/types/cpp_abstract_function.hpp"
#include "dogen/om/types/cpp_member_function_types.hpp"

namespace dogen {
namespace om {

class cpp_member_function final : public dogen::om::cpp_abstract_function {
public:
    cpp_member_function(const cpp_member_function&) = default;
    cpp_member_function(cpp_member_function&&) = default;

public:
    cpp_member_function();

    virtual ~cpp_member_function() noexcept { }

public:
    cpp_member_function(
        const std::string& name,
        const std::list<dogen::om::doxygen_command>& commands,
        const dogen::om::cpp_representation_types& representation_type,
        const bool is_inline,
        const dogen::om::cpp_instance_typeref& return_type,
        const std::list<dogen::om::cpp_argument>& arguments,
        const bool is_friend,
        const bool is_virtual,
        const bool is_explicit,
        const bool is_pure,
        const bool is_override,
        const bool is_final,
        const bool is_default,
        const bool is_static,
        const dogen::om::cpp_member_function_types& type);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const cpp_member_function& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, cpp_member_function& v, unsigned int version);

public:
    virtual void accept(const cpp_feature_visitor& v) const override {
        v.visit(*this);
    }

    virtual void accept(cpp_feature_visitor& v) const override {
        v.visit(*this);
    }

    virtual void accept(const cpp_feature_visitor& v) override {
        v.visit(*this);
    }

    virtual void accept(cpp_feature_visitor& v) override {
        v.visit(*this);
    }

public:
    void to_stream(std::ostream& s) const override;

public:
    bool is_virtual() const;
    void is_virtual(const bool v);

    bool is_explicit() const;
    void is_explicit(const bool v);

    bool is_pure() const;
    void is_pure(const bool v);

    bool is_override() const;
    void is_override(const bool v);

    bool is_final() const;
    void is_final(const bool v);

    bool is_default() const;
    void is_default(const bool v);

    bool is_static() const;
    void is_static(const bool v);

    dogen::om::cpp_member_function_types type() const;
    void type(const dogen::om::cpp_member_function_types& v);

public:
    bool operator==(const cpp_member_function& rhs) const;
    bool operator!=(const cpp_member_function& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::om::cpp_feature& other) const override;

public:
    void swap(cpp_member_function& other) noexcept;
    cpp_member_function& operator=(cpp_member_function other);

private:
    bool is_virtual_;
    bool is_explicit_;
    bool is_pure_;
    bool is_override_;
    bool is_final_;
    bool is_default_;
    bool is_static_;
    dogen::om::cpp_member_function_types type_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::om::cpp_member_function& lhs,
    dogen::om::cpp_member_function& rhs) {
    lhs.swap(rhs);
}

}

#endif
