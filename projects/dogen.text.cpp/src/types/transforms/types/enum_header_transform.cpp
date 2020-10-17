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
#include "dogen.utility/types/io/shared_ptr_io.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.logical/io/entities/element_io.hpp"
#include "dogen.physical/io/entities/artefact_io.hpp"
#include "dogen.identification/types/helpers/physical_meta_name_factory.hpp"
#include "dogen.logical/types/entities/structural/enumeration.hpp"
#include "dogen.identification/types/helpers/logical_meta_name_factory.hpp"
#include "dogen.utility/types/formatters/sequence_formatter.hpp"
#include "dogen.text.cpp/types/traits.hpp"
#include "dogen.text.cpp/types/transforms/traits.hpp"
#include "dogen.text.cpp/types/transforms/types/traits.hpp"
#include "dogen.text.cpp/types/transforms/assistant.hpp"
#include "dogen.text.cpp/types/transforms/types/enum_header_transform.hpp"
#include "dogen.text.cpp/types/transforms/types/enum_header_factory.hpp"

namespace dogen::text::cpp::transforms::types {
namespace {

const std::string transform_id("text.cpp.transforms.types.enum_header_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

const physical::entities::archetype& enum_header_transform::static_archetype() {
    static auto r(enum_header_factory::make());
    return r;
}

const physical::entities::archetype& enum_header_transform::archetype() const {
    return static_archetype();
}

inclusion_support_types enum_header_transform::inclusion_support_type() const {
    return inclusion_support_types::canonical_support;
}

boost::filesystem::path enum_header_transform::inclusion_path(
    const formattables::locator& l, const identification::entities::logical_name& n) const {
    return l.make_inclusion_path_for_cpp_header(n, archetype().meta_name().id().value());
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
    tracing::scoped_transform_tracer stp(lg, "enum header",
        transform_id, e.name().qualified().dot(), *ctx.tracer(), e);

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

            utility::formatters::sequence_formatter sf(ye.enumerators().size());
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
    stp.end_transform(a);
}

}
