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
#ifndef MASD_DOGEN_VARIABILITY_TYPES_META_MODEL_FEATURE_HPP
#define MASD_DOGEN_VARIABILITY_TYPES_META_MODEL_FEATURE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <algorithm>
#include <boost/shared_ptr.hpp>
#include "masd.dogen.archetypes/types/location.hpp"
#include "masd.dogen.variability/types/meta_model/element.hpp"
#include "masd.dogen.variability/types/meta_model/value_fwd.hpp"
#include "masd.dogen.variability/types/meta_model/value_type.hpp"
#include "masd.dogen.variability/types/meta_model/binding_type.hpp"

namespace masd::dogen::variability::meta_model {

/**
 * @brief Unit of configuration within Dogen. Defines the domain of values.
 */
class feature final : public masd::dogen::variability::meta_model::element {
public:
    feature(const feature&) = default;
    feature(feature&&) = default;

public:
    feature();

    virtual ~feature() noexcept { }

public:
    feature(
        const masd::dogen::variability::meta_model::name& name,
        const std::string& description,
        const masd::dogen::archetypes::location& location,
        const boost::shared_ptr<masd::dogen::variability::meta_model::value>& default_value,
        const masd::dogen::variability::meta_model::value_type value_type,
        const masd::dogen::variability::meta_model::binding_type binding_type,
        const bool is_partially_matchable);

public:
    void to_stream(std::ostream& s) const override;

public:
    /**
     * @brief The location of this element in archetype space.
     */
    /**@{*/
    const masd::dogen::archetypes::location& location() const;
    masd::dogen::archetypes::location& location();
    void location(const masd::dogen::archetypes::location& v);
    void location(const masd::dogen::archetypes::location&& v);
    /**@}*/

    /**
     * @brief Default value for element, if any.
     */
    /**@{*/
    const boost::shared_ptr<masd::dogen::variability::meta_model::value>& default_value() const;
    boost::shared_ptr<masd::dogen::variability::meta_model::value>& default_value();
    void default_value(const boost::shared_ptr<masd::dogen::variability::meta_model::value>& v);
    void default_value(const boost::shared_ptr<masd::dogen::variability::meta_model::value>&& v);
    /**@}*/

    /**
     * @brief Type of the value for the feature that will result of the template instantiation.
     */
    /**@{*/
    masd::dogen::variability::meta_model::value_type value_type() const;
    void value_type(const masd::dogen::variability::meta_model::value_type v);
    /**@}*/

    /**
     * @brief How the feature binds against other model elements.
     */
    /**@{*/
    masd::dogen::variability::meta_model::binding_type binding_type() const;
    void binding_type(const masd::dogen::variability::meta_model::binding_type v);
    /**@}*/

    /**
     * @brief Feature name can be matched partially.
     */
    /**@{*/
    bool is_partially_matchable() const;
    void is_partially_matchable(const bool v);
    /**@}*/

public:
    bool operator==(const feature& rhs) const;
    bool operator!=(const feature& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const masd::dogen::variability::meta_model::element& other) const override;

public:
    void swap(feature& other) noexcept;
    feature& operator=(feature other);

private:
    masd::dogen::archetypes::location location_;
    boost::shared_ptr<masd::dogen::variability::meta_model::value> default_value_;
    masd::dogen::variability::meta_model::value_type value_type_;
    masd::dogen::variability::meta_model::binding_type binding_type_;
    bool is_partially_matchable_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::variability::meta_model::feature& lhs,
    masd::dogen::variability::meta_model::feature& rhs) {
    lhs.swap(rhs);
}

}

#endif
