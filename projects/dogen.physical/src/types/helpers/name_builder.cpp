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
#include "dogen.physical/types/helpers/name_builder.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("physical.helpers.name_builder"));

const std::string kernel_name("masd");
const std::string dot(".");

const std::string empty_backend("Backend cannot be empty.");
const std::string empty_facet("Facet cannot be empty.");
const std::string empty_archetype(
    "Part and facet supplied but archetype is missing.");

}

namespace dogen::physical::helpers {

name_builder& name_builder::backend(const std::string& s) {
    name_.location().backend(s);
    return *this;
}

name_builder& name_builder::part(const std::string& s) {
    name_.location().part(s);
    return *this;
}

name_builder& name_builder::facet(const std::string& s) {
    name_.location().facet(s);
    return *this;
}

name_builder& name_builder::archetype(const std::string& s) {
    name_.location().archetype(s);
    return *this;
}

void name_builder::validate() {
    /*
     * Backend must never by empty.
     */
    auto& l(name_.location());
    const bool has_backend(!l.backend().empty());
    if (!has_backend) {
        BOOST_LOG_SEV(lg, error) << empty_backend;
        BOOST_THROW_EXCEPTION(building_error(empty_backend));
    }

    /*
     * Archetypes must always have a facet, but part is optional.
     */
    const bool has_facet(!l.facet().empty());
    const bool has_archetype(!l.archetype().empty());
    if (has_archetype && !has_facet) {
        BOOST_LOG_SEV(lg, error) << empty_facet;
        BOOST_THROW_EXCEPTION(building_error(empty_facet));
    }

    /*
     * If you have a facet and a part then you must also have an
     * archetype; if you have no archetype, you can either have a part
     * or a facet or neither, but not both at the same time.
     */
    const bool has_part(!l.part().empty());
    if (has_facet && has_part && !has_archetype) {
        BOOST_LOG_SEV(lg, error) << empty_archetype;
        BOOST_THROW_EXCEPTION(building_error(empty_archetype));
    }
}

entities::name name_builder::build() {
    validate();

    auto& l(name_.location());
    l.kernel(kernel_name);
    std::string qn(kernel_name + dot + l.backend());

    const bool has_part(!l.part().empty());
    if (has_part)
        qn += dot + l.part();

    const bool has_facet(!l.facet().empty());
    if (has_facet)
        qn += dot + l.facet();

    const bool has_archetype(!l.archetype().empty());
    if (has_archetype)
        qn += dot + l.archetype();

    name_.qualified(qn);
    if (has_archetype)
        name_.simple(l.archetype());
    else if (has_facet)
        name_.simple(l.facet());
    else if (has_part)
        name_.simple(l.part());

    return name_;
}

}
