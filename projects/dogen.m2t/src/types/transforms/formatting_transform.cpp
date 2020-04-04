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
#include "dogen.utility/types/io/unordered_map_io.hpp"
#include "dogen.physical/types/entities/meta_model.hpp"
#include "dogen.physical/types/entities/name_repository.hpp"
#include "dogen.variability/types/helpers/feature_selector.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.logical/types/entities/element.hpp"
#include "dogen.m2t/io/entities/model_io.hpp"
#include "dogen.logical/io/entities/formatting_styles_io.hpp"
#include "dogen.m2t/types/transforms/transformation_error.hpp"
#include "dogen.m2t/types/transforms/formatting_transform.hpp"

namespace {

const std::string transform_id("m2t.transforms.formatting_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string stock_style("stock");
const std::string wale_style("wale");
const std::string stitch_style("stitch");
const std::string formatting_style_trait("formatting_style");
const std::string formatting_input_trait("formatting_input");

const std::string invalid_style("Formatting style is not valid:");

}

namespace dogen::m2t::transforms {

entities::formatting_styles
formatting_transform::to_formatting_style(const std::string& s) {
    if (s == stock_style)
        return entities::formatting_styles::stock;
    else if (s == wale_style)
        return entities::formatting_styles::wale;
    else if (s == stitch_style)
        return entities::formatting_styles::stitch;

    BOOST_LOG_SEV(lg, error) << invalid_style << s;
    BOOST_THROW_EXCEPTION(transformation_error(invalid_style + s));
}

std::unordered_map<std::string, formatting_transform::feature_group>
formatting_transform::make_feature_groups(
    const variability::entities::feature_model& fm,
    const std::list<physical::entities::meta_name>& mns) {

    BOOST_LOG_SEV(lg, debug) << "Creating feature groups.";

    std::unordered_map<std::string, formatting_transform::feature_group> r;
    for (const auto& mn : mns) {
        const auto arch(mn.qualified());

        feature_group fg;
        const variability::helpers::feature_selector s(fm);
        const auto fs(formatting_style_trait);
        fg.formatting_style = s.get_by_name(arch, fs);

        const auto fi(formatting_input_trait);
        fg.formatting_input = s.get_by_name(arch, fi);

        r[arch] = fg;
    }

    BOOST_LOG_SEV(lg, debug) << "Created feature groups.";
    return r;
}

std::unordered_map<std::string, formatting_configuration>
formatting_transform::make_formatting_configuration(
    const std::unordered_map<std::string, feature_group>& fgs,
    const variability::entities::configuration& cfg) {
    std::unordered_map<std::string, formatting_configuration> r;

    const variability::helpers::configuration_selector s(cfg);
    for (const auto& pair : fgs) {
        const auto arch(pair.first);
        const auto& fg(pair.second);

        bool found(false);
        formatting_configuration fc;
        const auto fs(fg.formatting_style);
        if (s.has_configuration_point(fs)) {
            found = true;
            fc.style(to_formatting_style(s.get_text_content(fs)));
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

void formatting_transform::
apply(const std::unordered_map<std::string, feature_group> fgs,
    logical::entities::element& e) {
    BOOST_LOG_SEV(lg, trace) << "Transforming element: "
                             << e.name().qualified().dot();

    const auto cfgs(make_formatting_configuration(fgs, *e.configuration()));
    auto& ap(e.artefact_properties());
    for (auto& pair : ap) {
        const auto arch(pair.first);
        auto& art_prop(pair.second);
        const auto i(cfgs.find(arch));
        if (i == cfgs.end()) {
            using logical::entities::formatting_styles;
            art_prop.formatting_style(formatting_styles::stock);
            BOOST_LOG_SEV(lg,trace) << "Element has a stock formatter.";
            continue;
        }
        const auto& cfg(i->second);

        // FIXME: mega hack until we move artefact stuff into
        // generation
        auto lambda(
            [](entities::formatting_styles fs) {
                using entities::formatting_styles;
                if (fs == entities::formatting_styles::wale)
                    return logical::entities::formatting_styles::wale;
                else if (fs == entities::formatting_styles::stitch)
                    return logical::entities::formatting_styles::stitch;
                else if (fs == entities::formatting_styles::stock)
                    return logical::entities::formatting_styles::stock;
                else
                    return logical::entities::formatting_styles::invalid;
            });
        art_prop.formatting_style(lambda(cfg.style()));
        art_prop.formatting_input(cfg.input());
    }

    BOOST_LOG_SEV(lg, debug) << "Finished transforming element";
}

void formatting_transform::apply(const context& ctx, entities::model& m) {
    tracing::scoped_transform_tracer stp(lg, "formatting transform",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);

    const auto& pmm(*ctx.physical_meta_model());
    const auto& nrp(pmm.kernels().cbegin()->second.names());
    const auto& ns(nrp.all());
    const auto& fm(*ctx.feature_model());
    const auto fgs(make_feature_groups(fm, ns));
    for(auto& ea : m.elements()) {
        auto& e(*ea.element());
        apply(fgs, e);
    }

    stp.end_transform(m);
}

}
