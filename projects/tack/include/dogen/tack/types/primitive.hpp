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
#ifndef DOGEN_TACK_TYPES_PRIMITIVE_HPP
#define DOGEN_TACK_TYPES_PRIMITIVE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <algorithm>
#include "dogen/tack/types/type.hpp"
#include "dogen/tack/serialization/primitive_fwd_ser.hpp"

namespace dogen {
namespace tack {

/**
 * @brief Represents a value type that is built-in to the language.
 */
class primitive final : public dogen::tack::type {
public:
    primitive() = default;
    primitive(const primitive&) = default;
    primitive(primitive&&) = default;

    virtual ~primitive() noexcept { }

public:
    primitive(
        const std::string& documentation,
        const dogen::dynamic::object& extensions,
        const dogen::tack::name& name,
        const dogen::tack::generation_types generation_type,
        const dogen::tack::origin_types origin_type,
        const boost::optional<dogen::tack::name>& containing_module);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const primitive& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, primitive& v, unsigned int version);

public:
    virtual void accept(const type_visitor& v) const override {
        v.visit(*this);
    }

    virtual void accept(type_visitor& v) const override {
        v.visit(*this);
    }

    virtual void accept(const type_visitor& v) override {
        v.visit(*this);
    }

    virtual void accept(type_visitor& v) override {
        v.visit(*this);
    }

public:
    void to_stream(std::ostream& s) const override;

public:
    bool operator==(const primitive& rhs) const;
    bool operator!=(const primitive& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::tack::type& other) const override;

public:
    void swap(primitive& other) noexcept;
    primitive& operator=(primitive other);

};

} }

namespace std {

template<>
inline void swap(
    dogen::tack::primitive& lhs,
    dogen::tack::primitive& rhs) {
    lhs.swap(rhs);
}

}

#endif
