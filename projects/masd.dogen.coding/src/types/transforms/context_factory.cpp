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
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/throw_exception.hpp>
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.utility/types/filesystem/path.hpp"
#include "masd.dogen.utility/types/filesystem/file.hpp"
#include "masd.dogen.annotations/types/type_repository_factory.hpp"
#include "masd.dogen.annotations/types/archetype_location_repository_builder.hpp"
#include "masd.dogen.extraction/types/repository_factory.hpp"
#include "masd.dogen.tracing/types/tracer.hpp"
#include "masd.dogen.coding/types/helpers/mapping_set_repository_factory.hpp"
#include "masd.dogen.coding/types/helpers/artefact_writer_interface.hpp"
#include "masd.dogen.coding/types/helpers/filesystem_writer.hpp"
#include "masd.dogen.coding/types/transforms/building_error.hpp"
#include "masd.dogen.coding/types/transforms/options_validator.hpp"
#include "masd.dogen.coding/types/transforms/model_to_text_model_chain.hpp"
#include "masd.dogen.coding/types/transforms/context_factory.hpp"

namespace {

using namespace masd::dogen::utility::log;
auto lg(logger_factory("coding.transforms.context_factory"));

const std::string duplicate_segment("Duplicat segment: ");

}

namespace masd::dogen::coding::transforms {

std::unordered_map<std::string,
                   meta_model::intra_backend_segment_properties>
context_factory::create_intra_backend_segment_properties(
    const options& o, const model_to_text_model_transform_registrar& rg) {
    std::unordered_map<std::string,
                       meta_model::intra_backend_segment_properties> r;

    /*
     * Obtain the intra-backend segment properties of each registered
     * model-to-text transform. Notice that the segment names must be
     * unique globally. Then merge them all into a single container of
     * segment properties.
     */
    for (const auto& pair : rg.transforms_by_language()) {
        const auto& t(*pair.second);
        for (const auto& pair : t.intra_backend_segment_properties(o)) {
            const auto inserted(r.insert(pair).second);
            if (!inserted) {
                BOOST_LOG_SEV(lg, error) << duplicate_segment << pair.first;
                BOOST_THROW_EXCEPTION(
                    building_error(duplicate_segment + pair.first));
            }
        }
    }
    return r;
}

annotations::archetype_location_repository
context_factory::create_archetype_location_repository(
    const model_to_text_model_transform_registrar& rg) {
    annotations::archetype_location_repository_builder b;
    for (const auto& pair : rg.transforms_by_language()) {
        const auto& t(*pair.second);
        b.add(t.archetype_locations_by_meta_name());
        b.add(t.archetype_locations_by_family());
        b.add(t.archetype_location_repository_parts());
    }
    return b.build();
}

context context_factory::make(const options& o, const bool enable_validation) {
    BOOST_LOG_SEV(lg, debug) << "Creating the context.";

    if (enable_validation) {
        /*
         * Before anything else, lets make sure the transform options make
         * sense. No point in proceeding otherwise.
         */
        transforms::options_validator v;
        v.validate(o);
    }

    /*
     * Obtain the transform registrar and ensure it has been setup.
     */
    const auto& rg(model_to_text_model_chain::registrar());
    if (enable_validation)
        rg.validate();

    /*
     * Obtain all the data structures required to make a context, and
     * create the context.
     */
    const auto data_dir(utility::filesystem::data_files_directory());
    const auto data_dirs(std::vector<boost::filesystem::path>{ data_dir });

    helpers::mapping_set_repository_factory msrpf;
    const auto msrp(msrpf.make(data_dirs));

    const auto alrp(create_archetype_location_repository(rg));
    annotations::type_repository_factory atrpf;
    const auto atrp(atrpf.make(alrp, data_dirs));
    const auto ibsp(create_intra_backend_segment_properties(o, rg));

    extraction::repository_factory frpf;
    const auto frp(frpf.make(data_dirs));

    tracing::tracer tracer(alrp, atrp,
        o.log_level(), o.probe_all(), o.probe_all(),
        o.probe_all() || o.probe_stats(),
        o.probe_stats_disable_guids(),
        o.probe_stats_org_mode(),
        o.probe_use_short_names(),
        o.probe_directory());

    using helpers::filesystem_writer;
    auto writer(boost::make_shared<filesystem_writer>(o.force_write()));

    const context r(data_dirs, o, alrp, atrp, msrp, frp, tracer,
        ibsp, writer);

    BOOST_LOG_SEV(lg, debug) << "Created the context.";
    return r;
}

}
