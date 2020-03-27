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
#include "dogen.m2t/types/formatters/sequence_formatter.hpp"
#include "dogen.m2t.csharp/types/traits.hpp"
#include "dogen.physical/types/helpers/name_factory.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.logical/types/entities/visual_studio/project.hpp"
#include "dogen.m2t.csharp/types/transforms/visual_studio/traits.hpp"
#include "dogen.m2t.csharp/types/transforms/assistant.hpp"
#include "dogen.m2t.csharp/types/transforms/visual_studio/project_transform.hpp"

namespace dogen::m2t::csharp::transforms::visual_studio {

std::string project_transform::static_id() {
    return traits::project_archetype();
}

std::string project_transform::id() const {
    static auto r(physical_name().location().archetype());
    return r;
}

physical::entities::name
project_transform::physical_name() const {
    using physical::helpers::name_factory;
    static const auto r(name_factory::make(csharp::traits::backend_qn(),
        traits::facet_qn(), project_transform::static_id()));
    return r;
}

const logical::entities::name&
project_transform::meta_name() const {
    using logical::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_visual_studio_project_name());
    return r;
}

boost::filesystem::path project_transform::
full_path(const formattables::locator& l, const logical::entities::name& n) const {
    auto temp(n);
    temp.simple(boost::algorithm::join(n.location().model_modules(), ".") + ".csproj");
    return l.make_full_path_for_project(temp, static_id());
}

std::list<std::string> project_transform::
inclusion_dependencies(const logical::entities::element& /*e*/) const {
    std::list<std::string> r;
    return r;
}

physical::entities::artefact project_transform::
apply(const context& ctx, const logical::entities::element& e) const {
    assistant a(ctx, e, physical_name().location());
    using logical::entities::visual_studio::project;
    const auto& proj(a.as<project>(static_id(), e));

a.stream() << "<?xml version=\"1.0\" encoding=\"utf-8\"?>" << std::endl;
a.stream() << "<Project DefaultTargets=\"Build\" ToolsVersion=\"4.0\" xmlns=\"http://schemas.microsoft.com/developer/msbuild/2003\">" << std::endl;
a.stream() << "  <PropertyGroup>" << std::endl;
a.stream() << "    <Configuration Condition=\" '$(Configuration)' == '' \">Debug</Configuration>" << std::endl;
a.stream() << "    <Platform Condition=\" '$(Platform)' == '' \">AnyCPU</Platform>" << std::endl;
a.stream() << "    <ProjectGuid>{" << proj.guid() << "}</ProjectGuid>" << std::endl;
a.stream() << "    <OutputType>Library</OutputType>" << std::endl;
a.stream() << "    <RootNamespace>" << proj.project_name() << "</RootNamespace>" << std::endl;
a.stream() << "    <AssemblyName>" << proj.project_name() << "</AssemblyName>" << std::endl;
a.stream() << "  </PropertyGroup>" << std::endl;
a.stream() << "  <PropertyGroup Condition=\" '$(Configuration)|$(Platform)' == 'Debug|AnyCPU' \">" << std::endl;
a.stream() << "    <DebugSymbols>true</DebugSymbols>" << std::endl;
a.stream() << "    <DebugType>full</DebugType>" << std::endl;
a.stream() << "    <Optimize>false</Optimize>" << std::endl;
a.stream() << "    <OutputPath>bin\\Debug</OutputPath>" << std::endl;
a.stream() << "    <DefineConstants>DEBUG;</DefineConstants>" << std::endl;
a.stream() << "    <ErrorReport>prompt</ErrorReport>" << std::endl;
a.stream() << "    <WarningLevel>4</WarningLevel>" << std::endl;
a.stream() << "    <ConsolePause>false</ConsolePause>" << std::endl;
a.stream() << "  </PropertyGroup>" << std::endl;
a.stream() << "  <PropertyGroup Condition=\" '$(Configuration)|$(Platform)' == 'Release|AnyCPU' \">" << std::endl;
a.stream() << "    <DebugType>full</DebugType>" << std::endl;
a.stream() << "    <Optimize>true</Optimize>" << std::endl;
a.stream() << "    <OutputPath>bin\\Release</OutputPath>" << std::endl;
a.stream() << "    <ErrorReport>prompt</ErrorReport>" << std::endl;
a.stream() << "    <WarningLevel>4</WarningLevel>" << std::endl;
a.stream() << "    <ConsolePause>false</ConsolePause>" << std::endl;
a.stream() << "  </PropertyGroup>" << std::endl;
a.stream() << "  <ItemGroup>" << std::endl;
a.stream() << "    <Reference Include=\"System\" />" << std::endl;
a.stream() << "  </ItemGroup>" << std::endl;
        for (const auto& ig : proj.item_groups()) {
a.stream() << "  <ItemGroup>" << std::endl;
            for (const auto& i : ig.items())
a.stream() << "    <" << i.name() << " Include=\"" << i.include() << "\" />" << std::endl;
a.stream() << "  </ItemGroup>" << std::endl;
        }
a.stream() << "  <Import Project=\"$(MSBuildBinPath)\\Microsoft.CSharp.targets\" />" << std::endl;
a.stream() << "</Project>" << std::endl;
    return a.make_artefact();
}
}
