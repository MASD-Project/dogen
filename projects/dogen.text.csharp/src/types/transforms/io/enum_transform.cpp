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
#include "dogen.identification/types/helpers/physical_meta_name_factory.hpp"
#include "dogen.logical/types/entities/structural/enumeration.hpp"
#include "dogen.identification/types/helpers/logical_meta_name_factory.hpp"
#include "dogen.utility/types/formatters/sequence_formatter.hpp"
#include "dogen.text.csharp/types/traits.hpp"
#include "dogen.text.csharp/types/transforms/io/traits.hpp"
#include "dogen.text.csharp/types/transforms/assistant.hpp"
#include "dogen.text.csharp/types/transforms/io/enum_transform.hpp"
#include "dogen.text.csharp/types/transforms/io/enum_factory.hpp"

namespace dogen::text::csharp::transforms::io {
namespace {

const std::string transform_id("text.csharp.transforms.io.enum_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

const physical::entities::archetype& enum_transform::static_archetype() {
    static auto r(enum_factory::make());
    return r;
}

const physical::entities::archetype& enum_transform::archetype() const {
    return static_archetype();
}

std::list<std::string> enum_transform::
inclusion_dependencies(const logical::entities::element& /*e*/) const {
    std::list<std::string> r;
    return r;
}

void enum_transform::apply(const context& ctx, const logical::entities::element& e,
   physical::entities::artefact& a) const {
   tracing::scoped_transform_tracer stp(lg, "enum",
       transform_id, e.name().qualified().dot(), *ctx.tracer(), e);

    assistant ast(ctx, e, archetype().meta_name(), a);
    const auto& ye(ast.as<logical::entities::structural::enumeration>(archetype().meta_name().id().value(), e));
    {
        const auto sn(e.name().simple());
        const auto qn(ast.get_qualified_name(e.name()));
        auto sbf(ast.make_scoped_boilerplate_formatter(e));
        {
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
ast.stream() << "            string valueAsString = \"Unsupported Value\";" << std::endl;
ast.stream() << "            switch (value)" << std::endl;
ast.stream() << "            {" << std::endl;
            for (const auto& en : ye.enumerators()) {
ast.stream() << "                case " << ye.name().simple() << "." << en.name().simple() << ":" << std::endl;
ast.stream() << "                    valueAsString = \"" << en.name().simple() << "\";" << std::endl;
ast.stream() << "                    break;" << std::endl;
            }
ast.stream() << "            }" << std::endl;
ast.stream() << std::endl;
ast.stream() << "            assistant.Add(\"value\", valueAsString);" << std::endl;
ast.stream() << "            assistant.AddEndObject();" << std::endl;
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
    stp.end_transform(a);
}
}
