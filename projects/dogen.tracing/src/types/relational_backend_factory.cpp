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
#include "dogen/config.hpp"
#ifndef DOGEN_HAVE_RELATIONAL_MODEL
// dummy function to suppress ranlib warnings
void dumm_contents() { }
#else

#include <boost/make_shared.hpp>
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/io/optional_io.hpp"
#include "dogen/io/tracing_configuration_io.hpp"
#include "dogen/io/database_configuration_io.hpp"
#include "dogen.tracing/types/tracing_error.hpp"
#include "dogen.tracing/types/relational_backend.hpp"
#include "dogen.tracing/types/relational_backend_factory.hpp"

namespace {

const std::string id("tracing.relational_backend_factory");

using namespace dogen::utility::log;
auto lg(logger_factory(id));

const std::string no_database_config("Relational tracing requested but "
    " database settings not provided.");

}

namespace dogen::tracing {

std::string relational_backend_factory::id() const {
    return ::id;
}

dogen::tracing_backend relational_backend_factory::tracing_backend() const {
    return dogen::tracing_backend::relational_database;
}

boost::shared_ptr<backend> relational_backend_factory::
make(const configuration& cfg, const std::string& run_id) const {
    BOOST_LOG_SEV(lg, debug) << "Creating relational backend.";

    const auto& tcfg(cfg.tracing());
    BOOST_LOG_SEV(lg, trace) << "Tracing configuration: " << tcfg;
    if (!tcfg) {
        BOOST_LOG_SEV(lg, trace) << "No tracing configuration.";
        return boost::shared_ptr<backend>();
    } else if (tcfg->backend() != tracing_backend()) {
        BOOST_LOG_SEV(lg, trace) << "Backend is not relational database.";
        return boost::shared_ptr<backend>();
    }

    const auto& dbcfg(cfg.database());
    BOOST_LOG_SEV(lg, trace) << "Database configuration: " << dbcfg;
    if (!dbcfg) {
        BOOST_LOG_SEV(lg, error) << no_database_config;
        BOOST_THROW_EXCEPTION(tracing_error(no_database_config));
    }

    return boost::make_shared<relational_backend>(*tcfg, *dbcfg, run_id);
}

}

#endif
