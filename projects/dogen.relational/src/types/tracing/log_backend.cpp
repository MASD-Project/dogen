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
#include <boost/log/core.hpp>
#include <boost/log/sinks.hpp>
#include <boost/make_shared.hpp>
#include <boost/log/common.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/expressions/attr.hpp>
#include <boost/log/expressions/message.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/log/expressions.hpp>
#include "dogen.utility/types/log/severity_level.hpp"
#include "dogen.relational/types/tracing/log_event.hpp"
#include "dogen.relational/odb/tracing/log_event-odb.hxx"
#include "dogen.relational/odb/tracing/log_event-odb-pgsql.hxx"
#include "dogen.relational/types/tracing/log_backend.hpp"

namespace {

const std::string channel_attr("Channel");
const std::string severity_attr("Severity");
const std::string time_stamp_attr("TimeStamp");
const std::string record_format("%1% [%2%] [%3%] %4%");
const std::string time_stamp_format("%Y-%m-%d %H:%M:%S.%f");

}

namespace dogen::relational::tracing {

log_backend::
log_backend(const std::string& run_id, const database_configuration& dbcfg)
    : run_id_(run_id) {

    using odb::pgsql::database;
    database_ = boost::make_shared<database>(dbcfg.user(),
        dbcfg.password(), dbcfg.name(), dbcfg.host(), dbcfg.port());
}

void log_backend::consume(const boost::log::record_view& rv,
    const string_type& /*formatted_message*/) {
    using namespace boost::log;
    using utility::log::severity_level;

    log_event le;
    le.run_id(run_id(run_id_));
    le.message(rv[expressions::smessage].get());
    le.timestamp(
        rv[time_stamp_attr].extract_or_throw<boost::posix_time::ptime>());

    std::ostringstream s;
    s << rv[severity_attr].extract_or_throw<severity_level>();
    le.severity(s.str());
    s.str("");

    s << rv[channel_attr].extract_or_throw<std::string>();
    le.component(s.str());

    odb::transaction t(database_->begin());
    database_->persist(le);
    t.commit();
}

void create_relational_log_backend(const std::string& run_id,
    const database_configuration& dbcfg,
    const utility::log::severity_level severity) {
    using namespace boost::log;

    auto backend(boost::make_shared<log_backend>(run_id, dbcfg));

    typedef sinks::synchronous_sink<log_backend> sink_type;
    auto sink(boost::make_shared<sink_type>(backend));

    using utility::log::severity_level;
    sink->set_filter(
        expressions::attr<severity_level>(severity_attr) >= severity);

    sink->set_formatter(expressions::format(record_format)
        % expressions::format_date_time<boost::posix_time::ptime>(
            time_stamp_attr, time_stamp_format)
        % expressions::attr<severity_level>(severity_attr)
        % expressions::attr<std::string>(channel_attr)
        % expressions::smessage);

    boost::log::core::get()->add_sink(sink);
}

}
