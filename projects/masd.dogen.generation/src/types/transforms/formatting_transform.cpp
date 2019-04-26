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
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.utility/types/io/unordered_map_io.hpp"
#include "masd.dogen.archetypes/types/location_repository.hpp"
#include "masd.dogen.variability/io/type_io.hpp"
#include "masd.dogen.variability/types/entry_selector.hpp"
#include "masd.dogen.variability/types/type_repository_selector.hpp"
#include "masd.dogen.variability/types/helpers/feature_selector.hpp"
#include "masd.dogen.variability/types/helpers/configuration_selector.hpp"
#include "masd.dogen.tracing/types/scoped_tracer.hpp"
#include "masd.dogen.coding/types/meta_model/element.hpp"
#include "masd.dogen.generation/io/meta_model/model_io.hpp"
#include "masd.dogen.coding/io/meta_model/formatting_styles_io.hpp"
#include "masd.dogen.generation/types/transforms/transformation_error.hpp"
#include "masd.dogen.generation/types/transforms/formatting_transform.hpp"

namespace {

const std::string transform_id("generation.transforms.formatting_transform");

using namespace masd::dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string stock_style("stock");
const std::string wale_style("wale");
const std::string stitch_style("stitch");
const std::string formatting_style_trait("formatting_style");
const std::string formatting_input_trait("formatting_input");

const std::string invalid_style("Formatting style is not valid:");

}

