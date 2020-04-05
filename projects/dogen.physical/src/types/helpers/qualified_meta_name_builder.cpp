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
#include "dogen.physical/types/helpers/building_error.hpp"
#include "dogen.physical/types/helpers/qualified_meta_name_builder.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("physical.helpers.qualified_meta_name_builder"));

const std::string kernel_name("masd");
const std::string canonical_name("canonical_archetype");
const std::string dot(".");

const std::string empty_kernel("Kernel cannot be empty.");
const std::string empty_backend("Backend cannot be empty.");
const std::string empty_facet("Facet cannot be empty.");
const std::string empty_archetype(
    "Part and facet supplied but archetype is missing.");

}

namespace dogen::physical::helpers {

std::string qualified_meta_name_builder::build_kernel(const entities::location& l) {
    const auto& k(l.kernel());
    if (k.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_kernel;
        BOOST_THROW_EXCEPTION(building_error(empty_kernel));
    }
    return k;
}

std::string qualified_meta_name_builder::build_kernel(const entities::meta_name& mn) {
    return build_kernel(mn.location());
}

std::string qualified_meta_name_builder::build_backend(const entities::location& l) {
    const auto& b(l.backend());
    if (b.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_backend;
        BOOST_THROW_EXCEPTION(building_error(empty_backend));
    }

    return build_kernel(l) + dot + b;
}

std::string qualified_meta_name_builder::build_backend(const entities::meta_name& mn) {
    return build_backend(mn.location());
}

std::string qualified_meta_name_builder::build_facet(const entities::location& l,
    const bool add_canonical) {

    const auto& f(l.facet());
    if (f.empty()) {
        BOOST_LOG_SEV(lg, error) << empty_facet;
        BOOST_THROW_EXCEPTION(building_error(empty_facet));
    }

    std::string r;
    r = build_backend(l) + dot + f;

    if (add_canonical)
        r += dot + canonical_name;

    return r;
}

std::string qualified_meta_name_builder::build_facet(const entities::meta_name& mn,
    const bool add_canonical) {
    return build_facet(mn.location(), add_canonical);
}

std::string
qualified_meta_name_builder::build_archetype(const entities::location& l) {
    std::string r(build_backend(l));
    const bool has_facet(!l.facet().empty());
    if (has_facet)
        r += dot + l.facet();

    const bool has_archetype(!l.archetype().empty());
    if (has_archetype)
        r += dot + l.archetype();

    return r;
}

std::string qualified_meta_name_builder::
build_archetype(const entities::meta_name& mn) {
    return build_archetype(mn.location());
}

}
