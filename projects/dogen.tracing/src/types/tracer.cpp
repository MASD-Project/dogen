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
#include <boost/uuid/uuid.hpp>
#include <boost/make_shared.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include "dogen/config.hpp"
#include "dogen/io/tracing_backend_io.hpp"
#include "dogen/io/tracing_configuration_io.hpp"
#include "dogen/io/database_configuration_io.hpp"
#include "dogen.utility/types/io/optional_io.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/tracing_error.hpp"
#include "dogen.tracing/types/tracer.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("tracing.tracer"));

}

namespace dogen::tracing {

backend_factory_registrar tracer::registrar_;

backend_factory_registrar& tracer::registrar() {
    return registrar_;
}

tracer::tracer(const configuration& cfg, const std::string& activity)
    : backend_(registrar_.try_make_backend(cfg, generate_guid(), activity)) {}

std::string tracer::generate_guid() {
    const auto uuid = boost::uuids::random_generator()();
    return boost::uuids::to_string(uuid);
}

void tracer::add_references_graph(const std::string& root_vertex,
    const std::unordered_map<std::string, std::list<std::string>>&
    edges_per_model) const {
    if (backend_)
        backend_->add_references_graph(root_vertex, edges_per_model);
}

void tracer::end_run() const {
    BOOST_LOG_SEV(lg, debug) << "Finished tracing.";
    if (backend_)
        backend_->end_run();
}

void tracer::start_chain(const std::string& transform_id,
    const std::string& transform_instance_id) const {
    if (backend_)
        backend_->start_chain(transform_id, transform_instance_id);
}

void tracer::start_chain(const std::string& transform_id,
    const std::string& transform_instance_id,
    const std::string& model_id) const {
    if (backend_)
        backend_->start_chain(transform_id, transform_instance_id, model_id);
}

void tracer::start_transform(const std::string& transform_id,
    const std::string& transform_instance_id) const {
    if (backend_)
        backend_->start_transform(transform_id, transform_instance_id);
}

void tracer::start_transform(const std::string& transform_id,
    const std::string& transform_instance_id,
    const std::string& model_id) const {
    if (backend_)
        backend_->start_transform(transform_id,
            transform_instance_id, model_id);
}

void tracer::end_chain(const std::string& transform_id,
    const std::string& transform_instance_id) const {
    if (backend_)
        backend_->end_chain(transform_id, transform_instance_id);
}

void tracer::end_transform(const std::string& transform_id,
    const std::string& transform_instance_id) const {
    if (backend_)
        backend_->end_transform(transform_id, transform_instance_id);
}

bool tracer::operator==(const tracer& /*rhs*/) const {
    return false;
}

}
