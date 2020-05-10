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
#include "dogen.logical/types/entities/physical/archetype.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.text.cpp/types/transforms/assistant.hpp"
#include "dogen.text.cpp/types/transforms/types/archetype_class_header_transform_new.hpp"
#include "dogen.text.cpp/types/traits.hpp"
#include "dogen.text.cpp/types/transforms/types/traits.hpp"

namespace dogen::text::cpp::transforms::types {
physical::entities::archetype archetype_class_header_transform_new::static_archetype() const {
    static physical::entities::archetype r([]() {
        physical::entities::archetype r;
        using pmnf = physical::helpers::meta_name_factory;
        r.meta_name(pmnf::make(cpp::traits::backend_sn(),
            traits::facet_sn(), traits::archetype_class_header_archetype_sn()));
        using lmnf = logical::helpers::meta_name_factory;
        r.logical_meta_element_id(lmnf::make_physical_archetype_name().qualified().dot());
        r.text_to_text_transform("dogen.text.transforms.stitch_transform");
        return r;
    }());
    return r;
}

physical::entities::archetype archetype_class_header_transform_new::archetype() const {
    return static_archetype();
}

inclusion_support_types archetype_class_header_transform_new::inclusion_support_type() const {
    return inclusion_support_types::regular_support;
}

boost::filesystem::path archetype_class_header_transform_new::inclusion_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_inclusion_path_for_cpp_header(n, archetype().meta_name().qualified());
}

boost::filesystem::path archetype_class_header_transform_new::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path_for_cpp_header(n, archetype().meta_name().qualified());
}

std::list<std::string> archetype_class_header_transform_new::inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const logical::entities::element& /*e*/) const {
    static std::list<std::string> r;

    auto builder(f.make());
    builder.add_as_user("dogen.text.cpp/types/transforms/model_to_text_transform.hpp");

    return builder.build();
}

void archetype_class_header_transform_new::apply(const context& ctx, const logical::entities::element& e,
    physical::entities::artefact& a) const {
    assistant ast(ctx, e, archetype().meta_name(), true/*requires_header_guard*/, a);
    const auto& o(ast.as<logical::entities::physical::archetype>(e));

    {
        auto sbf(ast.make_scoped_boilerplate_formatter(o));
        {
            const auto ns(ast.make_namespaces(o.name()));
            auto snf(ast.make_scoped_namespace_formatter(ns));
ast.stream() << "class " << o.name().simple() << " final : public model_to_text_transform {" << std::endl;
ast.stream() << "public:" << std::endl;
ast.stream() << "    physical::entities::archetype static_archetype() const;" << std::endl;
ast.stream() << "    physical::entities::archetype archetype() const override;" << std::endl;
ast.stream() << std::endl;
ast.stream() << "public:" << std::endl;
ast.stream() << "    std::list<std::string> inclusion_dependencies(" << std::endl;
ast.stream() << "        const formattables::dependencies_builder_factory& f," << std::endl;
ast.stream() << "        const logical::entities::element& e) const override;" << std::endl;
ast.stream() << std::endl;
ast.stream() << "    inclusion_support_types inclusion_support_type() const override;" << std::endl;
ast.stream() << std::endl;
ast.stream() << "    boost::filesystem::path inclusion_path(" << std::endl;
ast.stream() << "        const formattables::locator& l," << std::endl;
ast.stream() << "        const logical::entities::name& n) const override;" << std::endl;
ast.stream() << std::endl;
ast.stream() << "    boost::filesystem::path full_path(" << std::endl;
ast.stream() << "        const formattables::locator& l," << std::endl;
ast.stream() << "        const logical::entities::name& n) const override;" << std::endl;
ast.stream() << std::endl;
ast.stream() << "public:" << std::endl;
ast.stream() << "    void apply(const context& ctx, const logical::entities::element& e," << std::endl;
ast.stream() << "        physical::entities::artefact& a) const override;" << std::endl;
ast.stream() << "};" << std::endl;
        } // snf
ast.stream() << std::endl;
    } // sbf
    ast.update_artefact();
}

}
