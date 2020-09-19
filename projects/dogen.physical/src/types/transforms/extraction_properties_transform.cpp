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

#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/io/unordered_set_io.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.variability/types/helpers/feature_selector.hpp"
#include "dogen.variability/types/helpers/configuration_selector.hpp"
#include "dogen.identification/io/entities/logical_id_io.hpp"
#include "dogen.physical/types/entities/meta_model.hpp"
#include "dogen.identification/types/entities/physical_meta_name_indices.hpp"
#include "dogen.physical/io/entities/model_io.hpp"
#include "dogen.identification/types/helpers/physical_meta_id_builder.hpp"
#include "dogen.physical/types/transforms/transform_exception.hpp"
#include "dogen.physical/types/transforms/extraction_properties_transform.hpp"

namespace {

const std::string
transform_id("physical.transforms.extraction_properties_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

const std::string cpp_headers_output_directory_feature(
    "masd.cpp.headers_output_directory");

const std::string root_module_not_found("Could not find root module: ");

}

namespace dogen::physical::transforms {

extraction_properties_transform::feature_group
extraction_properties_transform::
make_feature_group(const variability::entities::feature_model& fm) {
    feature_group r;
    const variability::helpers::feature_selector s(fm);

    const auto chod(cpp_headers_output_directory_feature);
    r.cpp_headers_output_directory = s.get_by_name(chod);

    return r;
}

boost::filesystem::path extraction_properties_transform::
obtain_cpp_headers_output_directory(const feature_group& fg,
    const variability::entities::configuration& cfg) {
    const variability::helpers::configuration_selector s(cfg);

    if (s.has_configuration_point(fg.cpp_headers_output_directory))
        return s.get_text_content(fg.cpp_headers_output_directory);

    return boost::filesystem::path();
}

entities::extraction_properties
extraction_properties_transform::make_extraction_properties(const context& ctx,
    const variability::entities::configuration& cfg) {

    const auto fg(make_feature_group(*ctx.feature_model()));
    entities::extraction_properties r;
    r.cpp_headers_output_directory(
        obtain_cpp_headers_output_directory(fg, cfg));

    return r;
}

void extraction_properties_transform::
apply(const context& ctx, entities::model& m) {
    tracing::scoped_transform_tracer stp(lg, "extraction properties",
        transform_id, m.name().id().value(), *ctx.tracer(), m);
    /*
     * Use the model's logical ID to locate the artefact set for the
     * root module. This contains the configuration for the model
     * itself.
     */
    const auto& lid(m.provenance().logical_name().id());
    const auto i(m.artefact_sets_by_logical_id().find(lid));
    if (i == m.artefact_sets_by_logical_id().end()) {
        BOOST_LOG_SEV(lg, error) << root_module_not_found << lid;
        BOOST_THROW_EXCEPTION(
            transform_exception(root_module_not_found + lid.value()));
    }

    const auto& cfg(*i->second.configuration());
    const auto ep(make_extraction_properties(ctx, cfg));
    m.meta_model_properties().extraction_properties(ep);

    stp.end_transform(m);
}

}
