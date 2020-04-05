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
#include <boost/throw_exception.hpp>
#include "dogen.utility/types/log/logger.hpp"
#include "dogen.physical/types/helpers/validation_error.hpp"
#include "dogen.physical/types/helpers/meta_name_validator.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("physical.helpers.meta_name_validator"));

const std::string empty_simple("Simple name is empty.");
const std::string empty_qualified("Qualified name is empty.");
const std::string empty_kernel("Model name is empty.");
const std::string empty_backend("Backend name is empty.");
const std::string empty_facet("Facet name is empty.");
const std::string non_empty_facet("Facet name is not empty.");
const std::string empty_archetype("Archetype is empty.");
const std::string non_empty_archetype("Archetype is not empty.");

}

namespace dogen::physical::helpers {

void meta_name_validator::common_validation(const entities::meta_name& mn) {
    /*
     * Simple name must be populated.
     */
    if (mn.simple().empty()) {
        BOOST_LOG_SEV(lg, error) << empty_simple;
        BOOST_THROW_EXCEPTION(validation_error(empty_simple));
    }

    /*
     * Qualified name must be populated.
     */
    if (mn.qualified().empty()) {
        BOOST_LOG_SEV(lg, error) << empty_qualified;
        BOOST_THROW_EXCEPTION(validation_error(empty_qualified));
    }

    /*
     * All locations must belong to a kernel.
     */
    const auto& l(mn.location());
    if (l.kernel().empty()) {
        BOOST_LOG_SEV(lg, error) << empty_kernel;
        BOOST_THROW_EXCEPTION(validation_error(empty_kernel));
    }

    /*
     * All locations must belong to a backend.
     */
    if (l.backend().empty()) {
        BOOST_LOG_SEV(lg, error) << empty_backend;
        BOOST_THROW_EXCEPTION(validation_error(empty_backend));
    }
}

void meta_name_validator::validate_backend_name(const entities::meta_name& mn) {
    common_validation(mn);

    /*
     * Facet must not be populated.
     */
    const auto& l(mn.location());
    if (!l.facet().empty()) {
        BOOST_LOG_SEV(lg, error) << non_empty_facet;
        BOOST_THROW_EXCEPTION(validation_error(non_empty_facet));
    }

    /*
     * Archetype must not be populated.
     */
    if (!l.archetype().empty()) {
        BOOST_LOG_SEV(lg, error) << non_empty_archetype;
        BOOST_THROW_EXCEPTION(validation_error(non_empty_archetype));
    }
}

void meta_name_validator::validate_facet_name(const entities::meta_name& mn) {
    common_validation(mn);

    /*
     * Facet must be populated.
     */
    const auto& l(mn.location());
    if (l.facet().empty()) {
        BOOST_LOG_SEV(lg, error) << empty_facet;
        BOOST_THROW_EXCEPTION(validation_error(empty_facet));
    }

    /*
     * Archetype must not be populated.
     */
    if (!l.archetype().empty()) {
        BOOST_LOG_SEV(lg, error) << non_empty_archetype;
        BOOST_THROW_EXCEPTION(validation_error(non_empty_archetype));
    }
}

void meta_name_validator::validate_archetype_name(const entities::meta_name& mn) {
    common_validation(mn);

    /*
     * All locations must belong to a facet.
     */
    const auto& l(mn.location());
    if (l.facet().empty()) {
        BOOST_LOG_SEV(lg, error) << empty_facet;
        BOOST_THROW_EXCEPTION(validation_error(empty_facet));
    }

    /*
     * Archetype must be populated
     */
    if (l.archetype().empty()) {
        BOOST_LOG_SEV(lg, error) << empty_archetype;
        BOOST_THROW_EXCEPTION(validation_error(empty_archetype));
    }
}

}
