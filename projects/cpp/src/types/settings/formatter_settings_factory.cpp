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
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/dynamic/schema/types/field_selector.hpp"
#include "dogen/dynamic/schema/types/repository_selector.hpp"
#include "dogen/cpp/types/traits.hpp"
#include "dogen/cpp/types/formatters/workflow.hpp"
#include "dogen/cpp/types/settings/building_error.hpp"
#include "dogen/cpp/types/settings/formatter_settings_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory(
        "cpp.settings.formatter_settings_factory"));

}

namespace dogen {
namespace cpp {
namespace settings {

formatter_settings_factory::formatter_settings_factory(
    const dynamic::schema::repository& rp)
    : formatter_properties_(make_formatter_properties(rp)) { }

formatter_settings_factory::formatter_properties
formatter_settings_factory::make_formatter_properties(
    const dynamic::schema::repository& rp,
    const std::string& formatter_name) const {

    formatter_properties r;
    const auto& fn(formatter_name);
    const dynamic::schema::repository_selector s(rp);
    r.enabled = s.select_field_by_name(fn, traits::enabled());
    r.file_path = s.select_field_by_name(fn, traits::file_path());
    r.header_guard = s.try_select_field_by_name(fn, traits::header_guard());

    const auto& id(traits::inclusion_dependency());
    r.inclusion_dependency = s.try_select_field_by_name(fn, id);

    const auto& ifct(traits::integrated_facet());
    r.integrated_facet = s.try_select_field_by_name(fn, ifct);

    return r;
}

std::unordered_map<
    std::string, formatter_settings_factory::formatter_properties
    >
formatter_settings_factory::make_formatter_properties(
    const dynamic::schema::repository& rp) const {
    const auto& c(formatters::workflow::registrar().formatter_container());
    std::unordered_map<std::string, formatter_properties> r;

    for (const auto& f : c.all_formatters()) {
        const auto oh(f->ownership_hierarchy());
        const auto& fn(oh.formatter_name());
        r[fn] = make_formatter_properties(rp, fn);
    }
    return r;
}

formatter_settings formatter_settings_factory::
create_settings_for_formatter(const formatter_properties& fp,
    const dynamic::schema::object& o) const {

    using namespace dynamic::schema;
    const field_selector fs(o);

    formatter_settings r;
    r.enabled(fs.get_boolean_content_or_default(fp.enabled));
    r.file_path(fs.get_text_content(fp.file_path));

    if (fp.header_guard)
        r.header_guard(fs.get_text_content(*fp.header_guard));

    if (fp.inclusion_dependency && fs.has_field(*fp.inclusion_dependency)) {
        r.inclusion_dependencies(
            fs.get_text_collection_content(*fp.inclusion_dependency));
    }

    if (fp.integrated_facet && fs.has_field(*fp.integrated_facet)) {
        const auto fcts(
            fs.get_text_collection_content(*fp.inclusion_dependency));

        for (const auto f : fcts)
            r.integrated_facets().insert(f);
    }

    return r;
}

std::unordered_map<std::string, formatter_settings>
formatter_settings_factory::
make(const dynamic::schema::object& o) const {
    std::unordered_map<std::string, formatter_settings> r;
    for (const auto& pair : formatter_properties_) {
        const auto s(create_settings_for_formatter(pair.second, o));
        r.insert(std::make_pair(pair.first, s));
    }
    return r;
}

} } }
