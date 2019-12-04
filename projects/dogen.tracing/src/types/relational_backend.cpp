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
#include <boost/shared_ptr.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/config.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/tracing_error.hpp"
#include "dogen.tracing/types/relational_backend.hpp"
#ifdef DOGEN_HAVE_RELATIONAL_MODEL
#include <odb/database.hxx>
#include <odb/transaction.hxx>
#include <odb/pgsql/database.hxx>
#include <odb/schema-catalog.hxx>
#include "dogen.relational/types/tracing/run.hpp"
#include "dogen.relational/odb/tracing/run-odb.hxx"
#include "dogen.relational/odb/tracing/run-odb-pgsql.hxx"
#endif

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("tracing.relational_backend"));

const std::string empty;
const std::string directory_missing("Tracing data directory must be supplied.");
const std::string no_tracing_configuration(
    "Tracing configuration not supplied.");
const std::string no_database_configuration(
    "Database configuration not supplied.");

}

namespace dogen::tracing {

namespace {

#ifdef DOGEN_HAVE_RELATIONAL_MODEL

class relational_impl: public relational_backend{
public:
    relational_impl(const boost::optional<tracing_configuration>& tcfg,
        const boost::optional<database_configuration>& dbcfg);
    virtual ~relational_impl() {}

public:
    virtual void add_initial_input(const std::string& input_id,
        const std::string& input) const override;

private:
    boost::shared_ptr<odb::pgsql::database> database_;

};

relational_impl::relational_impl(
    const boost::optional<tracing_configuration>& tcfg,
    const boost::optional<database_configuration>& dbcfg) {

    if (!tcfg) {
        BOOST_LOG_SEV(lg, error) << no_tracing_configuration;
        BOOST_THROW_EXCEPTION(tracing_error(no_tracing_configuration));
    }

    if (!dbcfg) {
        BOOST_LOG_SEV(lg, error) << no_database_configuration;
        BOOST_THROW_EXCEPTION(tracing_error(no_database_configuration));
    }

    database_ = boost::make_shared<odb::pgsql::database>(dbcfg->user(),
        dbcfg->password(), dbcfg->name(), dbcfg->host(), dbcfg->port());

    odb::transaction t(database_->begin());
    odb::schema_catalog::create_schema(*database_);
    t.commit();
}

void relational_impl::add_initial_input(const std::string& input_id,
    const std::string& input) const {
    BOOST_LOG_SEV(lg, debug) << "Adding initial input: " << input_id;

    dogen::relational::tracing::run_id id("ABC");
    dogen::relational::tracing::json json(input);

    dogen::relational::tracing::run run;
    run.id(id);
    run.configuration(json);

    odb::transaction t(database_->begin());
    database_->persist(run);
    t.commit();
}

#else

const std::string no_relational_support(
    "Dogen compiled without relational support.");


class null_impl: public relational_backend {
public:
    null_impl(const boost::optional<tracing_configuration>& /*tcfg*/,
        const boost::optional<database_configuration>& /*dbcfg*/) {
        BOOST_LOG_SEV(lg, error) << no_relational_support;
        BOOST_THROW_EXCEPTION(tracing_error(no_relational_support));
    }

    virtual ~null_impl() {}

public:
    virtual void add_initial_input(const std::string& /*input_id*/,
        const std::string& /*input*/) const {
        BOOST_LOG_SEV(lg, error) << no_relational_support;
        BOOST_THROW_EXCEPTION(tracing_error(no_relational_support));
    }
};

#endif

}

void relational_backend::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::tracing::file_tracer\"" << " }";
}

relational_backend* make_relational_backend(
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
