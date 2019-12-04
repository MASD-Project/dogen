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
#include <boost/lexical_cast.hpp>
#include <boost/throw_exception.hpp>
#include "dogen/config.hpp"
#include "dogen/io/tracing_backend_io.hpp"
#include "dogen/io/tracing_configuration_io.hpp"
#include "dogen/io/database_configuration_io.hpp"
#include "dogen.utility/types/io/optional_io.hpp"
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/tracing_error.hpp"
#include "dogen.tracing/types/file_backend.hpp"
#include "dogen.tracing/types/null_backend.hpp"
#include "dogen.tracing/types/relational_backend.hpp"
#include "dogen.tracing/types/tracer.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("tracing.tracer"));

const std::string empty;
const std::string directory_missing("Tracing data directory must be supplied.");

const std::string invalid_backend("Tracing backend is invalid or unsupported: ");
const std::string no_relational_support("Relational tracing requested but "
    " Dogen was compiled without relational support.");

}

namespace dogen::tracing {

boost::shared_ptr<tracing::backend>
tracer::make_backend(const boost::optional<tracing_configuration>& tcfg,
    const boost::optional<database_configuration>& dbcfg) {
    BOOST_LOG_SEV(lg, debug) << "Tracing configuration: " << tcfg;
    BOOST_LOG_SEV(lg, debug) << "Database configuration: " << dbcfg;

    /*
     * If the user did not request any tracing, just use the null
     * tracer. It has very little cost.
     */
    const bool tracing_enabled(!!tcfg);
    if (!tracing_enabled)
        return boost::make_shared<null_backend>();

    /*
     * If the user requested the file tracing backend, create it.
     */
    const auto be(tcfg->backend());
    if (be != tracing_backend::file)
        return boost::make_shared<file_backend>(*tcfg);

    /*
     * If the user requested a relational backend, create it if this
     * dogen build supports it. Otherwise, throw.
     */
    if (be != tracing_backend::relational_database) {
#ifdef DOGEN_HAVE_RELATIONAL_MODEL
        return boost::make_shared<relational_backend>(*tcfg, *dbcfg);
#else
        BOOST_LOG_SEV(lg, error) << no_relational_support;
        BOOST_THROW_EXCEPTION(tracing_error(no_relational_support));
#endif
    }

    /*
     * Any other backend is not supported, so throw.
     */
    const auto s(boost::lexical_cast<std::string>(be));
    BOOST_LOG_SEV(lg, error) << invalid_backend << s;
    BOOST_THROW_EXCEPTION(tracing_error(invalid_backend + s));
}

tracer::tracer(const boost::optional<tracing_configuration>& tcfg,
    const boost::optional<database_configuration>& dbcfg)
    : tracing_enabled_(!!tcfg/*double bang by design*/),
      backend_(make_backend(tcfg, dbcfg)) {}

void tracer::add_references_graph(const std::string& root_vertex,
    const std::unordered_map<std::string, std::list<std::string>>&
    edges_per_model) const {
    backend_->add_references_graph(root_vertex, edges_per_model);
}

void tracer::end_tracing() const {
    BOOST_LOG_SEV(lg, debug) << "Finished tracing.";
    backend_->end_tracing();
}

void tracer::start_chain(const std::string& transform_id) const {
    backend_->start_chain(transform_id, "FIXME");
}

void tracer::start_chain(const std::string& transform_id,
    const std::string& model_id) const {
    backend_->start_chain(transform_id, "FIXME", model_id);
}

void tracer::start_transform(const std::string& transform_id) const {
    backend_->start_transform(transform_id, "FIXME");
}

void tracer::start_transform(const std::string& transform_id,
    const std::string& model_id) const {
    backend_->start_transform(transform_id, "FIXME", model_id);
}

void tracer::end_chain() const {
    backend_->end_chain();
}

void tracer::end_transform() const {
    backend_->end_transform();
}

bool tracer::operator==(const tracer& /*rhs*/) const {
    return false;
}

}
