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
#include <boost/date_time/posix_time/posix_time.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/filesystem/path.hpp"
#include "dogen.utility/types/filesystem/file.hpp"
#include "dogen.tracing/types/tracer.hpp"
#include "dogen.physical/types/entities/meta_model.hpp"
#include "dogen.physical/io/entities/meta_model_io.hpp"
#include "dogen.physical/io/entities/meta_name_repository_io.hpp"
#include "dogen.physical/types/helpers/meta_name_repository_builder.hpp"
#include "dogen.physical/types/helpers/template_instantiation_domains_factory.hpp"
#include "dogen.variability/types/transforms/context.hpp"
#include "dogen.variability/types/features/initializer.hpp"
#include "dogen.variability/types/entities/feature_template_repository.hpp"
#include "dogen.variability/types/transforms/feature_model_production_chain.hpp"
#include "dogen.templating/types/initializer.hpp"
#include "dogen.injection/types/transforms/context.hpp"
#include "dogen.physical/types/features/initializer.hpp"
#include "dogen.injection/types/features/initializer.hpp"
#include "dogen.logical/types/features/initializer.hpp"
#include "dogen.m2t/types/features/initializer.hpp"
#include "dogen.m2t/types/transforms/model_to_text_chain.hpp"
#include "dogen.m2t/types/transforms/model_to_text_technical_space_chain_registrar.hpp"
#include "dogen.m2t.cpp/types/feature_initializer.hpp"
#include "dogen.m2t.csharp/types/feature_initializer.hpp"
#include "dogen.orchestration/io/transforms/context_io.hpp"
#include "dogen.orchestration/types/features/initializer.hpp"
#include "dogen.orchestration/types/transforms/factory_exception.hpp"
#include "dogen.orchestration/types/transforms/context_factory.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("orchestration.transforms.context_factory"));

const std::string nrp_input_id("physical_name_repository");
const std::string fm_input_id("feature_model");

const std::string duplicate_segment("Duplicat segment: ");

}

