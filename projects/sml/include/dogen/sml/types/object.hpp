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
#ifndef DOGEN_SML_TYPES_OBJECT_HPP
#define DOGEN_SML_TYPES_OBJECT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <algorithm>
#include <iosfwd>
#include <list>
#include <unordered_map>
#include "dogen/sml/hash/qname_hash.hpp"
#include "dogen/sml/hash/relationship_types_hash.hpp"
#include "dogen/sml/serialization/object_fwd_ser.hpp"
#include "dogen/sml/types/object_types.hpp"
#include "dogen/sml/types/operation.hpp"
#include "dogen/sml/types/property.hpp"
#include "dogen/sml/types/qname.hpp"
#include "dogen/sml/types/relationship_types.hpp"
#include "dogen/sml/types/type.hpp"

namespace dogen {
namespace sml {

/**
 * @brief Representation of the object notion in the OOP paradigm.
 */
class object final : public dogen::sml::type {
public:
    object(const object&) = default;
    object(object&&) = default;

public:
    object();

    virtual ~object() noexcept { }

public:
    object(
        const std::string& documentation,
        const boost::property_tree::ptree& meta_data,
        const dogen::sml::qname& name,
        const dogen::sml::generation_types& generation_type,
        const dogen::sml::origin_types& origin_type,
        const boost::optional<dogen::sml::qname>& containing_module,
        const std::list<dogen::sml::property>& all_properties,
        const std::list<dogen::sml::property>& local_properties,
        const std::unordered_map<dogen::sml::qname, std::list<dogen::sml::property> >& inherited_properties,
        const std::list<dogen::sml::operation>& operations,
        const bool is_parent,
        const unsigned int number_of_type_arguments,
        const bool is_visitable,
        const bool is_immutable,
        const bool is_versioned,
        const bool is_comparable,
        const bool is_fluent,
        const bool is_child,
        const std::unordered_map<dogen::sml::relationship_types, std::list<dogen::sml::qname> >& relationships,
        const bool is_inheritance_root,
        const dogen::sml::object_types& object_type,
        const bool is_aggregate_root,
        const std::list<dogen::sml::property>& identity);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const object& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, object& v, unsigned int version);

public:
    virtual void accept(const type_visitor& v) const override {
        v.visit(*this);
    }

    virtual void accept(type_visitor& v) const override {
        v.visit(*this);
    }

    virtual void accept(const type_visitor& v) override {
        v.visit(*this);
    }

    virtual void accept(type_visitor& v) override {
        v.visit(*this);
    }

public:
    void to_stream(std::ostream& s) const override;

public:
    /**
     * @brief All the properties associated with this type.
     *
     * This is a union of the following sets:
     *
     * @li the set of all properies obtained via inheritance relationships;
     * @li the set of all properies obtained via modeling of concepts, including any refinements;
     * @li the set of all properies directly associated with the type (local).
     *
     * The first and third sets are cached in this object. The second isn't as we do
     * not have a need for it.
     */
    /**@{*/
    const std::list<dogen::sml::property>& all_properties() const;
    std::list<dogen::sml::property>& all_properties();
    void all_properties(const std::list<dogen::sml::property>& v);
    void all_properties(const std::list<dogen::sml::property>&& v);
    /**@}*/

    /**
     * @brief The set of all properies directly associated with the type.
     */
    /**@{*/
    const std::list<dogen::sml::property>& local_properties() const;
    std::list<dogen::sml::property>& local_properties();
    void local_properties(const std::list<dogen::sml::property>& v);
    void local_properties(const std::list<dogen::sml::property>&& v);
    /**@}*/

    /**
     * @brief The set of all properies obtained via inheritance, by parent name.
     */
    /**@{*/
    const std::unordered_map<dogen::sml::qname, std::list<dogen::sml::property> >& inherited_properties() const;
    std::unordered_map<dogen::sml::qname, std::list<dogen::sml::property> >& inherited_properties();
    void inherited_properties(const std::unordered_map<dogen::sml::qname, std::list<dogen::sml::property> >& v);
    void inherited_properties(const std::unordered_map<dogen::sml::qname, std::list<dogen::sml::property> >&& v);
    /**@}*/

