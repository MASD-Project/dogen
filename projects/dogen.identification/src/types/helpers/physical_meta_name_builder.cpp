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
#include "dogen.identification/types/helpers/physical_meta_id_builder.hpp"
#include "dogen.identification/types/helpers/building_error.hpp"
#include "dogen.identification/types/helpers/physical_meta_name_validator.hpp"
#include "dogen.identification/types/helpers/physical_meta_name_builder.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("identification.helpers.physical_meta_name_builder"));

const std::string meta_model_name("masd");

const std::string empty_backend("Backend cannot be empty.");
const std::string empty_facet("Facet cannot be empty.");
const std::string empty_archetype(
    "Part and facet supplied but archetype is missing.");

}

namespace dogen::identification::helpers {

physical_meta_name_builder&
physical_meta_name_builder::meta_model(const std::string& s) {
    meta_name_.location().meta_model(s);
    return *this;
}

physical_meta_name_builder&
physical_meta_name_builder::backend(const std::string& s) {
    meta_name_.location().backend(s);
    return *this;
}

physical_meta_name_builder&
physical_meta_name_builder::part(const std::string& s) {
    meta_name_.location().part(s);
    return *this;
}

physical_meta_name_builder&
physical_meta_name_builder::facet(const std::string& s) {
    meta_name_.location().facet(s);
    return *this;
}

physical_meta_name_builder&
physical_meta_name_builder::archetype(const std::string& s) {
    meta_name_.location().archetype(s);
    return *this;
}

entities::physical_meta_name physical_meta_name_builder::build() {
    /*
     * Meta-model is always hard-coded to MASD.
     */
    auto& mn(meta_name_);
    mn.location().meta_model(meta_model_name);

    /*
     * Simple and qualified meta-names depend on what has been filled in.
     */
    const auto& l(mn.location());
    const bool has_backend(!l.backend().empty());
    const bool has_part(!l.part().empty());
    const bool has_facet(!l.facet().empty());
    const bool has_archetype(!l.archetype().empty());
    if (has_archetype) {
        mn.simple(l.archetype());
        mn.id(physical_meta_id_builder::build_archetype(l));
        physical_meta_name_validator::validate_archetype_name(mn);
    } else if (has_facet) {
        mn.simple(l.facet());
        mn.id(physical_meta_id_builder::build_facet(l));
        physical_meta_name_validator::validate_facet_name(mn);
    } else if (has_part) {
        mn.simple(l.part());
        mn.id(physical_meta_id_builder::build_part(l));
        physical_meta_name_validator::validate_part_name(mn);
    } else if (has_backend) {
        mn.simple(l.backend());
        mn.id(physical_meta_id_builder::build_backend(l));
        physical_meta_name_validator::validate_backend_name(mn);
    } else {
        mn.simple(l.meta_model());
        mn.id(physical_meta_id_builder::build_meta_model(l));
        physical_meta_name_validator::validate_meta_model_name(mn);
    }

    return mn;
}

}
