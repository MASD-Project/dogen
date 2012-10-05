/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include <boost/log/common.hpp>
#include <boost/log/filters.hpp>
#include <boost/log/formatters.hpp>
#include <boost/log/utility/init/common_attributes.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include "dogen/utility/exception/invalid_enum_value.hpp"
#include "dogen/utility/log/life_cycle_manager.hpp"

namespace {

const std::string postfix(".log");
const std::string channel_attr("Channel");
const std::string severity_attr("Severity");
const std::string time_stamp_attr("TimeStamp");
const std::string record_format("%1% [%2%] [%3%] %4%");
const std::string time_stamp_format("%Y-%m-%d %H:%M:%S.%f");

template<typename Backend>
void setup_formatter(boost::shared_ptr<Backend> backend) {
    using namespace boost::log;
    using dogen::utility::log::severity_level;

    backend->set_formatter(
        formatters::format(record_format)
        % formatters::date_time(time_stamp_attr,
            keywords::format = time_stamp_format, std::nothrow)
        % formatters::attr<severity_level>(severity_attr, std::nothrow)
        % formatters::attr<std::string>(channel_attr, std::nothrow)
        % formatters::message());
}

template<typename Backend>
void add_backend(boost::shared_ptr<Backend> backend,
    dogen::utility::log::severity_level severity,
    std::list<boost::shared_ptr<boost::log::core::sink_type> >& sinks) {
    using namespace boost::log;
    typedef sinks::synchronous_sink<Backend> sink_type;
    boost::shared_ptr<sink_type> sink(new sink_type(backend));

    using dogen::utility::log::severity_level;
    sink->set_filter(filters::attr<severity_level>(severity_attr,
            std::nothrow) >= severity);

    boost::shared_ptr<core> core(core::get());
    core->add_sink(sink);
    sinks.push_back(sink);
}

}

namespace dogen {
namespace utility {
namespace log {

std::list<boost::shared_ptr<boost::log::core::sink_type> >
life_cycle_manager::sinks_;

void life_cycle_manager::
create_file_backend(std::string file_name, severity_level severity) {
    using namespace boost::log;
    boost::shared_ptr<sinks::text_file_backend> backend(
        boost::make_shared<sinks::text_file_backend>(
            keywords::file_name = file_name + postfix,
            keywords::rotation_size = 5 * 1024 * 1024,
            keywords::time_based_rotation =
            sinks::file::rotation_at_time_point(12, 0, 0)
            )
        );

    setup_formatter<sinks::text_file_backend>(backend);
    add_backend(backend, severity, sinks_);
}

void life_cycle_manager::create_console_backend(severity_level severity) {
    using namespace boost::log;
    boost::shared_ptr<sinks::text_ostream_backend>
        backend(boost::make_shared<sinks::text_ostream_backend>());
    backend->add_stream(boost::shared_ptr<std::ostream>(&std::clog,
            empty_deleter()));

    setup_formatter<sinks::text_ostream_backend>(backend);
    add_backend(backend, severity, sinks_);
}

void life_cycle_manager::initialise(std::string file_name,
    severity_level severity, bool log_to_console) {
    if (log_to_console)
        create_console_backend(severity);

    create_file_backend(file_name, severity);
    boost::log::add_common_attributes();
}

void life_cycle_manager::shutdown() {
    using namespace boost::log;
    boost::shared_ptr<core> core(core::get());
    for (auto s : sinks_)
        core->remove_sink(s);
}

} } }
