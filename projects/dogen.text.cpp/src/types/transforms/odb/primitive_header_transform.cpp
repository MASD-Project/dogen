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
#include "dogen.logical/types/entities/structural/primitive.hpp"
#include "dogen.identification/types/helpers/logical_meta_name_factory.hpp"
#include "dogen.text.cpp/types/transforms/assistant.hpp"
#include "dogen.text.cpp/types/transforms/odb/primitive_header_transform.hpp"
#include "dogen.text.cpp/types/transforms/odb/primitive_header_factory.hpp"

namespace dogen::text::cpp::transforms::odb {
namespace {

const std::string transform_id("text.cpp.transforms.odb.primitive_header_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

const physical::entities::archetype& primitive_header_transform::static_archetype() {
    static auto r(primitive_header_factory::make());
    return r;
}

const physical::entities::archetype& primitive_header_transform::archetype() const {
    return static_archetype();
}

void primitive_header_transform::
apply(const text::transforms::context& ctx, const text::entities::model& lps,
    const logical::entities::element& e, physical::entities::artefact& a) const {
    tracing::scoped_transform_tracer stp(lg, "primitive header",
        transform_id, e.name().qualified().dot(), *ctx.tracer(), e);

    assistant ast(ctx, lps, e, archetype().meta_name(), true/*requires_header_guard*/, a);
    const auto& p(ast.as<logical::entities::structural::primitive>(e));

    {
        const auto sn(p.name().simple());
        const auto qn(ast.get_qualified_name(p.name()));
        auto sbf(ast.make_scoped_boilerplate_formatter(e));
        const auto attr(p.value_attribute());

        if (!p.orm_properties() || p.orm_properties()->odb_pragmas().empty()) {
ast.stream() << "// class has no ODB pragmas defined." << std::endl;
ast.stream() << std::endl;
        } else {
            {
                const auto ns(ast.make_namespaces(p.name()));
                auto snf(ast.make_scoped_namespace_formatter(ns));
ast.stream() << std::endl;
ast.stream() << "#ifdef ODB_COMPILER" << std::endl;
ast.stream() << std::endl;
                for (const auto& pg : p.orm_properties()->odb_pragmas())
ast.stream() << pg << std::endl;

                bool is_first(true);
                if (p.value_attribute().orm_properties() &&
                    !p.value_attribute().orm_properties()->odb_pragmas().empty()) {
                    for (const auto& pg : p.value_attribute().orm_properties()->odb_pragmas()) {
                        if (is_first)
ast.stream() << std::endl;
                            is_first = false;
ast.stream() << pg << std::endl;
                    }
ast.stream() << std::endl;
ast.stream() << "#endif" << std::endl;
ast.stream() << std::endl;
                }
            }
ast.stream() << std::endl;
        }
    } // sbf
    ast.update_artefact();
    stp.end_transform(a);
}

}
