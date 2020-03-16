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
#include "dogen.logical/types/entities/structural/enumeration.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.generation/types/formatters/sequence_formatter.hpp"
#include "dogen.generation.csharp/types/traits.hpp"
#include "dogen.generation.csharp/types/formatters/io/traits.hpp"
#include "dogen.generation.csharp/types/formatters/assistant.hpp"
#include "dogen.generation.csharp/types/formatters/io/enum_formatter.hpp"

namespace dogen::generation::csharp::formatters::io {

std::string enum_formatter::static_id() {
    return traits::enum_archetype();
}

std::string enum_formatter::id() const {
    return static_id();
}

physical::entities::location enum_formatter::archetype_location() const {
    static physical::entities::location
        r(csharp::traits::kernel(), csharp::traits::backend(),
          traits::facet(),
          enum_formatter::static_id());
    return r;
}

const logical::entities::name& enum_formatter::meta_name() const {
    using logical::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_enumeration_name());
    return r;
}

std::string enum_formatter::family() const {
    return csharp::traits::csharp_family();
}

boost::filesystem::path enum_formatter::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path(n, static_id());
}

std::list<std::string> enum_formatter::
inclusion_dependencies(const logical::entities::element& /*e*/) const {
    std::list<std::string> r;
    return r;
}

extraction::entities::artefact enum_formatter::
format(const context& ctx, const logical::entities::element& e) const {
    assistant a(ctx, e, archetype_location());
    const auto& ye(a.as<logical::entities::structural::enumeration>(static_id(), e));
    {
        const auto sn(e.name().simple());
        const auto qn(a.get_qualified_name(e.name()));
        auto sbf(a.make_scoped_boilerplate_formatter(e));
        {
            const auto ns(a.make_namespaces(e.name()));
            auto snf(a.make_scoped_namespace_formatter(ns));
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
a.stream() << "            string valueAsString = \"Unsupported Value\";" << std::endl;
a.stream() << "            switch (value)" << std::endl;
a.stream() << "            {" << std::endl;
            for (const auto& en : ye.enumerators()) {
a.stream() << "                case " << ye.name().simple() << "." << en.name().simple() << ":" << std::endl;
a.stream() << "                    valueAsString = \"" << en.name().simple() << "\";" << std::endl;
a.stream() << "                    break;" << std::endl;
            }
a.stream() << "            }" << std::endl;
a.stream() << std::endl;
a.stream() << "            assistant.Add(\"value\", valueAsString);" << std::endl;
a.stream() << "            assistant.AddEndObject();" << std::endl;
a.stream() << std::endl;
a.stream() << "            assistant.DecrementDepth();" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        public static string Dump(" << sn << " value)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            var assistant = new AssistantDumper();" << std::endl;
a.stream() << "            Dump(assistant, value);" << std::endl;
a.stream() << "            return assistant.ToString();" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << "    }" << std::endl;
        }
    } // sbf
    return a.make_artefact();
}
}
