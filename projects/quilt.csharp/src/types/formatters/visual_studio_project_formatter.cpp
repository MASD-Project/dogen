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
#include "dogen/quilt.csharp/types/formatters/visual_studio_project_formatter.hpp"
#include "dogen/quilt.csharp/types/fabric/visual_studio_project.hpp"
#include "dogen/quilt.csharp/types/formatters/assistant.hpp"
#include "dogen/quilt.csharp/types/formatters/types/traits.hpp"
#include "dogen/quilt.csharp/types/formatters/traits.hpp"
#include "dogen/quilt.csharp/types/traits.hpp"
#include "dogen/formatters/types/sequence_formatter.hpp"
#include <boost/make_shared.hpp>
#include <typeinfo>

namespace dogen {
namespace quilt {
namespace csharp {
namespace formatters {

std::string visual_studio_project_formatter::static_artefact() {
    return traits::visual_studio_project_archetype();
}

std::string visual_studio_project_formatter::formatter_name() const {
    static auto r(archetype_location().archetype());
    return r;
}

annotations::archetype_location visual_studio_project_formatter::archetype_location() const {
    static annotations::archetype_location
        r(csharp::traits::family(), csharp::traits::kernel(),
          traits::visual_studio_facet(),
          visual_studio_project_formatter::static_artefact());
    return r;
}

std::type_index visual_studio_project_formatter::element_type_index() const {
    static auto r(std::type_index(typeid(fabric::visual_studio_project)));
    return r;
}

boost::filesystem::path visual_studio_project_formatter::
full_path(const formattables::locator& l, const yarn::name& n) const {
    return l.make_full_path_for_project(n, static_artefact());
}

std::list<std::string> visual_studio_project_formatter::
inclusion_dependencies(const yarn::element& /*e*/) const {
    std::list<std::string> r;
    return r;
}

dogen::formatters::artefact
visual_studio_project_formatter::format(const context& ctx, const yarn::element& e) const {
    const auto id(e.name().id());
    assistant a(ctx, archetype_location(), id);
a.stream() << "<?xml version=\"1.0\" encoding=\"utf-8\"?>" << std::endl;
a.stream() << "<Project DefaultTargets=\"Build\" ToolsVersion=\"4.0\" xmlns=\"http://schemas.microsoft.com/developer/msbuild/2003\">" << std::endl;
a.stream() << "  <PropertyGroup>" << std::endl;
a.stream() << "    <Configuration Condition=\" '$(Configuration)' == '' \">Debug</Configuration>" << std::endl;
a.stream() << "    <Platform Condition=\" '$(Platform)' == '' \">AnyCPU</Platform>" << std::endl;
a.stream() << "    <ProjectGuid>{9E645ACD-C04A-4734-AB23-C3FCC0F7981B}</ProjectGuid>" << std::endl;
a.stream() << "    <OutputType>Library</OutputType>" << std::endl;
a.stream() << "    <RootNamespace>CSharpModel</RootNamespace>" << std::endl;
a.stream() << "    <AssemblyName>CSharpModel</AssemblyName>" << std::endl;
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
a.stream() << "  <ItemGroup>" << std::endl;
a.stream() << "    <Compile Include=\"AllPrimitives.cs\" />" << std::endl;
a.stream() << "  </ItemGroup>" << std::endl;
a.stream() << "  <Import Project=\"$(MSBuildBinPath)\\Microsoft.CSharp.targets\" />" << std::endl;
a.stream() << "</Project>" << std::endl;
    return a.make_artefact();
}
} } } }
