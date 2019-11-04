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
#include <boost/make_shared.hpp>
#include "dogen.generation/types/formatters/sequence_formatter.hpp"
#include "dogen.generation.csharp/types/traits.hpp"
#include "dogen.generation.csharp/types/fabric/meta_name_factory.hpp"
#include "dogen.generation.csharp/types/fabric/visual_studio_solution.hpp"
#include "dogen.generation.csharp/types/formatters/traits.hpp"
#include "dogen.generation.csharp/types/formatters/types/traits.hpp"
#include "dogen.generation.csharp/types/formatters/assistant.hpp"
#include "dogen.generation.csharp/types/formatters/visual_studio_solution_formatter.hpp"

namespace dogen::generation::csharp::formatters {

std::string visual_studio_solution_formatter::static_id() {
    return traits::visual_studio_solution_archetype();
}

std::string visual_studio_solution_formatter::id() const {
    static auto r(archetype_location().archetype());
    return r;
}

archetypes::location
visual_studio_solution_formatter::archetype_location() const {
    static archetypes::location
        r(csharp::traits::kernel(), csharp::traits::backend(),
          traits::visual_studio_facet(),
          visual_studio_solution_formatter::static_id());
    return r;
}

const assets::meta_model::name&
visual_studio_solution_formatter::meta_name() const {
    using fabric::meta_name_factory;
    static auto r(meta_name_factory::make_visual_studio_solution_name());
    return r;
}

std::string visual_studio_solution_formatter::family() const {
    return csharp::traits::visual_studio_solution_family();
}

boost::filesystem::path visual_studio_solution_formatter::
full_path(const formattables::locator& l, const assets::meta_model::name& n) const {
    return l.make_full_path_for_solution(n, static_id());
}

std::list<std::string> visual_studio_solution_formatter::
inclusion_dependencies(const assets::meta_model::element& /*e*/) const {
    std::list<std::string> r;
    return r;
}

extraction::meta_model::artefact visual_studio_solution_formatter::
format(const context& ctx, const assets::meta_model::element& e) const {
    assistant a(ctx, e, archetype_location());
    const auto& vsl(a.as<fabric::visual_studio_solution>(static_id(), e));
a.stream() << "Microsoft Visual Studio Solution File, Format Version 12.00" << std::endl;
a.stream() << "# Visual Studio 2012" << std::endl;
a.stream() << "Project(\"{" << vsl.project_solution_guid() << "}\") = \"" << vsl.project_name() << "\", \"" << vsl.project_name() << ".csproj\", \"{" << vsl.project_guid() << "}\"" << std::endl;
a.stream() << "EndProject" << std::endl;
a.stream() << "Global" << std::endl;
a.stream() << "    GlobalSection(SolutionConfigurationPlatforms) = preSolution" << std::endl;
a.stream() << "        Debug|Any CPU = Debug|Any CPU" << std::endl;
a.stream() << "        Release|Any CPU = Release|Any CPU" << std::endl;
a.stream() << "    EndGlobalSection" << std::endl;
a.stream() << "    GlobalSection(ProjectConfigurationPlatforms) = postSolution" << std::endl;
a.stream() << "        {" << vsl.project_guid() << "}.Debug|Any CPU.ActiveCfg = Debug|Any CPU" << std::endl;
a.stream() << "        {" << vsl.project_guid() << "}.Debug|Any CPU.Build.0 = Debug|Any CPU" << std::endl;
a.stream() << "        {" << vsl.project_guid() << "}.Release|Any CPU.ActiveCfg = Release|Any CPU" << std::endl;
a.stream() << "        {" << vsl.project_guid() << "}.Release|Any CPU.Build.0 = Release|Any CPU" << std::endl;
a.stream() << "    EndGlobalSection" << std::endl;
a.stream() << "    GlobalSection(MonoDevelopProperties) = preSolution" << std::endl;
a.stream() << "        StartupItem = CSharpModel.csproj" << std::endl;
a.stream() << "    EndGlobalSection" << std::endl;
a.stream() << "EndGlobal" << std::endl;
    return a.make_artefact();
}
}
