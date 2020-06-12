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
#include "dogen.physical/types/helpers/meta_name_factory.hpp"
#include "dogen.logical/types/entities/physical/backend.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.text.cpp/types/transforms/assistant.hpp"
#include "dogen.text.cpp/types/transforms/types/backend_class_header_transform_transform.hpp"
#include "dogen.text.cpp/types/traits.hpp"
#include "dogen.text.cpp/types/transforms/types/traits.hpp"

namespace dogen::text::cpp::transforms::types {
namespace {

const std::string transform_id("text.cpp.transforms.types.backend_class_header_transform_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

const physical::entities::archetype& backend_class_header_transform_transform::static_archetype() {
    static physical::entities::archetype r([]() {
        physical::entities::archetype r;
        using pmnf = physical::helpers::meta_name_factory;
        r.meta_name(pmnf::make(cpp::traits::backend_sn(),
            traits::facet_sn(), traits::backend_class_header_archetype_sn()));
        using lmnf = logical::helpers::meta_name_factory;
        r.logical_meta_element_id(lmnf::make_physical_backend_name().qualified().dot());
        r.referencing_status(physical::entities::referencing_status::facet_default);
        return r;
    }());
    return r;
}

const physical::entities::archetype& backend_class_header_transform_transform::archetype() const {
    return static_archetype();
}

inclusion_support_types backend_class_header_transform_transform::inclusion_support_type() const {
    return inclusion_support_types::canonical_support;
}

boost::filesystem::path backend_class_header_transform_transform::inclusion_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_inclusion_path_for_cpp_header(n, archetype().meta_name().qualified());
}

boost::filesystem::path backend_class_header_transform_transform::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path_for_cpp_header(n, archetype().meta_name().qualified());
}

std::list<std::string> backend_class_header_transform_transform::inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const logical::entities::element& e) const {

    const auto& be(assistant::as<logical::entities::physical::backend>(e));

    auto builder(f.make());
    builder.add_as_user("dogen.physical/types/entities/backend.hpp");
    using logical::entities::technical_space;
    if (be.major_technical_space() == technical_space::cpp) {
        builder.add_as_user(
            "dogen.text.cpp/types/transforms/registrar.hpp");
    } else if (be.major_technical_space() == technical_space::csharp) {
        builder.add_as_user(
            "dogen.text.csharp/types/transforms/registrar.hpp");
    }
    const auto ch_arch(traits::class_header_archetype_qn());
    return builder.build();
}

void backend_class_header_transform_transform::apply(const context& ctx, const logical::entities::element& e,
    physical::entities::artefact& a) const {
    tracing::scoped_transform_tracer stp(lg, "backend class header transform",
        transform_id, e.name().qualified().dot(), *ctx.tracer(), e);
    assistant ast(ctx, e, archetype().meta_name(), true/*requires_header_guard*/, a);
    const auto& be(ast.as<logical::entities::physical::backend>(e));

    {
        auto sbf(ast.make_scoped_boilerplate_formatter(be));
        {
            const auto ns(ast.make_namespaces(be.name(),
                    false/*detect_model_name*/));
            auto snf(ast.make_scoped_namespace_formatter(ns));
ast.stream() << std::endl;
            ast.comment(be.documentation());
ast.stream() << "class " << be.name().simple() << "_backend_chain final {" << std::endl;
ast.stream() << "public:" << std::endl;
ast.stream() << "    static const physical::entities::backend& static_backend();" << std::endl;
ast.stream() << "    const physical::entities::backend& backend() const;" << std::endl;
ast.stream() << std::endl;
ast.stream() << "public:" << std::endl;
ast.stream() << "    static void initialise(transforms::registrar& r);" << std::endl;
ast.stream() << "};" << std::endl;
        } // snf
ast.stream() << std::endl;
    } // sbf
    ast.update_artefact();
    stp.end_transform(a);
}

}