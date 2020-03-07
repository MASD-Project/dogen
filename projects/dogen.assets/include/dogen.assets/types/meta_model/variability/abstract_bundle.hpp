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
#ifndef DOGEN_ASSETS_TYPES_META_MODEL_VARIABILITY_ABSTRACT_BUNDLE_HPP
#define DOGEN_ASSETS_TYPES_META_MODEL_VARIABILITY_ABSTRACT_BUNDLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <algorithm>
#include <boost/optional.hpp>
#include "dogen.archetypes/types/location.hpp"
#include "dogen.assets/types/meta_model/name.hpp"
#include "dogen.assets/types/meta_model/element.hpp"
#include "dogen.variability/types/meta_model/binding_point.hpp"

namespace dogen::assets::meta_model::variability {

/**
 * @brief A feature template bundle represents an aggregation of feature templates in a
 * model.
 *
 * The feature templates should be "semantically related", that is, belong to a related
 * topic. A feature template bundle is used by code generation to generate
 * infrastructural code to ease the creation and subsequent processing of features.
 *
 * Generated code comprises of two aspects:
 *
 * @li the registration of the feature template for the dynamic part of the processing;
 * @li the generation of a static configuration class to  represent the feature once
 *  read out from the dynamic configuration - if requested.
 */
class abstract_bundle : public dogen::assets::meta_model::element {
public:
    abstract_bundle(const abstract_bundle&) = default;

public:
    abstract_bundle();

    virtual ~abstract_bundle() noexcept = 0;

public:
    abstract_bundle(abstract_bundle&& rhs);

public:
    abstract_bundle(
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
        const std::list<dogen::assets::meta_model::name>& transparent_associations,
        const std::list<dogen::assets::meta_model::name>& opaque_associations,
        const std::list<dogen::assets::meta_model::name>& associative_container_keys,
        const bool generate_static_configuration,
        const bool requires_manual_default_constructor,
        const dogen::archetypes::location& location,
        const boost::optional<dogen::variability::meta_model::binding_point>& default_binding_point);

public:
    virtual void to_stream(std::ostream& s) const;

public:
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
     * @brief If true, the code generator will output a class to represent the static configuration.
     */
    /**@{*/
    bool generate_static_configuration() const;
    void generate_static_configuration(const bool v);
    /**@}*/

    /**
     * @brief If true, the code generated for this feature template bundle needs a manually
     * generated default constructor.
     */
    /**@{*/
    bool requires_manual_default_constructor() const;
    void requires_manual_default_constructor(const bool v);
    /**@}*/

    /**
     * @brief Archetype location coordinates for the feature template to expand into.
     */
    /**@{*/
    const dogen::archetypes::location& location() const;
    dogen::archetypes::location& location();
    void location(const dogen::archetypes::location& v);
    void location(const dogen::archetypes::location&& v);
    /**@}*/

    /**
     * @brief Default binding point for all feature templates in this bundle.
     *
     * The binding point indicates where the feature will bind when instantiated in a
     * model. If the default binding point is supplied for a bundle, the templates cannot
     * supply individual binding points. Conversely, if not supplied, they must supply
     * their individual binding points.
     */
    /**@{*/
    const boost::optional<dogen::variability::meta_model::binding_point>& default_binding_point() const;
    boost::optional<dogen::variability::meta_model::binding_point>& default_binding_point();
    void default_binding_point(const boost::optional<dogen::variability::meta_model::binding_point>& v);
    void default_binding_point(const boost::optional<dogen::variability::meta_model::binding_point>&& v);
    /**@}*/

protected:
    bool compare(const abstract_bundle& rhs) const;
public:
    virtual bool equals(const dogen::assets::meta_model::element& other) const = 0;

protected:
    void swap(abstract_bundle& other) noexcept;

private:
    std::list<dogen::assets::meta_model::name> transparent_associations_;
    std::list<dogen::assets::meta_model::name> opaque_associations_;
    std::list<dogen::assets::meta_model::name> associative_container_keys_;
    bool generate_static_configuration_;
    bool requires_manual_default_constructor_;
    dogen::archetypes::location location_;
    boost::optional<dogen::variability::meta_model::binding_point> default_binding_point_;
};

inline abstract_bundle::~abstract_bundle() noexcept { }

inline bool operator==(const abstract_bundle& lhs, const abstract_bundle& rhs) {
    return lhs.equals(rhs);
}

}

#endif
