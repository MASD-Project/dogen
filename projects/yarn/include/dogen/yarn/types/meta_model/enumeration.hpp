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
#ifndef DOGEN_YARN_TYPES_META_MODEL_ENUMERATION_HPP
#define DOGEN_YARN_TYPES_META_MODEL_ENUMERATION_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <vector>
#include <algorithm>
#include "dogen/yarn/types/meta_model/name.hpp"
#include "dogen/yarn/types/meta_model/element.hpp"
#include "dogen/yarn/types/meta_model/enumerator.hpp"
#include "dogen/yarn/serialization/meta_model/enumeration_fwd_ser.hpp"

namespace dogen {
namespace yarn {
namespace meta_model {

/**
 * @brief Defines a bounded set of logically related values for a built-in type
 * or a string.
 */
class enumeration final : public dogen::yarn::meta_model::element {
public:
    enumeration(const enumeration&) = default;
    enumeration(enumeration&&) = default;

public:
    enumeration();

    virtual ~enumeration() noexcept { }

public:
    enumeration(
        const dogen::yarn::meta_model::name& name,
        const std::string& documentation,
        const dogen::annotations::annotation& annotation,
        const dogen::yarn::meta_model::origin_types origin_type,
        const boost::optional<dogen::yarn::meta_model::name>& contained_by,
        const bool in_global_module,
        const std::vector<std::string>& stereotypes,
        const dogen::yarn::meta_model::name& meta_name,
        const bool is_element_extension,
        const dogen::formatters::decoration_properties& decoration_properties,
        const std::unordered_map<std::string, dogen::yarn::meta_model::artefact_properties>& artefact_properties,
        const std::unordered_map<std::string, dogen::yarn::meta_model::local_archetype_location_properties>& archetype_location_properties,
        const dogen::yarn::meta_model::name& underlying_element,
        const std::vector<dogen::yarn::meta_model::enumerator>& enumerators,
        const bool use_implementation_defined_underlying_element,
        const bool use_implementation_defined_enumerator_values,
        const bool add_invalid_enumerator);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::yarn::meta_model::enumeration& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::yarn::meta_model::enumeration& v, unsigned int version);

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
    const dogen::yarn::meta_model::name& underlying_element() const;
    dogen::yarn::meta_model::name& underlying_element();
    void underlying_element(const dogen::yarn::meta_model::name& v);
    void underlying_element(const dogen::yarn::meta_model::name&& v);
    /**@}*/

    /**
     * @brief Enumerators for this enumeration.
     */
    /**@{*/
    const std::vector<dogen::yarn::meta_model::enumerator>& enumerators() const;
    std::vector<dogen::yarn::meta_model::enumerator>& enumerators();
    void enumerators(const std::vector<dogen::yarn::meta_model::enumerator>& v);
    void enumerators(const std::vector<dogen::yarn::meta_model::enumerator>&& v);
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
    bool equals(const dogen::yarn::meta_model::element& other) const override;

public:
    void swap(enumeration& other) noexcept;
    enumeration& operator=(enumeration other);

private:
    dogen::yarn::meta_model::name underlying_element_;
    std::vector<dogen::yarn::meta_model::enumerator> enumerators_;
    bool use_implementation_defined_underlying_element_;
    bool use_implementation_defined_enumerator_values_;
    bool add_invalid_enumerator_;
};

} } }

namespace std {

template<>
inline void swap(
    dogen::yarn::meta_model::enumeration& lhs,
    dogen::yarn::meta_model::enumeration& rhs) {
    lhs.swap(rhs);
}

}

#endif
