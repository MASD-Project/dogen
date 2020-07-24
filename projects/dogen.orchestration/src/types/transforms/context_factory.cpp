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
#include "dogen.orchestration/io/transforms/context_io.hpp"
#include "dogen.orchestration/types/transforms/factory_exception.hpp"
#include "dogen.orchestration/types/transforms/context_factory.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("orchestration.transforms.context_factory"));

}

namespace dogen::orchestration::transforms {

physical::transforms::minimal_context context_factory::
make_minimal_context(boost::shared_ptr<tracing::tracer> tracer) {
    physical::transforms::minimal_context r;
    r.tracer(tracer);
    return r;
}

variability::transforms::context
context_factory::make_variability_context(const configuration& cfg,
    boost::shared_ptr<tracing::tracer> tracer,
    const std::unordered_map<std::string, std::vector<std::string>>&
    template_instantiation_domains) {

    variability::transforms::context r;
    r.template_instantiation_domains(template_instantiation_domains);
    const bool cm(cfg.model_processing().compatibility_mode_enabled());
    r.compatibility_mode(cm);
    r.tracer(tracer);

    return r;
}

injection::transforms::context context_factory::make_injection_context(
    const std::string& activity, boost::shared_ptr<tracing::tracer> tracer,
    boost::shared_ptr<physical::entities::meta_model> /*pmm*/) {
    BOOST_LOG_SEV(lg, debug) << "Creating the context. Activity: " << activity;

    /*
     * Obtain the share directory.
     */
    injection::transforms::context r;
    const auto lib_dir(utility::filesystem::library_directory());
    const auto lib_dirs(std::vector<boost::filesystem::path>{ lib_dir });
    r.data_directories(lib_dirs);

    /*
     * Setup the tracer. Note that we do it regardless of whether
     * tracing is enabled or not - its the tracer job to handle that.
     */
    r.tracer(tracer);

    return r;
}

context context_factory::
make_context(const configuration& cfg, const std::string& activity,
    const boost::filesystem::path& output_directory,
    const variability::transforms::context& vctx,
    boost::shared_ptr<variability::entities::feature_model> fm,
    boost::shared_ptr<physical::entities::meta_model> pmm) {
    BOOST_LOG_SEV(lg, debug) << "Creating the top-level context. Activity: "
                             << activity;

    /*
     * Create the top-level context and all of its sub-contexts. Start
     * by copying across attributes we've already defined.
     */
    orchestration::transforms::context r;
    r.variability_context(vctx);

    /*
     * Obtain the data directories.
     */
    const auto lib_dir(utility::filesystem::library_directory());
    const auto lib_dirs(std::vector<boost::filesystem::path>{ lib_dir });
    r.injection_context().data_directories(lib_dirs);

    /*
     * Handle the feature model.
     */
    r.injection_context().feature_model(fm);
    r.logical_context().feature_model(fm);
    r.text_context().feature_model(fm);
    r.physical_context().feature_model(fm);

    /*
     * Handle the compatibility mode for all other contexts.
     */
    const auto cm(vctx.compatibility_mode());
    r.logical_context().compatibility_mode(cm);
    r.injection_context().compatibility_mode(cm);

    /*
     * Populate the output directory.
     */
    r.text_context().output_directory_path(output_directory);

    /*
     * Setup the archetype location repository.
     */
    r.physical_context().meta_model(pmm);
    r.logical_context().physical_meta_model(pmm);
    r.text_context().physical_meta_model(pmm);

    /*
     * Setup the tracer.
     */
    const auto tracer(vctx.tracer());
    r.injection_context().tracer(tracer);
    r.logical_context().tracer(tracer);
    r.text_context().tracer(tracer);
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
    r.text_context().generation_timestamp(s.str());
    r.logical_context().activity_timestamp(s.str());

    BOOST_LOG_SEV(lg, debug) << "Generated context. Result: " << r;
    return r;
}

}
