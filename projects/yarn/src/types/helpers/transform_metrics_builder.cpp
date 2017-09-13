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
#include <boost/uuid/uuid.hpp>
#include <boost/make_shared.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/throw_exception.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/yarn/types/helpers/building_error.hpp"
#include "dogen/yarn/types/helpers/transform_metrics.hpp"
#include "dogen/yarn/types/helpers/transform_metrics_builder.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("yarn.helpers.transform_metrics_builder"));

const std::string root_id("root");
const std::string unexpected_empty(
    "Logic error, no transforms started at present");
const std::string unmatch_start_end(
    "Expected the same number of start and end calls");

}

namespace dogen {
namespace yarn {
namespace helpers {

transform_metrics_builder::transform_metrics_builder() {
    BOOST_LOG_SEV(lg, debug) << "Initialising. ";
    stack_.push(create_metrics(root_id));
}

void transform_metrics_builder::ensure_stack_not_empty() const {
    if (stack_.empty()) {
        BOOST_LOG_SEV(lg, error) << unexpected_empty;
        BOOST_THROW_EXCEPTION(building_error(unexpected_empty));
    }
}

boost::shared_ptr<transform_metrics>
transform_metrics_builder::create_metrics(const std::string& id) const {
    BOOST_LOG_SEV(lg, debug) << "Creating metrics for id: " << id;
    auto r(boost::make_shared<transform_metrics>());
    r->id(id);

    auto uuid = boost::uuids::random_generator()();
    r->guid(boost::uuids::to_string(uuid));

    using namespace std::chrono;
    auto now(time_point_cast<milliseconds>(system_clock::now()));
    r->start(now.time_since_epoch().count());
    return r;
}

void transform_metrics_builder::update_end() {
    using namespace std::chrono;
    auto now(time_point_cast<milliseconds>(system_clock::now()));
    stack_.top()->end(now.time_since_epoch().count());
}

void transform_metrics_builder::start(const std::string& id) {
    BOOST_LOG_SEV(lg, debug) << "Starting id: " << id;

    ensure_stack_not_empty();
    auto next(create_metrics(id));
    stack_.top()->children().push_back(next);
    stack_.push(next);
}

void transform_metrics_builder::end() {
    BOOST_LOG_SEV(lg, debug) << "Ending id: " << current()->id();

    ensure_stack_not_empty();
    update_end();
    stack_.pop();
}

const boost::shared_ptr<const transform_metrics>
transform_metrics_builder::current() const {
    return stack_.top();
}

boost::shared_ptr<transform_metrics> transform_metrics_builder::build() {
    BOOST_LOG_SEV(lg, debug) << "Building.";

    if (stack_.size() != 1) {
        BOOST_LOG_SEV(lg, error) << unmatch_start_end;
        BOOST_THROW_EXCEPTION(building_error(unmatch_start_end));
    }

    update_end();
    return stack_.top();
}

} } }
