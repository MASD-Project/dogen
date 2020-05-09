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
#include "dogen.templating/types/wale/instantiator.hpp"
#include "dogen.templating/types/stitch/instantiator.hpp"
#include "dogen.logical/io/entities/model_io.hpp"
#include "dogen.logical/types/features/wale.hpp"
#include "dogen.logical/types/transforms/context.hpp"
#include "dogen.logical/types/entities/technical_space.hpp"
#include "dogen.logical/types/transforms/transformation_error.hpp"
#include "dogen.logical/types/transforms/archetype_rendering_transform.hpp"

namespace {

const std::string transform_id("logical.transforms.parsing_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string empty;
const std::string decoration_preamble_key("masd.decoration.preamble");
const std::string decoration_postamble_key("masd.decoration.postamble");
const std::string stitch_wale_key("stitch.wale.template_instantiation_result");

const std::string empty_stitch_template("Stitch template has no content: ");
const std::string empty_wale_template("Wale template has no content: ");
const std::string duplicate_wale_key("Duplicate wale key: ");
const std::string missing_decoration("Missing decoration: ");

}

namespace dogen::logical::transforms {

std::string archetype_rendering_transform::render_wale_template(
    const variability::entities::feature_model& fm,
    const entities::physical::archetype& arch) {

    /*
     * If there is no wale template there is nothing to do, return an
     * empty string.
     */
    if (!arch.wale_template()) {
        std::string r;
        return r;
    }

    /*
     * Conversely, if the user specifically requested a wale template,
     * we expect its contents to be non-zero.
     */
    if (arch.wale_template_content().empty()) {
        const auto tid(arch.wale_template()->qualified().dot());
        BOOST_LOG_SEV(lg, error) << empty_wale_template << tid;
        BOOST_THROW_EXCEPTION(transformation_error(empty_wale_template + tid));
    }

    /*
     * Read wale features.
     */
    const auto fg(features::wale::make_feature_group(fm));
    const auto scfg(features::wale::make_static_configuration(fg, arch));

    /*
     * Create the input kvps for wale template.
     */
    std::unordered_map<std::string, std::string> kvps;
    for (const auto& pair : scfg.kvp) {
        const auto inserted(kvps.insert(pair).second);
        if (!inserted) {
            const auto& k(pair.first);
            BOOST_LOG_SEV(lg, error) << duplicate_wale_key << k;
            BOOST_THROW_EXCEPTION(transformation_error(duplicate_wale_key + k));
        }
    }

    /*
     * Instantiate the wale template.
     */
    templating::wale::instantiator inst;
    const auto r(inst.instantiate(arch.wale_template_content(), kvps));
    return r;
}

void archetype_rendering_transform::
apply(const context& ctx, entities::model& m) {
    tracing::scoped_transform_tracer stp(lg, "parsing transform",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);

    auto& archs(m.physical_elements().archetypes());
    for (auto& pair : archs) {
        auto& arch(*pair.second);
        const auto id(arch.name().qualified().dot());

        /*
         * We start by rendering the wale template. This may not
         * exist, in which case the string will be empty.
         */
        const auto& fm(*ctx.feature_model());
        const auto rendered_wale_template(render_wale_template(fm, arch));

        /*
         * Stitch template cannot be empty.
         */
        const auto& st(arch.stitch_template_content());
        if (st.empty()) {
            BOOST_LOG_SEV(lg, error) << empty_stitch_template << id;
            BOOST_THROW_EXCEPTION(
                transformation_error(empty_stitch_template + id));
        }

        /*
         * Locate the decoration for this template. We have hard-coded it
         * to c++ given that this is the only use case. We use the
         * decoration to build up the KVP map that will be supplied to the
         * template instantiator. The decoration must exist.
         */
        // const auto ts(logical::entities::technical_space::cpp);
        // const auto i(arch.decoration().find(ts));
        // if (i == arch.decoration().end()) {
        //     BOOST_LOG_SEV(lg, error) << missing_decoration << id;
        //     BOOST_THROW_EXCEPTION(
        //         transformation_error(missing_decoration + id));
        // }

        /*
         * Create the KVPs for the stitch template.
         */
        // auto dec(i->second);
        const auto kvps = std::unordered_map<std::string, std::string> {
            // {
            //     decoration_preamble_key, dec ? dec->preamble() : empty
            // },
            // {
            //     decoration_postamble_key, dec ? dec->postamble() : empty
            // },
            {
                decoration_preamble_key, empty
            },
            {
                decoration_postamble_key, empty
            },
            {
                stitch_wale_key, rendered_wale_template
            }
        };

        using variability::helpers::configuration_factory;
        const configuration_factory cf(fm, false/*compatibility_model*/);
        templating::stitch::instantiator inst(""/*FIXME*/, fm, cf);
        arch.rendered_stitch_template(inst.instantiate(st, kvps));
    }

    stp.end_transform(m);
}

}
