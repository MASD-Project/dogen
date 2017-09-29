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
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/filesystem/path.hpp"
#include "dogen/utility/filesystem/file.hpp"
#include "dogen/formatters/types/filesystem_writer.hpp"
#include "dogen/yarn/types/transforms/text_model_generation_chain.hpp"
#include "dogen/yarn/types/helpers/file_linter.hpp"
#include "dogen/yarn/types/helpers/transform_metrics.hpp"
#include "dogen/yarn/types/helpers/scoped_transform_probing.hpp"
#include "dogen/yarn/types/transforms/code_generation_chain.hpp"

namespace {

const std::string transform_id("dogen.yarn.code_generation_chain");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

}

namespace dogen {
namespace yarn {
namespace transforms {

void code_generation_chain::write_files(const transforms::options& o,
    const meta_model::text_model& tm) {
    using dogen::formatters::filesystem_writer;
    auto w(std::make_shared<filesystem_writer>(o.force_write()));

    if (tm.artefacts().empty()) {
        BOOST_LOG_SEV(lg, warn) << "No files were generated, so no output.";
        return;
    }

    w->write(tm.artefacts());
}

void code_generation_chain::handle_lint(const transforms::options& o,
    const meta_model::text_model& tm) {
    if (!o.delete_extra_files())
        return;

    const auto lint(helpers::file_linter::lint(o.ignore_patterns(), tm));
    utility::filesystem::remove(lint);
}

void code_generation_chain::transform(const context& ctx) {
    BOOST_LOG_SEV(lg, info) << "Starting code generation.";

    const auto& o(ctx.transform_options());
    const auto model_name(o.target().filename().string());
    helpers::scoped_chain_probing stp(lg, "code generation chain",
        transform_id, model_name, ctx.prober());

    /*
     * Obtain the text models.
     */
    const auto tm(text_model_generation_chain::transform(ctx));

    /*
     * Write the files.
     */
    write_files(o, tm);

    /*
     * Perform any housekeeping if need be.
     */
    handle_lint(o, tm);

    BOOST_LOG_SEV(lg, info) << "Finished code generation.";
}

} } }
