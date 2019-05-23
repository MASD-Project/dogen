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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.variability/types/helpers/feature_selector.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"
#include "dogen.variability/types/helpers/enum_mapper.hpp"
#include "dogen.assets/types/traits.hpp"
#include "dogen.assets/io/meta_model/model_io.hpp"
#include "dogen.assets/types/meta_model/attribute.hpp"
#include "dogen.assets/types/meta_model/variability/feature_template_initializer.hpp"
#include "dogen.assets/types/transforms/context.hpp"
#include "dogen.assets/types/transforms/transformation_error.hpp"
#include "dogen.assets/types/transforms/variability_feature_bundle_transform.hpp"

namespace {

const std::string
transform_id("assets.transforms.variability_feature_bundle_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string empty;
const std::string fixed_mapping_not_found("Fixed mapping not found: ");

}

namespace dogen::assets::meta_model {

inline bool operator<(const name& lhs, const name& rhs) {
    return lhs.qualified().dot() < rhs.qualified().dot();
}

}

namespace dogen::assets::transforms {

variability_feature_bundle_transform::feature_group
variability_feature_bundle_transform::make_feature_group(
    const variability::meta_model::feature_model& fm) {

    feature_group r;
    const variability::helpers::feature_selector s(fm);
    r.binding_point = s.get_by_name(traits::variability::binding_point());
    r.archetype_location_kernel = s.get_by_name(
        traits::variability::archetype_location_kernel());
    r.archetype_location_backend = s.get_by_name(
        traits::variability::archetype_location_backend());
    r.archetype_location_facet = s.get_by_name(
        traits::variability::archetype_location_facet());
    r.archetype_location_archetype = s.get_by_name(
        traits::variability::archetype_location_archetype());
    r.template_kind = s.get_by_name(traits::variability::template_kind());

    return r;
}

variability::meta_model::binding_point variability_feature_bundle_transform::
make_binding_point(const feature_group& fg,
    const variability::meta_model::configuration& cfg) {

    const variability::helpers::configuration_selector s(cfg);
    const auto tc(s.get_text_content(fg.binding_point));
    BOOST_LOG_SEV(lg, trace) << "Read binding point: " << tc;

    using variability::helpers::enum_mapper;
    const auto r(enum_mapper::to_binding_point(tc));
    return r;
}

std::string variability_feature_bundle_transform::
make_archetype_location_kernel(const feature_group& fg,
    const variability::meta_model::configuration& cfg) {

    const variability::helpers::configuration_selector s(cfg);
    const auto r(s.get_text_content(fg.archetype_location_kernel));
    BOOST_LOG_SEV(lg, trace) << "Read kernel: " << r;
    return r;
}

std::string variability_feature_bundle_transform::
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

std::string variability_feature_bundle_transform::
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

std::string variability_feature_bundle_transform::
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

variability::meta_model::template_kind variability_feature_bundle_transform::
make_template_kind(const feature_group& fg,
    const variability::meta_model::configuration& cfg) {

    const variability::helpers::configuration_selector s(cfg);
    const auto tc(s.get_text_content(fg.template_kind));
    BOOST_LOG_SEV(lg, trace) << "Read template kind: " << tc;

    using variability::helpers::enum_mapper;
    const auto r(enum_mapper::to_template_kind(tc));
    return r;
}

void variability_feature_bundle_transform::update(const feature_group& fg,
    meta_model::variability::feature_template& ft) {
    const auto& cfg(*ft.configuration());

    ft.template_kind(make_template_kind(fg, cfg));
    ft.binding_point(make_binding_point(fg, cfg));

    archetypes::location al;
    al.kernel(make_archetype_location_kernel(fg, cfg));
    al.backend(make_archetype_location_backend(fg, cfg));
    al.facet(make_archetype_location_facet(fg, cfg));
    al.archetype(make_archetype_location_archetype(fg, cfg));
    ft.location(al);
}

void variability_feature_bundle_transform::
apply(const context& ctx,
    const std::unordered_map<std::string, std::string>& fixed_mappings,
    meta_model::model& m) {
    tracing::scoped_transform_tracer stp(lg,
        "variability feature bundle transform", transform_id,
        m.name().qualified().dot(), *ctx.tracer(), m);

    const auto& bundles(m.variability_elements().feature_bundles());
    if (bundles.empty())
        return;

    const auto& fm(*ctx.feature_model());
    const auto fg(make_feature_group(fm));
    for (auto& pair : bundles) {
        auto& fb(*pair.second);
        auto& sr(fb.static_representation());
        sr.name().simple("static_configuration");

        for (auto& ft : fb.feature_templates()) {
            update(fg, ft);
            meta_model::attribute attr;
            attr.name().simple(ft.name().simple());

            const auto& ut(ft.unparsed_type());
            const auto i(fixed_mappings.find(ut));
            if (i == fixed_mappings.end()) {
                BOOST_LOG_SEV(lg, error) << fixed_mapping_not_found << ut;
                BOOST_THROW_EXCEPTION(
                    transformation_error(fixed_mapping_not_found + ut));
            }
            attr.unparsed_type(i->second);
        }
    }

    if (m.variability_elements().feature_template_initializer() == nullptr)
        return;

    auto& fti(*m.variability_elements().feature_template_initializer());
    for (auto& pair : bundles) {
        auto& fb(*pair.second);
        fti.bundles().push_back(fb.name());
    }
    fti.bundles().sort();

    stp.end_transform(m);
}

}
