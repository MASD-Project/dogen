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
#include "masd.dogen.annotations/types/annotation_factory.hpp"
#include "masd.dogen.annotations/types/annotation_expander.hpp"
#include "masd.dogen.annotations/types/type_repository_factory.hpp"
#include "masd.dogen.annotations/types/archetype_location_repository_builder.hpp"
#include "masd.dogen.tracing/types/tracer.hpp"
#include "masd.dogen.injection/types/transforms/context.hpp"
#include "masd.dogen.extraction/types/repository_factory.hpp"
#include "masd.dogen.coding/types/helpers/mapping_set_repository_factory.hpp"
#include "masd.dogen.generation/types/transforms/model_to_extraction_model_chain.hpp"
#include "masd.dogen.generation/types/transforms/model_to_extraction_model_transform_registrar.hpp"
#include "masd.dogen.orchestration/types/transforms/factory_exception.hpp"
#include "masd.dogen.orchestration/types/transforms/context_factory.hpp"

namespace {

using namespace masd::dogen::utility::log;
auto lg(logger_factory("orchestration.transforms.context_factory"));

const std::string duplicate_segment("Duplicat segment: ");

}

namespace masd::dogen::orchestration::transforms {

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
    for (const auto& pair : rg.transforms_by_language()) {
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

boost::shared_ptr<annotations::archetype_location_repository>
create_archetype_location_repository(
    const model_to_extraction_model_transform_registrar& rg) {

    using namespace annotations;
    archetype_location_repository_builder b;
    for (const auto& pair : rg.transforms_by_language()) {
        const auto& t(*pair.second);
        b.add(t.archetype_locations_by_meta_name());
        b.add(t.archetype_locations_by_family());
        b.add(t.archetype_location_repository_parts());
    }
    return boost::make_shared<archetype_location_repository>(b.build());
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
     * Setup the annotations related data structures.
     */
    const auto alrp(create_archetype_location_repository(rg));
    r.archetype_location_repository(alrp);

    annotations::type_repository_factory atrpf;
    const auto atrp(boost::make_shared<annotations::type_repository>(
            atrpf.make(*alrp, data_dirs)));
    r.type_repository(atrp);

    /*
     * Setup the annotations related factories.
     */
    const bool cm(cfg.model_processing().compatibility_mode_enabled());
    const auto af(boost::make_shared<annotations::annotation_factory>(
                *alrp, *atrp, cm));
    r.annotation_factory(af);

    /*
     * Setup the tracer. Note that we do it regardless of whether
     * tracing is enabled or not - its the tracer job to handle that.
     */
    const auto tracer(
        boost::make_shared<tracing::tracer>(*alrp, *atrp, cfg.tracing()));
    r.tracer(tracer);

    return r;

}

context context_factory::make_context(const configuration& cfg,
    const boost::filesystem::path& output_directory) {
    BOOST_LOG_SEV(lg, debug) << "Creating the context.";

    orchestration::transforms::context r;
    r.generation_context().output_directory_path(output_directory);

    /*
     * Obtain the transform registrar and ensure it has been setup.
     */
    using generation::transforms::model_to_extraction_model_chain;
    const auto& rg = model_to_extraction_model_chain::registrar();
    rg.validate();

    /*
     * Obtain the data directories.
     */
    const auto data_dir(utility::filesystem::data_files_directory());
    const auto data_dirs(std::vector<boost::filesystem::path>{ data_dir });
    r.injection_context().data_directories(data_dirs);

    /*
     * Setup the annotations related data structures.
     */
    const auto alrp(create_archetype_location_repository(rg));
    r.injection_context().archetype_location_repository(alrp);
    r.coding_context().archetype_location_repository(alrp);
    r.generation_context().archetype_location_repository(alrp);

    annotations::type_repository_factory atrpf;
    const auto atrp(boost::make_shared<annotations::type_repository>(
            atrpf.make(*alrp, data_dirs)));
    r.injection_context().type_repository(atrp);
    r.coding_context().type_repository(atrp);
    r.generation_context().type_repository(atrp);

    /*
     * Setup the annotations related factories.
     */
    const bool cm(cfg.model_processing().compatibility_mode_enabled());
    const auto af(boost::make_shared<annotations::annotation_factory>(
                *alrp, *atrp, cm));
    r.injection_context().annotation_factory(af);
    r.coding_context().annotation_factory(af);
    r.generation_context().annotation_factory(af);

    const auto ae(boost::make_shared<annotations::annotation_expander>(
            data_dirs, *alrp, *atrp, cm));
    r.coding_context().annotation_expander(ae);
    r.generation_context().annotation_expander(ae);

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
     * Setup the extraction repository.
     */
    extraction::repository_factory frpf;
    const auto frp(
        boost::make_shared<extraction::repository>(frpf.make(data_dirs)));
    r.generation_context().formatting_repository(frp);

    /*
     * Setup the tracer. Note that we do it regardless of whether
     * tracing is enabled or not - its the tracer job to handle that.
     */
    const auto tracer(
        boost::make_shared<tracing::tracer>(*alrp, *atrp, cfg.tracing()));
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
