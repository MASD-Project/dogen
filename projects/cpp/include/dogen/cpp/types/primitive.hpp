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
#ifndef DOGEN_CPP_TYPES_PRIMITIVE_HPP
#define DOGEN_CPP_TYPES_PRIMITIVE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <iosfwd>
#include "dogen/cpp/serialization/primitive_fwd_ser.hpp"
#include "dogen/cpp/types/entity.hpp"

namespace dogen {
namespace cpp {

class primitive final : public dogen::cpp::entity {
public:
    primitive() = default;
    primitive(const primitive&) = default;
    primitive(primitive&&) = default;

    virtual ~primitive() noexcept { }

public:
    primitive(
        const std::string& name,
        const std::string& documentation,
        const std::list<std::string>& namespaces,
        const std::unordered_map<std::string, boost::filesystem::path>& relative_path_for_formatter,
        const std::unordered_map<std::string, dogen::cpp::includes>& includes_for_formatter);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const primitive& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, primitive& v, unsigned int version);

public:
    virtual void accept(const entity_visitor& v) const override {
        v.visit(*this);
    }

    virtual void accept(entity_visitor& v) const override {
        v.visit(*this);
    }

    virtual void accept(const entity_visitor& v) override {
        v.visit(*this);
    }

    virtual void accept(entity_visitor& v) override {
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
    bool equals(const dogen::cpp::entity& other) const override;

public:
    void swap(primitive& other) noexcept;
    primitive& operator=(primitive other);

};

} }

namespace std {

template<>
inline void swap(
    dogen::cpp::primitive& lhs,
    dogen::cpp::primitive& rhs) {
    lhs.swap(rhs);
}

}

#endif
