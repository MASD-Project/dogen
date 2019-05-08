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
#ifndef MASD_DOGEN_CODING_TYPES_META_MODEL_STRUCTURAL_BUILTIN_HPP
#define MASD_DOGEN_CODING_TYPES_META_MODEL_STRUCTURAL_BUILTIN_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <algorithm>
#include "masd.dogen.coding/types/meta_model/element.hpp"

namespace masd::dogen::coding::meta_model::structural {

/**
 * @brief Represents a value type that is built-in at the hardware level.
 */
class builtin final : public masd::dogen::coding::meta_model::element {
public:
    builtin(const builtin&) = default;
    builtin(builtin&&) = default;

public:
    builtin();

    virtual ~builtin() noexcept { }

public:
    builtin(
        const masd::dogen::coding::meta_model::name& name,
        const std::string& documentation,
        const masd::dogen::coding::meta_model::origin_types origin_type,
        const std::string& contained_by,
        const bool in_global_module,
        const std::list<masd::dogen::coding::meta_model::static_stereotypes>& static_stereotypes,
        const std::list<std::string>& dynamic_stereotypes,
        const masd::dogen::coding::meta_model::name& meta_name,
        const masd::dogen::coding::meta_model::technical_space intrinsic_technical_space,
        const boost::shared_ptr<masd::dogen::variability::meta_model::configuration>& configuration,
        const bool is_element_extension,
        const std::unordered_map<std::string, masd::dogen::coding::meta_model::artefact_properties>& artefact_properties,
        const std::unordered_map<std::string, masd::dogen::coding::meta_model::local_archetype_location_properties>& archetype_location_properties,
        const boost::optional<masd::dogen::coding::meta_model::decoration::element_properties>& decoration,
        const bool is_default_enumeration_type,
        const bool is_floating_point,
        const bool can_be_enumeration_underlier,
        const bool can_be_primitive_underlier);

public:
    using masd::dogen::coding::meta_model::element::accept;

    virtual void accept(const masd::dogen::coding::meta_model::element_visitor& v) const override;
    virtual void accept(masd::dogen::coding::meta_model::element_visitor& v) const override;
    virtual void accept(const masd::dogen::coding::meta_model::element_visitor& v) override;
    virtual void accept(masd::dogen::coding::meta_model::element_visitor& v) override;
public:
    void to_stream(std::ostream& s) const override;

public:
    /**
     * @brief If true, this built-in is the default type to be used on enumerations.
     */
    /**@{*/
    bool is_default_enumeration_type() const;
    void is_default_enumeration_type(const bool v);
    /**@}*/

    /**
     * @brief If true, this built-in represents a floating point number.
     */
    /**@{*/
    bool is_floating_point() const;
    void is_floating_point(const bool v);
    /**@}*/

    /**
     * @brief If true, this element can be the underlying element of an enumeration.
     */
    /**@{*/
    bool can_be_enumeration_underlier() const;
    void can_be_enumeration_underlier(const bool v);
    /**@}*/

    /**
     * @brief If true, this built-in can be the underlying element of a primitive.
     */
    /**@{*/
    bool can_be_primitive_underlier() const;
    void can_be_primitive_underlier(const bool v);
    /**@}*/

public:
    bool operator==(const builtin& rhs) const;
    bool operator!=(const builtin& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const masd::dogen::coding::meta_model::element& other) const override;

public:
    void swap(builtin& other) noexcept;
    builtin& operator=(builtin other);

private:
    bool is_default_enumeration_type_;
    bool is_floating_point_;
    bool can_be_enumeration_underlier_;
    bool can_be_primitive_underlier_;
};

}

namespace std {

template<>
inline void swap(
    masd::dogen::coding::meta_model::structural::builtin& lhs,
    masd::dogen::coding::meta_model::structural::builtin& rhs) {
    lhs.swap(rhs);
}

}

#endif
