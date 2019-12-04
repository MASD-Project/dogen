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
#include <ostream>
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/io/backend_io.hpp"
#include "dogen.tracing/types/tracing_error.hpp"
#include "dogen.tracing/types/throw_backend.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("tracing.relational_backend"));

const std::string no_relational_support(
    "Dogen compiled without relational support.");

}

namespace dogen::tracing {

void throw_backend::to_stream(std::ostream& s) const {
    s << " { "
      << "\"__type__\": " << "\"dogen::tracing::throw_backend\"" << ", "
      << "\"__parent_0__\": ";
    dogen::tracing::backend::to_stream(s);
    s << " }";
}

void throw_backend::start_tracing(const std::string& /*run_id*/,
    const std::string& /*input_id*/,
    const std::string& /*input*/) const {
    BOOST_LOG_SEV(lg, error) << no_relational_support;
    BOOST_THROW_EXCEPTION(tracing_error(no_relational_support));
}

void throw_backend::end_tracing() const {
    BOOST_LOG_SEV(lg, error) << no_relational_support;
    BOOST_THROW_EXCEPTION(tracing_error(no_relational_support));
}

void throw_backend::add_references_graph(const std::string& /*root_vertex*/,
    const std::unordered_map<std::string, std::list<std::string>>&
    /*edges_per_model*/) const {
    BOOST_LOG_SEV(lg, error) << no_relational_support;
    BOOST_THROW_EXCEPTION(tracing_error(no_relational_support));
}

void throw_backend::start_chain(const std::string& /*transform_id*/,
    const std::string& /*transform_instance_id*/) const {
    BOOST_LOG_SEV(lg, error) << no_relational_support;
    BOOST_THROW_EXCEPTION(tracing_error(no_relational_support));
}

void throw_backend::start_chain(const std::string& /*transform_id*/,
    const std::string& /*transform_instance_id*/,
    const std::string& /*model_id*/) const {
    BOOST_LOG_SEV(lg, error) << no_relational_support;
    BOOST_THROW_EXCEPTION(tracing_error(no_relational_support));
}

void throw_backend::start_chain(const std::string& /*transform_id*/,
    const std::string& /*transform_instance_id*/,
    const std::string& /*model_id*/,
    const std::string& /*input*/) const {
    BOOST_LOG_SEV(lg, error) << no_relational_support;
    BOOST_THROW_EXCEPTION(tracing_error(no_relational_support));
}

void throw_backend::end_chain() const {
    BOOST_LOG_SEV(lg, error) << no_relational_support;
    BOOST_THROW_EXCEPTION(tracing_error(no_relational_support));
}

void throw_backend::end_chain(const std::string& /*output*/) const {
    BOOST_LOG_SEV(lg, error) << no_relational_support;
    BOOST_THROW_EXCEPTION(tracing_error(no_relational_support));
}

void throw_backend::start_transform(const std::string& /*transform_id*/,
    const std::string& /*transform_instance_id*/) const {
    BOOST_LOG_SEV(lg, error) << no_relational_support;
    BOOST_THROW_EXCEPTION(tracing_error(no_relational_support));
}

void throw_backend::start_transform(const std::string& /*transform_id*/,
    const std::string& /*transform_instance_id*/,
    const std::string& /*model_id*/) const {
    BOOST_LOG_SEV(lg, error) << no_relational_support;
    BOOST_THROW_EXCEPTION(tracing_error(no_relational_support));
}

void throw_backend::start_transform(const std::string& /*transform_id*/,
    const std::string& /*transform_instance_id*/,
    const std::string& /*model_id*/,
    const std::string& /*input*/) const {
    BOOST_LOG_SEV(lg, error) << no_relational_support;
    BOOST_THROW_EXCEPTION(tracing_error(no_relational_support));
}

void throw_backend::end_transform() const {
    BOOST_LOG_SEV(lg, error) << no_relational_support;
    BOOST_THROW_EXCEPTION(tracing_error(no_relational_support));
}

void throw_backend::end_transform(const std::string& /*output*/) const {
    BOOST_LOG_SEV(lg, error) << no_relational_support;
    BOOST_THROW_EXCEPTION(tracing_error(no_relational_support));
}

}
