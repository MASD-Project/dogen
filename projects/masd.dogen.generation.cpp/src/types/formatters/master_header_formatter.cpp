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
#include "dogen.generation.cpp/types/formatters/master_header_formatter.hpp"
#include "dogen.generation.cpp/types/formatters/assistant.hpp"
#include "dogen.generation.cpp/types/formatters/traits.hpp"
#include "dogen.generation.cpp/types/traits.hpp"
#include "dogen.generation.cpp/types/formatters/assistant.hpp"
#include "dogen.generation.cpp/types/fabric/master_header.hpp"
#include "dogen.generation.cpp/types/fabric/meta_name_factory.hpp"
#include "dogen.formatting/types/sequence_formatter.hpp"
#include <boost/make_shared.hpp>

namespace dogen::generation::cpp::formatters {

master_header_formatter::master_header_formatter(const std::string& facet_name)
    : archetype_location_(cpp::traits::kernel(), cpp::traits::backend(),
          facet_name, traits::master_header_archetype(facet_name)) { }

std::string master_header_formatter::id() const {
    return archetype_location().archetype();
}

annotations::archetype_location
master_header_formatter::archetype_location() const {
    return archetype_location_;
}

const modeling::meta_model::name& master_header_formatter::meta_name() const {
    static auto r(fabric::meta_name_factory::make_master_header_name());
    return r;
}

std::string master_header_formatter::family() const {
    return cpp::traits::header_family();
}

inclusion_support_types
master_header_formatter::inclusion_support_type() const {
    return inclusion_support_types::regular_support;
}

boost::filesystem::path master_header_formatter::inclusion_path(
    const formattables::locator& l, const modeling::meta_model::name& n) const {
    const auto arch(archetype_location_.archetype());
    return l.make_inclusion_path_for_cpp_header(n, arch);
}

boost::filesystem::path master_header_formatter::full_path(
    const formattables::locator& l, const modeling::meta_model::name& n) const {
    const auto arch(archetype_location_.archetype());
    return l.make_full_path_for_cpp_header(n, arch);
}

std::list<std::string> master_header_formatter::inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const modeling::meta_model::element& e) const {
    const auto fct(archetype_location_.facet());
    const auto& mh(assistant::as<fabric::master_header>(e));

    const auto i(mh.inclusion_by_facet().find(fct));
    if (i == mh.inclusion_by_facet().end())
        return std::list<std::string>();

    auto builder(f.make());
    for (const auto& pair : i->second) {
        const auto& arch(pair.first);
        const auto& names(pair.second);
        builder.add(names, arch);
    }
    return builder.build();
}

modeling::meta_model::artefact master_header_formatter::
format(const context& ctx, const modeling::meta_model::element& e) const {
    assistant a(ctx, e, archetype_location(), false/*requires_header_guard*/);

    {
        auto sbf(a.make_scoped_boilerplate_formatter(e));
a.stream() << std::endl;
    } // sbf
    return a.make_artefact();
}
}
