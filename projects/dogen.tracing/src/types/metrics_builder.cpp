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
#include <chrono>
#include <sstream>
#include <boost/make_shared.hpp>
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/metrics.hpp"
#include "dogen.tracing/types/tracing_error.hpp"
#include "dogen.tracing/types/metrics_builder.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("tracing.metrics_builder"));

const std::string root_id("root");
const std::string unexpected_empty(
    "Logic error, no transforms started at present");
const std::string unmatch_start_end(
    "Expected the same number of start and end calls");

}

namespace dogen::tracing {

metrics_builder::metrics_builder(const std::string& version,
    const std::string& run_id, const std::string& logging_impact,
    const std::string& tracing_impact) {
    BOOST_LOG_SEV(lg, debug) << "Initialising.";
    std::ostringstream s;
    s << "version: v" << version << ", "
      << "logging impact: " << logging_impact << ", "
      << "tracing impact: " << tracing_impact;

    stack_.push(create_metrics(root_id, run_id, s.str()));
    BOOST_LOG_SEV(lg, debug) << "Stack size: " << stack_.size();
}

void metrics_builder::ensure_stack_not_empty() const {
    if (stack_.empty()) {
        BOOST_LOG_SEV(lg, error) << unexpected_empty;
        BOOST_THROW_EXCEPTION(tracing_error(unexpected_empty));
    }
}

boost::shared_ptr<metrics>
metrics_builder::create_metrics(const std::string& transform_id,
    const std::string& transform_instance_id,
    const std::string& model_id) const {
    BOOST_LOG_SEV(lg, debug) << "Creating metrics for: " << transform_id;

    auto r(boost::make_shared<metrics>());
    r->guid(transform_instance_id);
    r->transform_id(transform_id);
    r->model_id(model_id);

    using namespace std::chrono;
    auto now(time_point_cast<milliseconds>(system_clock::now()));
    const auto count(now.time_since_epoch().count());
    r->start(static_cast<unsigned long>(count));
    return r;
}

void metrics_builder::update_end() {
    ensure_stack_not_empty();
    using namespace std::chrono;
    auto now(time_point_cast<milliseconds>(system_clock::now()));
    const auto count(now.time_since_epoch().count());
    stack_.top()->end(static_cast<unsigned long>(count));
}

void metrics_builder::start(const std::string& transform_id,
    const std::string& transform_instance_id,
    const std::string& model_id) {
    BOOST_LOG_SEV(lg, debug) << "Starting: " << transform_id;

    ensure_stack_not_empty();
    auto next(create_metrics(transform_id, transform_instance_id, model_id));
    stack_.top()->children().push_back(next);
    stack_.push(next);
    BOOST_LOG_SEV(lg, debug) << "Stack size: " << stack_.size();
}

void metrics_builder::end() {
    BOOST_LOG_SEV(lg, debug) << "Ending: " << current()->transform_id();

    ensure_stack_not_empty();
    update_end();
    stack_.pop();
    BOOST_LOG_SEV(lg, debug) << "Stack size: " << stack_.size();
}

const boost::shared_ptr<const metrics>
metrics_builder::current() const {
    ensure_stack_not_empty();
    return stack_.top();
}

boost::shared_ptr<metrics> metrics_builder::build() {
    BOOST_LOG_SEV(lg, debug) << "Building.";
    BOOST_LOG_SEV(lg, debug) << "Stack size: " << stack_.size();

    if (stack_.size() != 1) {
        BOOST_LOG_SEV(lg, error) << unmatch_start_end;
        BOOST_THROW_EXCEPTION(tracing_error(unmatch_start_end));
    }

    update_end();
    return stack_.top();
}

}
