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
#ifndef DOGEN_SML_TYPES_TYPED_ELEMENT_HPP
#define DOGEN_SML_TYPES_TYPED_ELEMENT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <boost/optional.hpp>
#include <iosfwd>
#include <list>
#include "dogen/sml/serialization/typed_element_fwd_ser.hpp"
#include "dogen/sml/types/model_element.hpp"
#include "dogen/sml/types/model_element_visitor.hpp"
#include "dogen/sml/types/property.hpp"
#include "dogen/sml/types/qname.hpp"

namespace dogen {
namespace sml {

/**
 * @brief Represents an element of the model which has properties and operations.
 */
class typed_element : public dogen::sml::model_element {
public:
    typed_element(const typed_element&) = default;

public:
    typed_element();

    virtual ~typed_element() noexcept = 0;

public:
    typed_element(typed_element&& rhs);

public:
    typed_element(
        const dogen::sml::qname& name,
        const std::string& documentation,
        const std::vector<std::pair<std::string, std::string> >& implementation_specific_parameters,
        const dogen::sml::generation_types& generation_type,
        const std::list<dogen::sml::property>& properties,
        const boost::optional<dogen::sml::qname>& parent_name,
        const boost::optional<dogen::sml::qname>& original_parent_name,
        const std::list<dogen::sml::qname>& leaves,
        const unsigned int number_of_type_arguments,
        const bool is_parent,
        const bool is_visitable,
        const bool is_immutable,
        const bool is_versioned,
        const bool is_comparable,
        const bool is_fluent,
        const std::list<dogen::sml::qname>& modeled_concepts);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const typed_element& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, typed_element& v, unsigned int version);

public:
    virtual void to_stream(std::ostream& s) const;

public:
    /**
     * @brief Attributes that belong to this type.
     *
     * Does not include inherited attributes.
     */
    /**@{*/
    const std::list<dogen::sml::property>& properties() const;
    std::list<dogen::sml::property>& properties();
    void properties(const std::list<dogen::sml::property>& v);
    void properties(const std::list<dogen::sml::property>&& v);
    /**@}*/

    /**
     * @brief Qualified name for the type's parent, if one exists.
     */
    /**@{*/
    const boost::optional<dogen::sml::qname>& parent_name() const;
    boost::optional<dogen::sml::qname>& parent_name();
    void parent_name(const boost::optional<dogen::sml::qname>& v);
    void parent_name(const boost::optional<dogen::sml::qname>&& v);
    /**@}*/

    /**
     * @brief Qualified name for the root of the inheritance hierarchy, if the type is part of one.
     */
    /**@{*/
    const boost::optional<dogen::sml::qname>& original_parent_name() const;
    boost::optional<dogen::sml::qname>& original_parent_name();
    void original_parent_name(const boost::optional<dogen::sml::qname>& v);
    void original_parent_name(const boost::optional<dogen::sml::qname>&& v);
    /**@}*/

    /**
     * @brief All concrete types which are indirectly or directly derived from this type.
     */
    /**@{*/
    const std::list<dogen::sml::qname>& leaves() const;
    std::list<dogen::sml::qname>& leaves();
    void leaves(const std::list<dogen::sml::qname>& v);
    void leaves(const std::list<dogen::sml::qname>&& v);
    /**@}*/

    /**
     * @brief If the type is generic, contains the number of type arguments.
     */
    /**@{*/
    unsigned int number_of_type_arguments() const;
    void number_of_type_arguments(const unsigned int v);
    /**@}*/

    /**
     * @brief True if this type is the parent of one or more types, false otherwise.
     */
    /**@{*/
    bool is_parent() const;
    void is_parent(const bool v);
    /**@}*/

    /**
     * @brief If true, the type has an associated visitor type.
     *
     * Only applicable if is_parent is true.
     */
    /**@{*/
    bool is_visitable() const;
    void is_visitable(const bool v);
    /**@}*/

    /**
     * @brief If true, the type's properties can only be used as queries.
     */
    /**@{*/
    bool is_immutable() const;
    void is_immutable(const bool v);
    /**@}*/

    /**
     * @brief If true, the type has a versioned property.
     */
    /**@{*/
    bool is_versioned() const;
    void is_versioned(const bool v);
    /**@}*/

    /**
     * @brief If true, instances of this type can be compared.
     *
     * A type is only comparable if all of its properties have comparable types.
     */
    /**@{*/
    bool is_comparable() const;
    void is_comparable(const bool v);
    /**@}*/

    /**
     * @brief If true, the property setters must return the instance of the type.
     */
    /**@{*/
    bool is_fluent() const;
    void is_fluent(const bool v);
    /**@}*/

    /**
     * @brief All the concepts that this type models, if any.
     */
    /**@{*/
    const std::list<dogen::sml::qname>& modeled_concepts() const;
    std::list<dogen::sml::qname>& modeled_concepts();
    void modeled_concepts(const std::list<dogen::sml::qname>& v);
    void modeled_concepts(const std::list<dogen::sml::qname>&& v);
    /**@}*/

protected:
    bool compare(const typed_element& rhs) const;
public:
    virtual bool equals(const dogen::sml::model_element& other) const = 0;

protected:
    void swap(typed_element& other) noexcept;

private:
    std::list<dogen::sml::property> properties_;
    boost::optional<dogen::sml::qname> parent_name_;
    boost::optional<dogen::sml::qname> original_parent_name_;
    std::list<dogen::sml::qname> leaves_;
    unsigned int number_of_type_arguments_;
    bool is_parent_;
    bool is_visitable_;
    bool is_immutable_;
    bool is_versioned_;
    bool is_comparable_;
    bool is_fluent_;
    std::list<dogen::sml::qname> modeled_concepts_;
};

inline typed_element::~typed_element() noexcept { }

inline bool operator==(const typed_element& lhs, const typed_element& rhs) {
    return lhs.equals(rhs);
}

} }



#endif
