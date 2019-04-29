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
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.utility/types/filesystem/path.hpp"
#include "masd.dogen.utility/types/filesystem/file.hpp"
#include "masd.dogen.variability/types/helpers/feature_selector.hpp"
#include "masd.dogen.variability/types/helpers/configuration_selector.hpp"
#include "masd.dogen.archetypes/types/location_repository.hpp"
#include "masd.dogen.tracing/types/scoped_tracer.hpp"
#include "masd.dogen.extraction/types/traits.hpp"
#include "masd.dogen.extraction/io/meta_model/model_io.hpp"
#include "masd.dogen.extraction/types/transforms/update_outputting_properties_transform.hpp"

namespace {

const std::string transform_id(
    "extraction.transforms.update_outputting_properties_transform");

using namespace masd::dogen::utility::log;
auto lg(logger_factory(transform_id));

}

namespace masd::dogen::extraction::transforms {

update_outputting_properties_transform::feature_group
update_outputting_properties_transform::make_feature_group(
    const variability::meta_model::feature_model& fm) {

    feature_group r;
    const variability::helpers::feature_selector s(fm);

    const auto fw(traits::extraction::force_write());
    r.force_write = s.get_by_name(fw);

    const auto def(traits::extraction::delete_extra_files());
    r.delete_extra_files = s.get_by_name(def);

    const auto ifmr(traits::extraction::ignore_files_matching_regex());
    r.ignore_files_matching_regex = s.get_by_name(ifmr);

    const auto ded(traits::extraction::delete_empty_directories());
    r.delete_empty_directories = s.get_by_name(ded);

    return r;
}

bool update_outputting_properties_transform::
obtain_force_write(const feature_group& fg,
    const variability::meta_model::configuration& cfg) {
    const variability::helpers::configuration_selector s(cfg);
    return s.get_boolean_content_or_default(fg.force_write);
}

bool update_outputting_properties_transform::
obtain_delete_extra_files(const feature_group& fg,
    const variability::meta_model::configuration& cfg) {
    const variability::helpers::configuration_selector s(cfg);
    return s.get_boolean_content_or_default(fg.delete_extra_files);
}

std::vector<std::string> update_outputting_properties_transform::
obtain_ignore_files_matching_regex(const feature_group& fg,
    const variability::meta_model::configuration& cfg) {
    const variability::helpers::configuration_selector s(cfg);

    if (!s.has_configuration_point(fg.ignore_files_matching_regex))
        return std::vector<std::string>();

    const auto c(s.get_text_collection_content(fg.ignore_files_matching_regex));
    std::vector<std::string> r;
    r.reserve(c.size());
    for (const auto& e : c)
        r.push_back(e);
    return r;
}

bool update_outputting_properties_transform::
obtain_delete_empty_directories(const feature_group& fg,
    const variability::meta_model::configuration& cfg) {
    const variability::helpers::configuration_selector s(cfg);
    return s.get_boolean_content_or_default(fg.delete_empty_directories);
}

meta_model::outputting_properties
update_outputting_properties_transform::make_outputting_properties(
    const context& ctx, const variability::meta_model::configuration& cfg) {

    const auto fg(make_feature_group(*ctx.feature_model()));
    meta_model::outputting_properties r;
    r.force_write(obtain_force_write(fg, cfg));
    r.delete_extra_files(obtain_delete_extra_files(fg, cfg));
    r.ignore_files_matching_regex(obtain_ignore_files_matching_regex(fg, cfg));
    r.delete_empty_directories(obtain_delete_empty_directories(fg, cfg));

    return r;
}

void update_outputting_properties_transform::
apply(const context& ctx, meta_model::model& m) {
    tracing::scoped_transform_tracer stp(lg,
        "gather external artefacts transform", transform_id, m.name(),
        *ctx.tracer(), m);

    const auto& cfg(*m.configuration());
    const auto ep(make_outputting_properties(ctx, cfg));
    m.outputting_properties(ep);

    stp.end_transform(m);
}

}
