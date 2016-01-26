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
#include "dogen/yarn/types/name.hpp"
#include "dogen/yarn/types/element.hpp"
#include "dogen/yarn/hash/name_hash.hpp"
#include "dogen/yarn/types/property.hpp"
#include "dogen/yarn/types/object_types.hpp"
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
    object(object&&) = default;

public:
    object();

    virtual ~object() noexcept { }

public:
    object(
        const std::string& documentation,
        const dogen::dynamic::object& extensions,
        const dogen::yarn::name& name,
        const dogen::yarn::generation_types generation_type,
        const dogen::yarn::origin_types origin_type,
        const std::string& original_model_name,
        const boost::optional<dogen::yarn::name>& contained_by,
        const bool in_global_module,
        const std::list<dogen::yarn::property>& all_properties,
        const std::list<dogen::yarn::property>& local_properties,
        const std::unordered_map<dogen::yarn::name, std::list<dogen::yarn::property> >& inherited_properties,
        const bool is_immutable,
        const bool is_fluent,
        const bool is_parent,
        const bool is_child,
        const bool is_final,
        const std::list<dogen::yarn::name>& root_parents,
        const std::list<dogen::yarn::name>& parents,
        const std::list<dogen::yarn::name>& leaves,
        const std::list<dogen::yarn::name>& regular_associations,
        const std::list<dogen::yarn::name>& weak_associations,
        const bool is_visitable,
        const bool is_root_parent_visitable,
        const std::list<dogen::yarn::name>& visitable_by,
        const dogen::yarn::object_types object_type,
        const std::list<dogen::yarn::name>& modeled_concepts,
        const std::list<dogen::yarn::name>& associative_container_keys);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const object& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, object& v, unsigned int version);

public:
    virtual void accept(const element_visitor& v) const override {
        v.visit(*this);
    }

    virtual void accept(element_visitor& v) const override {
        v.visit(*this);
    }

    virtual void accept(const element_visitor& v) override {
        v.visit(*this);
    }

    virtual void accept(element_visitor& v) override {
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
    const std::list<dogen::yarn::property>& all_properties() const;
    std::list<dogen::yarn::property>& all_properties();
    void all_properties(const std::list<dogen::yarn::property>& v);
    void all_properties(const std::list<dogen::yarn::property>&& v);
    /**@}*/

    /**
     * @brief The set of all properies directly associated with the type.
     */
    /**@{*/
    const std::list<dogen::yarn::property>& local_properties() const;
    std::list<dogen::yarn::property>& local_properties();
    void local_properties(const std::list<dogen::yarn::property>& v);
    void local_properties(const std::list<dogen::yarn::property>&& v);
    /**@}*/

    /**
     * @brief The set of all properies obtained via inheritance, by parent name.
     */
    /**@{*/
    const std::unordered_map<dogen::yarn::name, std::list<dogen::yarn::property> >& inherited_properties() const;
    std::unordered_map<dogen::yarn::name, std::list<dogen::yarn::property> >& inherited_properties();
    void inherited_properties(const std::unordered_map<dogen::yarn::name, std::list<dogen::yarn::property> >& v);
    void inherited_properties(const std::unordered_map<dogen::yarn::name, std::list<dogen::yarn::property> >&& v);
    /**@}*/

    /**
     * @brief If true, do not generate setters for the element's properties.
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
     * @brief If true, the element cannot be inherited from.
     */
    /**@{*/
    bool is_final() const;
    void is_final(const bool v);
    /**@}*/

    /**
     * @brief Types at the root of the inheritance hierarchy.
     */
    /**@{*/
    const std::list<dogen::yarn::name>& root_parents() const;
    std::list<dogen::yarn::name>& root_parents();
    void root_parents(const std::list<dogen::yarn::name>& v);
    void root_parents(const std::list<dogen::yarn::name>&& v);
    /**@}*/

    /**
     * @brief Elements that are direct parents of this element.
     */
    /**@{*/
    const std::list<dogen::yarn::name>& parents() const;
    std::list<dogen::yarn::name>& parents();
    void parents(const std::list<dogen::yarn::name>& v);
    void parents(const std::list<dogen::yarn::name>&& v);
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
     * @brief Elements that are involved in aggregation or composition relationships.
     */
    /**@{*/
    const std::list<dogen::yarn::name>& regular_associations() const;
    std::list<dogen::yarn::name>& regular_associations();
    void regular_associations(const std::list<dogen::yarn::name>& v);
    void regular_associations(const std::list<dogen::yarn::name>&& v);
    /**@}*/

    /**
     * @brief Elements that are involved in aggregation or composition relationships via
     * indirection.
     *
     * This is used to break cycles where required.
     */
    /**@{*/
    const std::list<dogen::yarn::name>& weak_associations() const;
    std::list<dogen::yarn::name>& weak_associations();
    void weak_associations(const std::list<dogen::yarn::name>& v);
    void weak_associations(const std::list<dogen::yarn::name>&& v);
    /**@}*/

    /**
     * @brief If true, a visitor is to be generated for this element and its descendants.
     *
     * Only applicable if is_parent is true.
     */
    /**@{*/
    bool is_visitable() const;
    void is_visitable(const bool v);
    /**@}*/

    /**
     * @brief Is the root parent of this element a visitable element?
     *
     * Set to false if no parent exists, or if the parent is not visitable.
     */
    /**@{*/
    bool is_root_parent_visitable() const;
    void is_root_parent_visitable(const bool v);
    /**@}*/

    /**
     * @brief Elements that visit current type.
     */
    /**@{*/
    const std::list<dogen::yarn::name>& visitable_by() const;
    std::list<dogen::yarn::name>& visitable_by();
    void visitable_by(const std::list<dogen::yarn::name>& v);
    void visitable_by(const std::list<dogen::yarn::name>&& v);
    /**@}*/

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
    std::list<dogen::yarn::property> all_properties_;
    std::list<dogen::yarn::property> local_properties_;
    std::unordered_map<dogen::yarn::name, std::list<dogen::yarn::property> > inherited_properties_;
    bool is_immutable_;
    bool is_fluent_;
    bool is_parent_;
    bool is_child_;
    bool is_final_;
    std::list<dogen::yarn::name> root_parents_;
    std::list<dogen::yarn::name> parents_;
    std::list<dogen::yarn::name> leaves_;
    std::list<dogen::yarn::name> regular_associations_;
    std::list<dogen::yarn::name> weak_associations_;
    bool is_visitable_;
    bool is_root_parent_visitable_;
    std::list<dogen::yarn::name> visitable_by_;
    dogen::yarn::object_types object_type_;
    std::list<dogen::yarn::name> modeled_concepts_;
    std::list<dogen::yarn::name> associative_container_keys_;
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
