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
#include <boost/throw_exception.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "dogen/config.hpp"
#include "dogen/io/tracing_configuration_io.hpp"
#include "dogen/io/database_configuration_io.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/tracing_error.hpp"
#include "dogen.relational/types/tracing/run_event.hpp"
#include "dogen.relational/types/tracing/run_event_key.hpp"
#include "dogen.relational/odb/tracing/run_event-odb.hxx"
#include "dogen.relational/odb/tracing/run_event-odb-pgsql.hxx"
#include "dogen.relational/odb/tracing/run_event_key-odb.hxx"
#include "dogen.relational/odb/tracing/run_event_key-odb-pgsql.hxx"
#include "dogen.relational/types/tracing/transform_event.hpp"
#include "dogen.relational/odb/tracing/transform_event-odb.hxx"
#include "dogen.relational/odb/tracing/transform_event-odb-pgsql.hxx"
#include "dogen.relational/odb/tracing/transform_event_key-odb.hxx"
#include "dogen.relational/odb/tracing/transform_event_key-odb-pgsql.hxx"
#include "dogen.relational/types/tracing/relational_backend.hpp"

namespace {

const std::string id("tracing.relational_backend");

using namespace dogen::utility::log;
auto lg(logger_factory(id));

const std::string empty;
const std::string directory_missing("Tracing data directory must be supplied.");
const std::string no_tracing_configuration(
    "Tracing configuration not supplied.");
const std::string no_database_configuration(
    "Database configuration not supplied.");

}

namespace dogen::relational::tracing {

std::string relational_backend::id() const {
    return ::id;
}

dogen::tracing_backend relational_backend::tracing_backend() const {
    return dogen::tracing_backend::relational_database;
}

void relational_backend::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::tracing::relational_backend\"" << " }";
}

relational_backend::relational_backend(const tracing_configuration& tcfg,
    const database_configuration& dbcfg, const std::string& version,
    const std::string& run_id, const std::string& activity,
    const std::string& logging_impact, const std::string& tracing_impact)
    : tracing_configuration_(tcfg), database_configuration_(dbcfg),
      version_(version), run_id_(run_id), activity_(activity),
      logging_impact_(logging_impact), tracing_impact_(tracing_impact) {

    BOOST_LOG_SEV(lg, debug) << "Tracer initialised.";
    BOOST_LOG_SEV(lg, trace) << "Tracing configuration: "
                             << tracing_configuration_;
    BOOST_LOG_SEV(lg, trace) << "Database configuration: "
                             << database_configuration_;

    using odb::pgsql::database;
    database_ = boost::make_shared<database>(dbcfg.user(),
        dbcfg.password(), dbcfg.name(), dbcfg.host(), dbcfg.port());


    if (database_configuration_.generate_schema()) {
        BOOST_LOG_SEV(lg, info) << "Generating database schema.";
        odb::transaction t(database_->begin());
        odb::schema_catalog::create_schema(*database_);
        t.commit();
        BOOST_LOG_SEV(lg, info) << "Finished generating database schema.";
    } else
        BOOST_LOG_SEV(lg, info) << "Not generating database schema.";
}

void relational_backend::start_run(const std::string& input_id,
    const std::string& input) const {
    BOOST_LOG_SEV(lg, debug) << "Adding initial input: " << input_id;

    run_event_key k;
    k.run_id(run_id(run_id_));
    k.event_type(event_type::start);

    run_event re;
    re.run_event_key(k);
    re.version(version_);
    re.payload(json(input));
    re.activity(activity_);
    re.timestamp(boost::posix_time::microsec_clock::universal_time());
    re.logging_impact(logging_impact_);
    re.tracing_impact(tracing_impact_);

    odb::transaction t(database_->begin());
    database_->persist(re);
    t.commit();
}

void relational_backend::end_run() const {
    run_event_key k;
    k.run_id(run_id(run_id_));
    k.event_type(event_type::end);

    run_event re;
    re.run_event_key(k);
    re.version(version_);
    re.activity(activity_);
    re.timestamp(boost::posix_time::microsec_clock::universal_time());
    re.payload(json("{}"));
    re.timestamp(boost::posix_time::microsec_clock::universal_time());
    re.logging_impact(logging_impact_);
    re.tracing_impact(tracing_impact_);

    odb::transaction t(database_->begin());
    database_->persist(re);
    t.commit();
}

