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
#include <boost/algorithm/string/join.hpp>
#include "dogen.utility/types/formatters/sequence_formatter.hpp"
#include "dogen.text.csharp/types/traits.hpp"
#include "dogen.physical/types/helpers/meta_name_factory.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.logical/types/entities/visual_studio/solution.hpp"
#include "dogen.text.csharp/types/transforms/visual_studio/traits.hpp"
#include "dogen.text.csharp/types/transforms/types/traits.hpp"
#include "dogen.text.csharp/types/transforms/assistant.hpp"
#include "dogen.text.csharp/types/transforms/visual_studio/solution_transform.hpp"

namespace dogen::text::csharp::transforms::visual_studio {

physical::entities::archetype solution_transform::static_archetype() const {
    static physical::entities::archetype r([]() {
        physical::entities::archetype r;
        using pmnf = physical::helpers::meta_name_factory;
        r.meta_name(pmnf::make(csharp::traits::backend_sn(),
            traits::facet_sn(), traits::solution_archetype_sn()));
        using lmnf = logical::helpers::meta_name_factory;
        r.logical_meta_element_id(lmnf::make_visual_studio_solution_name().qualified().dot());
        return r;
    }());
    return r;
}

physical::entities::archetype solution_transform::archetype() const {
    return static_archetype();
}

boost::filesystem::path solution_transform::
full_path(const formattables::locator& l, const logical::entities::name& n) const {
    auto temp(n);
    temp.simple(boost::algorithm::join(n.location().model_modules(), ".") + ".sln");
    return l.make_full_path_for_project(temp, archetype().meta_name().qualified());
}

std::list<std::string> solution_transform::
inclusion_dependencies(const logical::entities::element& /*e*/) const {
    std::list<std::string> r;
    return r;
}

void solution_transform::apply(const context& ctx, const logical::entities::element& e,
    physical::entities::artefact& a) const {
    assistant ast(ctx, e, archetype().meta_name(), a);
    using logical::entities::visual_studio::solution;
    const auto& sln(ast.as<solution>(archetype().meta_name().qualified(), e));
ast.stream() << "Microsoft Visual Studio Solution File, Format Version 12.00" << std::endl;
ast.stream() << "# Visual Studio 2012" << std::endl;
    for (const auto& ppb : sln.project_persistence_blocks()) {
ast.stream() << "Project(\"{" << ppb.type_guid() << "}\") = \"" << ppb.name() << "\", \"" << ppb.name() << ".csproj\", \"{" << ppb.guid() << "}\"" << std::endl;
ast.stream() << "EndProject" << std::endl;
    }
ast.stream() << "Global" << std::endl;
ast.stream() << "    GlobalSection(SolutionConfigurationPlatforms) = preSolution" << std::endl;
ast.stream() << "        Debug|Any CPU = Debug|Any CPU" << std::endl;
ast.stream() << "        Release|Any CPU = Release|Any CPU" << std::endl;
ast.stream() << "    EndGlobalSection" << std::endl;
ast.stream() << "    GlobalSection(ProjectConfigurationPlatforms) = postSolution" << std::endl;
    for (const auto& ppb : sln.project_persistence_blocks()) {
ast.stream() << "        {" << ppb.guid() << "}.Debug|Any CPU.ActiveCfg = Debug|Any CPU" << std::endl;
ast.stream() << "        {" << ppb.guid() << "}.Debug|Any CPU.Build.0 = Debug|Any CPU" << std::endl;
ast.stream() << "        {" << ppb.guid() << "}.Release|Any CPU.ActiveCfg = Release|Any CPU" << std::endl;
ast.stream() << "        {" << ppb.guid() << "}.Release|Any CPU.Build.0 = Release|Any CPU" << std::endl;
    }
ast.stream() << "    EndGlobalSection" << std::endl;
ast.stream() << "    GlobalSection(MonoDevelopProperties) = preSolution" << std::endl;
ast.stream() << "        StartupItem = CSharpModel.csproj" << std::endl;
ast.stream() << "    EndGlobalSection" << std::endl;
ast.stream() << "EndGlobal" << std::endl;
    ast.update_artefact();
}
}
