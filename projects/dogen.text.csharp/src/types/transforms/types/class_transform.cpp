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
#include "dogen.physical/types/helpers/meta_name_factory.hpp"
#include "dogen.logical/types/entities/structural/object.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.text/types/formatters/sequence_formatter.hpp"
#include "dogen.text.csharp/types/traits.hpp"
#include "dogen.text.csharp/types/transforms/types/traits.hpp"
#include "dogen.text.csharp/types/transforms/assistant.hpp"
#include "dogen.text.csharp/types/transforms/types/class_transform.hpp"

namespace dogen::text::csharp::transforms::types {

physical::entities::archetype class_transform::static_archetype() const {
    static physical::entities::archetype r([]() {
        physical::entities::archetype r;
        using pmnf = physical::helpers::meta_name_factory;
        r.meta_name(pmnf::make(csharp::traits::backend_sn(),
            traits::facet_sn(), traits::class_archetype_sn()));
        using lmnf = logical::helpers::meta_name_factory;
        r.logical_meta_element_id(lmnf::make_object_name().qualified().dot());
        return r;
    }());
    return r;
}

physical::entities::archetype class_transform::archetype() const {
    return static_archetype();
}

boost::filesystem::path class_transform::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path(n, archetype().meta_name().qualified());
}

std::list<std::string> class_transform::
inclusion_dependencies(const logical::entities::element& /*e*/) const {
    std::list<std::string> r;
    return r;
}

