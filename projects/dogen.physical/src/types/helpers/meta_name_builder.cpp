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
#include "dogen.physical/types/helpers/qualified_meta_name_builder.hpp"
#include "dogen.physical/types/helpers/building_error.hpp"
#include "dogen.physical/types/helpers/meta_name_validator.hpp"
#include "dogen.physical/types/helpers/meta_name_builder.hpp"

namespace {

using namespace dogen::utility::log;
auto lg(logger_factory("physical.helpers.meta_name_builder"));

const std::string meta_model_name("masd");

const std::string empty_backend("Backend cannot be empty.");
const std::string empty_facet("Facet cannot be empty.");
const std::string empty_archetype(
    "Part and facet supplied but archetype is missing.");

}

namespace dogen::physical::helpers {

meta_name_builder& meta_name_builder::kernel(const std::string& s) {
    meta_name_.location().meta_model(s);
    return *this;
}

meta_name_builder& meta_name_builder::backend(const std::string& s) {
    meta_name_.location().backend(s);
    return *this;
}

meta_name_builder& meta_name_builder::facet(const std::string& s) {
    meta_name_.location().facet(s);
    return *this;
}

meta_name_builder& meta_name_builder::archetype(const std::string& s) {
    meta_name_.location().archetype(s);
    return *this;
}

entities::meta_name meta_name_builder::build() {
    /*
     * Meta-model is always hard-coded to MASD. FIXME: replace this
     * when we implement this properly.
     */
    auto& mn(meta_name_);
    auto& l(mn.location());
    l.meta_model(meta_model_name);

    /*
     * Simple and qualified names depend on what has been filled in.
     */
    const bool has_backend(!l.backend().empty());
    const bool has_facet(!l.facet().empty());
    const bool has_archetype(!l.archetype().empty());
    if (has_archetype) {
        mn.simple(l.archetype());
        mn.qualified(qualified_meta_name_builder::build_archetype(l));
        meta_name_validator::validate_archetype_name(mn);
    } else if (has_facet) {
        mn.simple(l.facet());
        mn.qualified(qualified_meta_name_builder::build_facet(l));
        meta_name_validator::validate_facet_name(mn);
    } else if (has_backend) {
        mn.simple(l.backend());
        mn.qualified(qualified_meta_name_builder::build_backend(l));
        meta_name_validator::validate_backend_name(mn);
    } else {
        mn.simple(l.meta_model());
        mn.qualified(qualified_meta_name_builder::build_kernel(l));
        meta_name_validator::validate_kernel_name(mn);
    }

    return mn;
}

}
