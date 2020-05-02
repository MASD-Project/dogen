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
#include "dogen.logical/types/entities/structural/primitive.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.m2t/types/formatters/sequence_formatter.hpp"
#include "dogen.m2t.csharp/types/traits.hpp"
#include "dogen.m2t.csharp/types/transforms/io/traits.hpp"
#include "dogen.m2t.csharp/types/transforms/assistant.hpp"
#include "dogen.m2t.csharp/types/transforms/io/primitive_transform.hpp"

namespace dogen::m2t::csharp::transforms::io {

std::string primitive_transform::static_id() {
    return traits::primitive_archetype_qn();
}

std::string primitive_transform::id() const {
    return static_id();
}

physical::entities::meta_name
primitive_transform::physical_meta_name() const {
    using physical::helpers::meta_name_factory;
    static const auto r(meta_name_factory::make(csharp::traits::backend_sn(),
        traits::facet_sn(), traits::primitive_archetype_sn()));
    return r;
}

physical::entities::archetype primitive_transform::archetype() const {
    static physical::entities::archetype r([]() {
        physical::entities::archetype r;
        using physical::helpers::meta_name_factory;
        r.meta_name(meta_name_factory::make(csharp::traits::backend_sn(),
            traits::facet_sn(), traits::primitive_archetype_sn()));
        return r;
    }());
    return r;
}

const logical::entities::name& primitive_transform::logical_meta_name() const {
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

void primitive_transform::apply(const context& ctx, const logical::entities::element& e,
    physical::entities::artefact& a) const {
    assistant ast(ctx, e, physical_meta_name(), a);
    const auto& p(ast.as<logical::entities::structural::primitive>(static_id(), e));
    {
        const auto sn(e.name().simple());
        const auto qn(ast.get_qualified_name(e.name()));
        auto sbf(ast.make_scoped_boilerplate_formatter(e));
        {
ast.stream() << "using System;" << std::endl;
ast.stream() << std::endl;
            const auto ns(ast.make_namespaces(e.name()));
            auto snf(ast.make_scoped_namespace_formatter(ns));
ast.stream() << "    /// <summary>" << std::endl;
ast.stream() << "    /// Generates sequences of " << sn << "." << std::endl;
ast.stream() << "    /// </summary>" << std::endl;
ast.stream() << "    public static class " << sn << "Dumper" << std::endl;
ast.stream() << "    {" << std::endl;
ast.stream() << "        static internal void Dump(AssistantDumper assistant, " << sn << " value, bool withSeparator = false)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            assistant.IncrementDepth();" << std::endl;
ast.stream() << "            if (assistant.MaximumDepthExceeded())" << std::endl;
ast.stream() << "                return;" << std::endl;
ast.stream() << std::endl;
ast.stream() << "            assistant.AddStartObject();" << std::endl;
ast.stream() << "            assistant.AddType(\"" << qn << "\", true/*withSeparator*/);" << std::endl;
ast.stream() << "            if (value == null)" << std::endl;
ast.stream() << "            {" << std::endl;
ast.stream() << "                assistant.Add(\"data\", \"<null>\");" << std::endl;
ast.stream() << "                assistant.AddEndObject();" << std::endl;
ast.stream() << "                return;" << std::endl;
ast.stream() << "            }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "            assistant.AddKey(\"data\");" << std::endl;
ast.stream() << "            assistant.AddPairSeparator();" << std::endl;
ast.stream() << "            assistant.AddStartObject();" << std::endl;
            const auto attr(p.value_attribute());
            const auto oap(ast.get_assistant_properties(attr));
            if (oap && oap->requires_assistance()) {
ast.stream() << "            assistant.Add(\"" << attr.name().simple() << "\", value." << attr.name().simple() << ");" << std::endl;
            } else {
                const auto attr_qn(ast.get_qualified_name(attr.parsed_type().current()));
ast.stream() << "            assistant.AddKey(\"" << attr.name().simple() << "\");" << std::endl;
ast.stream() << "            assistant.AddPairSeparator();" << std::endl;
ast.stream() << "            " << attr_qn << "Dumper.Dump(assistant, value." << attr.name().simple() << ";" << std::endl;
            }
ast.stream() << "            assistant.AddEndObject(); // data" << std::endl;
ast.stream() << "            assistant.AddEndObject(); // main object" << std::endl;
ast.stream() << "            assistant.HandleMemberSeparator(withSeparator);" << std::endl;
ast.stream() << std::endl;
ast.stream() << "            assistant.DecrementDepth();" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        public static string Dump(" << sn << " value)" << std::endl;
ast.stream() << "        {" << std::endl;
ast.stream() << "            var assistant = new AssistantDumper();" << std::endl;
ast.stream() << "            Dump(assistant, value);" << std::endl;
ast.stream() << "            return assistant.ToString();" << std::endl;
ast.stream() << "        }" << std::endl;
ast.stream() << "    }" << std::endl;
        }
    } // sbf

    ast.update_artefact();
}
}
