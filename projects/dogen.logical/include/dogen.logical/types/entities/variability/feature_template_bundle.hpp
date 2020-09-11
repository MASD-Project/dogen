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
#ifndef DOGEN_LOGICAL_TYPES_ENTITIES_VARIABILITY_FEATURE_TEMPLATE_BUNDLE_HPP
#define DOGEN_LOGICAL_TYPES_ENTITIES_VARIABILITY_FEATURE_TEMPLATE_BUNDLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <string>
#include <algorithm>
#include "dogen.logical/types/entities/variability/abstract_bundle.hpp"
#include "dogen.logical/types/entities/variability/feature_template.hpp"

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
 *  read out from the dynamic configuration.
 *
 * Both of these aspects are optional, but at least one must be chosen.
 */
class feature_template_bundle final : public dogen::logical::entities::variability::abstract_bundle {
public:
    feature_template_bundle() = default;
    feature_template_bundle(const feature_template_bundle&) = default;
    feature_template_bundle(feature_template_bundle&&) = default;

    virtual ~feature_template_bundle() noexcept { }

public:
    feature_template_bundle(
        const dogen::identification::entities::logical_name& name,
        const std::string& documentation,
        const dogen::identification::entities::codec_provenance& provenance,
        const dogen::identification::entities::logical_id& contained_by,
        const bool in_global_module,
        const dogen::logical::entities::stereotypes& stereotypes,
        const dogen::identification::entities::logical_meta_name& meta_name,
        const dogen::identification::entities::technical_space intrinsic_technical_space,
        const boost::shared_ptr<dogen::variability::entities::configuration>& configuration,
        const std::list<dogen::identification::entities::label>& labels,
        const dogen::logical::entities::generability_status generability_status,
        const std::unordered_map<dogen::identification::entities::technical_space, boost::optional<dogen::logical::entities::decoration::element_properties> >& decoration,
        const std::list<dogen::identification::entities::logical_name>& transparent_associations,
        const std::list<dogen::identification::entities::logical_name>& opaque_associations,
        const std::list<dogen::identification::entities::logical_name>& associative_container_keys,
        const std::string& key_prefix,
        const bool generate_registration,
        const bool generate_static_configuration,
        const bool requires_manual_default_constructor,
        const boost::optional<dogen::variability::entities::binding_point>& default_binding_point,
        const std::list<dogen::logical::entities::variability::feature_template>& feature_templates,
        const std::string& instantiation_domain_name);

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
     * @brief Set of feature templates associated with this feature template bundle.
     */
    /**@{*/
    const std::list<dogen::logical::entities::variability::feature_template>& feature_templates() const;
    std::list<dogen::logical::entities::variability::feature_template>& feature_templates();
    void feature_templates(const std::list<dogen::logical::entities::variability::feature_template>& v);
    void feature_templates(const std::list<dogen::logical::entities::variability::feature_template>&& v);
    /**@}*/

    const std::string& instantiation_domain_name() const;
    std::string& instantiation_domain_name();
    void instantiation_domain_name(const std::string& v);
    void instantiation_domain_name(const std::string&& v);

public:
    bool operator==(const feature_template_bundle& rhs) const;
    bool operator!=(const feature_template_bundle& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::logical::entities::element& other) const override;

public:
    void swap(feature_template_bundle& other) noexcept;
    feature_template_bundle& operator=(feature_template_bundle other);

private:
    std::list<dogen::logical::entities::variability::feature_template> feature_templates_;
    std::string instantiation_domain_name_;
};

}

namespace std {

template<>
inline void swap(
    dogen::logical::entities::variability::feature_template_bundle& lhs,
    dogen::logical::entities::variability::feature_template_bundle& rhs) {
    lhs.swap(rhs);
}

}

#endif