void class_transform::apply(const context& ctx, const logical::entities::element& e,
    physical::entities::artefact& a) const {
    const auto id(e.name().qualified().dot());
    assistant ast(ctx, e, archetype().meta_name(), a);
    const auto& o(ast.as<logical::entities::structural::object>(archetype().meta_name().qualified(), e));
    {
        const auto sn(e.name().simple());
        auto sbf(ast.make_scoped_boilerplate_formatter(e));
        {
ast.stream() << "using System;" << std::endl;
ast.stream() << std::endl;
            const auto ns(ast.make_namespaces(e.name()));
            auto snf(ast.make_scoped_namespace_formatter(ns));
            ast.comment(e.documentation(), 1/*indent*/);
            if (!o.in_inheritance_relationship() || !o.is_child()) {
ast.stream() << "    public " << ast.make_inheritance_keyword_text(o) << "class " << sn << std::endl;
            } else {
                const auto& pn(o.parents().front());
                const auto pqn(ast.get_qualified_name(pn));
ast.stream() << "    public " << ast.make_inheritance_keyword_text(o) << "class " << sn << " : " << pqn << std::endl;
            }
ast.stream() << "    {" << std::endl;
            if (!o.local_attributes().empty()) {
                if (!ctx.element_properties().helper_properties().empty())
                    ast.add_helper_methods(id);

                /*
                * Properties
                */
ast.stream() << "        #region Properties" << std::endl;
                for (const auto& attr : o.local_attributes()) {
                    ast.comment(attr.documentation(), 2/*indent*/);
ast.stream() << "        public " << ast.get_qualified_name(attr.parsed_type()) << " " << attr.name().simple() << " { get; " << (o.is_immutable() ? "internal " : "") << "set; }" << std::endl;
                }
ast.stream() << "        #endregion" << std::endl;
ast.stream() << std::endl;
            }

            /*
             * Constructors.
             */
ast.stream() << "        #region Constructors" << std::endl;
ast.stream() << "        public " << sn << "() { }" << std::endl;
            if (!o.all_attributes().empty()) {
                const auto attr_count(o.all_attributes().size());
                if (attr_count == 1) {
                     const auto attr(*o.all_attributes().begin());
ast.stream() << "        public " << sn << "(" << ast.get_qualified_name(attr.parsed_type()) << " " << ast.make_argument_name(attr) << ")" << std::endl;
                } else {
ast.stream() << std::endl;
ast.stream() << "        public " << sn << "(" << std::endl;
                    text::formatters::sequence_formatter sf(attr_count);
                    sf.postfix_configuration().last(")");
                    for (const auto& attr : o.all_attributes()) {
ast.stream() << "            " << ast.get_qualified_name(attr.parsed_type()) << " " << ast.make_argument_name(attr) << sf.postfix() << std::endl;
                        sf.next();
                    }
                }

                if (!o.parents().empty()) {
                    const auto& pair(*o.inherited_attributes().begin());
                    const auto& pattrs(pair.second);
                    const auto size(pattrs.size());

                    if (size == 0) {
ast.stream() << "            : base()" << std::endl;
                    } else if (size == 1) {
ast.stream() << "            : base(" << ast.make_argument_name(pattrs.front()) << ")" << std::endl;
                    } else {
                        text::formatters::sequence_formatter sf(size);
                        sf.postfix_configuration().last(")");
                        sf.prefix_configuration().first(",").not_first(",");
ast.stream() << "            : base(" << std::endl;
                        for (const auto& pattr : pattrs) {
ast.stream() << "                " << ast.make_argument_name(pattr) << sf.postfix() << std::endl;
                            sf.next();
                        }
                    }
                }
ast.stream() << "        {" << std::endl;
                if (o.local_attributes().empty()) {
ast.stream() << "            // no properties" << std::endl;
                } else {
                    for (const auto& attr : o.local_attributes()) {
ast.stream() << "            " << attr.name().simple() << " = " << ast.make_argument_name(attr) << ";" << std::endl;
                    }
                }
ast.stream() << "        }" << std::endl;
            }
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
            if (o.local_attributes().empty()) {
                if (!o.parents().empty()) {
ast.stream() << "            return (value != null && base.Equals(value));" << std::endl;
                } else {
ast.stream() << "            return value != null;" << std::endl;
                }
            } else {
                if (!o.parents().empty()) {
ast.stream() << "            if (value == null || !base.Equals(value)) return false;" << std::endl;
                } else {
ast.stream() << "            if (value == null) return false;" << std::endl;
                }
ast.stream() << std::endl;
ast.stream() << "            return" << std::endl;
                text::formatters::sequence_formatter sf(o.local_attributes().size());
                sf.element_separator("");
                sf.postfix_configuration().not_last(" &&");
                sf.postfix_configuration().last(";");
                for (const auto& attr : o.local_attributes()) {
                    if (attr.parsed_type().is_current_simple_type()) {
                        if (attr.parsed_type().is_floating_point()) {
ast.stream() << "                NearlyEqual(" << attr.name().simple() << ", value." << attr.name().simple() << ")" << sf.postfix() << std::endl;
                        } else {
ast.stream() << "                " << attr.name().simple() << " == value." << attr.name().simple() << sf.postfix() << std::endl;
                        }
                    } else {
ast.stream() << "                " << attr.name().simple() << " != null && value." << attr.name().simple() << " != null &&" << std::endl;
ast.stream() << "                " << attr.name().simple() << ".Equals(value." << attr.name().simple() << ")" << sf.postfix() << std::endl;
                    }
                    sf.next();
                }
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
            if (o.local_attributes().empty()) {
ast.stream() << "            return 0;" << std::endl;
            } else {
ast.stream() << "            unchecked" << std::endl;
ast.stream() << "            {" << std::endl;
ast.stream() << "                // Choose large primes to avoid hashing collisions" << std::endl;
ast.stream() << "                const int HashingBase = (int) 2166136261;" << std::endl;
ast.stream() << "                const int HashingMultiplier = 16777619;" << std::endl;
ast.stream() << std::endl;
ast.stream() << "                int hash = HashingBase;" << std::endl;
                for (const auto& attr : o.local_attributes()) {
                    if (attr.parsed_type().is_current_simple_type()) {
ast.stream() << "                hash = (hash * HashingMultiplier) ^ " << attr.name().simple() << ".GetHashCode();" << std::endl;
                    } else {
ast.stream() << "                hash = (hash * HashingMultiplier) ^" << std::endl;
ast.stream() << "                    (!" << ast.reference_equals(attr) << ".ReferenceEquals(null, " << attr.name().simple() << ") ? " << attr.name().simple() << ".GetHashCode() : 0);" << std::endl;
                    }
                }
ast.stream() << "                return hash;" << std::endl;
ast.stream() << "            }" << std::endl;
            }
ast.stream() << "        }" << std::endl;
ast.stream() << "        #endregion" << std::endl;
            if (o.in_inheritance_relationship())
            {
ast.stream() << std::endl;
ast.stream() << "        #region Dumpers" << std::endl;
                if (o.is_parent() && !o.is_child()) {
ast.stream() << "        internal abstract string Dump();" << std::endl;
                } else if (o.is_leaf()) {
ast.stream() << "        internal override string Dump()" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            return " << sn << "Dumper.Dump(this);" << std::endl;
ast.stream() << "        }" << std::endl;
                }
ast.stream() << "        #endregion" << std::endl;
        }
ast.stream() << "    }" << std::endl;
        } // snf
    } // sbf
    ast.update_artefact();
}
}
