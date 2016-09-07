/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
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
#ifndef DOGEN_QUILT_CPP_TYPES_PROPERTIES_INCLUDERS_INFO_HPP
#define DOGEN_QUILT_CPP_TYPES_PROPERTIES_INCLUDERS_INFO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <algorithm>
#include "dogen/quilt.cpp/types/properties/entity.hpp"
#include "dogen/quilt.cpp/types/properties/formattable_visitor.hpp"
#include "dogen/quilt.cpp/serialization/properties/includers_info_fwd_ser.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace properties {

class includers_info final : public dogen::quilt::cpp::properties::entity {
public:
    includers_info() = default;
    includers_info(const includers_info&) = default;
    includers_info(includers_info&&) = default;

    virtual ~includers_info() noexcept { }

public:
    includers_info(
        const std::string& identity,
        const dogen::quilt::cpp::properties::origin_types origin_type,
        const std::string& id,
        const std::string& name,
        const std::string& qualified_name,
        const std::string& documentation,
        const std::list<std::string>& namespaces);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::quilt::cpp::properties::includers_info& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::quilt::cpp::properties::includers_info& v, unsigned int version);

public:
    using formattable::accept;

    virtual void accept(const formattable_visitor& v) const override {
        v.visit(*this);
    }

    virtual void accept(formattable_visitor& v) const override {
        v.visit(*this);
    }

    virtual void accept(const formattable_visitor& v) override {
        v.visit(*this);
    }

    virtual void accept(formattable_visitor& v) override {
        v.visit(*this);
    }

public:
    void to_stream(std::ostream& s) const override;

public:
    bool operator==(const includers_info& rhs) const;
    bool operator!=(const includers_info& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::quilt::cpp::properties::formattable& other) const override;

public:
    void swap(includers_info& other) noexcept;
    includers_info& operator=(includers_info other);

};

} } } }

namespace std {

template<>
inline void swap(
    dogen::quilt::cpp::properties::includers_info& lhs,
    dogen::quilt::cpp::properties::includers_info& rhs) {
    lhs.swap(rhs);
}

}

#endif
