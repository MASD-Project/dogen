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
#ifndef DOGEN_ASSETS_TYPES_META_MODEL_STRUCTURAL_OBJECT_HPP
#define DOGEN_ASSETS_TYPES_META_MODEL_STRUCTURAL_OBJECT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <algorithm>
#include <unordered_map>
#include <boost/optional.hpp>
#include "dogen.assets/types/meta_model/name.hpp"
#include "dogen.assets/types/meta_model/element.hpp"
#include "dogen.assets/hash/meta_model/name_hash.hpp"
#include "dogen.assets/types/meta_model/attribute.hpp"
#include "dogen.assets/types/meta_model/type_parameters.hpp"
#include "dogen.assets/types/meta_model/orm/object_properties.hpp"

namespace dogen::assets::meta_model::structural {

/**
 * @brief Representation of the class notion in the OOP paradigm.
 *
 * The @e object is equivalent to a meta-class, but we decided against this
 * name because all elements should also have the prefix meta - after all, assets
 * is ameta-model. Since the word class cannot be used in c++ to name types, we
 * decided instead to use the word object.
 */
class object final : public dogen::assets::meta_model::element {
public:
    object(const object&) = default;

public:
    object();

    virtual ~object() noexcept { }

public:
    object(object&& rhs);

public:
    object(
        const dogen::assets::meta_model::name& name,
        const std::string& documentation,
        const dogen::assets::meta_model::origin_types origin_type,
        const std::string& origin_sha1_hash,
        const std::string& origin_element_id,
        const std::string& contained_by,
        const bool in_global_module,
        const std::list<dogen::assets::meta_model::static_stereotypes>& static_stereotypes,
        const std::list<std::string>& dynamic_stereotypes,
        const dogen::assets::meta_model::name& meta_name,
        const dogen::assets::meta_model::technical_space intrinsic_technical_space,
        const boost::shared_ptr<dogen::variability::meta_model::configuration>& configuration,
        const bool is_element_extension,
        const std::unordered_map<std::string, dogen::assets::meta_model::artefact_properties>& artefact_properties,
        const std::unordered_map<std::string, dogen::assets::meta_model::local_archetype_location_properties>& archetype_location_properties,
        const boost::optional<dogen::assets::meta_model::decoration::element_properties>& decoration,
        const std::list<dogen::assets::meta_model::attribute>& all_attributes,
        const std::list<dogen::assets::meta_model::attribute>& local_attributes,
        const std::unordered_map<dogen::assets::meta_model::name, std::list<dogen::assets::meta_model::attribute> >& inherited_attributes,
        const bool is_immutable,
        const bool is_fluent,
        const boost::optional<dogen::assets::meta_model::name>& base_visitor,
        const boost::optional<dogen::assets::meta_model::name>& derived_visitor,
        const bool is_visitation_root,
        const bool is_visitation_leaf,
        const std::list<dogen::assets::meta_model::name>& transparent_associations,
        const std::list<dogen::assets::meta_model::name>& opaque_associations,
        const std::list<dogen::assets::meta_model::name>& associative_container_keys,
        const bool is_parent,
        const bool is_child,
        const bool is_leaf,
        const bool is_final,
        const boost::optional<bool>& is_final_requested,
        const bool is_abstract,
        const bool in_inheritance_relationship,
        const std::list<dogen::assets::meta_model::name>& root_parents,
        const std::list<dogen::assets::meta_model::name>& parents,
        const std::list<dogen::assets::meta_model::name>& leaves,
        const dogen::assets::meta_model::type_parameters& type_parameters,
        const bool is_associative_container,
        const std::list<dogen::assets::meta_model::name>& object_templates,
        const bool provides_opaqueness,
        const bool can_be_primitive_underlier,
        const boost::optional<dogen::assets::meta_model::orm::object_properties>& orm_properties);

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
     * @li the set of all attributes obtained via instantiating object templates,
     *     including their inheritance tree;
     * @li the set of all attributes directly associated with the type (local).
     *
     * The first and third sets are cached in this object. The second isn't as we do
     * not have a need for it.
     */
    /**@{*/
    const std::list<dogen::assets::meta_model::attribute>& all_attributes() const;
    std::list<dogen::assets::meta_model::attribute>& all_attributes();
    void all_attributes(const std::list<dogen::assets::meta_model::attribute>& v);
    void all_attributes(const std::list<dogen::assets::meta_model::attribute>&& v);
    /**@}*/

