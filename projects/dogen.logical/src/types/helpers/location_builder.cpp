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
#include <sstream>
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.utility/types/io/list_io.hpp"
#include "dogen.utility/types/string/splitter.hpp"
#include "dogen.logical/io/entities/location_io.hpp"
#include "dogen.logical/types/helpers/building_error.hpp"
#include "dogen.logical/types/helpers/location_builder.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("logical.helpers.location_builder"));

const std::string empty_model_modules("Model modules are empty.");
const std::string empty_internal_modules("Internal modules are empty.");

}

namespace dogen::logical::helpers {

void location_builder::external_modules(const std::string& em) {
    if (em.empty())
        return;

    using utility::string::splitter;
    location_.external_modules(splitter::split_scoped(em));
    BOOST_LOG_SEV(lg, debug) << "Added external modules: " << em;
}

void
location_builder::external_modules(const std::list<std::string>& em) {
    location_.external_modules(em);
    BOOST_LOG_SEV(lg, debug) << "Added external modules: " << em;
}

void location_builder::model_modules(const std::string& mm) {
    if (mm.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_model_modules;
        BOOST_THROW_EXCEPTION(building_error(empty_model_modules));
    }

    using utility::string::splitter;
    location_.model_modules(splitter::split_scoped(mm));
    BOOST_LOG_SEV(lg, debug) << "Added model modules: " << mm;
}

void location_builder::
model_modules(const std::list<std::string>& mm) {
    location_.model_modules(mm);
    BOOST_LOG_SEV(lg, debug) << "Added model modules: " << mm;
}

void location_builder::internal_modules(const std::string& im) {
    if (im.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_internal_modules;
        BOOST_THROW_EXCEPTION(building_error(empty_internal_modules));
    }

    using utility::string::splitter;
    location_.internal_modules(splitter::split_scoped(im));
    BOOST_LOG_SEV(lg, debug) << "Added internal modules: " << im;
}

void location_builder::internal_modules(
    const std::list<std::string>& im) {
    location_.internal_modules(im);
    BOOST_LOG_SEV(lg, debug) << "Added internal models: " << im;
}

void location_builder::location(const entities::location& l) {
    location_ = l;
}

entities::location location_builder::build() {
    BOOST_LOG_SEV(lg, debug) << "Built location: " << location_;
    return location_;
}

}
