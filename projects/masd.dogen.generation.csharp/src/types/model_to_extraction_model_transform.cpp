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
#include <boost/algorithm/string/join.hpp>
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.tracing/types/scoped_tracer.hpp"
#include "masd.dogen.coding/types/meta_model/module.hpp"
#include "masd.dogen.generation.csharp/types/traits.hpp"
#include "masd.dogen.generation.csharp/types/formattables/workflow.hpp"
#include "masd.dogen.generation.csharp/types/formatters/workflow.hpp"
#include "masd.dogen.generation.csharp/types/formattables/locator.hpp"
#include "masd.dogen.generation.csharp/types/model_to_extraction_model_transform.hpp"

namespace {

const std::string
transform_id(masd::dogen::generation::csharp::traits::backend());

using namespace masd::dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string empty;
const std::string dot(".");

}

namespace masd::dogen::generation::csharp {

model_to_extraction_model_transform::
~model_to_extraction_model_transform() noexcept { }

formattables::model
model_to_extraction_model_transform::create_formattables_model(
    const annotations::type_repository& atrp,
    const annotations::annotation& ra,
    const formatters::repository& frp, const formattables::locator& l,
    const generation::meta_model::model& m) const {
    formattables::workflow fw;
    return fw.execute(atrp, ra, frp, l, m);
}

std::string model_to_extraction_model_transform::id() const {
    return traits::backend();
}

std::list<extraction::meta_model::artefact> model_to_extraction_model_transform::
format(const annotations::type_repository& /*atrp*/,
    const annotations::annotation_factory& /*af*/,
    const dogen::extraction::repository& /*drp*/,
    const formattables::model& fm) const {
    formatters::workflow wf;
    return wf.execute(fm);
}

const std::forward_list<annotations::archetype_location>&
model_to_extraction_model_transform::archetype_locations() const {
    const auto& rg(formatters::workflow::registrar());
    return rg.archetype_locations();
}

const std::unordered_map<std::string,
                         annotations::archetype_locations_group>&
model_to_extraction_model_transform::archetype_locations_by_meta_name() const {
    const auto& rg(formatters::workflow::registrar());
    return rg.archetype_locations_by_meta_name();
}

const std::unordered_map<std::string,
                         std::list<annotations::archetype_location>>&
model_to_extraction_model_transform::archetype_locations_by_family() const {
    const auto& rg(formatters::workflow::registrar());
    return rg.archetype_locations_by_family();
}

const annotations::archetype_location_repository_parts&
model_to_extraction_model_transform::
archetype_location_repository_parts() const {
    const auto& rg(formatters::workflow::registrar());
    return rg.archetype_location_repository_parts();
}

coding::meta_model::technical_space
model_to_extraction_model_transform::technical_space() const {
    return coding::meta_model::technical_space::csharp;
}

std::unordered_map<std::string,
                   generation::meta_model::intra_backend_segment_properties>
model_to_extraction_model_transform::intra_backend_segment_properties() const {
    using namespace coding::meta_model;
    generation::meta_model::intra_backend_segment_properties project;

    using generation::meta_model::path_contribution_types;
    project.internal_modules(path_contribution_types::as_folders);
    project.facet(path_contribution_types::as_folders);

    std::unordered_map<
        std::string,
        generation::meta_model::intra_backend_segment_properties> r;
    r["project"] = project;
    return r;
}

extraction::meta_model::model
model_to_extraction_model_transform::apply(
    const generation::transforms::context& ctx,
    const bool enable_backend_directories,
    const generation::meta_model::model& m) const {
    tracing::scoped_transform_tracer stp(lg,
        "C# model to text transform", transform_id, m.name().qualified().dot(),
        *ctx.tracer());

    BOOST_LOG_SEV(lg, debug) << "Started backend.";

    /*
     * Create the locator.
     */
    const auto mn(m.name());
    const auto& ra(m.root_module()->annotation());
    const auto& atrp(*ctx.type_repository());
    const auto odp(ctx.output_directory_path());
    const auto& frp(formatters::workflow::registrar().formatter_repository());
    const bool ekd(enable_backend_directories);
    const formattables::locator l(odp, atrp, frp, ra, mn, m.module_ids(), ekd);

    /*
     * Generate the formattables model.
     */
    const auto fm(create_formattables_model(atrp, ra, frp, l, m));

    /*
     * Code-generate all artefacts.
     */
    extraction::meta_model::model r;
    const auto& drp(*ctx.formatting_repository());
    const auto& af(*ctx.annotation_factory());
    r.artefacts(format(atrp, af, drp, fm));
    r.managed_directories().push_back(l.project_path());

    BOOST_LOG_SEV(lg, debug) << "Finished backend.";
    return r;
}

}
