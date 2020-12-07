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
#include <boost/make_shared.hpp>
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/formatters/sequence_formatter.hpp"
#include "dogen.identification/types/helpers/physical_meta_name_factory.hpp"
#include "dogen.logical/types/entities/structural/primitive.hpp"
#include "dogen.identification/types/helpers/logical_meta_name_factory.hpp"
#include "dogen.text.cpp/types/transforms/assistant.hpp"
#include "dogen.text.cpp/types/transforms/formatting_error.hpp"
#include "dogen.text.cpp/types/transforms/io/inserter_implementation_helper.hpp"
#include "dogen.text.cpp/types/transforms/io/primitive_implementation_transform.hpp"
#include "dogen.text.cpp/types/transforms/io/primitive_implementation_factory.hpp"

namespace dogen::text::cpp::transforms::io {
namespace {

const std::string transform_id("text.cpp.transforms.io.primitive_implementation_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

const physical::entities::archetype& primitive_implementation_transform::static_archetype() {
    static auto r(primitive_implementation_factory::make());
    return r;
}

const physical::entities::archetype& primitive_implementation_transform::archetype() const {
    return static_archetype();
}

void primitive_implementation_transform::
apply(const text::transforms::context& ctx, const text::entities::model& lps,
    const logical::entities::element& e, physical::entities::artefact& a) const {
    tracing::scoped_transform_tracer stp(lg, "primitive implementation",
        transform_id, e.name().qualified().dot(), *ctx.tracer(), e);

    assistant ast(ctx, lps, e, archetype().meta_name(), false/*requires_header_guard*/, a);
    const auto& p(ast.as<logical::entities::structural::primitive>(e));

    {
        auto sbf(ast.make_scoped_boilerplate_formatter(e));
        ast.add_helper_methods(p.name().qualified().dot());

        {
            const auto ns(ast.make_namespaces(p.name()));
            auto snf(ast.make_scoped_namespace_formatter(ns));
            const auto sn(p.name().simple());
            const auto qn(ast.get_qualified_name(p.name()));
            const auto attr(p.value_attribute());
ast.stream() << std::endl;
ast.stream() << "std::ostream& operator<<(std::ostream& s, const " << sn << "& v) {" << std::endl;
            if (ast.requires_stream_manipulators()) {
ast.stream() << "    boost::io::ios_flags_saver ifs(s);" << std::endl;
ast.stream() << "    s.setf(std::ios_base::boolalpha);" << std::endl;
ast.stream() << "    s.setf(std::ios::fixed, std::ios::floatfield);" << std::endl;
ast.stream() << "    s.precision(6);" << std::endl;
ast.stream() << "    s.setf(std::ios::showpoint);" << std::endl;
            }

            const std::string variable_name = "v." + attr.getter_setter_name() + "()";
ast.stream() << std::endl;
ast.stream() << "    s << \" { \"" << std::endl;
ast.stream() << "      << \"\\\"__type__\\\": \" << \"\\\"" << qn << "\\\"\" << \", \"" << std::endl;
ast.stream() << "      << \"\\\"" << attr.name().simple() << "\\\": \" << " << ast.streaming_for_type(attr.parsed_type().current(), variable_name) << std::endl;
ast.stream() << "      << \" }\";" << std::endl;
ast.stream() << std::endl;
ast.stream() << "    return s;" << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
        } // snf
    } // sbf
    ast.update_artefact();
    stp.end_transform(a);
}
}
