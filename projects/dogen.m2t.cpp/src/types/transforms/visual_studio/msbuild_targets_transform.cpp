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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.logical/types/helpers/meta_name_factory.hpp"
#include "dogen.logical/types/entities/visual_studio/msbuild_targets.hpp"
#include "dogen.m2t/types/formatters/sequence_formatter.hpp"
#include "dogen.m2t.cpp/types/transforms/assistant.hpp"
#include "dogen.m2t.cpp/types/transforms/visual_studio/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/traits.hpp"
#include "dogen.m2t.cpp/types/traits.hpp"
#include "dogen.m2t.cpp/types/transforms/assistant.hpp"
#include "dogen.m2t.cpp/types/transforms/formatting_error.hpp"
#include "dogen.m2t.cpp/types/transforms/visual_studio/msbuild_targets_transform.hpp"

namespace dogen::m2t::cpp::transforms::visual_studio {

std::string msbuild_targets_transform::static_id() {
    return traits::msbuild_targets_archetype();
}

std::string msbuild_targets_transform::id() const {
    static auto r(archetype_location().archetype());
    return r;
}

physical::entities::location
msbuild_targets_transform::archetype_location() const {
    static physical::entities::location
        r(cpp::traits::backend(), traits::facet(),
          msbuild_targets_transform::static_id());
    return r;
}

const logical::entities::name& msbuild_targets_transform::meta_name() const {
    using logical::helpers::meta_name_factory;
    static auto r(meta_name_factory::make_visual_studio_msbuild_targets_name());
    return r;
}

std::string msbuild_targets_transform::family() const {
    return cpp::traits::msbuild_family();
}

inclusion_support_types
msbuild_targets_transform::inclusion_support_type() const {
    return inclusion_support_types::not_supported;
}

boost::filesystem::path msbuild_targets_transform::inclusion_path(
    const formattables::locator& /*l*/, const logical::entities::name& n) const {

    using namespace dogen::utility::log;
    using namespace dogen::m2t::cpp::transforms;
    static logger lg(logger_factory(static_id()));

    static const std::string not_supported("Inclusion path is not supported: ");

    BOOST_LOG_SEV(lg, error) << not_supported << n.qualified().dot();
    BOOST_THROW_EXCEPTION(formatting_error(not_supported + n.qualified().dot()));
}

boost::filesystem::path msbuild_targets_transform::full_path(
    const formattables::locator& l, const logical::entities::name& n) const {
    return l.make_full_path_for_msbuild_targets(n, static_id());
}

std::list<std::string> msbuild_targets_transform::inclusion_dependencies(
    const formattables::dependencies_builder_factory& /*f*/,
    const logical::entities::element& /*e*/) const {
    static std::list<std::string> r;
    return r;
}

physical::entities::artefact msbuild_targets_transform::
format(const context& ctx, const logical::entities::element& e) const {
    assistant a(ctx, e, archetype_location(), false/*requires_header_guard*/);
    using logical::entities::visual_studio::msbuild_targets;
    const auto& c(a.as<msbuild_targets>(e));

    {
        const auto ts(logical::entities::technical_space::xml);
        a.make_decoration_preamble(e, ts);
        const auto model_name(a.get_identifiable_model_name(c.name()));
        const auto product_name(a.get_product_name(c.name()));
        const auto targets(c.odb_targets());
a.stream() << "<Project DefaultTargets=\"Build\" xmlns=\"http://schemas.microsoft.com/developer/msbuild/2003\" ToolsVersion=\"4.0\">" << std::endl;
a.stream() << std::endl;
a.stream() << "    <!--[" << std::endl;
a.stream() << "        .NAME: odb.targets" << std::endl;
a.stream() << std::endl;
a.stream() << "        .SYNOPSIS:" << std::endl;
a.stream() << "            Generates all of the ODB files for this project." << std::endl;
a.stream() << std::endl;
a.stream() << "        .DESCRIPTION:" << std::endl;
a.stream() << "            Calls the ODB compiler against each of the files in this Dogen model that require" << std::endl;
a.stream() << "            ODB compilation. Also moves the generated files to their correct location." << std::endl;
a.stream() << std::endl;
a.stream() << "        .INPUTS:" << std::endl;
a.stream() << std::endl;
a.stream() << "        .OUTPUTS:" << std::endl;
a.stream() << "    ]-->" << std::endl;
a.stream() << "    <Target Name=\"" << targets.main_target_name() << "\"" << std::endl;
            m2t::formatters::sequence_formatter sf(targets.targets().size());
            sf.prefix_configuration().first("          DependsOnTargets=\"")
                                     .not_first("                            ");
            sf.postfix_configuration().last("\">");
            sf.element_separator(";");
            for (const auto& target : targets.targets()) {
a.stream() << sf.prefix() << target.name() << sf.postfix() << std::endl;
                sf.next();
            }
a.stream() << "        <Message Importance=\"high\" Text=\"ODB " << model_name << " \"/>" << std::endl;
a.stream() << "    </Target>" << std::endl;
a.stream() << std::endl;
            for (const auto& target : targets.targets()) {
a.stream() << "    <Target Name=\"" << target.name() << "\">" << std::endl;
a.stream() << "        <Message Importance=\"high\" Text=\"" << target.comment() << "\"/>" << std::endl;
a.stream() << "        <Exec WorkingDirectory=\"$(OutputDirectory)\" Command=\"&quot;$(OdbPath)&quot; -D_SECURE_SCL=0 $(OdbIncludeDirectories) --options-file $(MSBuildThisFileDirectory)" << targets.common_odb_options() << " --options-file $(MSBuildThisFileDirectory)" << target.object_odb_options() << " --output-dir $(MSBuildThisFileDirectory)" << target.output_directory() << " $(MSBuildThisFileDirectory)" << target.types_file() << "\" />" << std::endl;
                for (const auto& pair : target.move_parameters()) {
a.stream() << "        <Move" << std::endl;
a.stream() << "            SourceFiles=\"$(MSBuildThisFileDirectory)" << pair.first << "\"" << std::endl;
a.stream() << "            DestinationFolder=\"$(MSBuildThisFileDirectory)" << pair.second << "\" />" << std::endl;
                }
a.stream() << "    </Target>" << std::endl;
            }
a.stream() << "</Project>" << std::endl;
    } // sbf
    return a.make_artefact();
}
}