    /**
     * @brief The set of all attributes directly associated with the type.
     */
    /**@{*/
    const std::list<dogen::assets::meta_model::attribute>& local_attributes() const;
    std::list<dogen::assets::meta_model::attribute>& local_attributes();
    void local_attributes(const std::list<dogen::assets::meta_model::attribute>& v);
    void local_attributes(const std::list<dogen::assets::meta_model::attribute>&& v);
    /**@}*/

    /**
     * @brief The set of all attributes obtained via inheritance, by parent name.
     *
     * Note that we are using name as a key by design (instead of id); it is required for
     * formatting.
     */
    /**@{*/
    const std::unordered_map<dogen::assets::meta_model::name, std::list<dogen::assets::meta_model::attribute> >& inherited_attributes() const;
    std::unordered_map<dogen::assets::meta_model::name, std::list<dogen::assets::meta_model::attribute> >& inherited_attributes();
    void inherited_attributes(const std::unordered_map<dogen::assets::meta_model::name, std::list<dogen::assets::meta_model::attribute> >& v);
    void inherited_attributes(const std::unordered_map<dogen::assets::meta_model::name, std::list<dogen::assets::meta_model::attribute> >&& v);
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
     * @brief Base class of the visitor that visits the current element, if any.
     */
    /**@{*/
    const boost::optional<dogen::assets::meta_model::name>& base_visitor() const;
    boost::optional<dogen::assets::meta_model::name>& base_visitor();
    void base_visitor(const boost::optional<dogen::assets::meta_model::name>& v);
    void base_visitor(const boost::optional<dogen::assets::meta_model::name>&& v);
    /**@}*/

    /**
     * @brief Derived class of the visitor that visits the current element, if any.
     */
    /**@{*/
    const boost::optional<dogen::assets::meta_model::name>& derived_visitor() const;
    boost::optional<dogen::assets::meta_model::name>& derived_visitor();
    void derived_visitor(const boost::optional<dogen::assets::meta_model::name>& v);
    void derived_visitor(const boost::optional<dogen::assets::meta_model::name>&& v);
    /**@}*/

    bool is_visitation_root() const;
    void is_visitation_root(const bool v);

    bool is_visitation_leaf() const;
    void is_visitation_leaf(const bool v);

    /**
     * @brief Elements that are involved in aggregation or composition relationships.
     */
    /**@{*/
    const std::list<dogen::assets::meta_model::name>& transparent_associations() const;
    std::list<dogen::assets::meta_model::name>& transparent_associations();
    void transparent_associations(const std::list<dogen::assets::meta_model::name>& v);
    void transparent_associations(const std::list<dogen::assets::meta_model::name>&& v);
    /**@}*/

    /**
     * @brief Elements that are involved in aggregation or composition relationships via
     * indirection.
     *
     * This is used to break cycles where required.
     */
    /**@{*/
    const std::list<dogen::assets::meta_model::name>& opaque_associations() const;
    std::list<dogen::assets::meta_model::name>& opaque_associations();
    void opaque_associations(const std::list<dogen::assets::meta_model::name>& v);
    void opaque_associations(const std::list<dogen::assets::meta_model::name>&& v);
    /**@}*/

    /**
     * @brief Elements that are keys in an associative container.
     */
    /**@{*/
    const std::list<dogen::assets::meta_model::name>& associative_container_keys() const;
    std::list<dogen::assets::meta_model::name>& associative_container_keys();
    void associative_container_keys(const std::list<dogen::assets::meta_model::name>& v);
    void associative_container_keys(const std::list<dogen::assets::meta_model::name>&& v);
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
     * @brief If present and true/false, user has requested is_final to be true/false.
     *
     * If not present, user did not make any statements with regards to finality.
     */
    /**@{*/
    const boost::optional<bool>& is_final_requested() const;
    boost::optional<bool>& is_final_requested();
    void is_final_requested(const boost::optional<bool>& v);
    void is_final_requested(const boost::optional<bool>&& v);
    /**@}*/

    /**
     * @brief If true, the type is an abstract type.
     */
    /**@{*/
    bool is_abstract() const;
    void is_abstract(const bool v);
    /**@}*/

    /**
     * @brief True if the object is related to at least one other object as a parent or a child.
     */
    /**@{*/
    bool in_inheritance_relationship() const;
    void in_inheritance_relationship(const bool v);
    /**@}*/

    /**
     * @brief Top-most parents at the root of the inheritance hierarchy, if any.
     */
    /**@{*/
    const std::list<dogen::assets::meta_model::name>& root_parents() const;
    std::list<dogen::assets::meta_model::name>& root_parents();
    void root_parents(const std::list<dogen::assets::meta_model::name>& v);
    void root_parents(const std::list<dogen::assets::meta_model::name>&& v);
    /**@}*/

