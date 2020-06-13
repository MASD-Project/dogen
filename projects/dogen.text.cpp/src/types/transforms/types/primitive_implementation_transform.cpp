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
#include "dogen.physical/types/helpers/meta_name_factory.hpp"
#include "dogen.logical/types/entities/structural/primitive.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.utility/types/formatters/sequence_formatter.hpp"
#include "dogen.text.cpp/types/traits.hpp"
#include "dogen.text.cpp/types/transforms/traits.hpp"
#include "dogen.text.cpp/types/transforms/assistant.hpp"
#include "dogen.text.cpp/types/transforms/inclusion_constants.hpp"
#include "dogen.text.cpp/types/transforms/formatting_error.hpp"
#include "dogen.text.cpp/types/transforms/io/traits.hpp"
#include "dogen.text.cpp/types/transforms/io/inserter_implementation_helper.hpp"
#include "dogen.text.cpp/types/transforms/types/traits.hpp"
#include "dogen.text.cpp/types/transforms/types/primitive_implementation_transform.hpp"
#include "dogen.text.cpp/types/transforms/types/primitive_implementation_factory.hpp"

namespace dogen::text::cpp::transforms::types {
namespace {

const std::string transform_id("text.cpp.transforms.types.primitive_implementation_transform");

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

inclusion_support_types primitive_implementation_transform::inclusion_support_type() const {
    return inclusion_support_types::not_supported;
}

boost::filesystem::path primitive_implementation_transform::inclusion_path(
    const formattables::locator& /*l*/, const logical::entities::name& n) const {

    using namespace dogen::utility::log;
    static logger lg(logger_factory(archetype().meta_name().qualified()));
    static const std::string not_supported("Inclusion path is not supported: ");

    BOOST_LOG_SEV(lg, error) << not_supported << n.qualified().dot();
    BOOST_THROW_EXCEPTION(formatting_error(not_supported + n.qualified().dot()));
}

boost::filesystem::path primitive_implementation_transform::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path_for_cpp_implementation(n, archetype().meta_name().qualified());
}

std::list<std::string>
primitive_implementation_transform::inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const logical::entities::element& e) const {
    using logical::entities::structural::primitive;
    const auto& o(assistant::as<primitive>(e));
    auto builder(f.make());

    const auto ch_arch(traits::primitive_header_archetype_qn());
    builder.add(o.name(), ch_arch);
    return builder.build();
}

void primitive_implementation_transform::apply(const context& ctx, const logical::entities::element& e,
    physical::entities::artefact& a) const {
    tracing::scoped_transform_tracer stp(lg, "primitive implementation transform",
        transform_id, e.name().qualified().dot(), *ctx.tracer(), e);

    assistant ast(ctx, e, archetype().meta_name(), false/*requires_header_guard*/, a);
    const auto& p(ast.as<logical::entities::structural::primitive>(e));

    const auto sn(p.name().simple());
    const auto qn(ast.get_qualified_name(p.name()));
    {
        auto sbf(ast.make_scoped_boilerplate_formatter(e));
        {
            const auto ns(ast.make_namespaces(p.name()));
            auto snf(ast.make_scoped_namespace_formatter(ns));
            const auto attr(p.value_attribute());

            /*
             * Default constructor.
             */
            if (ast.requires_manual_default_constructor()) {
ast.stream() << std::endl;
ast.stream() << sn << "::" << sn << "()" << std::endl;
ast.stream() << "    : " << attr.member_variable_name() << "(static_cast<" << ast.get_qualified_name(attr.parsed_type()) << ">(0)) { }" << std::endl;
            }

            /*
             * Move constructor.
             */
            if (ast.requires_manual_move_constructor()) {
ast.stream() << std::endl;
ast.stream() << sn << "::" << sn << "(" << sn << "&& rhs)" << std::endl;
ast.stream() << "    : " << attr.member_variable_name() << "(std::move(rhs." << attr.member_variable_name() << ")) { }" << std::endl;
            }

            /*
             * Complete constructor.
             */
ast.stream() << std::endl;
ast.stream() << sn << "::" << sn << "(const " << ast.get_qualified_name(attr.parsed_type()) << ast.make_by_ref_text(attr) << " " << attr.name().simple() << ")" << std::endl;
ast.stream() << "    : " << attr.member_variable_name() << "(" << attr.name().simple() << ") { }" << std::endl;
ast.stream() << std::endl;
            /*
             * Getters and setters
             */
             if (attr.parsed_type().is_current_simple_type()) {
ast.stream() << ast.get_qualified_name(attr.parsed_type()) << " " << sn << "::" << attr.name().simple() << "() const {" << std::endl;
ast.stream() << "    return " << attr.member_variable_name() << ";" << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
                if (!p.is_immutable()) {
ast.stream() << "void " << sn << "::" << attr.name().simple() << "(const " << ast.get_qualified_name(attr.parsed_type()) << " v) {" << std::endl;
ast.stream() << "    " << attr.member_variable_name() << " = v;" << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
                }
            } else {
ast.stream() << "const " << ast.get_qualified_name(attr.parsed_type()) << "& " << sn << "::" << attr.name().simple() << "() const {" << std::endl;
ast.stream() << "    return " << attr.member_variable_name() << ";" << std::endl;
ast.stream() << "}" << std::endl;
                if (!p.is_immutable()) {
ast.stream() << std::endl;
ast.stream() << ast.get_qualified_name(attr.parsed_type()) << "& " << sn << "::" << attr.name().simple() << "() {" << std::endl;
ast.stream() << "    return " << attr.member_variable_name() << ";" << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
ast.stream() << "void " << sn << "::" << attr.name().simple() << "(const " << ast.get_qualified_name(attr.parsed_type()) << "& v) {" << std::endl;
ast.stream() << "    " << attr.member_variable_name() << " = v;" << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
ast.stream() << "void " << sn << "::" << attr.name().simple() << "(const " << ast.get_qualified_name(attr.parsed_type()) << "&& v) {" << std::endl;
ast.stream() << "    " << attr.member_variable_name() << " = std::move(v);" << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
                }
            }

            /*
             * Equality.
             */
ast.stream() << "bool " << sn << "::operator==(const " << sn << "& rhs) const {" << std::endl;
ast.stream() << "    return " << attr.member_variable_name() << " == rhs." << attr.member_variable_name() << ";" << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
            /*
             * Swap and assignment.
             */
            if (!p.is_immutable()) {
ast.stream() << "void " << sn << "::swap(" << sn << "& other)" << ast.make_noexcept_keyword_text() << " {" << std::endl;
ast.stream() << "    using std::swap;" << std::endl;
ast.stream() << "    swap(" << attr.member_variable_name() << ", other." << attr.member_variable_name() << ");" << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
ast.stream() << sn << "& " << sn << "::operator=(" << sn << " other) {" << std::endl;
ast.stream() << "    using std::swap;" << std::endl;
ast.stream() << "    swap(*this, other);" << std::endl;
ast.stream() << "    return *this;" << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
            }
        } // snf
    } // sbf
    ast.update_artefact();
    stp.end_transform(a);
}
}