void relational_backend::add_references_graph(
    const std::string& /*root_vertex*/,
    const std::unordered_map<std::string, std::list<std::string>>&
    /*edges_per_model*/) const {
}

void relational_backend::
start_chain(const std::string& parent_transform_instance_id,
    const std::string& transform_id,
    const std::string& transform_instance_id) const {
    transform_event_key k;
    k.transform_instance_id(
        tracing::transform_instance_id(transform_instance_id));
    k.event_type(event_type::start);

    transform_event te;
    te.transform_event_key(k);
    te.run_id(run_id(run_id_));
    te.timestamp(boost::posix_time::microsec_clock::universal_time());
    te.payload(json("{}"));
    te.transform_type(transform_type::chain);
    te.transform_id(tracing::transform_id(transform_id));
    te.parent_transform(
        tracing::transform_instance_id(parent_transform_instance_id));

    odb::transaction t(database_->begin());
    database_->persist(te);
    t.commit();
}

void relational_backend::start_chain(
    const std::string& parent_transform_instance_id,
    const std::string& transform_id,
    const std::string& transform_instance_id,
    const std::string& model_id) const {

    transform_event_key k;
    k.transform_instance_id(
        tracing::transform_instance_id(transform_instance_id));
    k.event_type(event_type::start);

    transform_event te;
    te.transform_event_key(k);
    te.run_id(run_id(run_id_));
    te.timestamp(boost::posix_time::microsec_clock::universal_time());
    te.payload(json("{}"));
    te.transform_type(transform_type::chain);
    te.transform_id(tracing::transform_id(transform_id));
    te.model_id(model_id);
    te.parent_transform(
        tracing::transform_instance_id(parent_transform_instance_id));

    odb::transaction t(database_->begin());
    database_->persist(te);
    t.commit();
}

void relational_backend::start_chain(
    const std::string& parent_transform_instance_id,
    const std::string& transform_id,
    const std::string& transform_instance_id,
    const std::string& model_id,
    const std::string& input) const {

    transform_event_key k;
    k.transform_instance_id(
        tracing::transform_instance_id(transform_instance_id));
    k.event_type(event_type::start);

    transform_event te;
    te.transform_event_key(k);
    te.run_id(run_id(run_id_));
    te.timestamp(boost::posix_time::microsec_clock::universal_time());
    te.payload(json(input));
    te.transform_type(transform_type::chain);
    te.transform_id(tracing::transform_id(transform_id));
    te.model_id(model_id);
    te.parent_transform(
        tracing::transform_instance_id(parent_transform_instance_id));

    odb::transaction t(database_->begin());
    database_->persist(te);
    t.commit();
}

void relational_backend::
end_chain(const std::string& parent_transform_instance_id,
    const std::string& transform_id,
    const std::string& transform_instance_id) const {
    transform_event_key k;
    k.transform_instance_id(
        tracing::transform_instance_id(transform_instance_id));
    k.event_type(event_type::end);

    transform_event te;
    te.transform_event_key(k);
    te.run_id(run_id(run_id_));
    te.timestamp(boost::posix_time::microsec_clock::universal_time());
    te.payload(json("{}"));
    te.transform_type(transform_type::chain);
    te.transform_id(tracing::transform_id(transform_id));
    te.parent_transform(
        tracing::transform_instance_id(parent_transform_instance_id));

    odb::transaction t(database_->begin());
    database_->persist(te);
    t.commit();
}

void relational_backend::
end_chain(const std::string& parent_transform_instance_id,
    const std::string& transform_id, const std::string& transform_instance_id,
    const std::string& /*model_id*/, const std::string& output) const {
    transform_event_key k;
    k.transform_instance_id(
        tracing::transform_instance_id(transform_instance_id));
    k.event_type(event_type::end);

    transform_event te;
    te.transform_event_key(k);
    te.run_id(run_id(run_id_));
    te.timestamp(boost::posix_time::microsec_clock::universal_time());
    te.payload(json(output));
    te.transform_type(transform_type::chain);
    te.transform_id(tracing::transform_id(transform_id));
    te.parent_transform(
        tracing::transform_instance_id(parent_transform_instance_id));

    odb::transaction t(database_->begin());
    database_->persist(te);
    t.commit();
}

