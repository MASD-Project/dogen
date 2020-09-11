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
#ifndef DOGEN_LOGICAL_TYPES_ENTITIES_STRUCTURAL_PRIMITIVE_HPP
#define DOGEN_LOGICAL_TYPES_ENTITIES_STRUCTURAL_PRIMITIVE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <algorithm>
#include <boost/optional.hpp>
#include "dogen.logical/types/entities/element.hpp"
#include "dogen.logical/types/entities/attribute.hpp"
#include "dogen.logical/types/entities/orm/primitive_properties.hpp"

namespace dogen::logical::entities::structural {

/**
 * @brief Defines an element created by the user to wrap another element, most likely a built-in.
 */
class primitive final : public dogen::logical::entities::element {
public:
    primitive(const primitive&) = default;

public:
    primitive();

    virtual ~primitive() noexcept { }

public:
    primitive(primitive&& rhs);

public:
    primitive(
        const dogen::identification::entities::logical_name& name,
        const std::string& documentation,
        const dogen::identification::entities::codec_provenance& provenance,
        const dogen::identification::entities::logical_id& contained_by,
        const bool in_global_module,
        const dogen::logical::entities::stereotypes& stereotypes,
        const dogen::identification::entities::logical_meta_name& meta_name,
        const dogen::identification::entities::technical_space intrinsic_technical_space,
        const boost::shared_ptr<dogen::variability::entities::configuration>& configuration,
        const std::list<dogen::identification::entities::label>& labels,
        const dogen::logical::entities::generability_status generability_status,
        const std::unordered_map<dogen::identification::entities::technical_space, boost::optional<dogen::logical::entities::decoration::element_properties> >& decoration,
        const bool is_nullable,
        const dogen::logical::entities::attribute& value_attribute,
        const bool use_type_aliasing,
        const bool is_immutable,
        const boost::optional<dogen::logical::entities::orm::primitive_properties>& orm_properties);

public:
    using element::accept;

    virtual void accept(const element_visitor& v) const override;
    virtual void accept(element_visitor& v) const override;
    virtual void accept(const element_visitor& v) override;
    virtual void accept(element_visitor& v) override;
public:
    void to_stream(std::ostream& s) const override;

public:
    /**
     * @brief If true, this element can be null (empty).
     */
    /**@{*/
    bool is_nullable() const;
    void is_nullable(const bool v);
    /**@}*/

    /**
     * @brief Attribute that represents the value of the primitive.
     */
    /**@{*/
    const dogen::logical::entities::attribute& value_attribute() const;
    dogen::logical::entities::attribute& value_attribute();
    void value_attribute(const dogen::logical::entities::attribute& v);
    void value_attribute(const dogen::logical::entities::attribute&& v);
    /**@}*/

    /**
     * @brief If set to true, and if the owning technical space supports it, use type aliasing.
     */
    /**@{*/
    bool use_type_aliasing() const;
    void use_type_aliasing(const bool v);
    /**@}*/

    /**
     * @brief If true, do not generate modifiable operations.
     */
    /**@{*/
    bool is_immutable() const;
    void is_immutable(const bool v);
    /**@}*/

    const boost::optional<dogen::logical::entities::orm::primitive_properties>& orm_properties() const;
    boost::optional<dogen::logical::entities::orm::primitive_properties>& orm_properties();
    void orm_properties(const boost::optional<dogen::logical::entities::orm::primitive_properties>& v);
    void orm_properties(const boost::optional<dogen::logical::entities::orm::primitive_properties>&& v);

public:
    bool operator==(const primitive& rhs) const;
    bool operator!=(const primitive& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::logical::entities::element& other) const override;

public:
    void swap(primitive& other) noexcept;
    primitive& operator=(primitive other);

private:
    bool is_nullable_;
    dogen::logical::entities::attribute value_attribute_;
    bool use_type_aliasing_;
    bool is_immutable_;
    boost::optional<dogen::logical::entities::orm::primitive_properties> orm_properties_;
};

}

namespace std {

template<>
inline void swap(
    dogen::logical::entities::structural::primitive& lhs,
    dogen::logical::entities::structural::primitive& rhs) {
    lhs.swap(rhs);
}

}

#endif
