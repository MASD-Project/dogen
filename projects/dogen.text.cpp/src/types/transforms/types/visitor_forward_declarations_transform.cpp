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
#include "dogen.text.cpp/types/transforms/assistant.hpp"
#include "dogen.text.cpp/types/transforms/types/visitor_forward_declarations_transform.hpp"
#include "dogen.text.cpp/types/traits.hpp"
#include "dogen.text.cpp/types/transforms/types/traits.hpp"

namespace dogen::text::cpp::transforms::types {

physical::entities::archetype visitor_forward_declarations_transform::static_archetype() const {
    static physical::entities::archetype r([]() {
        physical::entities::archetype r;
        using pmnf = physical::helpers::meta_name_factory;
        r.meta_name(pmnf::make(cpp::traits::backend_sn(),
            traits::facet_sn(), traits::visitor_forward_declarations_archetype_sn()));
        using lmnf = logical::helpers::meta_name_factory;
        r.logical_meta_element_id(lmnf::make_visitor_name().qualified().dot());
        r.text_to_text_transform("");
        return r;
    }());
    return r;
}

physical::entities::archetype visitor_forward_declarations_transform::archetype() const {
    return static_archetype();
}

inclusion_support_types visitor_forward_declarations_transform::inclusion_support_type() const {
    return inclusion_support_types::regular_support;
}

boost::filesystem::path visitor_forward_declarations_transform::inclusion_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_inclusion_path_for_cpp_header(n, archetype().meta_name().qualified());
}

boost::filesystem::path visitor_forward_declarations_transform::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path_for_cpp_header(n, archetype().meta_name().qualified());
}

std::list<std::string> visitor_forward_declarations_transform::inclusion_dependencies(
    const formattables::dependencies_builder_factory& /*f*/,
    const logical::entities::element& /*e*/) const {
    static std::list<std::string> r;
    return r;
}

void visitor_forward_declarations_transform::apply(const context& ctx, const logical::entities::element& e,
    physical::entities::artefact& a) const {
    assistant ast(ctx, e, archetype().meta_name(), true/*requires_header_guard*/, a);
    const auto& o(ast.as<logical::entities::structural::visitor>(e));

    {
        auto sbf(ast.make_scoped_boilerplate_formatter(o));
        {
            const auto ns(ast.make_namespaces(o.name()));
            auto snf(ast.make_scoped_namespace_formatter(ns));
ast.stream() << std::endl;
ast.stream() << "class " << o.name().simple() << ";" << std::endl;
ast.stream() << std::endl;
        } // snf
ast.stream() << std::endl;
    } // sbf
    ast.update_artefact();
}

}
