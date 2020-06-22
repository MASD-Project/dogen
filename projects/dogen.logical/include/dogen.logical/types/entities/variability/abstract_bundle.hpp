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
#ifndef DOGEN_LOGICAL_TYPES_ENTITIES_VARIABILITY_ABSTRACT_BUNDLE_HPP
#define DOGEN_LOGICAL_TYPES_ENTITIES_VARIABILITY_ABSTRACT_BUNDLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <string>
#include <algorithm>
#include <boost/optional.hpp>
#include "dogen.logical/types/entities/name.hpp"
#include "dogen.logical/types/entities/element.hpp"
#include "dogen.variability/types/entities/binding_point.hpp"

namespace dogen::logical::entities::variability {

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
class abstract_bundle : public dogen::logical::entities::element {
public:
    abstract_bundle(const abstract_bundle&) = default;

public:
    abstract_bundle();

    virtual ~abstract_bundle() noexcept = 0;

public:
    abstract_bundle(abstract_bundle&& rhs);

public:
    abstract_bundle(
        const dogen::logical::entities::name& name,
        const std::string& documentation,
        const dogen::logical::entities::origin_types origin_type,
        const std::string& origin_sha1_hash,
        const std::string& contained_by,
        const bool in_global_module,
        const std::list<dogen::logical::entities::static_stereotypes>& static_stereotypes,
        const std::list<std::string>& dynamic_stereotypes,
        const dogen::logical::entities::name& meta_name,
        const dogen::logical::entities::technical_space intrinsic_technical_space,
        const boost::shared_ptr<dogen::variability::entities::configuration>& configuration,
        const std::list<dogen::logical::entities::label>& labels,
        const std::unordered_map<std::string, dogen::logical::entities::artefact_properties>& artefact_properties,
        const std::unordered_map<std::string, dogen::logical::entities::enablement_properties>& enablement_properties,
        const std::unordered_map<dogen::logical::entities::technical_space, boost::optional<dogen::logical::entities::decoration::element_properties> >& decoration,
        const std::list<dogen::logical::entities::name>& transparent_associations,
        const std::list<dogen::logical::entities::name>& opaque_associations,
        const std::list<dogen::logical::entities::name>& associative_container_keys,
        const std::string& key_prefix,
        const bool generate_registration,
        const bool generate_static_configuration,
        const bool requires_manual_default_constructor,
        const boost::optional<dogen::variability::entities::binding_point>& default_binding_point);

public:
    virtual void to_stream(std::ostream& s) const;

public:
    /**
     * @brief Elements that are involved in aggregation or composition relationships.
     */
    /**@{*/
    const std::list<dogen::logical::entities::name>& transparent_associations() const;
    std::list<dogen::logical::entities::name>& transparent_associations();
    void transparent_associations(const std::list<dogen::logical::entities::name>& v);
    void transparent_associations(const std::list<dogen::logical::entities::name>&& v);
    /**@}*/

    /**
     * @brief Elements that are involved in aggregation or composition relationships via
     * indirection.
     *
     * This is used to break cycles where required.
     */
    /**@{*/
    const std::list<dogen::logical::entities::name>& opaque_associations() const;
    std::list<dogen::logical::entities::name>& opaque_associations();
    void opaque_associations(const std::list<dogen::logical::entities::name>& v);
    void opaque_associations(const std::list<dogen::logical::entities::name>&& v);
    /**@}*/

    /**
     * @brief Elements that are keys in an associative container.
     */
    /**@{*/
    const std::list<dogen::logical::entities::name>& associative_container_keys() const;
    std::list<dogen::logical::entities::name>& associative_container_keys();
    void associative_container_keys(const std::list<dogen::logical::entities::name>& v);
    void associative_container_keys(const std::list<dogen::logical::entities::name>&& v);
    /**@}*/

    /**
     * @brief Prefix to use when composing the key, if any.
     */
    /**@{*/
    const std::string& key_prefix() const;
    std::string& key_prefix();
    void key_prefix(const std::string& v);
    void key_prefix(const std::string&& v);
    /**@}*/

    /**
     * @brief If true, code will be generated to perform the registration of the features.
     */
    /**@{*/
    bool generate_registration() const;
    void generate_registration(const bool v);
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
     * @brief Default binding point for all feature templates in this bundle.
     *
     * The binding point indicates where the feature will bind when instantiated in a
     * model. If the default binding point is supplied for a bundle, the templates cannot
     * supply individual binding points. Conversely, if not supplied, they must supply
     * their individual binding points.
     */
    /**@{*/
    const boost::optional<dogen::variability::entities::binding_point>& default_binding_point() const;
    boost::optional<dogen::variability::entities::binding_point>& default_binding_point();
    void default_binding_point(const boost::optional<dogen::variability::entities::binding_point>& v);
    void default_binding_point(const boost::optional<dogen::variability::entities::binding_point>&& v);
    /**@}*/

protected:
    bool compare(const abstract_bundle& rhs) const;
public:
    virtual bool equals(const dogen::logical::entities::element& other) const = 0;

protected:
    void swap(abstract_bundle& other) noexcept;

private:
    std::list<dogen::logical::entities::name> transparent_associations_;
    std::list<dogen::logical::entities::name> opaque_associations_;
    std::list<dogen::logical::entities::name> associative_container_keys_;
    std::string key_prefix_;
    bool generate_registration_;
    bool generate_static_configuration_;
    bool requires_manual_default_constructor_;
    boost::optional<dogen::variability::entities::binding_point> default_binding_point_;
};

inline abstract_bundle::~abstract_bundle() noexcept { }

inline bool operator==(const abstract_bundle& lhs, const abstract_bundle& rhs) {
    return lhs.equals(rhs);
}

}

#endif
