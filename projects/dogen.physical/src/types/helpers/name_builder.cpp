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
#include "dogen.physical/types/helpers/qualified_name_builder.hpp"
#include "dogen.physical/types/helpers/building_error.hpp"
#include "dogen.physical/types/helpers/name_validator.hpp"
#include "dogen.physical/types/helpers/name_builder.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("physical.helpers.name_builder"));

const std::string kernel_name("masd");

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

entities::name name_builder::build() {
    /*
     * Kernel is always hard-coded to MASD.
     */
    auto& l(name_.location());
    l.kernel(kernel_name);

    /*
     * Simple and qualified names depend on what has been filled in.
     */
    const bool has_part(!l.part().empty());
    const bool has_facet(!l.facet().empty());
    const bool has_archetype(!l.archetype().empty());
    if (has_archetype) {
        name_.simple(l.archetype());
        name_.qualified(qualified_name_builder::build_archetype(l));
        name_validator::validate_archetype_name(name_);
    } else if (has_facet) {
        name_.simple(l.facet());
        name_.qualified(qualified_name_builder::build_facet(l));
        name_validator::validate_facet_name(name_);
    } else if (has_part) {
        name_.simple(l.part());
        name_.qualified(qualified_name_builder::build_part(l));
        name_validator::validate_part_name(name_);
    } else {
        name_.simple(l.backend());
        name_.qualified(qualified_name_builder::build_backend(l));
        name_validator::validate_backend_name(name_);
    }

    return name_;
}

}
