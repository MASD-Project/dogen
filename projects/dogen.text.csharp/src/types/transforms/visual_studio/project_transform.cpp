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
#include <boost/make_shared.hpp>
#include <boost/algorithm/string/join.hpp>
#include "dogen.utility/types/formatters/sequence_formatter.hpp"
#include "dogen.text.csharp/types/traits.hpp"
#include "dogen.identification/types/helpers/physical_meta_name_factory.hpp"
#include "dogen.identification/types/helpers/logical_meta_name_factory.hpp"
#include "dogen.logical/types/entities/visual_studio/project.hpp"
#include "dogen.text.csharp/types/transforms/visual_studio/traits.hpp"
#include "dogen.text.csharp/types/transforms/assistant.hpp"
#include "dogen.text.csharp/types/transforms/visual_studio/project_transform.hpp"
#include "dogen.text.csharp/types/transforms/visual_studio/project_factory.hpp"

namespace dogen::text::csharp::transforms::visual_studio {
namespace {

const std::string transform_id("text.csharp.transforms.visual_studio.project_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

const physical::entities::archetype& project_transform::static_archetype() {
    static auto r(project_factory::make());
    return r;
}

const physical::entities::archetype& project_transform::archetype() const {
    return static_archetype();
}

std::list<std::string> project_transform::
inclusion_dependencies(const logical::entities::element& /*e*/) const {
    std::list<std::string> r;
    return r;
}

void project_transform::apply(const context& ctx, const logical::entities::element& e,
    physical::entities::artefact& a) const {
    tracing::scoped_transform_tracer stp(lg, "project",
        transform_id, e.name().qualified().dot(), *ctx.tracer(), e);

    assistant ast(ctx, e, archetype().meta_name(), a);
    using logical::entities::visual_studio::project;
    const auto& proj(ast.as<project>(archetype().meta_name().id().value(), e));

ast.stream() << "<?xml version=\"1.0\" encoding=\"utf-8\"?>" << std::endl;
ast.stream() << "<Project DefaultTargets=\"Build\" ToolsVersion=\"4.0\" xmlns=\"http://schemas.microsoft.com/developer/msbuild/2003\">" << std::endl;
ast.stream() << "  <PropertyGroup>" << std::endl;
ast.stream() << "    <Configuration Condition=\" '$(Configuration)' == '' \">Debug</Configuration>" << std::endl;
ast.stream() << "    <Platform Condition=\" '$(Platform)' == '' \">AnyCPU</Platform>" << std::endl;
ast.stream() << "    <ProjectGuid>{" << proj.guid() << "}</ProjectGuid>" << std::endl;
ast.stream() << "    <OutputType>Library</OutputType>" << std::endl;
ast.stream() << "    <RootNamespace>" << proj.project_name() << "</RootNamespace>" << std::endl;
ast.stream() << "    <AssemblyName>" << proj.project_name() << "</AssemblyName>" << std::endl;
ast.stream() << "  </PropertyGroup>" << std::endl;
ast.stream() << "  <PropertyGroup Condition=\" '$(Configuration)|$(Platform)' == 'Debug|AnyCPU' \">" << std::endl;
ast.stream() << "    <DebugSymbols>true</DebugSymbols>" << std::endl;
ast.stream() << "    <DebugType>full</DebugType>" << std::endl;
ast.stream() << "    <Optimize>false</Optimize>" << std::endl;
ast.stream() << "    <OutputPath>bin\\Debug</OutputPath>" << std::endl;
ast.stream() << "    <DefineConstants>DEBUG;</DefineConstants>" << std::endl;
ast.stream() << "    <ErrorReport>prompt</ErrorReport>" << std::endl;
ast.stream() << "    <WarningLevel>4</WarningLevel>" << std::endl;
ast.stream() << "    <ConsolePause>false</ConsolePause>" << std::endl;
ast.stream() << "  </PropertyGroup>" << std::endl;
ast.stream() << "  <PropertyGroup Condition=\" '$(Configuration)|$(Platform)' == 'Release|AnyCPU' \">" << std::endl;
ast.stream() << "    <DebugType>full</DebugType>" << std::endl;
ast.stream() << "    <Optimize>true</Optimize>" << std::endl;
ast.stream() << "    <OutputPath>bin\\Release</OutputPath>" << std::endl;
ast.stream() << "    <ErrorReport>prompt</ErrorReport>" << std::endl;
ast.stream() << "    <WarningLevel>4</WarningLevel>" << std::endl;
ast.stream() << "    <ConsolePause>false</ConsolePause>" << std::endl;
ast.stream() << "  </PropertyGroup>" << std::endl;
ast.stream() << "  <ItemGroup>" << std::endl;
ast.stream() << "    <Reference Include=\"System\" />" << std::endl;
ast.stream() << "  </ItemGroup>" << std::endl;
        for (const auto& ig : proj.item_groups()) {
ast.stream() << "  <ItemGroup>" << std::endl;
            for (const auto& i : ig.items())
ast.stream() << "    <" << i.name() << " Include=\"" << i.include() << "\" />" << std::endl;
ast.stream() << "  </ItemGroup>" << std::endl;
        }
ast.stream() << "  <Import Project=\"$(MSBuildBinPath)\\Microsoft.CSharp.targets\" />" << std::endl;
ast.stream() << "</Project>" << std::endl;
    ast.update_artefact();
    stp.end_transform(a);

}
}
