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
#include "dogen.physical/types/helpers/meta_name_factory.hpp"
#include "dogen.logical/types/entities/structural/primitive.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.m2t.cpp/types/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/types/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/hash/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/inclusion_constants.hpp"
#include "dogen.m2t.cpp/types/transforms/assistant.hpp"
#include "dogen.m2t.cpp/types/transforms/hash/primitive_header_transform.hpp"

namespace dogen::m2t::cpp::transforms::hash {

std::string primitive_header_transform::static_id() {
    return traits::primitive_header_archetype_qn();
}

std::string primitive_header_transform::id() const {
    return static_id();
}

physical::entities::meta_name
primitive_header_transform::physical_meta_name() const {
    using physical::helpers::meta_name_factory;
    static auto r(meta_name_factory::make(cpp::traits::backend_sn(),
        traits::facet_sn(), traits::primitive_header_archetype_sn()));
    return r;
}

const logical::entities::name& primitive_header_transform::logical_meta_name() const {
    using logical::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_primitive_name());
    return r;
}

inclusion_support_types primitive_header_transform::inclusion_support_type() const {
    return inclusion_support_types::canonical_support;
}

boost::filesystem::path primitive_header_transform::inclusion_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_inclusion_path_for_cpp_header(n, static_id());
}

boost::filesystem::path primitive_header_transform::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path_for_cpp_header(n, static_id());
}

std::list<std::string> primitive_header_transform::inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const logical::entities::element& e) const {

    auto builder(f.make());
    builder.add(inclusion_constants::std::functional());
    builder.add(e.name(), types::traits::canonical_archetype());
    return builder.build();
}

void primitive_header_transform::apply(const context& ctx, const logical::entities::element& e,
    physical::entities::artefact& a) const {
    assistant ast(ctx, e, physical_meta_name(), true/*requires_header_guard*/, a);
    const auto& p(ast.as<logical::entities::structural::primitive>(e));

    const auto sn(p.name().simple());
    const auto qn(ast.get_qualified_name(p.name()));
    {

        auto sbf(ast.make_scoped_boilerplate_formatter(e));
        {
            const auto ns(ast.make_namespaces(p.name()));
            auto snf(ast.make_scoped_namespace_formatter(ns));
ast.stream() << std::endl;
ast.stream() << "struct " << sn << "_hasher {" << std::endl;
ast.stream() << "public:" << std::endl;
ast.stream() << "    static std::size_t hash(const " << sn << "& v);" << std::endl;
ast.stream() << "};" << std::endl;
ast.stream() << std::endl;
        } // snf
ast.stream() << std::endl;
ast.stream() << "namespace std {" << std::endl;
ast.stream() << std::endl;
ast.stream() << "template<>" << std::endl;
ast.stream() << "struct hash<" << qn << "> {" << std::endl;
ast.stream() << "public:" << std::endl;
ast.stream() << "    size_t operator()(const " << qn << "& v) const {" << std::endl;
ast.stream() << "        return " << qn << "_hasher::hash(v);" << std::endl;
ast.stream() << "    }" << std::endl;
ast.stream() << "};" << std::endl;
ast.stream() << std::endl;
ast.stream() << "}" << std::endl;
    } // sbf
    ast.update_artefact();
}
}
