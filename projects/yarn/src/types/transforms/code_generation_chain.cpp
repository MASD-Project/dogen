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
#include "dogen/yarn/types/transforms/options_validator.hpp"
#include "dogen/yarn/types/transforms/context_factory.hpp"
#include "dogen/yarn/types/transforms/model_to_text_chain.hpp"
#include "dogen/yarn/types/transforms/text_model_generation_chain.hpp"
#include "dogen/yarn/types/helpers/housekeeper.hpp"
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

void code_generation_chain::perform_housekeeping(const transforms::options& o,
    const meta_model::text_model& tm) {

    std::set<boost::filesystem::path> expected_files;
    for (const auto a : tm.artefacts()) {
        expected_files.insert(a.path().generic_string());
        for (const auto& d : a.dependencies())
            expected_files.insert(d.generic_string());
    }

    const auto& ip(o.ignore_patterns());
    const std::list<std::string> ignore_patterns(ip.begin(), ip.end());
    const auto& dirs(tm.managed_directories());
    helpers::housekeeper hk(ignore_patterns, dirs, expected_files);
    hk.tidy_up();
}

void code_generation_chain::transform(const transforms::options& o) {
    BOOST_LOG_SEV(lg, info) << "Starting code generation.";

    /*
     * Before anything else, lets make sure the transform options make
     * sense. No point in proceeding otherwise.
     */
    transforms::options_validator v;
    v.validate(o);

    /*
     * Obtain the kernel registrar and ensure it has been setup.
     */
    const auto& rg(model_to_text_chain::registrar());
    rg.validate();

    /*
     * Next we obtain the transformation context, used by (most)
     * transformations.
     */
    const auto ctx(context_factory::make(rg, o));

    {
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
        if (o.delete_extra_files())
            perform_housekeeping(o, tm);
    }

    ctx.prober().end_probing();

    BOOST_LOG_SEV(lg, info) << "Finished code generation.";
}

} } }