    /**
     * @brief Operations (methods) that can be executed.
     */
    /**@{*/
    const std::list<dogen::sml::operation>& operations() const;
    std::list<dogen::sml::operation>& operations();
    void operations(const std::list<dogen::sml::operation>& v);
    void operations(const std::list<dogen::sml::operation>&& v);
    /**@}*/

    /**
     * @brief True if this class is the parent of one or more classes, false otherwise.
     */
    /**@{*/
    bool is_parent() const;
    void is_parent(const bool v);
    /**@}*/

    /**
     * @brief How many type arguments does this type have
     */
    /**@{*/
    unsigned int number_of_type_arguments() const;
    void number_of_type_arguments(const unsigned int v);
    /**@}*/

    /**
     * @brief If true, a visitor is to be generated for this type and its descendants.
     *
     * Only applicable if is_parent is true.
     */
    /**@{*/
    bool is_visitable() const;
    void is_visitable(const bool v);
    /**@}*/

    /**
     * @brief If true, do not generate setters for the type's properties.
     */
    /**@{*/
    bool is_immutable() const;
    void is_immutable(const bool v);
    /**@}*/

    /**
     * @brief If true, add a version property to the type.
     */
    /**@{*/
    bool is_versioned() const;
    void is_versioned(const bool v);
    /**@}*/

    /**
     * @brief If true, generates the less than operator.
     *
     * A type is only comparable if all of its properties are primitives or strings,
     * or other comparable model types.
     */
    /**@{*/
    bool is_comparable() const;
    void is_comparable(const bool v);
    /**@}*/

    /**
     * @brief If true, generate fluent setters.
     */
    /**@{*/
    bool is_fluent() const;
    void is_fluent(const bool v);
    /**@}*/

    /**
     * @brief If true, the type has at least one parent.
     */
    /**@{*/
    bool is_child() const;
    void is_child(const bool v);
    /**@}*/

    const std::unordered_map<dogen::sml::relationship_types, std::list<dogen::sml::qname> >& relationships() const;
    std::unordered_map<dogen::sml::relationship_types, std::list<dogen::sml::qname> >& relationships();
    void relationships(const std::unordered_map<dogen::sml::relationship_types, std::list<dogen::sml::qname> >& v);
    void relationships(const std::unordered_map<dogen::sml::relationship_types, std::list<dogen::sml::qname> >&& v);

    /**
     * @brief True if this object is at the root of an inheritance graph.
     */
    /**@{*/
    bool is_inheritance_root() const;
    void is_inheritance_root(const bool v);
    /**@}*/

    /**
     * @brief What kind of object is this.
     */
    /**@{*/
    dogen::sml::object_types object_type() const;
    void object_type(const dogen::sml::object_types& v);
    /**@}*/

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
     * @note temporarily moved here until we have property types.
     */
    /**@{*/
    const std::list<dogen::sml::property>& identity() const;
    std::list<dogen::sml::property>& identity();
    void identity(const std::list<dogen::sml::property>& v);
    void identity(const std::list<dogen::sml::property>&& v);
    /**@}*/

public:
    bool operator==(const object& rhs) const;
    bool operator!=(const object& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::sml::type& other) const override;

public:
    void swap(object& other) noexcept;
    object& operator=(object other);

private:
    std::list<dogen::sml::property> all_properties_;
    std::list<dogen::sml::property> local_properties_;
    std::unordered_map<dogen::sml::qname, std::list<dogen::sml::property> > inherited_properties_;
    std::list<dogen::sml::operation> operations_;
    bool is_parent_;
    unsigned int number_of_type_arguments_;
    bool is_visitable_;
    bool is_immutable_;
    bool is_versioned_;
    bool is_comparable_;
    bool is_fluent_;
    bool is_child_;
    std::unordered_map<dogen::sml::relationship_types, std::list<dogen::sml::qname> > relationships_;
    bool is_inheritance_root_;
    dogen::sml::object_types object_type_;
    bool is_aggregate_root_;
    std::list<dogen::sml::property> identity_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::sml::object& lhs,
    dogen::sml::object& rhs) {
    lhs.swap(rhs);
}

}

#endif
