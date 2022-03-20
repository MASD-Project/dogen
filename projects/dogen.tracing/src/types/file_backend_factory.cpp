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
#include "dogen.utility/types/io/optional_io.hpp"
#include "dogen/io/tracing_configuration_io.hpp"
#include "dogen.tracing/types/file_backend.hpp"
#include "dogen.tracing/types/file_backend_factory.hpp"

namespace {

const std::string id("tracing.relational_backend_factory");

using namespace dogen::utility::log;
auto lg(logger_factory(id));

}

namespace dogen::tracing {

std::string file_backend_factory::id() const {
    return ::id;
}

dogen::tracing_backend file_backend_factory::tracing_backend() const {
    return dogen::tracing_backend::file;
}

boost::shared_ptr<backend> file_backend_factory::
make(const configuration& cfg,  const std::string& version,
    const std::string& activity, const std::string& logging_impact,
    const std::string& tracing_impact) const {
    BOOST_LOG_SEV(lg, debug) << "Creating relational backend.";

    const auto& tcfg(cfg.tracing());
    BOOST_LOG_SEV(lg, trace) << "Tracing configuration: " << tcfg;
    if (!tcfg) {
        BOOST_LOG_SEV(lg, trace) << "No tracing configuration.";
        return boost::shared_ptr<backend>();
    } else if (tcfg->backend() != tracing_backend()) {
        BOOST_LOG_SEV(lg, trace) << "Tracing backend is not file.";
        return boost::shared_ptr<backend>();
    }

    return boost::make_shared<file_backend>(*tcfg, version, tcfg->run_id(),
        activity, logging_impact, tracing_impact);
}

}
