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
#include "dogen/quilt.cpp/types/formatters/hash/primitive_header_formatter.hpp"
#include "dogen/quilt.cpp/types/formatters/assistant.hpp"
#include "dogen/quilt.cpp/types/formatters/inclusion_constants.hpp"
#include "dogen/quilt.cpp/types/formatters/hash/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/types/traits.hpp"
#include "dogen/quilt.cpp/types/formatters/traits.hpp"
#include "dogen/quilt.cpp/types/traits.hpp"
#include "dogen/yarn/types/helpers/meta_name_factory.hpp"
#include "dogen/yarn/types/meta_model/primitive.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace formatters {
namespace hash {

std::string primitive_header_formatter::static_id() {
    return traits::primitive_header_archetype();
}

std::string primitive_header_formatter::id() const {
    return static_id();
}

annotations::archetype_location
primitive_header_formatter::archetype_location() const {
    static annotations::archetype_location
        r(cpp::traits::kernel(), cpp::traits::backend(),
          traits::facet(),
          primitive_header_formatter::static_id());
    return r;
}

const yarn::meta_model::name& primitive_header_formatter::meta_name() const {
    using yarn::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_primitive_name());
    return r;
}

std::string primitive_header_formatter::family() const {
    return cpp::traits::header_family();
}

inclusion_support_types primitive_header_formatter::inclusion_support_type() const {
    return inclusion_support_types::canonical_support;
}

boost::filesystem::path primitive_header_formatter::inclusion_path(
    const formattables::locator& l, const yarn::meta_model::name& n) const {
    return l.make_inclusion_path_for_cpp_header(n, static_id());
}

boost::filesystem::path primitive_header_formatter::full_path(
    const formattables::locator& l, const yarn::meta_model::name& n) const {
    return l.make_full_path_for_cpp_header(n, static_id());
}

std::list<std::string> primitive_header_formatter::inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const yarn::meta_model::element& e) const {

    auto builder(f.make());
    builder.add(inclusion_constants::std::functional());
    builder.add(e.name(), types::traits::canonical_archetype());
    return builder.build();
}

yarn::meta_model::artefact primitive_header_formatter::
format(const context& ctx, const yarn::meta_model::element& e) const {
    assistant a(ctx, e, archetype_location(), true/*requires_header_guard*/);
    const auto& p(a.as<yarn::meta_model::primitive>(e));

    const auto sn(p.name().simple());
    const auto qn(a.get_qualified_name(p.name()));
    {

        auto sbf(a.make_scoped_boilerplate_formatter(e));
        {
            const auto ns(a.make_namespaces(p.name()));
            auto snf(a.make_scoped_namespace_formatter(ns));
a.stream() << std::endl;
a.stream() << "struct " << sn << "_hasher {" << std::endl;
a.stream() << "public:" << std::endl;
a.stream() << "    static std::size_t hash(const " << sn << "& v);" << std::endl;
a.stream() << "};" << std::endl;
a.stream() << std::endl;
        } // snf
a.stream() << std::endl;
a.stream() << "namespace std {" << std::endl;
a.stream() << std::endl;
a.stream() << "template<>" << std::endl;
a.stream() << "struct hash<" << qn << "> {" << std::endl;
a.stream() << "public:" << std::endl;
a.stream() << "    size_t operator()(const " << qn << "& v) const {" << std::endl;
a.stream() << "        return " << qn << "_hasher::hash(v);" << std::endl;
a.stream() << "    }" << std::endl;
a.stream() << "};" << std::endl;
a.stream() << std::endl;
a.stream() << "}" << std::endl;
    } // sbf
    return a.make_artefact();
}
} } } } }
