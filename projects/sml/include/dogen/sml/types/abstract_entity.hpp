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

namespace dogen {
namespace sml {

/**
 * @brief Represents a type in the domain which has identity.
 *
 * Identity here is understood in a stronger sense than just the basic
 * OOP guarantee of identity - say, by providing a unique memory address
 * for an object. We mean identity in a @b domain sense, such that it
 * could be preserved regardless of the object life-time in memory
 * (e.g. it could be persisted in a database or to file).
 *
 * Identity emerges by deep domain analysis and is then expressed in the
 * model by manually defining of a set of properties which uniquely
 * identify an entity. These properties form part of the state of the
 * entity. The identity function (or operation) can be understood as a
 * conceptual device that maps the entity's identity to the entity.
 *
 * As with any typed element, entities can be versioned or unversioned,
 * depending on the requirements of the underlying typed element.
 *
 * @note Identity properties can only be supplied once when in an
 * inheritance tree. This means that an identity can be obtained by
 * either refining a concept that provides an identity, or by inheriting
 * from a parent which provides an identity but not both; and when this
 * occurs the type can no longer provide an identity itself. Across an
 * inheritance graph, the identity operation can only be defined once.
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
        const std::unordered_map<std::string, std::string>& simple_tags,
        const std::unordered_map<std::string, std::list<std::string> >& complex_tags,
        const dogen::sml::qname& name,
        const dogen::sml::generation_types& generation_type,
        const dogen::sml::origin_types& origin_type,
        const std::list<dogen::sml::property>& properties,
        const std::list<dogen::sml::operation>& operations,
        const boost::optional<dogen::sml::qname>& parent_name,
        const boost::optional<dogen::sml::qname>& original_parent_name,
        const std::list<dogen::sml::qname>& leaves,
        const bool is_parent,
        const unsigned int number_of_type_arguments,
        const bool is_visitable,
        const bool is_immutable,
        const bool is_versioned,
        const bool is_comparable,
        const bool is_fluent,
        const std::list<dogen::sml::qname>& modeled_concepts,
        const bool is_aggregate_root,
        const std::list<dogen::sml::property>& identity);

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
     * @brief List of properties that make up the identity operation.
     *
     * @note These properties are copied from the original source such as
     * a concept, parent or the main properties container.
     */
    /**@{*/
    const std::list<dogen::sml::property>& identity() const;
    std::list<dogen::sml::property>& identity();
    void identity(const std::list<dogen::sml::property>& v);
    void identity(const std::list<dogen::sml::property>&& v);
    /**@}*/

protected:
    bool compare(const abstract_entity& rhs) const;
public:
    virtual bool equals(const dogen::sml::type& other) const = 0;

protected:
    void swap(abstract_entity& other) noexcept;

private:
    bool is_aggregate_root_;
    std::list<dogen::sml::property> identity_;
};

inline abstract_entity::~abstract_entity() noexcept { }

inline bool operator==(const abstract_entity& lhs, const abstract_entity& rhs) {
    return lhs.equals(rhs);
}

} }



#endif
