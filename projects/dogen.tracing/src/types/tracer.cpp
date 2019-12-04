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
#include "dogen/io/tracing_configuration_io.hpp"
#include "dogen.utility/types/io/optional_io.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/tracing_error.hpp"
#include "dogen.tracing/types/tracer.hpp"
#include "dogen/types/tracing_backend.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("tracing.tracer"));

const std::string empty;
const std::string directory_missing("Tracing data directory must be supplied.");

}

namespace dogen::tracing {

tracer::tracer(const boost::optional<tracing_configuration>& tcfg,
    const boost::optional<database_configuration>& dbcfg) :
    file_backend_(tcfg), configuration_(tcfg) {

    relational_backend_ = boost::shared_ptr<relational_backend>(
        make_relational_backend(tcfg, dbcfg));
}

void tracer::validate() const {
    /*
     * If data tracing was requested, we must have a directory in
     * which to place the data.
     */
    if (tracing_enabled() && configuration_->output_directory().empty()) {
        BOOST_LOG_SEV(lg, error) << directory_missing;
        BOOST_THROW_EXCEPTION(tracing_error(directory_missing));
    }

    BOOST_LOG_SEV(lg, debug) << "Tracer initialised. Configuration: "
                             << configuration_;
}

bool tracer::tracing_enabled() const {
    // double-bang by design.
    return !!configuration_;
}

bool tracer::detailed_tracing_enabled() const {
    return tracing_enabled() &&
        configuration_->level() == tracing_level::detail;
}

void tracer::add_references_graph(const std::string& root_vertex,
    const std::unordered_map<std::string, std::list<std::string>>&
    edges_per_model) const {
    file_backend_.add_references_graph(root_vertex, edges_per_model);
}

void tracer::start_chain(const std::string& transform_id) const {
    file_backend_.start_chain(transform_id);
}

void tracer::start_chain(const std::string& transform_id,
    const std::string& model_id) const {
    file_backend_.start_chain(transform_id, model_id);
}

void tracer::start_transform(const std::string& transform_id) const {
    file_backend_.start_transform(transform_id);
}

void tracer::start_transform(const std::string& transform_id,
    const std::string& model_id) const {
    file_backend_.start_transform(transform_id, model_id);
}

void tracer::end_chain() const {
    file_backend_.end_chain();
}

void tracer::end_transform() const {
    file_backend_.end_transform();
}

void tracer::end_tracing() const {
    BOOST_LOG_SEV(lg, debug) << "Finished tracing.";
    file_backend_.end_tracing();
}

bool tracer::operator==(const tracer& /*rhs*/) const {
    return false;
}

}
