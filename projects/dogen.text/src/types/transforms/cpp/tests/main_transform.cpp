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
#include "dogen.identification/types/helpers/physical_meta_name_factory.hpp"
#include "dogen.logical/types/entities/structural/entry_point.hpp"
#include "dogen.identification/types/helpers/logical_meta_name_factory.hpp"
#include "dogen.utility/types/formatters/sequence_formatter.hpp"
#include "dogen.text/types/formatters/assistant.hpp"
#include "dogen.text/types/transforms/transformation_error.hpp"
#include "dogen.text/types/transforms/cpp/tests/main_transform.hpp"
#include "dogen.text/types/transforms/cpp/tests/main_factory.hpp"

namespace dogen::text::transforms::cpp::tests {
namespace {

const std::string transform_id("text.transforms.tests.main_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

const physical::entities::archetype& main_transform::static_archetype() {
    static auto r(main_factory::make());
    return r;
}

const physical::entities::archetype& main_transform::archetype() const {
    return static_archetype();
}

void main_transform::
apply(const text::transforms::context& ctx, const text::entities::model& lps,
    const logical::entities::element& e, physical::entities::artefact& a) const {
    tracing::scoped_transform_tracer stp(lg, "main",
        transform_id, e.name().qualified().dot(), *ctx.tracer(), e);

    text::formatters::assistant ast(lps, e, a, false/*requires_header_guard*/);
    using logical::entities::structural::entry_point;
    const auto& ep(ast.as<entry_point>(e));
    const auto qn(ast.get_qualified_name(ep.name()));
ast.stream() << "#define BOOST_TEST_MODULE " << qn << std::endl;
ast.stream() << std::endl;
    {
        auto sbf(ast.make_scoped_boilerplate_formatter(ep));
ast.stream() << std::endl;
ast.stream() << "namespace  {" << std::endl;
ast.stream() << std::endl;
ast.stream() << "const std::string error_msg(\"Error during test.\");" << std::endl;
ast.stream() << std::endl;
ast.stream() << "inline void translate(const boost::exception& e) {" << std::endl;
ast.stream() << "    std::cerr << std::endl << boost::diagnostic_information(e);" << std::endl;
ast.stream() << "    throw std::runtime_error(error_msg);" << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
ast.stream() << "struct exception_fixture {" << std::endl;
ast.stream() << "    exception_fixture() {" << std::endl;
ast.stream() << "        using boost::exception;" << std::endl;
ast.stream() << "        using boost::unit_test::unit_test_monitor;" << std::endl;
ast.stream() << "        unit_test_monitor.register_exception_translator<exception>(&translate);" << std::endl;
ast.stream() << "    }" << std::endl;
ast.stream() << "};" << std::endl;
ast.stream() << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
ast.stream() << "BOOST_GLOBAL_FIXTURE(exception_fixture);" << std::endl;
    } // sbf
    ast.update_artefact();
    stp.end_transform(a);
}
}
