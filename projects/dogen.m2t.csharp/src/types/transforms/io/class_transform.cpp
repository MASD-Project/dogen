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
#include "dogen.m2t/types/formatters/sequence_formatter.hpp"
#include "dogen.m2t.csharp/types/traits.hpp"
#include "dogen.m2t.csharp/types/transforms/io/traits.hpp"
#include "dogen.m2t.csharp/types/transforms/assistant.hpp"
#include "dogen.m2t.csharp/types/transforms/io/class_transform.hpp"

namespace dogen::m2t::csharp::transforms::io {

std::string class_transform::static_id() {
    return traits::class_archetype_qn();
}

std::string class_transform::id() const {
    return static_id();
}

physical::entities::meta_name
class_transform::physical_meta_name() const {
    using physical::helpers::meta_name_factory;
    static const auto r(meta_name_factory::make(csharp::traits::backend_sn(),
        traits::facet_sn(), traits::class_archetype_sn()));
    return r;
}

const logical::entities::name& class_transform::logical_meta_name() const {
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
    assistant a(ctx, e, physical_meta_name());
    const auto& o(a.as<logical::entities::structural::object>(static_id(), e));
    {
        const auto sn(e.name().simple());
        const auto qn(a.get_qualified_name(e.name()));
        auto sbf(a.make_scoped_boilerplate_formatter(e));
        {
a.stream() << "using System;" << std::endl;
a.stream() << std::endl;
            const auto ns(a.make_namespaces(e.name()));
            auto snf(a.make_scoped_namespace_formatter(ns));
            const bool has_attributes(!o.local_attributes().empty());
a.stream() << "    /// <summary>" << std::endl;
a.stream() << "    /// Generates sequences of " << sn << "." << std::endl;
a.stream() << "    /// </summary>" << std::endl;
a.stream() << "    public static class " << sn << "Dumper" << std::endl;
a.stream() << "    {" << std::endl;
a.stream() << "        static internal void Dump(AssistantDumper assistant, " << sn << " value, bool withSeparator = false)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            assistant.IncrementDepth();" << std::endl;
a.stream() << "            if (assistant.MaximumDepthExceeded())" << std::endl;
a.stream() << "                return;" << std::endl;
a.stream() << std::endl;
a.stream() << "            assistant.AddStartObject();" << std::endl;
a.stream() << "            assistant.AddType(\"" << qn << "\", true/*withSeparator*/);" << std::endl;
a.stream() << "            if (value == null)" << std::endl;
a.stream() << "            {" << std::endl;
a.stream() << "                assistant.Add(\"data\", \"<null>\");" << std::endl;
a.stream() << "                assistant.AddEndObject();" << std::endl;
a.stream() << "                return;" << std::endl;
a.stream() << "            }" << std::endl;
a.stream() << std::endl;
a.stream() << "            assistant.AddKey(\"data\");" << std::endl;
a.stream() << "            assistant.AddPairSeparator();" << std::endl;
a.stream() << "            assistant.AddStartObject();" << std::endl;
                if (!o.parents().empty()) {
                    const auto& pn(o.parents().front());
                    const auto pqn(a.get_qualified_name(pn));
a.stream() << "            assistant.AddKey(\"__parent_0__\");" << std::endl;
a.stream() << "            assistant.AddPairSeparator();" << std::endl;
a.stream() << "            " << pqn << "Dumper.Dump(assistant, value" << (has_attributes ? ", true/*withSeparator*/" : "") << ");" << std::endl;
                }

                m2t::formatters::sequence_formatter sf(o.local_attributes().size());
                sf.element_separator("");
                sf.postfix_configuration().not_last(", true/*withSeparator*/");
                sf.postfix_configuration().last("");

                for (const auto& attr : o.local_attributes()) {
                    const auto oap(a.get_assistant_properties(attr));
                    if (oap && oap->requires_assistance()) {
a.stream() << "            assistant.Add(\"" << attr.name().simple() << "\", value." << attr.name().simple() << sf.postfix() << ");" << std::endl;
                    } else {
                        const auto attr_qn(a.get_qualified_name(attr.parsed_type().current()));
a.stream() << "            assistant.AddKey(\"" << attr.name().simple() << "\");" << std::endl;
a.stream() << "            assistant.AddPairSeparator();" << std::endl;
a.stream() << "            " << attr_qn << "Dumper.Dump(assistant, value." << attr.name().simple() << sf.postfix() << ");" << std::endl;
                    }

                    sf.next();
                }
a.stream() << "            assistant.AddEndObject(); // data" << std::endl;
a.stream() << "            assistant.AddEndObject(); // main object" << std::endl;
a.stream() << "            assistant.HandleMemberSeparator(withSeparator);" << std::endl;
a.stream() << std::endl;
a.stream() << "            assistant.DecrementDepth();" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public static string Dump(" << sn << " value)" << std::endl;
a.stream() << "        {" << std::endl;
                if (o.is_parent()) {
a.stream() << "            return value.Dump();" << std::endl;
                } else {
a.stream() << "            var assistant = new AssistantDumper();" << std::endl;
a.stream() << "            Dump(assistant, value);" << std::endl;
a.stream() << "            return assistant.ToString();" << std::endl;
                }
a.stream() << "        }" << std::endl;
a.stream() << "    }" << std::endl;
        }
    } // sbf
    return a.make_artefact();
}
}
