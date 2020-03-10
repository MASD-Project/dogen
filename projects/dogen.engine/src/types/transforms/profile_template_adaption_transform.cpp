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
#include "dogen.assets/types/features/variability_profile.hpp"
#include "dogen.assets/types/features/variability_entry.hpp"
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

variability::meta_model::profile_template profile_template_adaption_transform::
adapt(const variability::meta_model::feature_model& fm,
    const assets::meta_model::variability::profile_template& vpt) {

    using assets::features::variability_profile;
    const auto fg1(variability_profile::make_feature_group(fm));

    using assets::features::variability_profile;
    const auto scfg1(variability_profile::make_static_configuration(fg1, vpt));

    const auto sn(vpt.name().simple());
    const auto qn(vpt.name().qualified().dot());
    BOOST_LOG_SEV(lg, trace) << "Adapting: " << sn << " (" << qn << ")";

    variability::meta_model::profile_template r;
    r.name().simple(sn);
    r.name().qualified(qn);

    std::unordered_set<std::string> labels;
    for (const auto& l : scfg1.labels) {
        const auto inserted(labels.insert(l).second);
        if (!inserted) {
            BOOST_LOG_SEV(lg, error) << duplicate_label << l;
            BOOST_THROW_EXCEPTION(transform_exception(duplicate_label + l));
        }
    }

    r.labels(labels);

    for (const auto& n : vpt.parents())
        r.parents().push_back(n.qualified().dot());

    using assets::features::variability_entry;
    const auto fg2(variability_entry::make_feature_group(fm));
    for (const auto& e : vpt.entries()) {
        const auto& k(e.key());
        BOOST_LOG_SEV(lg, trace) << "Adapting entry: " << k;

        using assets::features::variability_entry;
        const auto scfg2(variability_entry::make_static_configuration(fg2, e));

        variability::meta_model::configuration_point_template cpt;
        cpt.name().simple(k);

        using variability::helpers::enum_mapper;
        const auto tc(enum_mapper::to_template_kind(scfg2.template_kind));
        cpt.kind(tc);

        /*
         * FIXME: not yet reading binding point.
         */

        using variability::meta_model::template_kind;
        if (cpt.kind() == template_kind::instance)
            cpt.name().qualified(k);

        archetypes::location al;
        al.kernel(scfg2.kernel);
        al.backend(scfg2.backend);
        al.facet(scfg2.facet);
        al.archetype(scfg2.archetype);
        cpt.location(al);

        if (!scfg2.value.empty() && !e.value().empty()) {
            BOOST_LOG_SEV(lg, error) << conflicting_values << k;
            BOOST_THROW_EXCEPTION(transform_exception(conflicting_values + k));
        } else if (scfg2.value.empty() && e.value().empty()) {
            BOOST_LOG_SEV(lg, error) << missing_value << k;
            BOOST_THROW_EXCEPTION(transform_exception(missing_value + k));
        } else if (!scfg2.value.empty()) {
            BOOST_LOG_SEV(lg, trace) << "Untyped value: " << scfg2.value;
            cpt.untyped_value(scfg2.value);
        } else {
            BOOST_LOG_SEV(lg, trace) << "Untyped value: " << e.value();
            cpt.untyped_value(e.value());
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
    std::list<variability::meta_model::profile_template> r;
    for (const auto& pair :
             ms.target().variability_elements().profile_templates()) {
        const auto& vpt(*pair.second);
        r.push_back(adapt(fm, vpt));
    }

    for (const auto& m : ms.references()) {
        for (const auto& pair : m.variability_elements().profile_templates()) {
            const auto& vpt(*pair.second);
            r.push_back(adapt(fm, vpt));
        }
    }

    stp.end_transform(r);
    return r;
}

}
