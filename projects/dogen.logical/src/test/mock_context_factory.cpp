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
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.tracing/types/tracer.hpp"
#include "dogen.physical/types/entities/meta_model.hpp"
#include "dogen/types/tracing_configuration.hpp"
#include "dogen.logical/test/mock_context_factory.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("logical.transforms.mock_context_factory"));

}

namespace dogen::logical::test {

transforms::context mock_context_factory::make() {
    BOOST_LOG_SEV(lg, debug) << "Creating the mock context.";

    transforms::context r;
    r.physical_meta_model(boost::make_shared<physical::entities::meta_model>());

    configuration cfg;
    const auto activity("testing");
    auto tracer(boost::make_shared<tracing::tracer>(cfg, activity));
    r.tracer(tracer);

    BOOST_LOG_SEV(lg, debug) << "Created the context.";
    return r;
}

}
