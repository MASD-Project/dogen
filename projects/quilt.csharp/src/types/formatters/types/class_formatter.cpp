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
#include "dogen/quilt.csharp/types/formatters/types/class_formatter.hpp"
#include "dogen/quilt.csharp/types/formatters/assistant.hpp"
#include "dogen/quilt.csharp/types/formatters/types/traits.hpp"
#include "dogen/quilt.csharp/types/traits.hpp"
#include "dogen/formatters/types/sequence_formatter.hpp"
#include "dogen/yarn/types/object.hpp"
#include <boost/make_shared.hpp>
#include <typeinfo>

namespace dogen {
namespace quilt {
namespace csharp {
namespace formatters {
namespace types {

std::string class_formatter::static_artefact() {
    return traits::class_archetype();
}

std::string class_formatter::formatter_name() const {
    static auto r(archetype_location().archetype());
    return r;
}

annotations::archetype_location class_formatter::archetype_location() const {
    static annotations::archetype_location
        r(csharp::traits::family(), csharp::traits::kernel(),
          traits::facet(),
          class_formatter::static_artefact());
    return r;
}

std::type_index class_formatter::element_type_index() const {
    static auto r(std::type_index(typeid(yarn::object)));
    return r;
}

boost::filesystem::path class_formatter::
full_path(const formattables::locator& l, const yarn::name& n) const {
    return l.make_full_path(n, static_artefact());
}

std::list<std::string> class_formatter::
inclusion_dependencies(const yarn::element& /*e*/) const {
    std::list<std::string> r;
    return r;
}

dogen::formatters::artefact
class_formatter::format(const context& ctx, const yarn::element& e) const {
    const auto id(e.name().id());
    assistant a(ctx, archetype_location(), id);
    const auto& o(a.as<yarn::object>(static_artefact(), e));
    {
        const auto sn(e.name().simple());
        // const auto qn(a.get_qualified_name(e.name()));
        auto sbf(a.make_scoped_boilerplate_formatter());
        {
a.stream() << "using System;" << std::endl;
a.stream() << std::endl;
            const auto ns(a.make_namespaces(e.name()));
            auto snf(a.make_scoped_namespace_formatter(ns));
            a.comment(e.documentation(), 1/*indent*/);
a.stream() << "    public class " << sn << std::endl;
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
a.stream() << "        public " << a.get_qualified_name(attr.parsed_type()) << " " << attr.name().simple() << " { get; set; }" << std::endl;
                }
a.stream() << "        #endregion" << std::endl;
a.stream() << std::endl;
            }

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
a.stream() << "            return value != null;" << std::endl;
            } else {
a.stream() << "            if (value == null) return false;" << std::endl;
a.stream() << std::endl;
a.stream() << "            return" << std::endl;
                dogen::formatters::sequence_formatter sf(o.local_attributes().size());
                sf.element_separator("");
                sf.postfix_configuration().not_last(" &&");
                sf.postfix_configuration().last(";");
                for (const auto& attr : o.local_attributes()) {
                    if (attr.parsed_type().is_current_simple_type())
                        if (attr.parsed_type().is_floating_point())
a.stream() << "                NearlyEqual(" << attr.name().simple() << ", value." << attr.name().simple() << ")" << sf.postfix() << std::endl;
                        else
a.stream() << "                " << attr.name().simple() << " == value." << attr.name().simple() << sf.postfix() << std::endl;
                    else {
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
a.stream() << "    }" << std::endl;
        } // snf
    } // sbf
    return a.make_artefact();
}
} } } } }
