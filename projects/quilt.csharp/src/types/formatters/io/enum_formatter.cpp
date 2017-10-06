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
#include "dogen/quilt.csharp/types/formatters/io/enum_formatter.hpp"
#include "dogen/quilt.csharp/types/formatters/assistant.hpp"
#include "dogen/quilt.csharp/types/formatters/io/traits.hpp"
#include "dogen/quilt.csharp/types/traits.hpp"
#include "dogen/formatters/types/sequence_formatter.hpp"
#include "dogen/yarn/types/helpers/meta_name_factory.hpp"
#include "dogen/yarn/types/meta_model/enumeration.hpp"

namespace dogen {
namespace quilt {
namespace csharp {
namespace formatters {
namespace io {

std::string enum_formatter::static_artefact() {
    return traits::enum_archetype();
}

std::string enum_formatter::formatter_name() const {
    static auto r(archetype_location().archetype());
    return r;
}

annotations::archetype_location enum_formatter::archetype_location() const {
    static annotations::archetype_location
        r(csharp::traits::family(), csharp::traits::backend(),
          traits::facet(),
          enum_formatter::static_artefact());
    return r;
}

const yarn::meta_model::name& enum_formatter::meta_name() const {
    using yarn::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_enumeration_name());
    return r;
}

boost::filesystem::path enum_formatter::full_path(
    const formattables::locator& l, const yarn::meta_model::name& n) const {
    return l.make_full_path(n, static_artefact());
}

std::list<std::string> enum_formatter::
inclusion_dependencies(const yarn::meta_model::element& /*e*/) const {
    std::list<std::string> r;
    return r;
}

dogen::formatters::artefact enum_formatter::
format(const context& ctx, const yarn::meta_model::element& e) const {
    const auto id(e.name().id());
    assistant a(ctx, archetype_location(), id);
    const auto& ye(a.as<yarn::meta_model::enumeration>(static_artefact(), e));
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
} } } } }
