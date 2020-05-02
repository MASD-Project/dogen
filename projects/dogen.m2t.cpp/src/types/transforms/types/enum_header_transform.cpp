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
#include "dogen.logical/types/entities/structural/enumeration.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.m2t/types/formatters/sequence_formatter.hpp"
#include "dogen.m2t.cpp/types/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/types/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/assistant.hpp"
#include "dogen.m2t.cpp/types/transforms/types/enum_header_transform.hpp"
#include "dogen.m2t.cpp/types/transforms/types/enum_header_transform.hpp"

namespace dogen::m2t::cpp::transforms::types {

physical::entities::archetype enum_header_transform::static_archetype() const {
    static physical::entities::archetype r([]() {
        physical::entities::archetype r;
        using pmnf = physical::helpers::meta_name_factory;
        r.meta_name(pmnf::make(cpp::traits::backend_sn(),
            traits::facet_sn(), traits::enum_header_archetype_sn()));
        using lmnf = logical::helpers::meta_name_factory;
        r.logical_meta_element_id(lmnf::make_enumeration_name().qualified().dot());
        return r;
    }());
    return r;
}

physical::entities::archetype enum_header_transform::archetype() const {
    return static_archetype();
}

inclusion_support_types enum_header_transform::inclusion_support_type() const {
    return inclusion_support_types::canonical_support;
}

boost::filesystem::path enum_header_transform::inclusion_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_inclusion_path_for_cpp_header(n, archetype().meta_name().qualified());
}

boost::filesystem::path enum_header_transform::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path_for_cpp_header(n, archetype().meta_name().qualified());
}

std::list<std::string> enum_header_transform::inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const logical::entities::element& e) const {

    using logical::entities::structural::enumeration;
    const auto& en(assistant::as<enumeration>(e));
    auto builder(f.make());
    const auto arch(traits::canonical_archetype());
    builder.add(en.underlying_element(), arch);
    return builder.build();
}

void enum_header_transform::apply(const context& ctx, const logical::entities::element& e,
    physical::entities::artefact& a) const {
    assistant ast(ctx, e, archetype().meta_name(), true/*requires_header_guard*/, a);
    const auto& ye(ast.as<logical::entities::structural::enumeration>(e));

    {
        auto sbf(ast.make_scoped_boilerplate_formatter(e));
        {
            const auto ns(ast.make_namespaces(e.name()));
            auto snf(ast.make_scoped_namespace_formatter(ns));
ast.stream() << std::endl;
            ast.comment(e.documentation());
            if (ast.is_cpp_standard_98()) {
ast.stream() << "enum " << ye.name().simple() << " {" << std::endl;
            } else {
                if (ye.use_implementation_defined_underlying_element())
ast.stream() << "enum class " << ye.name().simple() << " {" << std::endl;
                else
ast.stream() << "enum class " << ye.name().simple() << " : " << ast.get_qualified_name(ye.underlying_element()) << " {" << std::endl;
            }

            m2t::formatters::sequence_formatter sf(ye.enumerators().size());
            for (const auto& en : ye.enumerators()) {
                if (ye.use_implementation_defined_enumerator_values())
ast.stream() << "    " << en.name().simple() << sf.postfix() << ast.comment_inline(en.documentation()) << std::endl;
                else
ast.stream() << "    " << en.name().simple() << " = " << en.value() << sf.postfix() << ast.comment_inline(en.documentation()) << std::endl;
                sf.next();
            }
ast.stream() << "};" << std::endl;
ast.stream() << std::endl;
        } // snf
ast.stream() << std::endl;
    } // sbf
    ast.update_artefact();
}

}
