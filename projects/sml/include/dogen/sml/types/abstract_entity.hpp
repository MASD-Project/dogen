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
#ifndef DOGEN_SML_TYPES_ABSTRACT_ENTITY_HPP
#define DOGEN_SML_TYPES_ABSTRACT_ENTITY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <iosfwd>
#include <list>
#include "dogen/sml/serialization/abstract_entity_fwd_ser.hpp"
#include "dogen/sml/types/abstract_object.hpp"
#include "dogen/sml/types/property.hpp"
#include "dogen/sml/types/type_visitor.hpp"

namespace dogen {
namespace sml {

/**
 * @brief Represents a type in the domain which has identity.
 *
 * Identity here is understood in the strong sense, not just of the basic identity
 * provided by the programming language (e.g. unique memory address for the
 * object) but in a domain sense, such that this identity could be perserved
 * regardless of how the object was stored (e.g. persisted in a database).
 *
 * All entities have keys associated with them which are implementations of  the
 * identity function; they key could be a regular domain type such as a value, or it
 * could be a system generated type for this purpose. As with any typed element,
 * keys can be versioned or unversioned, depending on the versioning
 * requirements of the underlying typed element.
 */
class abstract_entity : public dogen::sml::abstract_object {
public:
    abstract_entity(const abstract_entity&) = default;
    abstract_entity(abstract_entity&&) = default;

public:
    abstract_entity();

    virtual ~abstract_entity() noexcept = 0;

public:
    abstract_entity(
        const std::string& documentation,
        const std::vector<std::pair<std::string, std::string> >& implementation_specific_parameters,
        const dogen::sml::qname& name,
        const dogen::sml::generation_types& generation_type,
        const std::list<dogen::sml::property>& properties,
        const boost::optional<dogen::sml::qname>& parent_name,
        const boost::optional<dogen::sml::qname>& original_parent_name,
        const std::list<dogen::sml::qname>& leaves,
        const bool is_parent,
        const unsigned int number_of_type_arguments,
        const bool is_visitable,
        const bool is_immutable,
        const bool is_versioned,
        const bool is_keyed,
        const bool is_comparable,
        const bool is_fluent,
        const std::list<dogen::sml::qname>& modeled_concepts,
        const bool is_aggregate_root,
        const std::list<dogen::sml::property>& identity_operation);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const abstract_entity& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, abstract_entity& v, unsigned int version);

public:
    virtual void to_stream(std::ostream& s) const;

public:
    /**
     * @brief If true, this type is a root of an aggregate.
     */
    /**@{*/
    bool is_aggregate_root() const;
    void is_aggregate_root(const bool v);
    /**@}*/

    /**
     * @brief List of properties that make up the identity operation, uniquely identifying this entity.
     */
    /**@{*/
    const std::list<dogen::sml::property>& identity_operation() const;
    std::list<dogen::sml::property>& identity_operation();
    void identity_operation(const std::list<dogen::sml::property>& v);
    void identity_operation(const std::list<dogen::sml::property>&& v);
    /**@}*/

protected:
    bool compare(const abstract_entity& rhs) const;
public:
    virtual bool equals(const dogen::sml::type& other) const = 0;

protected:
    void swap(abstract_entity& other) noexcept;

private:
    bool is_aggregate_root_;
    std::list<dogen::sml::property> identity_operation_;
};

inline abstract_entity::~abstract_entity() noexcept { }

inline bool operator==(const abstract_entity& lhs, const abstract_entity& rhs) {
    return lhs.equals(rhs);
}

} }



#endif
