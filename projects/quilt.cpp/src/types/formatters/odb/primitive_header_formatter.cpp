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
#include "dogen/quilt.cpp/types/formatters/odb/primitive_header_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/assistant.hpp"
#include "dogen/quilt.cpp/types/formatters/inclusion_constants.hpp"
#include "dogen/quilt.cpp/types/formatters/odb/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/types/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/traits.hpp"
#include "dogen/quilt.cpp/types/traits.hpp"
#include "dogen/yarn/types/helpers/meta_name_factory.hpp"
#include "dogen/yarn/types/meta_model/primitive.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace odb {

std::string primitive_header_formatter::static_artefact() {
    return traits::primitive_header_archetype();
}

std::string primitive_header_formatter::formatter_name() const {
    static auto r(archetype_location().archetype());
    return r;
}

annotations::archetype_location
primitive_header_formatter::archetype_location() const {
    static annotations::archetype_location
        r(cpp::traits::family(), cpp::traits::kernel(),
          traits::facet(),
          primitive_header_formatter::static_artefact());
    return r;
}

const yarn::meta_model::name& primitive_header_formatter::meta_name() const {
    using yarn::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_primitive_name());
    return r;
}

inclusion_support_types primitive_header_formatter::inclusion_support_type() const {
    return inclusion_support_types::canonical_support;
}

boost::filesystem::path primitive_header_formatter::inclusion_path(
    const formattables::locator& l, const yarn::meta_model::name& n) const {
    return l.make_inclusion_path_for_cpp_header(n, static_artefact());
}

boost::filesystem::path primitive_header_formatter::full_path(
    const formattables::locator& l, const yarn::meta_model::name& n) const {
    return l.make_full_path_for_cpp_header(n, static_artefact());
}

std::list<std::string> primitive_header_formatter::inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const yarn::meta_model::element& e) const {

    using yarn::meta_model::primitive;
    const auto& p(assistant::as<primitive>(static_artefact(), e));
    auto builder(f.make());
    builder.add(p.name(), types::traits::primitive_header_archetype());

    return builder.build();
}

dogen::formatters::artefact primitive_header_formatter::
format(const context& ctx, const yarn::meta_model::element& e) const {
    const auto id(e.name().id());
    assistant a(ctx, archetype_location(), true/*requires_header_guard*/, id);
    const auto& p(a.as<yarn::meta_model::primitive>(static_artefact(), e));

    {
        const auto sn(p.name().simple());
        const auto qn(a.get_qualified_name(p.name()));
        auto sbf(a.make_scoped_boilerplate_formatter(e));
        const auto top_level_pragmas(a.get_odb_pragmas());
        const auto attr(p.value_attribute());

        if (top_level_pragmas.empty()) {
a.stream() << "// class has no ODB pragmas defined." << std::endl;
a.stream() << std::endl;
        } else {
            {
                const auto ns(a.make_namespaces(p.name()));
                auto snf(a.make_scoped_namespace_formatter(ns));
a.stream() << std::endl;
a.stream() << "#ifdef ODB_COMPILER" << std::endl;
a.stream() << std::endl;
                for (const auto& pg : top_level_pragmas)
a.stream() << "#pragma db " << a.get_odb_type() << "(" << sn << ") " << pg << std::endl;

                bool is_first(true);
                const auto attr_level_pragmas(a.get_odb_pragmas(attr.name().id()));
                for (const auto pg : attr_level_pragmas) {
                        if (is_first)
a.stream() << std::endl;
                        is_first = false;
a.stream() << "#pragma db member(" << sn << "::" << a.make_member_variable_name(attr) << ") " << pg << std::endl;
                }
a.stream() << std::endl;
a.stream() << "#endif" << std::endl;
a.stream() << std::endl;
            }
a.stream() << std::endl;
        }
    } // sbf
    return a.make_artefact();
}

} } } } }
