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
#include "dogen/io/configuration_io.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/filesystem/path.hpp"
#include "dogen.utility/types/filesystem/file.hpp"
#include "dogen.tracing/types/scoped_tracer.hpp"
#include "dogen.codec/types/transforms/context_bootstrapping_chain.hpp"

namespace {

const std::string transform_id(
    "codec.transforms.context_bootstrapping_chain");

using namespace dogen::utility::log;
auto lg(logger_factory(transform_id));

const std::string input_id("configuration");

}

namespace dogen::codec::transforms {

boost::shared_ptr<tracing::tracer>
context_bootstrapping_chain::create_and_setup_tracer(
    const configuration& cfg, const std::string& activity) {
    /*
     * Setup the tracer. Note that we do it regardless of whether
     * tracing is enabled or not - its the tracer job to handle
     * that. Also, we start tracing here so that all transforms can
     * make use of it.
     */
    using namespace transforms;
    const auto r(boost::make_shared<tracing::tracer>(cfg, activity));
    r->start_run(input_id, cfg);
    return r;
}

codec::transforms::context
context_bootstrapping_chain::bootstrap_codec_context(
    const configuration& cfg, const std::string& activity) {

    /*
     * Obtain the tracer. Note that we do it regardless of whether tracing is
     * enabled or not - its the tracer job to handle that.
     */
    codec::transforms::context r;
    const auto t(create_and_setup_tracer(cfg, activity));
    tracing::scoped_chain_tracer stp(lg, "full bootstrapping", transform_id,
        "bootstrapping", *t);
    r.tracer(t);

    /*
     * Obtain the share directory.
     */
    const auto lib_dir(utility::filesystem::library_directory());
    const auto lib_dirs(std::vector<boost::filesystem::path>{ lib_dir });
    r.data_directories(lib_dirs);

    stp.end_chain(r);
    return r;
}

}
