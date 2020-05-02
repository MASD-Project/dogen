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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.m2t/types/formatters/sequence_formatter.hpp"
#include "dogen.m2t.cpp/types/traits.hpp"
#include "dogen.physical/types/helpers/meta_name_factory.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.logical/types/entities/visual_studio/project.hpp"
#include "dogen.m2t.cpp/types/transforms/visual_studio/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/types/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/assistant.hpp"
#include "dogen.m2t.cpp/types/transforms/formatting_error.hpp"
#include "dogen.m2t.cpp/types/transforms/visual_studio/project_transform.hpp"

namespace dogen::m2t::cpp::transforms::visual_studio {

physical::entities::archetype project_transform::static_archetype() const {
    static physical::entities::archetype r([]() {
        physical::entities::archetype r;
        using pmnf = physical::helpers::meta_name_factory;
        r.meta_name(pmnf::make(cpp::traits::backend_sn(),
            traits::facet_sn(), traits::project_archetype_sn()));
        using lmnf = logical::helpers::meta_name_factory;
        r.logical_meta_element_id(lmnf::make_visual_studio_project_name().qualified().dot());
        return r;
    }());
    return r;
}

physical::entities::archetype project_transform::archetype() const {
    return static_archetype();
}

inclusion_support_types
project_transform::inclusion_support_type() const {
    return inclusion_support_types::not_supported;
}

boost::filesystem::path project_transform::inclusion_path(
    const formattables::locator& /*l*/, const logical::entities::name& n) const {

    using namespace dogen::utility::log;
    using namespace dogen::m2t::cpp::transforms;
    static logger lg(logger_factory(archetype().meta_name().qualified()));

    static const std::string not_supported("Inclusion path is not supported: ");

    BOOST_LOG_SEV(lg, error) << not_supported << n.qualified().dot();
    BOOST_THROW_EXCEPTION(formatting_error(not_supported + n.qualified().dot()));
}

boost::filesystem::path project_transform::
full_path(const formattables::locator& l, const logical::entities::name& n) const {
    auto temp(n);
    temp.simple(boost::algorithm::join(n.location().model_modules(), ".") + ".vcxproj");
    return l.make_full_path_for_project(temp, archetype().meta_name().qualified());
}

std::list<std::string> project_transform::inclusion_dependencies(
    const formattables::dependencies_builder_factory& /*f*/,
    const logical::entities::element& /*e*/) const {
    static std::list<std::string> r;
    return r;
}

void project_transform::apply(const context& ctx, const logical::entities::element& e,
    physical::entities::artefact& a) const {
    assistant ast(ctx, e, archetype().meta_name(), false/*requires_header_guard*/, a);
    using logical::entities::visual_studio::project;
    const auto& proj(ast.as<project>(e));

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
ast.stream() << "  <Import Project=\"$(MSBuildBinPath)\\Microsoft.Cpp.targets\" />" << std::endl;
ast.stream() << "</Project>" << std::endl;
    ast.update_artefact();
}
}
