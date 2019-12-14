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
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.engine/types/transforms/scoped_context_manager.hpp"
#include "dogen.engine/types/transforms/code_generation_chain.hpp"
#include "dogen.engine/types/generator.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("engine.generator"));

const std::string generation_activity("generation");

}

namespace dogen::engine {

void generator::generate(const configuration& cfg,
    const boost::filesystem::path& target,
    const boost::filesystem::path& output_directory) const {

    BOOST_LOG_SEV(lg, debug) << "Started generation.";

    {
        using namespace transforms;
        scoped_context_manager scm(cfg, generation_activity, output_directory);
        code_generation_chain::apply(scm.context(), target);
    }

    BOOST_LOG_SEV(lg, debug) << "Finished generation.";
}

}
