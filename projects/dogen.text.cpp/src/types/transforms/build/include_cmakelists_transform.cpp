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
#include "dogen.identification/types/helpers/logical_meta_name_factory.hpp"
#include "dogen.logical/types/entities/build/cmakelists.hpp"
#include "dogen.utility/types/formatters/sequence_formatter.hpp"
#include "dogen.text.cpp/types/transforms/assistant.hpp"
#include "dogen.text.cpp/types/transforms/build/traits.hpp"
#include "dogen.text.cpp/types/transforms/traits.hpp"
#include "dogen.text.cpp/types/traits.hpp"
#include "dogen.text.cpp/types/transforms/traits.hpp"
#include "dogen.text.cpp/types/transforms/assistant.hpp"
#include "dogen.text.cpp/types/transforms/formatting_error.hpp"
#include "dogen.text.cpp/types/transforms/build/include_cmakelists_transform.hpp"
#include "dogen.text.cpp/types/transforms/build/include_cmakelists_factory.hpp"

namespace dogen::text::cpp::transforms::build {
namespace {

const std::string transform_id("text.cpp.transforms.build.include_cmakelists_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

const physical::entities::archetype& include_cmakelists_transform::static_archetype() {
    static auto r(include_cmakelists_factory::make());
    return r;
}

const physical::entities::archetype& include_cmakelists_transform::archetype() const {
    return static_archetype();
}

void include_cmakelists_transform::apply(const context& ctx,
    const logical::entities::element& e, physical::entities::artefact& a) const {
    tracing::scoped_transform_tracer stp(lg, "include cmakelists",
        transform_id, e.name().qualified().dot(), *ctx.tracer(), e);

    assistant ast(ctx, e, archetype().meta_name(), false/*requires_header_guard*/, a);
    using logical::entities::build::cmakelists;
    const auto& c(ast.as<cmakelists>(e));

    {
        const auto ts(identification::entities::technical_space::cmake);
        ast.make_decoration_preamble(e, ts);
ast.stream() << "add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/" << c.source_directory_name() << ")" << std::endl;
       if (ast.is_tests_enabled()) {
ast.stream() << "add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/" << c.tests_directory_name() << ")" << std::endl;
       }
ast.stream() << std::endl;
ast.stream() << "install(" << std::endl;
ast.stream() << "    DIRECTORY " << c.include_directory_path() << "/" << std::endl;
ast.stream() << "    DESTINATION " << c.include_directory_path() << "/" << std::endl;
ast.stream() << "    COMPONENT headers" << std::endl;
ast.stream() << "    FILES_MATCHING PATTERN \"*." << c.header_file_extension() << "\")" << std::endl;
    } // sbf
    ast.update_artefact();
    stp.end_transform(a);
}
}
