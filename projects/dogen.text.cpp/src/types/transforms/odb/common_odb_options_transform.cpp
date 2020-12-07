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
#include "dogen.logical/types/entities/orm/common_odb_options.hpp"
#include "dogen.identification/types/helpers/logical_meta_name_factory.hpp"
#include "dogen.utility/types/formatters/sequence_formatter.hpp"
#include "dogen.text.cpp/types/transforms/assistant.hpp"
#include "dogen.text.cpp/types/transforms/formatting_error.hpp"
#include "dogen.text.cpp/types/transforms/odb/common_odb_options_transform.hpp"
#include "dogen.text.cpp/types/transforms/odb/common_odb_options_factory.hpp"

namespace dogen::text::cpp::transforms::odb {
namespace {

const std::string transform_id("text.cpp.transforms.odb.common_odb_options_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

const physical::entities::archetype& common_odb_options_transform::static_archetype() {
    static auto r(common_odb_options_factory::make());
    return r;
}

const physical::entities::archetype& common_odb_options_transform::archetype() const {
    return static_archetype();
}

void common_odb_options_transform::
apply(const text::transforms::context& ctx, const text::entities::model& lps,
    const logical::entities::element& e, physical::entities::artefact& a) const {
    tracing::scoped_transform_tracer stp(lg, "common odb options",
        transform_id, e.name().qualified().dot(), *ctx.tracer(), e);

    assistant ast(ctx, lps, e, archetype().meta_name(), false/*requires_header_guard*/, a);
    using logical::entities::orm::common_odb_options;
    const auto& o(ast.as<common_odb_options>(e));

    {
        const auto ts(identification::entities::technical_space::odb);
        ast.make_decoration_preamble(e, ts);

        if (!ast.is_cpp_standard_98()) {
ast.stream() << "# enable C++11" << std::endl;
ast.stream() << "--std c++11" << std::endl;
ast.stream() << std::endl;
        }

        if (!o.sql_name_case().empty()) {
ast.stream() << "# casing" << std::endl;
ast.stream() << "--sql-name-case " << o.sql_name_case() << std::endl;
ast.stream() << std::endl;
        }

        if (o.databases().size() > 1) {
ast.stream() << "# enable multi-database support" << std::endl;
ast.stream() << "--multi-database static" << std::endl;
ast.stream() << std::endl;
        }

        if (!o.databases().empty()) {
ast.stream() << "# target databases" << std::endl;

            for (const auto& d : o.databases())
ast.stream() << "--database " << d << std::endl;
ast.stream() << std::endl;
        }
ast.stream() << "# use the boost profile" << std::endl;
ast.stream() << "--profile boost" << std::endl;
ast.stream() << std::endl;
ast.stream() << "# generate queries and embedded schemas" << std::endl;
ast.stream() << "--generate-query" << std::endl;
ast.stream() << "--generate-schema" << std::endl;
ast.stream() << "--schema-format embedded" << std::endl;
ast.stream() << std::endl;
ast.stream() << "# force odb extensions to be different from dogen ones just in case." << std::endl;
ast.stream() << "--ixx-suffix .ixx" << std::endl;
ast.stream() << "--hxx-suffix .hxx" << std::endl;
ast.stream() << "--cxx-suffix .cxx" << std::endl;
ast.stream() << std::endl;
ast.stream() << "# debug regexes" << std::endl;
ast.stream() << "# --include-regex-trace" << std::endl;
    } // sbf
    ast.update_artefact();
    stp.end_transform(a);
}

}
