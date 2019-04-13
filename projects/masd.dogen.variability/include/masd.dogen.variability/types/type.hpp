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
#ifndef MASD_DOGEN_VARIABILITY_TYPES_TYPE_HPP
#define MASD_DOGEN_VARIABILITY_TYPES_TYPE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/shared_ptr.hpp>
#include "masd.dogen.variability/types/name.hpp"
#include "masd.dogen.archetypes/types/location.hpp"
#include "masd.dogen.variability/types/value_fwd.hpp"
#include "masd.dogen.variability/types/scope_types.hpp"
#include "masd.dogen.variability/types/value_types.hpp"

namespace masd::dogen::variability {

/**
 * @brief Defines the domain of values.
 */
class type final {
public:
    type(const type&) = default;
    type(type&&) = default;
    ~type() = default;

public:
    type();

public:
    type(
        const masd::dogen::variability::name& name,
        const masd::dogen::variability::value_types value_type,
        const masd::dogen::variability::scope_types scope,
        const masd::dogen::archetypes::location& archetype_location,
        const boost::shared_ptr<masd::dogen::variability::value>& default_value,
        const bool is_partially_matchable);

public:
    /**
     * @brief Name of the field to which this definition applies.
     */
    /**@{*/
    const masd::dogen::variability::name& name() const;
    masd::dogen::variability::name& name();
    void name(const masd::dogen::variability::name& v);
    void name(const masd::dogen::variability::name&& v);
    /**@}*/

    /**
     * @brief Type of the field.
     */
    /**@{*/
    masd::dogen::variability::value_types value_type() const;
    void value_type(const masd::dogen::variability::value_types v);
    /**@}*/

    /**
     * @brief Valid scopes where the type may be present.
     */
    /**@{*/
    masd::dogen::variability::scope_types scope() const;
    void scope(const masd::dogen::variability::scope_types v);
    /**@}*/

    /**
     * @brief The archetype location for this type.
     */
    /**@{*/
    const masd::dogen::archetypes::location& archetype_location() const;
    masd::dogen::archetypes::location& archetype_location();
    void archetype_location(const masd::dogen::archetypes::location& v);
    void archetype_location(const masd::dogen::archetypes::location&& v);
    /**@}*/

    /**
     * @brief Default value for the field, if any.
     */
    /**@{*/
    const boost::shared_ptr<masd::dogen::variability::value>& default_value() const;
    boost::shared_ptr<masd::dogen::variability::value>& default_value();
    void default_value(const boost::shared_ptr<masd::dogen::variability::value>& v);
    void default_value(const boost::shared_ptr<masd::dogen::variability::value>&& v);
    /**@}*/

    bool is_partially_matchable() const;
    void is_partially_matchable(const bool v);

public:
    bool operator==(const type& rhs) const;
    bool operator!=(const type& rhs) const {
        return !this->operator==(rhs);
    }

public:
    void swap(type& other) noexcept;
    type& operator=(type other);

private:
    masd::dogen::variability::name name_;
    masd::dogen::variability::value_types value_type_;
    masd::dogen::variability::scope_types scope_;
    masd::dogen::archetypes::location archetype_location_;
    boost::shared_ptr<masd::dogen::variability::value> default_value_;
    bool is_partially_matchable_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::variability::type& lhs,
    masd::dogen::variability::type& rhs) {
    lhs.swap(rhs);
}

}

#endif
