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
#include <typeinfo>
#include <boost/make_shared.hpp>
#include "dogen/quilt.cpp/types/fabric/master_header.hpp"
#include "dogen/quilt.cpp/types/formatters/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/assistant.hpp"
#include "dogen/quilt.cpp/types/formatters/master_header_formatter_stitch.hpp"
#include "dogen/quilt.cpp/types/formatters/master_header_formatter.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {

master_header_formatter::master_header_formatter(const std::string& facet_name)
    : ownership_hierarchy_(formatters::traits::kernel(), facet_name,
        traits::master_header_archetype(facet_name)) { }

std::string master_header_formatter::formatter_name() const {
    return archetype_location().archetype();
}

annotations::archetype_location
master_header_formatter::archetype_location() const {
    return ownership_hierarchy_;
}

std::type_index master_header_formatter::element_type_index() const {
    auto r(std::type_index(typeid(fabric::master_header)));
    return r;
}

std::list<std::string> master_header_formatter::inclusion_dependencies(
    const formattables::inclusion_dependencies_builder_factory& f,
    const yarn::element& e) const {
    const auto fctn(ownership_hierarchy_.facet());
    const auto fmtn(ownership_hierarchy_.archetype());
    const auto& mh(assistant::as<fabric::master_header>(fmtn, e));

    const auto i(mh.inclusion_by_facet().find(fctn));
    if (i == mh.inclusion_by_facet().end())
        return std::list<std::string>();

    auto builder(f.make());
    for (const auto& pair : i->second) {
        const auto& fmtn(pair.first);
        const auto& names(pair.second);
        builder.add(names, fmtn);
    }
    return builder.build();
}

inclusion_support_types
master_header_formatter::inclusion_support_type() const {
    return inclusion_support_types::regular_support;
}

boost::filesystem::path master_header_formatter::inclusion_path(
    const formattables::locator& l, const yarn::name& n) const {
    const auto fmtn(ownership_hierarchy_.archetype());
    return l.make_inclusion_path_for_cpp_header(n, fmtn);
}

boost::filesystem::path master_header_formatter::full_path(
    const formattables::locator& l, const yarn::name& n) const {
    const auto fmtn(ownership_hierarchy_.archetype());
    return l.make_full_path_for_cpp_header(n, fmtn);
}

dogen::formatters::artefact master_header_formatter::
format(const context& ctx, const yarn::element& e) const {
    const auto id(e.name().id());
    assistant a(ctx, archetype_location(), false/*requires_header_guard*/, id);
    const auto fmtn(ownership_hierarchy_.archetype());
    const auto& mh(a.as<fabric::master_header>(fmtn, e));
    const auto r(master_header_formatter_stitch(a, mh));
    return r;
}

} } } }
