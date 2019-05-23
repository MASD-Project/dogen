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
#include "dogen.utility/types/io/list_io.hpp"
#include "dogen.utility/types/io/unordered_set_io.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.variability/types/helpers/enum_mapper.hpp"
#include "dogen.variability/types/helpers/feature_selector.hpp"
#include "dogen.variability/io/meta_model/profile_template_io.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"
#include "dogen.assets/io/meta_model/model_set_io.hpp"
#include "dogen.assets/io/meta_model/variability/profile_template_io.hpp"
#include "dogen.engine/types/traits.hpp"
#include "dogen.engine/types/transforms/context.hpp"
#include "dogen.engine/types/transforms/transform_exception.hpp"
#include "dogen.engine/types/transforms/profile_template_adaption_transform.hpp"

namespace {

const std::string transform_id(
    "engine.transforms.profile_template_adaption_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string empty;

const std::string duplicate_label("Profile has a duplicate lable: ");
const std::string conflicting_values(
    "Entry has a value as meta-data and as a property: ");
const std::string missing_value("Must supply a value for entry: ");

}

namespace dogen::engine::transforms {

profile_template_adaption_transform::feature_group
profile_template_adaption_transform::make_feature_group(
    const variability::meta_model::feature_model& fm) {

    feature_group r;
    const variability::helpers::feature_selector s(fm);
    r.binding_point = s.get_by_name(traits::variability::binding_point());
    r.labels = s.get_by_name(traits::variability::labels());
    r.archetype_location_kernel = s.get_by_name(
        traits::variability::archetype_location_kernel());
    r.archetype_location_backend = s.get_by_name(
        traits::variability::archetype_location_backend());
    r.archetype_location_facet = s.get_by_name(
        traits::variability::archetype_location_facet());
    r.archetype_location_archetype = s.get_by_name(
        traits::variability::archetype_location_archetype());
    r.template_kind = s.get_by_name(traits::variability::template_kind());
    r.untyped_value = s.get_by_name(traits::variability::untyped_value());

    return r;
}

variability::meta_model::binding_point profile_template_adaption_transform::
make_binding_point(const feature_group& fg,
    const variability::meta_model::configuration& cfg) {

    const variability::helpers::configuration_selector s(cfg);
    const auto tc(s.get_text_content(fg.binding_point));
    BOOST_LOG_SEV(lg, trace) << "Read binding point: " << tc;

    using variability::helpers::enum_mapper;
    const auto r(enum_mapper::to_binding_point(tc));
    return r;
}

std::unordered_set<std::string> profile_template_adaption_transform::
make_labels(const feature_group& fg,
    const variability::meta_model::configuration& cfg) {

    std::unordered_set<std::string> r;
    const variability::helpers::configuration_selector s(cfg);
    if (s.has_configuration_point(fg.labels)) {
        const auto tc(s.get_text_collection_content(fg.labels));
        BOOST_LOG_SEV(lg, trace) << "Read labels: " << r;

        for (const auto& l : tc) {
            const auto inserted(r.insert(l).second);
            if (!inserted) {
                BOOST_LOG_SEV(lg, error) << duplicate_label << l;
                BOOST_THROW_EXCEPTION(transform_exception(duplicate_label + l));
            }
        }
    }
    return r;
}

std::string profile_template_adaption_transform::
make_archetype_location_kernel(const feature_group& fg,
    const variability::meta_model::configuration& cfg) {

    const variability::helpers::configuration_selector s(cfg);
    const auto r(s.get_text_content(fg.archetype_location_kernel));
    BOOST_LOG_SEV(lg, trace) << "Read kernel: " << r;
    return r;
}

std::string profile_template_adaption_transform::
make_archetype_location_backend(const feature_group& fg,
    const variability::meta_model::configuration& cfg) {

    const variability::helpers::configuration_selector s(cfg);
    if (s.has_configuration_point(fg.archetype_location_backend)) {
        const auto r(s.get_text_content(fg.archetype_location_backend));
        BOOST_LOG_SEV(lg, trace) << "Read backend: " << r;
        return r;
    }

    return empty;
}

std::string profile_template_adaption_transform::
make_archetype_location_facet(const feature_group& fg,
    const variability::meta_model::configuration& cfg) {

    const variability::helpers::configuration_selector s(cfg);
    if (s.has_configuration_point(fg.archetype_location_facet)) {
        const auto r(s.get_text_content(fg.archetype_location_facet));
        BOOST_LOG_SEV(lg, trace) << "Read facet: " << r;
        return r;
    }

    return empty;
}

std::string profile_template_adaption_transform::
make_archetype_location_archetype(const feature_group& fg,
    const variability::meta_model::configuration& cfg) {

    const variability::helpers::configuration_selector s(cfg);
    if (s.has_configuration_point(fg.archetype_location_archetype)) {
        const auto r(s.get_text_content(fg.archetype_location_archetype));
        BOOST_LOG_SEV(lg, trace) << "Read archetype: " << r;
        return r;
    }

    return empty;
}

variability::meta_model::template_kind profile_template_adaption_transform::
make_template_kind(const feature_group& fg,
    const variability::meta_model::configuration& cfg) {

    const variability::helpers::configuration_selector s(cfg);
    const auto tc(s.get_text_content(fg.template_kind));
    BOOST_LOG_SEV(lg, trace) << "Read template kind: " << tc;

    using variability::helpers::enum_mapper;
    const auto r(enum_mapper::to_template_kind(tc));
    return r;
}

std::list<std::string> profile_template_adaption_transform::
make_untyped_value(const feature_group& fg,
    const variability::meta_model::configuration& cfg) {

    const variability::helpers::configuration_selector s(cfg);
    if (s.has_configuration_point(fg.untyped_value)) {
        const auto r(s.get_text_collection_content(fg.untyped_value));
        BOOST_LOG_SEV(lg, trace) << "Read untyped value: " << r;
        return r;
    }
    return std::list<std::string>{};
}

variability::meta_model::profile_template profile_template_adaption_transform::
adapt(const feature_group& fg,
    const assets::meta_model::variability::profile_template& vpt) {
    variability::meta_model::profile_template r;

    const auto sn(vpt.name().simple());
    const auto qn(vpt.name().qualified().dot());
    BOOST_LOG_SEV(lg, trace) << "Adapting: " << sn << " (" << qn << ")";

    r.name().simple(sn);
    r.name().qualified(qn);
    r.labels(make_labels(fg, *vpt.configuration()));

    for (const auto& n : vpt.parents())
        r.parents().push_back(n.qualified().dot());

    for (const auto& e : vpt.entries()) {
        const auto& cfg(*e.configuration());
        const auto& k(e.key());
        BOOST_LOG_SEV(lg, trace) << "Adapting entry: " << k;

        variability::meta_model::configuration_point_template cpt;
        cpt.name().simple(k);
        cpt.kind(make_template_kind(fg, cfg));

        /*
         * FIXME: not yet reading binding point.
         */

        using variability::meta_model::template_kind;
        if (cpt.kind() == template_kind::instance)
            cpt.name().qualified(k);

        archetypes::location al;
        al.kernel(make_archetype_location_kernel(fg, cfg));
        al.backend(make_archetype_location_backend(fg, cfg));
        al.facet(make_archetype_location_facet(fg, cfg));
        al.archetype(make_archetype_location_archetype(fg, cfg));
        cpt.location(al);

        const auto uv(make_untyped_value(fg, cfg));
        if (!uv.empty() && !e.value().empty()) {
            BOOST_LOG_SEV(lg, error) << conflicting_values << k;
            BOOST_THROW_EXCEPTION(transform_exception(conflicting_values + k));
        } else if (uv.empty() && e.value().empty()) {
            BOOST_LOG_SEV(lg, error) << missing_value << k;
            BOOST_THROW_EXCEPTION(transform_exception(missing_value + k));
        } else if (!uv.empty()) {
            BOOST_LOG_SEV(lg, trace) << "Untyped value: " << uv;
            cpt.untyped_value(uv);
        } else {
            BOOST_LOG_SEV(lg, trace) << "Untyped value: "
                                     << e.value();
            cpt.untyped_value().push_back(e.value());
        }
        r.templates().push_back(cpt);
    }

    return r;
}

std::list<variability::meta_model::profile_template>
profile_template_adaption_transform::
apply(const context& ctx, const assets::meta_model::model_set& ms) {
    tracing::scoped_transform_tracer stp(lg,
        "profile template adaption transform",
        transform_id, *ctx.variability_context().tracer(), ms);

    const auto& fm(*ctx.injection_context().feature_model());
    const auto fg(make_feature_group(fm));

    std::list<variability::meta_model::profile_template> r;
    for (const auto& pair :
             ms.target().variability_elements().profile_templates()) {
        const auto& vpt(*pair.second);
        r.push_back(adapt(fg, vpt));
    }

    for (const auto& m : ms.references()) {
        for (const auto& pair : m.variability_elements().profile_templates()) {
            const auto& vpt(*pair.second);
            r.push_back(adapt(fg, vpt));
        }
    }

    stp.end_transform(r);
    return r;
}

}
