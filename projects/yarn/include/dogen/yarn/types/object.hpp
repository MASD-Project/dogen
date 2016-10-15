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
#ifndef DOGEN_YARN_TYPES_OBJECT_HPP
#define DOGEN_YARN_TYPES_OBJECT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <algorithm>
#include <unordered_map>
#include <boost/optional.hpp>
#include "dogen/yarn/types/name.hpp"
#include "dogen/yarn/types/element.hpp"
#include "dogen/yarn/hash/name_hash.hpp"
#include "dogen/yarn/types/attribute.hpp"
#include "dogen/yarn/types/object_types.hpp"
#include "dogen/yarn/types/type_parameters.hpp"
#include "dogen/yarn/serialization/object_fwd_ser.hpp"

namespace dogen {
namespace yarn {

/**
 * @brief Representation of the class notion in the OOP paradigm.
 *
 * The yarn @e object is equivalent to a meta-class, but we decided against this
 * name because all elements should also have the prefix meta - after all, yarn is a
 * meta-model. Since the word class cannot be used in c++ to name types, we
 * decided instead to use the word object.
 */
class object final : public dogen::yarn::element {
public:
    object(const object&) = default;

public:
    object();

    virtual ~object() noexcept { }

public:
    object(object&& rhs);

public:
    object(
        const std::string& documentation,
        const dogen::annotations::annotation& annotation,
        const dogen::yarn::name& name,
        const dogen::yarn::origin_types origin_type,
        const boost::optional<dogen::yarn::name>& contained_by,
        const bool in_global_module,
        const std::vector<std::string>& stereotypes,
        const bool is_element_extension,
        const std::list<dogen::yarn::attribute>& all_attributes,
        const std::list<dogen::yarn::attribute>& local_attributes,
        const std::unordered_map<dogen::yarn::name, std::list<dogen::yarn::attribute> >& inherited_attributes,
        const bool is_immutable,
        const bool is_fluent,
        const bool is_parent,
        const bool is_child,
        const bool is_leaf,
        const bool is_final,
        const boost::optional<dogen::yarn::name>& root_parent,
        const boost::optional<dogen::yarn::name>& parent,
        const std::list<dogen::yarn::name>& leaves,
        const bool in_inheritance_relationship,
        const std::list<dogen::yarn::name>& transparent_associations,
        const std::list<dogen::yarn::name>& opaque_associations,
        const boost::optional<dogen::yarn::name>& base_visitor,
        const boost::optional<dogen::yarn::name>& derived_visitor,
        const bool is_visitation_root,
        const bool is_visitation_leaf,
        const dogen::yarn::type_parameters& type_parameters,
        const dogen::yarn::object_types object_type,
        const std::list<dogen::yarn::name>& modeled_concepts,
        const std::list<dogen::yarn::name>& associative_container_keys,
        const bool provides_opaqueness);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::yarn::object& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::yarn::object& v, unsigned int version);

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
     * @brief All attributes associated with this type.
     *
     * This is a union of the following sets:
     *
     * @li the set of all attributes obtained via inheritance relationships;
     * @li the set of all attributes obtained via modeling of concepts, including any refinements;
     * @li the set of all attributes directly associated with the type (local).
     *
     * The first and third sets are cached in this object. The second isn't as we do
     * not have a need for it.
     */
    /**@{*/
    const std::list<dogen::yarn::attribute>& all_attributes() const;
    std::list<dogen::yarn::attribute>& all_attributes();
    void all_attributes(const std::list<dogen::yarn::attribute>& v);
    void all_attributes(const std::list<dogen::yarn::attribute>&& v);
    /**@}*/

    /**
     * @brief The set of all attributes directly associated with the type.
     */
    /**@{*/
    const std::list<dogen::yarn::attribute>& local_attributes() const;
    std::list<dogen::yarn::attribute>& local_attributes();
    void local_attributes(const std::list<dogen::yarn::attribute>& v);
    void local_attributes(const std::list<dogen::yarn::attribute>&& v);
    /**@}*/

