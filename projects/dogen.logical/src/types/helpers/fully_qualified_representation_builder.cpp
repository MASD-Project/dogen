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
#include "dogen.logical/types/helpers/building_error.hpp"
#include "dogen.logical/types/helpers/string_processor.hpp"
#include "dogen.logical/types/helpers/fully_qualified_representation_builder.hpp"

namespace {

using namespace dogen::utility::log;

auto
lg(logger_factory("assets.helpers.fully_qualified_representation_builder"));

}

namespace dogen::logical::helpers {

fully_qualified_representation_builder::
fully_qualified_representation_builder()
    : dot_printer_(separators::dots),
      colon_printer_(separators::double_colons) {}

void fully_qualified_representation_builder::add(const entities::name& n) {
    dot_printer_.add(n.qualified().dot());
    colon_printer_.add(n.qualified().colon());
}

void fully_qualified_representation_builder::
add(const entities::name_tree& nt) {
    dot_printer_.add_child(nt.qualified().dot());
    colon_printer_.add_child(nt.qualified().colon());
}

entities::fully_qualified_representation
fully_qualified_representation_builder::build() {
    entities::fully_qualified_representation r;

    r.dot(dot_printer_.print());
    r.colon(colon_printer_.print());

    string_processor sp;
    r.identifiable(sp.to_identifiable(r.colon()));
    return r;
}

entities::fully_qualified_representation
fully_qualified_representation_builder::
build(const entities::name& n, const bool model_name_mode) {
    dot_printer_.add(n, model_name_mode);
    colon_printer_.add(n, model_name_mode);
    return build();
}

}
