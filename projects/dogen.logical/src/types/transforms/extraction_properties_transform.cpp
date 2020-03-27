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
#include "dogen.physical/types/entities/meta_model.hpp"
#include "dogen.physical/types/entities/name_repository.hpp"
#include "dogen.logical/io/entities/model_io.hpp"
#include "dogen.logical/types/traits.hpp"
#include "dogen.logical/types/entities/structural/module.hpp"
#include "dogen.logical/types/transforms/context.hpp"
#include "dogen.logical/types/transforms/extraction_properties_transform.hpp"

namespace {

const std::string
transform_id("transforms.extraction_properties_transform");

using namespace dogen::utility::log;
static logger lg(logger_factory(transform_id));

}

namespace dogen::logical::transforms {

extraction_properties_transform::feature_group
extraction_properties_transform::make_feature_group(
    const variability::entities::feature_model& fm,
    const std::list<physical::entities::name>& ns) {
    feature_group r;
    const variability::helpers::feature_selector s(fm);

    const auto chod(traits::extraction::cpp_headers_output_directory());
    r.cpp_headers_output_directory = s.get_by_name(chod);

    const auto ekd(traits::extraction::enable_backend_directories());
    r.enable_backend_directories = s.get_by_name(ekd);

    const auto en(traits::enabled());
    for (const auto n : ns) {
        const auto& l(n.location());
        const auto b(l.backend());
        r.enabled[b] = s.get_by_name(b, en);
    }

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

std::unordered_set<std::string>
extraction_properties_transform::
obtain_enabled_backends(const feature_group& fg,
    const variability::entities::configuration& cfg) {
    std::unordered_set<std::string> r;
    const variability::helpers::configuration_selector s(cfg);
    for (const auto& pair : fg.enabled) {
        const auto& b(pair.first);
        const auto& f(pair.second);
        const bool enabled(s.get_boolean_content_or_default(f));
        if (!enabled) {
            BOOST_LOG_SEV(lg, trace) << "Backend disabled: " << b;
            continue;
        }

        r.insert(b);
    }

    BOOST_LOG_SEV(lg, trace) << "Enabled backends: " << r;
    return r;
}

bool extraction_properties_transform::
obtain_enable_backend_directories(const feature_group& fg,
    const variability::entities::configuration& cfg) {
    const variability::helpers::configuration_selector s(cfg);
    return s.get_boolean_content_or_default(fg.enable_backend_directories);
}

entities::extraction_properties
extraction_properties_transform::make_extraction_properties(const context& ctx,
    const std::list<physical::entities::name>& ns,
    const variability::entities::configuration& cfg) {

    const auto fg(make_feature_group(*ctx.feature_model(), ns));
    entities::extraction_properties r;
    r.cpp_headers_output_directory(
        obtain_cpp_headers_output_directory(fg, cfg));

    r.enabled_backends(obtain_enabled_backends(fg, cfg));
    if (r.enabled_backends().size() > 1) {
        /*
         * If the user requested more than one backend, we have no
         * option but to create directories for each.
         */
        BOOST_LOG_SEV(lg, warn) << "More than one backend is enabled: "
                                << r.enabled_backends().size()
                                << ". Forcing enable_backend_directories.";
        r.enable_backend_directories(true);
    } else
        r.enable_backend_directories(
            obtain_enable_backend_directories(fg, cfg));

    return r;
}

void extraction_properties_transform::apply(const context& ctx,
    entities::model& m) {
    tracing::scoped_transform_tracer stp(lg, "feature model transform",
        transform_id, transform_id, *ctx.tracer(), m);

    const auto& pmm(*ctx.physical_meta_model());
    const auto& nrp(pmm.kernels().cbegin()->second.names());
    const auto& ns(nrp.all());
    const auto& cfg(*m.root_module()->configuration());
    const auto ep(make_extraction_properties(ctx, ns, cfg));
    m.extraction_properties(ep);

    stp.end_transform(m);
}

}
