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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.identification/types/helpers/physical_meta_name_factory.hpp"
#include "dogen.identification/types/helpers/logical_meta_name_factory.hpp"
#include "dogen.logical/types/entities/visual_studio/msbuild_targets.hpp"
#include "dogen.utility/types/formatters/sequence_formatter.hpp"
#include "dogen.text/types/formatters/assistant.hpp"
#include "dogen.text/types/formatters/assistant.hpp"
#include "dogen.text/types/transforms/transformation_error.hpp"
#include "dogen.text/types/transforms/cpp/visual_studio/msbuild_targets_transform.hpp"
#include "dogen.text/types/transforms/cpp/visual_studio/msbuild_targets_factory.hpp"

namespace dogen::text::transforms::cpp::visual_studio {
namespace {

const std::string transform_id("text.transforms.visual_studio.msbuild_targets_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

const physical::entities::archetype& msbuild_targets_transform::static_archetype() {
    static auto r(msbuild_targets_factory::make());
    return r;
}

const physical::entities::archetype& msbuild_targets_transform::archetype() const {
    return static_archetype();
}

void msbuild_targets_transform::
apply(const text::transforms::context& ctx, const text::entities::model& lps,
    const logical::entities::element& e, physical::entities::artefact& a) const {
    tracing::scoped_transform_tracer stp(lg, "msbuild targets",
        transform_id, e.name().qualified().dot(), *ctx.tracer(), e);

    text::formatters::assistant ast(lps, e, a, false/*requires_header_guard*/);
    using logical::entities::visual_studio::msbuild_targets;
    const auto& c(ast.as<msbuild_targets>(e));

    {
        const auto ts(identification::entities::technical_space::xml);
        ast.make_decoration_preamble(e, ts);
        const auto model_name(ast.get_identifiable_model_name(c.name()));
        const auto product_name(ast.get_product_name(c.name()));
        const auto targets(c.odb_targets());
ast.stream() << "<Project DefaultTargets=\"Build\" xmlns=\"http://schemas.microsoft.com/developer/msbuild/2003\" ToolsVersion=\"4.0\">" << std::endl;
ast.stream() << std::endl;
ast.stream() << "    <!--[" << std::endl;
ast.stream() << "        .NAME: odb.targets" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        .SYNOPSIS:" << std::endl;
ast.stream() << "            Generates all of the ODB files for this project." << std::endl;
ast.stream() << std::endl;
ast.stream() << "        .DESCRIPTION:" << std::endl;
ast.stream() << "            Calls the ODB compiler against each of the files in this Dogen model that require" << std::endl;
ast.stream() << "            ODB compilation. Also moves the generated files to their correct location." << std::endl;
ast.stream() << std::endl;
ast.stream() << "        .INPUTS:" << std::endl;
ast.stream() << std::endl;
ast.stream() << "        .OUTPUTS:" << std::endl;
ast.stream() << "    ]-->" << std::endl;
ast.stream() << "    <Target Name=\"" << targets.main_target_name() << "\"" << std::endl;
            utility::formatters::sequence_formatter sf(targets.targets().size());
            sf.prefix_configuration().first("          DependsOnTargets=\"")
                                     .not_first("                            ");
            sf.postfix_configuration().last("\">");
            sf.element_separator(";");
            for (const auto& target : targets.targets()) {
ast.stream() << sf.prefix() << target.name() << sf.postfix() << std::endl;
                sf.next();
            }
ast.stream() << "        <Message Importance=\"high\" Text=\"ODB " << model_name << " \"/>" << std::endl;
ast.stream() << "    </Target>" << std::endl;
ast.stream() << std::endl;
            for (const auto& target : targets.targets()) {
ast.stream() << "    <Target Name=\"" << target.name() << "\">" << std::endl;
ast.stream() << "        <Message Importance=\"high\" Text=\"" << target.comment() << "\"/>" << std::endl;
ast.stream() << "        <Exec WorkingDirectory=\"$(OutputDirectory)\" Command=\"&quot;$(OdbPath)&quot; -D_SECURE_SCL=0 $(OdbIncludeDirectories) --options-file $(MSBuildThisFileDirectory)" << targets.common_odb_options() << " --options-file $(MSBuildThisFileDirectory)" << target.object_odb_options() << " --output-dir $(MSBuildThisFileDirectory)" << target.output_directory() << " $(MSBuildThisFileDirectory)" << target.types_file() << "\" />" << std::endl;
                for (const auto& pair : target.move_parameters()) {
ast.stream() << "        <Move" << std::endl;
ast.stream() << "            SourceFiles=\"$(MSBuildThisFileDirectory)" << pair.first << "\"" << std::endl;
ast.stream() << "            DestinationFolder=\"$(MSBuildThisFileDirectory)" << pair.second << "\" />" << std::endl;
                }
ast.stream() << "    </Target>" << std::endl;
            }
ast.stream() << "</Project>" << std::endl;
    } // sbf
    ast.update_artefact();
    stp.end_transform(a);
}
}
