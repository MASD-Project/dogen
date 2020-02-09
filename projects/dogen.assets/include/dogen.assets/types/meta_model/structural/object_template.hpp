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
#ifndef DOGEN_ASSETS_TYPES_META_MODEL_STRUCTURAL_OBJECT_TEMPLATE_HPP
#define DOGEN_ASSETS_TYPES_META_MODEL_STRUCTURAL_OBJECT_TEMPLATE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <algorithm>
#include <unordered_map>
#include "dogen.assets/types/meta_model/name.hpp"
#include "dogen.assets/types/meta_model/element.hpp"
#include "dogen.assets/hash/meta_model/name_hash.hpp"
#include "dogen.assets/types/meta_model/attribute.hpp"

namespace dogen::assets::meta_model::structural {

/**
 * @brief Represents a structural template for masd objects.
 */
class object_template final : public dogen::assets::meta_model::element {
public:
    object_template(const object_template&) = default;
    object_template(object_template&&) = default;

public:
    object_template();

    virtual ~object_template() noexcept { }

public:
    object_template(
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
        const std::unordered_map<std::string, dogen::assets::meta_model::artefact_properties>& artefact_properties,
        const std::unordered_map<std::string, dogen::assets::meta_model::local_archetype_location_properties>& archetype_location_properties,
        const std::unordered_map<dogen::assets::meta_model::technical_space, boost::optional<dogen::assets::meta_model::decoration::element_properties> >& decoration,
        const std::list<dogen::assets::meta_model::attribute>& all_attributes,
        const std::list<dogen::assets::meta_model::attribute>& local_attributes,
        const std::unordered_map<dogen::assets::meta_model::name, std::list<dogen::assets::meta_model::attribute> >& inherited_attributes,
        const bool is_immutable,
        const bool is_fluent,
        const std::list<dogen::assets::meta_model::name>& parents,
        const bool is_child);

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
     * @brief List of object templates that this object template inherits from, if any.
     */
    /**@{*/
    const std::list<dogen::assets::meta_model::name>& parents() const;
    std::list<dogen::assets::meta_model::name>& parents();
    void parents(const std::list<dogen::assets::meta_model::name>& v);
    void parents(const std::list<dogen::assets::meta_model::name>&& v);
    /**@}*/

    /**
     * @brief If true, the object template has at least one parent.
     */
    /**@{*/
    bool is_child() const;
    void is_child(const bool v);
    /**@}*/

public:
    bool operator==(const object_template& rhs) const;
    bool operator!=(const object_template& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::assets::meta_model::element& other) const override;

public:
    void swap(object_template& other) noexcept;
    object_template& operator=(object_template other);

private:
    std::list<dogen::assets::meta_model::attribute> all_attributes_;
    std::list<dogen::assets::meta_model::attribute> local_attributes_;
    std::unordered_map<dogen::assets::meta_model::name, std::list<dogen::assets::meta_model::attribute> > inherited_attributes_;
    bool is_immutable_;
    bool is_fluent_;
    std::list<dogen::assets::meta_model::name> parents_;
    bool is_child_;
};

}

namespace std {

template<>
inline void swap(
    dogen::assets::meta_model::structural::object_template& lhs,
    dogen::assets::meta_model::structural::object_template& rhs) {
    lhs.swap(rhs);
}

}

#endif
