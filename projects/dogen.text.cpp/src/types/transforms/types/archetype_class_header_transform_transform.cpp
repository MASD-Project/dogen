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
#include "dogen.logical/types/entities/physical/archetype.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.text.cpp/types/transforms/assistant.hpp"
#include "dogen.text.cpp/types/transforms/types/archetype_class_header_transform_transform.hpp"
#include "dogen.text.cpp/types/transforms/types/archetype_class_header_transform_factory.hpp"
#include "dogen.text.cpp/types/traits.hpp"
#include "dogen.text.cpp/types/transforms/types/traits.hpp"

namespace dogen::text::cpp::transforms::types {
namespace {

const std::string transform_id("text.cpp.transforms.types.archetype_class_header_transform_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

const physical::entities::archetype& archetype_class_header_transform_transform::static_archetype() {
    static auto r(archetype_class_header_transform_factory::make());
    return r;
}

const physical::entities::archetype& archetype_class_header_transform_transform::archetype() const {
    return static_archetype();
}

inclusion_support_types archetype_class_header_transform_transform::inclusion_support_type() const {
    return inclusion_support_types::canonical_support;
}

boost::filesystem::path archetype_class_header_transform_transform::inclusion_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_inclusion_path_for_cpp_header(n, archetype().meta_name().id().value());
}

boost::filesystem::path archetype_class_header_transform_transform::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path_for_cpp_header(n, archetype().meta_name().id().value());
}

std::list<std::string> archetype_class_header_transform_transform::inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const logical::entities::element& e) const {
    const auto& arch(assistant::as<logical::entities::physical::archetype>(e));

    auto builder(f.make());
    using identification::entities::technical_space;
    if (arch.major_technical_space() == technical_space::cpp) {
        builder.add_as_user(
            "dogen.text.cpp/types/transforms/model_to_text_transform.hpp");
    } else if (arch.major_technical_space() == technical_space::csharp) {
        builder.add_as_user(
            "dogen.text.csharp/types/transforms/model_to_text_transform.hpp");
    }

    return builder.build();
}

void archetype_class_header_transform_transform::apply(const context& ctx, const logical::entities::element& e,
    physical::entities::artefact& a) const {
    tracing::scoped_transform_tracer stp(lg, "types archetype class header transform",
        transform_id, e.name().qualified().dot(), *ctx.tracer(), e);
    assistant ast(ctx, e, archetype().meta_name(), true/*requires_header_guard*/, a);
    const auto& o(ast.as<logical::entities::physical::archetype>(e));

    {
        auto sbf(ast.make_scoped_boilerplate_formatter(o));
        {
            const auto ns(ast.make_namespaces(o.name()));
            auto snf(ast.make_scoped_namespace_formatter(ns));
            const auto sn(o.name().simple() + "_transform");
ast.stream() << std::endl;
ast.stream() << "class " << sn << " final : public model_to_text_transform {" << std::endl;
ast.stream() << "public:" << std::endl;
ast.stream() << "    static const physical::entities::archetype& static_archetype();" << std::endl;
ast.stream() << "    const physical::entities::archetype& archetype() const override;" << std::endl;
ast.stream() << std::endl;
ast.stream() << "public:" << std::endl;
            using identification::entities::technical_space;
            if (o.major_technical_space() == technical_space::cpp) {
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
            } else if (o.major_technical_space() == technical_space::csharp) {
ast.stream() << "    std::list<std::string> inclusion_dependencies(" << std::endl;
ast.stream() << "        const logical::entities::element& e) const override;" << std::endl;
ast.stream() << std::endl;
ast.stream() << "    boost::filesystem::path full_path(" << std::endl;
ast.stream() << "        const formattables::locator& l, const logical::entities::name& n) const override;" << std::endl;
            }
ast.stream() << std::endl;
ast.stream() << "public:" << std::endl;
ast.stream() << "    void apply(const context& ctx, const logical::entities::element& e," << std::endl;
ast.stream() << "        physical::entities::artefact& a) const override;" << std::endl;
ast.stream() << "};" << std::endl;
ast.stream() << std::endl;
        } // snf
ast.stream() << std::endl;
    } // sbf
    ast.update_artefact();
    stp.end_transform(a);

}

}
