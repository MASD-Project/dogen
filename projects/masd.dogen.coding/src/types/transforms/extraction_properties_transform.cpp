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
#include "masd.dogen.variability/types/entry_selector.hpp"
#include "masd.dogen.variability/types/type_repository_selector.hpp"
#include "masd.dogen.variability/types/helpers/feature_selector.hpp"
#include "masd.dogen.variability/types/helpers/configuration_selector.hpp"
#include "masd.dogen.archetypes/types/location_repository.hpp"
#include "masd.dogen.coding/types/traits.hpp"
#include "masd.dogen.coding/types/meta_model/module.hpp"
#include "masd.dogen.coding/types/transforms/context.hpp"
#include "masd.dogen.coding/types/transforms/extraction_properties_transform.hpp"

namespace {

using namespace masd::dogen::utility::log;
static logger
lg(logger_factory("masd.transforms.extraction_properties_transform"));

}

namespace masd::dogen::coding::transforms {

extraction_properties_transform::type_group
extraction_properties_transform::make_type_group(
    const variability::type_repository& atrp,
    const std::list<archetypes::location>& als) {
    type_group r;
    const variability::type_repository_selector rs(atrp);

    const auto chod(traits::extraction::cpp_headers_output_directory());
    r.cpp_headers_output_directory = rs.select_type_by_name(chod);

    const auto ekd(traits::extraction::enable_backend_directories());
    r.enable_backend_directories = rs.select_type_by_name(ekd);

    const auto en(traits::enabled());
    for (const auto al : als) {
        type_group tg;
        const auto backend(al.backend());
        r.enabled.push_back(rs.select_type_by_name(backend, en));
    }

    return r;
}

boost::filesystem::path extraction_properties_transform::
obtain_cpp_headers_output_directory(const type_group& tg,
    const variability::annotation& ra) {
    const variability::entry_selector s(ra);

    if (s.has_entry(tg.cpp_headers_output_directory))
        return s.get_text_content(tg.cpp_headers_output_directory);

    return boost::filesystem::path();
}

std::unordered_set<std::string>
extraction_properties_transform::obtain_enabled_backends(const type_group& tg,
    const variability::annotation& ra) {
    std::unordered_set<std::string> r;
    const variability::entry_selector s(ra);
    for (const auto& t : tg.enabled) {
        const bool enabled(s.get_boolean_content_or_default(t));
        if (!enabled)
            continue;

        r.insert(t.archetype_location().backend());
    }

    return r;
}

bool extraction_properties_transform::obtain_enable_backend_directories(
    const type_group& tg, const variability::annotation& ra) {
    const variability::entry_selector s(ra);
    return s.get_boolean_content_or_default(tg.enable_backend_directories);
}

meta_model::extraction_properties extraction_properties_transform::
make_extraction_properties(const context& ctx,
    const std::list<archetypes::location>& als,
    const variability::annotation& ra) {

    const auto tg(make_type_group(*ctx.type_repository(), als));
    meta_model::extraction_properties r;
    r.cpp_headers_output_directory(obtain_cpp_headers_output_directory(tg, ra));

    r.enabled_backends(obtain_enabled_backends(tg, ra));
    if (r.enabled_backends().size() > 1) {
        BOOST_LOG_SEV(lg, warn) << "More than one backend is enabled: "
                                << r.enabled_backends().size()
                                << ". Forcing enable_backend_directories.";
        r.enable_backend_directories(true);
    } else
        r.enable_backend_directories(obtain_enable_backend_directories(tg, ra));

    return r;
}

extraction_properties_transform::feature_group
extraction_properties_transform::make_feature_group(
    const variability::meta_model::feature_model& fm,
    const std::list<archetypes::location>& als) {
    feature_group r;
    const variability::helpers::feature_selector s(fm);

    const auto chod(traits::extraction::cpp_headers_output_directory());
    r.cpp_headers_output_directory = s.get_by_name(chod);

    const auto ekd(traits::extraction::enable_backend_directories());
    r.enable_backend_directories = s.get_by_name(ekd);

    const auto en(traits::enabled());
    for (const auto al : als) {
        type_group tg;
        const auto backend(al.backend());
        r.enabled.push_back(s.get_by_name(backend, en));
    }

    return r;
}

boost::filesystem::path extraction_properties_transform::
obtain_cpp_headers_output_directory(const feature_group& fg,
    const variability::meta_model::configuration& cfg) {
    const variability::helpers::configuration_selector s(cfg);

    if (s.has_configuration_point(fg.cpp_headers_output_directory))
        return s.get_text_content(fg.cpp_headers_output_directory);

    return boost::filesystem::path();
}

std::unordered_set<std::string>
extraction_properties_transform::
obtain_enabled_backends(const feature_group& fg,
    const variability::meta_model::configuration& cfg) {
    std::unordered_set<std::string> r;
    const variability::helpers::configuration_selector s(cfg);
    for (const auto& f : fg.enabled) {
        const bool enabled(s.get_boolean_content_or_default(f));
        if (!enabled)
            continue;

        r.insert(f.location().backend());
    }

    return r;
}

bool extraction_properties_transform::
obtain_enable_backend_directories(const feature_group& fg,
    const variability::meta_model::configuration& cfg) {
    const variability::helpers::configuration_selector s(cfg);
    return s.get_boolean_content_or_default(fg.enable_backend_directories);
}

meta_model::extraction_properties extraction_properties_transform::
make_extraction_properties(const context& ctx,
    const std::list<archetypes::location>& als,
    const variability::meta_model::configuration& cfg) {

    const auto fg(make_feature_group(*ctx.feature_model(), als));
    meta_model::extraction_properties r;
    r.cpp_headers_output_directory(obtain_cpp_headers_output_directory(fg, cfg));

    r.enabled_backends(obtain_enabled_backends(fg, cfg));
    if (r.enabled_backends().size() > 1) {
        BOOST_LOG_SEV(lg, warn) << "More than one backend is enabled: "
                                << r.enabled_backends().size()
                                << ". Forcing enable_backend_directories.";
        r.enable_backend_directories(true);
    } else
        r.enable_backend_directories(obtain_enable_backend_directories(fg, cfg));

    return r;
}

void extraction_properties_transform::apply(const context& ctx,
    meta_model::model& m) {

    const auto& alrp(*ctx.archetype_location_repository());
    const auto& als(alrp.all());

    if (ctx.use_configuration()) {
        const auto& cfg(*m.root_module()->configuration());
        const auto ep(make_extraction_properties(ctx, als, cfg));
        m.extraction_properties(ep);
    } else {
        const auto& ra(m.root_module()->annotation());
        const auto ep(make_extraction_properties(ctx, als, ra));
        m.extraction_properties(ep);
    }
}

}
