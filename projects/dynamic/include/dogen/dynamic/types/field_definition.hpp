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
#ifndef DOGEN_DYNAMIC_TYPES_FIELD_DEFINITION_HPP
#define DOGEN_DYNAMIC_TYPES_FIELD_DEFINITION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/shared_ptr.hpp>
#include "dogen/dynamic/serialization/field_definition_fwd_ser.hpp"
#include "dogen/dynamic/types/name.hpp"
#include "dogen/dynamic/types/ownership_hierarchy.hpp"
#include "dogen/dynamic/types/scope_types.hpp"
#include "dogen/dynamic/types/value_fwd.hpp"
#include "dogen/dynamic/types/value_types.hpp"

namespace dogen {
namespace dynamic {

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
        const dogen::dynamic::name& name,
        const dogen::dynamic::value_types& type,
        const dogen::dynamic::scope_types& scope,
        const dogen::dynamic::ownership_hierarchy& ownership_hierarchy,
        const boost::shared_ptr<dogen::dynamic::value>& default_value);

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
    const dogen::dynamic::name& name() const;
    dogen::dynamic::name& name();
    void name(const dogen::dynamic::name& v);
    void name(const dogen::dynamic::name&& v);
    /**@}*/

    /**
     * @brief Type of the field.
     */
    /**@{*/
    dogen::dynamic::value_types type() const;
    void type(const dogen::dynamic::value_types& v);
    /**@}*/

    /**
     * @brief Valid scopes where the field may be present.
     */
    /**@{*/
    dogen::dynamic::scope_types scope() const;
    void scope(const dogen::dynamic::scope_types& v);
    /**@}*/

    /**
     * @brief The ownership hierarchy information for this field.
     */
    /**@{*/
    const dogen::dynamic::ownership_hierarchy& ownership_hierarchy() const;
    dogen::dynamic::ownership_hierarchy& ownership_hierarchy();
    void ownership_hierarchy(const dogen::dynamic::ownership_hierarchy& v);
    void ownership_hierarchy(const dogen::dynamic::ownership_hierarchy&& v);
    /**@}*/

    /**
     * @brief Default value for the field, if any.
     */
    /**@{*/
    const boost::shared_ptr<dogen::dynamic::value>& default_value() const;
    boost::shared_ptr<dogen::dynamic::value>& default_value();
    void default_value(const boost::shared_ptr<dogen::dynamic::value>& v);
    void default_value(const boost::shared_ptr<dogen::dynamic::value>&& v);
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
    dogen::dynamic::name name_;
    dogen::dynamic::value_types type_;
    dogen::dynamic::scope_types scope_;
    dogen::dynamic::ownership_hierarchy ownership_hierarchy_;
    boost::shared_ptr<dogen::dynamic::value> default_value_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::dynamic::field_definition& lhs,
    dogen::dynamic::field_definition& rhs) {
    lhs.swap(rhs);
}

}

#endif
