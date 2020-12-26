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
#include "dogen.logical/types/entities/structural/exception.hpp"
#include "dogen.identification/types/helpers/logical_meta_name_factory.hpp"
#include "dogen.text/types/formatters/assistant.hpp"
#include "dogen.text/types/transforms/cpp/types/exception_header_transform.hpp"
#include "dogen.text/types/transforms/cpp/types/exception_header_factory.hpp"

namespace dogen::text::transforms::cpp::types {
namespace {

const std::string transform_id("text.transforms.types.exception_header_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

const physical::entities::archetype& exception_header_transform::static_archetype() {
    static auto r(exception_header_factory::make());
    return r;
}

const physical::entities::archetype& exception_header_transform::archetype() const {
    return static_archetype();
}
void exception_header_transform::
apply(const text::transforms::context& ctx, const text::entities::model& lps,
    const logical::entities::element& e, physical::entities::artefact& a) const {
    tracing::scoped_transform_tracer stp(lg, "exception header",
        transform_id, e.name().qualified().dot(), *ctx.tracer(), e);

    text::formatters::assistant ast(lps, e, a, true/*requires_header_guard*/);
    const auto& ye(ast.as<logical::entities::structural::exception>(e));

    {
        auto sbf(ast.make_scoped_boilerplate_formatter(e));
        {
            const auto ns(ast.make_namespaces(ye.name()));
            auto snf(ast.make_scoped_namespace_formatter(ns));
ast.stream() << std::endl;
            ast.comment(ye.documentation());
ast.stream() << "class " << ye.name().simple() << " : public virtual std::exception, public virtual boost::exception {" << std::endl;
ast.stream() << "public:" << std::endl;
            if (ast.is_cpp_standard_98()) {
ast.stream() << "    " << ye.name().simple() << "() {}" << std::endl;
ast.stream() << "    ~" << ye.name().simple() << "() {}" << std::endl;
            } else {
ast.stream() << "    " << ye.name().simple() << "() = default;" << std::endl;
ast.stream() << "    ~" << ye.name().simple() << "()" << ast.make_noexcept_keyword_text() << " = default;" << std::endl;
            }
ast.stream() << std::endl;
ast.stream() << "public:" << std::endl;
ast.stream() << "    explicit " << ye.name().simple() << "(const std::string& message) : message_(message) { }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "public:" << std::endl;
            if (ast.is_cpp_standard_98()) {
                // Note: we are using BOOST_NOEXCEPT here by design. The problem is
                // users may include this header in a C++ 98 project or in a C++ > 11 project;
                // and we need to have different behaviours. Depending on this inclusion.
                // If we do not, we will cause compilation errors when including C++ 98 code
                // on a C++ 11 project. This is because the standard library will have noexcept
                // but we won't (as we were generated for C++ 98), so we'd be weakening the exception
                // guarantees. By using the boost macro we will do the right thing hopefully.
                // And since we already need boost for exception, we should be ok.
ast.stream() << "    const char* what() const BOOST_NOEXCEPT { return(message_.c_str()); }" << std::endl;
            } else {
ast.stream() << "    const char* what() const" << ast.make_noexcept_keyword_text() << " { return(message_.c_str()); }" << std::endl;
            }
ast.stream() << std::endl;
ast.stream() << "private:" << std::endl;
ast.stream() << "    const std::string message_;" << std::endl;
ast.stream() << "};" << std::endl;
ast.stream() << std::endl;
        } // snf
ast.stream() << std::endl;
    } // sbf
    ast.update_artefact();
    stp.end_transform(a);
}

}
