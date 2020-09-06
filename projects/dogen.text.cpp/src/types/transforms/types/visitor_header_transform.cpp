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
#include "dogen.logical/types/entities/structural/visitor.hpp"
#include "dogen.identification/types/helpers/logical_meta_name_factory.hpp"
#include "dogen.text.cpp/types/transforms/assistant.hpp"
#include "dogen.text.cpp/types/traits.hpp"
#include "dogen.text.cpp/types/transforms/traits.hpp"
#include "dogen.text.cpp/types/transforms/inclusion_constants.hpp"
#include "dogen.text.cpp/types/transforms/io/traits.hpp"
#include "dogen.text.cpp/types/transforms/serialization/traits.hpp"
#include "dogen.text.cpp/types/transforms/types/traits.hpp"
#include "dogen.text.cpp/types/transforms/hash/traits.hpp"
#include "dogen.text.cpp/types/transforms/types/visitor_header_transform.hpp"
#include "dogen.text.cpp/types/transforms/types/visitor_header_factory.hpp"

namespace dogen::text::cpp::transforms::types {
namespace {

const std::string transform_id("text.cpp.transforms.types.visitor_header_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

const physical::entities::archetype& visitor_header_transform::static_archetype() {
    static auto r(visitor_header_factory::make());
    return r;
}

const physical::entities::archetype& visitor_header_transform::archetype() const {
    return static_archetype();
}

inclusion_support_types visitor_header_transform::inclusion_support_type() const {
    return inclusion_support_types::canonical_support;
}

boost::filesystem::path visitor_header_transform::inclusion_path(
    const formattables::locator& l, const identification::entities::logical_name& n) const {
    return l.make_inclusion_path_for_cpp_header(n, archetype().meta_name().id().value());
}

boost::filesystem::path visitor_header_transform::full_path(
    const formattables::locator& l, const identification::entities::logical_name& n) const {
    return l.make_full_path_for_cpp_header(n, archetype().meta_name().id().value());
}

std::list<std::string> visitor_header_transform::inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const logical::entities::element& e) const {
    using logical::entities::structural::visitor;
    const auto& v(assistant::as<visitor>(e));
    auto builder(f.make());
    builder.add(v.visits(), traits::class_forward_declarations_archetype_qn());

    if (v.parent())
        builder.add(*v.parent(), traits::visitor_header_archetype_qn());

    return builder.build();
}

void visitor_header_transform::apply(const context& ctx, const logical::entities::element& e,
    physical::entities::artefact& a) const {
    tracing::scoped_transform_tracer stp(lg, "visitor header transform",
        transform_id, e.name().qualified().dot(), *ctx.tracer(), e);

    assistant ast(ctx, e, archetype().meta_name(), true/*requires_header_guard*/, a);
    const auto& v(ast.as<logical::entities::structural::visitor>(e));

    {
        auto sbf(ast.make_scoped_boilerplate_formatter(e));
        {
            const auto ns(ast.make_namespaces(v.name()));
            auto snf(ast.make_scoped_namespace_formatter(ns));
ast.stream() << std::endl;
            ast.comment(v.documentation());
            if (!v.parent())
ast.stream() << "class " << v.name().simple() << " {" << std::endl;
            else {
                const auto& pn(*v.parent());
                const auto pqn(ast.get_qualified_name(pn));
ast.stream() << "class " << v.name().simple() << " : public " << pqn << " {" << std::endl;
            }
ast.stream() << "public:" << std::endl;
ast.stream() << "    virtual ~" << v.name().simple() << "()" << ast.make_noexcept_keyword_text() << " = 0;" << std::endl;
ast.stream() << std::endl;
ast.stream() << "public:" << std::endl;
            if (v.parent()) {
                const auto& pn(*v.parent());
                const auto pqn(ast.get_qualified_name(pn));
ast.stream() << "    using " << pqn << "::visit;" << std::endl;
ast.stream() << std::endl;
            }

            bool is_first(true);
            for (const auto& t : v.visits()) {
                if (!is_first)
ast.stream() << std::endl;
                const auto qn(ast.get_qualified_name(t));
                const auto doc("Accept visits for type " + qn);
                ast.comment_start_method_group(doc);
ast.stream() << "    virtual void visit(const " << qn << "&) const { }" << std::endl;
ast.stream() << "    virtual void visit(const " << qn << "&) { }" << std::endl;
ast.stream() << "    virtual void visit(" << qn << "&) const { }" << std::endl;
ast.stream() << "    virtual void visit(" << qn << "&) { }" << std::endl;
                ast.comment_end_method_group(doc);
                is_first = false;
            }
ast.stream() << "};" << std::endl;
ast.stream() << std::endl;
ast.stream() << "inline " << v.name().simple() << "::~" << v.name().simple() << "()" << ast.make_noexcept_keyword_text() << " { }" << std::endl;
ast.stream() << std::endl;
        } // snf
ast.stream() << std::endl;
    } // sbf
    ast.update_artefact();
    stp.end_transform(a);
}

}
