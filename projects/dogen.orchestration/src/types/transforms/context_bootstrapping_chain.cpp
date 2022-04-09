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
#include "dogen/io/configuration_io.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.variability/types/features/initializer.hpp"
#include "dogen.variability/types/entities/feature_template_repository.hpp"
#include "dogen.variability/types/transforms/feature_model_production_chain.hpp"
#include "dogen.physical/types/transforms/minimal_context.hpp"
#include "dogen.physical/types/transforms/meta_model_production_chain.hpp"
#include "dogen.templating/types/initializer.hpp"
#include "dogen.physical/types/features/initializer.hpp"
#include "dogen.codec/types/features/initializer.hpp"
#include "dogen.logical/types/features/initializer.hpp"
#include "dogen.orchestration/io/transforms/context_io.hpp"
#include "dogen.orchestration/types/features/initializer.hpp"
#include "dogen.text/types/transforms/cpp/cpp_factory.hpp"
#include "dogen.text/types/transforms/csharp/csharp_factory.hpp"
#include "dogen.orchestration/io/transforms/context_io.hpp"
#include "dogen.orchestration/types/transforms/context_factory.hpp"
#include "dogen.orchestration/types/transforms/context_bootstrapping_chain.hpp"

namespace {

const std::string transform_id(
    "orchestration.transforms.context_bootstrapping_chain");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string input_id("configuration");

}

namespace dogen::orchestration::transforms {

void context_bootstrapping_chain::register_variability_entities(
    variability::helpers::registrar& rg) {
    physical::features::initializer::register_entities(rg);
    codec::features::initializer::register_entities(rg);
    logical::features::initializer::register_entities(rg);
    templating::initializer::register_entities(rg);
    variability::features::initializer::register_entities(rg);
    features::initializer::register_entities(rg);
}

boost::shared_ptr<tracing::tracer>
context_bootstrapping_chain::create_and_setup_tracer(
    const configuration& cfg, const std::string& activity) {
    /*
     * Setup the tracer. Note that we do it regardless of whether
     * tracing is enabled or not - its the tracer job to handle
     * that. Also, we start tracing here so that all transforms can
     * make use of it.
     */
    using namespace transforms;
    const auto r(boost::make_shared<tracing::tracer>(cfg, activity));
    r->start_run(input_id, cfg);
    return r;
}

boost::shared_ptr<physical::entities::meta_model> context_bootstrapping_chain::
create_physical_meta_model(boost::shared_ptr<tracing::tracer> tracer) {
    /*
     * Create the minimal context. Note that we cannot use a regular
     * context because these depend on the PMM.
     */
    const auto ctx(context_factory::make_minimal_context(tracer));

    /*
     * Obtain the backends.
     */
    const std::list<physical::entities::backend> bes {
        text::transforms::cpp::cpp_factory::make(),
        text::transforms::csharp::csharp_factory::make()
    };

    /*
     * Execute the physical chain to get a PMM.
     */
    using physical::transforms::meta_model_production_chain;
    const auto r(meta_model_production_chain::apply(ctx, bes));

    return r;
}

boost::shared_ptr<variability::entities::feature_model>
context_bootstrapping_chain::
create_variability_feature_model(const variability::transforms::context& ctx) {
    /*
     * First we must register all entities in the variability space,
     * which we obtain by all the initialisers scattered across all
     * models.
     */
    variability::helpers::registrar vrg;
    register_variability_entities(vrg);
    const auto ftrp(vrg.feature_template_repository());
    const auto frp(vrg.feature_repository());

    /*
     * Now apply the feature model production chain to use those
     * entities to create a feature model.
     */
    using variability::transforms::feature_model_production_chain;
    const auto r(feature_model_production_chain::apply(ctx, ftrp, frp));
    return r;
}

context context_bootstrapping_chain::
bootstrap_full_context(const configuration& cfg, const std::string& activity,
    const std::vector<boost::filesystem::path>& reference_directories,
    const boost::filesystem::path& output_directory) {
    /*
     * Obtain the tracer.
     */
    const auto t(create_and_setup_tracer(cfg, activity));
    tracing::scoped_chain_tracer stp(lg, "full bootstrapping", transform_id,
        "bootstrapping", *t);

    /*
     * Create the physical meta-model.
     */
    const auto pmm(create_physical_meta_model(t));

    /*
     * Create the variability context, needed to create the feature
     * model.
     */
    const auto tid(pmm->template_instantiation_domains());
    const auto vctx(context_factory::make_variability_context(cfg, t, tid));

    /*
     * Now we can create the feature model.
     */
    const auto fm(create_variability_feature_model(vctx));

    /*
     * Finally, create the top-level context.
     */
    const auto& a(activity);
    const auto& od(output_directory);
    const auto& rds(reference_directories);
    const auto r(context_factory::make_context(cfg, a, rds, od, vctx, fm, pmm));

    stp.end_chain(r);
    return r;
}

}
