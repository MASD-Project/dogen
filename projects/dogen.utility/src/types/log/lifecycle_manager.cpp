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
#include <boost/core/null_deleter.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/log/core.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/common.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/support/date_time.hpp>
#include "dogen.utility/types/log/logging_configuration_validator.hpp"
#include "dogen.utility/types/log/lifecycle_manager.hpp"

namespace {

const std::string extension(".log");
const std::string channel_attr("Channel");
const std::string severity_attr("Severity");
const std::string time_stamp_attr("TimeStamp");
const std::string record_format("%1% [%2%] [%3%] %4%");
const std::string time_stamp_format("%Y-%m-%d %H:%M:%S.%f");

}

namespace dogen::utility::log {

void lifecycle_manager::create_file_backend(
    boost::filesystem::path path, const severity_level severity) {
    using namespace boost::log;

    if (path.extension() != extension)
        path += extension;

    auto backend(boost::make_shared<sinks::text_file_backend>(
            keywords::file_name = path.string(),
            keywords::rotation_size = 300 * 1024 * 1024,
            keywords::time_based_rotation =
            sinks::file::rotation_at_time_point(12, 0, 0)));
    backend->auto_flush(true);

    typedef sinks::synchronous_sink<sinks::text_file_backend> sink_type;
    auto sink(boost::make_shared<sink_type>(backend));

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

void lifecycle_manager::create_console_backend(const severity_level severity) {
    using namespace boost; // to handle empty deleter moving namespaces
    using namespace boost::log;

    boost::shared_ptr<std::ostream> s(&std::clog, null_deleter());
    auto backend(boost::make_shared<sinks::text_ostream_backend>());
    backend->add_stream(s);

    typedef sinks::synchronous_sink<sinks::text_ostream_backend> sink_type;
    auto sink(boost::make_shared<sink_type>(backend));

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

void lifecycle_manager::
initialise(const boost::optional<logging_configuration>& ocfg) {
    /*
     * If no configuration is supplied, logging is to be disabled.
     */
    auto& core(*boost::log::core::get());
    if (!ocfg) {
        core.set_logging_enabled(false);
        return;
    }

    /*
     * A configuration was supplied. Ensure it is valid.
     */
    const auto& cfg(*ocfg);
    logging_configuration_validator::validate(cfg);
    core.set_logging_enabled(true);

    /*
     * Use the configuration to setup the logging infrastructure for
     * both console and file, if enabled. We don't have to worry about
     * making sure that at least one is enabled - that is the
     * validator's job.
     */
    const auto sl(to_severity_level(cfg.severity()));
    if (cfg.output_to_console())
        create_console_backend(sl);

    if (!cfg.filename().empty()) {
        const auto path(cfg.output_directory() / cfg.filename());
        create_file_backend(path, sl);
    }

    /*
     * Finally, add the timestamp attributes.
     */
    core.add_global_attribute(time_stamp_attr,
        boost::log::attributes::local_clock());
}

void lifecycle_manager::shutdown() {
    auto core(boost::log::core::get());
    core->remove_all_sinks();
}

}
