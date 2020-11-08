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
#include "dogen.identification/io/entities/logical_id_io.hpp"
#include "dogen.logical/io/entities/model_io.hpp"
#include "dogen.logical/types/features/wale.hpp"
#include "dogen.logical/types/transforms/context.hpp"
#include "dogen.identification/types/entities/technical_space.hpp"
#include "dogen.logical/types/transforms/transformation_error.hpp"
#include "dogen.logical/types/entities/templating/logic_less_template.hpp"
#include "dogen.logical/types/transforms/archetype_rendering_transform.hpp"

namespace {

const std::string transform_id(
    "logical.transforms.archetype_rendering_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string empty;
const std::string decoration_preamble_key("masd.decoration.preamble");
const std::string decoration_postamble_key("masd.decoration.postamble");
const std::string stitch_wale_key("stitch.wale.template_instantiation_result");

const std::string empty_stitch_template("Stitch template has no content: ");
const std::string empty_wale_template("Wale template has no content: ");
const std::string duplicate_key("Duplicate wale key: ");
const std::string missing_decoration("Missing decoration: ");
const std::string missing_logic_less_template(
    "Could not locate referenced logic-less template: ");

}

namespace dogen::logical::transforms {

void archetype_rendering_transform::
wale_template_population(entities::model& m) {
    const auto& pe(m.physical_elements());
    auto& archs(pe.archetypes());
    for (auto& pair : archs) {
        auto& arch(*pair.second);
        auto& tt(arch.text_templating());
        if (!tt.wale_template())
            continue;

        /*
         * Resolve logic-less template references to its content. We
         * expect to find the template since resolution already has
         * taken place, but you never know.
         */
        const auto tid(tt.wale_template()->id());
        const auto& llt(m.templating_elements().logic_less_templates());
        const auto k(llt.find(tid));
        if (k == llt.end()) {
            BOOST_LOG_SEV(lg, error) << missing_logic_less_template << tid;
            BOOST_THROW_EXCEPTION(transformation_error(
                    missing_logic_less_template + tid.value()));
        }
        tt.wale_template_content(k->second->content());
    }
}

std::string archetype_rendering_transform::render_wale_template(
    const variability::entities::feature_model& fm,
    const entities::physical::archetype& arch) {
    BOOST_LOG_SEV(lg, debug) << "Rendering wale template.";

    /*
     * If there is no wale template there is nothing to do, return an
     * empty string.
     */
    auto& tt(arch.text_templating());
    if (!tt.wale_template()) {
        std::string r;
        return r;
    }

    /*
     * Conversely, if the user specifically requested a wale template,
     * we expect its contents to be non-zero.
     */
    if (tt.wale_template_content().empty()) {
        const auto tid(tt.wale_template()->qualified().dot());
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
    const auto checked_insert(
        [&](const auto& pair) {
            const auto inserted(kvps.insert(pair).second);
            if (!inserted) {
                const auto& k(pair.first);
                BOOST_LOG_SEV(lg, error) << duplicate_key << k;
                BOOST_THROW_EXCEPTION(transformation_error(duplicate_key + k));
            }
        });

    for (const auto& pair : scfg.kvp)
        checked_insert(pair);

    /*
     * Inject the keys that can be inferred from the meta-model element.
     */
    const auto rs(arch.relations().status());
    if (!rs.empty())
        checked_insert(std::make_pair("referencing_status", rs));

    /*
     * Instantiate the wale template.
     */
    templating::wale::instantiator inst;
    const auto& content(tt.wale_template_content());
    const auto r(inst.instantiate(content, kvps));
    BOOST_LOG_SEV(lg, debug) << "Finished rendering wale template.";
    return r;
}

std::string archetype_rendering_transform::render_stitch_template(
    const variability::entities::feature_model& fm,
    const std::string& wale_template,
    const entities::physical::archetype& arch) {

    /*
     * Stitch template cannot be empty.
     */
    BOOST_LOG_SEV(lg, debug) << "Rendering stitch template.";
    auto& tt(arch.text_templating());
    const auto id(arch.name().qualified().dot());
    const auto& st(tt.stitch_template_content());
    if (st.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_stitch_template << id;
        BOOST_THROW_EXCEPTION(transformation_error(empty_stitch_template + id));
    }

    /*
     * Locate the decoration for this template. We have hard-coded it
     * to c++ given that this is the only use case. We use the
     * decoration to build up the KVP map that will be supplied to the
     * template instantiator. The decoration must exist.
     */
    const auto ts(identification::entities::technical_space::cpp);
    const auto i(arch.decoration().find(ts));
    if (i == arch.decoration().end()) {
        BOOST_LOG_SEV(lg, error) << missing_decoration << id;
        BOOST_THROW_EXCEPTION(transformation_error(missing_decoration + id));
    }

    /*
     * Create the KVPs for the stitch template.
     */
    auto dec(i->second);
    const auto kvps = std::unordered_map<std::string, std::string> {
        {
            decoration_preamble_key, dec ? dec->preamble() : empty
        },
        {
            decoration_postamble_key, dec ? dec->postamble() : empty
        },
        {
            stitch_wale_key, wale_template
        }
    };

    /*
     * Render the stitch template.
     */
    using variability::helpers::configuration_factory;
    const configuration_factory cf(fm, false/*compatibility_model*/);
    templating::stitch::instantiator inst(""/*FIXME*/, fm, cf);
    const auto r(inst.instantiate(st, kvps));
    BOOST_LOG_SEV(lg, debug) << "Finished rendering stitch template.";
    return r;
}

void archetype_rendering_transform::
render_all_templates(const context& ctx, entities::model& m) {
    auto& archs(m.physical_elements().archetypes());
    for (auto& pair : archs) {
        auto& arch(*pair.second);
        BOOST_LOG_SEV(lg, debug) << "Processing: "
                                 << arch.name().qualified().dot();

        /*
         * We start by rendering the wale template. This may not
         * exist, in which case the string will be empty.
         */
        const auto& fm(*ctx.feature_model());
        const auto rwt(render_wale_template(fm, arch));

        /*
         * Now render the stitch template and update the archetype.
         */
        const auto rst(render_stitch_template(fm, rwt, arch));
        arch.text_templating().rendered_stitch_template(rst);
    }
}

void archetype_rendering_transform::
apply(const context& ctx, entities::model& m) {
    tracing::scoped_transform_tracer stp(lg, "archetype rendering",
        transform_id, m.name().qualified().dot(), *ctx.tracer(), m);

    /*
     * Start by copying across the contents of all wale templates to
     * the elements which use them.
     */
    wale_template_population(m);

    /*
     * Render all templates - stitch and wale - on all elements which
     * have them.
     */
    render_all_templates(ctx, m);

    stp.end_transform(m);
}

}
