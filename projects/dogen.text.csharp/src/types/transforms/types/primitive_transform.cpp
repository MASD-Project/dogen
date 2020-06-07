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
#include <iostream>
#include "dogen.physical/types/helpers/meta_name_factory.hpp"
#include "dogen.logical/types/entities/structural/primitive.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.utility/types/formatters/sequence_formatter.hpp"
#include "dogen.text.csharp/types/traits.hpp"
#include "dogen.text.csharp/types/transforms/types/traits.hpp"
#include "dogen.text.csharp/types/transforms/assistant.hpp"
#include "dogen.text.csharp/types/transforms/types/primitive_transform.hpp"

namespace dogen::text::csharp::transforms::types {
namespace {

const std::string transform_id("text.csharp.transforms.types.primitive_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

const physical::entities::archetype& primitive_transform::static_archetype() {
    static physical::entities::archetype r([]() {
        physical::entities::archetype r;
        using pmnf = physical::helpers::meta_name_factory;
        r.meta_name(pmnf::make(csharp::traits::backend_sn(),
            traits::facet_sn(), traits::primitive_archetype_sn()));
        using lmnf = logical::helpers::meta_name_factory;
        r.logical_meta_element_id(lmnf::make_primitive_name().qualified().dot());
        r.referencing_status(physical::entities::referencing_status::facet_default);
        return r;
    }());
    return r;
}

const physical::entities::archetype& primitive_transform::archetype() const {
    return static_archetype();
}

boost::filesystem::path primitive_transform::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path(n, archetype().meta_name().qualified());
}

std::list<std::string> primitive_transform::
inclusion_dependencies(const logical::entities::element& /*e*/) const {
    std::list<std::string> r;
    return r;
}

void primitive_transform::apply(const context& ctx, const logical::entities::element& e,
    physical::entities::artefact& a) const {
    tracing::scoped_transform_tracer stp(lg, "primitive transform",
        transform_id, e.name().qualified().dot(), *ctx.tracer(), e);

    const auto id(e.name().qualified().dot());
    assistant ast(ctx, e, archetype().meta_name(), a);
    const auto& p(ast.as<logical::entities::structural::primitive>(archetype().meta_name().qualified(), e));
    {
        const auto sn(e.name().simple());
        auto sbf(ast.make_scoped_boilerplate_formatter(e));
        {
ast.stream() << "using System;" << std::endl;
ast.stream() << std::endl;
            const auto ns(ast.make_namespaces(e.name()));
            auto snf(ast.make_scoped_namespace_formatter(ns));
            ast.comment(e.documentation(), 1/*indent*/);
ast.stream() << "    public sealed class " << sn << std::endl;
ast.stream() << "    {" << std::endl;
            if (!ctx.element_properties().helper_properties().empty())
                ast.add_helper_methods(id);

            /*
             * Properties
             */
ast.stream() << "        #region Properties" << std::endl;
            const auto& attr(p.value_attribute());
            ast.comment(attr.documentation(), 2/*indent*/);
ast.stream() << "        public " << ast.get_qualified_name(attr.parsed_type()) << " " << attr.name().simple() << " { get; " << (p.is_immutable() ? "internal " : "") << "set; }" << std::endl;
ast.stream() << "        #endregion" << std::endl;
ast.stream() << std::endl;
            /*
             * Constructors.
             */
ast.stream() << "        #region Constructors" << std::endl;
ast.stream() << "        public " << sn << "() { }" << std::endl;
ast.stream() << "        public " << sn << "(" << ast.get_qualified_name(attr.parsed_type()) << " " << ast.make_argument_name(attr) << ")" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            " << attr.name().simple() << " = " << ast.make_argument_name(attr) << ";" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << "        #endregion" << std::endl;
ast.stream() << std::endl;
            /*
             * Equals
             */
ast.stream() << "        #region Equality" << std::endl;
ast.stream() << "        public override bool Equals(object obj)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            if (ReferenceEquals(null, obj)) return false;" << std::endl;
ast.stream() << "            if (ReferenceEquals(this, obj)) return true;" << std::endl;
ast.stream() << "            if (obj.GetType() != GetType()) return false;" << std::endl;
ast.stream() << std::endl;
ast.stream() << "            var value = obj as " << sn << ";" << std::endl;
ast.stream() << "            if (value == null) return false;" << std::endl;
ast.stream() << "            return" << std::endl;
             if (attr.parsed_type().is_current_simple_type()) {
                if (attr.parsed_type().is_floating_point()) {
ast.stream() << "                NearlyEqual(" << attr.name().simple() << ", value." << attr.name().simple() << ");" << std::endl;
                } else {
ast.stream() << "                " << attr.name().simple() << " == value." << attr.name().simple() << ";" << std::endl;
                }
           } else {
ast.stream() << "                " << attr.name().simple() << " != null && value." << attr.name().simple() << " != null &&" << std::endl;
ast.stream() << "                " << attr.name().simple() << ".Equals(value." << attr.name().simple() << ");" << std::endl;
            }
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        public static bool operator ==(" << sn << " lhs, " << sn << " rhs)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            if (Object.ReferenceEquals(lhs, rhs))" << std::endl;
ast.stream() << "                return true;" << std::endl;
ast.stream() << std::endl;
ast.stream() << "            return !Object.ReferenceEquals(null, lhs) && lhs.Equals(rhs);" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        public static bool operator !=(" << sn << " lhs, " << sn << " rhs)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            return !(lhs == rhs);" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        public override int GetHashCode()" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            unchecked" << std::endl;
ast.stream() << "            {" << std::endl;
ast.stream() << "                // Choose large primes to avoid hashing collisions" << std::endl;
ast.stream() << "                const int HashingBase = (int) 2166136261;" << std::endl;
ast.stream() << "                const int HashingMultiplier = 16777619;" << std::endl;
ast.stream() << std::endl;
ast.stream() << "                int hash = HashingBase;" << std::endl;
                if (attr.parsed_type().is_current_simple_type()) {
ast.stream() << "                hash = (hash * HashingMultiplier) ^ " << attr.name().simple() << ".GetHashCode();" << std::endl;
                } else {
ast.stream() << "                hash = (hash * HashingMultiplier) ^" << std::endl;
ast.stream() << "                    (!" << ast.reference_equals(attr) << ".ReferenceEquals(null, " << attr.name().simple() << ") ? " << attr.name().simple() << ".GetHashCode() : 0);" << std::endl;
                }
ast.stream() << "                return hash;" << std::endl;
ast.stream() << "            }" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << "        #endregion" << std::endl;
ast.stream() << "    }" << std::endl;
        } // snf
    } // sbf
    ast.update_artefact();
    stp.end_transform(a);
}
}
