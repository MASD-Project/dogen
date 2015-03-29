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
#ifndef DOGEN_DYNAMIC_SCHEMA_TYPES_FIELD_DEFINITION_HPP
#define DOGEN_DYNAMIC_SCHEMA_TYPES_FIELD_DEFINITION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/shared_ptr.hpp>
#include "dogen/dynamic/schema/serialization/field_definition_fwd_ser.hpp"
#include "dogen/dynamic/schema/types/field_definition_types.hpp"
#include "dogen/dynamic/schema/types/name.hpp"
#include "dogen/dynamic/schema/types/ownership_hierarchy.hpp"
#include "dogen/dynamic/schema/types/scope_types.hpp"
#include "dogen/dynamic/schema/types/value_fwd.hpp"
#include "dogen/dynamic/schema/types/value_types.hpp"

namespace dogen {
namespace dynamic {
namespace schema {

/**
 * @brief Defines the properties of the field used for validation.
 */
class field_definition final {
public:
    field_definition(const field_definition&) = default;
    field_definition(field_definition&&) = default;
    ~field_definition() = default;

public:
    field_definition();

public:
    field_definition(
        const dogen::dynamic::schema::name& name,
        const dogen::dynamic::schema::value_types& value_type,
        const dogen::dynamic::schema::scope_types& scope,
        const dogen::dynamic::schema::ownership_hierarchy& ownership_hierarchy,
        const boost::shared_ptr<dogen::dynamic::schema::value>& default_value,
        const dogen::dynamic::schema::field_definition_types& definition_type);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const field_definition& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, field_definition& v, unsigned int version);

public:
    /**
     * @brief Name of the field to which this definition applies.
     */
    /**@{*/
    const dogen::dynamic::schema::name& name() const;
    dogen::dynamic::schema::name& name();
    void name(const dogen::dynamic::schema::name& v);
    void name(const dogen::dynamic::schema::name&& v);
    /**@}*/

    /**
     * @brief Type of the field.
     */
    /**@{*/
    dogen::dynamic::schema::value_types value_type() const;
    void value_type(const dogen::dynamic::schema::value_types& v);
    /**@}*/

    /**
     * @brief Valid scopes where the field may be present.
     */
    /**@{*/
    dogen::dynamic::schema::scope_types scope() const;
    void scope(const dogen::dynamic::schema::scope_types& v);
    /**@}*/

    /**
     * @brief The ownership hierarchy information for this field.
     */
    /**@{*/
    const dogen::dynamic::schema::ownership_hierarchy& ownership_hierarchy() const;
    dogen::dynamic::schema::ownership_hierarchy& ownership_hierarchy();
    void ownership_hierarchy(const dogen::dynamic::schema::ownership_hierarchy& v);
    void ownership_hierarchy(const dogen::dynamic::schema::ownership_hierarchy&& v);
    /**@}*/

    /**
     * @brief Default value for the field, if any.
     */
    /**@{*/
    const boost::shared_ptr<dogen::dynamic::schema::value>& default_value() const;
    boost::shared_ptr<dogen::dynamic::schema::value>& default_value();
    void default_value(const boost::shared_ptr<dogen::dynamic::schema::value>& v);
    void default_value(const boost::shared_ptr<dogen::dynamic::schema::value>&& v);
    /**@}*/

    /**
     * @brief Type of the field definition.
     */
    /**@{*/
    dogen::dynamic::schema::field_definition_types definition_type() const;
    void definition_type(const dogen::dynamic::schema::field_definition_types& v);
    /**@}*/

public:
    bool operator==(const field_definition& rhs) const;
    bool operator!=(const field_definition& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(field_definition& other) noexcept;
    field_definition& operator=(field_definition other);

private:
    dogen::dynamic::schema::name name_;
    dogen::dynamic::schema::value_types value_type_;
    dogen::dynamic::schema::scope_types scope_;
    dogen::dynamic::schema::ownership_hierarchy ownership_hierarchy_;
    boost::shared_ptr<dogen::dynamic::schema::value> default_value_;
    dogen::dynamic::schema::field_definition_types definition_type_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::dynamic::schema::field_definition& lhs,
    dogen::dynamic::schema::field_definition& rhs) {
    lhs.swap(rhs);
}

}

#endif
