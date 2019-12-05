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
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen/io/tracing_backend_io.hpp"
#include "dogen.tracing/types/backend.hpp"
#include "dogen.tracing/types/registrar_error.hpp"
#include "dogen.tracing/types/backend_registrar.hpp"


namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("tracing.backend_registrar"));

const std::string no_backends("No backends provided.");
const std::string missing_backend("Backend not available: ");
const std::string null_backend("Backend supplied is null.");
const std::string duplicate_backend(
    "More than one backend registered for this id: ");

}

namespace dogen::tracing {

void backend_registrar::
    register_backend(const boost::shared_ptr<backend> b) {
    if (!b) {
        BOOST_LOG_SEV(lg, error) << null_backend;
        BOOST_THROW_EXCEPTION(registrar_error(null_backend));
    }

    const auto tb(b->tracing_backend());
    const auto pair(std::make_pair(tb, b));
    const auto inserted(backends_.insert(pair).second);
    if (!inserted) {
        const auto s(boost::lexical_cast<std::string>(tb));
        BOOST_LOG_SEV(lg, error) << duplicate_backend + s;
        BOOST_THROW_EXCEPTION(registrar_error(duplicate_backend + s));
    }

    BOOST_LOG_SEV(lg, debug) << "Registered backend: " << b->id();
}

void backend_registrar::validate() const {
    if (backends_.empty()) {
        BOOST_LOG_SEV(lg, error) << no_backends;
        BOOST_THROW_EXCEPTION(registrar_error(no_backends));
    }
    BOOST_LOG_SEV(lg, debug) << "Registrar is in a valid state.";
}

const boost::shared_ptr<backend>
backend_registrar::obtain_backend(const tracing_backend tb) {
    const auto i(backends_.find(tb));
    if (i == backends_.end()) {
        const auto s(boost::lexical_cast<std::string>(tb));
        BOOST_LOG_SEV(lg, error) << missing_backend << s;
        BOOST_THROW_EXCEPTION(registrar_error(missing_backend + s));
    }

    return i->second;
}

}
