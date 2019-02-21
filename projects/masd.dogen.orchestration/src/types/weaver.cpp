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
#include <boost/throw_exception.hpp>
#include "masd.dogen.utility/types/log/logger.hpp"
#include "masd.dogen/types/weaving_exception.hpp"
#include "masd.dogen.templating/types/wale/workflow.hpp"
#include "masd.dogen.templating/types/stitch/workflow.hpp"
#include "masd.dogen.orchestration/types/weaver.hpp"

namespace {

using namespace masd::dogen::utility::log;
auto lg(logger_factory("orchestration.generator"));

const std::string stitch_ext(".stitch");
const std::string unsupported_extension("Extension is unsupported: ");

}

namespace masd::dogen::orchestration {

void weaver::weave(const configuration& /*cfg*/,
    const boost::filesystem::path& target,
    const boost::filesystem::path& /*tracing_output_directory*/) const {
    BOOST_LOG_SEV(lg, debug) << "Started weaving.";

    masd::dogen::templating::stitch::workflow w(false/*compatibility_mode*/);
    w.execute(target);
    BOOST_LOG_SEV(lg, debug) << "Started weaving.";
}

}
