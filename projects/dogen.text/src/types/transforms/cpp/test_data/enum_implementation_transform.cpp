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
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/formatters/sequence_formatter.hpp"
#include "dogen.identification/types/helpers/physical_meta_name_factory.hpp"
#include "dogen.logical/types/entities/structural/enumeration.hpp"
#include "dogen.identification/types/helpers/logical_meta_name_factory.hpp"
#include "dogen.text/types/formatters/assistant.hpp"
#include "dogen.text/types/transforms/transformation_error.hpp"
#include "dogen.text/types/transforms/cpp/test_data/enum_implementation_transform.hpp"
#include "dogen.text/types/transforms/cpp/test_data/enum_implementation_factory.hpp"

namespace dogen::text::transforms::cpp::test_data {
namespace {

const std::string transform_id("text.transforms.test_data.enum_implementation_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

const physical::entities::archetype& enum_implementation_transform::static_archetype() {
    static auto r(enum_implementation_factory::make());
    return r;
}

const physical::entities::archetype& enum_implementation_transform::archetype() const {
    return static_archetype();
}

void enum_implementation_transform::
apply(const text::transforms::context& ctx, const text::entities::model& lps,
    const logical::entities::element& e, physical::entities::artefact& a) const {
    tracing::scoped_transform_tracer stp(lg, "enum implementation",
        transform_id, e.name().qualified().dot(), *ctx.tracer(), e);

    text::formatters::assistant ast(lps, e, a, false/*requires_header_guard*/);
    const auto& ye(ast.as<logical::entities::structural::enumeration>(e));

    {
        auto sbf(ast.make_scoped_boilerplate_formatter(e));
        {
            const auto ns(ast.make_namespaces(ye.name()));
            auto snf(ast.make_scoped_namespace_formatter(ns));
ast.stream() << std::endl;
ast.stream() << ye.name().simple() << "_generator::" << ye.name().simple() << "_generator() : position_(0) { }" << std::endl;
ast.stream() << "void " << ye.name().simple() << "_generator::" << std::endl;
ast.stream() << "populate(const unsigned int position, result_type& v) {" << std::endl;
ast.stream() << "    v = static_cast<" << ye.name().simple() << ">(position % " << ye.enumerators().size() << ");" << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
ast.stream() << ye.name().simple() << "_generator::result_type" << std::endl;
ast.stream() << ye.name().simple() << "_generator::create(const unsigned int  position) {" << std::endl;
ast.stream() << "    result_type r;" << std::endl;
ast.stream() << "    " << ye.name().simple() << "_generator::populate(position, r);" << std::endl;
ast.stream() << "    return r;" << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
ast.stream() << ye.name().simple() << "_generator::result_type" << std::endl;
ast.stream() << ye.name().simple() << "_generator::operator()() {" << std::endl;
ast.stream() << "    return create(position_++);" << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
         } // snf
    } // sbf
    ast.update_artefact();
    stp.end_transform(a);
}

}
