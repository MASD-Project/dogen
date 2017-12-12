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
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/string/splitter.hpp"
#include "dogen/annotations/types/entry_selector.hpp"
#include "dogen/annotations/types/type_repository_selector.hpp"
#include "dogen/stitch/types/traits.hpp"
#include "dogen/stitch/types/building_error.hpp"
#include "dogen/stitch/types/stitching_properties_factory.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("stitch.stitching_properties_factory"));

const std::string field_definition_not_found(
    "Could not find expected field definition: ");

}

namespace dogen {
namespace stitch {

stitching_properties_factory::
stitching_properties_factory(const annotations::type_repository& arp)
    : type_group_(make_type_group(arp)) {}

stitching_properties_factory::type_group
stitching_properties_factory::make_type_group(
    const annotations::type_repository& arp) const {
    type_group r;
    const annotations::type_repository_selector s(arp);

    const auto& svn(traits::stream_variable_name());
    r.stream_variable_name = s.select_type_by_name(svn);

    const auto& rod(traits::relative_output_directory());
    r.relative_output_directory = s.select_type_by_name(rod);

    const auto& id(traits::inclusion_dependency());
    r.inclusion_dependency = s.select_type_by_name(id);

    const auto cn(traits::containing_namespaces());
    r.containing_namespaces = s.select_type_by_name(cn);

    const auto wt(traits::wale_template());
    r.wale_template = s.select_type_by_name(wt);

    const auto wkvp(traits::wale_kvp());
    r.wale_kvp = s.select_type_by_name(wkvp);

    return r;
}

std::string stitching_properties_factory::
extract_stream_variable_name(const annotations::annotation& a) const {
    using namespace annotations;
    const entry_selector s(a);
    const auto& tg(type_group_);
    return s.get_text_content_or_default(tg.stream_variable_name);
}

boost::filesystem::path stitching_properties_factory::
extract_relative_output_directory(const annotations::annotation& a) const {
    using namespace annotations;
    const entry_selector s(a);
    if (!s.has_entry(traits::relative_output_directory()))
        return boost::filesystem::path();

    const auto text(s.get_text_content(traits::relative_output_directory()));
    return boost::filesystem::path(text);
}

std::list<std::string> stitching_properties_factory::
extract_inclusion_dependencies(const annotations::annotation& a) const {
    std::list<std::string> r;
    using namespace annotations;
    const entry_selector s(a);
    const auto& t(type_group_.inclusion_dependency);
    if (!s.has_entry(t))
        return r;

    return s.get_text_collection_content(t);
}

std::list<std::string> stitching_properties_factory::
extract_containing_namespaces(const annotations::annotation& a) const {
    std::list<std::string> r;
    using namespace annotations;
    const entry_selector s(a);
    const auto& t(type_group_.containing_namespaces);
    if (!s.has_entry(t))
        return r;

    const auto cns(s.get_text_content(t));
    if (cns.empty())
        return r;

    using utility::string::splitter;
    return splitter::split_scoped(cns);
}

std::string stitching_properties_factory::
extract_wale_template(const annotations::annotation& a) const {
    std::string r;
    using namespace annotations;
    const entry_selector s(a);
    const auto& t(type_group_.wale_template);
    if (!s.has_entry(t))
        return r;

    return s.get_text_content(t);
}

std::unordered_map<std::string, std::string> stitching_properties_factory::
extract_wale_kvps(const annotations::annotation& a) const {
    std::unordered_map<std::string, std::string>  r;
    using namespace annotations;
    const entry_selector s(a);
    const auto& t(type_group_.wale_kvp);
    if (!s.has_entry(t))
        return r;

    return s.get_kvp_content(t);
}

stitching_properties stitching_properties_factory::
make(const annotations::annotation& a) const {
    stitching_properties r;
    r.stream_variable_name(extract_stream_variable_name(a));
    r.relative_output_directory(extract_relative_output_directory(a));
    r.inclusion_dependencies(extract_inclusion_dependencies(a));
    r.containing_namespaces(extract_containing_namespaces(a));
    r.wale_template(extract_wale_template(a));
    r.wale_kvps(extract_wale_kvps(a));
    return r;
}

} }