    /**
     * @brief The set of all attributes obtained via inheritance, by parent name.
     */
    /**@{*/
    const std::unordered_map<dogen::yarn::name, std::list<dogen::yarn::attribute> >& inherited_attributes() const;
    std::unordered_map<dogen::yarn::name, std::list<dogen::yarn::attribute> >& inherited_attributes();
    void inherited_attributes(const std::unordered_map<dogen::yarn::name, std::list<dogen::yarn::attribute> >& v);
    void inherited_attributes(const std::unordered_map<dogen::yarn::name, std::list<dogen::yarn::attribute> >&& v);
    /**@}*/

    /**
     * @brief If true, do not generate setters for the element's attributes.
     */
    /**@{*/
    bool is_immutable() const;
    void is_immutable(const bool v);
    /**@}*/

    /**
     * @brief If true, generate fluent setters.
     */
    /**@{*/
    bool is_fluent() const;
    void is_fluent(const bool v);
    /**@}*/

    /**
     * @brief True if this element is the parent of one or more elements, false otherwise.
     */
    /**@{*/
    bool is_parent() const;
    void is_parent(const bool v);
    /**@}*/

    /**
     * @brief If true, the element has at least one parent.
     */
    /**@{*/
    bool is_child() const;
    void is_child(const bool v);
    /**@}*/

    /**
     * @brief True if the type has a parent but no children.
     */
    /**@{*/
    bool is_leaf() const;
    void is_leaf(const bool v);
    /**@}*/

    /**
     * @brief If true, the element cannot be inherited from.
     */
    /**@{*/
    bool is_final() const;
    void is_final(const bool v);
    /**@}*/

    /**
     * @brief Top-most parent at the root of the inheritance hierarchy, if any.
     */
    /**@{*/
    const boost::optional<dogen::yarn::name>& root_parent() const;
    boost::optional<dogen::yarn::name>& root_parent();
    void root_parent(const boost::optional<dogen::yarn::name>& v);
    void root_parent(const boost::optional<dogen::yarn::name>&& v);
    /**@}*/

    /**
     * @brief Direct parent of this element, if any.
     */
    /**@{*/
    const boost::optional<dogen::yarn::name>& parent() const;
    boost::optional<dogen::yarn::name>& parent();
    void parent(const boost::optional<dogen::yarn::name>& v);
    void parent(const boost::optional<dogen::yarn::name>&& v);
    /**@}*/

    /**
     * @brief Elements that are at the bottom of the inheritance tree.
     */
    /**@{*/
    const std::list<dogen::yarn::name>& leaves() const;
    std::list<dogen::yarn::name>& leaves();
    void leaves(const std::list<dogen::yarn::name>& v);
    void leaves(const std::list<dogen::yarn::name>&& v);
    /**@}*/

    /**
     * @brief True if the object is related to at least one other object as a parent or a child.
     */
    /**@{*/
    bool in_inheritance_relationship() const;
    void in_inheritance_relationship(const bool v);
    /**@}*/

    /**
     * @brief Elements that are involved in aggregation or composition relationships.
     */
    /**@{*/
    const std::list<dogen::yarn::name>& transparent_associations() const;
    std::list<dogen::yarn::name>& transparent_associations();
    void transparent_associations(const std::list<dogen::yarn::name>& v);
    void transparent_associations(const std::list<dogen::yarn::name>&& v);
    /**@}*/

    /**
     * @brief Elements that are involved in aggregation or composition relationships via
     * indirection.
     *
     * This is used to break cycles where required.
     */
    /**@{*/
    const std::list<dogen::yarn::name>& opaque_associations() const;
    std::list<dogen::yarn::name>& opaque_associations();
    void opaque_associations(const std::list<dogen::yarn::name>& v);
    void opaque_associations(const std::list<dogen::yarn::name>&& v);
    /**@}*/

