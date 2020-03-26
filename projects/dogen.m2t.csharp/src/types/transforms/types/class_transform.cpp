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
#include "dogen.physical/types/helpers/name_factory.hpp"
#include "dogen.logical/types/entities/structural/object.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.m2t/types/formatters/sequence_formatter.hpp"
#include "dogen.m2t.csharp/types/traits.hpp"
#include "dogen.m2t.csharp/types/transforms/types/traits.hpp"
#include "dogen.m2t.csharp/types/transforms/assistant.hpp"
#include "dogen.m2t.csharp/types/transforms/types/class_transform.hpp"

namespace dogen::m2t::csharp::transforms::types {

std::string class_transform::static_id() {
    return traits::class_archetype();
}

std::string class_transform::id() const {
    return static_id();
}

physical::entities::name
class_transform::physical_name() const {
    using physical::helpers::name_factory;
    static const auto r(name_factory::make(csharp::traits::backend(),
        traits::facet(), class_transform::static_id()));
    return r;
}

const logical::entities::name& class_transform::meta_name() const {
    using logical::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_object_name());
    return r;
}

boost::filesystem::path class_transform::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path(n, static_id());
}

std::list<std::string> class_transform::
inclusion_dependencies(const logical::entities::element& /*e*/) const {
    std::list<std::string> r;
    return r;
}