    /**
     * @brief Direct parent of this element, if any.
     */
    /**@{*/
    const std::list<dogen::assets::meta_model::name>& parents() const;
    std::list<dogen::assets::meta_model::name>& parents();
    void parents(const std::list<dogen::assets::meta_model::name>& v);
    void parents(const std::list<dogen::assets::meta_model::name>&& v);
    /**@}*/

    /**
     * @brief Elements that are at the bottom of the inheritance tree.
     */
    /**@{*/
    const std::list<dogen::assets::meta_model::name>& leaves() const;
    std::list<dogen::assets::meta_model::name>& leaves();
    void leaves(const std::list<dogen::assets::meta_model::name>& v);
    void leaves(const std::list<dogen::assets::meta_model::name>&& v);
    /**@}*/

    const dogen::assets::meta_model::type_parameters& type_parameters() const;
    dogen::assets::meta_model::type_parameters& type_parameters();
    void type_parameters(const dogen::assets::meta_model::type_parameters& v);
    void type_parameters(const dogen::assets::meta_model::type_parameters&& v);

    /**
     * @brief Object is an associative container.
     */
    /**@{*/
    bool is_associative_container() const;
    void is_associative_container(const bool v);
    /**@}*/

    /**
     * @brief All object templates associated with this object.
     */
    /**@{*/
    const std::list<dogen::assets::meta_model::name>& object_templates() const;
    std::list<dogen::assets::meta_model::name>& object_templates();
    void object_templates(const std::list<dogen::assets::meta_model::name>& v);
    void object_templates(const std::list<dogen::assets::meta_model::name>&& v);
    /**@}*/

    /**
     * @brief If true, this type provides opaqueness to any type parameters it may have.
     */
    /**@{*/
    bool provides_opaqueness() const;
    void provides_opaqueness(const bool v);
    /**@}*/

    /**
     * @brief If true, this object can be the underlying element of a primitive.
     */
    /**@{*/
    bool can_be_primitive_underlier() const;
    void can_be_primitive_underlier(const bool v);
    /**@}*/

    const boost::optional<dogen::assets::meta_model::orm::object_properties>& orm_properties() const;
    boost::optional<dogen::assets::meta_model::orm::object_properties>& orm_properties();
    void orm_properties(const boost::optional<dogen::assets::meta_model::orm::object_properties>& v);
    void orm_properties(const boost::optional<dogen::assets::meta_model::orm::object_properties>&& v);

public:
    bool operator==(const object& rhs) const;
    bool operator!=(const object& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::assets::meta_model::element& other) const override;

public:
    void swap(object& other) noexcept;
    object& operator=(object other);

private:
    std::list<dogen::assets::meta_model::attribute> all_attributes_;
    std::list<dogen::assets::meta_model::attribute> local_attributes_;
    std::unordered_map<dogen::assets::meta_model::name, std::list<dogen::assets::meta_model::attribute> > inherited_attributes_;
    bool is_immutable_;
    bool is_fluent_;
    boost::optional<dogen::assets::meta_model::name> base_visitor_;
    boost::optional<dogen::assets::meta_model::name> derived_visitor_;
    bool is_visitation_root_;
    bool is_visitation_leaf_;
    std::list<dogen::assets::meta_model::name> transparent_associations_;
    std::list<dogen::assets::meta_model::name> opaque_associations_;
    std::list<dogen::assets::meta_model::name> associative_container_keys_;
    bool is_parent_;
    bool is_child_;
    bool is_leaf_;
    bool is_final_;
    boost::optional<bool> is_final_requested_;
    bool is_abstract_;
    bool in_inheritance_relationship_;
    std::list<dogen::assets::meta_model::name> root_parents_;
    std::list<dogen::assets::meta_model::name> parents_;
    std::list<dogen::assets::meta_model::name> leaves_;
    dogen::assets::meta_model::type_parameters type_parameters_;
    bool is_associative_container_;
    std::list<dogen::assets::meta_model::name> object_templates_;
    bool provides_opaqueness_;
    bool can_be_primitive_underlier_;
    boost::optional<dogen::assets::meta_model::orm::object_properties> orm_properties_;
};

}

namespace std {

template<>
inline void swap(
    dogen::assets::meta_model::structural::object& lhs,
    dogen::assets::meta_model::structural::object& rhs) {
    lhs.swap(rhs);
}

}

#endif
