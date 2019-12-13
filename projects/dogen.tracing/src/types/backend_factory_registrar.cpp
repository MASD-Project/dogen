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
#include "dogen.tracing/types/backend_factory.hpp"
#include "dogen.tracing/types/registrar_error.hpp"
#include "dogen.tracing/types/backend_factory_registrar.hpp"


namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("tracing.backend_factory_registrar"));

const std::string no_factories("No backend factories provided.");
const std::string missing_factory("Backend factory not available: ");
const std::string null_factory("Backend factory supplied is null.");
const std::string duplicate_factory(
    "More than one backend factory registered for this id: ");

}

namespace dogen::tracing {

void backend_factory_registrar::
register_backend_factory(const boost::shared_ptr<backend_factory> bf) {
    if (!bf) {
        BOOST_LOG_SEV(lg, error) << null_factory;
        BOOST_THROW_EXCEPTION(registrar_error(null_factory));
    }

    const auto tb(bf->tracing_backend());
    const auto pair(std::make_pair(tb, bf));
    const auto inserted(backend_factories_.insert(pair).second);
    if (!inserted) {
        const auto s(boost::lexical_cast<std::string>(tb));
        BOOST_LOG_SEV(lg, error) << duplicate_factory + s;
        BOOST_THROW_EXCEPTION(registrar_error(duplicate_factory + s));
    }

    BOOST_LOG_SEV(lg, debug) << "Registered backend factory: " << bf->id();
}

void backend_factory_registrar::validate() const {
    if (backend_factories_.empty()) {
        BOOST_LOG_SEV(lg, error) << no_factories;
        BOOST_THROW_EXCEPTION(registrar_error(no_factories));
    }
    BOOST_LOG_SEV(lg, debug) << "Registrar is in a valid state. Found: "
                             << backend_factories_.size()
                             << " backend factories.";

    for (const auto& pair : backend_factories_)
        BOOST_LOG_SEV(lg, trace) << "Backend factory: " << pair.second->id();
}

const boost::shared_ptr<backend_factory>
backend_factory_registrar::obtain_backend_factory(const tracing_backend tb) {
    const auto i(backend_factories_.find(tb));
    if (i == backend_factories_.end()) {
        const auto s(boost::lexical_cast<std::string>(tb));
        BOOST_LOG_SEV(lg, error) << missing_factory << s;
        BOOST_THROW_EXCEPTION(registrar_error(missing_factory + s));
    }
    return i->second;
}

}