physical::entities::artefact class_transform::
apply(const context& ctx, const logical::entities::element& e) const {
    const auto id(e.name().qualified().dot());
    assistant a(ctx, e, physical_name().location());
    const auto& o(a.as<logical::entities::structural::object>(static_id(), e));
    {
        const auto sn(e.name().simple());
        auto sbf(a.make_scoped_boilerplate_formatter(e));
        {
a.stream() << "using System;" << std::endl;
a.stream() << std::endl;
            const auto ns(a.make_namespaces(e.name()));
            auto snf(a.make_scoped_namespace_formatter(ns));
            a.comment(e.documentation(), 1/*indent*/);
            if (!o.in_inheritance_relationship() || !o.is_child()) {
a.stream() << "    public " << a.make_inheritance_keyword_text(o) << "class " << sn << std::endl;
            } else {
                const auto& pn(o.parents().front());
                const auto pqn(a.get_qualified_name(pn));
a.stream() << "    public " << a.make_inheritance_keyword_text(o) << "class " << sn << " : " << pqn << std::endl;
            }
a.stream() << "    {" << std::endl;
            if (!o.local_attributes().empty()) {
                if (!ctx.element_properties().helper_properties().empty())
                    a.add_helper_methods(id);

                /*
                * Properties
                */
a.stream() << "        #region Properties" << std::endl;
                for (const auto& attr : o.local_attributes()) {
                    a.comment(attr.documentation(), 2/*indent*/);
a.stream() << "        public " << a.get_qualified_name(attr.parsed_type()) << " " << attr.name().simple() << " { get; " << (o.is_immutable() ? "internal " : "") << "set; }" << std::endl;
                }
a.stream() << "        #endregion" << std::endl;
a.stream() << std::endl;
            }

            /*
             * Constructors.
             */
a.stream() << "        #region Constructors" << std::endl;
a.stream() << "        public " << sn << "() { }" << std::endl;
            if (!o.all_attributes().empty()) {
                const auto attr_count(o.all_attributes().size());
                if (attr_count == 1) {
                     const auto attr(*o.all_attributes().begin());
a.stream() << "        public " << sn << "(" << a.get_qualified_name(attr.parsed_type()) << " " << a.make_argument_name(attr) << ")" << std::endl;
                } else {
a.stream() << std::endl;
a.stream() << "        public " << sn << "(" << std::endl;
                    m2t::formatters::sequence_formatter sf(attr_count);
                    sf.postfix_configuration().last(")");
                    for (const auto attr : o.all_attributes()) {
a.stream() << "            " << a.get_qualified_name(attr.parsed_type()) << " " << a.make_argument_name(attr) << sf.postfix() << std::endl;
                        sf.next();
                    }
                }

                if (!o.parents().empty()) {
                    const auto& pair(*o.inherited_attributes().begin());
                    const auto& pattrs(pair.second);
                    const auto size(pattrs.size());

                    if (size == 0) {
a.stream() << "            : base()" << std::endl;
                    } else if (size == 1) {
a.stream() << "            : base(" << a.make_argument_name(pattrs.front()) << ")" << std::endl;
                    } else {
                        m2t::formatters::sequence_formatter sf(size);
                        sf.postfix_configuration().last(")");
                        sf.prefix_configuration().first(",").not_first(",");
a.stream() << "            : base(" << std::endl;
                        for (const auto& pattr : pattrs) {
a.stream() << "                " << a.make_argument_name(pattr) << sf.postfix() << std::endl;
                            sf.next();
                        }
                    }
                }
a.stream() << "        {" << std::endl;
                if (o.local_attributes().empty()) {
a.stream() << "            // no properties" << std::endl;
                } else {
                    for (const auto& attr : o.local_attributes()) {
a.stream() << "            " << attr.name().simple() << " = " << a.make_argument_name(attr) << ";" << std::endl;
                    }
                }
a.stream() << "        }" << std::endl;
            }
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
            if (o.local_attributes().empty()) {
                if (!o.parents().empty()) {
a.stream() << "            return (value != null && base.Equals(value));" << std::endl;
                } else {
a.stream() << "            return value != null;" << std::endl;
                }
            } else {
                if (!o.parents().empty()) {
a.stream() << "            if (value == null || !base.Equals(value)) return false;" << std::endl;
                } else {
a.stream() << "            if (value == null) return false;" << std::endl;
                }
a.stream() << std::endl;
a.stream() << "            return" << std::endl;
                m2t::formatters::sequence_formatter sf(o.local_attributes().size());
                sf.element_separator("");
                sf.postfix_configuration().not_last(" &&");
                sf.postfix_configuration().last(";");
                for (const auto& attr : o.local_attributes()) {
                    if (attr.parsed_type().is_current_simple_type()) {
                        if (attr.parsed_type().is_floating_point()) {
a.stream() << "                NearlyEqual(" << attr.name().simple() << ", value." << attr.name().simple() << ")" << sf.postfix() << std::endl;
                        } else {
a.stream() << "                " << attr.name().simple() << " == value." << attr.name().simple() << sf.postfix() << std::endl;
                        }
                    } else {
a.stream() << "                " << attr.name().simple() << " != null && value." << attr.name().simple() << " != null &&" << std::endl;
a.stream() << "                " << attr.name().simple() << ".Equals(value." << attr.name().simple() << ")" << sf.postfix() << std::endl;
                    }
                    sf.next();
                }
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
            if (o.local_attributes().empty()) {
a.stream() << "            return 0;" << std::endl;
            } else {
a.stream() << "            unchecked" << std::endl;
a.stream() << "            {" << std::endl;
a.stream() << "                // Choose large primes to avoid hashing collisions" << std::endl;
a.stream() << "                const int HashingBase = (int) 2166136261;" << std::endl;
a.stream() << "                const int HashingMultiplier = 16777619;" << std::endl;
a.stream() << std::endl;
a.stream() << "                int hash = HashingBase;" << std::endl;
                for (const auto& attr : o.local_attributes()) {
                    if (attr.parsed_type().is_current_simple_type()) {
a.stream() << "                hash = (hash * HashingMultiplier) ^ " << attr.name().simple() << ".GetHashCode();" << std::endl;
                    } else {
a.stream() << "                hash = (hash * HashingMultiplier) ^" << std::endl;
a.stream() << "                    (!" << a.reference_equals(attr) << ".ReferenceEquals(null, " << attr.name().simple() << ") ? " << attr.name().simple() << ".GetHashCode() : 0);" << std::endl;
                    }
                }
a.stream() << "                return hash;" << std::endl;
a.stream() << "            }" << std::endl;
            }
a.stream() << "        }" << std::endl;
a.stream() << "        #endregion" << std::endl;
            if (o.in_inheritance_relationship())
            {
a.stream() << std::endl;
a.stream() << "        #region Dumpers" << std::endl;
                if (o.is_parent() && !o.is_child()) {
a.stream() << "        internal abstract string Dump();" << std::endl;
                } else if (o.is_leaf()) {
a.stream() << "        internal override string Dump()" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            return " << sn << "Dumper.Dump(this);" << std::endl;
a.stream() << "        }" << std::endl;
                }
a.stream() << "        #endregion" << std::endl;
        }
a.stream() << "    }" << std::endl;
        } // snf
    } // sbf
    return a.make_artefact();
}
}
