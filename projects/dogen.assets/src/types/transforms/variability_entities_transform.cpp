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
#include <boost/throw_exception.hpp>
#include "dogen.assets/types/meta_model/variability/abstract_feature.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/io/list_io.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.variability/types/helpers/enum_mapper.hpp"
#include "dogen.variability/lexical_cast/meta_model/binding_point_lc.hpp"
#include "dogen.variability/lexical_cast/meta_model/template_kind_lc.hpp"
#include "dogen.assets/types/traits.hpp"
#include "dogen.assets/io/meta_model/model_io.hpp"
#include "dogen.assets/types/meta_model/attribute.hpp"
#include "dogen.assets/types/meta_model/variability/initializer.hpp"
#include "dogen.assets/types/transforms/context.hpp"
#include "dogen.assets/types/transforms/transformation_error.hpp"
#include "dogen.assets/types/meta_model/variability/profile_template.hpp"
#include "dogen.assets/types/meta_model/variability/profile.hpp"
#include "dogen.assets/types/transforms/variability_entities_transform.hpp"

namespace {

const std::string
transform_id("assets.transforms.variability_entities_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string empty;
const std::string duplicate_label("Profile has a duplicate label: ");
const std::string conflicting_values(
    "Entry has a value as meta-data and as a property: ");
const std::string missing_value("Must supply a value for entry: ");
const std::string fixed_mapping_not_found("Fixed mapping not found: ");
const std::string too_many_bindings(
    "Binding point supplied at bundle and template level: ");
const std::string missing_bindings(
    "Binding point must be supplied at either bundle or template level: ");
const std::string  bundle_generates_nothing(
    "Bundle does not generate either registration or static configuration: ");

}

namespace dogen::assets::meta_model {

inline bool operator<(const name& lhs, const name& rhs) {
    return lhs.qualified().dot() < rhs.qualified().dot();
}

}

namespace dogen::assets::transforms {

void variability_entities_transform::update(
    const features::variability_templates::feature_group& fg,
    meta_model::variability::abstract_feature& ft) {

    using features::variability_templates;
    const auto scfg(variability_templates::make_static_configuration(fg, ft));

    ft.is_optional(scfg.is_optional);

    using boost::lexical_cast;
    using variability::meta_model::binding_point;
    if (!scfg.binding_point.empty())
        ft.binding_point(lexical_cast<binding_point>(scfg.binding_point));
}

void variability_entities_transform::
update(const features::variability_bundle::feature_group& fg,
    meta_model::variability::abstract_bundle& fb) {

    using features::variability_bundle;
    const auto scfg(variability_bundle::make_static_configuration(fg, fb));
    fb.generate_registration(scfg.generate_registration);
    fb.generate_static_configuration(scfg.generate_static_configuration);

    archetypes::location al;
    al.kernel(scfg.kernel);
    al.backend(scfg.backend);
    al.facet(scfg.facet);
    al.archetype(scfg.archetype);
    fb.location(al);

    using boost::lexical_cast;
    using variability::meta_model::template_kind;
    using meta_model::variability::feature_template_bundle;
    auto ftb(dynamic_cast<feature_template_bundle*>(&fb));
    if (ftb)
        ftb->template_kind(lexical_cast<template_kind>(scfg.template_kind));

    using boost::lexical_cast;
    using variability::meta_model::binding_point;
    if (!scfg.default_binding_point.empty()) {
        fb.default_binding_point(lexical_cast<binding_point>(
                scfg.default_binding_point));
    }
}

void variability_entities_transform::update(
    const features::variability_profile::feature_group& fg,
    meta_model::variability::abstract_profile& ap) {

    using vp = assets::features::variability_profile;
    const auto scfg1(vp::make_static_configuration(fg, ap));

    std::unordered_set<std::string> labels;
    for (const auto& l : scfg1.labels) {
        const auto inserted(labels.insert(l).second);
        if (!inserted) {
            BOOST_LOG_SEV(lg, error) << duplicate_label << l;
            BOOST_THROW_EXCEPTION(transformation_error(duplicate_label + l));
        }
    }
    ap.labels(labels);
}

void variability_entities_transform::update(
    const features::variability_entry::feature_group& fg,
    meta_model::variability::abstract_profile_entry& ape) {

    const auto& k(ape.key());
    BOOST_LOG_SEV(lg, trace) << "Adapting entry: " << k;

    using assets::features::variability_entry;
    const auto scfg(variability_entry::make_static_configuration(fg, ape));

    using boost::lexical_cast;
    using variability::meta_model::template_kind;
    using meta_model::variability::profile_template_entry;
    auto pte(dynamic_cast<profile_template_entry*>(&ape));
    if (pte)
        pte->template_kind(lexical_cast<template_kind>(scfg.template_kind));

    /*
     * FIXME: not yet reading binding point.
     */
    archetypes::location al;
    al.kernel(scfg.kernel);
    al.backend(scfg.backend);
    al.facet(scfg.facet);
    al.archetype(scfg.archetype);

    /*
     * We must supply the value for the entry _either_ via meta-data
     * or via the value attribute; they can't both be empty or both be
     * populated.
     */
    if (!scfg.value.empty() && !ape.value().empty()) {
        BOOST_LOG_SEV(lg, error) << conflicting_values << k;
        BOOST_THROW_EXCEPTION(transformation_error(conflicting_values + k));
    } else if (scfg.value.empty() && ape.value().empty()) {
        BOOST_LOG_SEV(lg, error) << missing_value << k;
        BOOST_THROW_EXCEPTION(transformation_error(missing_value + k));
    }

    if (!scfg.value.empty())
        ape.value(scfg.value);

    BOOST_LOG_SEV(lg, trace) << "Untyped value: " << ape.value();
}

void variability_entities_transform::process_abstract_feature(
    const features::variability_templates::feature_group& fg1,
    const std::unordered_map<std::string, std::string>& fixed_mappings,
    const boost::optional<variability::meta_model::binding_point>&
    default_binding_point, meta_model::variability::abstract_feature& af) {

    update(fg1, af);

    const bool is_bound(default_binding_point.is_initialized());
    if (is_bound) {
        /*
         * Cannot supply binding points at both the bundle and
         * template level.
         */
        if (af.binding_point().is_initialized()) {
            const auto k(af.key());
            BOOST_LOG_SEV(lg, error) << too_many_bindings << k;
            BOOST_THROW_EXCEPTION(transformation_error(too_many_bindings + k));
        }

        /*
         * If a default binding point was supplied at the bundle
         * level, copy it across.
         */
        af.binding_point(default_binding_point);
    }

    /*
     * Must supply binding points at either the bundle or
     * template level.
     */
    if (!is_bound && !af.binding_point().is_initialized()) {
        const auto k(af.key());
        BOOST_LOG_SEV(lg, error) << missing_bindings << k;
        BOOST_THROW_EXCEPTION(transformation_error(missing_bindings + k));
    }

    /*
     * A feature template will require optionality on the
     * generated static configuration if it is optional and
     * its underlying type does not have a natural way of
     * representing absence (e.g. .empty()) and it has no
     * default value. In this case, the property in the static
     * configuration must be of an optional type, in order to
     * handle the tri-bool logic: a) not supplied b) supplied
     * but set to default (of the type, not of the template
     * since it has not default) c) supplied and set to a
     * value.
     */
    const bool has_default(!af.value().empty());
    using variability::meta_model::value_type;
    const bool type_without_empty(
        af.value_type() == value_type::boolean ||
        af.value_type() == value_type::number);
    af.requires_optionality(af.is_optional() && type_without_empty &&
        !has_default);

    /*
     * Now we need to first map the unparsed type, using the
     * fixed mappings. These will return expressions that will
     * require parsing.
     */
    const auto& ut(af.unparsed_type());
    const auto i(fixed_mappings.find(ut));
    if (i == fixed_mappings.end()) {
        BOOST_LOG_SEV(lg, error) << fixed_mapping_not_found << ut;
        BOOST_THROW_EXCEPTION(
            transformation_error(fixed_mapping_not_found + ut));
    }

    /*
     * If optionality is needed, we need to inject it here,
     * before any parsing takes place.
     */
    if (af.requires_optionality()) {
        std::ostringstream s;
        s << "boost::optional<" << i->second << ">";
        af.mapped_type(s.str());
    } else
        af.mapped_type(i->second);
}

void variability_entities_transform::
process_feature_template_bundles(
    const variability::meta_model::feature_model& fm,
    const std::unordered_map<std::string, std::string>& fixed_mappings,
    meta_model::model& m) {
    /*
     * If there are no bundles, there is no work to do.
     */
    auto& ftb(m.variability_elements().feature_template_bundles());
    if (ftb.empty())
        return;

    /*
     * Create feature groups for all required features.
     */
    using features::variability_bundle;
    const auto fg1(variability_bundle::make_feature_group(fm));

    using features::variability_templates;
    const auto fg2(variability_templates::make_feature_group(fm));

    /*
     * Process all bundles and contained feature templates.
     */
    for (auto& pair : ftb) {
        auto& fb(*pair.second);
        update(fg1, fb);

        /*
         * Feature bundles are expected to generate either
         * registration or static configuration or both, but never
         * neither.
         */
        if (!fb.generate_registration() && !fb.generate_static_configuration()) {
            const auto id(fb.name().qualified().dot());
            BOOST_LOG_SEV(lg, error) << bundle_generates_nothing << id;
            BOOST_THROW_EXCEPTION(
                transformation_error(bundle_generates_nothing + id));
        }

        const auto& dbp(fb.default_binding_point());
        for (auto& ft : fb.feature_templates())
            process_abstract_feature(fg2, fixed_mappings, dbp, ft);
    }
}

void variability_entities_transform::
process_feature_bundles(const variability::meta_model::feature_model& fm,
    const std::unordered_map<std::string, std::string>& fixed_mappings,
    meta_model::model& m) {
    /*
     * If there are no bundles, there is no work to do.
     */
    auto& fbs(m.variability_elements().feature_bundles());
    if (fbs.empty())
        return;

    /*
     * Create feature groups for all required features.
     */
    using features::variability_bundle;
    const auto fg1(variability_bundle::make_feature_group(fm));

    using features::variability_templates;
    const auto fg2(features::variability_templates::make_feature_group(fm));

    /*
     * Process all bundles and contained feature templates.
     */
    for (auto& pair : fbs) {
        auto& fb(*pair.second);
        update(fg1, fb);

        /*
         * Feature bundles are expected to generate either
         * registration or static configuration or both, but never
         * neither.
         */
        if (!fb.generate_registration() && !fb.generate_static_configuration()) {
            const auto id(fb.name().qualified().dot());
            BOOST_LOG_SEV(lg, error) << bundle_generates_nothing << id;
            BOOST_THROW_EXCEPTION(
                transformation_error(bundle_generates_nothing + id));
        }

        const auto& dbp(fb.default_binding_point());
        for (auto& f : fb.features())
            process_abstract_feature(fg2, fixed_mappings, dbp, f);
    }
}

void variability_entities_transform::process_initialiser(meta_model::model& m) {
    /*
     * If the user did not add an initialiser to the model, there is
     * nothing to be done.
     */
    if (m.variability_elements().initializer() == nullptr)
        return;

    /*
     * Obtain the names of all feature template bundles, and add them
     * to the initialiser in sorted form.
     */
    auto& fti(*m.variability_elements().initializer());
    auto& ftb(m.variability_elements().feature_template_bundles());
    for (auto& pair : ftb) {
        auto& fb(*pair.second);

        /*
         * Only add feature templates which require registration.
         */
        if (fb.generate_registration())
            fti.feature_template_bundles().push_back(fb.name());
    }
    fti.feature_template_bundles().sort();

    /*
     * Obtain the names of all feature bundles, and add them to the
     * initialiser in sorted form.
     */
    auto& fb(m.variability_elements().feature_bundles());
    for (auto& pair : fb) {
        auto& f(*pair.second);

        /*
         * Only add feature templates which require registration.
         */
        if (f.generate_registration())
            fti.feature_bundles().push_back(f.name());
    }
    fti.feature_bundles().sort();
}

void variability_entities_transform::process_profile_templates(
    const variability::meta_model::feature_model& fm, meta_model::model& m) {
    /*
     * If there are no profile templates, there is no work to do.
     */
    auto& pts(m.variability_elements().profile_templates());
    if (pts.empty())
        return;

    /*
     * Create feature groups for all required features.
     */
    using features::variability_profile;
    const auto fg1(variability_profile::make_feature_group(fm));

    using features::variability_entry;
    const auto fg2(features::variability_entry::make_feature_group(fm));

    /*
     * Process all profile templates and contained entries.
     */
    for (auto& pair : pts) {
        auto& pt(*pair.second);
        update(fg1, pt);

        for (auto& e : pt.entries())
            update(fg2, e);
    }
}

void variability_entities_transform::process_profiles(
    const variability::meta_model::feature_model& fm, meta_model::model& m) {
    /*
     * If there are no profiles, there is no work to do.
     */
    auto& ps(m.variability_elements().profiles());
    if (ps.empty())
        return;

    /*
     * Create feature groups for all required features.
     */
    using features::variability_profile;
    const auto fg1(variability_profile::make_feature_group(fm));

    using features::variability_entry;
    const auto fg2(features::variability_entry::make_feature_group(fm));

    /*
     * Process all profile templates and contained entries.
     */
    for (auto& pair : ps) {
        auto& p(*pair.second);
        update(fg1, p);

        for (auto& e : p.entries())
            update(fg2, e);
    }
}

void variability_entities_transform::apply(const context& ctx,
    const std::unordered_map<std::string, std::string>& fixed_mappings,
    meta_model::model& m) {
    tracing::scoped_transform_tracer stp(lg, "variability entities transform",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);

    const auto& fm(*ctx.feature_model());
    process_feature_template_bundles(fm, fixed_mappings, m);
    process_feature_bundles(fm, fixed_mappings, m);
    process_initialiser(m);

    process_profiles(fm, m);
    process_profile_templates(fm, m);

    stp.end_transform(m);
}

}
