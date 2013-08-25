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
#ifndef DOGEN_OM_TYPES_CPP_TYPEDEF_HPP
#define DOGEN_OM_TYPES_CPP_TYPEDEF_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <iosfwd>
#include <list>
#include "dogen/om/serialization/cpp_typedef_fwd_ser.hpp"
#include "dogen/om/types/cpp_feature.hpp"
#include "dogen/om/types/cpp_typeref.hpp"
#include "dogen/om/types/doxygen_command.hpp"

namespace dogen {
namespace om {

class cpp_typedef final : public dogen::om::cpp_feature {
public:
    cpp_typedef() = default;
    cpp_typedef(const cpp_typedef&) = default;
    cpp_typedef(cpp_typedef&&) = default;

    virtual ~cpp_typedef() noexcept { }

public:
    cpp_typedef(
        const std::string& name,
        const std::list<dogen::om::doxygen_command>& commands,
        const dogen::om::cpp_typeref& type);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const cpp_typedef& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, cpp_typedef& v, unsigned int version);

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

    const dogen::om::cpp_typeref& type() const;
    dogen::om::cpp_typeref& type();
    void type(const dogen::om::cpp_typeref& v);
    void type(const dogen::om::cpp_typeref&& v);

public:
    bool operator==(const cpp_typedef& rhs) const;
    bool operator!=(const cpp_typedef& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::om::cpp_feature& other) const override;

public:
    void swap(cpp_typedef& other) noexcept;
    cpp_typedef& operator=(cpp_typedef other);

private:
    std::list<dogen::om::doxygen_command> commands_;
    dogen::om::cpp_typeref type_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::om::cpp_typedef& lhs,
    dogen::om::cpp_typedef& rhs) {
    lhs.swap(rhs);
}

}

#endif