void relational_backend::start_transform(
    const std::string& parent_transform_instance_id,
    const std::string& transform_id,
    const std::string& transform_instance_id) const {
    transform_event_key k;
    k.transform_instance_id(
        tracing::transform_instance_id(transform_instance_id));
    k.event_type(event_type::start);

    transform_event te;
    te.transform_event_key(k);
    te.run_id(run_id(run_id_));
    te.timestamp(boost::posix_time::microsec_clock::universal_time());
    te.payload(json("{}"));
    te.transform_type(transform_type::leaf);
    te.transform_id(tracing::transform_id(transform_id));
    te.parent_transform(
        tracing::transform_instance_id(parent_transform_instance_id));

    odb::transaction t(database_->begin());
    database_->persist(te);
    t.commit();
}

void relational_backend::start_transform(
    const std::string& parent_transform_instance_id,
    const std::string& transform_id,
    const std::string& transform_instance_id,
    const std::string& model_id) const {
    transform_event_key k;
    k.transform_instance_id(
        tracing::transform_instance_id(transform_instance_id));
    k.event_type(event_type::start);

    transform_event te;
    te.transform_event_key(k);
    te.run_id(run_id(run_id_));
    te.timestamp(boost::posix_time::microsec_clock::universal_time());
    te.payload(json("{}"));
    te.transform_type(transform_type::leaf);
    te.transform_id(tracing::transform_id(transform_id));
    te.model_id(model_id);
    te.parent_transform(
        tracing::transform_instance_id(parent_transform_instance_id));

    odb::transaction t(database_->begin());
    database_->persist(te);
    t.commit();
}

void relational_backend::start_transform(
    const std::string& parent_transform_instance_id,
    const std::string& transform_id,
    const std::string& transform_instance_id,
    const std::string& model_id,
    const std::string& input) const {
    transform_event_key k;
    k.transform_instance_id(
        tracing::transform_instance_id(transform_instance_id));
    k.event_type(event_type::start);

    transform_event te;
    te.transform_event_key(k);
    te.run_id(run_id(run_id_));
    te.timestamp(boost::posix_time::microsec_clock::universal_time());
    te.payload(json(input));
    te.transform_type(transform_type::leaf);
    te.transform_id(tracing::transform_id(transform_id));
    te.model_id(model_id);
    te.parent_transform(
        tracing::transform_instance_id(parent_transform_instance_id));

    odb::transaction t(database_->begin());
    database_->persist(te);
    t.commit();
}

void relational_backend::
end_transform(const std::string& parent_transform_instance_id,
    const std::string& transform_id,
    const std::string& transform_instance_id) const {
    transform_event_key k;
    k.transform_instance_id(
        tracing::transform_instance_id(transform_instance_id));
    k.event_type(event_type::end);

    transform_event te;
    te.transform_event_key(k);
    te.run_id(run_id(run_id_));
    te.timestamp(boost::posix_time::microsec_clock::universal_time());
    te.payload(json("{}"));
    te.transform_type(transform_type::leaf);
    te.transform_id(tracing::transform_id(transform_id));
    te.parent_transform(
        tracing::transform_instance_id(parent_transform_instance_id));

    odb::transaction t(database_->begin());
    database_->persist(te);
    t.commit();
}

void relational_backend::end_transform(
    const std::string& parent_transform_instance_id,
    const std::string& transform_id, const std::string& transform_instance_id,
    const std::string& /*model_id*/, const std::string& output) const {
    transform_event_key k;
    k.transform_instance_id(
        tracing::transform_instance_id(transform_instance_id));
    k.event_type(event_type::end);

    transform_event te;
    te.transform_event_key(k);
    te.run_id(run_id(run_id_));
    te.timestamp(boost::posix_time::microsec_clock::universal_time());
    te.payload(json(output));
    te.transform_type(transform_type::leaf);
    te.transform_id(tracing::transform_id(transform_id));
    te.parent_transform(
        tracing::transform_instance_id(parent_transform_instance_id));

    odb::transaction t(database_->begin());
    database_->persist(te);
    t.commit();
}

}