    /**
     * @brief Base class of the visitor that visits the current element, if any.
     */
    /**@{*/
    const boost::optional<dogen::yarn::name>& base_visitor() const;
    boost::optional<dogen::yarn::name>& base_visitor();
    void base_visitor(const boost::optional<dogen::yarn::name>& v);
    void base_visitor(const boost::optional<dogen::yarn::name>&& v);
    /**@}*/

    /**
     * @brief Derived class of the visitor that visits the current element, if any.
     */
    /**@{*/
    const boost::optional<dogen::yarn::name>& derived_visitor() const;
    boost::optional<dogen::yarn::name>& derived_visitor();
    void derived_visitor(const boost::optional<dogen::yarn::name>& v);
    void derived_visitor(const boost::optional<dogen::yarn::name>&& v);
    /**@}*/

    bool is_visitation_root() const;
    void is_visitation_root(const bool v);

    bool is_visitation_leaf() const;
    void is_visitation_leaf(const bool v);

    const dogen::yarn::type_parameters& type_parameters() const;
    dogen::yarn::type_parameters& type_parameters();
    void type_parameters(const dogen::yarn::type_parameters& v);
    void type_parameters(const dogen::yarn::type_parameters&& v);

    /**
     * @brief What kind of object is this.
     */
    /**@{*/
    dogen::yarn::object_types object_type() const;
    void object_type(const dogen::yarn::object_types v);
    /**@}*/

    /**
     * @brief Concepts modeled by this object.
     */
    /**@{*/
    const std::list<dogen::yarn::name>& modeled_concepts() const;
    std::list<dogen::yarn::name>& modeled_concepts();
    void modeled_concepts(const std::list<dogen::yarn::name>& v);
    void modeled_concepts(const std::list<dogen::yarn::name>&& v);
    /**@}*/

    /**
     * @brief Elements that are keys in an associative container.
     */
    /**@{*/
    const std::list<dogen::yarn::name>& associative_container_keys() const;
    std::list<dogen::yarn::name>& associative_container_keys();
    void associative_container_keys(const std::list<dogen::yarn::name>& v);
    void associative_container_keys(const std::list<dogen::yarn::name>&& v);
    /**@}*/

    /**
     * @brief If true, this type provides opaqueness to any type parameters it may have.
     */
    /**@{*/
    bool provides_opaqueness() const;
    void provides_opaqueness(const bool v);
    /**@}*/

public:
    bool operator==(const object& rhs) const;
    bool operator!=(const object& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::yarn::element& other) const override;

public:
    void swap(object& other) noexcept;
    object& operator=(object other);

private:
    std::list<dogen::yarn::attribute> all_attributes_;
    std::list<dogen::yarn::attribute> local_attributes_;
    std::unordered_map<dogen::yarn::name, std::list<dogen::yarn::attribute> > inherited_attributes_;
    bool is_immutable_;
    bool is_fluent_;
    bool is_parent_;
    bool is_child_;
    bool is_leaf_;
    bool is_final_;
    boost::optional<dogen::yarn::name> root_parent_;
    boost::optional<dogen::yarn::name> parent_;
    std::list<dogen::yarn::name> leaves_;
    bool in_inheritance_relationship_;
    std::list<dogen::yarn::name> transparent_associations_;
    std::list<dogen::yarn::name> opaque_associations_;
    boost::optional<dogen::yarn::name> base_visitor_;
    boost::optional<dogen::yarn::name> derived_visitor_;
    bool is_visitation_root_;
    bool is_visitation_leaf_;
    dogen::yarn::type_parameters type_parameters_;
    dogen::yarn::object_types object_type_;
    std::list<dogen::yarn::name> modeled_concepts_;
    std::list<dogen::yarn::name> associative_container_keys_;
    bool provides_opaqueness_;
};

} }

namespace std {

template<>
inline void swap(
    dogen::yarn::object& lhs,
    dogen::yarn::object& rhs) {
    lhs.swap(rhs);
}

}

#endif
