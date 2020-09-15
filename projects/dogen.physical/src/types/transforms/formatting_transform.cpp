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
#include "dogen.physical/types/entities/artefact_set.hpp"
#include "dogen.variability/types/helpers/feature_selector.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/io/optional_io.hpp"
#include "dogen.utility/types/io/unordered_map_io.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.physical/types/entities/meta_model.hpp"
#include "dogen.physical/io/entities/artefact_repository_io.hpp"
#include "dogen.physical/io/entities/backend_properties_io.hpp"
#include "dogen.physical/io/entities/facet_properties_io.hpp"
#include "dogen.physical/io/entities/archetype_properties_io.hpp"
#include "dogen.physical/io/entities/enablement_properties_io.hpp"
#include "dogen.physical/types/entities/artefact.hpp"
#include "dogen.physical/types/transforms/transform_exception.hpp"
#include "dogen.physical/types/transforms/formatting_transform.hpp"

namespace {

const std::string
transform_id("physical.transforms.formatting_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string stock_style("stock");
const std::string wale_style("wale");
const std::string stitch_style("stitch");
const std::string formatting_style_trait("formatting_style");
const std::string formatting_input_trait("formatting_input");

const std::string invalid_style("Formatting style is not valid:");

}

namespace dogen::physical::transforms {

entities::formatting_styles
formatting_transform::to_formatting_style(const std::string& s) {
    if (s == stock_style)
        return entities::formatting_styles::stock;
    else if (s == wale_style)
        return entities::formatting_styles::wale;
    else if (s == stitch_style)
        return entities::formatting_styles::stitch;

    BOOST_LOG_SEV(lg, error) << invalid_style << s;
    BOOST_THROW_EXCEPTION(transform_exception(invalid_style + s));
}

std::unordered_map<identification::entities::physical_meta_id,
                   formatting_transform::feature_group>
formatting_transform::make_feature_groups(
    const variability::entities::feature_model& fm,
    const std::list<identification::entities::physical_meta_name>& pmns) {

    BOOST_LOG_SEV(lg, debug) << "Creating feature groups.";

    std::unordered_map<identification::entities::physical_meta_id,
                       formatting_transform::feature_group> r;
    for (const auto& pmn : pmns) {
        const auto arch(pmn.id());

        feature_group fg;
        const variability::helpers::feature_selector s(fm);
        const auto fs(formatting_style_trait);
        fg.formatting_style = s.get_by_name(arch.value(), fs);

        const auto fi(formatting_input_trait);
        fg.formatting_input = s.get_by_name(arch.value(), fi);

        r[arch] = fg;
    }

    BOOST_LOG_SEV(lg, debug) << "Created feature groups.";
    return r;
}

std::unordered_map<identification::entities::physical_meta_id,
                   entities::formatting_configuration>
formatting_transform::make_formatting_configuration(
    const std::unordered_map<identification::entities::physical_meta_id,
    feature_group>& fgs, const variability::entities::configuration& cfg) {
    std::unordered_map<identification::entities::physical_meta_id,
                       entities::formatting_configuration> r;

    const variability::helpers::configuration_selector s(cfg);
    for (const auto& pair : fgs) {
        const auto arch(pair.first);
        const auto& fg(pair.second);

        bool found(false);
        entities::formatting_configuration fc;
        const auto fs(fg.formatting_style);
        if (s.has_configuration_point(fs)) {
            found = true;
            fc.styles(to_formatting_style(s.get_text_content(fs)));
        }

        const auto fi(fg.formatting_input);
        if (s.has_configuration_point(fi)) {
            found = true;
            fc.input(s.get_text_content(fi));
        }

        if (found)
            r[arch] = fc;
    }
    return r;
}

void formatting_transform::apply(const std::unordered_map<
    identification::entities::physical_meta_id, feature_group> fgs,
    entities::artefact_set& as) {
    const auto id(as.provenance().logical_name().id().value());
    BOOST_LOG_SEV(lg, trace) << "Transforming: " << id;

    const auto cfgs(make_formatting_configuration(fgs, *as.configuration()));
    for (auto& pair : as.artefacts_by_archetype()) {
        const auto arch(pair.first);
        auto& a(*pair.second);
        const auto i(cfgs.find(arch));
        if (i == cfgs.end()) {
            using entities::formatting_styles;
            a.formatting_style(formatting_styles::stock);
            BOOST_LOG_SEV(lg,trace) << "Element has a stock formatter.";
            continue;
        }
        const auto& cfg(i->second);
        a.formatting_style(cfg.styles());
        a.formatting_input(cfg.input());
    }

    BOOST_LOG_SEV(lg, debug) << "Finished transforming element";
}

void formatting_transform::
apply(const context& ctx, entities::artefact_repository& arp) {
    tracing::scoped_transform_tracer stp(lg, "formatting transform",
        transform_id, arp.provenance().logical_name().id().value(),
        *ctx.tracer(), arp);

    const auto& pmm(*ctx.meta_model());
    const auto& in(pmm.indexed_names());
    const auto& fm(*ctx.feature_model());
    const auto fgs(make_feature_groups(fm, in.all()));
    for(auto& pair : arp.artefact_sets_by_logical_id()) {
        auto& as(pair.second);
        apply(fgs, as);
    }

    stp.end_transform(arp);
}

}
