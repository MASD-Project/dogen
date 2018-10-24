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
#ifndef MASD_DOGEN_ANNOTATIONS_TYPES_TYPE_TEMPLATE_HPP
#define MASD_DOGEN_ANNOTATIONS_TYPES_TYPE_TEMPLATE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/shared_ptr.hpp>
#include "masd.dogen.annotations/types/name.hpp"
#include "masd.dogen.annotations/types/value_fwd.hpp"
#include "masd.dogen.annotations/types/scope_types.hpp"
#include "masd.dogen.annotations/types/value_types.hpp"
#include "masd.dogen.annotations/types/template_kinds.hpp"
#include "masd.dogen.annotations/types/archetype_location.hpp"

namespace masd::dogen::annotations {

/**
 * @brief Defines a template that can be used to instantiate types.
 */
class type_template final {
public:
    type_template(const type_template&) = default;
    type_template(type_template&&) = default;
    ~type_template() = default;

public:
    type_template();

public:
    type_template(
        const masd::dogen::annotations::name& name,
        const masd::dogen::annotations::value_types value_type,
        const masd::dogen::annotations::scope_types scope,
        const masd::dogen::annotations::archetype_location& archetype_location,
        const boost::shared_ptr<masd::dogen::annotations::value>& default_value,
        const masd::dogen::annotations::template_kinds kind);

public:
    /**
     * @brief Name of the field to which this definition applies.
     */
    /**@{*/
    const masd::dogen::annotations::name& name() const;
    masd::dogen::annotations::name& name();
    void name(const masd::dogen::annotations::name& v);
    void name(const masd::dogen::annotations::name&& v);
    /**@}*/

    /**
     * @brief Type of the field.
     */
    /**@{*/
    masd::dogen::annotations::value_types value_type() const;
    void value_type(const masd::dogen::annotations::value_types v);
    /**@}*/

    /**
     * @brief Valid scopes where the type may be present.
     */
    /**@{*/
    masd::dogen::annotations::scope_types scope() const;
    void scope(const masd::dogen::annotations::scope_types v);
    /**@}*/

    /**
     * @brief The archetype location for this type.
     */
    /**@{*/
    const masd::dogen::annotations::archetype_location& archetype_location() const;
    masd::dogen::annotations::archetype_location& archetype_location();
    void archetype_location(const masd::dogen::annotations::archetype_location& v);
    void archetype_location(const masd::dogen::annotations::archetype_location&& v);
    /**@}*/

    /**
     * @brief Default value for the field, if any.
     */
    /**@{*/
    const boost::shared_ptr<masd::dogen::annotations::value>& default_value() const;
    boost::shared_ptr<masd::dogen::annotations::value>& default_value();
    void default_value(const boost::shared_ptr<masd::dogen::annotations::value>& v);
    void default_value(const boost::shared_ptr<masd::dogen::annotations::value>&& v);
    /**@}*/

    /**
     * @brief If the type is a template, defines the kind of template.
     */
    /**@{*/
    masd::dogen::annotations::template_kinds kind() const;
    void kind(const masd::dogen::annotations::template_kinds v);
    /**@}*/

public:
    bool operator==(const type_template& rhs) const;
    bool operator!=(const type_template& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(type_template& other) noexcept;
    type_template& operator=(type_template other);

private:
    masd::dogen::annotations::name name_;
    masd::dogen::annotations::value_types value_type_;
    masd::dogen::annotations::scope_types scope_;
    masd::dogen::annotations::archetype_location archetype_location_;
    boost::shared_ptr<masd::dogen::annotations::value> default_value_;
    masd::dogen::annotations::template_kinds kind_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::annotations::type_template& lhs,
    masd::dogen::annotations::type_template& rhs) {
    lhs.swap(rhs);
}

}

#endif
