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
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.utility/types/io/list_io.hpp"
#include "masd.dogen.tracing/types/scoped_tracer.hpp"
#include "masd.dogen.variability/io/meta_model/profile_io.hpp"
#include "masd.dogen.variability/types/helpers/feature_selector.hpp"
#include "masd.dogen.variability/io/meta_model/profile_template_io.hpp"
#include "masd.dogen.variability/types/helpers/configuration_selector.hpp"
#include "masd.dogen.variability/types/helpers/template_instantiator.hpp"
#include "masd.dogen.variability/types/transforms/profile_template_instantiation_transform.hpp"

namespace {

const std::string transform_id(
    "variability.transforms.profile_template_instantiation_transform");

using namespace masd::dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string empty;
const std::string profile_field("masd.variability.profile");


}

namespace masd::dogen::variability::transforms {

profile_template_instantiation_transform::feature_group
profile_template_instantiation_transform::
make_feature_group(const meta_model::feature_model& fm) {
    BOOST_LOG_SEV(lg, debug) << "Creating feature group.";

    feature_group r;
    const helpers::feature_selector s(fm);
    r.profile = s.get_by_name(profile_field);

    BOOST_LOG_SEV(lg, debug) << "Created feature group.";
    return r;
}

std::string profile_template_instantiation_transform::
obtain_profile_name(const feature_group& fg,
    const meta_model::configuration& cfg) {

    BOOST_LOG_SEV(lg, debug) << "Reading profile name.";
    const helpers::configuration_selector s(cfg);
    std::string r;
    if (s.has_configuration_point(fg.profile))
        r = s.get_text_content(fg.profile);

    BOOST_LOG_SEV(lg, debug) << "Profile name: '" << r << "'";
    return r;
}

std::list<meta_model::profile> profile_template_instantiation_transform::
apply(const context& ctx, const meta_model::feature_model& fm,
    const std::list<meta_model::profile_template>& pts) {
    tracing::scoped_transform_tracer stp(lg,
        "profile template instantiation transform",
        transform_id, transform_id, *ctx.tracer(), pts);

    const auto fg(make_feature_group(fm));
    const auto cm(ctx.compatibility_mode());
    const auto& alrp(*ctx.archetype_location_repository());
    helpers::template_instantiator ti(alrp, cm);

    std::list<meta_model::profile> r;
    for (const auto& pt : pts) {
        auto prf(ti.instantiate(fm, pt));

        /*
         * FIXME: big hack. Create a temporary configuration just so
         * we can read the base profile name from the profile.
         */
        meta_model::configuration prf_cfg;
        prf_cfg.configuration_points(prf.configuration_points());
        const auto prf_bl(obtain_profile_name(fg, prf_cfg));
        prf.base_layer_profile(prf_bl);

        r.push_back(prf);
    }

    BOOST_LOG_SEV(lg, debug) << "Total number of templates instantiated: "
                             << r.size();

    stp.end_transform(r);
    return r;
}

}