namespace masd::dogen::generation::transforms {

meta_model::formatting_styles
formatting_transform::to_formatting_style(const std::string& s) {
    if (s == stock_style)
        return meta_model::formatting_styles::stock;
    else if (s == wale_style)
        return meta_model::formatting_styles::wale;
    else if (s == stitch_style)
        return meta_model::formatting_styles::stitch;

    BOOST_LOG_SEV(lg, error) << invalid_style << s;
    BOOST_THROW_EXCEPTION(transformation_error(invalid_style + s));
}

std::ostream&
operator<<(std::ostream& s, const formatting_transform::type_group& v) {
    s << " { "
      << "\"__type__\": " << "\"masd::dogen::masd::cpp::formattables::"
      << "formatting_transform::type_group\"" << ", "
      << "\"formatting_style\": " << v.formatting_style << ", "
      << "\"formatting_input\": " << v.formatting_input
      << " }";

    return s;
}

std::unordered_map<std::string, formatting_transform::type_group>
formatting_transform::make_type_groups(const variability::type_repository& atrp,
    const std::list<archetypes::location>& als) {

    BOOST_LOG_SEV(lg, debug) << "Creating type groups.";

    std::unordered_map<std::string, formatting_transform::type_group> r;
    for (const auto al : als) {
        const auto arch(al.archetype());

        type_group tg;
        const variability::type_repository_selector s(atrp);
        const auto fs(formatting_style_trait);
        tg.formatting_style = s.select_type_by_name(arch, fs);

        const auto fi(formatting_input_trait);
        tg.formatting_input = s.select_type_by_name(arch, fi);

        r[arch] = tg;
    }

    BOOST_LOG_SEV(lg, debug) << "Created type groups. Result: " << r;
    return r;
}

std::unordered_map<std::string, formatting_configuration>
formatting_transform::make_formatting_configuration(
    const std::unordered_map<std::string, type_group>& tgs,
    const variability::annotation& a) {
    std::unordered_map<std::string, formatting_configuration> r;

    const variability::entry_selector s(a);
    for (const auto& pair : tgs) {
        const auto arch(pair.first);
        const auto& tg(pair.second);

        bool found(false);
        formatting_configuration cfg;
        const auto fs(tg.formatting_style);
        if (s.has_entry(fs)) {
            found = true;
            cfg.style(to_formatting_style(s.get_text_content(fs)));
        }

        const auto fi(tg.formatting_input);
        if (s.has_entry(fi)) {
            found = true;
            cfg.input(s.get_text_content(fi));
        }

        if (found)
            r[arch] = cfg;
    }
    return r;
}

void formatting_transform::
apply(const std::unordered_map<std::string, type_group> tgs,
    coding::meta_model::element& e) {
    BOOST_LOG_SEV(lg, debug) << "Transforming element: "
                             << e.name().qualified().dot();

    const auto cfgs(make_formatting_configuration(tgs, e.annotation()));
    auto& ap(e.artefact_properties());
    for (auto& pair : ap) {
        const auto arch(pair.first);
        auto& art_prop(pair.second);
        const auto i(cfgs.find(arch));
        if (i == cfgs.end()) {
            using coding::meta_model::formatting_styles;
            art_prop.formatting_style(formatting_styles::stock);
            continue;
        }
        const auto& cfg(i->second);

        // FIXME: mega hack until we move artefact stuff into
        // generation
        auto lambda(
            [](meta_model::formatting_styles fs) {
                using meta_model::formatting_styles;
                if (fs == meta_model::formatting_styles::wale)
                    return coding::meta_model::formatting_styles::wale;
                else if (fs == meta_model::formatting_styles::stitch)
                    return coding::meta_model::formatting_styles::stitch;
                else if (fs == meta_model::formatting_styles::stock)
                    return coding::meta_model::formatting_styles::stock;
                else
                    return coding::meta_model::formatting_styles::invalid;
            });
        art_prop.formatting_style(lambda(cfg.style()));
        art_prop.formatting_input(cfg.input());
    }

    BOOST_LOG_SEV(lg, debug) << "Finished transforming element";
}

std::unordered_map<std::string, formatting_transform::feature_group>
formatting_transform::make_feature_groups(
    const variability::meta_model::feature_model& fm,
    const std::list<archetypes::location>& als) {

    BOOST_LOG_SEV(lg, debug) << "Creating feature groups.";

    std::unordered_map<std::string, formatting_transform::feature_group> r;
    for (const auto al : als) {
        const auto arch(al.archetype());

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
    const variability::meta_model::configuration& cfg) {
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
    coding::meta_model::element& e) {
    BOOST_LOG_SEV(lg, trace) << "Transforming element: "
                             << e.name().qualified().dot();

    const auto cfgs(make_formatting_configuration(fgs, *e.configuration()));
    auto& ap(e.artefact_properties());
    for (auto& pair : ap) {
        const auto arch(pair.first);
        auto& art_prop(pair.second);
        const auto i(cfgs.find(arch));
        if (i == cfgs.end()) {
            using coding::meta_model::formatting_styles;
            art_prop.formatting_style(formatting_styles::stock);
            BOOST_LOG_SEV(lg,trace) << "Element has a stock formatter.";
            continue;
        }
        const auto& cfg(i->second);

        // FIXME: mega hack until we move artefact stuff into
        // generation
        auto lambda(
            [](meta_model::formatting_styles fs) {
                using meta_model::formatting_styles;
                if (fs == meta_model::formatting_styles::wale)
                    return coding::meta_model::formatting_styles::wale;
                else if (fs == meta_model::formatting_styles::stitch)
                    return coding::meta_model::formatting_styles::stitch;
                else if (fs == meta_model::formatting_styles::stock)
                    return coding::meta_model::formatting_styles::stock;
                else
                    return coding::meta_model::formatting_styles::invalid;
            });
        art_prop.formatting_style(lambda(cfg.style()));
        art_prop.formatting_input(cfg.input());
    }

    BOOST_LOG_SEV(lg, debug) << "Finished transforming element";
}

void formatting_transform::apply(const context& ctx, meta_model::model& m) {
    tracing::scoped_transform_tracer stp(lg, "formatting transform",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);

    const auto& atrp(*ctx.type_repository());
    const auto& als(ctx.archetype_location_repository()->all());
    if (ctx.use_configuration()) {
        const auto& fm(*ctx.feature_model());
        const auto fgs(make_feature_groups(fm, als));
        for(auto& ptr : m.elements())
            apply(fgs, *ptr);
    } else {
        const auto tgs(make_type_groups(atrp, als));
        for(auto& ptr : m.elements())
            apply(tgs, *ptr);
    }
    stp.end_transform(m);
}

}
