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
#ifndef DOGEN_ASSETS_TYPES_META_MODEL_VARIABILITY_FEATURE_TEMPLATE_BUNDLE_HPP
#define DOGEN_ASSETS_TYPES_META_MODEL_VARIABILITY_FEATURE_TEMPLATE_BUNDLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <list>
#include <iosfwd>
#include <algorithm>
#include "dogen.variability/types/meta_model/template_kind.hpp"
#include "dogen.assets/types/meta_model/variability/abstract_bundle.hpp"
#include "dogen.assets/types/meta_model/variability/feature_template.hpp"

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
class feature_template_bundle final : public dogen::assets::meta_model::variability::abstract_bundle {
public:
    feature_template_bundle(const feature_template_bundle&) = default;
    feature_template_bundle(feature_template_bundle&&) = default;

public:
    feature_template_bundle();

    virtual ~feature_template_bundle() noexcept { }

public:
    feature_template_bundle(
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
        const boost::optional<dogen::variability::meta_model::binding_point>& default_binding_point,
        const std::list<dogen::assets::meta_model::variability::feature_template>& feature_templates,
        const dogen::variability::meta_model::template_kind template_kind);

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
    const std::list<dogen::assets::meta_model::variability::feature_template>& feature_templates() const;
    std::list<dogen::assets::meta_model::variability::feature_template>& feature_templates();
    void feature_templates(const std::list<dogen::assets::meta_model::variability::feature_template>& v);
    void feature_templates(const std::list<dogen::assets::meta_model::variability::feature_template>&& v);
    /**@}*/

    /**
     * @brief Kind of template expansion to perform for this feature template.
     */
    /**@{*/
    dogen::variability::meta_model::template_kind template_kind() const;
    void template_kind(const dogen::variability::meta_model::template_kind v);
    /**@}*/

public:
    bool operator==(const feature_template_bundle& rhs) const;
    bool operator!=(const feature_template_bundle& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::assets::meta_model::element& other) const override;

public:
    void swap(feature_template_bundle& other) noexcept;
    feature_template_bundle& operator=(feature_template_bundle other);

private:
    std::list<dogen::assets::meta_model::variability::feature_template> feature_templates_;
    dogen::variability::meta_model::template_kind template_kind_;
};

}

namespace std {

template<>
inline void swap(
    dogen::assets::meta_model::variability::feature_template_bundle& lhs,
    dogen::assets::meta_model::variability::feature_template_bundle& rhs) {
    lhs.swap(rhs);
}

}

#endif
