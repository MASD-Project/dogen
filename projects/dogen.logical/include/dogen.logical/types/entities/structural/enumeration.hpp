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
#ifndef DOGEN_LOGICAL_TYPES_ENTITIES_STRUCTURAL_ENUMERATION_HPP
#define DOGEN_LOGICAL_TYPES_ENTITIES_STRUCTURAL_ENUMERATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <algorithm>
#include "dogen.logical/types/entities/name.hpp"
#include "dogen.logical/types/entities/element.hpp"
#include "dogen.logical/types/entities/structural/enumerator.hpp"

namespace dogen::logical::entities::structural {

/**
 * @brief Defines a bounded set of logically related values for a built-in type
 * or a string.
 */
class enumeration final : public dogen::logical::entities::element {
public:
    enumeration(const enumeration&) = default;
    enumeration(enumeration&&) = default;

public:
    enumeration();

    virtual ~enumeration() noexcept { }

public:
    enumeration(
        const dogen::logical::entities::name& name,
        const std::string& documentation,
        const dogen::logical::entities::origin_types origin_type,
        const std::string& origin_sha1_hash,
        const std::string& contained_by,
        const bool in_global_module,
        const std::list<dogen::logical::entities::static_stereotypes>& static_stereotypes,
        const std::list<dogen::identification::entities::stereotype>& dynamic_stereotypes,
        const dogen::logical::entities::name& meta_name,
        const dogen::logical::entities::technical_space intrinsic_technical_space,
        const boost::shared_ptr<dogen::variability::entities::configuration>& configuration,
        const std::list<dogen::logical::entities::label>& labels,
        const dogen::logical::entities::generability_status generability_status,
        const std::unordered_map<dogen::logical::entities::technical_space, boost::optional<dogen::logical::entities::decoration::element_properties> >& decoration,
        const dogen::logical::entities::name& underlying_element,
        const std::list<dogen::logical::entities::structural::enumerator>& enumerators,
        const bool use_implementation_defined_underlying_element,
        const bool use_implementation_defined_enumerator_values,
        const bool add_invalid_enumerator);

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
     * @brief Underlying element of each instance of the enumeration.
     */
    /**@{*/
    const dogen::logical::entities::name& underlying_element() const;
    dogen::logical::entities::name& underlying_element();
    void underlying_element(const dogen::logical::entities::name& v);
    void underlying_element(const dogen::logical::entities::name&& v);
    /**@}*/

    /**
     * @brief Enumerators for this enumeration.
     */
    /**@{*/
    const std::list<dogen::logical::entities::structural::enumerator>& enumerators() const;
    std::list<dogen::logical::entities::structural::enumerator>& enumerators();
    void enumerators(const std::list<dogen::logical::entities::structural::enumerator>& v);
    void enumerators(const std::list<dogen::logical::entities::structural::enumerator>&& v);
    /**@}*/

    /**
     * @brief If true, we will use the implementation specific default enumeration type.
     */
    /**@{*/
    bool use_implementation_defined_underlying_element() const;
    void use_implementation_defined_underlying_element(const bool v);
    /**@}*/

    /**
     * @brief If true, we will rely on compiler generated enumeration values.
     */
    /**@{*/
    bool use_implementation_defined_enumerator_values() const;
    void use_implementation_defined_enumerator_values(const bool v);
    /**@}*/

    /**
     * @brief If true, an enumerator for "invalid" will be added.
     */
    /**@{*/
    bool add_invalid_enumerator() const;
    void add_invalid_enumerator(const bool v);
    /**@}*/

public:
    bool operator==(const enumeration& rhs) const;
    bool operator!=(const enumeration& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::logical::entities::element& other) const override;

public:
    void swap(enumeration& other) noexcept;
    enumeration& operator=(enumeration other);

private:
    dogen::logical::entities::name underlying_element_;
    std::list<dogen::logical::entities::structural::enumerator> enumerators_;
    bool use_implementation_defined_underlying_element_;
    bool use_implementation_defined_enumerator_values_;
    bool add_invalid_enumerator_;
};

}

namespace std {

template<>
inline void swap(
    dogen::logical::entities::structural::enumeration& lhs,
    dogen::logical::entities::structural::enumeration& rhs) {
    lhs.swap(rhs);
}

}

#endif
