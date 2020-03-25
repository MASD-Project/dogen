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
#include <iostream>
#include "dogen.physical/types/helpers/name_factory.hpp"
#include "dogen.logical/types/entities/structural/primitive.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.m2t/types/formatters/sequence_formatter.hpp"
#include "dogen.m2t.csharp/types/traits.hpp"
#include "dogen.m2t.csharp/types/transforms/types/traits.hpp"
#include "dogen.m2t.csharp/types/transforms/assistant.hpp"
#include "dogen.m2t.csharp/types/transforms/types/primitive_transform.hpp"

namespace dogen::m2t::csharp::transforms::types {

std::string primitive_transform::static_id() {
    return traits::primitive_archetype();
}

std::string primitive_transform::id() const {
    return static_id();
}

physical::entities::location primitive_transform::archetype_location() const {
    static physical::entities::location
        r(csharp::traits::kernel(), csharp::traits::backend(),
          csharp::traits::empty_part(), traits::facet(),
          primitive_transform::static_id());
    return r;
}

physical::entities::name
primitive_transform::physical_name() const {
    using physical::helpers::name_factory;
    static const auto r(name_factory::make(csharp::traits::backend(),
        traits::facet(), primitive_transform::static_id()));
    return r;
}

const logical::entities::name& primitive_transform::meta_name() const {
    using logical::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_primitive_name());
    return r;
}

boost::filesystem::path primitive_transform::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path(n, static_id());
}

std::list<std::string> primitive_transform::
inclusion_dependencies(const logical::entities::element& /*e*/) const {
    std::list<std::string> r;
    return r;
}

physical::entities::artefact primitive_transform::
apply(const context& ctx, const logical::entities::element& e) const {
    const auto id(e.name().qualified().dot());
    assistant a(ctx, e, archetype_location());
    const auto& p(a.as<logical::entities::structural::primitive>(static_id(), e));
    {
        const auto sn(e.name().simple());
        auto sbf(a.make_scoped_boilerplate_formatter(e));
        {
a.stream() << "using System;" << std::endl;
a.stream() << std::endl;
            const auto ns(a.make_namespaces(e.name()));
            auto snf(a.make_scoped_namespace_formatter(ns));
            a.comment(e.documentation(), 1/*indent*/);
a.stream() << "    public sealed class " << sn << std::endl;
a.stream() << "    {" << std::endl;
            if (!ctx.element_properties().helper_properties().empty())
                a.add_helper_methods(id);

            /*
             * Properties
             */
a.stream() << "        #region Properties" << std::endl;
            const auto& attr(p.value_attribute());
            a.comment(attr.documentation(), 2/*indent*/);
a.stream() << "        public " << a.get_qualified_name(attr.parsed_type()) << " " << attr.name().simple() << " { get; " << (p.is_immutable() ? "internal " : "") << "set; }" << std::endl;
a.stream() << "        #endregion" << std::endl;
a.stream() << std::endl;
            /*
             * Constructors.
             */
a.stream() << "        #region Constructors" << std::endl;
a.stream() << "        public " << sn << "() { }" << std::endl;
a.stream() << "        public " << sn << "(" << a.get_qualified_name(attr.parsed_type()) << " " << a.make_argument_name(attr) << ")" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            " << attr.name().simple() << " = " << a.make_argument_name(attr) << ";" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << "        #endregion" << std::endl;
a.stream() << std::endl;
            /*
             * Equals
             */
a.stream() << "        #region Equality" << std::endl;
a.stream() << "        public override bool Equals(object obj)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            if (ReferenceEquals(null, obj)) return false;" << std::endl;
a.stream() << "            if (ReferenceEquals(this, obj)) return true;" << std::endl;
a.stream() << "            if (obj.GetType() != GetType()) return false;" << std::endl;
a.stream() << std::endl;
a.stream() << "            var value = obj as " << sn << ";" << std::endl;
a.stream() << "            if (value == null) return false;" << std::endl;
a.stream() << "            return" << std::endl;
             if (attr.parsed_type().is_current_simple_type()) {
                if (attr.parsed_type().is_floating_point()) {
a.stream() << "                NearlyEqual(" << attr.name().simple() << ", value." << attr.name().simple() << ");" << std::endl;
                } else {
a.stream() << "                " << attr.name().simple() << " == value." << attr.name().simple() << ";" << std::endl;
                }
           } else {
a.stream() << "                " << attr.name().simple() << " != null && value." << attr.name().simple() << " != null &&" << std::endl;
a.stream() << "                " << attr.name().simple() << ".Equals(value." << attr.name().simple() << ");" << std::endl;
            }
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public static bool operator ==(" << sn << " lhs, " << sn << " rhs)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            if (Object.ReferenceEquals(lhs, rhs))" << std::endl;
a.stream() << "                return true;" << std::endl;
a.stream() << std::endl;
a.stream() << "            return !Object.ReferenceEquals(null, lhs) && lhs.Equals(rhs);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public static bool operator !=(" << sn << " lhs, " << sn << " rhs)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            return !(lhs == rhs);" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public override int GetHashCode()" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            unchecked" << std::endl;
a.stream() << "            {" << std::endl;
a.stream() << "                // Choose large primes to avoid hashing collisions" << std::endl;
a.stream() << "                const int HashingBase = (int) 2166136261;" << std::endl;
a.stream() << "                const int HashingMultiplier = 16777619;" << std::endl;
a.stream() << std::endl;
a.stream() << "                int hash = HashingBase;" << std::endl;
                if (attr.parsed_type().is_current_simple_type()) {
a.stream() << "                hash = (hash * HashingMultiplier) ^ " << attr.name().simple() << ".GetHashCode();" << std::endl;
                } else {
a.stream() << "                hash = (hash * HashingMultiplier) ^" << std::endl;
a.stream() << "                    (!" << a.reference_equals(attr) << ".ReferenceEquals(null, " << attr.name().simple() << ") ? " << attr.name().simple() << ".GetHashCode() : 0);" << std::endl;
                }
a.stream() << "                return hash;" << std::endl;
a.stream() << "            }" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << "        #endregion" << std::endl;
a.stream() << "    }" << std::endl;
        } // snf
    } // sbf
    return a.make_artefact();
}
}
