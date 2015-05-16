/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include "dogen/dynamic/types/field_selector.hpp"
#include "dogen/dynamic/types/repository_selector.hpp"
#include "dogen/cpp/types/traits.hpp"
#include "dogen/cpp/types/formattables/formatter_properties_factory.hpp"

namespace dogen {
namespace cpp {
namespace formattables {

formatter_properties_factory::formatter_properties_factory(
    const dynamic::repository& rp,
    const dynamic::object& root_object,
    const formatters::container& fc)
    : integrated_facets_(obtain_integrated_facets(rp, root_object, fc)) {}

std::unordered_map<std::string, std::unordered_set<std::string> >
formatter_properties_factory::
obtain_integrated_facets(const dynamic::repository& rp,
    const dynamic::object& root_object,
    const formatters::container& fc) const {

    const dynamic::field_selector fs(root_object);
    const dynamic::repository_selector s(rp);
    const auto& ifct(traits::integrated_facet());
    std::unordered_map<std::string, std::unordered_set<std::string> > r;
    for (const auto& f : fc.all_formatters()) {
        const auto oh(f->ownership_hierarchy());
        const auto& fn(oh.formatter_name());
        const auto iffd(s.try_select_field_by_name(fn, ifct));

        if (!iffd)
            continue;

        if (fs.has_field(*iffd)) {
            const auto fcts(fs.get_text_collection_content(*iffd));
            std::unordered_set<std::string> set;
            for (const auto f : fcts)
                set.insert(f);
            r[fn] = set;
        }
    }
    return r;
}

std::unordered_map<std::string, formatter_properties>
formatter_properties_factory::make(
    const std::unordered_map<std::string, path_derivatives>&
    path_derivatives,
    const std::unordered_map<std::string, std::list<std::string> >&
    inclusion_dependencies,
    const std::unordered_map<std::string, bool>& enablement) const {

    std::unordered_map<std::string, formatter_properties> r;
    for (const auto& pair : path_derivatives) {
        r[pair.first].file_path(pair.second.file_path());
        r[pair.first].header_guard(pair.second.header_guard());
    }

    for (const auto& pair : inclusion_dependencies)
        r[pair.first].inclusion_dependencies(pair.second);

    for (const auto& pair : integrated_facets_)
        r[pair.first].integrated_facets(pair.second);

    for (const auto& pair : enablement)
        r[pair.first].enabled(pair.second);

    return r;
}

} } }
