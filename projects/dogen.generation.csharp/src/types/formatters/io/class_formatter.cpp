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
#include "dogen.assets/types/meta_model/structural/object.hpp"
#include "dogen.assets/types/helpers/meta_name_factory.hpp"
#include "dogen.generation/types/formatters/sequence_formatter.hpp"
#include "dogen.generation.csharp/types/traits.hpp"
#include "dogen.generation.csharp/types/formatters/io/traits.hpp"
#include "dogen.generation.csharp/types/formatters/assistant.hpp"
#include "dogen.generation.csharp/types/formatters/io/class_formatter.hpp"

namespace dogen::generation::csharp::formatters::io {

std::string class_formatter::static_id() {
    return traits::class_archetype();
}

std::string class_formatter::id() const {
    return static_id();
}

physical::location class_formatter::archetype_location() const {
    static physical::location
        r(csharp::traits::kernel(), csharp::traits::backend(),
          traits::facet(),
          class_formatter::static_id());
    return r;
}

const assets::meta_model::name& class_formatter::meta_name() const {
    using assets::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_object_name());
    return r;
}

std::string class_formatter::family() const {
    return csharp::traits::csharp_family();
}

boost::filesystem::path class_formatter::full_path(
    const formattables::locator& l, const assets::meta_model::name& n) const {
    return l.make_full_path(n, static_id());
}

std::list<std::string> class_formatter::
inclusion_dependencies(const assets::meta_model::element& /*e*/) const {
    std::list<std::string> r;
    return r;
}

extraction::meta_model::artefact class_formatter::
format(const context& ctx, const assets::meta_model::element& e) const {
    assistant a(ctx, e, archetype_location());
    const auto& o(a.as<assets::meta_model::structural::object>(static_id(), e));
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

                generation::formatters::sequence_formatter sf(o.local_attributes().size());
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
