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
#include <boost/algorithm/string/case_conv.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.identification/types/helpers/physical_meta_name_factory.hpp"
#include "dogen.logical/types/entities/structural/object.hpp"
#include "dogen.identification/types/helpers/logical_meta_name_factory.hpp"
#include "dogen.utility/types/formatters/sequence_formatter.hpp"
#include "dogen.text/types/formatters/assistant.hpp"
#include "dogen.text/types/transforms/transformation_error.hpp"
#include "dogen.text/types/transforms/cpp/odb/object_odb_options_transform.hpp"
#include "dogen.text/types/transforms/cpp/odb/object_odb_options_factory.hpp"

namespace dogen::text::transforms::cpp::odb {
namespace {

const std::string transform_id("text.transforms.odb.object_odb_options_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

const physical::entities::archetype& object_odb_options_transform::static_archetype() {
    static auto r(object_odb_options_factory::make());
    return r;
}

const physical::entities::archetype& object_odb_options_transform::archetype() const {
    return static_archetype();
}

void object_odb_options_transform::
apply(const text::transforms::context& ctx, const text::entities::model& lps,
    const logical::entities::element& e, physical::entities::artefact& a) const {
    tracing::scoped_transform_tracer stp(lg, "object odb options",
        transform_id, e.name().qualified().dot(), *ctx.tracer(), e);

    text::formatters::assistant ast(lps, e, a, false/*requires_header_guard*/);
    const auto& o(ast.as<logical::entities::structural::object>(e));

    {
        const auto ts(identification::entities::technical_space::odb);
        ast.make_decoration_preamble(e, ts);

        if (!o.orm_properties()) {
ast.stream() << std::endl;
ast.stream() << "#" << std::endl;
ast.stream() << "# class has no ODB options defined." << std::endl;
ast.stream() << "#" << std::endl;
        } else {
            const auto ooo(o.orm_properties()->odb_options());
ast.stream() << "# epilogue" << std::endl;
ast.stream() << "--odb-epilogue " << ooo.epilogue() << std::endl;
ast.stream() << std::endl;
            if (!ooo.include_regexes().empty()) {
ast.stream() << "# regexes" << std::endl;
                for (const auto& regex : ooo.include_regexes())
ast.stream() << "--include-regex " << regex << std::endl;
ast.stream() << std::endl;
ast.stream() << "# debug regexes" << std::endl;
ast.stream() << "# --include-regex-trace" << std::endl;
ast.stream() << std::endl;
ast.stream() << "# make the header guards similar to dogen ones" << std::endl;
ast.stream() << "--guard-prefix " << ooo.header_guard_prefix() << std::endl;
            }
        }
    } // sbf
    ast.update_artefact();
    stp.end_transform(a);
}

}
