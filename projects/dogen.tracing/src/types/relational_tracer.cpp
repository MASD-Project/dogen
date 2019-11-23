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
#include "dogen/config.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/tracing_error.hpp"
#include "dogen.tracing/types/relational_tracer.hpp"
#ifdef DOGEN_HAVE_RELATIONAL_MODEL
#endif

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("tracing.relational_tracer"));

const std::string empty;
const std::string directory_missing("Tracing data directory must be supplied.");

}

namespace dogen::tracing {

namespace {

#ifdef DOGEN_HAVE_RELATIONAL_MODEL

class relational_impl: public relational_tracer{
public:
    relational_impl(const boost::optional<tracing_configuration>& tcfg,
        const boost::optional<database_configuration>& dbcfg);
    virtual ~relational_impl() {}

public:
    virtual void add_initial_input(const std::string& input_id,
        const std::string& input) const override;
};

relational_impl::relational_impl(
    const boost::optional<tracing_configuration>& /*tcfg*/,
    const boost::optional<database_configuration>& /*dbcfg*/) {

}

void relational_impl::add_initial_input(const std::string& input_id,
    const std::string& /*input*/) const {
    BOOST_LOG_SEV(lg, debug) << "Adding initial input: " << input_id;
}

#else

const std::string no_relational_support(
    "Dogen compiled without relational support.");


class null_impl: public relational_tracer {
public:
    impl(const boost::optional<tracing_configuration>& tcfg,
        const boost::optional<database_configuration>& dbcfg) {
        BOOST_LOG_SEV(lg, error) << no_relational_support;
        BOOST_THROW_EXCEPTION(tracing_error(no_relational_support));
    }

    virtual ~relational_impl() {}

public:
    virtual void add_initial_input(const std::string& input_id,
        const std::string& input) const overide {
        BOOST_LOG_SEV(lg, error) << no_relational_support;
        BOOST_THROW_EXCEPTION(tracing_error(no_relational_support));
    }
};

#endif

}

relational_tracer* make_relational_tracer(
    const boost::optional<tracing_configuration>& tcfg,
    const boost::optional<database_configuration>& dbcfg) {

    if (!tcfg || tcfg->backend() != tracing_backend::relational_database)
        return nullptr;

#ifdef DOGEN_HAVE_RELATIONAL_MODEL
    return new relational_impl(tcfg, dbcfg);
#else
    return new null_impl(tcfg, dbcfg);
#endif
}

}
