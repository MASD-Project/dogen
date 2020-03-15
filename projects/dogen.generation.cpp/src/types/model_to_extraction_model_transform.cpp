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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/filesystem/path.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.assets/types/meta_model/structural/module.hpp"
#include "dogen.generation.cpp/types/traits.hpp"
#include "dogen.generation.cpp/types/formatters/workflow.hpp"
#include "dogen.generation.cpp/types/formattables/workflow.hpp"
#include "dogen.generation.cpp/types/model_to_extraction_model_transform.hpp"

namespace {

const std::string transform_id(dogen::generation::cpp::traits::backend());

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string empty;
const std::string dot(".");
const std::string description(
    "Generates C++ code according to the MASD generative model.");

}

namespace dogen::generation::cpp {

model_to_extraction_model_transform::
~model_to_extraction_model_transform() noexcept { }

const formatters::repository&
model_to_extraction_model_transform::formatters_repository() const {
    const auto& rg(formatters::workflow::registrar());
    rg.validate();
    return rg.formatter_repository();
}

formattables::model
model_to_extraction_model_transform::create_formattables_model(
    const variability::meta_model::feature_model& feature_model,
    const variability::meta_model::configuration& rcfg,
    const formatters::repository& frp, const formattables::locator& l,
    const generation::meta_model::model& m) const {
    formattables::workflow fw;
    return fw.execute(feature_model, rcfg, l, frp, m);
}

formattables::locator model_to_extraction_model_transform::make_locator(
    const boost::filesystem::path& output_directory_path,
    const variability::meta_model::feature_model& fm,
    const variability::meta_model::configuration& cfg,
    const formatters::repository& frp, const bool enable_backend_directories,
    const generation::meta_model::model& m) const {

    const auto& mn(m.name());
    const auto odp(output_directory_path);
    const auto& ep(m.extraction_properties());
    const auto chodp(ep.cpp_headers_output_directory());
    const auto ekd(enable_backend_directories);
    const auto ids(m.module_ids());
    const formattables::locator r(odp, chodp, fm, frp, cfg, mn, ids, ekd);
    return r;
}

std::string model_to_extraction_model_transform::id() const {
    return traits::backend();
}

std::string model_to_extraction_model_transform::description() const {
    return ::description;
}

std::list<extraction::meta_model::artefact>
model_to_extraction_model_transform::
format(const std::unordered_set<generation::meta_model::element_archetype>&
    enabled_archetype_for_element, const formattables::locator& l,
    const variability::meta_model::feature_model& feature_model,
    const variability::helpers::configuration_factory& cf,
    const formattables::model& fm) const {
    formatters::workflow wf(l, feature_model, cf);
    return wf.execute(enabled_archetype_for_element, fm);
}

std::list<boost::filesystem::path> model_to_extraction_model_transform::
managed_directories(const formattables::locator& l) const {
    std::list<boost::filesystem::path> r;
    r.push_back(l.project_path());
    if (l.project_path() != l.headers_project_path())
        r.push_back(l.headers_model_path());

    return r;
}

const std::forward_list<archetypes::location>&
model_to_extraction_model_transform::archetype_locations() const {
    const auto& rg(formatters::workflow::registrar());
    return rg.archetype_locations();
}

const std::unordered_map<std::string,
                         archetypes::locations_group>&
model_to_extraction_model_transform::archetype_locations_by_meta_name() const {
    const auto& rg(formatters::workflow::registrar());
    return rg.archetype_locations_by_meta_name();
}

const std::unordered_map<std::string,
                         std::list<archetypes::location>>&
model_to_extraction_model_transform::archetype_locations_by_family() const {
    const auto& rg(formatters::workflow::registrar());
    return rg.archetype_locations_by_family();
}

const archetypes::location_repository_parts&
model_to_extraction_model_transform::
archetype_location_repository_parts() const {
    const auto& rg(formatters::workflow::registrar());
    return rg.archetype_location_repository_parts();
}

assets::meta_model::technical_space
model_to_extraction_model_transform::technical_space() const {
    return assets::meta_model::technical_space::cpp;
}

std::unordered_map<std::string,
                   generation::meta_model::intra_backend_segment_properties>
model_to_extraction_model_transform::
intra_backend_segment_properties() const {
    std::unordered_map<
        std::string,
        generation::meta_model::intra_backend_segment_properties> r;
    return r;
}

extraction::meta_model::model model_to_extraction_model_transform::apply(
    const generation::transforms::context& ctx,
    const bool enable_backend_directories,
    const generation::meta_model::model& m) const {
    tracing::scoped_transform_tracer stp(lg,
        "C++ model to text transform", transform_id, m.name().qualified().dot(),
        *ctx.tracer());

    BOOST_LOG_SEV(lg, debug) << "Started backend.";

    /*
     * Create the locator.
     */
    const auto& odp(ctx.output_directory_path());
    const auto& feature_model(*ctx.feature_model());
    const auto& rcfg(*m.root_module()->configuration());
    const auto& frp(formatters_repository());
    const auto l(make_locator(odp, feature_model, rcfg, frp,
            enable_backend_directories, m));

    /*
     * Generate the formattables model.
     */
    const auto fm(create_formattables_model(feature_model, rcfg, frp, l, m));

    /*
     * Code-generate all artefacts.
     */
    extraction::meta_model::model r;
    const auto& eafe(m.enabled_archetype_for_element());
    using variability::helpers::configuration_factory;
    const configuration_factory cf(feature_model, false/*compatibility_model*/);

    r.artefacts(format(eafe, l, feature_model, cf, fm));
    r.managed_directories(managed_directories(l));

    BOOST_LOG_SEV(lg, debug) << "Finished backend.";
    return r;
}

}
