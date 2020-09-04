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
#include "dogen.logical/types/entities/structural/primitive.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.utility/types/formatters/sequence_formatter.hpp"
#include "dogen.text.cpp/types/transforms/assistant.hpp"
#include "dogen.text.cpp/types/traits.hpp"
#include "dogen.text.cpp/types/transforms/traits.hpp"
#include "dogen.text.cpp/types/transforms/inclusion_constants.hpp"
#include "dogen.text.cpp/types/transforms/formatting_error.hpp"
#include "dogen.text.cpp/types/transforms/types/traits.hpp"
#include "dogen.text.cpp/types/transforms/hash/traits.hpp"
#include "dogen.text.cpp/types/transforms/hash/primitive_implementation_transform.hpp"
#include "dogen.text.cpp/types/transforms/hash/primitive_implementation_factory.hpp"

namespace dogen::text::cpp::transforms::hash {
namespace {

const std::string transform_id("text.cpp.transforms.hash.primitive_implementation_transform");

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
    static logger lg(logger_factory(archetype().meta_name().id().value()));
    static const std::string not_supported("Inclusion path is not supported: ");

    BOOST_LOG_SEV(lg, error) << not_supported << n.qualified().dot();
    BOOST_THROW_EXCEPTION(formatting_error(not_supported + n.qualified().dot()));
}

boost::filesystem::path primitive_implementation_transform::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path_for_cpp_implementation(n, archetype().meta_name().id().value());
}

std::list<std::string>
primitive_implementation_transform::inclusion_dependencies(
    const formattables::dependencies_builder_factory& f,
    const logical::entities::element& e) const {

    using logical::entities::structural::primitive;
    const auto& p(assistant::as<primitive>(e));
    const identification::entities::physical_meta_id carch(traits::canonical_archetype());
    auto builder(f.make());
    builder.add(p.name(), carch);

    return builder.build();
}

void primitive_implementation_transform::
apply(const context& ctx, const logical::entities::element& e,
    physical::entities::artefact& a) const {
    tracing::scoped_transform_tracer stp(lg, "primitive implementation transform",
        transform_id, e.name().qualified().dot(), *ctx.tracer(), e);

    assistant ast(ctx, e, archetype().meta_name(), false/*requires_header_guard*/, a);
    const auto& p(ast.as<logical::entities::structural::primitive>(e));

    const auto sn(p.name().simple());
    const auto qn(ast.get_qualified_name(p.name()));
    {
        auto sbf(ast.make_scoped_boilerplate_formatter(e));
ast.stream() << std::endl;
ast.stream() << "namespace {" << std::endl;
ast.stream() << std::endl;
ast.stream() << "template <typename HashableType>" << std::endl;
ast.stream() << "inline void combine(std::size_t& seed, const HashableType& value) {" << std::endl;
ast.stream() << "    std::hash<HashableType> hasher;" << std::endl;
ast.stream() << "    seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);" << std::endl;
ast.stream() << "}" << std::endl;

        ast.add_helper_methods(p.name().qualified().dot());
ast.stream() << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
        {
            const auto ns(ast.make_namespaces(p.name()));
            auto snf(ast.make_scoped_namespace_formatter(ns));
            const auto sn(p.name().simple());
            const auto qn(ast.get_qualified_name(p.name()));
            const auto attr(p.value_attribute());
ast.stream() << std::endl;
ast.stream() << "std::size_t " << sn << "_hasher::hash(const " << sn << "& v) {" << std::endl;
ast.stream() << "    std::size_t seed(0);" << std::endl;
            if (ast.requires_hashing_helper_method(attr))
ast.stream() << "    combine(seed, hash_" << attr.parsed_type().qualified().identifiable() << "(v." << attr.name().simple() << "()));" << std::endl;
            else
ast.stream() << "    combine(seed, v." << attr.name().simple() << "());" << std::endl;
ast.stream() << "    return seed;" << std::endl;
ast.stream() << "}" << std::endl;
ast.stream() << std::endl;
        } // snf
    } // sbf
    ast.update_artefact();
    stp.end_transform(a);
}
}
