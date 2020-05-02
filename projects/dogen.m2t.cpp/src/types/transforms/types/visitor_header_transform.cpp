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
#include "dogen.logical/types/entities/structural/visitor.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.m2t.cpp/types/transforms/assistant.hpp"
#include "dogen.m2t.cpp/types/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/inclusion_constants.hpp"
#include "dogen.m2t.cpp/types/transforms/io/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/serialization/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/types/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/hash/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/types/visitor_header_transform.hpp"

namespace dogen::m2t::cpp::transforms::types {

std::string visitor_header_transform::static_id() {
    return traits::visitor_header_archetype_qn();
}

std::string visitor_header_transform::id() const {
    return static_id();
}

physical::entities::meta_name
visitor_header_transform::physical_meta_name() const {
    using physical::helpers::meta_name_factory;
    static auto r(meta_name_factory::make(cpp::traits::backend_sn(),
        traits::facet_sn(), traits::visitor_header_archetype_sn()));
    return r;
}

const logical::entities::name& visitor_header_transform::logical_meta_name() const {
    using logical::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_visitor_name());
    return r;
}

physical::entities::archetype visitor_header_transform::archetype() const {
    static physical::entities::archetype r([]() {
        physical::entities::archetype r;
        using physical::helpers::meta_name_factory;
        r.meta_name(meta_name_factory::make(cpp::traits::backend_sn(),
            traits::facet_sn(), traits::visitor_header_archetype_sn()));
        return r;
    }());
    return r;
}

inclusion_support_types visitor_header_transform::inclusion_support_type() const {
    return inclusion_support_types::canonical_support;
}

boost::filesystem::path visitor_header_transform::inclusion_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_inclusion_path_for_cpp_header(n, static_id());
}

boost::filesystem::path visitor_header_transform::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path_for_cpp_header(n, static_id());
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
    assistant ast(ctx, e, physical_meta_name(), true/*requires_header_guard*/, a);
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
}

}
