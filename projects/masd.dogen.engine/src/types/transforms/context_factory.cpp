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
#include <boost/make_shared.hpp>
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.utility/types/filesystem/path.hpp"
#include "masd.dogen.utility/types/filesystem/file.hpp"
#include "masd.dogen.tracing/types/tracer.hpp"
#include "masd.dogen.archetypes/types/features/initializer.hpp"
#include "masd.dogen.archetypes/io/location_repository_io.hpp"
#include "masd.dogen.archetypes/types/location_repository_builder.hpp"
#include "masd.dogen.variability/types/features/initializer.hpp"
#include "masd.dogen.variability/types/transforms/context.hpp"
#include "masd.dogen.variability/types/helpers/feature_template_registrar.hpp"
#include "masd.dogen.variability/types/transforms/feature_model_production_chain.hpp"
#include "masd.dogen.templating/types/initializer.hpp"
#include "masd.dogen.injection/types/transforms/context.hpp"
#include "masd.dogen.injection/types/features/registrar.hpp"
#include "masd.dogen.coding/types/features/initializer.hpp"
#include "masd.dogen.coding/types/helpers/mapping_set_repository_factory.hpp"
#include "masd.dogen.generation/types/features/initializer.hpp"
#include "masd.dogen.generation/types/transforms/model_to_extraction_model_chain.hpp"
#include "masd.dogen.generation/types/transforms/model_to_extraction_model_transform_registrar.hpp"
#include "masd.dogen.generation.cpp/types/feature_initializer.hpp"
#include "masd.dogen.generation.csharp/types/feature_initializer.hpp"
#include "masd.dogen.extraction/types/features/initializer.hpp"
#include "masd.dogen.engine/types/transforms/factory_exception.hpp"
#include "masd.dogen.engine/types/transforms/context_factory.hpp"

namespace {

using namespace masd::dogen::utility::log;
auto lg(logger_factory("engine.transforms.context_factory"));

const std::string alrp_input_id("archetype_location_repository");
const std::string fm_input_id("feature_model");

const std::string duplicate_segment("Duplicat segment: ");

}

