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
#include "dogen.identification/types/helpers/building_error.hpp"
#include "dogen.identification/types/helpers/identifiable_factory.hpp"
#include "dogen.identification/types/helpers/qualified_name_representations_builder.hpp"

namespace {

using namespace dogen::utility::log;

auto
lg(logger_factory("identification.helpers.qualified_name_representations_builder"));

}

namespace dogen::identification::helpers {

qualified_name_representations_builder::
qualified_name_representations_builder()
    : dot_printer_(separators::dots),
      colon_printer_(separators::double_colons) {}

void qualified_name_representations_builder::add(const entities::logical_name& n) {
    dot_printer_.add(n.qualified().dot());
    colon_printer_.add(n.qualified().colon());
}

void qualified_name_representations_builder::
add(const entities::logical_name_tree& nt) {
    dot_printer_.add_child(nt.qualified().dot());
    colon_printer_.add_child(nt.qualified().colon());
}

entities::qualified_representations
qualified_name_representations_builder::build() {
    entities::qualified_representations r;

    r.dot(dot_printer_.print());
    r.colon(colon_printer_.print());
    r.identifiable(identifiable_factory::make(r.colon()));
    return r;
}

entities::qualified_representations
qualified_name_representations_builder::
build(const entities::logical_name& n, const bool model_name_mode) {
    dot_printer_.add(n, model_name_mode);
    colon_printer_.add(n, model_name_mode);
    return build();
}

}
