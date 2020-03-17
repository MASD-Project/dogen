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
#include <iostream>
#include <sstream>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/io/diffing_destination_io.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/filesystem/file.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.physical/io/entities/model_io.hpp"
#include "dogen.physical/types/transforms/transform_exception.hpp"
#include "dogen.physical/types/transforms/generate_patch_transform.hpp"

namespace {

const std::string transform_id(
    "physical.transforms.generate_patch_transform");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string unexpected_destination(
    "Destination is invalid or unsupported: ");
const std::string created_dir_message("Created directory: ");
const std::string using_dir_message("Using directory: ");

}

namespace dogen::physical::transforms {

void generate_patch_transform::
apply(const context& ctx, const entities::model& m) {
    tracing::scoped_transform_tracer stp(lg,
        "generate patch transform", transform_id, m.name(),
        *ctx.tracer(), m);

    BOOST_LOG_SEV(lg, debug) << "Creating patch for model: " << m.name();

    /*
     * If the user did not request diffing, there is nothing to do.
     */
    if (!ctx.diffing_configuration()) {
        BOOST_LOG_SEV(lg, debug) << "Diffing not enabled.";
        return;
    }

    std::ostringstream ss;
    for (auto& a : m.artefacts()) {
        BOOST_LOG_SEV(lg, trace) << "Processing arefact: "
                                 << a.paths().absolute().filename();

        if (a.unified_diff().empty()) {
            BOOST_LOG_SEV(lg, trace) << "Arefact has no diff.";
            continue;
        }

        BOOST_LOG_SEV(lg, debug) << "Adding diff to patch. Size: "
                                 << a.unified_diff().size();

        ss << a.unified_diff();
    }

    const auto c(ss.str());
    const auto& cfg(*ctx.diffing_configuration());
    const auto dest(cfg.destination());
    switch(dest) {
    case diffing_destination::file: {
        const auto od(cfg.output_directory());
        BOOST_LOG_SEV(lg, debug) << "Outputting diffs to: " << od;

        using boost::filesystem::create_directories;
        create_directories(cfg.output_directory());

        boost::filesystem::path p(cfg.output_directory());
        p /= m.name() + ".patch";

        BOOST_LOG_SEV(lg, debug) << "Writing patch file: " << p.generic()
                                 << ". Size: " << c.size();
        using dogen::utility::filesystem::write_file_content;
        write_file_content(p, c);
        break;
    }
    case diffing_destination::console:
        BOOST_LOG_SEV(lg, debug) << "Outputting patch to console.";
        std::cout << c;
        break;
    default: {
        const auto s(boost::lexical_cast<std::string>(dest));
        BOOST_LOG_SEV(lg, error) << unexpected_destination << s;
        BOOST_THROW_EXCEPTION(transform_exception(unexpected_destination + s));
    } }
    BOOST_LOG_SEV(lg, debug) << "Finished generating patch";
}

}
