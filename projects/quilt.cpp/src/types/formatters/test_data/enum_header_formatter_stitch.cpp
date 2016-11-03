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
#include "dogen/quilt.cpp/types/formatters/test_data/enum_header_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/assistant.hpp"
#include "dogen/quilt.cpp/types/formatters/inclusion_constants.hpp"
#include "dogen/quilt.cpp/types/formatters/test_data/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/types/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/traits.hpp"
#include "dogen/formatters/types/sequence_formatter.hpp"
#include "dogen/yarn/types/enumeration.hpp"
#include <boost/make_shared.hpp>
#include <typeinfo>

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace test_data {

std::string enum_header_formatter::static_artefact() {
    return traits::enum_header_archetype();
}

std::string enum_header_formatter::formatter_name() const {
    static auto r(archetype_location().archetype());
    return r;
}

annotations::archetype_location enum_header_formatter::
archetype_location() const {
    static annotations::archetype_location
        r(formatters::traits::kernel(), traits::facet(),
            enum_header_formatter::static_artefact());
    return r;
}

std::type_index enum_header_formatter::element_type_index() const {
    static auto r(std::type_index(typeid(yarn::enumeration)));
    return r;
}

inclusion_support_types enum_header_formatter::inclusion_support_type() const {
    return inclusion_support_types::canonical_support;
}

boost::filesystem::path enum_header_formatter::inclusion_path(
    const formattables::locator& l, const yarn::name& n) const {
    return l.make_inclusion_path_for_cpp_header(n, static_artefact());
}

boost::filesystem::path enum_header_formatter::full_path(
    const formattables::locator& l, const yarn::name& n) const {
    return l.make_full_path_for_cpp_header(n, static_artefact());
}

std::list<std::string> enum_header_formatter::inclusion_dependencies(
    const formattables::inclusion_dependencies_builder_factory& f,
    const yarn::element& e) const {
    auto builder(f.make());

    builder.add(e.name(), types::traits::enum_header_archetype());
    return builder.build();
}

dogen::formatters::artefact enum_header_formatter::
format(const context& ctx, const yarn::element& e) const {
    const auto id(e.name().id());
    assistant a(ctx, archetype_location(), true/*requires_header_guard*/, id);
    const auto& ye(a.as<yarn::enumeration>(static_artefact(), e));

    {
        auto sbf(a.make_scoped_boilerplate_formatter());
        {
            const auto ns(a.make_namespaces(ye.name()));
            auto snf(a.make_scoped_namespace_formatter(ns));
a.stream() << std::endl;
a.stream() << "class " << ye.name().simple() << "_generator {" << std::endl;
a.stream() << "public:" << std::endl;
a.stream() << "    " << ye.name().simple() << "_generator();" << std::endl;
a.stream() << std::endl;
a.stream() << "public:" << std::endl;
a.stream() << "    typedef " << a.get_qualified_name(ye.name()) << " result_type;" << std::endl;
a.stream() << std::endl;
a.stream() << "public:" << std::endl;
a.stream() << "    static void populate(const unsigned int position, result_type& v);" << std::endl;
a.stream() << "    static result_type create(const unsigned int position);" << std::endl;
a.stream() << "    result_type operator()();" << std::endl;
a.stream() << std::endl;
a.stream() << "private:" << std::endl;
a.stream() << "    unsigned int position_;" << std::endl;
a.stream() << "};" << std::endl;
a.stream() << std::endl;
         } // snf
a.stream() << std::endl;
    } // sbf
    return a.make_artefact();
}

} } } } }