namespace dogen::orchestration::transforms {

using m2t::transforms::model_to_text_technical_space_chain_registrar;

boost::shared_ptr<physical::entities::meta_model>
create_physical_meta_model(
    const model_to_text_technical_space_chain_registrar& rg) {

    physical::helpers::meta_name_repository_builder b;
    for (const auto& pair : rg.transforms_by_technical_space()) {
        const auto& t(*pair.second);
        b.add(t.physical_meta_names_by_logical_meta_name());
        b.add(t.physical_meta_name_repository_parts());
    }

    using physical::entities::meta_model;
    auto r(boost::make_shared<meta_model>());

    const auto nrp(b.build());
    r->kernels()["masd"].names(nrp);

    /*
     * Obtain the template instantiation domains.
     */
    using tidf = physical::helpers::template_instantiation_domains_factory;
    r->template_instantiation_domains(tidf::make(nrp.all()));
    return r;
}
void context_factory::
register_variability_entities(variability::helpers::registrar& rg) {
    physical::features::initializer::register_entities(rg);
    injection::features::initializer::register_entities(rg);
    logical::features::initializer::register_entities(rg);
    m2t::features::initializer::register_entities(rg);
    templating::initializer::register_entities(rg);
    variability::features::initializer::register_entities(rg);
    m2t::cpp::feature_initializer::register_entities(rg);
    m2t::csharp::feature_initializer::register_entities(rg);
    features::initializer::register_entities(rg);
}

injection::transforms::context context_factory::
make_injection_context(const configuration& cfg,
    const std::string& activity) {
    BOOST_LOG_SEV(lg, debug) << "Creating the context. Activity: " << activity;

    /*
     * Obtain the transform registrar and ensure it has been setup.
     */
    using m2t::transforms::model_to_text_chain;
    const auto& rg = model_to_text_chain::registrar();
    rg.validate();

    /*
     * Obtain the share directory.
     */
    injection::transforms::context r;
    const auto lib_dir(utility::filesystem::library_directory());
    const auto lib_dirs(std::vector<boost::filesystem::path>{ lib_dir });
    r.data_directories(lib_dirs);

    /*
     * Setup the physical data structures.
     */
    const auto pmm(create_physical_meta_model(rg));
    r.physical_meta_model(pmm);

    /*
     * Setup the tracer. Note that we do it regardless of whether
     * tracing is enabled or not - its the tracer job to handle that.
     */
    const auto tracer(boost::make_shared<tracing::tracer>(cfg, activity));
    r.tracer(tracer);

    return r;

}

context context_factory::
make_context(const configuration& cfg, const std::string& activity,
    const boost::filesystem::path& output_directory) {
    BOOST_LOG_SEV(lg, debug) << "Creating the top-level context. Activity: "
                             << activity;

    /*
     * First we create the variability context, needed to create the
     * feature model.
     */
    variability::transforms::context vctx;

    /*
     * Obtain the transform registrar and ensure it has been setup.
     */
    using m2t::transforms::model_to_text_chain;
    const auto& rg = model_to_text_chain::registrar();
    rg.validate();

    /*
     * Obtain the physical meta-model.
     */
    const auto pmm(create_physical_meta_model(rg));
    const auto& nrp(pmm->kernels().begin()->second.names());
    vctx.template_instantiation_domains(pmm->template_instantiation_domains());

    /*
     * Handle the compatibility mode.
     */
    const bool cm(cfg.model_processing().compatibility_mode_enabled());
    vctx.compatibility_mode(cm);

    /*
     * Setup the tracer. Note that we do it regardless of whether
     * tracing is enabled or not - its the tracer job to handle that.
     */
    const auto tracer(boost::make_shared<tracing::tracer>(cfg, activity));
    vctx.tracer(tracer);
    tracer->start_run(nrp_input_id, nrp);

    /*
     * Create the top-level context and all of its sub-contexts. Start
     * by copying across attributes we've already defined.
     */
    orchestration::transforms::context r;
    r.variability_context(vctx);
    r.logical_context().compatibility_mode(cm);

    /*
     * Obtain the data directories.
     */
    const auto lib_dir(utility::filesystem::library_directory());
    const auto lib_dirs(std::vector<boost::filesystem::path>{ lib_dir });
    r.injection_context().data_directories(lib_dirs);

    /*
     * Now we can create the feature model. First we must register all
     * entities in the variability space, which we obtain by all the
     * initialisers scattered across all models. Then we can apply the
     * feature model production chain to use those entities to create
     * a feature model.
     */
    variability::helpers::registrar vrg;
    register_variability_entities(vrg);
    const auto ftrp(vrg.feature_template_repository());
    const auto frp(vrg.feature_repository());
    using variability::transforms::feature_model_production_chain;
    const auto fm(feature_model_production_chain::apply(vctx, ftrp, frp));
    r.injection_context().feature_model(fm);
    r.logical_context().feature_model(fm);
    r.generation_context().feature_model(fm);
    r.physical_context().feature_model(fm);

    /*
     * Handle the compatibility mode for all other contexts.
     */
    r.injection_context().compatibility_mode(cm);

    /*
     * Populate the output directory.
     */
    r.generation_context().output_directory_path(output_directory);

    /*
     * Setup the archetype location repository.
     */
    r.injection_context().physical_meta_model(pmm);
    r.logical_context().physical_meta_model(pmm);
    r.generation_context().physical_meta_model(pmm);

    /*
     * Setup the tracer.
     */
    r.injection_context().tracer(tracer);
    r.logical_context().tracer(tracer);
    r.generation_context().tracer(tracer);
    r.physical_context().tracer(tracer);

    /*
     * Setup the diffing and operational reporting configuration.
     */
    r.physical_context().diffing_configuration(cfg.diffing());
    r.physical_context().reporting_configuration(cfg.reporting());

    /*
     * Populate dry run mode.
     */
    const auto drm(cfg.model_processing().dry_run_mode_enabled());
    r.physical_context().dry_run_mode_enabled(drm);

    /*
     * Populate the variability overrides.
     */
    const auto& vo(cfg.model_processing().variability_overrides());
    r.injection_context().variability_overrides(vo);

    /*
     * Populate the generation timestamp.
     */
    using namespace boost::posix_time;
    std::ostringstream s;
    s << to_iso_extended_string(cfg.model_processing().activity_timestamp());
    r.generation_context().generation_timestamp(s.str());

    BOOST_LOG_SEV(lg, debug) << "Generated context. Result: " << r;
    return r;
}

}
