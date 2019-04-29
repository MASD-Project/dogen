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
#include <boost/throw_exception.hpp>
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen.utility/types/string/splitter.hpp"
#include "masd.dogen.variability/types/helpers/feature_selector.hpp"
#include "masd.dogen.variability/types/helpers/configuration_selector.hpp"
#include "masd.dogen.templating/types/stitch/traits.hpp"
#include "masd.dogen.templating/types/stitch/building_error.hpp"
#include "masd.dogen.templating/types/stitch/properties_factory.hpp"

namespace {

using namespace masd::dogen::utility::log;
auto lg(logger_factory("templating.stitch.properties_factory"));

const std::string field_definition_not_found(
    "Could not find expected field definition: ");

}

namespace masd::dogen::templating::stitch {

properties_factory::properties_factory(
    const variability::meta_model::feature_model& fm)
    : feature_group_(make_feature_group(fm)) {}

properties_factory::feature_group properties_factory::make_feature_group(
    const variability::meta_model::feature_model& fm) const {
    feature_group r;
    const variability::helpers::feature_selector s(fm);

    const auto& svn(traits::stream_variable_name());
    r.stream_variable_name = s.get_by_name(svn);

    const auto& rod(traits::relative_output_directory());
    r.relative_output_directory = s.get_by_name(rod);

    const auto& id(traits::inclusion_dependency());
    r.inclusion_dependency = s.get_by_name(id);

    const auto cn(traits::containing_namespaces());
    r.containing_namespaces = s.get_by_name(cn);

    const auto wt(traits::wale_template());
    r.wale_template = s.get_by_name(wt);

    const auto wkvp(traits::wale_kvp());
    r.wale_kvp = s.get_by_name(wkvp);

    return r;
}

std::string properties_factory::
extract_stream_variable_name(
    const variability::meta_model::configuration& cfg) const {
    const variability::helpers::configuration_selector s(cfg);
    const auto& tg(feature_group_);
    return s.get_text_content_or_default(tg.stream_variable_name);
}

boost::filesystem::path
properties_factory::extract_relative_output_directory(
    const variability::meta_model::configuration& cfg) const {
    const variability::helpers::configuration_selector s(cfg);
    if (!s.has_configuration_point(traits::relative_output_directory()))
        return boost::filesystem::path();

    const auto text(s.get_text_content(traits::relative_output_directory()));
    return boost::filesystem::path(text);
}

std::list<std::string>
properties_factory::extract_inclusion_dependencies(
    const variability::meta_model::configuration& cfg) const {
    std::list<std::string> r;
    const variability::helpers::configuration_selector s(cfg);
    const auto& f(feature_group_.inclusion_dependency);
    if (!s.has_configuration_point(f))
        return r;

    return s.get_text_collection_content(f);
}

std::list<std::string>
properties_factory::extract_containing_namespaces(
    const variability::meta_model::configuration& cfg) const {
    std::list<std::string> r;
    const variability::helpers::configuration_selector s(cfg);
    const auto& f(feature_group_.containing_namespaces);
    if (!s.has_configuration_point(f))
        return r;

    const auto cns(s.get_text_content(f));
    if (cns.empty())
        return r;

    using utility::string::splitter;
    return splitter::split_scoped(cns);
}

std::string properties_factory::
extract_wale_template(const variability::meta_model::configuration& cfg) const {
    std::string r;
    const variability::helpers::configuration_selector s(cfg);
    const auto& f(feature_group_.wale_template);
    if (!s.has_configuration_point(f))
        return r;

    return s.get_text_content(f);
}

std::unordered_map<std::string, std::string> properties_factory::
extract_wale_kvps(const variability::meta_model::configuration& cfg) const {
    std::unordered_map<std::string, std::string>  r;
    const variability::helpers::configuration_selector s(cfg);
    const auto& f(feature_group_.wale_kvp);
    if (!s.has_configuration_point(f))
        return r;

    return s.get_kvp_content(f);
}

properties properties_factory::
make(const variability::meta_model::configuration& cfg) const {
    properties r;
    r.stream_variable_name(extract_stream_variable_name(cfg));
    r.relative_output_directory(extract_relative_output_directory(cfg));
    r.inclusion_dependencies(extract_inclusion_dependencies(cfg));
    r.containing_namespaces(extract_containing_namespaces(cfg));
    r.wale_template(extract_wale_template(cfg));
    r.wale_kvps(extract_wale_kvps(cfg));
    return r;
}

}