namespace masd::dogen::engine::transforms {

using generation::transforms::model_to_extraction_model_transform_registrar;

std::unordered_map<std::string,
                   generation::meta_model::intra_backend_segment_properties>
create_intra_backend_segment_properties(
    const model_to_extraction_model_transform_registrar& rg) {
    std::unordered_map<
        std::string,
        generation::meta_model::intra_backend_segment_properties> r;

    /*
     * Obtain the intra-backend segment properties of each registered
     * model-to-text transform. Notice that the segment names must be
     * unique globally. Then merge them all into a single container of
     * segment properties.
     */
    for (const auto& pair : rg.transforms_by_technical_space()) {
        const auto& t(*pair.second);
        for (const auto& pair : t.intra_backend_segment_properties()) {
            const auto inserted(r.insert(pair).second);
            if (!inserted) {
                BOOST_LOG_SEV(lg, error) << duplicate_segment << pair.first;
                BOOST_THROW_EXCEPTION(
                    factory_exception(duplicate_segment + pair.first));
            }
        }
    }
    return r;
}

boost::shared_ptr<archetypes::location_repository>
create_archetype_location_repository(
    const model_to_extraction_model_transform_registrar& rg) {

    archetypes::location_repository_builder b;
    for (const auto& pair : rg.transforms_by_technical_space()) {
        const auto& t(*pair.second);
        b.add(t.archetype_locations_by_meta_name());
        b.add(t.archetype_locations_by_family());
        b.add(t.archetype_location_repository_parts());
    }
    return boost::make_shared<archetypes::location_repository>(b.build());
}

injection::transforms::context context_factory::
make_injection_context(const configuration& cfg) {
    BOOST_LOG_SEV(lg, debug) << "Creating the context.";

    /*
     * Obtain the transform registrar and ensure it has been setup.
     */
    using generation::transforms::model_to_extraction_model_chain;
    const auto& rg = model_to_extraction_model_chain::registrar();
    rg.validate();

    /*
     * Obtain the data directories.
     */
    injection::transforms::context r;
    const auto data_dir(utility::filesystem::data_files_directory());
    const auto data_dirs(std::vector<boost::filesystem::path>{ data_dir });
    r.data_directories(data_dirs);

    /*
     * Setup the archetypes data structures.
     */
    const auto alrp(create_archetype_location_repository(rg));
    r.archetype_location_repository(alrp);

    /*
     * Setup the tracer. Note that we do it regardless of whether
     * tracing is enabled or not - its the tracer job to handle that.
     */
    const auto tracer(boost::make_shared<tracing::tracer>(cfg.tracing()));
    r.tracer(tracer);

    return r;

}

context context_factory::make_context(const configuration& cfg,
    const boost::filesystem::path& output_directory) {
    BOOST_LOG_SEV(lg, debug) << "Creating the top-level context.";

    /*
     * First we create the variability context, needed to create the
     * feature model.
     */
    variability::transforms::context vctx;

    /*
     * Obtain the data directories.
     */
    const auto data_dir(utility::filesystem::data_files_directory());
    const auto data_dirs(std::vector<boost::filesystem::path>{ data_dir });
    vctx.data_directories(data_dirs);

    /*
     * Obtain the transform registrar and ensure it has been setup.
     */
    using generation::transforms::model_to_extraction_model_chain;
    const auto& rg = model_to_extraction_model_chain::registrar();
    rg.validate();

    /*
     * Obtain the archetype location repository.
     */
    const auto alrp(create_archetype_location_repository(rg));
    vctx.archetype_location_repository(alrp);

    /*
     * Handle the compatibility mode.
     */
    const bool cm(cfg.model_processing().compatibility_mode_enabled());
    vctx.compatibility_mode(cm);

    /*
     * Setup the tracer. Note that we do it regardless of whether
     * tracing is enabled or not - its the tracer job to handle that.
     */
    const auto tracer(boost::make_shared<tracing::tracer>(cfg.tracing()));
    vctx.tracer(tracer);
    tracer->add_initial_input(alrp_input_id, *alrp);

    /*
     * Create the top-level context and all of its sub-contexts.
     */
    engine::transforms::context r;
    r.variability_context(vctx);

    /*
     * Now we can create the feature model.
     */
    using variability::transforms::feature_model_production_chain;
    variability::helpers::feature_template_registrar ftrg;
    injection::features::registrar::register_templates(ftrg);
    coding::features::initializer::register_templates(ftrg);
    generation::features::initializer::register_templates(ftrg);
    templating::initializer::register_templates(ftrg);
    variability::features::initializer::register_templates(ftrg);
    archetypes::features::initializer::register_templates(ftrg);
    extraction::features::initializer::register_templates(ftrg);
    generation::cpp::feature_initializer::register_templates(ftrg);
    generation::csharp::feature_initializer::register_templates(ftrg);
    const auto ftrp(ftrg.repository());
    const auto fm(feature_model_production_chain::apply(vctx, ftrp));
    r.injection_context().feature_model(fm);
    r.coding_context().feature_model(fm);
    r.generation_context().feature_model(fm);
    r.extraction_context().feature_model(fm);

    /*
     * Handle the compatibility mode for all other contexts.
     */
    r.injection_context().compatibility_mode(cm);

    /*
     * Populate the output directory.
     */
    r.generation_context().output_directory_path(output_directory);

    /*
     * Populate the data directories.
     */
    r.injection_context().data_directories(data_dirs);

    /*
     * Setup the archetype location repository.
     */
    r.injection_context().archetype_location_repository(alrp);
    r.coding_context().archetype_location_repository(alrp);
    r.generation_context().archetype_location_repository(alrp);

    /*
     * Setup the intrabackend segment properties.
     */
    const auto ibsp(create_intra_backend_segment_properties(rg));
    r.generation_context().intra_backend_segment_properties(ibsp);

    coding::helpers::mapping_set_repository_factory msrpf;
    const auto msrp(
        boost::make_shared<coding::helpers::mapping_set_repository>(
            msrpf.make(data_dirs)));
    r.coding_context().mapping_repository(msrp);

    /*
     * Setup the tracer.
     */
    r.injection_context().tracer(tracer);
    r.coding_context().tracer(tracer);
    r.generation_context().tracer(tracer);
    r.extraction_context().tracer(tracer);

    /*
     * Setup the diffing and operational reporting configuration.
     */
    r.extraction_context().diffing_configuration(cfg.diffing());
    r.extraction_context().reporting_configuration(cfg.reporting());

    /*
     * Populate dry run mode.
     */
    const auto drm(cfg.model_processing().dry_run_mode_enabled());
    r.extraction_context().dry_run_mode_enabled(drm);

    return r;
}

}
