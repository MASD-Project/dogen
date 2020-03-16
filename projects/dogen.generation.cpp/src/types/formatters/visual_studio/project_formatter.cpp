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
#include "dogen.generation/types/formatters/sequence_formatter.hpp"
#include "dogen.generation.cpp/types/traits.hpp"
#include "dogen.assets/types/helpers/meta_name_factory.hpp"
#include "dogen.assets/types/meta_model/visual_studio/project.hpp"
#include "dogen.generation.cpp/types/formatters/visual_studio/traits.hpp"
#include "dogen.generation.cpp/types/formatters/types/traits.hpp"
#include "dogen.generation.cpp/types/formatters/assistant.hpp"
#include "dogen.generation.cpp/types/formatters/formatting_error.hpp"
#include "dogen.generation.cpp/types/formatters/visual_studio/project_formatter.hpp"

namespace dogen::generation::cpp::formatters::visual_studio {

std::string project_formatter::static_id() {
    return traits::project_archetype();
}

std::string project_formatter::id() const {
    static auto r(archetype_location().archetype());
    return r;
}

physical::location
project_formatter::archetype_location() const {
    static physical::location
        r(cpp::traits::kernel(), cpp::traits::backend(),
          traits::facet(),
          project_formatter::static_id());
    return r;
}

const assets::meta_model::name&
project_formatter::meta_name() const {
    using assets::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_visual_studio_project_name());
    return r;
}

std::string project_formatter::family() const {
    return cpp::traits::visual_studio_project_family();
}

inclusion_support_types
project_formatter::inclusion_support_type() const {
    return inclusion_support_types::not_supported;
}

boost::filesystem::path project_formatter::inclusion_path(
    const formattables::locator& /*l*/, const assets::meta_model::name& n) const {

    using namespace dogen::utility::log;
    using namespace dogen::generation::cpp::formatters;
    static logger lg(logger_factory(static_id()));

    static const std::string not_supported("Inclusion path is not supported: ");

    BOOST_LOG_SEV(lg, error) << not_supported << n.qualified().dot();
    BOOST_THROW_EXCEPTION(formatting_error(not_supported + n.qualified().dot()));
}

boost::filesystem::path project_formatter::
full_path(const formattables::locator& l, const assets::meta_model::name& n) const {
    auto temp(n);
    temp.simple(boost::algorithm::join(n.location().model_modules(), ".") + ".vcxproj");
    return l.make_full_path_for_project(temp, static_id());
}

std::list<std::string> project_formatter::inclusion_dependencies(
    const formattables::dependencies_builder_factory& /*f*/,
    const assets::meta_model::element& /*e*/) const {
    static std::list<std::string> r;
    return r;
}

extraction::meta_model::artefact project_formatter::
format(const context& ctx, const assets::meta_model::element& e) const {
    assistant a(ctx, e, archetype_location(), false/*requires_header_guard*/);
    using assets::meta_model::visual_studio::project;
    const auto& proj(a.as<project>(e));

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
a.stream() << "  <Import Project=\"$(MSBuildBinPath)\\Microsoft.Cpp.targets\" />" << std::endl;
a.stream() << "</Project>" << std::endl;
    return a.make_artefact();
}
}
