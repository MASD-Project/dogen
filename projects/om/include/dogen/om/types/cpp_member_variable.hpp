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
#ifndef DOGEN_OM_TYPES_CPP_MEMBER_VARIABLE_HPP
#define DOGEN_OM_TYPES_CPP_MEMBER_VARIABLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <iosfwd>
#include "dogen/om/serialization/cpp_member_variable_fwd_ser.hpp"
#include "dogen/om/types/cpp_abstract_instance.hpp"

namespace dogen {
namespace om {

class cpp_member_variable final : public dogen::om::cpp_abstract_instance {
public:
    cpp_member_variable(const cpp_member_variable&) = default;
    cpp_member_variable(cpp_member_variable&&) = default;

public:
    cpp_member_variable();

    virtual ~cpp_member_variable() noexcept { }

public:
    cpp_member_variable(
        const std::string& name,
        const std::list<dogen::om::doxygen_command>& commands,
        const dogen::om::cpp_typeref& type,
        const std::string& default_value,
        const bool is_mutable,
        const bool is_static);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const cpp_member_variable& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, cpp_member_variable& v, unsigned int version);

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
    bool is_mutable() const;
    void is_mutable(const bool v);

    bool is_static() const;
    void is_static(const bool v);

public:
    bool operator==(const cpp_member_variable& rhs) const;
    bool operator!=(const cpp_member_variable& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::om::cpp_feature& other) const override;

public:
    void swap(cpp_member_variable& other) noexcept;
    cpp_member_variable& operator=(cpp_member_variable other);

private:
    bool is_mutable_;
    bool is_static_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::om::cpp_member_variable& lhs,
    dogen::om::cpp_member_variable& rhs) {
    lhs.swap(rhs);
}

}

#endif
