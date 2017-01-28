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
#ifndef DOGEN_YARN_TYPES_PRIMITIVE_HPP
#define DOGEN_YARN_TYPES_PRIMITIVE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <algorithm>
#include "dogen/yarn/types/name.hpp"
#include "dogen/yarn/types/element.hpp"
#include "dogen/yarn/types/attribute.hpp"
#include "dogen/yarn/serialization/primitive_fwd_ser.hpp"

namespace dogen {
namespace yarn {

/**
 * @brief Defines an element created by the user to wrap another element, most likely a built-in.
 */
class primitive final : public dogen::yarn::element {
public:
    primitive(const primitive&) = default;
    primitive(primitive&&) = default;

public:
    primitive();

    virtual ~primitive() noexcept { }

public:
    primitive(
        const std::string& documentation,
        const dogen::annotations::annotation& annotation,
        const dogen::yarn::name& name,
        const dogen::yarn::origin_types origin_type,
        const boost::optional<dogen::yarn::name>& contained_by,
        const bool in_global_module,
        const std::vector<std::string>& stereotypes,
        const bool is_element_extension,
        const dogen::yarn::name& underlying_type,
        const bool is_nullable,
        const dogen::yarn::attribute& value_attribute);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::yarn::primitive& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::yarn::primitive& v, unsigned int version);

public:
    using element::accept;

    virtual void accept(const element_visitor& v) const override;
    virtual void accept(element_visitor& v) const override;
    virtual void accept(const element_visitor& v) override;
    virtual void accept(element_visitor& v) override;
public:
    void to_stream(std::ostream& s) const override;

public:
    const dogen::yarn::name& underlying_type() const;
    dogen::yarn::name& underlying_type();
    void underlying_type(const dogen::yarn::name& v);
    void underlying_type(const dogen::yarn::name&& v);

    /**
     * @brief If true, this element can be null (empty).
     */
    /**@{*/
    bool is_nullable() const;
    void is_nullable(const bool v);
    /**@}*/

    const dogen::yarn::attribute& value_attribute() const;
    dogen::yarn::attribute& value_attribute();
    void value_attribute(const dogen::yarn::attribute& v);
    void value_attribute(const dogen::yarn::attribute&& v);

public:
    bool operator==(const primitive& rhs) const;
    bool operator!=(const primitive& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::yarn::element& other) const override;

public:
    void swap(primitive& other) noexcept;
    primitive& operator=(primitive other);

private:
    dogen::yarn::name underlying_type_;
    bool is_nullable_;
    dogen::yarn::attribute value_attribute_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::yarn::primitive& lhs,
    dogen::yarn::primitive& rhs) {
    lhs.swap(rhs);
}

}

#endif
