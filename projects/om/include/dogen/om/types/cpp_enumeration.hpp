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
#ifndef DOGEN_OM_TYPES_CPP_ENUMERATION_HPP
#define DOGEN_OM_TYPES_CPP_ENUMERATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <iosfwd>
#include <list>
#include "dogen/om/serialization/cpp_enumeration_fwd_ser.hpp"
#include "dogen/om/types/cpp_enumerator.hpp"
#include "dogen/om/types/cpp_feature.hpp"
#include "dogen/om/types/cpp_fundamental_types.hpp"
#include "dogen/om/types/cpp_representation_types.hpp"
#include "dogen/om/types/doxygen_command.hpp"

namespace dogen {
namespace om {

class cpp_enumeration final : public dogen::om::cpp_feature {
public:
    cpp_enumeration(const cpp_enumeration&) = default;
    cpp_enumeration(cpp_enumeration&&) = default;

public:
    cpp_enumeration();

    virtual ~cpp_enumeration() noexcept { }

public:
    cpp_enumeration(
        const std::string& name,
        const std::list<dogen::om::doxygen_command>& commands,
        const dogen::om::cpp_representation_types& representation_type,
        const dogen::om::cpp_fundamental_types& type,
        const std::list<dogen::om::cpp_enumerator>& enumerators,
        const bool is_class);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const cpp_enumeration& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, cpp_enumeration& v, unsigned int version);

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

    dogen::om::cpp_fundamental_types type() const;
    void type(const dogen::om::cpp_fundamental_types& v);

    const std::list<dogen::om::cpp_enumerator>& enumerators() const;
    std::list<dogen::om::cpp_enumerator>& enumerators();
    void enumerators(const std::list<dogen::om::cpp_enumerator>& v);
    void enumerators(const std::list<dogen::om::cpp_enumerator>&& v);

    bool is_class() const;
    void is_class(const bool v);

public:
    bool operator==(const cpp_enumeration& rhs) const;
    bool operator!=(const cpp_enumeration& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::om::cpp_feature& other) const override;

public:
    void swap(cpp_enumeration& other) noexcept;
    cpp_enumeration& operator=(cpp_enumeration other);

private:
    std::list<dogen::om::doxygen_command> commands_;
    dogen::om::cpp_representation_types representation_type_;
    dogen::om::cpp_fundamental_types type_;
    std::list<dogen::om::cpp_enumerator> enumerators_;
    bool is_class_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::om::cpp_enumeration& lhs,
    dogen::om::cpp_enumeration& rhs) {
    lhs.swap(rhs);
}

}

#endif
