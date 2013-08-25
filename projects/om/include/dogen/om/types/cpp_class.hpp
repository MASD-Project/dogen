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
#ifndef DOGEN_OM_TYPES_CPP_CLASS_HPP
#define DOGEN_OM_TYPES_CPP_CLASS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <iosfwd>
#include <list>
#include "dogen/om/serialization/cpp_class_fwd_ser.hpp"
#include "dogen/om/types/cpp_base.hpp"
#include "dogen/om/types/cpp_feature.hpp"
#include "dogen/om/types/cpp_member_group.hpp"
#include "dogen/om/types/cpp_representation_types.hpp"
#include "dogen/om/types/doxygen_command.hpp"

namespace dogen {
namespace om {

class cpp_class final : public dogen::om::cpp_feature {
public:
    cpp_class(const cpp_class&) = default;
    cpp_class(cpp_class&&) = default;

public:
    cpp_class();

    virtual ~cpp_class() noexcept { }

public:
    cpp_class(
        const std::string& name,
        const std::list<dogen::om::doxygen_command>& commands,
        const dogen::om::cpp_representation_types& representation_type,
        const std::list<dogen::om::cpp_base>& bases,
        const std::list<dogen::om::cpp_member_group>& members,
        const bool is_final,
        const bool is_friend);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const cpp_class& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, cpp_class& v, unsigned int version);

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
    const std::list<dogen::om::doxygen_command>& commands() const;
    std::list<dogen::om::doxygen_command>& commands();
    void commands(const std::list<dogen::om::doxygen_command>& v);
    void commands(const std::list<dogen::om::doxygen_command>&& v);

    dogen::om::cpp_representation_types representation_type() const;
    void representation_type(const dogen::om::cpp_representation_types& v);

    const std::list<dogen::om::cpp_base>& bases() const;
    std::list<dogen::om::cpp_base>& bases();
    void bases(const std::list<dogen::om::cpp_base>& v);
    void bases(const std::list<dogen::om::cpp_base>&& v);

    const std::list<dogen::om::cpp_member_group>& members() const;
    std::list<dogen::om::cpp_member_group>& members();
    void members(const std::list<dogen::om::cpp_member_group>& v);
    void members(const std::list<dogen::om::cpp_member_group>&& v);

    bool is_final() const;
    void is_final(const bool v);

    bool is_friend() const;
    void is_friend(const bool v);

public:
    bool operator==(const cpp_class& rhs) const;
    bool operator!=(const cpp_class& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::om::cpp_feature& other) const override;

public:
    void swap(cpp_class& other) noexcept;
    cpp_class& operator=(cpp_class other);

private:
    std::list<dogen::om::doxygen_command> commands_;
    dogen::om::cpp_representation_types representation_type_;
    std::list<dogen::om::cpp_base> bases_;
    std::list<dogen::om::cpp_member_group> members_;
    bool is_final_;
    bool is_friend_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::om::cpp_class& lhs,
    dogen::om::cpp_class& rhs) {
    lhs.swap(rhs);
}

}

#endif
